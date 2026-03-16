//
//  main.cpp
//  posn_day2_2026
//
//  Created by AdaBrain on 16/3/2569 BE.
//

#include <iostream>

using namespace std;

bool is_magic_sqrt(vector<int>& grid) {
    int g[3][3];
    for (int i = 0; i < 9; ++i) {
        g[i/3][i%3] = grid[i];
    }
    
    int sum = g[0][0] + g[0][1] + g[0][2];
    for (int i = 0; i < 3; ++i) {
        // Check rows
        if (g[i][0] + g[i][1] + g[i][2] != sum)
            return false;
        // Check cols
        if (g[0][i] + g[1][i] + g[2][i] != sum)
            return false;
    }
    if (g[0][0] + g[1][1] + g[2][2] != sum)
        return false;
    if (g[0][2] + g[1][1] + g[2][0] != sum)
        return false;
    
    return true;
}

void p02_solution() {
    vector<int> perm = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int count = 0;
    do {
        if (is_magic_sqrt(perm))
            count++;
    } while(next_permutation(perm.begin(), perm.end()));
    
    cout << "Possible solution is " << count << " solutions" << endl;
}

//Problem Statement: กำหนดตาราง N×M จงหาพื้นที่สี่เหลี่ยมย่อย (Sub-rectangle) ภายในตารางนี้ที่มีผลรวมของสมาชิกสูงที่สุด
//Input:
//- บรรทัดแรกประกอบด้วย N และ M (1≤N,M≤50)
//- N บรรทัดถัดมา บรรทัดละ M ตัว เป็นค่าในตาราง (-10^4≤〖"grid" 〗_(i,j)≤10^4)
//Output:
//- ค่าผลรวมสูงสุดของสี่เหลี่ยมย่อย

typedef vector<vector<int>> mat;

void p03_solution() {
    int n, m;
    if (!(cin >> n >> m))
        return;
    
    mat grid(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> grid[i][j];
    
    // Build 2D prefix sum
    mat psum(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            psum[i][j] = grid[i-1][j-1] + psum[i-1][j] + psum[i][j-1] - psum[i-1][j-1];
    

    // Find Best sum
    int best_sum = INT_MIN;
    // Left-Top (r1, c1), Right-Bottom (r2, c2)
    for (int r1 = 1; r1 <= n; r1++){
        for (int r2 = r1; r2 <= n; r2++) {
            for (int c1 = 1; c1 <= m; c1++) {
                for (int c2 = c1; c2 <= m; c2++) {
                    int cur_sum = psum[r2][c2] - psum[r1-1][c2] - psum[r2][c1 - 1] + psum[r1-1][c1-1];
                    best_sum = max(best_sum, cur_sum);
                }
            }
        }
    }
    
    cout << "Area Best Sum = " << best_sum << endl;
}


void p10_solution() {
    int n = 4;
    int w_limit = 7;
    
    vector<long> w = {2, 3, 4, 5};
    vector<long> v = {3, 4, 5, 6};
    
    long best_v = 0;
    int subsets = 1 << n;
    
    for (int set = 0; set < subsets; set++) {
        long total_w = 0;
        long total_v = 0;
        int xor_index = 0;
        
        for (int i = 0; i < n; i++) {
            if (set & (1 << i)) {
                total_w += w[i];
                total_v += v[i];
                xor_index ^= i; // xor_index = xor_index ^ i;
            }
        }
        
        if (total_w <= w_limit && (xor_index % 2 == 0)) {
            best_v = max(best_v, total_v);
        }
    }
    cout << "Best Value of P10 = " << best_v << endl;
}


int main_0(int argc, const char * argv[]) {
    p02_solution();
    p10_solution();
    
//    p03_solution();
    return EXIT_SUCCESS;
}
