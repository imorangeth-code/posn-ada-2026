//
//  main.cpp
//  posn_day1_2026
//
//  Created by AdaBrain on 15/3/2569 BE.
//

#include <iostream>
using namespace std;

// Binary Search
int binary_search(vector<int>& arr, int target) {
    int left = 0;
    int right = (int) arr.size() - 1;
    
    while(left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

//P04 [E] — Search in Rotated Sorted Array
//A sorted array was rotated at an unknown pivot. Find target.
//Return index or -1. Must be O(log n).
//
//Input:  arr = [4, 5, 6, 7, 0, 1, 2],  target = 0
//Output: 4
//
//Input:  arr = [4, 5, 6, 7, 0, 1, 2],  target = 3
//Output: -1
//
//Insight: at least one half is always sorted — check which half
//and whether target lies in it.

int p04_solution(vector<int>& arr, int target) {
    int left = 0;
    int right = (int) arr.size() - 1;
    
    while(left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        }
        
        if (arr[left] <= arr[mid]) {
            // Left haf is sorted
            if (arr[left] <= target && target < arr[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {
            // Right half is sorted
            if (arr[mid] < target && target <= arr[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    
    return -1;
}

//P05 [M] — Find Peak Element
//A peak element is one that is STRICTLY greater than its neighbors.
//arr[-1] = arr[n] = -infinity. Return ANY peak index. O(log n).
//
//Input:  arr = [1, 2, 3, 1]
//Output: 2   (arr[2]=3 is peak)
//
//Input:  arr = [1, 2, 1, 3, 5, 6, 4]
//Output: 5   (arr[5]=6 is peak)
//
//Insight: if arr[mid] < arr[mid+1], the right half contains a peak.

int p05_solution(vector<int>& arr) {
    int left = 0;
    int right = (int) arr.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] < arr[mid + 1]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
}

//P06 [M] — Median of Two Sorted Arrays
//Find median of two sorted arrays combined. O(log(min(m,n))).
//
//Input:  A = [1, 3],  B = [2]
//Output: 2.0
//
//Input:  A = [1, 2],  B = [3, 4]
//Output: 2.5
//
//Insight: binary search on partition of the smaller array.
//Ensure left half of partition ≤ right half.

double p06_solution(vector<int>& A, vector<int>& B) {
    if (A.size() > B.size()) {
        swap(A, B);
    }
    
    int m = (int) A.size();
    int n = (int) B.size();
    
    int left = 0;
    int right = m;
    
    while(left <= right) {
        int pA = left + (right - left) / 2;
        int pB = (m + n + 1) / 2 - pA;
        
        int maxL_A = (pA == 0) ? INT_MIN : A[pA - 1];
        int minR_A = (pA == m) ? INT_MAX : A[pA];
        int maxL_B = (pB == 0) ? INT_MIN : B[pB - 1];
        int minR_B = (pB == n) ? INT_MAX : B[pB];
        
        if (maxL_A <= minR_B && maxL_B <= minR_A) {
            if ((m + n) % 2 == 1) {
                return max(maxL_A, maxL_B);
            }
            return (max(maxL_A, maxL_B) + min(minR_A, minR_B)) / 2;
        } else if (maxL_A > maxL_B) {
            right = pA - 1;
        } else {
            left = pA + 1;
        }
    }
    
    return 0.0;
}


int main_1 (int argc, const char * argv[]) {
    vector<int> arr = {4, 5, 6, 7, 0, 1, 2};
    int target = 4;
    cout << p04_solution(arr, target) << endl;
    
    // P05
    vector<int> arr_1 = {1, 2, 3, 1};
    cout << p05_solution(arr_1) << endl;
    
    
    return EXIT_SUCCESS;
}
