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
    int num_lines = lines.size();
    vector<vector<long long>> num_ways(num_lines, vector<long long>(lines[0].size(), 0));
    for (int i = 1; i < num_lines; ++i) {
        for(int j = 0; j < lines[i].size(); ++j) {
            if (lines[i-1][j] == 'S') {
                lines[i][j] = '|';
                num_ways[i][j] = 1;
            } else if (lines[i-1][j] == '|') {
                if (lines[i][j] == '.') {
                    lines[i][j] = '|';
                    num_ways[i][j] += num_ways[i-1][j];
                } else if (lines[i][j] == '|') {
                    lines[i][j] = '|';
                    num_ways[i][j] += num_ways[i-1][j];
                } else {
                    if (j - 1 >= 0 && lines[i][j-1] != '^') {
                        lines[i][j-1] = '|';
                        num_ways[i][j-1] += num_ways[i-1][j];
                    }
                    if (j + 1 < lines[i].size() && lines[i][j+1] != '^') {
                        lines[i][j+1] = '|';
                        num_ways[i][j+1] += num_ways[i-1][j];
                    }
                }
            }
        }
    }
    // Print the lines.
    for(const auto& l : lines) {
        cout << l << endl;
    }
    // Print the number of ways.
    long long total_ways = 0;
    for (int j = 0; j < lines[num_lines - 1].size(); ++j) {
        total_ways += num_ways[num_lines - 1][j];
    }
    cout << "Total ways: " << total_ways << endl;
}