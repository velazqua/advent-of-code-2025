#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int canAccess(const vector<string>& grid, int row, int col) {
    int count = 0;
    int numRows = grid.size();
    int numCols = grid[0].size();
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue; // Skip the current cell
            int newRow = row + dr;
            int newCol = col + dc;
            if (newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols) {
                if (grid[newRow][newCol] == '@') {
                    count++;
                }
            }
        }
    }
    return count < 4;
}

int main () {
    vector<string> lines;
    string line;
    int answer = 0;
    while (cin >> line) {
        lines.push_back(line);
    }
    while (true) {
        bool changed = false;
        int local_removed = 0;
        for(int i = 0; i < lines.size(); ++i) {
            for(int j = 0; j < lines[i].size(); ++j) {
                if(lines[i][j] == '@' && canAccess(lines, i, j)) {
                    lines[i][j] = '.'; // Remove access
                    changed = true;
                    local_removed++;
                
                }
            }
        }
        answer += local_removed;
        if (!changed) break; // No more changes, exit loop
    }
    cout << "Answer: " << answer << endl;
    return 0;
}