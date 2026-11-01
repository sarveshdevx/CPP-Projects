#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void takeinput(int nel,vector<int>& arr){
    cout<<"Please enter Minterms:";
    for(int i=0;i<nel;i++){
        cin>>arr[i];
    }
}

void var1(){
    cout<<"Unavailable";
}
void var2(){
    cout<<"Unavailable";
}
void var3(){
    cout<<"Unavailble";
}
void var4(){
    cout<<"Unavailble";
} 

int main(){
    int n,nel;

    cout<<"Enter The Number Of Variable:\n";
    cin >>n;
    if(n < 1 || n > 4){
        cout << "Invalid number of variables";
        return 0;
    }

    nel=pow(2,n);
    vector<int> arr(nel);

    takeinput(nel,arr);
    cout<<"Array Elements : ";
    for(int i=0;i<nel;i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    switch(n){
        case 1:
            var1();
            break;
        case 2:
            var2();
            break;
        case 3:
            var3();
            break;
        case 4:
            var4();
            break;
        default:
            cout<<"\nEntered Of Is Invalid\n";
    }
    return 0;
}
