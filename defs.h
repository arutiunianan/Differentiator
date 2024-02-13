#define DIFF(elem_to_diff) DifferentiateNode(elem_to_diff, var)
#define COPY(elem_to_copy) CopyNode( elem_to_copy)
#define CREATE_NUM(num) CreateNodeWithType( NUM_TYPE, num )

#define LEFT node->left
#define RIGHT node->right
//#define _ADD(left_node, right_node) CreateNodeWithType( OPER_TYPE, ADD, left_node, right_node)
//#define _SUB(left_node, right_node) CreateNodeWithType( OPER_TYPE, SUB, left_node, right_node)
//#define _MUL(left_node, right_node) CreateNodeWithType( OPER_TYPE, MUL, left_node, right_node)
//#define _DIV(left_node, right_node) CreateNodeWithType( OPER_TYPE, DIV, left_node, right_node)
//#define _POW(left_node, right_node) CreateNodeWithType( OPER_TYPE, POW, left_node, right_node)
#define _SIN(_node) CreateNodeWithType( OPER_TYPE, SIN, _node)
#define _COS(_node) CreateNodeWithType( OPER_TYPE, COS, _node)
#define _LN(_node) CreateNodeWithType( OPER_TYPE, LN, _node)
#define _SH(_node) CreateNodeWithType( OPER_TYPE, SH, _node)
#define _CH(_node) CreateNodeWithType( OPER_TYPE, CH, _node)

OPER_DEF(MUL, '*',
    new_node = _ADD( _MUL( DIFF(LEFT), COPY(RIGHT) ), _MUL( COPY(LEFT), DIFF(RIGHT) ) ),

    if( node->left->value->type == OPER_TYPE && ( node->left->value->arg == '+' || node->left->value->arg == '-' ) )
    {
        fprintf( log, "(" );
        fprintf( out, "(" );
        PrintExpression( node->left, log, out );
        fprintf( out, ")*" );
        fprintf( log, ")*" );
    }
    else if( node->left->value->type == NUM_TYPE && node->left->value->arg == -1 )
    {
        //if()
        fprintf( log, "-" );
        fprintf( out, "-" );
    }
    else
    {
        PrintExpression( node->left, log, out );
        fprintf( out, "*" );
        if( node->left->value->type != NUM_TYPE )
            fprintf( log, "*" );
    }
    if( node->right->value->type == OPER_TYPE && ( node->right->value->arg == '+' || node->right->value->arg == '-' ) )
    {
        fprintf( out, "(" );
        fprintf( log, "(" );
        PrintExpression( node->right, log, out );
        fprintf( out, ")" );
        fprintf( log, ")" );
    }
    else
        PrintExpression( node->right, log, out )
)

OPER_DEF(ADD, '+',
    new_node = _ADD( DIFF( LEFT ), DIFF( RIGHT ) ),

    PrintExpression( node->left, log, out );
    fprintf( out, "+" );
    fprintf( log, "+" );
    PrintExpression( node->right, log, out )
)

OPER_DEF(SUB, '-',
    new_node = _SUB( DIFF( LEFT ), DIFF( RIGHT ) ),

    PrintExpression( node->left, log, out );
    fprintf( out, "-" );
    fprintf( log, "-" );
    PrintExpression( node->right, log, out )
)

OPER_DEF(_DIV, '/',
    new_node = _DIV( _SUB ( _MUL( DIFF( LEFT ), COPY( RIGHT ) ), _MUL( COPY( LEFT ), DIFF( RIGHT ) ) ), _MUL( COPY( RIGHT ), COPY( RIGHT ) ) ),

    fprintf( log, "\\frac{" );
    if( node->left->value->type != VAR_TYPE && node->left->value->type != NUM_TYPE )
    {
        fprintf( out, "(" );
        PrintExpression( node->left, log, out );
        fprintf( out, ")" );
    }
    else
        PrintExpression( node->left, log, out );
    fprintf( log, "}{" );
    fprintf( out, "/" );
    if( node->right->value->type != VAR_TYPE && node->right->value->type != NUM_TYPE )
    {
        fprintf( out, "(" );
        PrintExpression( node->right, log, out );
        fprintf( out, ")" );
    }
    else
        PrintExpression( node->right, log, out );
    fprintf( log, "}" )
)

OPER_DEF(POW, '^',
	if ( RIGHT->value->type == NUM_TYPE )
		new_node = _MUL(_MUL(COPY(RIGHT), _POW(COPY(LEFT), _SUB(COPY(RIGHT), CREATE_NUM(1)))), DIFF(LEFT));
	else
    {
        Node* y = _POW(COPY(LEFT), COPY(RIGHT));
		new_node = _MUL(y, _ADD(_MUL(_LN(COPY(LEFT)), DIFF(RIGHT)), _MUL(DIFF(_LN(COPY(LEFT))), COPY(RIGHT))));
    },

    fprintf( log, "{" );
    if( node->left->value->type == OPER_TYPE && ( node->left->value->arg == '*' || node->left->value->arg == '+' || node->left->value->arg == '-' || node->left->value->arg == '/' ) )
    {
        fprintf( log, "(" );
        fprintf( out, "(" );
        PrintExpression( node->left, log, out );
        fprintf( log, ")" );
        fprintf( out, ")" );
    }
    else
        PrintExpression( node->left, log, out );
    fprintf( log, "}^{" );
    fprintf( out, "**" );
    if( node->right->value->type == OPER_TYPE && ( node->right->value->arg == '*' || node->right->value->arg == '+' || node->right->value->arg == '-' || node->right->value->arg == '/' ) )
    {
        fprintf( out, "(" );
        PrintExpression( node->right, log, out );
        fprintf( out, ")" );
    }
    else
        PrintExpression( node->right, log, out );
    fprintf( log, "}" )
)

OPER_DEF(COS, 'c',
	new_node = _MUL(_MUL(CREATE_NUM( -1 ), _SIN(COPY(LEFT)) ), DIFF(LEFT)),

    fprintf( log, "\\cos(" );
    fprintf( out, "cos(" );
    PrintExpression( node->left, log, out );
    fprintf( out, ")" );
    fprintf( log, ")" )
)
             
OPER_DEF(SIN, 's',
	new_node = _MUL(_COS(COPY(LEFT)), DIFF(LEFT)),

    fprintf( log, "\\sin(" );
    fprintf( out, "sin(" );
    PrintExpression( node->left, log, out );
    fprintf( out, ")" );
    fprintf( log, ")" )
)
             
OPER_DEF(LN,  'l',
	new_node = _MUL(_DIV(CREATE_NUM( 1 ), COPY(LEFT)), DIFF(LEFT)),

    fprintf( log, "\\ln(" );
    fprintf( out, "log(" );
    PrintExpression( node->left, log, out );
    fprintf( out, ")" );
    fprintf( log, ")" )
)

OPER_DEF(CH, 'h',
	new_node = _MUL(_SH(COPY(LEFT)), DIFF(LEFT)),

    fprintf( log, "\\cosh(" );
    fprintf( out, "cosh(" );
    PrintExpression( node->left, log, out );
    fprintf( out, ")" );
    fprintf( log, ")" )
)
             
OPER_DEF(SH, 'w',
	new_node = _MUL(_CH(COPY(LEFT)), DIFF(LEFT)),

    fprintf( log, "\\sinh(" );
    fprintf( out, "sinh(" );
    PrintExpression( node->left, log, out );
    fprintf( out, ")" );
    fprintf( log, ")" )
)