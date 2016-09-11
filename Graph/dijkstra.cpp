/*
dijkstra's shortest path algorithm using priority queue
Time Complexity: O(|E|*(log|V|)

via: reconstructs shortest path.
distance: shortest distance from source to destination.
*/
const long long INF = 9223372036854775807;

void dijkstra(std::vector<std::vector<std::pair<int, int>>>& adj, int src, int dst)
{
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

  std::size_t N = adj.size();
  std::vector<long long> distance(N, INF);
  std::vector<long long> via(N, 0LL);

  pq.push({ 0, src }); // or pq.push(std::make_pair(0, src));
  distance[src] = 0LL;

  while (!pq.empty())
  {
    auto u = pq.top(); // std::pair<int, int>
    pq.pop();

    if (u.second == dst) break;
    if (distance[u.second] != u.first) continue;

    for (auto v : adj[u.second])
    {
      if (distance[v.second] > distance[u.second] + v.first)
      {
        via[v.second] = u.second;
        pq.push({(distance[v.second] = distance[u.second] + v.first), v.second});
      }
    }
  }

  /* reconstruct or print distance */
}
