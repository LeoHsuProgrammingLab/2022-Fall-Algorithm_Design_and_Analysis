#include<bits/stdc++.h>
#define ll long long
using namespace std;

int main(){

    int n, a;
    cin>>n;
    int arr[500005];
    for(int i = 0; i<n; i++){
        cin >> arr[i];
    }


    ll ans = 0;
    int minimum;
    
    for(int i = 0; i<n; i++){
        for(int j = i+1; j<n; j++){
            int &minimum = *min_element(arr + i, arr + j + 1);
            // cout << "minimum = " << minimum << "\n";
            if(abs(arr[i] - arr[j]) == minimum){
                ans ++;
            }
        }
    }

    cout << ans << "\n";


    return 0;
}