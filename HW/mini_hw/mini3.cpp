// ref: advice from TA 許博翔
#include<bits/stdc++.h>
using namespace std;
//SCC: use DFS
#define white 0
#define gray 1
#define black 2

class node{
    public:
        int d;
        int f;
        int color;
        int id;
        node *parent;
        node(){
            color = white;
            parent = (node*)NULL;
        }
};

vector<node> node_list;

void dfs_visit(int &time, vector< vector<int> > &adj_list, int cur, long long &num){
    time ++;
    node_list[cur].d = time;
    node_list[cur].color = gray;
    // cout << cur << " ";
    int size = adj_list[cur].size();
    for(int i = 0; i<size; ++i){
        int v = adj_list[cur][i];
        if(node_list[v].color == white){
            dfs_visit(time, adj_list, v, num);
        }
    }
    num ++;
    node_list[cur].color = black;
    time ++;
    node_list[cur].f = time;
}

bool cmp(node a, node b){
    return a.f > b.f;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector< vector<int> > adj_list(n);
    vector< vector<int> > adj_listT(n);
    node_list.resize(n);

    //init
    for(int i = 0; i<n; ++i){
        node_list[i].id = i;
    }
    for(int i = 0; i<m; ++i){
        int u, v;
        cin >> u >> v;
        adj_list[u-1].push_back(v-1);
        adj_listT[v-1].push_back(u-1);
    }
    //dfs
    int time = 0;
    long long num = 0;//calculate for the scc numbers
    for(int i = 0; i<n; i++){
        if(node_list[i].color == white){
            //dfs visit
            num = 0;
            dfs_visit(time, adj_list, i, num);
        }
    }

    //construct G transpose
    sort(node_list.begin(), node_list.end(), cmp);
    for(int i = 0; i<n; ++i){
        node_list[i].color = white;
    }

    time = 0;
    long long ans = 0;
    for(int i = 0; i<n; ++i){
        if(node_list[node_list[i].id].color == white){
            //dfs visit
            num = 0;
            dfs_visit(time, adj_listT, node_list[i].id, num);
            ans += (num * (num-1))/2;
        }
    }
    cout << ans << "\n";

    return 0;
}