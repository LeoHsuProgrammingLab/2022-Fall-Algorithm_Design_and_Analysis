//Advice from TA 胡材溢, really appreciate!

#include<bits/stdc++.h>
using namespace std;
#define ll long long

class node{
    public:
        int max_path;
        ll cost;
        node(){
            max_path = 0;
            cost = 0;
        }
};

class edge{
    public:
        int from, to;
        int l;
        ll c;
        edge(int f, int t, int len, ll co){
            from = f;
            to = t;
            l = len;
            c = co;
        }
        edge(){
            from = -1;
            to = -1;
            l = -1;
            c = -1;
        }
};


bool operator<(const edge &a, const edge &b){
    return (a.l > b.l) || ( (a.l == b.l) && (a.c > b.c) );
}

priority_queue<edge> min_h;

void addEdge(int cur_node, vector<edge> adj_list[], vector<node> &node_list){
    int size = adj_list[cur_node].size();
    //update current edge info
    for(int i = 0; i<size; ++i){
        if(adj_list[cur_node][i].l == node_list[cur_node].max_path){
            adj_list[cur_node][i].c = node_list[cur_node].cost + adj_list[cur_node][i].c;
        }else if(adj_list[cur_node][i].l < node_list[cur_node].max_path){
            adj_list[cur_node][i].c = node_list[cur_node].cost;
        }
        min_h.push(adj_list[cur_node][i]);
    }
}

ll MST_Prim(vector<node> &node_list, bool in_MST[], vector<edge> adj_list[], int n){
    
    for(int i = 0; i<(n-1); ++i){//Haven't finished discovering
        int next_node = min_h.top().to;
        while(in_MST[next_node]){
            min_h.pop();
            next_node = min_h.top().to;
        }
        int cur_node = min_h.top().from;
        int piece_len = min_h.top().l;
        ll piece_cost = min_h.top().c;
        node_list[next_node].cost = min_h.top().c;
        if(piece_len > node_list[cur_node].max_path){
            node_list[next_node].max_path = piece_len;
        }else if(piece_len <= node_list[cur_node].max_path){
            node_list[next_node].max_path = node_list[cur_node].max_path;
        }
        
        min_h.pop();
        addEdge(next_node, adj_list, node_list);
        in_MST[next_node] = 1;
    }

    ll ans = 0;
    for(int i = 1; i<n; ++i){
        ans += node_list[i].cost;
    }
    return ans;
}



int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<edge> adj_list[n];
    vector<node> node_list(n);
    vector<edge> edge_list(2*m);
    
    priority_queue<edge> min_h;
    //Check if it is already in MST
    bool in_MST[n]; in_MST[0] = 1;
    for(int i = 1; i<n; ++i){
        in_MST[i] = 0;
    }

    int u, v, l; ll c;
    for(int i = 0; i<m; ++i){
        cin >> u >> v >> l >> c;
        edge_list[2*i] = edge(u, v, l, c);
        edge_list[2*i+1] = edge(v, u, l, c);
        adj_list[u].push_back(edge_list[2*i]);
        adj_list[v].push_back(edge_list[2*i+1]);
    }

    //start from 0 index vertex
    addEdge(0, adj_list, node_list);
    cout << MST_Prim(node_list, in_MST, adj_list, n) << "\n";


    return 0;
}