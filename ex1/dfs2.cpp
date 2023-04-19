#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define rep(i, a, b) for (int i = a; i < b; i++)



using namespace std;

constexpr int dx[4] = {-1, 1, 0, 0};
constexpr int dy[4] = {0, 0, -1, 1};

string fileName = "";
std::ifstream ifs;
vector<pair<int,int>> visited;
pair<int, int> goal = {9, 9};

int h, w;
vector<string> maze;
vector<vector<int>> dist(h, vector<int>(w));

int timeComplexity = 0;
int memory = 0;

void next (stack<pair<int, int>> &s){
    //時間計算量を記録
    timeComplexity++;

    auto pos = s.top();
    s.pop();
    for(int i=0; i<4; i++){
        int nextY = pos.first+dy[i], nextX = pos.second+dx[i];
        if((1 <= nextX and nextX <= w-2 and 1 <= nextY and nextY <= h-2)){
            if(dist[nextY][nextX]==-1 and maze[nextY][nextX] == '0'){
                // cerr << "x,y = (" << nextX << "," << nextY << ") -> "<<maze[nextX][nextY] << endl;
                dist[nextY][nextX] = dist[pos.first][pos.second] + 1; //距離の更新
                if(pair<int, int>(nextX, nextY)== goal){
                    cerr << "GOAL" << endl;
                    while(!s.empty()){
                        s.pop();
                    }
                    return;
                }  
                pair<int, int> nv = {nextY, nextX};
                s.push(nv);
                //メモリの取得
                int size = s.size();
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


//迷路ファイルの読み込みと表示
void mazeIO(){
    string str;
    string fileNum;

    fileName = "./map1010";
    // fileName = "./6002/map" + string(argv[1]);
    ifs = std::ifstream(fileName);

    while (getline(ifs, str)) {  
        maze.emplace_back(str);  
    }
    w = str.length();  
    //正しくmazeが取得できたかを表示
    for(auto v : maze){
        cerr << v << endl;
        h++;
    }
    cerr << "h, w =  " << h << ", " << w << endl;
}

int main (int argc, char* argv[]){

    //迷路ファイルの読み込みと表示
    mazeIO();

    dist.resize(h, vector<int>(w));
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            dist[i][j] = -1;
        }
    }
    stack<pair<int, int>> s;
    s.push({1,1});
    dist[1][1] = 0;
    while(!s.empty()){
        next(s);
    }

    resultVisualizer();
    
    cout << "memory: " << memory << "\t" << 
            "timeComplexity: " << timeComplexity << endl; 
            
    cout << "ans : " << dist[9][9] << endl;
}


