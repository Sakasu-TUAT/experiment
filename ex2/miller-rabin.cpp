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

ofstream ofs("miller-rabin.csv");  // ファイルパスを指定する


int p; 
int s = 1e5;
vector<int> carmichaelNumbers = {
    561, 1105, 1729, 2465, 2821, 6601, 8911,
    // 7, 13, 21, 51, 23, 57
}; 

void calcMillerRabin(){
    for(const auto &p : carmichaelNumbers){
        int u = 0, v = p - 1;
        while (v % 2 == 0) {
            ++u;
            v >>= 1;
        }
        // cout << p-1  << ", " << u << ", " << v << endl;

        int notPrime = 0;
        int prime = 0;
   
        for(int i=0; i<s; i++){
            int a = random(1, p-1); //乱数生成
            int res = power(a, p-1, p); //a^(p-1)のmod.p
            bool isPrime = true;
            if(res != 1){
                notPrime++;
            } else if(res == 1){
                for(int j=1; j<=u; j++){
                    int res1 = power(a, pow(2, j)*v, p);
                    int res2 = power(a, pow(2, j-1)*v, p);
                    if(res1 == 1 and res2 != 1 and res2 != p-1){ //p-1 == -1(mod.p)
                        notPrime++;
                        isPrime = false;
                        break;
                    }
                }
                if(isPrime) {
                    prime++;
                    isPrime = true;
                }
            }   
        }
        // cout << notPrime << " + " << prime << " == " << s << endl;

        cout << "Prime probability : "<< p <<" # " << (double(prime)/double(s))*100 << "%" << endl;
        ofs << p << ", " << (double(prime)/double(s))*100 << endl;
    }
}

int main(){

    ofs << "iteration, " << s << endl; 
    calcMillerRabin();

}