#include<bits/stdc++.h>
#define max_int INT_MAX
#define ll long long
using namespace std;

int main(){

    string s;
    cin >> s;
    int n = s.size();
    // cout << "n = " << n <<"\n";

    ll k;
    cin >> k;
    ll k_ = k;
    // cout << k_ << " here\n";

    for(int i = 0; i<n; i++){
        // cout << "i " << i << "\n";
        //find the available minimum
        int min_pos = i;
        for(int j = i+1; j<=(i + k_); j++){
            if(j >= n) break;
            if( int(s[j]) < int(s[i]) && int(s[j]) < int(s[min_pos]) ){
                min_pos = j;
            }
        }
        k_ = k_ - (min_pos - i);
        // swap to the target
        for(int m = min_pos; m > i; m--){
            int temp = s[m];
            s[m] = s[m-1];
            s[m-1] = temp;
        }
        if (k_ == 0) break; 
    }

    for(int i = 0; i<n; i++){
        // cout << "what\n";
        cout << s[i];
    }
    

    return 0;
}