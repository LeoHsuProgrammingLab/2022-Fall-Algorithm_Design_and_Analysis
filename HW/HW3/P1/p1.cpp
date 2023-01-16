// ref: Done by myself
#include<bits/stdc++.h>
using namespace std;
#define ll long long

class node{
    public:
        int id;
        int value;
        node(int idx, int val){
            id = idx; value = val;
        }
};

bool operator<(const node &a, const node &b){  
    return a.value < b.value;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m; cin >> m;
    string cmd;
    ll temp1, temp2;

    //vector thing
    vector<int> table(m);
    vector<ll> table_sum(m);

    //set of the taken out one
    set<int> id_set;

    int idx = 0;
    for(int i = 0; i<m; ++i){
        cin >> cmd; 
        if(cmd == "PUT"){
            //store the prefix sum and the number
            cin >> temp1;
            table[idx] = temp1;
            if(idx == 0){
                table_sum[idx] = temp1;
            }else{
                table_sum[idx] = table_sum[idx-1] + table[idx];
            }
            idx ++;
        }else if(cmd == "DD"){
            cin >> temp1;
            //calculate the last temp1 numbers
            cout << table_sum[idx-1] - table_sum[idx-temp1] + table[idx-temp1] << "\n";
        }else if(cmd == "CC"){
            cin >> temp1 >> temp2;
            //deal with k
            int ceiling = ceil((double)temp1/(double)temp2);
            //build max heap
            priority_queue<node> max_heap;
            int start = idx-temp1;
            int num = temp1;
            idx = start;
            while(temp1){
                max_heap.push(node(start, table[start]));
                temp1 --;
                start ++;
            }
            long long taken_out = 0;
            for(int j = 0; j<ceiling; j++){
                taken_out += max_heap.top().value;
                id_set.insert(max_heap.top().id);
                max_heap.pop();
            }
            cout << taken_out << "\n";

            //update the table
            start = idx;
            while(num--){
                if(id_set.count(start)){//dango has been removed
                    id_set.erase(start);
                    start ++;
                }else{//dango is still in!
                    table[idx] = table[start];
                    if(idx == 0){
                        table_sum[idx] = table[start];
                    }else{
                        table_sum[idx] = table_sum[idx-1] + table[start];
                    }
                    idx ++; start ++;
                }
            }
        }else{//TAKE
            //vector.pop_back()
            while(id_set.count(idx-1)){//already poped out
                id_set.erase(idx-1);
                idx --;
            }
            cout << table[idx-1] << "\n";
            idx --;
        }
    }
    

    return 0;
}