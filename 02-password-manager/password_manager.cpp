
#include <sodium.h>
#include <termios.h>
#include <unistd.h>
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

struct PasswordEntry {
    uint32_t id;
    string company;
    string accountType;
    string accountId;
    string password;
};

struct Vault {
    vector<unsigned char> salt;
    vector<unsigned char> nonce;
    vector<unsigned char> ciphertext;
};

const string VAULT_FILE = "vault.txt";
const string TEMP_FILE = "vault.txt.tmp";

string readLine(const string& prompt) {
    cout << prompt;
    string value;
    getline(cin, value);
    return value;
}

string readHidden(const string& prompt) {
    cout << prompt;
    cout.flush();

    termios oldSettings{};
    termios newSettings{};

    if (tcgetattr(STDIN_FILENO, &oldSettings) != 0) {
        string value;
        getline(cin, value);
        return value;
    }

    newSettings = oldSettings;
    newSettings.c_lflag &= ~ECHO;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &newSettings) != 0) {
        string value;
        getline(cin, value);
        return value;
    }

    string value;
    getline(cin, value);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &oldSettings);
    cout << '\n';

    return value;
}

string encodeHex(const vector<unsigned char>& data) {
    string result(data.size() * 2, '\0');
    sodium_bin2hex(result.data(), result.size() + 1, data.data(), data.size());
    return result;
}

vector<unsigned char> decodeHex(const string& value, size_t expectedSize) {
    vector<unsigned char> result(expectedSize);
    size_t decodedLength = 0;

    if (sodium_hex2bin(
            result.data(), result.size(),
            value.c_str(), value.size(),
            nullptr, &decodedLength, nullptr) != 0 ||
        decodedLength != expectedSize) {
        throw runtime_error("Invalid vault format.");
    }

    return result;
}

string encodeBase64(const vector<unsigned char>& data) {
    size_t size = sodium_base64_encoded_len(
        data.size(), sodium_base64_VARIANT_ORIGINAL);

    string result(size, '\0');

    sodium_bin2base64(
        result.data(), result.size(),
        data.data(), data.size(),
        sodium_base64_VARIANT_ORIGINAL);

    result.resize(strlen(result.c_str()));
    return result;
}

vector<unsigned char> decodeBase64(const string& value) {
    vector<unsigned char> result(value.size());
    size_t decodedLength = 0;

    if (sodium_base642bin(
            result.data(), result.size(),
            value.c_str(), value.size(),
            nullptr, &decodedLength, nullptr,
            sodium_base64_VARIANT_ORIGINAL) != 0) {
        throw runtime_error("Invalid encrypted data.");
    }

    result.resize(decodedLength);
    return result;
}

void appendNumber(vector<unsigned char>& data, uint32_t value) {
    for (int i = 0; i < 4; ++i) {
        data.push_back(static_cast<unsigned char>((value >> (i * 8)) & 0xff));
    }
}

uint32_t readNumber(const vector<unsigned char>& data, size_t& position) {
    if (position + 4 > data.size()) {
        throw runtime_error("Invalid vault contents.");
    }

    uint32_t value = 0;

    for (int i = 0; i < 4; ++i) {
        value |= static_cast<uint32_t>(data[position++]) << (i * 8);
    }

    return value;
}

void appendString(vector<unsigned char>& data, const string& value) {
    if (value.size() > 1024 * 1024) {
        throw runtime_error("Field is too large.");
    }

    appendNumber(data, static_cast<uint32_t>(value.size()));
    data.insert(data.end(), value.begin(), value.end());
}

string readString(const vector<unsigned char>& data, size_t& position) {
    uint32_t length = readNumber(data, position);

    if (length > 1024 * 1024 || position + length > data.size()) {
        throw runtime_error("Invalid vault contents.");
    }

    string value(
        reinterpret_cast<const char*>(data.data() + position), length);

    position += length;
    return value;
}

vector<unsigned char> serializeEntries(const vector<PasswordEntry>& entries) {
    vector<unsigned char> data;
    appendNumber(data, static_cast<uint32_t>(entries.size()));

    for (const auto& entry : entries) {
        appendNumber(data, entry.id);
        appendString(data, entry.company);
        appendString(data, entry.accountType);
        appendString(data, entry.accountId);
        appendString(data, entry.password);
    }

    return data;
}

