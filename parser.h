token next_token(void);

void error(void);

void match(token tok);

void system_goal(void);

void program(void);

void statement_list(void);

void statement(void);

void id_list(void);

void expression(void);

void expr_list(void);

void add_op(void);

void cond_op(void);

void primary(void);

token current_token;

token next_tok;