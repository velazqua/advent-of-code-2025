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
    int64_t z;
    Point(const string& s) {
        sscanf(s.c_str(), "%ld,%ld,%ld", &x, &y, &z);
    }
};

bool operator < (const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    if (a.y != b.y) return a.y < b.y;
    return a.z < b.z;
}

int64_t distance(const Point& a, const Point& b) {
    return (a.x - b.x) * (a.x - b.x) +
                (a.y - b.y) * (a.y - b.y) +
                (a.z - b.z) * (a.z - b.z);
}

int main () {
    vector<Point> points;
    string line;
    while (cin >> line) {
        points.push_back(Point(line));
    }

    set<tuple<int64_t, Point, Point>> sorted_points;
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            int64_t dist = distance(points[i], points[j]);
            sorted_points.insert(make_tuple(dist, points[i], points[j]));
        }
    }

    auto it = sorted_points.begin();
    map<Point, int> point_map;
    map<int, set<Point>> circuit_map;
    int circuit_count = 0;
    while (it != sorted_points.end()) {
        int64_t dist = get<0>(*it);
        Point p1 = get<1>(*it);
        Point p2 = get<2>(*it);
        printf("Distance: %ld between points (%ld,%ld,%ld) and (%ld,%ld,%ld)\n",
               dist, p1.x, p1.y, p1.z, p2.x, p2.y, p2.z);
        // There are many cases.
        // Case 1: Both points are new and are not in any circuit.
        bool p1_in_map = point_map.find(p1) != point_map.end();
        bool p2_in_map = point_map.find(p2) != point_map.end();
        if (!p1_in_map && !p2_in_map) {
            int circuit_id = ++circuit_count;
            point_map[p1] = circuit_id;
            point_map[p2] = circuit_id;
            cout << "Creating new circuit " << circuit_id << " with points." << endl;
            circuit_map[circuit_id] = {p1, p2};
        } else if (p1_in_map && !p2_in_map) {
            // Case 2: p1 is in a circuit, p2 is new.
            int circuit_id = point_map[p1];
            point_map[p2] = circuit_id;
            circuit_map[circuit_id].insert(p2);
            cout << "Adding point to existing circuit " << circuit_id << "." << endl;
        } else if (!p1_in_map && p2_in_map) {
            // Case 3: p2 is in a circuit, p1 is new.
            int circuit_id = point_map[p2];
            point_map[p1] = circuit_id;
            circuit_map[circuit_id].insert(p1);
            cout << "Adding point to existing circuit " << circuit_id << "." << endl;
        } else {
            // Case 4: Both points are in circuits. We need to merge circuits if they are different.
            int circuit_id1 = point_map[p1];
            int circuit_id2 = point_map[p2];
            if (circuit_id1 != circuit_id2) {
                // Merge circuit_id2 into circuit_id1
                for (const auto& pt : circuit_map[circuit_id2]) {
                    point_map[pt] = circuit_id1;
                    circuit_map[circuit_id1].insert(pt);
                }
                circuit_map.erase(circuit_id2);
                cout << "Merging circuits " << circuit_id1 << " and " << circuit_id2 << "." << endl;
            } else {
                cout << "Both points already in the same circuit " << circuit_id1 << "." << endl;
            }
        }
        cout << "Current number of circuits: " << circuit_map.size() << endl;
        if (circuit_map.size() == 1) {
            cout << circuit_map.begin()->second.size() << " vs. " << points.size() << endl;
        }
        if (circuit_map.size() == 1 && circuit_map.begin()->second.size() == points.size()) {
            cout << "The last connecting guys were: " << p1.x << " and " << p2.x << endl;
            cout << " and their product is " << (p1.x * p2.x) << endl;
            break;
        }
        it++;
    }
    cout << "Reached the end of the distance list." << endl;
}