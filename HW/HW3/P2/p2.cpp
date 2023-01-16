// ref: https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
// Discuss with classmate whose discord ID is "chung66"

#include<bits/stdc++.h>
using namespace std;
#define MAXN LONG_MAX
#define ll long long

class node{
    public:
        int v;
        ll mile;
        node(int b, ll c){
            v = b;
            mile = c;
        }
};

bool operator<(const node &a, const node &b){
    return a.mile > b.mile;
}

class Graph{
    public:
        int v;
        vector< pair<int, int> >  adj_list[2001];
    Graph(int n){
        v = n;
    }
    void append_edge(int a, int b, int c){//destination & miles pair
        adj_list[a].push_back(make_pair(b, c));
    }
};

ll dijkstra_heap(Graph &graph, int n, int target){
    ll temp = 0;
    vector<ll> dis_arr(n+1, MAXN);
    dis_arr[1] = 0;
    dis_arr[target] = 0;

    priority_queue<node> min_heap;
    min_heap.push(node(1, 0));
    // insert the 0 edge
    min_heap.push(node(target, 0));
        
    while(!min_heap.empty()){
        int v = min_heap.top().v;
        min_heap.pop();

        for(auto x : graph.adj_list[v]){
            int u = x.first;
            int miles = x.second;
            
            if(dis_arr[u] > dis_arr[v] + miles){
                dis_arr[u] = dis_arr[v] + miles;
                min_heap.push(node(u, dis_arr[u]));
            }
        }
    }
    for(int j = 1; j<=n; ++j){
        temp += dis_arr[j];
    }

    return temp;
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    
    //various graph possibility
    //min heap for miles from origin to each vertex which is connected

    int a, b, c;
    Graph graph(n);
    
    for(int i = 0; i<m; ++i){
        cin >> a >> b >> c;
        graph.append_edge(a, b, c);
    }

    //Dijkstra's algorithm
    // 1.min_heap
    // 2.build dis_arr comparing rules
    ll ans = MAXN;
    for(int i = 2; i<=n; ++i){
        ll temp = dijkstra_heap(graph, n, i);
        if(temp < ans) ans = temp;
    }
    cout << ans <<'\n';

    return 0;
}