/*
suffix array
construction in O(L*log^2(L))
compute the length of the longest common prefix(LCP) in O(log(L))
*/
class suffix_array
{
public:
  suffix_array(std::string const& string) : _size(string.length()), _string(string), _P(1, std::vector<int>(_size, 0)), _M(_size)
  {
    for (unsigned int i = 0; i < _size; ++i) _P[0][i] = static_cast<int>(_string[i]);

    for (unsigned int j = 1, k = 1; j < _size; j *= 2, ++k)
    {
      _P.push_back(std::vector<int>(_size, 0));

      for (unsigned int i = 0; i < _size; ++i) _M[i] = std::make_pair(std::make_pair(_P[k - 1][i], (i + j < _size) ? _P[k - 1][i + j] : -1000), i);

      std::sort(std::begin(_M), std::end(_M)); // std::sort(_M.begin(), _M.end());

      for (unsigned int i = 0; i < _size; ++i) _P[k][_M[i].second] = (i > 0 && _M[i].first == _M[i - 1].first) ? _P[k][_M[i - 1].second] : i;
    }
  }

  std::vector<int> get() { return _P.back(); }

  std::size_t longest_common_prefix(int i, int j)
  {
    std::size_t length = 0;

    if (i == j) return _size - i;

    for (int k = _P.size() - 1; k >= 0 && i < _size && j < _size; --k)
    {
      if (_P[k][i] == _P[k][j])
      {
        i += (1 << k);
        j += (1 << k);

        length += (1 << k);
      }
    }

    return length;
  }

private:
  std::size_t _size;
  std::string _string;

  std::vector<std::vector<int>> _P;
  std::vector<std::pair<std::pair<int, int>, int>> _M;
};

/*
int main(int const argc, char const** argv)
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  suffix_array suffix("bobbuger");
  std::vector<int> arr = suffix.get();

  // expected: 1 5 0 2 7 4 3 6 and 1
  std::copy(std::begin(arr), std::end(arr), std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";

  std::cout << suffix.longest_common_prefix(0, 2) << "\n";


  return 0;
}
*/
