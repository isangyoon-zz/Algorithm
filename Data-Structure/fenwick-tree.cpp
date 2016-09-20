// Fenwick Tree (BIT) using STL vector

template <typename T>
class fenwick_tree
{
private:
  typedef std::size_t size_type;
  typedef T value_type;
  
public:
  fenwick_tree(size_type size = 0) : _size(size), _tree(std::vector<value_type>(size)) {}
  fenwick_tree(std::vector<value_type> const& tree) : _size(tree.size()), _tree(tree) {}
  
  void assign(size_type size, value_type default_value = 0)
  {
    _size = size;
    _tree.assign(size, default_value);
  }
  
  void resize(size_type size, value_type default_value = 0)
  {
    _size = size;
    _tree.resize(size, default_value);
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
