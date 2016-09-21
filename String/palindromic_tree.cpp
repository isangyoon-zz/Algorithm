class palindromic_tree
{
private:
  static const int ALPHABET = 4;

protected:
  struct node
  {
    node* next[ALPHABET];
    node* link;
    node* half_link;

    int length;
    int full;
    int half;
    int count;

    node() : count(0), full(0), half(0) { std::memset(next, 0, sizeof(next)); }
  };

private:
  typedef node node_type;
  typedef node_type* pointer_type;
  typedef int key_type;

public:
  explicit palindromic_tree(std::string s)
  {
    _s = s;

    int n = s.length();
    std::memset(_T, 0, sizeof(_T[0]) * (n + 5));

    last = &_T[1];

    _T[0].length = -1;
    _T[1].length = 0;

    _T[0].link = _T[1].link = &_T[0];

    index = 2;
    n = -1;
  }

  key_type get_key(char c) const
  {
    switch (c)
    {
      case 'A': return 0;
      case 'C': return 1;
      case 'G': return 2;
      case 'T': return 3;

      default: return -1;
    }

    // return c - 'a';
  }

  pointer_type get_link(pointer_type p)
  {
    while (n - p->length - 1 < 0 || _s[n] != _s[n - p->length - 1]) p = p->link;

    return p;
  }

  bool append(int p, int& result)
  {
    int key = get_key(_s[p]);
    _s[++n] = _s[p];

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
      node* t = cursor->half_link;
      while (n - t->length - 1 < 0 || _s[n] != _s[n - t->length - 1] || (t->length + 2) * 2 > last->length) t = t->link;
      
      last->half_link = t->next[key];
    }

    if (last->length & 1) last->full = last->length;
    else
    {
      last->half = std::min(cursor->half + 1, last->half_link->full + last->length / 2 - last->half_link->length);
      last->full = std::min(cursor->full + 2, last->half + 1);
      last->full = std::min(last->full, last->link->full + last->length - last->link->length);

      result = std::min(result, last->full + static_cast<int>(_s.length()) - last->length);
    }

    return true;
  }

private:
  std::string _s;

  node_type _T[100005];
  pointer_type last;

  int index;
  int n;
};
