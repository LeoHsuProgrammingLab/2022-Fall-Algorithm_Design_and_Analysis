#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){

    int n, num;
    long long max, temp;
    vector<int> arr;

    cin>>n;
    while(cin>>num){
        arr.push_back(num);
    }
    // cout<<"sum = "<<max<<endl;
    max = arr[0];
    temp = 0;
    int length = arr.size();
    for (int i = 0; i< length; i++){
        temp += arr[i];
        if (max < temp){
            max = temp;
        }
        if (temp < 0){
            temp = 0;
        }
    }
    
    cout<<max<<"\n";

    return 0;
}