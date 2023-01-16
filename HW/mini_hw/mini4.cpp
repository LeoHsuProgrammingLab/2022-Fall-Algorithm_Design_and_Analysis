#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX LLONG_MAX

class info{
    public:
        int to;
        ll cost;
        info(){
            to = -1;
            cost = MAX;
        }
        info(int a, int b){
            to = a;
            cost = b;
        }
}; 

bool operator<(const info &a, const info &b){
    return a.cost > b.cost;
}

int main(){

    int n, m;
    cin >> n >> m;
    int a, b; ll c, ans = 0;
    vector<info> adj_list[n];
    priority_queue<info> min_h;
    vector<info> info_list(2*m);

    for(int i = 0; i< m; ++i){
        cin >> a >> b >> c;
        info_list[2*i] = info(b-1, c);
        info_list[2*i+1] = info(a-1, c);
        adj_list[a-1].push_back(info_list[2*i]);
        adj_list[b-1].push_back(info_list[2*i+1]);
    }
    // cout << "here\n";
    int cur = 0;
    for(int i = 0; i<adj_list[0].size(); ++i){
        min_h.push(adj_list[0][i]);
        // cout << "size= " << min_h.size() << "\n";
    }
    // cout << adj_list[2].size() << "\n";
    int in_MST[n];
    in_MST[0]=1;
    for(int i =1; i<n; ++i){
        in_MST[i] = 0;
    }
    for(int i = 0; i<n-1; ++i){
        int cur = min_h.top().to;
        while(in_MST[cur]){
            // cout << "what\n";
            min_h.pop();
            cur = min_h.top().to;
        }
        // cout << min_h.top().to << " " << min_h.top().cost << "\n";
        // cout << "over\n";
        ans += min_h.top().cost;
        in_MST[min_h.top().to] = 1;
        min_h.pop();
        int size = adj_list[cur].size();
        for(int j = 0; j<size; ++j){
            min_h.push(adj_list[cur][j]);
        }
    }
    cout << ans << "\n";

    return 0;
}