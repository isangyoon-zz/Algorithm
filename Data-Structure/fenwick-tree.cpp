// Fenwick Tree (BIT) using STL vector
// usage: fenwick_tree::query(index), fenwick_tree::update(index, diff)
namespace fenwick_tree
{
  const int SIZE = 100000;
  int tree[SIZE + 1];
  
  int query(int p)
  {
    int answer = 0;
    for (; p > 0; p -= p & -p) answer += tree[p];
    
    return answer;
  }
  
  void update(int p, int value) { for (; p <= SIZE; p += p & -p) tree[p] += value; }
}

// usage: fenwick_tree<int> bit(size), bit.query(index), bit.update(index, diff)
template <typename T>
class fenwick_tree
{
private:
  typedef std::size_t size_type;
  typedef T value_type;
  
public:
  fenwick_tree(size_type size = 0) : _size(size + 1), _tree(std::vector<value_type>(size + 1)) {}
  fenwick_tree(std::vector<value_type> const& tree) : _size(tree.size()), _tree(tree) {}
  
  void assign(size_type size, value_type default_value = 0)
  {
    _size = size + 1;
    _tree.assign(size + 1, default_value);
  }
  
  void resize(size_type size, value_type default_value = 0)
  {
    _size = size + 1;
    _tree.resize(size + 1, default_value);
  }
  
  void update(int p, value_type value)
  {
    for(; p < _size; p += (p & (-p))) _tree[p] += value;
  }
  
  value_type query(int p)
  {
    value_type result = 0;
    for (; p; p -= (p & (-p))) result += _tree[p];
    
    return result;
  }
  
  size_type size() const noexcept { return _size; }
  
private:
  size_type _size;
  std::vector<value_type> _tree;
};
