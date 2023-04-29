#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define vector_ll vecor<long long>
#define MOD 1000000007
typedef long long int int64;
typedef unsigned long int uint32;

template<class Fun> class y_combinator_result {
    Fun fun_;
public:
    template<class T> explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}
    template<class ...Args> decltype(auto) operator()(Args &&...args) { return fun_(std::ref(*this), std::forward<Args>(args)...); }
};
template<class Fun> decltype(auto) y_combinator(Fun &&fun) { return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun)); }


template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#ifdef SPIROS_DEBUG
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

class Graph{
public:
    Graph(ll n , ll m) : n(n) , w(m){}

    void addEdge(ll u , ll v){
        m[u].push_back(v);
        m[v].push_back(u);
    }
    void dfs(ll &start , vector<bool> &visited){
        visited[start] = true;
        for(auto & x : m[start]){
            if(!visited[x]){
                dfs(x , visited);
            }
        }
    }

    ll connected_components(){
        ll ans = 0;
        vector<bool> visited(n , false);
        for(ll i = 0; i<n; i++){
            if(!visited[i]){
                dfs(i , visited);
                ans++;
            }
        }
        return ans;
    }

private:
    unordered_map<ll , vector<ll> > m;

    ll n;
    ll w;
};

int main(){
    ll n , m; cin >> n >> m;
    Graph g(n  , m);
    while(m--){
        ll a , b; cin >> a >> b;
        g.addEdge(a , b);
    }
    cout << g.connected_components() << '\n';
}
