class palindromic_tree
{
private:
  static const int MAX = 100005;
  static const int ALPHABET = 26;

protected:
  struct _node
  {
    _node* next[ALPHABET];
    _node* link;
    _node* half_link;

    int length;
    int full;
    int half;
    int count;

    _node() : count(0), full(0), half(0) { std::memset(next, 0, sizeof(next)); }
  };

private:
  typedef _node node_type;
  typedef node_type* pointer_type;
  typedef int key_type;

public:
  explicit palindromic_tree(std::string s)
  {
    _s = s;

    int n = static_cast<int>(s.length());
    std::memset(_T, 0, sizeof(_T[0]) * (n + 5));

    last = &_T[1];

    _T[0].length = -1;
    _T[1].length = 0;

    _T[0].link = _T[1].link = &_T[0];

    index = 2;
    node = -1;
  }

  key_type get_key(char c) const { return c - 'a'; }

  pointer_type get_link(pointer_type p)
  {
    while (node - p->length - 1 < 0 || _s[node] != _s[node - p->length - 1]) p = p->link;

    return p;
  }

  bool append(int p)
  {
    int key = get_key(_s[p]);
    _s[++node] = _s[p];

    pointer_type cursor = get_link(last);
    if (cursor->next[key])
    {
      last = cursor->next[key];

      return false;
    }

    last = &_T[index++];
    last->length = cursor->length + 2;

    cursor->next[key] = last;

    if (last->length == 1)
    {
      last->link = last->half_link = &_T[1];
      last->full = 1;

      return true;
    }

    last->link = get_link(cursor->link)->next[key];

    if (last->length <= 2) last->half_link = last->link;
    else
    {
      _node* t = cursor->half_link;
      while (node - t->length - 1 < 0 || _s[node] != _s[node - t->length - 1] || (t->length + 2) * 2 > last->length) t = t->link;

      last->half_link = t->next[key];
    }

    if (last->length & 1) last->full = last->length;
    else
    {
      last->half = std::min(cursor->half + 1, last->half_link->full + last->length / 2 - last->half_link->length);
      last->full = std::min(cursor->full + 2, last->half + 1);
      last->full = std::min(last->full, last->link->full + last->length - last->link->length);
    }

    return true;
  }

private:
  std::string _s;

  node_type _T[100005];
  pointer_type last;

  int index;
  int node;
};
