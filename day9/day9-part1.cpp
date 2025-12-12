#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

struct Point {
    int64_t x;
    int64_t y;
    Point(const string& s) {
        sscanf(s.c_str(), "%ld,%ld", &x, &y);
    }
};

int main () {
    vector<Point> points;
    string line;
    while (cin >> line) {
        points.push_back(Point(line));
    }

    int64_t max_area = 0;

    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            // Calculate the "rectangle area" for each pair of points.
            int64_t area = (abs(points[i].x - points[j].x) + 1) * (abs(points[i].y - points[j].y) + 1);
            max_area = max(max_area, area);
        }
    }
    cout << "Max area: " << max_area << endl;
}