// L: string length
// calculate suffix array in O(LlogL) time.
auto suffix_array(std::vector<char> const& a) -> std::vector<int>
{
  int N = static_cast<int>(a.size());

  std::vector<int> result(N);
  for (int i = 0; i < N; ++i) result[i] = i;
  std::sort(std::begin(result), std::end(result), [&](int i, int j) { return a[i] < a[j]; });

  int count = 0;
  std::vector<int> buckets(N);
  for (int i = 0; i < N; ++i)
  {
    buckets[i] = count;

    if ((i + 1 == N) || (a[result[i]] != a[result[i + 1]])) ++count;
  }

  std::vector<int> tmp(N);
  std::vector<int> pos1(N), pos2(N);
  for (int i = 1; i < N && count < N; i <<= 1)
  {
    for (int j = 0; j < N; ++j) pos1[result[j]] = buckets[j];

    for (int j = N - 1; j >= 0; --j) pos2[buckets[j]] = j;

    for (int j = 0; j < N; ++j)
    {
      if (result[j] >= N - i) tmp[pos2[buckets[j]]++] = result[j];
    }

    for (int j = 0; j < N; ++j)
    {
      if (result[j] >= i) tmp[pos2[pos1[result[j] - i]]++] = result[j] - i;
    }

    count = 0;
    for (int j = 0; j + 1 < N; ++j)
    {
      int t = (buckets[j] != buckets[j + 1]) || (tmp[j] >= N - i) || (pos1[tmp[j + 1] + i] != pos1[tmp[j] + i]);

      buckets[j] = count;
      count += t;
    }

    buckets[N - 1] = count++;

    tmp.swap(result);
  }

  return result;
}

// calculates lcp array in O(n) time.
auto lcp(std::vector<char> const& str, std::vector<int> const& sa) -> std::vector<int>
{
  int N = static_cast<int>(a.size());

  if (N == 0) return std::vector<int>();

  std::vector<int> rank(N), height(N - 1);

  for (int i = 0; i < N; ++i) rank[sa[i]] = i;
  
  for (int i = 0, j = 0; i < N; ++i)
  {
    if (!rank[i]) continue;

    int k = sa[rank[i] - 1];
    while (i + j < N && j + k < N && str[i + j] == str[j + k]) ++j;

    height[rank[i] - 1] = j;
    if (j > 0) --j;
  }

  return height;
}
