// #include<iostream>
// #include<vector>
// #include<algorithm>
// #include<queue>
// using namespace std;

// #define ll long long

// bool sortcol(const vector<ll>& v1, const vector<ll>& v2){
//     return v1[0] < v2[0];
// }

// void cdq_reverse_pair(vector< vector<ll> > &coord, ll start, ll end, ll* ans){
//     //Base case
//     if(start == end){
//         return;
//     }

//     ll mid = (start + end)/2;
//     cdq_reverse_pair(coord, start, mid, ans);
//     cdq_reverse_pair(coord, mid+1, end, ans);


//     //sort left half
//     vector<long long> left;
//     for(ll i = start; i<=mid; i++){
//         left.push_back(coord[i][1]);
//     }
//     sort(left.begin(), left.end());

//     //sort right half
//     vector<long long> right;
//     for(ll i = mid+1; i<=end; i++){
//         right.push_back(coord[i][1]);
//     }
//     sort(right.begin(), right.end());

//     // cout<<"start: "<<start<<" "<<"mid: "<<mid<<" "<<"end: "<<end<<"\n";
//     // cout<<"this is size: "<<left.size()<<"\n";

//     ll i = start, j = mid+1;
//     while( i <= mid && j <= end){
//         if(left[i-start] >= right[j-(mid+1)]){
//             *ans += (mid-i)+1;
//             j++;
//         }else{
//             if(coord[i][0] == coord[j][0]){
//                 *ans += 1;
//             }
//             i++;
//         }
//     }
// }

// void chiou_rnp(vector< vector<ll> > &coord, ll start, ll end, ll* ans){
    
//     cout << "in\n";
//     for(ll i =start; i <= end; ++i){
//         cout << coord[i][1] << " ";
//     }
//     cout << '\n';
//     if(start == end) return;


//     ll mid = (start + end)/2;
//     chiou_rnp(coord,start,mid,ans);
//     chiou_rnp(coord,mid+1,end,ans);

//     ll ptr1 = start;
//     ll ptr2 = mid+1;
//     queue<ll> q;
//     ll add = 0;
//     while( ptr1 <= mid && ptr2 <= end ){
//         cout << coord[ptr1][1] << "vs"<< coord[ptr2][1] << endl;
//         if(coord[ptr1][1] < coord[ptr2][1]){
//             if(coord[ptr1][0] == coord[ptr2][0]) add++;
//             q.push(coord[ptr1][1]);
//             cout << "abbccc " << ptr1 << '\n';
//             ptr1++;
//             cout << "abbccc2 " << ptr1 << '\n';
//         }else{
//             add += mid - ptr1 + 1;
//             cout << "addadd " <<  mid - ptr1 + 1<<'\n';
//             cout << coord[ptr2][1] << ' ' << coord[ptr1][1] << '\n';
//             cout << mid << " " << ptr1 << endl;
//             q.push(coord[ptr2][1]);
//             ptr2++;
//         }
//     }

//     *ans += add;

//     while(ptr1 <= mid){
//         q.push(coord[ptr1][1]);
//         ptr1++;
//     }

//     while(ptr2 <= end){
//         q.push(coord[ptr2][1]);
//         ptr2++;
//     }
//     cout << "add = " << add << ' '; 
//     cout << "ans = " << *ans << '\n'; 

// }

// void bf(ll* ans){
    
// }

// int main(){
//     ll l1, l2, r1, r2, n;
//     cin>>n>>l1>>l2>>r1>>r2;
    
//     vector< vector<ll> > original_coord;
//     vector< vector<ll> > coord; 
//     ll x, y;
//     ll num = n;
    
//     while(num--){
//         vector<ll> vec;
//         cin>>x>>y;
//         vec.push_back(l1*x - l2*y);
//         vec.push_back(r1*x - r2*y);
//         coord.push_back(vec);
//     }
    
//     // ll n1 = coord.size();
//     // ll m = coord[0].size();
//     // cout<<"start sort!"<<"\n";
//     // for(ll i = 0; i<n1; i++){
//     //     for(ll j = 0; j<m; j++){
//     //         cout<<coord[i][j]<<" ";
//     //     }
//     //     cout<<"\n";
//     // }

//     // cout<<"sort here!"<<"\n";

//     sort(coord.begin(), coord.end(), sortcol);

    
//     ll ans = 0;
//     cdq_reverse_pair(coord, 0, n-1, &ans);
//     //cdq_reverse_pair(coord, 0, n-1, &ans);
//     cout<<ans<<"\n";
    
    
//     // for(ll i = 0; i<n1; i++){
//     //     for(ll j = 0; j<m; j++){
//     //         cout<<coord[i][j]<<" ";
//     //     }
//     //     cout<<"\n";
//     // }



//     return 0;
// }

#include<iostream>
#define err 0.00000000001
using namespace std;
#define ll long long

typedef struct Point{
    ll x, y;
}Point;

Point point[1000005];

double cal(Point p1, Point p2){
    return ((double)p1.y - (double)p2.y) / ((double)p1.x - (double)p2.x);
}

int main(){
    ll total, l1, l2, r1, r2;
    
    cin >> total >> l1 >> l2 >> r1 >> r2;
    double l = (double)l1 / (double)l2;
    double r = (double)r1 / (double)r2;
    cout<< "l = " << l << " r = " << r << "\n";
    
    for(int i = 0; i < total; i++)
        cin >> point[i].x >> point[i].y;
    
    
    ll counter = 0;
    for(int i = 0; i < total; i++){
        for(int j = i + 1; j < total; j++){
            double slope = cal(point[i], point[j]);
            cout << "point i = " << point[i].x << " " << point[i].y << "\n";
            cout << "point j = " << point[j].x << " " << point[j].y << "\n";
            
            if(l - err <= slope && slope <= r + err){
                cout<< "slope = " << slope << "\n";
                cout<< "\n";
                counter++;
            }
        }
    }
    
    cout << counter << "\n";
}