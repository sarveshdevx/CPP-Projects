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

void var2(){
    int kmap[2][2];
    for (int i =0;i<2;i++){
        for(int j=0;int j<0;j++){
            
        }
    }
}
void var3(){
    int kmap[2][4];
}
void var4(){
    int kmap[4][4];
} 

int main(){
    int n,nel;

    cout<<"Enter The Number Of Variable:\n";
    cin >>n;
    if(n < 2 || n > 4){
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
