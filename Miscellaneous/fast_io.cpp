namespace io
{
  const int BUFFER_SIZE = 524288;
  char buffer[BUFFER_SIZE];
  int size = BUFFER_SIZE;

  inline char read_char()
  {
    if (size == BUFFER_SIZE)
    {
      fread(buffer, 1, BUFFER_SIZE, stdin);

      size = 0;
    }

    return buffer[size++];
  }

  int read_int()
  {
    char c = read_char();
    while ((c < '0' || c > '9') && c != '-') c = read_char();

    bool is_negative = (c == '-');
    int value = 0;

    if (is_negative) c = read_char();
    while ((c >= '0') && (c <= '9')) value = (value * 10 + c - '0'), c = read_char();

    return (is_negative) ? -value : value;
  }
}