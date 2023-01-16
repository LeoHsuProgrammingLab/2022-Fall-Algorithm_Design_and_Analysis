#include "choose.h"
#include<bits/stdc++.h>

/*
Feel free to use global variables.
However, if you want to write your code more "correctly",
you can search for the keyword "anonymous namespace", a helpful tool in C++.
*/

// this is an example usage

int cmp(int a, int b){
    return (compare_task(a, b) == 1);
}

void schedule(int N) {
    int endtime[3];
    for(int i = 0; i<3; ++i){
        endtime[i] = 0;
    }
    std::vector<int> order(N);
    
    for(int i = 0; i<N; ++i){
        order[i] = i+1;
    }
    std::sort(order.begin(), order.end(), cmp);
    for(int i = 0; i<N; ++i){
        if(endtime[1] < endtime[2]){
            endtime[1] = assign_task(1, order[i]);
        }else{
            endtime[2] = assign_task(2, order[i]);
        }
    }
}

