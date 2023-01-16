#include<bits/stdc++.h>
using namespace std;
#define MAXN LONG_MAX
#define ll long long

typedef pair<int, int> node;//miles, v

void append_edge(vector< vector< pair<int, int> > > &adj_list, int a, int b, int c){//destination & miles pair
    vector<pair<int, int>> adj;
    adj_list[a].push_back(make_pair(b, c));
}

int main(){

    int n, m;
    cin >> n >> m;
    
    //various graph possibility
    vector< vector< pair<int, int> > > g_arr[n];

    int a, b, c;
    
    g_arr[0].reserve(n+1);
    
    for(int i = 0; i<m; ++i){
        cin >> a >> b >> c;
        append_edge(g_arr[0], a, b, c);
    }
    for(int i = 1; i<=n; ++i){
        for(int j = 0; j<g_arr[0][i].size(); ++j){
            cout << g_arr[0][i][j].first << " ";
        }
        cout << "\n";
    }

//     //Dijkstra's algorithm
//     // 1.min_heap
//     // 2.build dis_arr comparing rules
//     ll ans = MAXN;

//     for(int g = 2; g<=n; g++){// Do for n-1 times
//         // cout << "here\n";
//         vector<int> temp_size(adj_size[g-2].begin(), adj_size[g-2].end());
//         // for(int i = 0; i<temp_size.size(); i++){cout << temp_size[i] << "\n";}

//         append_edge(g_arr[g-2], temp_size, 1, g, 0);
//         // for(int i = 1; i<=n; ++i){
//         //     for(int j = 0; j<temp_size[i]; ++j){
//         //         cout << g_arr[g-2][i][j].first << " ";
//         //     }
//         //     cout << "\n";
//         // }

//         ll temp = 0;
//         vector<ll> dis_arr(n+1, MAXN);
//         dis_arr[1] = 0;

//         priority_queue<node, vector<node>, greater<node>> min_heap;
//         min_heap.push(node(0, 1));
//         // insert the 0 edge
//         min_heap.push(node(0, g));
//         while(!min_heap.empty()){
//             int cur_v = min_heap.top().second;
//             min_heap.pop();
//             // cout << cur_v << " " << "size = " << temp_size[cur_v] << "\n";
//             for(int i = 0; i<temp_size[cur_v]; ++i){
//                 int to_v = g_arr[g-2][cur_v][i].first;
//                 int miles = g_arr[g-2][cur_v][i].second;
//                 // cout << to_v << " " << miles << "\n";
                
//                 if(dis_arr[to_v] > dis_arr[cur_v] + miles){
//                     dis_arr[to_v] = dis_arr[cur_v] + miles;
//                     min_heap.push(node(dis_arr[to_v], to_v));
//                 }
//             }
//         }
//         for(int j = 1; j<=n; ++j){
//             temp += dis_arr[j];
//         }
//         if(temp < ans) ans = temp;
//     }
//     cout << ans <<'\n';

    return 0;
}