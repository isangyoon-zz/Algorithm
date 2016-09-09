// Maximum Flow
struct ford_fulkerson
{
  struct edge
  {
    int to;
    int capacity;
    edge* reverse;

    edge(int to, int capacity) : to(to), capacity(capacity) {}
  };

  std::size_t n;
  int source, sink;
  std::vector<std::vector<edge*>> adj;

  ford_fulkerson(std::size_t n, int source, int sink) : n(n), source(source), sink(sink)
  {
    adj.resize(n);
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

  int dfs(int u, int c)
  {
    if (visited[u]) return 0;
    visited[u] = true;

    if (u == sink) return c;

    for (unsigned int i = 0; i < adj[u].size(); ++i)
    {
      if (adj[u][i]->capacity > 0)
      {
        int capacity = adj[u][i]->capacity;
        if (c != 0 && c < capacity) capacity = c;

        int flow = dfs(adj[u][i]->to, capacity);
        if (flow)
        {
          adj[u][i]->capacity -= flow;
          adj[u][i]->reverse->capacity += flow;

          return flow;
        }
      }
    }

    return 0;
  }

  int flow()
  {
    int answer = 0;
    while (true)
    {
      std::fill(visited.begin(), visited.end(), false);

      int f = dfs(source, 0);
      if (f == 0) break;

      answer += f;
    }

    return answer;
  }
};
