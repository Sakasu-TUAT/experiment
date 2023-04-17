#include <bits/stdc++.h>
#include <fstream>

using std::ofstream;
using namespace std;

ofstream ofs("prime.csv");  // ファイルパスを指定する

int main(){
    for(int i=2; i<1e5; i++){
        int cnt = 0;
        bool isPrime = true;
        for(int k=2; k<=sqrt(i); k++){
            cnt++;
            if(i%k==0) {
                cout << i << " is not irime numer" << endl;
                isPrime = false;
                break;
            }
        }
        if(isPrime) ofs << i << ", " << cnt << endl;
    }
  
}