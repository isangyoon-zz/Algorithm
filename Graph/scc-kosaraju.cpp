// find Strongly Connected Components in givien graph

// const int SIZE = 101;
// std::vector<int> adj[SIZE];
// std::vector<int> pred[SIZE];
int visited[SIZE];
int indices[SIZE];
int v_count, scc_count;
std::vector<int> components;

void dfs(int u, std::vector<int> const adj[])
{
  visited[u] = v_count;

  for (auto const v : adj[u])
  {
    if (visited[v] == v_count) continue;
    dfs(v, adj);
  }

  components.push_back(u);
}

void scc(std::size_t n)
{
  scc_count = 0;
  v_count = 0;

  components.clear();
  std::fill(std::begin(visited), std::end(visited), 0);

  for (auto i = 0; i < n; ++i)
  {
    if (visited[i] == v_count) continue;
    dfs(i, adj);
  }

  ++v_count;

  for (auto u : std::vector<int>(components.rbegin(), components.rend()))
  {
    if (visited[u] == v_count) continue;
    components.clear();

    dfs(u, pred);

    ++scc_count;
    for (auto v : components)
    {
      indices[v] = scc_count;
    }
  }
}