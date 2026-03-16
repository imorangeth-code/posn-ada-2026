//
//  main.cpp
//  posn_day1_2026
//
//  Created by AdaBrain on 15/3/2569 BE.
//

//P01 [E] — First and Last Occurrence
//Given an array of integers (possibly unsorted) and a target,
//return the index of the FIRST and LAST occurrence.
//Return {-1, -1} if not found.
//
//Input:  arr = [4, 2, 7, 2, 9, 2, 1],  target = 2
//Output: {1, 5}
//
//Input:  arr = [1, 3, 5],  target = 4
//Output: {-1, -1}

#include <iostream>
using namespace std;

typedef pair<int, int> pii;

pii p01_solution(vector<int>& input, int target) {
    int first = -1;
    int last = -1;
    
    for (int i = 0; i < (int)input.size(); i++) {
        if (input[i] == target) {
            if (first == -1) {
                first = i;
            }
            
            last = i;
        }
    }
    
    return {first, last};
}

int p02_solution(vector<int>& arr, int n) {
    vector<bool> seen_map(n + 1, false);
    // Foreach
    for(int x : arr) {
        seen_map[x] = true;
    }
    
    for(int i = 1; i <= n; i++) {
        if(!seen_map[i])
            return i;
    }
    
    return -1;
}

//P03 [M] — Majority Element (Boyer-Moore Voting)
//Find the element that appears MORE than n/2 times.
//Guaranteed to exist. Must run in O(n) time, O(1) space.
//
//Input:  arr = [2, 2, 1, 1, 1, 2, 2]
//Output: 2

int p03_solution(vector<int>& arr) {
    int candidate = arr[0];
    int count = 1;
    
    // Phase 1: Find candidate
    // Time: O(n)
    for (int i = 1; i < (int)arr.size(); i++) {
        if (arr[i] == candidate) {
            count++;
        } else {
            count--;
            if (count == 0) {
                candidate = arr[i];
                count = 1;
            }
        }
    }
    
    // Phase 2: Verify
    // Time: O(n)
    int freq = 0;
    for(int i : arr) {
        if (i == candidate) {
            freq++;
        }
    }

    return (freq > (int)arr.size()/2) ? candidate : -1;
}


int main_0(int argc, const char * argv[]) {
    vector<int> arr = {4, 2, 7, 2, 9, 2, 1};
    int target = 2;
    
    auto [f, l] = p01_solution(arr, target);
    cout << "{" << f << ", " << l << "}" << endl;
    
    vector<int> arr_2 = {3, 1, 4};
    int n = 4;
    
    cout << p02_solution(arr_2, n) << endl;
    
    vector<int> arr_3 = {2, 2, 1, 1, 1, 2, 2};
    cout << p03_solution(arr_3) << endl;
    
    return EXIT_SUCCESS;
}
