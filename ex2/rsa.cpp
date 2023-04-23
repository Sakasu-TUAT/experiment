#include <bits/stdc++.h>
#include <fstream>

using std::ofstream;
using namespace std;

ofstream ofs("random.csv");  // ファイルパスを指定する

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

std::random_device rd;
std::mt19937 gen(rd());

int random(int low, int high) {
    std::uniform_int_distribution<> rand(low, high);
    return rand(gen);
}

/**
 * @brief ミラーラビン法による素数判定
 * @param p 素数の候補
 * @param s 反復回数
 * @return true 
 * @return false 
 */
bool calcMillerRabin(int p, int s){

    //例外処理
    if (p == 2) {
        return true;
    }
    if (p < 2 || p % 2 == 0) {
        return false;
    }

    int u = 0, v = p - 1;
    while (v % 2 == 0) {
        ++u;
        v >>= 1; // v/=2;
    }

    for(int i=0; i<s; i++){
        int a = random(1, p-1); //乱数生成
        int res = power(a, p-1, p); //a^(p-1)のmod.p
        if(res != 1){
            return false;
        } else if(res == 1){
            for(int j=1; j<=u; j++){
                int res1 = power(a, pow(2, j)*v, p);
                int res2 = power(a, pow(2, j-1)*v, p);
                if(res1 == 1 and res2 != 1 and res2 != p-1){ //p-1 == -1(mod.p)
                    return false;
                }
            }
        }   
    }
    return true;
}

// nビットの素数を生成する
int generatePrime(int n, int k) {
    if(n==1) return -1;
    //n-1ビットの整数pを{0, 1}^(n-1)からランダムに選び、素数の候補をpの先頭に1を付加したnビットの整数
    int p = (1 << (n - 1)) + random(0, 1 << (n - 2)) + 1; //最後に+1で奇数にする
    while (!calcMillerRabin(p, k)) {
        p = (1 << (n - 1)) + random(0, 1 << (n - 2)) + 1;
    }
    return p;
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

void calcRSASystem(int bit, int s, int p, int q){
    cout << "p: " << p << ", q: " << q << endl;
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
        cout << v << ", ";
    } cout << endl;

    cout << "hirabun:\t";
    for(const auto &v : hirabun){
        cout << v << ", ";
    } cout << endl;

}

int main(){
    int bit=4;
    int s=1e2;
    int p = generatePrime(bit, s);
    int q;
    while((q = generatePrime(bit, s) )== p){};
   calcRSASystem(bit, s, p, q);
}