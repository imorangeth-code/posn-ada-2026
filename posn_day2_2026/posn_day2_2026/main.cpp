//
//  main.cpp
//  posn_day2_2026
//
//  Created by AdaBrain on 16/3/2569 BE.
//
#include <iostream>

using namespace std;

//int branch_and_bound(Problem problem) {
//    int best = initial_solution(problem); // เริ่มจาก greedy หรือ heuristic
//    queue<Node> q;
//    q.push(root_node);
//
//    while (!q.empty()) {
//        Node node = select_node(q); // BFS หรือ DFS หรือ Best-First
//
//        if (node.bound() <= best) { // Pruning condition
//            continue;               // ตัดกิ่งนี้ทิ้ง
//        }
//
//        if (node.is_leaf()) {
//            best = max(best, node.value);
//        } else {
//            for (Node child : node.branch()) {
//                if (child.bound() > best) {
//                    q.push(child);  // เพิ่มเฉพาะ node ที่มีโอกาส
//                }
//            }
//        }
//    }
//    return best;
//}


struct item {
    long w;
    long v;
    int id;
};

void p01_solution() {
    int n = 4;
    int w_limit = 5;
    
    vector<item> items(n);
    items[0] = {2, 6, 0};
    items[1] = {2, 10, 1};
    items[2] = {3, 12, 2};
    items[3] = {7, 14, 3};
    
    sort(items.begin(), items.end(), [](item& a, item& b) {
        return (double) a.v / a.w > (double) b.v / b.w;
    });
    
    long best_v = 0;
    
    auto upper_bound = [&](int idx, long cur_w, long cur_v) {
        double bound = cur_v;
        long remain = w_limit - cur_w;
        
        for (int i = idx; i < n; ++i) {
            if (items[i].w <= remain) {
                bound += items[i].v;
                remain -= items[i].w;
            } else {
                bound += remain * ((double) items[i].v / items[i].w);
                break;
            }
        }
        return bound;
    };
    
    auto solve = [&] (auto& self, int idx, long cur_w, long cur_v) -> void {
        if (idx == n) {
            if (cur_v > best_v) {
                best_v = cur_v;
            }
            return;
        }
        
        if (upper_bound(idx, cur_w, cur_v) <= best_v) {
            return;
        }
        
        long w = items[idx].w;
        long v = items[idx].v;
        
        if (cur_w + w <= w_limit) {
            self(self, idx + 1, cur_w + w, cur_v + v);
        }
        
        self(self, idx + 1, cur_w, cur_v);
    };
    
    solve(solve, 0, 0, 0);
    cout << "The best value is " << best_v << endl;
}


void p02_bnb_solution() {
    int n = 5;
    int t = 15;
    vector<long> arr = {3, 8, 2, 5, 7};
    
    sort(arr.begin(), arr.end());
    
    vector<long> suffix_sum(n + 1, 0);
    
    for (int i = n - 1; i >= 0; i--) {
        suffix_sum[i] = suffix_sum[i + 1] + arr[i];
    }
    
    bool is_found = false;
    
    auto solve = [&](auto& self, int idx, long cur_sum) -> void {
        // Halt case , Terminate case
        if (is_found) return;
        if (cur_sum == t) {
            is_found = true;
            return;
        }
        if (idx == n || cur_sum > t) return;
        if (cur_sum + suffix_sum[idx] < t) return;
        
        self(self, idx + 1, cur_sum + arr[idx]);
        self(self, idx + 1, cur_sum);
    };
    
    solve(solve, 0, 0);
    cout << (is_found ? "YES" : "NO") << endl;
}

void p04_bnb_solution() {
    int n = 8;
    
    int counter = 0;
    
    vector<bool> col(n, false), diag1(2 * n , false), diag2(2 * n, false);
    
    auto solve = [&](auto& self, int r) -> void {
        // Terminate Case
        if (r == n) {
            counter++;
            return;
        }
        
        for (int c = 0; c < n; c++) {
            if (!col[c] && !diag1[r + c] && !diag2[r - c + n -1]) {
                col[c] = true;
                diag1[r + c] = true;
                diag2[r - c + n - 1] = true;
                
                self(self, r + 1);
                
                col[c] = false;
                diag1[r + c] = false;
                diag2[r - c + n - 1] = false;
            }
        }
    };
    
    solve(solve, 0);
    cout << "Total solution = " << counter << endl;
}

int main(int argc, const char * argv[]) {

//    p02_bnb_solution();
    p04_bnb_solution();
    
    return EXIT_SUCCESS;
}
