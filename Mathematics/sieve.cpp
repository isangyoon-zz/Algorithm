// find prime numbers in 1 ~ N(size) using Eratosthenes
// O(N * log(log N))
auto sieve_of_eratosthenes(std::size_t const size) -> std::vector<bool>
{
  std::vector<bool> primes(size + 1, true);
  
  primes[0] = primes[1] = false;
  for (auto p = 2; p * p <= size; ++p)
  {
    if (primes[p] == true)
    {
      for (auto i = p * 2; i <= size; i += p)
      {
        primes[i] = false;
      }
    }
  }
  
  return primes;
}

// find prime numbers in 1 ~ N(size) using Atkin
// O(N / (log(log N)))
auto sieve_of_atkin(std::size_t const size) -> std::vector<bool>
{
  std::vector<bool> primes(size + 1, true);
  
  primes[0] = primes[1] = false;
  for (auto p = 2; p <= size; ++p)
  {
    if (!primes[p]) continue;
    
    int n = 2;
    int multiply = p * n;
    while (multiply <= size)
    {
      primes[multiply] = false;
      
      ++n;
      multiply = p * n;
    }
  }
  
  return primes;
}
