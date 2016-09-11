// int adj[MAX_N + 1][MAX_N + 1];
// int via[MAX_N + 1][MAX_N + 1];
void floyd()
{
  for (auto k = 1; k <= N; ++k)
  {
    for (auto i = 1; i <= N; ++i)
    {
      for (auto j = 1; j <= N; ++j)
      {
        // compute distance
        if (adj[i][j] > adj[i][k] + adj[k][j]) adj[i][j] = adj[i][k] + adj[k][j];

        via[i][j] = k;

        // check reachable
        adj[i][j] |= adj[i][k] && adj[k][j];
			}
		}
	}
}

void reconstruct(int u, int v, std::vector<int>& paths)
{
  if (via[u][v] == -1)
  {
    paths.push_back(u);
    if (u != v) paths.push_back(v);
  }
  else
  {
    int w = via[u][v];

    reconstruct(u, w, paths);
    paths.pop_back();
    reconstruct(w, v, paths);
  }
}
