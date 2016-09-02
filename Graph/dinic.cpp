// dinic max_flow(n);
// max_flow.add(FROM, TO, capacity[, reverse_capacity]);
// auto answer = max_flow.flow(SOURCE, SINK);

class dinic
{
private:
  typedef int flow_type;
  typedef std::size_t size_type;

public:
  dinic(std::size_t n) : _n(n)
  {
    _adj.resize(_n);
    for (auto i = 0; i < _n; ++i) _adj[i].clear();
  }

  void add(int from, int to, flow_type capacity, flow_type reverse = 0)
  {
    _adj[from].push_back(_edge(to, _adj[to].size(), capacity));
    _adj[to].push_back(_edge(from, _adj[from].size(), reverse));
  }

  bool level(int s, int t)
  {
    int i = 0;

    std::fill(std::begin(_level), std::end(_level), 0);

    _level[s] = 1;
    _q[i++] = s;
    for (auto j = 0; j < i && !_level[t]; ++j)
    {
      int u = _q[j];
      for (auto const& v : _adj[u])
      {
        if (_level[v.next()] || v.residual() == 0) continue;

        _level[v.next()] = _level[u] + 1;
        _q[i++] = v.next();
      }
    }

    return (_level[t] != 0);
  }

  flow_type block(int s, int t, flow_type current)
  {
    if (s == t) return current;
    
    for (auto& i = _start[s]; i < _adj[s].size(); ++i)
    {
      auto& j = _adj[s][i];

      if (j.residual() == 0 || _level[j.next()] != _level[s] + 1) continue;
      if (flow_type residual = block(j.next(), t, std::min(j.residual(), current)))
      {
        j.residual -= residual;
        _adj[j.next()][j.inverse()].add(residual);

        return residual;
      }
    }

    return 0;
  }

  flow_type flow(int s, int t)
  {
    _q.resize(_n);
    _level.resize(_n);
    _start.reserve(_n);

    flow_type result = 0;
    while (level(s, t))
    {
      std::fill(std::begin(_start), std::end(_start), 0);
      while (flow_type f = block(s, t, std::numberic_limits<flow_type>::max())) result += f;
    }

    return result;
  }

protected:
  class _edge
  {
  public:
    _edge(int next, int inverse, flow_type residual) : _next(next), _inverse_edge(inverse), _residual(residual) {}

    int next() const { return _next; }
    int next() { return _next; }
        
    int inverse() const { return _inverse_edge; }
    int inverse() { return _inverse_edge; }


    flow_type residual() const { return _residual; }
    flow_type residual() { return _residual; }

    void add(flow_type r) { _residual += r; }

  private:
    int _next;
    int _inverse_edge;

    flow_type _residual;
  };

private:
  size_type _n;
  std::vector<std::vector<_edge>> _adj;
  std::vector<int> _q, _start;
  std::vector<int> _level;
};