vector<PasswordEntry> deserializeEntries(
    const vector<unsigned char>& data) {
    size_t position = 0;
    uint32_t count = readNumber(data, position);

    if (count > 100000) {
        throw runtime_error("Invalid number of records.");
    }

    vector<PasswordEntry> entries;
    entries.reserve(count);

    for (uint32_t i = 0; i < count; ++i) {
        PasswordEntry entry;
        entry.id = readNumber(data, position);
        entry.company = readString(data, position);
        entry.accountType = readString(data, position);
        entry.accountId = readString(data, position);
        entry.password = readString(data, position);
        entries.push_back(move(entry));
    }

    if (position != data.size()) {
        throw runtime_error("Invalid vault contents.");
    }

    return entries;
}

bool deriveKey(
    const string& masterPassword,
    const vector<unsigned char>& salt,
    unsigned char* key) {
    return crypto_pwhash(
        key,
        crypto_aead_xchacha20poly1305_ietf_KEYBYTES,
        masterPassword.data(),
        masterPassword.size(),
        salt.data(),
        crypto_pwhash_OPSLIMIT_INTERACTIVE,
        crypto_pwhash_MEMLIMIT_INTERACTIVE,
        crypto_pwhash_ALG_ARGON2ID13) == 0;
}

vector<unsigned char> encryptData(
    const vector<unsigned char>& plaintext,
    const unsigned char* key,
    vector<unsigned char>& nonce) {
    nonce.resize(crypto_aead_xchacha20poly1305_ietf_NPUBBYTES);
    randombytes_buf(nonce.data(), nonce.size());

    vector<unsigned char> ciphertext(
        plaintext.size() +
        crypto_aead_xchacha20poly1305_ietf_ABYTES);

    unsigned long long ciphertextLength = 0;

    if (crypto_aead_xchacha20poly1305_ietf_encrypt(
            ciphertext.data(), &ciphertextLength,
            plaintext.data(), plaintext.size(),
            nullptr, 0, nullptr, nonce.data(), key) != 0) {
        throw runtime_error("Encryption failed.");
    }

    ciphertext.resize(ciphertextLength);
    return ciphertext;
}

bool decryptData(
    const vector<unsigned char>& ciphertext,
    const vector<unsigned char>& nonce,
    const unsigned char* key,
    vector<unsigned char>& plaintext) {
    if (ciphertext.size() < crypto_aead_xchacha20poly1305_ietf_ABYTES) {
        return false;
    }

    plaintext.resize(
        ciphertext.size() -
        crypto_aead_xchacha20poly1305_ietf_ABYTES);

    unsigned long long plaintextLength = 0;

    if (crypto_aead_xchacha20poly1305_ietf_decrypt(
            plaintext.data(), &plaintextLength,
            nullptr,
            ciphertext.data(), ciphertext.size(),
            nullptr, 0, nonce.data(), key) != 0) {
        sodium_memzero(plaintext.data(), plaintext.size());
        plaintext.clear();
        return false;
    }

    plaintext.resize(plaintextLength);
    return true;
}

void saveVault(
    const vector<PasswordEntry>& entries,
    const vector<unsigned char>& salt,
    const unsigned char* key) {
    vector<unsigned char> plaintext = serializeEntries(entries);
    vector<unsigned char> nonce;
    vector<unsigned char> ciphertext = encryptData(plaintext, key, nonce);

    string contents =
        "CPP-PASSWORD-VAULT-1\n" +
        encodeHex(salt) + "\n" +
        encodeHex(nonce) + "\n" +
        encodeBase64(ciphertext) + "\n";

    sodium_memzero(plaintext.data(), plaintext.size());

    {
        ofstream output(TEMP_FILE, ios::binary | ios::trunc);

        if (!output) {
            throw runtime_error("Cannot create temporary vault file.");
        }

        output.write(contents.data(), contents.size());
        output.flush();

        if (!output) {
            output.close();
            filesystem::remove(TEMP_FILE);
            throw runtime_error("Could not write vault data.");
        }
    }

    if (std::rename(TEMP_FILE.c_str(), VAULT_FILE.c_str()) != 0) {
        filesystem::remove(TEMP_FILE);
        throw runtime_error("Could not replace vault file.");
    }
}

Vault loadVaultFile() {
    ifstream input(VAULT_FILE, ios::binary);

    if (!input) {
        throw runtime_error("Cannot open vault file.");
    }

    string version, saltLine, nonceLine, ciphertextLine, extra;

    if (!getline(input, version) ||
        !getline(input, saltLine) ||
        !getline(input, nonceLine) ||
        !getline(input, ciphertextLine) ||
        getline(input, extra) ||
        version != "CPP-PASSWORD-VAULT-1") {
        throw runtime_error("Invalid vault file.");
    }

    Vault vault;
    vault.salt = decodeHex(saltLine, crypto_pwhash_SALTBYTES);
    vault.nonce = decodeHex(
        nonceLine, crypto_aead_xchacha20poly1305_ietf_NPUBBYTES);
    vault.ciphertext = decodeBase64(ciphertextLine);

    return vault;
}

