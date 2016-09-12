std::pair<int, std::vector<int>> min_cut(std::vector<std::vector<int>>& weights)
{
  int n = static_cast<int>(weights.size());
  
  std::vector<int> visited(n), cut, best_cut;
  
  int best_weight = -1;
  for (int i = n - 1; i >= 0; --i)
  {
    std::vector<int> weight = weights[0];
    std::vector<int> used = visited;
    
    int prev, last = 0;
    for (int j = 0; j < i; ++j)
    {
      prev = last;
      last = -1;
      
      for (int k = 1; k < n; ++k)
      {
        if (!used[k] && (last == -1 || weight[k] > weight[last]))
        {
          last = k;
        }
      }
      
      if (j == i - 1)
      {
        for (int k = 0; k < n; ++k) weights[prev][k] += weights[last][k];
        for (int k = 0; k < n; ++k) weights[j][prev] += weights[prev][j];
        
        visited[last] = true;
        cut.push_back(last);
        
        if (best_weight == -1 || best_weight > weight[last])
        {
          best_cut = cut;
          best_weight = weight[last];
        }
      }
      else
      {
        for (int k = 0; k < n; ++k) weight[k] += weights[last][k];
        
        used[last] = true;
      }
    }
  }
  
  return std::make_pair(best_weight, best_cut);
}
