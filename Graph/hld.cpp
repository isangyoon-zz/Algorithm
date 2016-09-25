// Heavy-light decomposition
namespace hld
{
  typedef int value_type;
  typedef value_type const_value;
  
  typedef value_type& reference;
  typedef const reference const_reference;
  
  typedef value_type* pointer;
  typedef const pointer const_pointer;
  
  typedef std::size_t size_type;
  
  const int LOG = 18;
  const int N = 1 << (LOG - 1);
  
  std::vector<int> tree[N];
  int subtree_size[N], depth[N], parent[LOG][N];
  
  int flat_index[N + 1], flat_ptr;
  
  int chain;
  int head[N], indice[N];
  
  void dfs(int u, int p)
  {
    parent[0][u] = p;    
    subtree_size[u] = 1;
    
    for (auto const v : tree[u])
    {
      if (v == parent[0][u]) continue;
      
      depth[v] = depth[u] + 1;
      dfs(v, u);
      
      subtree_size[u] += subtree_size[v];
    }
  }
  
  void init(size_type size)
  {
    chain = flat_ptr = 0;
    dfs(0, -1);
    std::memset(head, -1, sizeof(head));
    
    for (int i = 1; i < LOG; ++i)
    {
      for (int j = 0; j < size; ++j)
      {
        if (parent[i -  1][j] != -1) parent[i][j] = parent[i - 1][parent[i - 1][j]];
      }
    }
  }
  
  void decompose(int u)
  {
    if (head[chain] == -1) head[chain] = u;
    indices[u] = chain;
    flat_index[u] = ++flat_ptr;
    
    int max_child = -1;
    for (auto const v : tree[u])
    {
      if (v == parent[0][u]) continue;      
      if (max_child == -1 || subtree_size[v] > subtree_size[max_child]) max_child = v;
    }
    
    if (max_child != -1) decompose(max_child);
    
    for (auto const v : tree[u])
    {
      if (v == parent[0][u] || v == max_child) continue;
      
      ++chain;
      
      decompose(v);
    }
  }
  
  int lca(int u, int v)
  {
    if (depth[u] < depth[v]) std::swap(u, v);
    
    int l;
    for (l = 1; 1 << l <= depth[u]; ++l);
    --l;
    
    int diff = depth[u] - depth[v];
    for (int i = l; i >= 0; --i)
    {
      if ((diff >> i) & 1) u = parent[i][u];
    }
    
    if (u == v) return u;
    
    for (int i = l; i >= 0; --i)
    {
      if (parent[i][u] != parent[i][v])
      {
        u = parent[i][u], v = parent[i][v];
      }
    }
    
    return parent[0][u];
  }
  
  int subquery(int u, int v, int t)
  {
    int u_chain;
    int v_chain = indice[v];
    
    int answer = 0;
    while (true)
    {
      u_chain = indice[u];
      
      if (u_chain == v_chain)
      {
        answer += query(... Todo
      }
    }
  }
}
  
