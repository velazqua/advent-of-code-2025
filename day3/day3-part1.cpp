#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main () {
    vector<string> lines;
    string line;
    int answer = 0;
    while (cin >> line) {
        lines.push_back(line);
        // Find the largest number from index 0 to n-1.
        char first_digit = line[0];
        int first_digit_index = 0;
        for(int i = 0; i < line.size()-1; i++) {
            if (line[i] > first_digit) {
                first_digit = line[i];
                first_digit_index = i;
            }
        }
        // Find the largest number after the last index.
        char second_digit = '0';
        for(int i = first_digit_index + 1; i < line.size(); i++) {
            if (line[i] > second_digit) {
                second_digit = line[i];
            }
        }
        answer += (first_digit - '0') * 10 + (second_digit - '0');
    }
    cout << "Answer: " << answer << endl;
    return 0;
}