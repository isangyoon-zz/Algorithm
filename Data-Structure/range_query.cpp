// result: range_minimum_query, range_maximum_query in [left, right]
class range_query
{
private:
  typedef int value_type;
  typedef std::size_t size_type;

public:
  explicit range_query(std::vector<value_type> const& data)
  {
    _n = data.size();
    _minimum.resize(_n * 4);
    _maximum.resize(_n * 4);

    initialize(data, 1, 0, _n - 1);
  }

  std::pair<value_type, value_type> query(int node, int start, int end, int left, int right)
  {
    if (left > end || right < start) return std::make_pair(-1, -1);
    if (left <= start && end <= right) return std::make_pair(_minimum[node], _maximum[node]);

    auto q1 = query(node * 2, start, (start + end) / 2, left, right); // std::pair<value_type, value_type>
    auto q2 = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right); // std::pair<value_type, value_type>

    if (q1 == std::make_pair(-1, -1)) return q2;
    else if (q2 == std::make_pair(-1, -1)) return q1;
    else return std::make_pair(std::min(std::max(0, q1.first), std::max(0, q2.first)), std::max(std::max(0, q1.second), std::max(0, q2.second)));
  }

  std::pair<value_type, value_type> query(int left, int right)
  {
    return query(1, 0, _n - 1, left - 1, right - 1);
  }

private:
  void initialize(std::vector<value_type> const& data, int node, int start, int end)
  {
    if (start == end) _maximum[node] = _minimum[node] = data[start];
    else
    {
      initialize(data, node * 2, start, (start + end) / 2);
      initialize(data, node * 2 + 1, (start + end) / 2 + 1, end);

      _minimum[node] = std::min(_minimum[node * 2], _minimum[node * 2 + 1]);
      _maximum[node] = std::max(_maximum[node * 2], _maximum[node * 2 + 1]);
    }
  }

private:
  size_type _n;
  std::vector<value_type> _minimum;
  std::vector<value_type> _maximum;
};
