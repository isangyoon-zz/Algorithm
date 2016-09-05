// find k s.t. k === a[0] (mod m[0]), k === a[1] (mod m[1]) ...
long long chinese_remainder_theorem(long long* a, long long* m, std::size_t size)
{
  if (size == 1) return *a;
  
  long long inv = mod_inverse(m[0], m[1]);
  long long t = (inv * (a[1] - a[0]) % m[1] + m[1]) % m[1];
  
  long long o = a[1];
  
  long long g = gcd(m[0], m[1]);
  a[1] = a[0] + m[0] / g * t;
  m[1] *= m[0] / g;
  
  long long result = chinese_remainder_theorem(a + 1, m + 1, size - 1);
  m[1] /= m[0] / g;
  a[1] = o;
  
  return result;
}