uint32_t nextId(const vector<PasswordEntry>& entries) {
    uint32_t highest = 0;

    for (const auto& entry : entries) {
        highest = max(highest, entry.id);
    }

    if (highest == numeric_limits<uint32_t>::max()) {
        throw runtime_error("No more record IDs are available.");
    }

    return highest + 1;
}

void addEntry(vector<PasswordEntry>& entries) {
    PasswordEntry entry;

    entry.id = nextId(entries);
    entry.company = readLine("Company or service: ");
    entry.accountType = readLine("Account ID type (Email/Username/Phone): ");
    entry.accountId = readLine("Account ID: ");
    entry.password = readHidden("Account password: ");

    if (entry.company.empty() || entry.accountType.empty() ||
        entry.accountId.empty() || entry.password.empty()) {
        sodium_memzero(entry.password.data(), entry.password.size());
        cout << "All fields are required.\n";
        return;
    }

    entries.push_back(move(entry));
    cout << "Account added. Remember to save your changes.\n";
}

void showEntries(const vector<PasswordEntry>& entries) {
    if (entries.empty()) {
        cout << "No saved accounts.\n";
        return;
    }

    for (const auto& entry : entries) {
        cout << "\nRecord ID: " << entry.id
             << "\nCompany: " << entry.company
             << "\nAccount type: " << entry.accountType
             << "\nAccount ID: " << entry.accountId
             << "\nPassword: " << entry.password
             << "\n-------------------------\n";
    }
}

void updateEntry(vector<PasswordEntry>& entries) {
    string input = readLine("Record ID to update: ");
    uint32_t id;

    try {
        size_t position = 0;
        unsigned long value = stoul(input, &position);

        if (position != input.size() ||
            value > numeric_limits<uint32_t>::max()) {
            throw runtime_error("Invalid ID.");
        }

        id = static_cast<uint32_t>(value);
    } catch (...) {
        cout << "Invalid record ID.\n";
        return;
    }

    auto it = find_if(entries.begin(), entries.end(),
        [id](const PasswordEntry& entry) {
            return entry.id == id;
        });

    if (it == entries.end()) {
        cout << "Record not found.\n";
        return;
    }

    cout << "1. Update company\n"
         << "2. Update account ID type\n"
         << "3. Update account ID\n"
         << "4. Update password\n";

    string choice = readLine("Choose field: ");

    if (choice == "1") {
        it->company = readLine("New company: ");
    } else if (choice == "2") {
        it->accountType = readLine("New account ID type: ");
    } else if (choice == "3") {
        it->accountId = readLine("New account ID: ");
    } else if (choice == "4") {
        string updated = readHidden("New account password: ");

        if (updated.empty()) {
            cout << "Password cannot be empty.\n";
            return;
        }

        sodium_memzero(it->password.data(), it->password.size());
        it->password = move(updated);
    } else {
        cout << "Invalid choice.\n";
        return;
    }

    cout << "Record updated. Remember to save your changes.\n";
}

void deleteEntry(vector<PasswordEntry>& entries) {
    string input = readLine("Record ID to delete: ");
    uint32_t id;

    try {
        size_t position = 0;
        unsigned long value = stoul(input, &position);

        if (position != input.size() ||
            value > numeric_limits<uint32_t>::max()) {
            throw runtime_error("Invalid ID.");
        }

        id = static_cast<uint32_t>(value);
    } catch (...) {
        cout << "Invalid record ID.\n";
        return;
    }

    auto it = find_if(entries.begin(), entries.end(),
        [id](const PasswordEntry& entry) {
            return entry.id == id;
        });

    if (it == entries.end()) {
        cout << "Record not found.\n";
        return;
    }

    string confirmation = readLine("Delete this record? (yes/no): ");

    if (confirmation != "yes") {
        cout << "Deletion cancelled.\n";
        return;
    }

    sodium_memzero(it->password.data(), it->password.size());
    entries.erase(it);
    cout << "Record deleted. Remember to save your changes.\n";
}

