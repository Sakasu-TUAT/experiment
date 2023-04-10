#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <limits>
#include <deque>
#include <cmath>
#include <iomanip>
#include <limits>
#include <deque>
#include <set>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;
using ll = long long;
#define rep(i, a, b) for (int i = a; i < b; i++)



using namespace std;

constexpr int dx[4] = {-1, 1, 0, 0};
constexpr int dy[4] = {0, 0, -1, 1};

std::ifstream ifs("./6002/map0");
vector<pair<int,int>> visited;
pair<int, int> goal = {99, 99};

int h, w;
vector<vector<int>> dist(h, vector<int>(w));

int timeComplexity = 0;
int memory = 0;

void next (queue<pair<int, int>> &q, const vector<string> &map){
    //時間計算量を記録
    timeComplexity++;

    auto pos = q.front();
    q.pop();
    for(int i=0; i<4; i++){
        int nextY = pos.first+dy[i], nextX = pos.second+dx[i];
        if((1 <= nextX and nextX <= w-2 and 1 <= nextY and nextY <= h-2)){
            if(dist[nextY][nextX]==-1 and map[nextY][nextX] == '0'){
                // cerr << "x,y = (" << nextX << "," << nextY << ") -> "<<map[nextX][nextY] << endl;
                dist[nextY][nextX] = dist[pos.first][pos.second] + 1; //距離の更新
                if(pair<int, int>(nextX, nextY)== goal){
                    cerr << "GOAL" << endl;
                    while(!q.empty()){
                        q.pop();
                    }
                    return;
                }  
                pair<int, int> nv = {nextY, nextX};
                q.push(nv);
                //メモリの取得
                int size = q.size();
                memory = max(memory, size);
            }
        }
    }
}

void resultVisualizer(){
  for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            if(dist[i][j]!=-1){
                if(i == h-2 and j == w-2){
                    printf("\x1b[31m");     /* 前景色をシアンに */
                } else {
                    printf("\x1b[32m");     /* 前景色をシアンに */
                }
                cerr << dist[i][j] << ",\t";
                printf("\x1b[39m");     /* 前景色をデフォルトに戻す */
            } else {
                cerr << dist[i][j]+2 << ",\t";
            }
        } 
        cerr << endl;
    }
}

int main (){
    string str;
    vector<string> map;

    while (getline(ifs, str)) {  
        map.emplace_back(str);  
        w = str.length();  
    }
    //正しくmapが取得できたかを表示
    for(auto v : map){
        // cerr << v << endl;
        h++;
    }
    cerr << "h, w =  " << h << ", " << w << endl;
    dist.resize(h, vector<int>(w));
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            dist[i][j] = -1;
        }
    }
    queue<pair<int, int>> q;
    q.push({1,1});
    dist[1][1] = 0;
    while(!q.empty()){
        next(q, map);
    }

    // resultVisualizer();
    cout << "memory: " << memory << "\t" << 
            "timeComplexity: " << timeComplexity << endl; 

  
    cout << "ans : " << dist[9][9] << endl;
}


