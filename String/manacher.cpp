// L: string length
// find longest palindromic span for each element in given string in O(L) time.
std::string manacher_preprocess(std::string s)
{
  int n = s.length();
  if (n == 0) return "^$";

  std::string t = "^";
  for (int i = 0; i < n; i++) t += "#" + s.substr(i, 1);
  t += "#$";

  return t;
}

// returns longest palindromic str, length: manacher(s).length()
std::string manacher(std::string s)
{
  std::string t = manacher_preprocess(s);
  int n = t.length();
  std::vector<int> P(n, 0);
  int c = 0, r = 0;
  
  for (int i = 1; i < n - 1; i++)
  {
    int m = 2 * c - i;
    P[i] = (r > i) ? std::min(r - i, P[m]) : 0;

    while (t[i + 1 + P[i]] == t[i - 1 - P[i]]) P[i]++;

    if (i + P[i] > r) c = i, r = i + P[i];
  }

  int radius = 0;
  int center = 0;
  for (int i = 1; i < n - 1; ++i)
  {
    if (P[i] > radius) radius = P[i], center = i;
  }

  return s.substr((center - 1 - radius) / 2, radius);
}
