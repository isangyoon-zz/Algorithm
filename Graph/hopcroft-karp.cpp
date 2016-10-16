/* Hopcroft-Karp Maximum bipartite matching */
// usage:
// HopcroftKarp::initialize(n, m); // initialize
// HopcroftKarp::add_edge; // add_edge
// int answer = HopcroftKarp::matching; // find maximum matching
namespace HopcroftKarp
{
  const int MAX = 50000;
  
  int N, M;
  std::vector<int> adj[MAX];
  int left[MAX], right[MAX];
  int dist[MAX];
  bool used[MAX];
  
  void initialize(int n, int m)
  {
    N = n, M = m;
    
    std::fill(left, left + MAX, -1);
    std::fill(right, right + MAX, -1);
    std::fill(used, used + MAX, false);
    
    for (int i = 0; i < N; ++i) adj[i].clear();
  }
  
  void add_edge(int u, int v)
  {
    adj[u].push_back(v);
  }
  
  void bfs()
  {
    std::queue<int> q;
    
    for (int i = 0; i < N; ++i)
    {
      if (!used[i]) dist[i] = 0, q.push(i);
      else dist[i] = 1 << 30;
    }
    
    while (!q.empty())
    {
      int u = q.front();
      q.pop();
      
      for (int const v : adj[u])
      {
        if (right[v] != -1 && dist[right[v]] == 1 << 30)
        {
          dist[right[v]] = dist[u] + 1;
          q.push(right[v]);
        }
      }
    }
  }
  
  bool dfs(int u)
  {
    for (int const v : adj[u])
    {
      if (right[v] == -1 || (dist[right[v]] == dist[u] + 1 && dfs(right[v])))
      {
        used[u] = true;
        left[u] = v, right[v] = u;
        
        return true;
      }
    }
    
    return false;
  }
  
  int matching()
  {
    for (int answer = 0;;)
    {
      bfs();
      
      int flow = 0;
      for (int i = 0; i < N; ++i)
      {
        if (!used[i] && dfs(i)) ++flow;
      }
      
      if (!flow) return answer;
      answer += flow;
    }
  }
}
