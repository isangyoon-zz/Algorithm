// given a set, the power set is the set of all subsets of set
template <typename Set>
auto powerset(Set const& set)
{
  std::set<Set> result;
  result.emplace();

  for (auto&& element : set)
  {
    std::set<Set> sub;
    for (auto x : result)
    {
      x.insert(element);
      sub.insert(x);
    }

    result.insert(std::begin(sub), std::end(sub));
  }

  return result;
}
