#define MAXIDLEN 33
typedef char string[MAXIDLEN];

extern int lookup(string s);

extern void enter(string s);

void generate(string op_code, string a, string b, string r);

char * extract_op(op_rec op);

char * extract_expr(expr_rec expr);

int lookup(string s);

void enter(string s);

void check_id(string s);

char *get_register(void);

char *get_temp(void);

void start(void);

void finish(void);

void assign(expr_rec target, expr_rec source);

op_rec process_op(void);

expr_rec gen_infix(expr_rec e1, op_rec op, expr_rec e2);

void read_id(expr_rec in_var);

expr_rec process_id(void);

expr_rec process_literal(void);

void write_expr(expr_rec out_expr);
