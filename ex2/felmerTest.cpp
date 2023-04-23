#include <bits/stdc++.h>

using namespace std;

long long int mod (int a, int m){
    return (a%m + m) % m;
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
    std::uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

using std::ofstream;

ofstream ofs("felmerTest.csv");  // ファイルパスを指定する


int main(){
    int s = 1e4;
    int p = 76;
    bool isPrime = true;

    // for(int p = 2; p < 500; p++){

        p = 561;
        int cnt = 0;
        for(int i=0; i<s; i++){
            int a = random(1, p-1); //乱数生成
            int res = power(a, p-1, p); //a^(p-1)のmod.p
            // cerr << "a: " << a << " ";
            if(res == 1){
                cnt++;
            } 
        }
        cout << cnt << endl;
        cout << "Probability that p is a prime number: " << (double(cnt)/double(s))*100 << "%" << endl;
        ofs << p << ", " << (double(cnt)/double(s))*100 << endl;
    // }
    
}