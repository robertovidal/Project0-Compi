token next_token(void);

void error(void);

void match(token tok, times again);

void system_goal(void);

void program(void);

void statement_list(void);

void statement(void);

void id_list(void);

void expression(expr_rec *result, bool skip);

void expr_list(void);

void add_op(op_rec *result);

void primary(expr_rec *result);

token current_token;

token next_tok;

void start(void);

void finish(void);

void assign(expr_rec target, expr_rec source);

op_rec process_op(void);

expr_rec gen_infix(expr_rec e1, op_rec op, expr_rec e2);

void read_id(expr_rec in_var);

expr_rec process_id(void);

expr_rec process_literal(void);

void write_expr(expr_rec out_expr);
