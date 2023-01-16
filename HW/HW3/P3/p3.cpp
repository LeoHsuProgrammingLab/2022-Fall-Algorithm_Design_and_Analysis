// ref: Advice from TA 林東君, really appreciate!
// The rest part are from myself
#include<bits/stdc++.h>
using namespace std;
#define white 0
#define black 1

class node{
    public:
        int color, f_time, sub_num, cost, sum_cost, pi, root_id, sub_total_cost;
    node(){
        color = white;//Haven't been discovered
        pi = -1;
        sub_total_cost = 0;
    }
};

vector<node> node_list;

void dfs_visit(vector<int> adj_list[], int &time, int cur_id, vector<int> &order, int num){
    time ++;
    node_list[cur_id].color = black;
    int temp_num = 0, temp_cost = 0;
    for(auto x: adj_list[cur_id]){
        if(node_list[x].color == white){
            dfs_visit(adj_list, time, x, order, temp_num);
            num += node_list[x].sub_num;
            temp_cost += node_list[x].sub_total_cost;
        }
    }
    time ++;
    node_list[cur_id].f_time = time;
    num ++;
    node_list[cur_id].sub_num = num;
    temp_cost += node_list[cur_id].cost;
    node_list[cur_id].sub_total_cost = temp_cost;
    order.push_back(cur_id);
}

void dfs_(vector<int> forest_roots, int &time, vector<int> adj_list[], vector<int> &order){
    for(int i = 0; i<forest_roots.size(); ++i){
        int num = 0;
        dfs_visit(adj_list, time, forest_roots[i], order, num);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int time = 0;
    int n, m; //m is the dollars
    cin >> n >> m;

    node_list.resize(n);
    vector<int> adj_list[n];
    vector<int> forest_roots;

    for(int i = 0; i<n; ++i){
        cin >> node_list[i].pi;
        if(node_list[i].pi == -1){
            forest_roots.push_back(i);
        }else{
            adj_list[node_list[i].pi].push_back(i);
        }
    }

    for(int i = 0; i<n; ++i){
        cin >> node_list[i].cost >> node_list[i].sum_cost;
    }

    //dfs to specify finish time
    vector<int> order;
    dfs_(forest_roots, time, adj_list, order);

    // DP 
    // 0-1 knapsack problem
    int dp_matrix[n+1][m+1];
    for(int i = 0; i<m+1; ++i){
        dp_matrix[0][i] = 0;
    }
    int cur_node;
    for(int i = 1; i<n+1; ++i){
        for(int j = 0; j<m+1; ++j){
            cur_node = order[i-1];
            if(node_list[cur_node].cost > j){ 
                if(node_list[cur_node].sum_cost > j){//1 option
                    dp_matrix[i][j] = dp_matrix[i-1][j];
                }else{//2 options: (Don't take) & Take all subtrees +
                    dp_matrix[i][j] = max(dp_matrix[i-1][j], node_list[cur_node].sub_total_cost + dp_matrix[i-node_list[cur_node].sub_num][j-node_list[cur_node].sum_cost]);
                }
            }else{
                if(node_list[cur_node].sum_cost > j){
                    dp_matrix[i][j] = max(dp_matrix[i-1][j], dp_matrix[i-1][j-node_list[cur_node].cost] + node_list[cur_node].cost);
                }else{
                    //consider 3 situations
                    dp_matrix[i][j] = max(dp_matrix[i-1][j], node_list[cur_node].sub_total_cost + dp_matrix[i-node_list[cur_node].sub_num][j-node_list[cur_node].sum_cost]);
                    dp_matrix[i][j] = max(dp_matrix[i][j], dp_matrix[i-1][j-node_list[cur_node].cost] + node_list[cur_node].cost);
                }
            }
        }
    }
    cout << dp_matrix[n][m] << "\n";

    return 0;
}