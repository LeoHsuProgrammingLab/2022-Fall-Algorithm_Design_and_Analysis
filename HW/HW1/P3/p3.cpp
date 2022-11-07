// The idea to solve this problem is from the discord channel and I implement it myself.
// ref:
// 1. https://zhuanlan.zhihu.com/p/332996578
// 2. https://blog.csdn.net/K_R_forever/article/details/81702934

#include<iostream>
#include<vector>
#include<algorithm>
#define Int long long
using namespace std;

Int transform(pair<Int, Int> pair_coord, Int l1_or_r1, Int l2_or_r2){
    return l1_or_r1*pair_coord.first - l2_or_r2*pair_coord.second;
}

void cdq_reverse_pair(vector< pair<Int, Int> > &coord, Int start, Int end, Int& ans, Int l1_or_r1, Int l2_or_r2, bool anti){
    //Base case
    if(start == end){
        return;
    }

    Int mid = (start + end)/2;
    cdq_reverse_pair(coord, start, mid, ans, l1_or_r1, l2_or_r2, anti);
    cdq_reverse_pair(coord, mid+1, end, ans, l1_or_r1, l2_or_r2, anti);

    vector<Int> temp;

    Int ptr1 = start, ptr2 = mid+1;
    while(ptr2 <= end){

        if(ptr1 <= mid){
            if(anti){
                while(coord[ptr1].second <= coord[ptr2].second){
                    temp.push_back(coord[ptr1].second);
                    ptr1 ++;
                    if(ptr1 > mid) {
                        break;
                    }
                }
            }else{
                while(coord[ptr1].second < coord[ptr2].second){
                    temp.push_back(coord[ptr1].second);
                    ptr1 ++;
                    if(ptr1 > mid) {
                        break;
                    }
                }
            }
            ans += (mid - ptr1 + 1);
        }
        temp.push_back(coord[ptr2].second);
        ptr2++;
    }
    while(ptr1 <= mid){
        temp.push_back(coord[ptr1].second);
        ptr1++;
    }

    for(Int i = start; i<=end; ++i){
        coord[i].second = temp[i-start]; 
    }
    

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    Int l1, l2, r1, r2, n;
    cin >> n >> l1 >> l2 >> r1 >> r2;
    
    vector< pair<Int, Int> > coord1;
     
    Int x, y;
    
    
    for(Int i = 0; i<n; i++){
        cin>>x>>y;
        coord1.push_back(make_pair(x, y));
    }

    sort(coord1.begin(), coord1.end());
    Int size = coord1.size();
    vector< pair<Int, Int> > coord2(coord1);
    

    for(int i = 0; i<size; i++){
        coord1[i].second = transform(coord1[i], l1, l2);
    }

    for(int i = 0; i<size; i++){
        coord2[i].second = transform(coord2[i], r1, r2);
    }     
    

    vector< pair<Int, Int> >::iterator itr2;
    bool anti = 0;

    Int ans = 0; 
    cdq_reverse_pair(coord1, 0, n-1, ans, l1, l2, anti);

    Int anti_ans = 0;
    anti = 1;
    cdq_reverse_pair(coord2, 0, n-1, anti_ans, r1, r2, anti);

    cout << ans - anti_ans <<"\n";

    return 0;
}

