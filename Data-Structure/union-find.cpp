// O(a(N)) = faster than O(log N)
// index from 0 ~ N - 1
class unionfind
{
public:
  unionfind(int const n) : _parent(n, 0), _rank(n, 0)
  {
    for (int i = 0; i < n; ++i) _parent[i] = i;
  }
  ~unionfind() {}

  int find(int v)
  {
    return (_parent[v] == v) ? v : _parent[v] = find(_parent[v]);
  }

  void unite(int v, int u)
  {
    v = find(v);
    u = find(u);
    if (v == u) return;

    if (_rank[v] < _rank[u])
    {
      _parent[v] = u;
    }
    else
    {
      _parent[u] = v;
      if (_rank[v] == _rank[u]) ++_rank[v];
    }
  }

  bool same(int v, int u)
  {
    return find(v) == find(u);
  }

private:
  std::vector<int> _parent;
  std::vector<int> _rank;
};
