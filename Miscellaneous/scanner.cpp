const int BUFFER_SIZE = 65536;
char buffer[BUFFER_SIZE];

struct scanner
{
  char* cursor;

  scanner()
  {
    fread(buffer, 1, sizeof(buffer), stdin);
    cursor = buffer;
  }
  
  void assign()
  {
    std::size_t n = buffer + BUFFER_SIZE - cursor;
    
    if (n < 100)
    {
      std::memcpy(buffer, cursor, n);
      fread(buffer + n, 1, BUFFER_SIZE - n, stdin);
      
      cursor = buffer;
    }
  }
  
  char read_char()
  {
    assign();
    while (*cursor <= ' ') ++cursor;
    
    return *(cursor++);
  }
  
  int read_int()
  {
    assign();
    while (*cursor <= ' ') ++cursor;
    
    bool is_negative = false;
    if (*cursor == '-') is_negative = true, ++cursor;
    
    int value = 0;
    while (*cursor > ' ') value = value * 10 + (*(cursor++) & 15);
    
    return (!is_negative) ? value : -value;
  }
};
