//ref: Really appreciate classmate 李奕霆，He helped me find the bug of the diminishing table

#include<bits/stdc++.h>
using namespace std;

#define ll long long

vector< vector<ll> > dp(400, vector<ll>(400));
vector< vector<ll> > magic(400, vector<ll>(400));

int main(){

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    cin >> n;
    k = n;

    for(int i = 0; i<n; ++i){
        for(int j = 0; j<n; ++j){
            cin >> magic[i][j];
        }
    }
    //dp solution
    //K cuts, 1 to N length
    //Do N times for each result for N start point
    //Instead, use the combining mode of the result to set the max value 
    //through (size - 1) in each iteration
   
    int end_id = 0, right_cut = 0;
    ll best = 0, temp_no_cut = 0, temp_cut = 0;
    int bind_num = 0;
    vector<ll> store(k, 0);

    int cnt = 0, cnt2 = 0;

    for(int start_id = 1; start_id <= n; ++start_id){// starting point and the "num-th round"
        // For the i = 0 part, No cut
        end_id = start_id;
        if(temp_no_cut < magic[start_id-1][end_id -1])
            temp_no_cut = magic[start_id-1][end_id -1];

        // i >= 1
        bind_num = start_id;
        for(int i = 1; i<=(n-bind_num); ++i){
            for(int j = i; j<=(n-bind_num); ++j){
                end_id = start_id + j;
                right_cut = end_id -1;
                if(end_id == n){ end_id = start_id - 1; }

                //Remember, the right bound of magic array id the next
                best = 0;
                if(i != 1){
                    for(int cut_id = start_id+i-1; cut_id <= right_cut; cut_id++){
                        temp_cut = dp[i-1][cut_id - start_id] + magic[cut_id][end_id];
                        if(best < temp_cut) best = temp_cut;
                    }
                }else{//cut 1 time, 2 parts
                    for(int cut_id = start_id; cut_id <= right_cut; cut_id++){
                        temp_cut = magic[start_id-1][cut_id] + magic[cut_id][end_id];
                        if(best < temp_cut) best = temp_cut;
                    }
                }
                dp[i][j] = best;
            }
        }
        for(int i = 1; i<=(n-bind_num); i++){
            if(store[i] < dp[i][n-bind_num])
                store[i] = dp[i][n-bind_num];
        }
    }

    store[0] = temp_no_cut;
    
    for(int i = 0; i<k; ++i){
        cout << store[i] << " ";
    }

    return 0;
}