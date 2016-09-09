// Maximum Flow
struct dinic
{
  struct edge
  {
    int to;
    int capacity;
    edge* reverse;

    edge(int to, int capacity) : to(to), capacity(capacity) {}
  };

  const int INF = 2147483647;

  std::size_t n;
  int source, sink;
  std::vector<std::vector<edge*>> adj;
  std::vector<int> distance;
  std::vector<int> q, s;

  dinic(std::size_t n, int source, int sink) : n(n), source(source), sink(sink)
  {
    adj.resize(n);
    distance.resize(n);
    q.resize(n);
    s.resize(n);
  }

  void add_edge(int u, int v, int capacity)
  {
    edge* forward = new edge(v, capacity);
    edge* backward = new edge(u, 0);

    forward->reverse = backward;
    backward->reverse = forward;

    adj[u].push_back(forward);
    adj[v].push_back(backward);
  }

  void add_edge_from_source(int v, int capacity)
  {
    add_edge(source, v, capacity);
  }

  void add_edge_to_sink(int u, int capacity)
  {
    add_edge(u, sink, capacity);
  }

  bool bfs(int source, int sink)
  {
    int i = 0;
    std::memset(&distance[0], 0, sizeof(distance[0]) * n);

    distance[source] = 1;
    q[i++] = source;
    for (int j = 0; i > j && !distance[sink]; ++j)
    {
      int u = q[j];
      for (auto const& v : adj[u])
      {
        if (distance[v->to] || v->capacity == 0) continue;

        distance[v->to] = distance[u] + 1;
        q[i++] = v->to;
      }
    }

    return (distance[sink] != 0);
  }

  int dfs(int current, int sink, int capacity)
  {
    if (current == sink) return current;

    for (auto& i = s[current]; i < adj[current].size(); ++i)
    {
      auto v = adj[current][i];

      if (int flow = dfs(v->to, sink, std::min(v->capacity, capacity)))
      {
        adj[current][i]->capacity -= flow;
        adj[current][i]->reverse->capacity += flow;
        
        return flow;
      }
    }

    return 0;
  }

  int flow()
  {
    int answer = 0;
    while (bfs(source, sink))
    {
      std::memset(&s[0], 0, sizeof(s[0]) * n);
      while (int f = dfs(source, sink, INF))
      {
        answer += f;
      }
    }

    return answer;
  }
};
