// Maximum Flow
struct edmonds_karp
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

  edmonds_karp(std::size_t n, int source, int sink) : n(n), source(source), sink(sink)
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

  int bfs()
  {
    std::vector<bool> visited(n, false);
    std::vector<std::pair<int, int>> pred(n, std::make_pair(-1, -1));
    std::queue<int> q;

    q.push(source);
    visited[source] = true;

    while (!q.empty())
    {
      int u = q.front();
      q.pop();

      for (auto i = 0; i < adj[u].size(); ++i)
      {
        auto v = adj[u][i];

        if (v->capacity > 0 && !visited[v->to])
        {
          q.push(v->to);
          visited[v->to] = true;
          pred[v->to] = { u, i };
        }
      }
    }

    if (!visited[sink]) return 0;

    int v = sink;
    int flow = adj[pred[v].first][pred[v].second]->capacity;
    while (pred[v].first != -1)
    {
      if (adj[pred[v].first][pred[v].second]->capacity < flow)
      {
        flow = adj[pred[v].first][pred[v].second]->capacity;
      }

      v = pred[v].first;
    }

    v = sink;
    while (pred[v].first != -1)
    {
      adj[pred[v].first][pred[v].second]->capacity -= flow;
      adj[pred[v].first][pred[v].second]->reverse->capacity += flow;

      v = pred[v].first;
    }

    return flow;
  }

  int flow()
  {
    int answer = 0;
    while (true)
    {
      int f = bfs();
      if (f == 0) break;

      answer += f;
    }

    return answer;
  }
};
