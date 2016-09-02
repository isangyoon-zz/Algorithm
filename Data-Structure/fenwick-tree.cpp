template <typename T>
class fenwick_tree
{
public:
  fenwick_tree(std::size_t n = 100000) : _n(n) { _tree.assign(_n + 1, 0); }
  fenwick_tree(std::vector<auto> const& tree) : _n(tree.size()), _tree(tree) {}

  value_type query(int p)
  {
    value_type result = 0;
    for (; p > 0; p -= p & -p) result += _tree[p];

    return result;
  }

  void update(int p, value_type value)
  {
    for (; p <= _n; p += p & -p) _tree[p] += value;
  }

  size_type size const noexcept{ return _n; }

private:
  typedef typename T value_type;
  typedef typename std::size_t size_type;

  std::vector<value_type> _tree;
  std::size_t _n;
};