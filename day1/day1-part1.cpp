#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main () {
    // Read day1.in file contents and store them in a vector.
    ifstream infile("day1.in");
    vector<string> lines;
    string line;
    int location = 50;
    int times_at_zero = 0;
    while (getline(infile, line)) {
        lines.push_back(line);
        char direction = line[0];
        int distance = stoi(line.substr(1));
        if (direction == 'L') {
            location -= distance;
        } else if (direction == 'R') {
            location += distance;
        }
        location = (100 + location) % 100;
        if (location == 0) {
            times_at_zero++;
        }
    }
    cout << "Hit zero " << times_at_zero << " times." << endl;
    infile.close();
    return 0;
}