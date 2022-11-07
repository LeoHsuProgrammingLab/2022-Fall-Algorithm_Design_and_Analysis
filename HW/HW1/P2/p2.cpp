// I sloved this problem on my own, and come up with the idea from the below reference.
// ref:
// 1. https://www.geeksforgeeks.org/unbounded-knapsack-repetition-items-allowed/
// 2. https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/

#include<bits/stdc++.h>

using namespace std;

int greedy(int total_cash, vector<int> store, int n){

    int left = total_cash;
    if(left < store[0]){
        return 0;
    }
    
    for(int i = n-1; i>=0; i--){
        while(left >= store[i]){
            left -= store[i];
        }
        //Don't use %, it is super slow!
        // left = left%store[i]; 
    }

    return left;
}

void resampleOptimizer(int total_cash, vector<int> store, int dp[], int n){
    
    for(int i = 0; i<=total_cash; i++){
        for (int j = 0; j<n; j++){
            if(store[j] <= i){
                dp[i] = max(dp[i], dp[i-store[j]]+store[j]);
            }else{
                break;
            }
        }
    }

}



int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, w;
    cin >> n >> w;

    //For all the ai
    vector<int> store(n);
    //input ai
    for(int i = 0; i< n; i++){
        cin >> store[i];
    }
    sort(store.begin(), store.end());

    //for all weights
    int dp[5001];
    memset(dp, 0, sizeof(dp));
    
    resampleOptimizer(w, store, dp, n);

    for(int i = 1; i<=w; i++){
        if(dp[i] != 0){
            dp[i] = i - dp[i];
        }
        cout<<greedy(i, store, n) - dp[i]<<"\n";
    }


    return 0;
}