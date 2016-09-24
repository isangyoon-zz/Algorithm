// find longest increasing subsequence(LIS) size in O(N*logN) time.
std::size_t lis() // But it spend more times.
{
  std::multiset<int> answer;
  for (int i = 0; i < N; ++i)
  {
    answer.insert(A[i]);
    
    auto it = std::upper_bound(std::begin(answer), std::end(answer), A[i]);
    if (it != std::end(answer)) answer.erase(it);
  }
  
  return answer.size();
}

std::size_t lis() // Good! very nice!! i love this solution.
{
  std::vector<int> answer(1, A[0]);
  
  for (int i = 0; i < N; ++i)
  {
    if (A[i] > answer.back()) answer.push_back(A[i]);
    else *std::lower_bound(std::begin(answer), std::end(answer), A[i]) = A[i];
  }
  
  return answer.size();
}
