struct hopcroft_karp
{
  std::size_t n, m; // number of left nodes (n), number of right nodes (m)
  std::vector<std::vector<int>> adj;
  std::vector<int> matching;
  std::vector<int> distance;
  
  hopcroft_karp(std::size_t n, std::size_t m) : n(n), m(m)
  {
    adj.resize(n);
    matching.resize(n, -1);
    distance.resize(n, -1);
  }
  
  void add_edge(int u, int v)
  {
    adj[u].push_back(v);
  }
  
  void bfs()
  {
    std::queue<int> q;
    for (auto i = 0; i < n; ++i)
    {
      if (matching[i] == -1)
      {
        distance[i] = 0;
        
        q.push(i);
      }
      else
      {
        distance[i] = -1;
      }
    }
    
    while (!q.empty())
    {
      auto u = q.front();
      q.pop();
      
      for (auto v : adj[u])
      {
        if (distance[matching[v]] == -1) return true;
        if (distance[matching[v]] != -1) continue;
        
        distance[matching[v]] = distance[u] + 1;
        
        q.push(matching[v]);
      }
    }
    
    return false;
  }
  
  bool dfs(int u)
  {
    for (auto v : adj[u])
    {
      if (distance[matching[v]] == distance[u] + 1)
      {
        if (dfs(matching[v]))
        {
          matching[u] = v;
          matching[v] = u;
          
          return true;
        }
      }
    }
    
    return false;
  }
  
  int match()
  {
    int answer = 0;
    while (bfs())
    {
      for (auto i = 0; i < n; ++i)
      {
        if (dfs(i) && matching[i] == 0) ++answer;
      }
    }
    
    return answer;
  }
};
