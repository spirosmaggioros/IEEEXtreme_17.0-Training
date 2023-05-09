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

class graph{
public:
    graph(int V , int E) : V(V) , E(E) {}

    void addEdge(int a , int b){
        adj[a].push_back(b);
        //adj[b].push_back(a);
    }

    void dfs(int start){
        vector<bool> visited(V , false);
        visited[start] = true;
        stack<int> s;
        s.push(start);
        while(!s.empty()){
            int current = s.top();
            visited[current] = true;
            s.pop();
            for(auto & x : adj[current]){
                if(!visited[x]){
                    s.push(x);
                }
            }
        }
    }

    void bfs(int start){
        vector<bool> visited(V , false);
        visited[start] = true;
        queue<int> q;
        q.push(start);
        while(!q.empty()){
            auto current = q.front();
            visited[current] = true;
            q.pop();
            for(auto & x : adj[current]){
                if(!visited[x]){
                    q.push(x);
                }
            }
        }
    }

    void dfs_2(vector<bool> &visited , int start){
        visited[start] = true;
        for(auto & x : adj[start]){
            if(!visited[x]){
                dfs_2(visited , x);
            }
        }
    }


    int islands(int start){
        int counter = 0;
        vector<bool> visited(V , false);
        for(int i = 0; i<V; i++){
            if(!visited[i]) {
                dfs_2(visited, i);
                counter++;
            }
        }
        return counter;
    }

private:
    unordered_map<int , vector<int> > adj;
    int V;
    int E;
};


int main(){
    int V , E; cin >> V >> E;
    graph g(V , E);
    while(E--) {
        int a, b;
        cin >> a >> b;
        g.addEdge(a , b);
    }
    cout << g.islands(0) << '\n';
}
