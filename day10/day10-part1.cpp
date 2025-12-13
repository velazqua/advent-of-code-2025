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
                // Ignore {} tokens for now.
            }
        }
        // Set up a queue that continuously presses buttons
        set<string> visited_lights;
        deque<string> light_queue;
        light_queue.push_back(string(lights.size(), '.'));
        int button_pushes = 0;
        bool done = false;
        while (!light_queue.empty()) {
            if (done) break;
            int queue_size = light_queue.size();
            for (int i = 0; i < queue_size; ++i) {
                string current_lights = light_queue.front();
                light_queue.pop_front();
                if (visited_lights.count(current_lights)) {
                    continue;
                }
                visited_lights.insert(current_lights);
                if (current_lights == lights) {
                    done = true;
                    cout << "Reached target lights configuration after " << button_pushes << " button presses." << endl;
                    total_button_presses += button_pushes;
                    break;
                }
                for (const auto& button : buttons) {
                    string new_lights = current_lights;
                    for (int idx : button) {
                        if (idx >= 0 && idx < new_lights.size()) {
                            new_lights[idx] = (new_lights[idx] == '.') ? '#' : '.';
                        }
                    }
                    if (!visited_lights.count(new_lights)) {
                        light_queue.push_back(new_lights);
                    }
                }
            }
            button_pushes++;
        }
        
    }
    cout << "Total button presses: " << total_button_presses << endl;
}