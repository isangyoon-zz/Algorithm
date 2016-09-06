// calculate greatest commond divisors
long long gcd(long long a, long long b)
{
  return (b == 0) ? a : gcd(b, a % b);
}

// find a pair {c, d} s.t a * c + b * d = gcd(a, b)
std::pair<long long, long long> extended_gcd(long long a, long long b)
{
  if (b == 0) return {1, 0};
  
  auto gcd = extended_gcd(b, a % b);
  return {gcd.second, gcd.first - gcd.second * (a / b)};
}

// find x in [0, m) s.t. a * x === gcd(a, m) (mod m)
long long mod_inverse(long long a, long long mod)
{
  return (extended_gcd(a, mod).first % mod + mod) % mod;
}

// calculate number of divisors in [1, N]
// O(N * log N)
auto number_of_divisors(std::size_t const size) -> std::vector<int>
{
  std::vector<int> divisors(size + 1);
  
  for (auto i = 1; i <= size; ++i)
  {
    for (auto j = i; j <= size; j += i)
    {
      divisors[j] += 1;
    }
  }
  
  return divisors;
}

// calculate sum of divisors in [1, N]
// O(N * log N)
auto sum_of_divisors(std::size_t const size) -> std::vector<int>
{
  std::vector<int> divisors(size + 1);
  
  for (auto i = 1; i <= size; ++i)
  {
    for (auto j = i; j <= size; j += i)
    {
      divisors[j] += i;
    }
  }
  
  return divisors;
}

// calcuate euler's phi function in [1, N]
// phi(N) = number of integers k s.t. [0, N] for which the gcd(N, k) = 1
// O(N * log(log N))
auto totient(std::size_t const size) -> std::vector<int>
{
  std::vector<int> phi(size + 1, 0);
  
  for (auto i = 1; i <= size; ++i)
  {
    phi[i] = i;
  }
  
  for (auto i = 2; i <= size; ++i)
  {
    if (phi[i] == i)
    {
      for (auto j = i; j <= size; j += i)
      {
        phi[j] -= (phi[j] / i);
      }
    }
  }
  
  return phi;
}