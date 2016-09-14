class range_minimum_query
{
private:
  typedef int value_type;
  typedef std::size_t size_type;

public:
  explicit range_minimum_query(std::vector<value_type> const& data)
  {
    _n = data.size();
    _minimum.resize(_n * 4);

    initialize(data, 1, 0, _n - 1);
  }

  value_type query(int node, int start, int end, int left, int right)
  {
    if (left > end || right < start) return -1;
    if (left <= start && end <= right) return _minimum[node];

    int q1 = query(node * 2, start, (start + end) / 2, left, right);
    int q2 = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);

    if (q1 == -1) return q2;
    else if (q2 == -1) return q1;
    else return std::min(q1, q2);
  }

  value_type query(int left, int right)
  {
    return query(1, 0, _n - 1, left - 1, right - 1);
  }

  value_type update(int index, int value, int node, int left, int right)
  {
    if (left > index || index > right) return _minimum[node];
    if (left == right) return _minimum[node] = value;

    return _minimum[node] = std::min(update(index, value, node * 2, left, (left + right) / 2), update(index, value, node * 2 + 1, (left + right) / 2 + 1, right));
  }

  value_type update(int index, int value)
  {
    return update(index - 1, value, 1, 0, _n - 1);
  }

private:
  void initialize(std::vector<value_type> const& data, int node, int start, int end)
  {
    if (start == end) _minimum[node] = data[start];
    else
    {
      initialize(data, node * 2, start, (start + end) / 2);
      initialize(data, node * 2 + 1, (start + end) / 2 + 1, end);

      _minimum[node] = std::min(_minimum[node * 2], _minimum[node * 2 + 1]);
    }
  }

private:
  size_type _n;
  std::vector<value_type> _minimum;
};
