/* find Euler Path */
// check, connected graph and number of odd vertices.
// if directed graph, change _edge to int and add_edge method.
class euler_path
{
public:
  euler_path() {}
  
  void add_edge(int u, int v)
  {
    _adj[u].push_front(_edge(v));
    _adj[v].push_front(_edge(u));
    
    auto forward = std::begin(_adj[u]);
    auto backward = std::begin(_adj[v]);
    
    forward->_reverse = backward;
    backward->_reverse = forward;
  }
  
  void find_path(int u)
  {
    while (_adj[u].size() > 0)
    {
      int v = _adj[u].front()._to;
      
      _adj[v].erase(_adj[u].front()._reverse);
      _adj[u].pop_front();
      
      find_path(v);
    }
    
    _paths.push_back(u);
  }
  
  std::vector<int> paths() { return _paths; }
  
protected:
  struct _edge
  {
    int _to;
    std::list<_edge>::iterator _reverse;
    
    _edge(int to) : _to(to) {}
  };
  
private:
  std::list<_edge> _adj[100001];
  std::vector<int> _paths;
};

/*
int main(int const argc, char const** argv)
{
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  
  euler_path euler;
  
  euler.add_edge(1, 2);
  euler.add_edge(2, 3);
  euler.add_edge(3, 4);
  euler.add_edge(4, 1);
  euler.add_edge(1, 3);
  
  euler.find_path(1);
  
  auto paths = euler.paths();
  
  // expected 3 2 1 4 3 1
  std::copy(std::begin(paths), std::end(paths), std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";
  
  return 0;
}
*/
