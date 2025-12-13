// NOTE: Solution is too slow. Abandoning it for a linear programming approach.
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <deque>

using namespace std;
struct Point {
    int64_t x;
    int64_t y;
    Point(int64_t x_, int64_t y_) : x(x_), y(y_) {}
    Point(const string& s) {
        sscanf(s.c_str(), "%ld,%ld", &x, &y);
    }
};

int main () {
    string line;
    int total_button_presses = 0;
    while (getline(cin, line)) {
        istringstream iss(line);
        string token;
        string lights; iss >> lights;
        lights = lights.substr(1, lights.size() - 2); // Remove []
        vector<vector<int>> buttons;
        vector<int> joltage_levels;
        while (iss >> token) {
            if (token[0] == '(') {
                vector<int> button;
                token = token.substr(1, token.size() - 2); // Remove parentheses
                istringstream token_ss(token);
                string coord;
                while (getline(token_ss, coord, ',')) {
                    button.push_back(stoi(coord));
                }
                buttons.push_back(button);
            } else {
                token = token.substr(1, token.size() - 2); // Remove {}
                istringstream token_ss(token);
                string level;
                while (getline(token_ss, level, ',')) {
                    joltage_levels.push_back(stoi(level));
                }
            }
        }
        // Set up a queue that continuously presses buttons
        set<vector<int>> visited_joltages;
        deque<vector<int>> joltage_queue;
        joltage_queue.push_back(vector<int>(lights.size(), 0));
        int button_pushes = 0;
        bool done = false;
        while (!joltage_queue.empty()) {
            if (done) break;
            int queue_size = joltage_queue.size();
            for (int i = 0; i < queue_size; ++i) {
                vector<int> current_joltage = joltage_queue.front();
                joltage_queue.pop_front();
                if (visited_joltages.count(current_joltage)) {
                    continue;
                }
                visited_joltages.insert(current_joltage);
                if (joltage_levels == current_joltage) {
                    done = true;
                    cout << "Reached joltage configuration after " << button_pushes << " button presses." << endl;
                    cout << "Queue size at completion: " << joltage_queue.size() << endl;
                    total_button_presses += button_pushes;
                    break;
                }
                for (const auto& button : buttons) {
                    vector<int> new_lights = current_joltage;
                    for (int idx : button) {
                        if (idx >= 0 && idx < new_lights.size()) {
                            new_lights[idx]++;
                        }
                    }
                    if (!visited_joltages.count(new_lights)) {
                        joltage_queue.push_back(new_lights);
                    }
                }
            }
            button_pushes++;
        }
    }
    cout << "Total button presses: " << total_button_presses << endl;
}