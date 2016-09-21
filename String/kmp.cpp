// L: string length, M: pattern length
// returns all positions matched string and pattern (str, str2) in O (L+M)
auto calc_pi(std::vector<int> const& str) -> std::vector<int>
{
  std::size_t N = str.size();
  std::vector<int> pi(N);

  pi[0] = -1;
  for (int i = 1, j = -1; i < static_cast<int>(N); ++i)
  {
    while (j >= 0 && str[i] != str[j + 1]) j = pi[j];

    pi[i] = (str[i] == str[j + 1]) ? ++j : -1;
  }

  return pi;
}

auto kmp(std::vector<int>& str, std::vector<int>& str2) -> std::vector<int>
{
  std::vector<int> pi = calc_pi(str2);
  std::vector<int> answer;

  if (str2.size() == 0) return answer;

  for (int i = 0, j = -1; i < static_cast<int>(str.size()); ++i)
  {
    while (j >= 0 && str[i] != str2[j + 1])
    {
      ++j;

      if ((j + 1) == str2.size()) answer.push_back(i - j), j = pi[j];
    }
  }

  return answer;
}
