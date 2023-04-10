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

constexpr int dx[4] = {-1, 1, 0, 0};
constexpr int dy[4] = {0, 0, -1, 1};

std::ifstream ifs("./6002/map0");

int h, w;
vector<vector<int>> dist(h, vector<int>(w));
vector<vector<bool>> visited;  // 既に通った場所なのかを記録しておく配列

int timeComplexity = 0;
int memory = 0;


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

void dfs(std::pair<int,int> pos, const vector<string> &map) {
    timeComplexity++;

    visited[pos.first][pos.second] = true;

    for (int i = 0; i < 4; i++) {
        int nextY = pos.first  + dy[i];    
        int nextX = pos.second + dx[i];    
        if (nextY <= 0 || h-1 <= nextY || nextX <= 0 || w-1 <= nextX) continue; // 迷路の外に出るならスルー
        if (map[nextY][nextX] == '1') {
            continue;       // 障害物があればスルー
        }
        if (visited[nextY][nextX]) {
            continue;             //探索済みならスルー
        }
        // cerr << "x,y = (" << nextX << "," << nextY << ") -> "<<map[nextX][nextY] << endl; 
        dist[nextY][nextX] = dist[pos.first][pos.second] + 1;
        memory = max(memory, dist[nextY][nextX]);

        
        dfs(pair<int, int>({nextY, nextX}), map);
    }

    return ;
}

int main () {
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
    visited.assign(h, vector<bool>(w, false));
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            dist[i][j] = -1;
        }
    }
    pair<int, int> start = {1,1};
    dist[1][1] = 0;
    dfs(start, map);

    // resultVisualizer();

    cout << "memory: " << memory << "\t" << 
        "timeComplexity: " << timeComplexity << endl; 

    cout << "ans : " << dist[9][9] << endl;
}


