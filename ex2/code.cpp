#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define rep(i, a, b) for (int i = a; i < b; i++)

long long int calcExtendedEuclid(long long int a, long long int b, long long int &x, long long int &y){  
    if(b==0){
        x = 1;
        y = 0;
        return a;
    }
    long long int d = calcExtendedEuclid(b, a%b, y, x);
    y -= a/b*x;
    return d;
}

long long int mod (int a, int m){
    return (a%m + m) % m;
}

long long int modinv(long long int a, long long int m){
    long long int x, y;
    calcExtendedEuclid(a, m, x, y);
    return mod(x, m);
}


long long int calcEuclid(long long int a, long long int b){  
    if(b==0){
        return a;
    }
    return calcEuclid(b, a%b);
}

long long int calcE(long long int p, long long int q){
    long long int e = 2;
    while(calcEuclid((p-1)*(q-1), e) !=1){
        e++;
    }
    return e;
}

/*
 * 繰り返し自乗法を使った法nのべき乗計算（aのk乗をnで割った余りを求める）
 * 
 * unsigned long int a : 底
 * unsigned int k : 指数
 * unsigned int n : 法
*/
unsigned int power(unsigned int a, unsigned int k, unsigned int n) {

    a %= n;

    if(a == 0 || n == 0){
        return 0;
    }
    if(k == 0){
        return 1 % n;
    }

    int i;
    unsigned int value = 1;
    for(i = 0; i < k; i++) {
        value *= a;
        if(value >= n) {
            value %= n;
        }
    }
    return value;
}


vector<int> hirabun, angou;

void encryptor(int e, int n){
    for(int m=0; m<n; m++){
        int c = power(m, e, n);
        angou.emplace_back(c);
    }
}

void decryptor(int d, int n){
    for(const auto &c: angou){
        int m = power(c, d, n);
        hirabun.emplace_back(m);
    }
}


int main(){
    int p = 41, q = 13;
    int n = p*q;
    int e = calcE(p,q);
    cout << "N: " << n << endl;
    cout << "E: " << e << endl;

    int d = modinv(e, (p-1)*(q-1));
    cout << "d: "<< d << endl;

    encryptor(e, n);
    decryptor(d, n);
    cout << "angou:\t";
    for(const auto &v : angou){
        cout << v;
    } cout << endl;

    cout << "hirabun:\t";
    for(const auto &v : hirabun){
        cout << v;
    } cout << endl;


    int original = 2;
    int a = power(original, e, n);
    int b = power(a, d, n);
    cout <<  original <<"->"<<a << "->"<<b<<endl;

}