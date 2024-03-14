#define DIFF(elem_to_diff) DifferentiateNode(elem_to_diff, var)
#define COPY(elem_to_copy) CopyNode(elem_to_copy)
#define CREATE_NUM(num) CreateNodeWithType(NUM_TYPE, num)

#define LEFT node->left
#define RIGHT node->right
#define _SIN(_node) CreateNodeWithType(OPER_TYPE, SIN, _node)
#define _COS(_node) CreateNodeWithType(OPER_TYPE, COS, _node)
#define _LN(_node) CreateNodeWithType(OPER_TYPE, LN, _node)
#define _SH(_node) CreateNodeWithType(OPER_TYPE, SH, _node)
#define _CH(_node) CreateNodeWithType(OPER_TYPE, CH, _node)

OPER_DEF(MUL, '*', 
    new_node = _ADD(_MUL(DIFF(LEFT), COPY(RIGHT)), _MUL(COPY(LEFT), DIFF(RIGHT))),

    if(LEFT->value->type == OPER_TYPE && (LEFT->value->arg == '+' || LEFT->value->arg == '-'))
    {
        fprintf(tex, "(");
        fprintf(out, "(");
        PrintExpression(LEFT, tex, out);
        fprintf(out, ")*");
        fprintf(tex, ")*");
    }
    else if(LEFT->value->type == NUM_TYPE && LEFT->value->arg == -1)
    {
        fprintf(tex, "-");
        fprintf(out, "-");
    }
    else
    {
        PrintExpression(LEFT, tex, out);
        fprintf(out, "*");
        if(LEFT->value->type != NUM_TYPE)
            fprintf(tex, "*");
    }
    if(RIGHT->value->type == OPER_TYPE && (RIGHT->value->arg == '+' || RIGHT->value->arg == '-'))
    {
        fprintf(out, "(");
        fprintf(tex, "(");
        PrintExpression(RIGHT, tex, out);
        fprintf(out, ")");
        fprintf(tex, ")");
    }
    else
        PrintExpression(RIGHT, tex, out)
)

OPER_DEF(ADD, '+',
    new_node = _ADD(DIFF(LEFT), DIFF(RIGHT)),

    PrintExpression(LEFT, tex, out);
    fprintf(out, "+");
    fprintf(tex, "+");
    PrintExpression(RIGHT, tex, out)
)

OPER_DEF(SUB, '-',
    new_node = _SUB(DIFF(LEFT), DIFF(RIGHT)),

    PrintExpression(LEFT, tex, out);
    fprintf(out, "-");
    fprintf(tex, "-");
    PrintExpression(RIGHT, tex, out)
)

OPER_DEF(_DIV, '/',
    new_node = _DIV(_SUB (_MUL(DIFF(LEFT), COPY(RIGHT)), _MUL(COPY(LEFT), DIFF(RIGHT))), _MUL(COPY(RIGHT), COPY(RIGHT))),

    fprintf(tex, "\\frac{");
    if(LEFT->value->type != VAR_TYPE && LEFT->value->type != NUM_TYPE)
    {
        fprintf(out, "(");
        PrintExpression(LEFT, tex, out);
        fprintf(out, ")");
    }
    else
        PrintExpression(LEFT, tex, out);
    fprintf(tex, "}{");
    fprintf(out, "/");
    if(RIGHT->value->type != VAR_TYPE && RIGHT->value->type != NUM_TYPE)
    {
        fprintf(out, "(");
        PrintExpression(RIGHT, tex, out);
        fprintf(out, ")");
    }
    else
        PrintExpression(RIGHT, tex, out);
    fprintf(tex, "}")
)

OPER_DEF(POW, '^',
    if (RIGHT->value->type == NUM_TYPE)
        new_node = _MUL(_MUL(COPY(RIGHT), _POW(COPY(LEFT), _SUB(COPY(RIGHT), CREATE_NUM(1)))), DIFF(LEFT));
    else
    {
        Node* y = _POW(COPY(LEFT), COPY(RIGHT));
        new_node = _MUL(y, _ADD(_MUL(_LN(COPY(LEFT)), DIFF(RIGHT)), _MUL(DIFF(_LN(COPY(LEFT))), COPY(RIGHT))));
    },

    fprintf(tex, "{");
    if(LEFT->value->type == OPER_TYPE && (LEFT->value->arg == '*' || LEFT->value->arg == '+' || LEFT->value->arg == '-' || LEFT->value->arg == '/'))
    {
        fprintf(tex, "(");
        fprintf(out, "(");
        PrintExpression(LEFT, tex, out);
        fprintf(tex, ")");
        fprintf(out, ")");
    }
    else
        PrintExpression(LEFT, tex, out);
    fprintf(tex, "}^{");
    fprintf(out, "**");
    if(RIGHT->value->type == OPER_TYPE && (RIGHT->value->arg == '*' || RIGHT->value->arg == '+' || RIGHT->value->arg == '-' || RIGHT->value->arg == '/'))
    {
        fprintf(out, "(");
        PrintExpression(RIGHT, tex, out);
        fprintf(out, ")");
    }
    else
        PrintExpression(RIGHT, tex, out);
    fprintf(tex, "}")
)

OPER_DEF(COS, 'c',
    new_node = _MUL(_MUL(CREATE_NUM(-1), _SIN(COPY(LEFT))), DIFF(LEFT)),

    fprintf(tex, "\\cos(");
    fprintf(out, "cos(");
    PrintExpression(LEFT, tex, out);
    fprintf(out, ")");
    fprintf(tex, ")")
)
             
OPER_DEF(SIN, 's',
    new_node = _MUL(_COS(COPY(LEFT)), DIFF(LEFT)),

    fprintf(tex, "\\sin(");
    fprintf(out, "sin(");
    PrintExpression(LEFT, tex, out);
    fprintf(out, ")");
    fprintf(tex, ")")
)
             
OPER_DEF(LN,  'l',
    new_node = _MUL(_DIV(CREATE_NUM(1), COPY(LEFT)), DIFF(LEFT)),

    fprintf(tex, "\\ln(");
    fprintf(out, "log(");
    PrintExpression(LEFT, tex, out);
    fprintf(out, ")");
    fprintf(tex, ")")
)

OPER_DEF(CH, 'h',
    new_node = _MUL(_SH(COPY(LEFT)), DIFF(LEFT)),

    fprintf(tex, "\\cosh(");
    fprintf(out, "cosh(");
    PrintExpression(LEFT, tex, out);
    fprintf(out, ")");
    fprintf(tex, ")")
)
             
OPER_DEF(SH, 'w',
    new_node = _MUL(_CH(COPY(LEFT)), DIFF(LEFT)),

    fprintf(tex, "\\sinh(");
    fprintf(out, "sinh(");
    PrintExpression(LEFT, tex, out);
    fprintf(out, ")");
    fprintf(tex, ")")
)