//
//  main.cpp
//  posn_day1_2026
//
//  Created by AdaBrain on 15/3/2569 BE.
//
#include <iostream>

using namespace std;

int lower_bound (vector<int>& arr, int target) {
    int left = 0;
    int right = (int) arr.size();
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
}

int upper_bound (vector<int>& arr, int target) {
    int left = 0;
    int right = (int) arr.size();
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] <= target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
}

//P07 [E] — Count Range Queries
//Given sorted array and Q queries each asking:
//"how many elements are in range [L, R]?"
//Answer each query in O(log n).
//
//Input:  arr = [1,2,3,4,5,6,7,8],  queries = [{3,6},{1,5},{4,8}]
//Output: [4, 5, 5]
int p07_solution(vector<int>& arr, int target) {
    return upper_bound(arr, target) - lower_bound(arr, target);
}


//P08 [M] — Minimum Difference Element
//Given a sorted array and target, find the element with
//minimum absolute difference to target.
//
//Input:  arr = [1, 3, 6, 10, 15],  target = 12
//Output: 10   (|10-12|=2 < |15-12|=3)
//
//Input:  arr = [1, 3, 6, 10, 15],  target = 7
//Output: 6

int p08_solution(vector<int>& arr, int target) {
    auto it = lower_bound(arr.begin(), arr.end(), target);
    
    if (it == arr.end())
        return arr.back();
    
    if (it == arr.begin())
        return arr.front();
    
    int left = *prev(it);
    int right = *it;
    
    return (abs(right - target) <= abs(left - target)) ? right : left;
}

//P09 [M] — Longest Increasing Subsequence (LIS) — O(n log n)
//Find the LENGTH of the longest strictly increasing subsequence.
//
//Input:  arr = [10, 9, 2, 5, 3, 7, 101, 18]
//Output: 4   (subsequence: 2, 3, 7, 101)
//
//Insight: maintain a "patience sorting" array `tails`.
//  tails[i] = smallest tail of all increasing subseqs of length i+1.
//  Use lower_bound to find where to place each new element.

int p09_solution(vector<int>& arr) {
    vector<int> tails;
    for (int ele : arr) {
        auto it = lower_bound(tails.begin(), tails.end(), ele);
        if (it == tails.end()) {
            tails.push_back(ele);
        } else {
            *it = ele;
        }
    }
    
    return (int)tails.size();
}


//P10 [M] — Minimize Maximum Distance Between Gas Stations
//Given positions of gas stations on a highway and K new stations
//to add, minimize the maximum distance between adjacent stations.
//Answer with precision 1e-6.
//
//Input:  stations = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],  K = 9
//Output: 0.5
//Input: stations = {23, 24, 36, 39, 46, 56, 57, 65, 84, 98}, K = 1
//Output: 14.00
//Input: stations = {10, 19, 25, 27, 32, 38, 38, 39, 41, 41, 45, 45, 50, 53, 54, 55, 64, 66, 68, 71, 74, 76, 76, 76, 88, 89, 89, 90, 98, 99}, K = 2
//Output: 9.00

bool check(double d, vector<int>& stations, int k) {
    int count = 0;
    for (int i = 1; i < (int)stations.size(); i++) {
        double gap = stations[i] - stations[i - 1];
        count += (int)ceil(gap / d) - 1;
        if (count > k) {
            return false;
        }
    }
    
    return true;
}

double p10_solution(vector<int>& stations, int k) {
    double left = 0;
    double right = stations.back() - stations.front();
    for (int i = 0; i < 100; i++) {
        double mid = left + (right - left) / 2.0;
        if (check(mid, stations, k)) {
            right = mid;
        } else {
            left = mid;
        }
    }
    
    return (left + right) / 2;
}



int main_2(int argc, const char * argv[]) {
    vector<int> arr = {1, 3, 6, 10, 15};
    int target = 12;
    
    cout << p08_solution(arr, target) << endl;
    
    return EXIT_SUCCESS;
}
