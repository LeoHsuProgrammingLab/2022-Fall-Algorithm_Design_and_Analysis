// ref: Discussion with classmates in Discord

#include<bits/stdc++.h>
#include "ypglpk.hpp"
using namespace std;

#define ll long long

int main(){

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n,m;
    cin >> n >> m;
    vector< vector<double> > A(m+3*n, vector<double>(n+m, 0));
    vector<double> B(m+3*n), C(n+m);
    //C is the vector of parameters you want to maximize
    //B is the vector of parameters in your inequality formula
    for(int i = 0; i<n; ++i){
        C[i] = 0;
    }

    int u, v, w;
    vector< int > adj_list_out[n];//store the index of the out edge
    vector< int > adj_list_in[n];//store the index of the in edge
    for(int i = 0; i<m; ++i){
        cin >> u >> v >> w;
        C[n+i] = w;
        B[i] = 9999;
        A[i][u-1] = 1; A[i][v-1] = -1;
        A[i][n+i] = 10000;
        adj_list_out[u-1].push_back(i);
        adj_list_in[v-1].push_back(i);
    }
    for(int i = 0; i<n; ++i){
        int len_in = adj_list_in[i].size();
        int len_out = adj_list_out[i].size();
        //fill the 3*n rows of the A 
        for(int j = 0; j<len_in; ++j){
            A[m+2*i][n+adj_list_in[i][j]] = 1;
            A[m+(2*i+1)][n+adj_list_in[i][j]] = -1;
        }
        for(int j = 0; j<len_out; ++j){
            A[m+2*i][n+adj_list_out[i][j]] = -1;
            A[m+(2*i+1)][n+adj_list_out[i][j]] = 1;
            //last n rows
            A[m+2*n+i][n+adj_list_out[i][j]] = 1;
        }
        
        if(i == 0){
            B[m+2*i] = -1;
            B[m+(2*i+1)] = 1;
            B[m+2*n+i] = 1;
        }else if(i == n-1){
            B[m+2*i] = 1;
            B[m+(2*i+1)] = -1;
            B[m+2*n+i] = 0;
        }else{
            B[m+2*i] = 0;
            B[m+(2*i+1)] = 0;
            B[m+2*n+i] = 1;
        }
    }

    // for(int i = 0; i<(m+3*n); i++){
    //     for(int j = 0; j<(m+n); j++){
    //         cout << A[i][j] << " ";
    //     }
    //     cout << B[i];
    //     cout << "\n";
    // }
    pair<double, vector<double>> res;
    
    vector<int> vartype(m+n);
    for(int i = 0; i<m+n; ++i){
        if(i >= n){
            vartype[i] = GLP_BV;
        }else{
            vartype[i] = GLP_CV;
        }
    }

    res = ypglpk::mixed_integer_linear_programming(A, B, C, vartype);
    if(res.first == -ypglpk::INF){
        cout << -1 << "\n";
    }else{
        cout << (ll)res.first << "\n";
        for(int i = 0; i<m; ++i){
            cout << res.second[n+i];
        }
        cout << "\n";
    }

    return 0;
}