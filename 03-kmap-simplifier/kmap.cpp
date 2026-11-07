#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

// template <size_t R, size_t C>
// void displaykmap(int (&kmap)[R][C],int n)
// {
//     cout<< "K-Map Structure :\n";
//     for (int i =0;i<n;i++){
//         for(int j=0;j<n;j++){
//             cout<<" "<<kmap[i][j]<<" ";
//         }
//         cout<<"\n";
//     }
// }
// void displaystr(string &s){
//     cout<<"String : ";
//     for(int i=1;s[i]!='\0';i++){
//         cout<<s[i];
//     }
//     cout<<"\n";
// }
void displayexp(string &s3){
    cout<<"Kmap Evaluation :";
    for(int i=1;s3[i]!='\0';i=i+3){
        if((s3[i]=='X')&&(s3[i+1]=='1')){
            cout<<"B";
        }
        else if((s3[i]=='X')&&(s3[i+1]=='0')){
            cout<<"B̄";
        }
        else if((s3[i]=='1')&&(s3[i+1]=='X')){
            cout<<"A";
        }
        else if((s3[i]=='0')&&(s3[i+1]=='X')){
            cout<<"Ā";
        }
        else if((s3[i]=='0')&&(s3[i+1]=='0')){
            cout<<"ĀB̄";
        }
        else if((s3[i]=='0')&&(s3[i+1]=='1')){
            cout<<"ĀB";
        }
        else if((s3[i]=='1')&&(s3[i+1]=='0')){
            cout<<"AB̄";
        }
        else if((s3[i]=='1')&&(s3[i+1]=='1')){
            cout<<"AB";
        }
        if(i + 3 < s3.size()){
            cout << "+";
        }
    }
}

void check2pair(string &s, string &s2);
void sortstr(string &s2,string &s3);

int takeinput(int nel,vector<int>& arr){
    int flag=0;
    cout<<"Please Enter K map values(0 & 1):\n";
    for(int i=0;i<nel;i++){
        cin>>arr[i];
    }

    for(int j=0;j<nel;j++){
        if(arr[j]!=1&&arr[j]!=0){
            return 2;
        }
        if(arr[j]==1){
            flag++;
        }
    }

    if(flag==nel){
        return 1;
    }
    else if(flag==0){
        return 0;
    }
    else {
        return 3;
    }
}

void var2(int nel,vector<int>& arr){

    string s,s2,s3;
    s.reserve(100);
    s2.reserve(100);
    s3.reserve(100);

    int kmap[2][2];
    int count =0,num=0,numc=0;

    for (int i =0;i<2;i++){
        for(int j=0;j<2;j++){
            kmap[i][j] = arr[count];
            if(kmap[i][j]==1){
                num=i*10+j;
                if(num!=0&&num!=1){
                    s += "," + to_string(num);
                    num=0;
                }
                else if(num==0) {
                    s += ",00" ;
                }
                else if(num==1){
                    s += ",01";
                }
            }
            count++;
        }
    }
    check2pair(s,s2);
    sortstr(s2,s3);
    displayexp(s3);
}
void var3(int nel,vector<int>& arr){
    int kmap[2][4];
}
void var4(int nel,vector<int>& arr){
    int kmap[4][4];
} 

void sortstr(string &s2,string &s3){
    string s4;
    s4.reserve(3);
    int flag =0;
    for(int i=1;s2[i]!='\0';i=i+3){
        for(int j=1;s2[j]!='\0';j=j+3){
            if(s2[j]=='X'||s2[j+1]=='X'){
                flag=1;
                s4 = s2.substr(j-1, 3);
                if (s3.find(s4) == string::npos) {
                    s3+=s4;
                }            
            }
        }
    }
    if(flag==0){
        s3.clear();
        s3=s2;
    }
}
void check2pair(string &s,string &s2){
    for(int i=1;s[i]!='\0';i=i+3){
        int flag=0;
        for(int j=1;s[j]!='\0';j=j+3){

            if(s[i]==s[j] && i!=j){
                s2+=",";
                s2+=s[i];
                s2+="X";
                flag=1;
                continue;
            }
            else if(s[i+1]==s[j+1] && i!=j){
                s2+=",";
                s2+="X";
                s2+=s[i+1];
                flag=1;
                continue;
            }
        }
        if(flag==0){
            s2+=",";
            s2+=s[i];
            s2+=s[i+1];
        }
    }
}

int main(){
    int n,nel,ti;
    cout<<"Enter The Number Of Variable:\n";
    cin >>n;
    if(n < 2 || n > 4){
        cout << "Invalid number of variables ";
        return 0;
    }

    nel=pow(2,n);
    vector<int> arr(nel);

    ti=takeinput(nel,arr);
    if(ti==0){
        cout<<"Kmap Evaluation :"<<ti;
        return 0;
    }
    else if(ti==1){
        cout<<"Kmap Evaluation :"<<ti;
        return 0;
    }
    else if(ti==2){
        cout<<"Invalid Input ";
        return 0;
    }

    // cout<<"Array Elements : ";
    // for(int i=0;i<nel;i++){
    //     cout << arr[i] << " ";
    // }
    // cout << endl;

    switch(n){
        case 2:
            var2(nel,arr);
            break;
        case 3:
            var3(nel,arr);
            break;
        case 4:
            var4(nel,arr);
            break;
        default:
            cout<<"\nEntered Of Is Invalid\n";
    }
    return 0;
}
