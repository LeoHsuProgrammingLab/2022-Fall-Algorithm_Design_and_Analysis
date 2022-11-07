// ref: 
// 1. https://walkonnet.com/archives/462481
// 2. Advice from TA 林東君, really appreciate his passionate and generous teaching style!
// 3. Discuss with classmates whose dicord name is “阿光”

#include<bits/stdc++.h>
using namespace std;

#define ll long long

//Wanna know how many different heights can we get
ll op_plus(ll a, ll b, ll modulo){
    return (a + b > modulo ? a+b - modulo : a+b);
}

ll op_minus(ll a, ll b, ll modulo){
    if(a - b < 0){
        return (a-b) + modulo;
    }
    return a - b;
}

void dp_processing(ll dp1[305][305], ll dp2[305][305], int k, ll modulo){
    // 1. preprocessing for prefix
    for(int j = 0; j<=k; ++j){
        for(int m = 1; m<=k; ++m){
            dp1[j][m] = op_plus(dp1[j][m], dp1[j][m-1], modulo);
        }
    }

    // 2. calculate
    for(int m = 0; m<=k; ++m){
        dp2[0][m] = dp1[0][m];
    }

    for(int j = 1; j<=k; ++j){
        for(int m = 0; m<=k; ++m){
            dp2[j][m] = op_plus( dp1[j][m], op_minus(dp2[j-1][m+1], dp1[j-1][m], modulo), modulo);
        }
    }
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    ll modulo, ans; 
    cin >> modulo;
    
    ll dp1[305][305], dp2[305][305];
    //initialization
    for(int i = 0; i<=k; ++i){
        for(int j = 0; j<=k; j++){
            dp1[i][j] = 1;
            dp2[i][j] = 0;
        }
    }

    bool i_even;

    for(int i = 2; i <= (n+1); ++i){
        if(i % 2 == 0) i_even = true;
        else i_even = false;

        //rolling dp
        if(i_even){//put to the dp1
            dp_processing(dp1, dp2, k, modulo);
        }else{//put to the dp2
            dp_processing(dp2, dp1, k, modulo);
        }
    }

    if(i_even){
        ans = dp2[k][0];
    }else{
        ans = dp1[k][0];
    }
    
    //output the modulo
    cout << ans << "\n";

    return 0;
}