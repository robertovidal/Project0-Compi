void clear_buffer(void);

void buffer_char(char c);

token check_reserved(void);

void lexical_error(char c);

token scanner();

token storeLiteral(char c);

char getChar();