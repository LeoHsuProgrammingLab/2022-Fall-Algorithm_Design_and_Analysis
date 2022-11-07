// ref: I programmed this problem by myself.
// The only material is from the class content.

#include<iostream>
#include<vector>
#include<map>
using namespace std;

void divide_conquer(int& step, int start, int end, vector< pair<int, int> >& store){
    
    //Base case
    if(start == end){
        store.push_back(make_pair(3, 0));
        (step) ++;
    }else{
        //Divide and Conquer
        //first half
        divide_conquer(step, start, (start+end)/2, store);
        //Switch position: O(2n)
        //1. POPs
        for(int i = start; i <= end; i++){ 
            store.push_back(make_pair(1, 0));
            (step) ++;
        }
        //2. PLACEs
        for(int i = start; i<=(start+end)/2; i++){
            store.push_back(make_pair(2, i));
            (step) ++;
        }
        for(int i = end; i>(start+end)/2; i--){
            store.push_back(make_pair(2, i));
            (step) ++;
        }
        
        //second half
        divide_conquer(step, (start+end)/2 + 1, end, store);
        
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin>>n;

    int step = 0;
    //0 is no operation, 1 is POP, 2 is PLACE, 3 is PHOTO
    vector< pair<int, int> > store;
    store.reserve(4000001);
    
    //Place in an descending way
    for(int i = 0; i<n; i++){
        store.push_back(make_pair(2, n-i));
        step++;
    }
    divide_conquer(step, 1, n, store);
    
    //stdout step 
    cout<<step<<"\n";
    //stdout operation
    vector<pair<int, int> >::iterator iter;
    for(iter = store.begin(); iter!=store.end(); iter++){
        if((*iter).first == 1){
            cout<<"POP"<<"\n";
        }else if((*iter).first == 2){
            cout<<"PLACE"<<" "<<(*iter).second<<"\n";
        }else{
            cout<<"PHOTO"<<"\n";
        }
        
    }
 
    return 0;
}