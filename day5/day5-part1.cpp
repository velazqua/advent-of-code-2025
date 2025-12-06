#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main () {
    vector<pair<long long, long long>> ranges;
    string line;
    long long num_fresh = 0;
    while (cin >> line) {
        if (line.find('-') != string::npos) {
            size_t pos = line.find('-');
            long long start = stoll(line.substr(0, pos));
            long long end = stoll(line.substr(pos + 1));
            ranges.push_back({start, end});
        } else {
            break;      
        }
    }
    sort(ranges.begin(), ranges.end());
    int index = 0;
    while (index + 1 < ranges.size()) {
        //cout << "Current size: " << ranges.size() << " and current index: " << index << endl;
        // Check for overlaps within adjacent elements.
        long long start_a, start_b, end_a, end_b;
        start_a = ranges[index].first;
        end_a = ranges[index].second;
        start_b = ranges[index + 1].first;
        end_b = ranges[index + 1].second;
        // If there's no overlap, move to the next element.
        if (end_a + 1 < start_b) {
            num_fresh += (end_a - start_a + 1);
            //cout << "Adding range: " << start_a << "-" << end_a << " which is " << (end_a - start_a + 1) << endl;
            index++;
        } else {
            ranges[index].second = max(end_a, end_b);
            ranges.erase(ranges.begin() + index + 1);
            //cout << "Adding " << start_a << "-" << max(end_a, end_b) << " which is " << (max(end_a, end_b) - start_a + 1) << endl;
        }
    }
    // Add the last element.
    num_fresh += (ranges.back().second - ranges.back().first + 1);

    /*
    cout << "Num elements left: " << ranges.size() << endl;
    for(const auto& range : ranges) {
        cout << "Remaining range: " << range.first << "-" << range.second << endl;
    }
    */
    

    cout << "Answer: " << num_fresh << endl;
    return 0;
}