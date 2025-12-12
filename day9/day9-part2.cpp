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
    Point(int64_t x_, int64_t y_) : x(x_), y(y_) {}
    Point(const string& s) {
        sscanf(s.c_str(), "%ld,%ld", &x, &y);
    }
};

bool inGreenOutline(const pair<int64_t, int64_t>& p, const map<int64_t, set<int64_t>>& green_x_map, const map<int64_t, set<int64_t>>& green_y_map) {
    // Go up, down, left and right from pt until we hit a green outline point.
    // If we hit a green outline point in all four directions, return true.
    Point pt(p.first, p.second);
    bool up = false, down = false, left = false, right = false;
    set<int64_t> x_set;
    try {
        x_set = green_x_map.at(pt.x);
    } catch (const out_of_range& e) {
        return false;
    }
    set<int64_t> y_set;
    try {
        y_set = green_y_map.at(pt.y);
    } catch (const out_of_range& e) {
        return false;
    }
    auto x_it = x_set.lower_bound(pt.y);
    auto y_it = y_set.lower_bound(pt.x);
    if (x_it != x_set.end()) {
        up = true;
    }
    if (x_it != x_set.begin()) {
        down = true;
    }
    if (*x_it == pt.y) {
        up = true;
        down = true;
    }
    if (y_it != y_set.end()) {
        right = true;
    }
    if (y_it != y_set.begin()) {
        left = true;
    }
    if (*y_it == pt.x) {
        right = true;
        left = true;
    }
    return up && down && left && right;
}

bool get_outline_points(const Point& p1, const Point& p2, map<int64_t, set<int64_t>>& green_x_map, map<int64_t, set<int64_t>>& green_y_map) {
    vector<Point> points = {p1, Point(p1.x, p2.y), p2, Point(p2.x, p1.y)};
    vector<pair<int64_t, int64_t>> outline = {{p1.x, p2.y}, {p2.x, p1.y}, {p1.x, p1.y}, {p2.x, p2.y}};
    if (inGreenOutline({p1.x, p2.y}, green_x_map, green_y_map) == false || inGreenOutline({p2.x, p1.y}, green_x_map, green_y_map) == false) {
        return false;
    }
    for(int i = 0; i < points.size(); ++i) {
        int j = (i + 1) % points.size();
            if (points[i].x == points[j].x) {
                // Vertical line
                int64_t x = points[i].x;
                int64_t y1 = min(points[i].y, points[j].y);
                int64_t y2 = max(points[i].y, points[j].y);
                for (int64_t y = y1+1; y < y2; ++y) {
                    if (inGreenOutline({x, y}, green_x_map, green_y_map) == false) {
                        return false;
                    }
                }
            } else if (points[i].y == points[j].y) {
                // Horizontal line
                int64_t y = points[i].y;
                int64_t x1 = min(points[i].x, points[j].x);
                int64_t x2 = max(points[i].x, points[j].x);
                for (int64_t x = x1+1; x < x2; ++x) {
                    if (inGreenOutline({x, y}, green_x_map, green_y_map) == false) {
                        return false;
                    }
                }
            }
    }
    return true;
}

int main () {
    vector<Point> points;
    string line;
    vector<string> grid;
    while (cin >> line) {
        Point p(line);
        points.push_back(p);
    }

    // Mark the grid with green outline.
    points.push_back(points[0]);
    set<pair<int64_t, int64_t>> green_outline;
    map<int64_t, set<int64_t>> green_x_map;
    map<int64_t, set<int64_t>> green_y_map;
    for(int i = 0; i < points.size(); ++i) {
        int j = (i + 1) % points.size();
            if (points[i].x == points[j].x) {
                // Vertical line
                int64_t x = points[i].x;
                int64_t y1 = min(points[i].y, points[j].y);
                int64_t y2 = max(points[i].y, points[j].y);
                for (int64_t y = y1; y <= y2; ++y) {
                    green_x_map[x].insert(y);
                    green_y_map[y].insert(x);
                }
            } else if (points[i].y == points[j].y) {
                // Horizontal line
                int64_t y = points[i].y;
                int64_t x1 = min(points[i].x, points[j].x);
                int64_t x2 = max(points[i].x, points[j].x);
                for (int64_t x = x1; x <= x2; ++x) {
                    green_x_map[x].insert(y);
                    green_y_map[y].insert(x);
                }
            }
    }

    int64_t max_area = 0;
    cout << "There are " << points.size() << " points read." << endl;
    cout << "There are " << points.size() * points.size() << " pairs of points to check." << endl;
    vector<tuple<int64_t, Point, Point>> sorted_rectangles;
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            int64_t area = (abs(points[i].x - points[j].x) + 1) * (abs(points[i].y - points[j].y) + 1);
            sorted_rectangles.push_back({area, points[i], points[j]});
        }
    }
    sort(sorted_rectangles.begin(), sorted_rectangles.end(), [](const auto& a, const auto& b) {
        return get<0>(a) > get<0>(b);
    });
    for(int idx = 0; idx < sorted_rectangles.size(); ++idx) {
        auto [area, p1, p2] = sorted_rectangles[idx];
        if (area <= max_area) {
            continue;
        }
        cout << "Checking points: (" << p1.x << "," << p1.y << ") and (" << p2.x << "," << p2.y << ") with area: " << area << endl;
        // Check that the diagonal points are inside the red/green area.
        // Create outline points for the rectangle formed by points[i] and points[j].
        if (get_outline_points(p1, p2, green_x_map, green_y_map)) {
            cout << "The area for this rectangle is: " << area << endl;
            max_area = max(max_area, area);
            break;
        }       
    }
    cout << "Max area: " << max_area << endl;
}