#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main () {
    vector<string> lines;
    string line;
    while (cin >> line) {
        lines.push_back(line);
    }
    int splits = 0;
    int num_lines = lines.size();
    for (int i = 1; i < num_lines; ++i) {
        for(int j = 0; j < lines[i].size(); ++j) {
            if (lines[i-1][j] == 'S' || lines[i-1][j] == '|') {
                if (lines[i][j] == '.' || lines[i][j] == '|') {
                    lines[i][j] = '|';
                } else {
                    splits++;
                    if (j - 1 >= 0 && lines[i][j-1] != '^') {
                        lines[i][j-1] = '|';
                    }
                    if (j + 1 < lines[i].size() && lines[i][j+1] != '^') {
                        lines[i][j+1] = '|';
                    }
                }
            }
        }
    }
    // Print the lines.
    for(const auto& l : lines) {
        cout << l << endl;
    }
    cout << splits << endl;
}