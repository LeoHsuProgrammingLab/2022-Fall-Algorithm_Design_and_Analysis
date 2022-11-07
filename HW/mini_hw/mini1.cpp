// I discussed with classmate 羅恩至 and think myself about dp problem
#include<bits/stdc++.h>
using namespace std;

int dp_transformString(string x, string y){
    int size1 = x.size(), size2 = y.size();
    int dp[size1+1][size2+1];
    for(int i = 0; i<= size1; i++){
        for(int j = 0; j<=size2; j++){
            if(i == 0)
                dp[i][j] = j;
            else if(j == 0)
                dp[i][j] = i;
            else if(x[i-1] == y[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + min(min(dp[i][j-1], dp[i-1][j]), dp[i-1][j-1]);
        }
    }
    int ans = dp[size1][size2];

    return ans;

}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string x;
    string y;
    cin >> x >> y;
    cout << dp_transformString(x, y) << "\n";


    return 0;
}


