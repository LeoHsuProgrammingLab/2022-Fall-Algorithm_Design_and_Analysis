// I solved the problem based on the advice from TA 許博翔.
// Really appreciate his patience and great teaching skill.

#include<bits/stdc++.h>
#include<vector>
#define ll long long
using namespace std;

void find_pair(ll& ans, int start, int end, int arr[], int table_l[], int table_r[]){
    
    if(start == end) return;

    int mid = (start + end) / 2;

    find_pair(ans, start, mid, arr, table_l, table_r);
    find_pair(ans, mid+1, end, arr, table_l, table_r);

    //store the table_l & table_r id
    vector<int> store_id_l;
    vector<int> store_id_r;

    //construct the minimum table
    int min_table_l[mid - start + 1];
    int min_table_r[end - mid];
    
    int mini = 100001;
    for(int i = mid; i >= start; i--){
        if(arr[i] < mini) mini = arr[i];
        min_table_l[i - start] = mini;
    }

    mini = 100001;
    for(int i = mid + 1; i<=end; i++){
        if(arr[i] < mini) mini = arr[i];
        min_table_r[i - (mid + 1)] = mini;
    }
    
    int ptr1 = mid, ptr2 = mid +1;
    int target1, target2; 
    // minimum at the left side
    while(ptr1 >= start){
        if(ptr2 <= end){
            while(min_table_r[ptr2 - (mid + 1)] > min_table_l[ptr1 - start]){
                table_r[arr[ptr2]] ++; store_id_r.push_back(arr[ptr2]);
                ptr2 ++;
                if(ptr2 > end) break;
            }
        }
         
        target1 = arr[ptr1] - min_table_l[ptr1 - start];
        target2 = arr[ptr1] + min_table_l[ptr1 - start];
        if(target1 > 0){
            ans += table_r[target1];
        }
        if(target2 < 100000){
            ans += table_r[target2];
        }
        ptr1 --;
    }
    
    // minimum at the right side
    ptr2 = mid + 1; ptr1 = mid;
    while(ptr2 <= end){
        if(ptr1 >= start){
            while(min_table_l[ptr1 - start] >= min_table_r[ptr2 - (mid + 1)]){
                table_l[arr[ptr1]] ++; store_id_l.push_back(arr[ptr1]);
                ptr1 --;
                if (ptr1 < start) break;
            }
        }
        
        target1 = arr[ptr2] - min_table_r[ptr2 - (mid + 1)];
        target2 = arr[ptr2] + min_table_r[ptr2 - (mid + 1)];
        if(target1 > 0){
            ans += table_l[target1];
        }
        if(target2 < 100000){
            ans += table_l[target2];
        }
        ptr2 ++;
    }
    
    // clear the history
    // left
    for(int i = 0; i<store_id_l.size(); i++){
        table_l[store_id_l[i]] = 0;
    }
    // right
    for(int i = 0; i<store_id_r.size(); i++){
        table_r[store_id_r[i]] = 0;
    }

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a;
    cin>>n;
    int arr[500005];
    for(int i = 0; i<n; i++){
        cin >> arr[i];
    }

    int table_l[100001] = {0};
    int table_r[100001] = {0};

    ll ans = 0;
    find_pair(ans, 0, n-1, arr, table_l, table_r);

    cout << ans << "\n";

    return 0;
}