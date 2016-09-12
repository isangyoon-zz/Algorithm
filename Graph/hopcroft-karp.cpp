/* Hopcroft-Karp Maximum bipartite matching */
// Index from 1
class hopcroft_karp
{
private:
  typedef std::size_t size_type;
  
  const int INF = 1 << 30;
  
public:
  hopcroft_karp(size_type n) : _n(n), _adj(n + 1), _visited(n + 1, false), _distance(n + 1), _l_match(n + 1), _r_match( n + 1) {}
  
  void add_edge(int u, int v)
  {
    _adj[u].push_back(v);
  }
  
  bool bfs()
  {
    std::queue<int> q;
    
    for (unsigned int i = 1; i <= _n; ++i)
    {
      if (!_l_match[i])
      {
        _distance[i] = 0;
        
        q.push(i);
      }
      else
      {
        _distance[i] = INF;
      }
    }
    
    _distance[0] = INF;
    
    while (!q.empty())
    {
      int u = q.front();
      q.pop();
      
      for (auto v : _adj[u])
      {
        if (_distance[_r_match[v]] == INF)
        {
          _distance[_r_match[v]] = _distance[u] + 1;
          
          q.push(_r_match[v]);
        }
      }
    }
    
    return _distance[0] != INF;
  }
  
  bool dfs(int u)
  {
    if (u)
    {
      for (auto v : _adj[u])
      {
        if (_distance[_r_match[v]] == _distance[u] + 1 && dfs(_r_match[v]))
        {
          _l_match[u] = v;
          _r_match[v] = u;
          
          return true;
        }
      }
      
      _distance[u] = INF;
      
      return false;
    }
    
    return true;
  }
  
  int match()
  {
    int answer = 0;
    
    while (bfs())
    {
      for (unsigned int i = 1; i <= _n; ++i)
      {
        if (!_l_match[i])
        {
          if (dfs(i))
          {
            ++answer;
          }
        }
      }
    }
    
    return answer;
  }

private:
  std::size_t _n;
  std::vector<int> _l_match, _r_match;
  std::vector<int> _distance;
  
  std::vector<bool> _visited;
  std::vector<std::vector<int>> _adj;
};
