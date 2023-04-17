#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define rep(i, a, b) for (int i = a; i < b; i++)



using namespace std;



int calcExtendedEuclid(int a, int b, int &x, int &y){  
    if(b==0){
        x = 1;
        y = 0;
        return a;
    }
    int d = calcExtendedEuclid(b, a%b, y, x);
    y -= a/b*x;
    return d;
}

int mod (int a, int m){
    return (a%m + m) %m;
}

int modinv(int a, int m){
    int x, y;
    calcExtendedEuclid(a, m, x, y);
    return mod(x, m);
}

int main(){
    int a = 5, b = 13;
    int x, y;
    //5y=1(mod. 13) -> 5*8-13*3=1 
    // -> 5x+13y=1を満たすyがmodにおける乗法の逆元(ここではy=8)
    cout << modinv(a, b);

}