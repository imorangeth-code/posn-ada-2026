//
//  main.cpp
//  posn_day1_2026
//
//  Created by AdaBrain on 15/3/2569 BE.
//
#include <iostream>

using namespace std;

void p20_solution(vector<vector<int>>& rooms) {
    int row = (int) rooms.size();
    int col = (int) rooms[0].size();
    
    const int INF = INT_MAX;
    
    queue<pair<int,int>> q;
    
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            if (rooms[r][c] == 0) {
                q.push({r, c});
            }
        }
    }
    
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        
        for (int i = 0; i < 4; i++) {
            int dr = r + dx[i];
            int dc = c + dy[i];
            
            if (dr >= 0 && dr < row && dc >= 0 && dc < col && rooms[dr][dc] == INF) {
                rooms[dr][dc] = rooms[r][c] + 1;
                q.push({dr, dc});
            }
        }
    }
}

void print_matrix(vector<vector<int>> m) {
    for (vector<int> row : m) {
        for (int x : row) {
            cout << x << "\t";
        }
        cout << endl;
    }
}


//P27 [H] — Cheapest Flights Within K Stops
//n cities, directed flights [from,to,price].
//Find the cheapest price from src to dst with at most k stops.
//(k stops = k+1 edges). Return -1 if impossible.
//
//Input:  n=3, flights=[[0,1,100],[1,2,100],[0,2,500]], src=0, dst=2, k=1
//Output: 200   (0→1→2 = 200 ≤ 500 direct)
//
//State: (cost, node, stops_used). Stop when stops > k.
//Modified Dijkstra / BFS with stop constraint.

int p27_solution(int n, vector<vector<int>> filghts, int src, int dst, int k) {
    // Adjacency list -> {(v, price)}
    vector<vector<pair<int, int>>> adj(n);
    for (auto& f : filghts) {
        adj[f[0]].push_back({f[1], f[2]});
    }
    
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;
    
    queue<pair<int, int>> q;
    q.push({0, src});
    
    int count_stops = 0;
    
    while (!q.empty() && count_stops <= k) {
        int qsize = (int) q.size();
        vector<int> temp = dist;
        
        while(qsize) {
            auto [cost, u] = q.front();
            q.pop();
            
            
            for (auto [v, price] : adj[u]) {
                if (cost + price < temp[v]) {
                    temp[v] = cost + price;
                    q.push({temp[v], v});
                }
            }
            
            
            qsize--;
        }
        
        dist = temp;
        count_stops++;
    }
    
    return dist[dst] == INT_MAX ? -1 : dist[dst];
}


int main(int argc, const char * argv[]) {
    const int INF = INT_MAX;
    vector<vector<int>> rooms = {
        {INF, -1, 0, INF},
        {INF, INF, INF, -1},
        {INF, -1, INF, -1},
        {0, -1, INF, INF}
    };
    
    p20_solution(rooms);
    
    print_matrix(rooms);
    
    cout << endl;
    
    int n = 3;
    vector<vector<int>> flights = {{0,1,100},{1,2,100},{0,2,500}};
    cout << p27_solution(n, flights, 0, 2, 1) << endl;
}

