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
    int times_past_zero = 0;
    while (getline(infile, line)) {
        lines.push_back(line);
        char direction = line[0];
        int distance = stoi(line.substr(1));
        int new_location = location;
        int revolutions = distance / 100;
        times_past_zero += revolutions;
        distance %= 100;
        if (direction == 'L') {
            new_location -= distance;
        } else if (direction == 'R') {
            new_location += distance;
        }
        if ((new_location < 0 && location > 0) || (location < 100 && new_location > 100)) {
            times_past_zero++;
        }
        new_location = (100 + new_location) % 100;
        if (new_location == 0) {
            times_at_zero++;
        }
        location = new_location;
    }
    cout << "Hit zero " << times_at_zero + times_past_zero << " times." << endl;
    infile.close();
    return 0;
}