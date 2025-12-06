#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

long long power(int base, int exp) {
    long long result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

long long bestTwelveDigits(const string& line, int start, int end, int digits_left) {
    if (digits_left == 0) {
        return 0;
    }
    // Find the largest digit within the range.
    char max_digit = '0';
    int max_index = start;
    for(int i = start; i <= end; i++) {
        if (line[i] > max_digit) {
            max_digit = line[i];
            max_index = i;
        }
    }
    return (max_digit - '0') * power(10, digits_left - 1) + bestTwelveDigits(line, max_index + 1, end + 1, digits_left - 1);
}


int main () {
    vector<string> lines;
    string line;
    long long answer = 0;
    while (cin >> line) {
        lines.push_back(line);
        long long line_answer = bestTwelveDigits(line, 0, line.size()-12, 12);
        cout << "Line: " << line << " -> " << line_answer << endl;
        answer += line_answer;
    }
    cout << "Answer: " << answer << endl;
    return 0;
}