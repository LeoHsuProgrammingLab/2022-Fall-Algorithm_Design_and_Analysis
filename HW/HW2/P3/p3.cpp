// ref:
// 1. From TA 胡材溢 & 沈立程 advice, really appreciate!
// 2. Discuss with classmates whose discord name is "阿光".

#include<bits/stdc++.h>
#include<stdio.h>
#define max_int INT_MAX
#define ll long long
using namespace std;

char answer[500005];

int ascii(char a){
    if((int)a >= 48 && (int)a <= 57){
        return (int)a - 48;
    }
    else if((int)a >= 65 && (int)a <= 90){
        return (int)a - 65 + 10;
    }
    else {//if((int)a >= 97 && (int)a <= 122)
        return (int)a - 97 + 36;
    }
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    ll k;
    cin >> k;
    int n = s.size();

    //for first table to store the 62 characters
    vector< deque<int> > char_table(62);

    //previous_larger, tag
    vector< pair<int, int> > info_table;

    //Make the first table
    int tag = 0;
    for(int i = 0; i < n; i++){
        char_table[ascii(s[i])].push_back(i);
        int before_larger = 0;
        for(int j = 61; j > ascii(s[i]); j--){ 
            before_larger += char_table[j].size();
        }
        info_table.push_back(make_pair(before_larger, tag));
    }

    //this is the newborn answer array for store the sorted answer
    int idx = 0;
    unordered_set<int> already_pushed_id;

    for(int i = 0; i<n; i++){
        //For every index I should think the optimal char
        for(int j = 0; j<62; j++){
            if(!char_table[j].empty()){
                int cur_larger = ( info_table[char_table[j].front()].first ) + ( info_table[char_table[j].front()].second );
                if( cur_larger <= k){ //the OPT is here!
                    k -= cur_larger;//adjust the k_
                    answer[idx++] = s[char_table[j].front()];
                    already_pushed_id.insert(char_table[j].front());
                    char_table[j].pop_front();
                    break;
                }else{
                    //change the tag value. 
                    // Because if you need to loop to here, it means that this is the limit of the k_, 
                    // you don't need to specify the tag of the same character in other position 
                    info_table[ char_table[j].front() ].second -= 1;
                }
            }
        }
        if (k == 0) break;
    }

    for(int i = 0; i<n; i++){
        if(!already_pushed_id.count(i)){
            answer[idx++] = s[i];
        }
    }

    //Output the answer array
    cout << answer;

    return 0;
}