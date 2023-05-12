#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#endif

using namespace std;

#define ll long long
#define vector_ll vecor<long long>
#define MOD 1000000007
typedef long long int int64;
typedef unsigned long int uint32;

template <class Fun> class y_combinator_result {
  Fun fun_;

public:
  template <class T>
  explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}
  template <class... Args> decltype(auto) operator()(Args &&...args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};
template <class Fun> decltype(auto) y_combinator(Fun &&fun) {
  return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

template <typename A, typename B>
ostream &operator<<(ostream &os, const pair<A, B> &p) {
  return os << '(' << p.first << ", " << p.second << ')';
}
template <typename T_container, typename T = typename enable_if<
                                    !is_same<T_container, string>::value,
                                    typename T_container::value_type>::type>
ostream &operator<<(ostream &os, const T_container &v) {
  os << '{';
  string sep;
  for (const T &x : v)
    os << sep << x, sep = ", ";
  return os << '}';
}

void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) {
  cerr << ' ' << H;
  dbg_out(T...);
}
#ifdef SPIROS_DEBUG
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

class graph {
public:
  graph(int V, int E) : V(V), E(E) {}

  void addEdge(int a, int b) {
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  void dfs(int start) {
    vector<bool> visited(V, false);
    visited[start] = true;
    stack<int> s;
    s.push(start);
    while (!s.empty()) {
      int current = s.top();
      visited[current] = true;
      s.pop();
      for (auto &x : adj[current]) {
        if (!visited[x]) {
          s.push(x);
        }
      }
    }
  }

  void bfs(int start) {
    vector<bool> visited(V, false);
    visited[start] = true;
    queue<int> q;
    q.push(start);
    while (!q.empty()) {
      auto current = q.front();
      visited[current] = true;
      q.pop();
      for (auto &x : adj[current]) {
        if (!visited[x]) {
          q.push(x);
        }
      }
    }
  }

  void dfs_2(vector<bool> &visited, int start) {
    visited[start] = true;
    for (auto &x : adj[start]) {
      if (!visited[x]) {
        dfs_2(visited, x);
      }
    }
  }

  int islands(int start) {
    int counter = 0;
    vector<bool> visited(V, false);
    for (int i = 0; i < V; i++) {
      if (!visited[i]) {
        dfs_2(visited, i);
        counter++;
      }
    }
    return counter;
  }

  void push_vertex(int start, stack<int> &s, vector<bool> &visited) {
    visited[start] = true;
    for (auto &x : adj[start]) {
      if (!visited[x]) {
        push_vertex(x, s, visited);
      }
    }

    s.push(start);
  }

  void dfs_with_new(vector<bool> &visited, int start,
                    unordered_map<int, vector<int>> &adj) {
    visited[start] = true;
    for (auto &x : adj[start]) {
      if (!visited[x]) {
        dfs_with_new(visited, x, adj);
      }
    }
  }

  int kosaraju() {
    vector<bool> visited(V, false);
    stack<int> s;
    for (int i = 0; i < V; i++) {
      if (!visited[i]) {
        push_vertex(i, s, visited);
      }
    }
    // φτιάχνω τον καινουργιο γράφο
    unordered_map<int, vector<int>> new_adj;
    for (int i = 0; i < V; i++) {
      for (auto &x : adj[i]) {
        new_adj[x].push_back(i);
      }
    }

    // 2ο πέρασμα
    int scc = 0;
    for (int i = 0; i < V; i++) {
      visited[i] = false;
    }
    while (!s.empty()) {
      int current = s.top();
      s.pop();
      if (!visited[current]) {
        dfs_with_new(visited, current, new_adj);
        scc++;
      }
    }
    return scc;
  }

private:
  unordered_map<int, vector<int>> adj;
  int V;
  int E;
};

class Graph {
public:
  Graph(int V, int E) : V(V), E(E) {}
  void addEdge(int a, int b, int w) {
    adj[a].push_back({b, w});
    adj[b].push_back({a, w});
  }

  int dijkstra(int start, int end) {
    vector<int> dist(V, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        q;
    q.push({0, start});
    dist[start] = 0;
    while (!q.empty()) {
      int currentNode = q.top().second;
      int currentDist = q.top().first;
      q.pop();
      for (auto &x : adj[currentNode]) {
        if (currentDist + x.second < dist[x.second]) {
          dist[x.second] = currentDist + x.second;
          q.push({dist[x.first], x.first});
        }
      }
    }
    if (dist[end] != INT_MAX) {
      return dist[end];
    }
    return -1;
  }

private:
  unordered_map<int, vector<pair<int, int>>> adj;
  int V;
  int E;
};

int main() {
  int V, E;
  cin >> V >> E;
  graph g(V, E);
  while (E--) {
    int a, b;
    cin >> a >> b;
    g.addEdge(a, b);
  }
  cout << g.kosaraju() << '\n';
}
