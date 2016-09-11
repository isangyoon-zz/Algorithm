// a binary gap is any maximal sequence of consecutive zeros that is surrounded by ones at bothe ends in the binary.

// returns bianry gap.
std::size_t binary_gap(unsigned int N)
{
  std::size_t answer = 0;

  N |= (N - 1);
  for (std::size_t gap = 0; N != (N >> 1);)
  {
    N >>= 1;

    if (N & 1) answer = std::max(answer, gap), gap = 0;
    else ++gap;
  }

  return answer;
}