bool unlockVault(
    const Vault& vault,
    vector<PasswordEntry>& entries,
    unsigned char* key) {
    for (int attempt = 1; attempt <= 3; ++attempt) {
        string masterPassword = readHidden("Master password: ");

        if (!deriveKey(masterPassword, vault.salt, key)) {
            sodium_memzero(masterPassword.data(), masterPassword.size());
            cout << "Key derivation failed.\n";
            return false;
        }

        sodium_memzero(masterPassword.data(), masterPassword.size());

        vector<unsigned char> plaintext;

        if (decryptData(vault.ciphertext, vault.nonce, key, plaintext)) {
            try {
                entries = deserializeEntries(plaintext);
                sodium_memzero(plaintext.data(), plaintext.size());
                return true;
            } catch (...) {
                sodium_memzero(plaintext.data(), plaintext.size());
                sodium_memzero(key, crypto_aead_xchacha20poly1305_ietf_KEYBYTES);
                throw;
            }
        }

        sodium_memzero(key, crypto_aead_xchacha20poly1305_ietf_KEYBYTES);

        cout << "Incorrect master password. Attempts remaining: "
             << 3 - attempt << '\n';
    }

    return false;
}

int main() {
    if (sodium_init() < 0) {
        cerr << "Cryptographic initialization failed.\n";
        return 1;
    }

    try {
        vector<PasswordEntry> entries;
        vector<unsigned char> salt(crypto_pwhash_SALTBYTES);
        unsigned char key[crypto_aead_xchacha20poly1305_ietf_KEYBYTES]{};

        if (!filesystem::exists(VAULT_FILE)) {
            cout << "Create your master password.\n";

            string first = readHidden("New master password (at least 12 characters): ");

            if (first.size() < 12) {
                sodium_memzero(first.data(), first.size());
                cout << "Master password must contain at least 12 characters.\n";
                return 1;
            }

            string second = readHidden("Confirm master password: ");

            if (first != second) {
                sodium_memzero(first.data(), first.size());
                sodium_memzero(second.data(), second.size());
                cout << "Passwords do not match.\n";
                return 1;
            }

            randombytes_buf(salt.data(), salt.size());

            if (!deriveKey(first, salt, key)) {
                sodium_memzero(first.data(), first.size());
                sodium_memzero(second.data(), second.size());
                cerr << "Key derivation failed.\n";
                return 1;
            }

            sodium_memzero(first.data(), first.size());
            sodium_memzero(second.data(), second.size());

            saveVault(entries, salt, key);
            cout << "Encrypted vault created.\n";
        } else {
            Vault vault = loadVaultFile();
            salt = vault.salt;

            if (!unlockVault(vault, entries, key)) {
                sodium_memzero(key, sizeof(key));
                cout << "Vault remains locked.\n";
                return 1;
            }

            cout << "Vault unlocked.\n";
        }

        bool dirty = false;
        bool running = true;

        while (running) {
            cout << "\n===== PASSWORD MANAGER =====\n"
                 << "1. Save new password\n"
                 << "2. Update password\n"
                 << "3. Delete password\n"
                 << "4. Show all passwords\n"
                 << "5. Save changes\n"
                 << "6. Lock vault\n"
                 << "7. Exit\n";

            string choice = readLine("Choose an option: ");

            if (choice == "1") {
                size_t before = entries.size();
                addEntry(entries);
                if (entries.size() != before) dirty = true;
            } else if (choice == "2") {
                updateEntry(entries);
                dirty = true;
            } else if (choice == "3") {
                size_t before = entries.size();
                deleteEntry(entries);
                if (entries.size() != before) dirty = true;
            } else if (choice == "4") {
                showEntries(entries);
            } else if (choice == "5") {
                saveVault(entries, salt, key);
                dirty = false;
                cout << "Vault saved successfully.\n";
            } else if (choice == "6" || choice == "7") {
                if (dirty) {
                    string answer = readLine("Unsaved changes. Save before continuing? (yes/no/cancel): ");

                    if (answer == "cancel") continue;

                    if (answer == "yes") {
                        saveVault(entries, salt, key);
                    } else if (answer != "no") {
                        cout << "Invalid choice.\n";
                        continue;
                    }
                }

                for (auto& entry : entries) {
                    sodium_memzero(entry.password.data(), entry.password.size());
                }

                entries.clear();
                sodium_memzero(key, sizeof(key));

                if (choice == "7") {
                    running = false;
                } else {
                    Vault vault = loadVaultFile();
                    salt = vault.salt;

                    if (!unlockVault(vault, entries, key)) {
                        sodium_memzero(key, sizeof(key));
                        cout << "Vault remains locked.\n";
                        return 1;
                    }

                    dirty = false;
                    cout << "Vault unlocked.\n";
                }
            } else {
                cout << "Invalid choice.\n";
            }
        }

        sodium_memzero(key, sizeof(key));
        cout << "Password Manager closed.\n";
    } catch (const exception& error) {
        cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
