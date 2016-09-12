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
  
  auto paths() { return _paths.back(); }
  
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

