// fast fourier transform
// usage: math::fft, math::multiply(a, b);
namespace math
{
  const double PI = std::acos(-1.0);
  
  typedef std::complex<double> complex_type;
  
  void fft(std::vector<complex_type>& a, int w = 1)
  {
    int n = static_cast<int>(a.size());
    for (int i = 1, j = 0; i < n; ++i)
    {
      int bit = n >> 1;
      for (; j >= bit; bit >>= 1) j-= bit;
      j += bit;
      
      if (i < j) std::swap(a[i], a[j]);
    }
    
    for (int l = 2; l <= n; l <<= 1)
    {
      double angle = 2 * w * PI / l;
      complex_type length(std::cos(angle), std::sin(angle));
      for (int i = 0; i < n; i += l)
      {
        complex_type omega(1);
        for (int j = 0; j < l / 2; ++j)
        {
          complex_type p = a[i + j], q = a[i + j + l / 2] * omega;
          
          a[i + j] = p + q;
          a[i + j + l / 2] = p - q;
          
          omega *= length;
        }
      }
    }
    
    if (w == -1)
    {
      for (int i = 0; i < n; ++i) a[i] /= n;
    }
  }
  
  std::vector<long long> multiply(std::vector<long long> const& a, std::vector<long long> const& b)
  {
    std::vector<complex_type> fa(std::begin(a), std::end(a)), fb(std::begin(b), std::end(b));
    
    int n = 1;
    while (std::max(a.size(), b.size()) > n) n <<= 1;
    n <<= 1;
    
    fa.resize(n), fb.resize(n);
  
    fft(fa), fft(fb);
    
    for (int i = 0; i < n; ++i) fa[i] *= fb[i];
    
    fft(fa, -1);
    
    std::vector<long long> answer(n);
    for (int i = 0; i < n; ++i) answer[i] = static_cast<long long>(fa[i].real() + 0.5);
    
    return answer;
  }
}
