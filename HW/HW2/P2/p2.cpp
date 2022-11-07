// ref:
// Advice from TA 林秉軒 really appreciate him!

#include<bits/stdc++.h>
using namespace std;

#define ll long long

ll max(ll a, ll b){
    if(a > b) return a;
    else return b;
}

// the sorting rule
bool cmp1(pair<ll, ll> a, pair<ll, ll> b){
    return a.second > b.second;
}
// I learned how to sort the pair of the pair!
// However, TA suggest that I should write a struct to implement, it's way more easy to think.
bool cmp2(pair< ll, pair<ll, ll> > a, pair< ll, pair<ll, ll> > b){
    ll version1 = (a.second.first * a.second.second) + (a.first + b.second.first)*b.second.second;
    ll version2 = (b.second.first * b.second.second) + (b.first + a.second.first)*a.second.second;
    return version1 < version2;
}

// preproceesing for each group
pair<ll, ll> group_time(vector< pair<ll, ll> > group_info){
    ll num = group_info.size();
    sort(group_info.begin(), group_info.end(), cmp1);
    ll a = 0, b = 0;
    for(ll i = 0; i<num; i++){
        a += group_info[i].first;
        b = max(b, a + group_info[i].second);
    }
    return make_pair(a, b);
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, size;
    ll a, b;
    cin >> n;
    vector< pair<ll, ll> >store;
    
    vector< pair<ll, pair<ll, ll> > > inter_group_pair;
    for(ll i = 0; i<n; i++){
        cin >> size;
        
        vector< pair<ll, ll> >group_info;
        for(ll j = 0; j<size; j++){
            cin >> a >> b;
            group_info.push_back(make_pair(a, b));
        }

        pair<ll, ll> temp;
        temp = group_time(group_info);
        store.push_back(temp);
        inter_group_pair.push_back(make_pair(temp.first, make_pair(temp.second, size)));
    }

    sort(inter_group_pair.begin(), inter_group_pair.end(), cmp2);

    ll total = 0;
    ll time = 0;
    for(int i = 0; i<n; i++){
        total += (inter_group_pair[i].second.first + time) * inter_group_pair[i].second.second;
        time += inter_group_pair[i].first;
    }

    cout << total << "\n";

    return 0;
}