// ref: Advice from TAs! Really appreciate!

#include<bits/stdc++.h>
#include<stdlib.h>
using namespace std;

struct node{
    // wrong method!
    // int *freq=new int(0);
    // int *index=new int(0);
    int freq;
    int index;
    struct node *left;
    struct node *right;
    // node() {
    //     freq = new int(0);
    //     ...
    // }
};

// node arr[] = new node[10]

struct cmp{  
    bool operator()(node *l, node *r){  
        return l->freq > r->freq;
    }  
 };


void iterate_heap(node* top, string result[], string str){
    if(top == NULL) return;
    
    if(top->index != -1){
        if(str == ""){
            str = str + "0";
        }
        result[top->index] = str;
    }
    // cout << "Hi\n";
    iterate_heap(top->left, result, str + "0");
    iterate_heap(top->right, result, str + "1");
}

int main(){
    
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int base = -1;
    int f = 0;
    int n; cin >> n;
    int arr[55];
    string result[55];
    node** node_arr = (node**)malloc( 105*sizeof(node*) );
    for(int i=0; i<105; ++i)node_arr[i]=(node*)malloc(sizeof(node));
    // for(int i=0; i<105; ++i)node_arr[i]=new node();
    //min-heap
    priority_queue< node*, vector<node*>, cmp > min_h;
    int temp;
    for(int i = 0; i<n; i++){
        cin >> arr[i];
        //construct the node
        node_arr[i+50]->left = NULL;
        node_arr[i+50]->right = NULL;
        node_arr[i+50]->freq = arr[i];
        node_arr[i+50]->index = i;
        
        node_arr[i]->left = NULL;
        node_arr[i]->right = NULL;
        node_arr[i]->freq = f;
        node_arr[i]->index = base;
        

        // cout << node_arr[i+50]->freq << " freq\n";
        min_h.push(node_arr[i+50]);
        result[i] = "";
    }

    // while(!min_h.empty()){
    //     cout << min_h.top().freq << "\n";
    //     min_h.pop();
    // }
    
    for(int i = 0; i<n-1; i++){
        //construct left
        node_arr[i]->left = min_h.top();
        //pop
        min_h.pop();
        //construct right
        node_arr[i]->right = min_h.top();
        //pop
        min_h.pop();

        //freq = left + right
        node_arr[i]->freq = node_arr[i]->left->freq + node_arr[i]->right->freq;
        min_h.push(node_arr[i]);
        // cout << "freq of the root = " << node_arr[i]->freq << "\n";
        // cout << "i = " << i << " \n";
    }
    
    iterate_heap(min_h.top(), result, "");
    
    for(int i = 0; i<n; ++i){
        cout << result[i] << "\n";
    }

    return 0;
}