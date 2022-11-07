//ref:
// 1. Advice from the TA 朱俊能 and 鄭天盛 really appreciate them!

#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define maximum LLONG_MAX

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, temp, max;
    cin >> n >> k;
    int arr[1005];
    for(int i = 0; i<n; i++){
        cin >> arr[i];
    }
    
    // Construct a maximum subarraya table
    // static can store data in somewhere else rather than stack!
    static ll m_subarray_table[1005][1005]; 
    for(int i = 0; i<n; ++i){//start
        temp = 0; max = arr[i];
        for(int j = i; j <n; ++j){//end
            temp += arr[j];
            if(max < temp){
                max = temp;
            }
            if(temp < 0){
                temp = 0;
            }
            m_subarray_table[i][j] = max;
        }
    }

    //dp part
    ll dp[505][1005];
    for(int j = 0; j<n; ++j){
        dp[0][j] = m_subarray_table[0][j]*(j+1);
    }
    ll mini;
    for(int i = 1; i<k; ++i){//i is the cut numbers
        for(int j = i; j<n; ++j){//j is the position of the array
            mini = maximum;
            //dp[i][j] is the minimum of the sum of left plus right of the cut
            for(int m = j-1; m>=(i-1); --m){//m is the cut position 
                mini = min(mini, dp[i-1][m] + m_subarray_table[m+1][j]*(j-m));
            }
            dp[i][j] = mini;
        }
    }
    
    cout << dp[k-1][n-1] << "\n";

    return 0;
}