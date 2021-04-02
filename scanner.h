void clear_buffer(void);

void buffer_char(char c);

token check_reserved(void);

void lexical_error(char c);

token scanner(times again);

void return_chars(int count);
