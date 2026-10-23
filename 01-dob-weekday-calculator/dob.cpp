#include <iostream>
#include <chrono>
#include <ctime>
using namespace std;

int  ty(int dd,int mm ,int yyyy){
    int d=0;
    switch(mm){
            case 12:
                d=d+30;
            case 11:
                d=d+31;
            case 10:
                d=d+30;
            case 9:
                d=d+31;
            case 8:
                d=d+31;
            case 7:
                d=d+30;
            case 6:
                d=d+31;
            case 5:
                d=d+30;
            case 4:
                d=d+31;
            case 3:
                d=d+28;
            case 2:
                d=d+31;
            case 1:
                d=d+0;
    }
    d=d+dd;
    if((yyyy%4==0&&yyyy%100!=0||yyyy%400==0)&& mm>2){
        d++;
    }
    return d;
}

int  dy(int dd,int mm,int yyyy){
    int d=0;
    switch(mm){
            case 12:
                d=d+30;
            case 11:
                d=d+31;
            case 10:
                d=d+30;
            case 9:
                d=d+31;
            case 8:
                d=d+31;
            case 7:
                d=d+30;
            case 6:
                d=d+31;
            case 5:
                d=d+30;
            case 4:
                d=d+31;
            case 3:
                d=d+28;
            case 2:
                d=d+31;
            case 1:
                d=d+0;
    }
    d=365-d-dd;
    if ((yyyy%4==0&&yyyy%100!=0||yyyy%400==0)&& mm<=2) {
    d++;
}
    return d;
}
int by(int d_year ,int t_year){
    int d=0;
    for(int i=d_year+1;i<t_year;i++){
        if((i%4==0 && i%100!=0 || i%400==0)){
            d=d+366;
        }
        else{
            d=d+365;
        }
    }
    return d;
}
void pday(int n){
    switch(n){
        case 0:
            cout<<"Sunday";
            break;
        case 1:
            cout<<"Monday";
            break;
        case 2:
            cout<<"Tuesday";
            break;
        case 3:
            cout<<"Wednesday";
            break;
        case 4:
            cout<<"Thursday";
            break;
        case 5:
            cout<<"Friday";
            break;
        case 6:
            cout<<"Saturday";
            break;
    }
}

int main(){

    int n,ddy,dty,dby,nof,fnof;
    int d_day,d_month,d_year;

    cout <<"Enter Your DOB (ddmmyyyy): \n";
    cin>>n;

    d_year= n%10000;
    
    d_month= n%1000000 ;
    d_month = d_month/10000;     

    d_day = n%100000000;
    d_day = d_day/1000000;

    auto now = chrono::system_clock::now();
    time_t t = chrono::system_clock::to_time_t(now);
    tm* local = localtime(&t);

    int t_year  = local->tm_year + 1900;
    int t_month = local->tm_mon + 1;
    int t_day   = local->tm_mday;

    if (d_year < 1900 || d_month < 1 || d_month > 12 ||d_day < 1 || d_day > 31 || d_year > t_year ||(d_year == t_year &&(d_month > t_month ||(d_month == t_month && d_day > t_day)))) {
        cout << "Invalid DOB";
        return 1;
    }


    dty=ty(t_day,t_month,t_year);
    ddy=dy(d_day,d_month,d_year);
    dby=by(d_year,t_year);

    if (d_year == t_year) {
        nof = dty - ty(d_day, d_month, d_year);
    } else {
        nof = dty + ddy + dby;
    }
    cout<<"No Of Days :"<<nof<<"\n";

    fnof=by(1899,d_year)+ty(d_day,d_month,d_year);
    pday(fnof%7);

    return 0;
}
