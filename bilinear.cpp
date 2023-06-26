
#include <iostream>
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
#include <algorithm>
using namespace std;
using ll = long long;

struct Point{
    int x, y;
    const Point operator+ (Point other){
        return Point{x+other.x, y+other.y};
    };
    const Point operator- (Point other){
        return Point{x-other.x, y-other.y};
    };
};

double bilinear(const std::vector<pair<Point, double>>& v, Point p){
    Point r = p - v[0].first;
    double rx = r.x/3.0;
    double ry = r.y/3.0;
    cout << "r(x, y) = " << rx << ", " << ry << endl;
    double ans = 
        (1-rx)*(1-ry)*v[0].second
        +(1-rx)*ry*v[1].second
        +rx*(1-ry)*v[2].second
        +rx*ry*v[3].second;
        cerr << (1-rx)*(1-ry)*v[0].second << ", "
            << (1-rx)*ry*v[1].second << ", "
            << rx*(1-ry)*v[2].second << ", "
            << rx*ry*v[3].second << endl;
    return ans;
}

int main(){
    vector<pair<Point, double>> p = {
        {{60, 45}, 50}, 
        {{60, 48}, 65}, 
        {{63, 45}, 95}, 
        {{63, 48}, 20}
    };

    cout << bilinear(p, {61,48}) << endl;
    cout << bilinear(p, {61,47}) << endl;
    cout << bilinear(p, {62,47}) << endl;
    cout << bilinear(p, {62,46}) << endl;
    
}