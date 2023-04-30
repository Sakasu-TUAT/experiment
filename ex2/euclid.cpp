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

    vector<pair<int, int>> test = {{12, 8}, {5,4}, {50, 5}, {41, 29}};
    for(const auto [a, b] : test){
        cout << "gcd(" << a << ", " << b << ") = " << calcEuclid(a, b) << endl;
    }
    
}