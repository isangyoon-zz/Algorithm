// given non-negative integers N, K, generate all size N combinations of the integers [0, N-1] in sorted order
auto combination(int const N, int const K)
{
  std::vector<std::vector<int>> result;

  std::string mask(K, 1);
  mask.resize(N, 0);

  do
  {
    std::vector<int> c;
    for (auto i = 0; i < N; ++i)
    {
      if (mask[i]) c.push_back(i);
    }

    result.push_back(c);
  } while (std::prev_permutation(std::begin(mask), std::end(mask)));

  return result;
}