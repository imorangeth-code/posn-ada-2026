//
//  main.cpp
//  posn_day3_2026
//
//  Created by AdaBrain on 17/3/2569 BE.
//

#include <iostream>

using namespace std;

//มีเหรียญมูลค่า {1, 5, 10, 25} ต้องการทอนเงิน N บาทโดยใช้เหรียญ จำนวนน้อยที่สุด
//
//45 -> 25 (45 - 25)
//20 -> 10 (20 - 10)
//10 -> 10


void coin_changer_problem() {
    vector<int> coins = {25, 10, 5, 1};
    int N = 36;
    
    int count = 0;
    for (int c : coins) {
        count += N / c;
        N = N % c;
    }
    
    cout << count << endl;
}


//Fractional Knapsack
//โจทย์
//กระเป๋ารับน้ำหนักได้ W kg
//มีของ n ชิ้น แต่ละชิ้นมีน้ำหนัก w[i] และมูลค่า v[i]
//ตัดแบ่งของได้ — หาค่ามูลค่าสูงสุดที่ใส่กระเป๋าได้
//
//แนวคิด Greedy
//เรียงตาม value/weight ratio จากมากไปน้อย
//ใส่ให้เต็มชิ้น ถ้าใส่ไม่ได้ทั้งชิ้นให้ตัดบางส่วน
//
//Input:
//3 50
//10 60
//20 100
//30 120
//
//Output:
//240
//
//(ใส่ item 1 ทั้งหมด (ratio=6), item 2 ทั้งหมด (ratio=5), item 3 บางส่วน 20kg (ratio=4)
// 60 + 100 + 80 = 240)

struct item {
    long long w, v;
    double ratio;
};

void fractional_knapsack() {
    int n = 3;
    int cap = 50;
    
    vector<item> items(n);
    items[0] = {10, 60, (double) 60/10};
    items[1] = {20, 100, (double) 100/20};
    items[2] = {30, 120, (double) 120/30};
    
    sort(items.begin(), items.end(), [](item& a, item& b) {
        return a.ratio > b.ratio;
    });
    
    double total_v = 0;
    int remain = cap;
    
    for (auto x : items) {
        if (remain <= 0) break;
        
        // Whole item
        if (x.w <= remain) {
            total_v += x.v;
            remain -= x.w;
        } else { // Partial item
            total_v += x.ratio * remain;
            remain = 0;
        }
    }
    
    cout << "Total Value = " << total_v << endl;
}

//6. Huffman Coding
//โจทย์
//บีบอัดข้อมูลโดยให้อักขระที่ใช้บ่อยมี code สั้นกว่า
//
//ตัวอย่าง: AABBBCCCC
//
//A ปรากฏ 2 ครั้ง
//B ปรากฏ 3 ครั้ง
//C ปรากฏ 4 ครั้ง
//
//ขั้น 1: [A:2, B:3, C:4]
//         ↓ รวม A+B
//ขั้น 2: [AB:5, C:4]
//         ↓ รวม C+AB
//ขั้น 3: [CAB:9]
//
//Tree:
//      9
//     / \
//    C   5
//   (4) / \
//      A   B
//     (2) (3)
//
//C = "0"  (1 bit)
//A = "10" (2 bits)
//B = "11" (2 bits)

struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator() (Node *a, Node *b) {
        return a->freq > b->freq;
    }
};

void print_codes(Node* root, string code) {
    if (!root) return;
    if (!root->left && !root->right) {
        cout << root->ch << ": " << code << endl;
    }
    
    print_codes(root->left, code + "0");
    print_codes(root->right, code + "1");
}

void huffman_coding_problem() {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    
    // AABBBCCCC
    pq.push(new Node('A', 2));
    pq.push(new Node('B', 3));
    pq.push(new Node('C', 4));
    
    
    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        
        Node* right = pq.top();
        pq.pop();
        
        Node* merged = new Node('*', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }
    
    print_codes(pq.top(), "");
}


int main_0(int argc, const char * argv[]) {
//    coin_changer_problem();
//    fractional_knapsack();
    
    huffman_coding_problem();
    return EXIT_SUCCESS;
}
