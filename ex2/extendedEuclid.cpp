#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define rep(i, a, b) for (int i = a; i < b; i++)



using namespace std;


//拡張ユークリッド関数
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

//aをmで割った正の余りを計算
int mod (int a, int m){
    return (a%m + m) %m;
}

//逆元を計算
int modinv(int a, int m){
    int x, y;
    calcExtendedEuclid(a, m, x, y);
    cout << "(a, b, x, y) = ("
    << a << ", " << m << ", " << x << ", " << y;
    if(y==17) cout << ")\t" ;
    else cout << ")\t\t" ;
    cout << "Inverse modulo: ";
    return mod(x, m);
}

int main(){

    //5y=1(mod. 13) -> 5*8-13*3=1 
    // -> 5y+13x=1を満たすyがmodにおける乗法の逆元(ここではy=8)
    // int a = 5, b = 13;
    // int x, y;

    vector<pair<int, int>> test = {{12, 8}, {5,4}, {50, 5}, {41, 29}};
    for(const auto [a, b] : test){
        cout << modinv(a, b) << endl;
    }
 

}