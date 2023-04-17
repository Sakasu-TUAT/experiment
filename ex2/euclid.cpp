#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define rep(i, a, b) for (int i = a; i < b; i++)



using namespace std;

int calcEuclid(int a, int b){  
    if(b==0){
        return a;
    }
    return calcEuclid(b, a%b);
}

int main(){
    int a = 12, b = 8;
    cout << calcEuclid(a, b) << endl;
    
}