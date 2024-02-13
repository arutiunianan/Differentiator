#include "dif.h"

#define CONNECT(PAR, CHI, SIDE)           \
    PAR->SIDE = CHI;                       \
    CHI->parent = PAR;

int GetFileSize( FILE* text, int start )
{
    assert( text != NULL );
    fseek( text, 0, SEEK_END );
    int fileSize = ftell( text ) - start;
    fseek( text, 0, start );
    return fileSize;
}

int IsMathConst( char op )
{
    if( op == EXP || op == PI )
        return op;

    //return FUNC_IS_OK;
    return 0;
}

int StrEqual( const char *l, const char *r, int len )
{
    if( l == NULL || r == NULL ) return 0;

    for( int i = 0; i < len; i++ )
        if ( l[i] != r[i] ) 
            return 0;

    return 1;
}

void ChangeNode( Node* node, int type, double arg, Node* left, Node* right )
{
    if( node == NULL ) return;
    node->left = left;
    node->right = right;
    node->value->arg = arg;
    node->value->type = type;

}

void ChangeNode( Node* node, int type, double arg )
{
    ChangeNode( node, type, arg, NULL, NULL );
}

void ChangeNode( Node* node, int type, double arg, Node* left )
{
    ChangeNode( node, type, arg, left, NULL );
}

void ChangeNode( Node* node, Node* copy_node )
{
    ChangeNode( node, copy_node->value->type, copy_node->value->arg, copy_node->left, copy_node->right );
}

Node* CreateNodeWithType( int type, double arg )
{
    Node* node = ( Node* )calloc( 1, sizeof( Node ) );
    if( node == NULL ) return NULL;
    value* argum = ( value* )calloc( 1, sizeof( value ) );
    if  ( argum == NULL ) return NULL;
    argum->type = type;
    argum->arg = arg;
    node->value = argum;
    return node;
}

Node* CreateNodeWithType( int type, double arg, Node* val )
{
    Node* node = CreateNodeWithType( type, arg );
    if( node == NULL ) return NULL;
    CONNECT( node, val, left );
    return node;
}

Node* CreateNodeWithType( int type, double arg, Node* val1, Node* val2 )
{
    Node* node = CreateNodeWithType( type, arg );
    if( node == NULL ) return NULL;
    CONNECT( node, val1, left );
    CONNECT( node, val2, right );
    return node;
}

int ReadFunc( char **str, int *n )
{
    //if( str == NULL || *str == NULL ) 
        //return PTR_IS_NULL;
    
    //int status = FUNC_IS_OK;
    int status = 1;


    if( StrEqual( *str, "pi", 2 ) )
    {
        (*str) += 2;
        *n = PI;
    }
    else
    if( StrEqual( *str, "exp", 1 ) )
    {
        (*str) += 3;
        *n = EXP;
    }
    else
    if( StrEqual( *str, "sin", 3 ) )
    {
        (*str) += 3;
        *n = SIN;
    }
    else
    if( StrEqual( *str, "cos", 3 ) )
    {
        (*str) += 3;
        *n    = COS;
    }
    else
    if( StrEqual( *str, "ln", 2 ) )
    {
        (*str) += 2;
        *n     = LN;
    }
    else
    if( StrEqual( *str, "sh", 2 ) )
    {
        (*str) += 2;
        *n     = SH;
    }
    else
    if( StrEqual( *str, "ch", 2 ) )
    {
        (*str) += 2;
        *n     = CH;
    }
    else
    {
        *n = 0;
        //status = OPER_NOT_FOUND;
        status = 0;
    }

    return status;
}

Node* GetN( char **str )
{
    if ( str == NULL || *str == NULL ) return NULL;

    double num = 0;
    int check = 0;
    sscanf( *str, "%lf%n", &num, &check );
    
    if( check == 0 )
        return NULL;
    (*str) += check;

    return CreateNodeWithType( NUM_TYPE, num );
}

Node* GetV( char **str )
{
    if ( str == NULL || *str == NULL ) return NULL;

    char var = 0;
    if ('a' <= **str && **str <= 'z')
    {
        var = **str;
        (*str)++;
    }

    if( var != 0 )
        return CreateNodeWithType( VAR_TYPE, var );
    else
        return GetN( str );
}

Node* GetF( char **str )
{
    if( str == NULL || *str == NULL) return NULL;

    int oper = 0;

    ReadFunc( str, &oper );

    if( IsMathConst( oper ) )
        return CreateNodeWithType( OPER_TYPE, IsMathConst( oper ) );
    else if( oper != 0 )
    {
        Node* val = GetP( str );
        assert( val != NULL );

        Node* node = CreateNodeWithType( OPER_TYPE, oper, val );
        //CONNECT( node, val, left );
        
        return node;
    }
    else
        return GetV( str );
}

Node* GetP( char **str )
{
    if( str == NULL || *str == NULL ) return NULL;

    int multiplier = 1;

    while( **str == '+' || **str == '-' )
        if ( *( (*str)++ ) == '-' )
            multiplier *= -1;
    
    if( multiplier == -1 )
    {
        //Node* L = CreateNodeWithType( NUM_TYPE, 0 );
        

        

        //CONNECT( node, L, left );

        Node* R = GetP( str );
        assert( R != NULL );

        //CONNECT(node, R, right);
        Node* node = CreateNodeWithType( OPER_TYPE, SUB, CreateNodeWithType( NUM_TYPE, 0 ), R );

        return node;
    }
    if ( **str == '(' )
    {
        (*str)++;

        Node* val = GetE( str );
        assert( val != NULL );

        if( **str != ')' )
            return NULL;
        else
            (*str)++;

        return val;
    }
    else
        return GetF( str );
}

Node* GetW( char **str )
{
    if( str == NULL || *str == NULL ) return NULL;

    Node* val = GetP( str );
    assert( val != NULL );

    if( **str == '^' )
    {
        (*str)++;
        Node* val2 = GetW( str );
        assert( val2 != NULL );

        Node* node = CreateNodeWithType( OPER_TYPE, POW, val, val2 );

        val = node;
    }
    return val;
}

Node* GetT( char** str )
{
    if( str == NULL || *str == NULL) return NULL;

    Node* val = GetW( str );
    assert( val != NULL );
    
    while( **str == '*' || **str == '/' )
    {
        int op = **str;
        (*str)++;

        Node* val2 = GetW( str );
        assert( val2 != NULL );

        Node* node = CreateNodeWithType( OPER_TYPE, op, val, val2 );

        //CONNECT( node, val,  left );
        //CONNECT( node, val2, right );
        
        val = node;
    }

    return val;
}

Node* GetE( char** str )
{
    if ( str == NULL || *str == NULL ) return NULL;

    Node* val = GetT( str );
    assert( val != NULL );

    while( **str == '+' || **str == '-' )
    {
        char op = **str;
        (*str)++;

        Node* val2 = GetT( str );
        assert( val2 != NULL );

        Node* node = CreateNodeWithType( OPER_TYPE, op, val, val2 );

        //CONNECT( node, val,  left );
        //CONNECT( node, val2, right );
        
        val = node;
    }

    return val;
}

Node* GetG( char** str )
{
    if ( str == NULL || *str == NULL ) return NULL;

    Node* val = GetE( str );
    assert( val != NULL );

    if( **str != '#' )
        return NULL;
    else
        (*str)++;

    return val;
}

int TreeFill( Dif* dif )
{
    //assert( dif );
    //if( tree == NULL ) 
    //    return TREE_IS_NULL;
    //if( file == NULL ) 
    //    return FILE_IS_NULL;
    //if( buff == NULL || *buff != NULL ) return PTR_IS_NULL;
    
    size_t buff_size = 0;
    //if( GetFileSize( stream ) )
    //    return FILESIZE_IS_ZERO;
         
    dif->file_size = GetFileSize( dif->input, SEEK_SET );
    //if( GetFileSize( file, SEEK_SET ) < 1 )
    //    return BUFFER_CANT_BE_READ;
    dif->buffer = ( char* )calloc( dif->file_size + 1, sizeof( char ) );
    fread( dif->buffer, sizeof( char ), dif->file_size, dif->input );
    dif->buffer[dif->file_size] = '\0';

    dif->tree->root = GetG( &dif->buffer );
    
    //TreeDump(dif->tree, dif->tree->log);
    //if (status) return status;

    //return FUNC_IS_OK;
}

void DifCtor( Dif* dif, const char* input, const char* output )
{
    assert( dif );

    dif->tree = ( Tree* )calloc( 1, sizeof( Tree ) );;
    TreeCtor( dif->tree );

    dif->log =  fopen( "diflog.txt", "wb" );
    //dif->output = fopen( output, "wb" );
    dif->input = fopen( input, "r" );
    dif->file_size = 0;
    dif->buffer = "";

    /*if( !akin->input && !akin->output )
        akin->errors = CANT_OPEN_FILE;
    else 
        akin->errors = GAME_IS_OK;*/
}






char* FileName( int i )
{
    char num[] = {(char) i};
    char* file_name = ( char* )calloc( 9, sizeof( char ) );
    strcat( file_name, "out" );
    strcat( file_name, num );
    strcat( file_name, ".txt" );
    return file_name;
}

void DifferentiateNTimes( Dif* dif, FILE* log, char var, int n )
{
    for( int i = 0; i < n; i++ )
    {
        FILE* out2 = fopen( FileName( i ),"wb" );
        
        dif->tree->root = DifferentiateNode( dif->tree->root, var);
        PrintNewExpression( dif->tree ,log, out2);
    }
}

Node* DifferentiateNode( Node* node, char var)
{	
	if( node == NULL )
		return NULL;


	//DoIntermidiatePrint(expr_tree, node);
    
	if( NUM_TYPE == node->value->type || ( char ) node->value->arg == 'p' || ( char ) node->value->arg == 'e' )
	{
        Node* new_node = CreateNodeWithType( NUM_TYPE, 0 );

		//DoIntermidiatePrint(expr_tree, new_node);
		//DO_LATEX_PRINTF(" \\newline ");

		return new_node;
	}

	if (VAR_TYPE == node->value->type)
	{
        Node* new_node = CreateNodeWithType( NUM_TYPE, (char) node->value->arg == var );

		//DoIntermidiatePrint(expr_tree, new_node);
		//DO_LATEX_PRINTF(" \\newline ");

		return new_node;
	}
    Node* new_node = NULL;
	//if(NODE_OPER)
	//	DO_LATEX_PRINTF(" \\newline ");
    if( OPER_TYPE == node->value->type )
    {

        switch ( (char) node->value->arg )
		{
			#define OPER_DEF( value, designation, differentiate_code, tech_code )  \
            case designation:  \
                differentiate_code;  \
                break; \
				
			#include "defs.h"
			#undef OPER_DEF
		}
	
	//DoIntermidiatePrint(expr_tree, new_node);
    }
    return new_node;
}

void Optimization( Node* node )
{

    if( node->left )
        Optimization( node->left );
    if( node->right )
        Optimization( node->right );
        
    //if(!node)
    //    return NULL;

    if ( node->value->type == OPER_TYPE && ( char ) node->value->arg != 'p' && ( char ) node->value->arg != 'e' )
    {
        switch( ( char ) node->value->arg )
        {
        case MUL:
            if( node->left->value->type == NUM_TYPE && ( char ) node->left->value->arg == 0 || node->right->value->type == NUM_TYPE && ( char ) node->right->value->arg == 0 )
                ChangeNode( node, NUM_TYPE, 0 );
            else if( node->left->value->arg == 1 && node->left->value->type == NUM_TYPE )
                ChangeNode( node, node->right );
            else if( node->right->value->arg == 1 && node->right->value->type == NUM_TYPE )
                ChangeNode( node, node->left );

            else if( node->left->value->type == NUM_TYPE && node->right->value->type == NUM_TYPE )
                ChangeNode( node, NUM_TYPE, node->left->value->arg * node->right->value->arg );
            else if( node->left->value->type == VAR_TYPE && node->right->value->type == VAR_TYPE && node->left->value->arg == node->right->value->arg )
                ChangeNode( node, OPER_TYPE, POW, CreateNodeWithType( VAR_TYPE, node->right->value->arg ) ,CreateNodeWithType( NUM_TYPE, 2 ) );
            break;

        case ADD:
            if( node->left->value->arg == 0 && node->left->value->type == NUM_TYPE )
                ChangeNode( node, node->right );
            else if( node->right->value->arg == 0 && node->right->value->type == NUM_TYPE )
                ChangeNode( node, node->left );
            else if( node->left->value->type == NUM_TYPE && node->right->value->type == NUM_TYPE )
                ChangeNode( node, NUM_TYPE, node->left->value->arg + node->right->value->arg );
            else if( node->left->value->type == VAR_TYPE && node->right->value->type == VAR_TYPE && node->left->value->arg == node->right->value->arg )
                ChangeNode( node, OPER_TYPE, MUL, CreateNodeWithType( NUM_TYPE, 2 ) ,CreateNodeWithType( VAR_TYPE, node->right->value->arg ) );
            break;

        case SUB:
            if( node->right->value->arg == 0 && node->right->value->type == NUM_TYPE )
                ChangeNode( node, node->left );
            else if( node->left->value->type == NUM_TYPE && node->right->value->type == NUM_TYPE )
                ChangeNode( node, NUM_TYPE, node->left->value->arg - node->right->value->arg );
            else if( node->left->value->type == VAR_TYPE && node->right->value->type == VAR_TYPE && node->left->value->arg == node->right->value->arg )
                ChangeNode( node, NUM_TYPE, 0 );
            break;

        case DIV:
            if( node->left->value->arg == 0 && node->left->value->type == NUM_TYPE )
                ChangeNode( node, NUM_TYPE, 0 );
            else if( node->left->value->type == NUM_TYPE && node->right->value->type == NUM_TYPE )
            {
                //printf("%lf \n", node->left->value->arg/node->right->value->arg);
                ChangeNode( node, NUM_TYPE, node->left->value->arg / node->right->value->arg );
                printf( "%lf \n", node->value->arg );
                
            }
            else if( node->left->value->type == VAR_TYPE && node->right->value->type == VAR_TYPE && node->left->value->arg == node->right->value->arg )
                ChangeNode( node, NUM_TYPE, 1 );
            break;
        
        case POW:
            if( node->right->value->arg == 0 && node->right->value->type == NUM_TYPE )
                ChangeNode( node, NUM_TYPE, 1 );
            else if( node->right->value->arg == 1 && node->right->value->type == NUM_TYPE )
                ChangeNode( node, node->left );
            else if( node->left->value->type == NUM_TYPE && node->right->value->type == NUM_TYPE )
                ChangeNode( node, NUM_TYPE, pow(node->left->value->arg,node->right->value->arg) );
            break;

        case LN:
            if( ( char ) node->left->value->arg == 'e' )
                ChangeNode( node, NUM_TYPE, 1 );
            break;

        case COS:
            if( ( char ) node->left->value->arg == 'p' )
                ChangeNode( node, NUM_TYPE, -1 );
            else if( node->left->value->arg == 0 )
                ChangeNode( node, NUM_TYPE, 1 );
            break;

        case SIN:
            if( ( char ) node->left->value->arg == 'p' || node->left->value->arg == 0 )
                ChangeNode( node, NUM_TYPE, 0 );
            break;

        //default:
            //break;
        }
    }

}


void MaclaurinSeries( Dif* dif, char var, int n )
{

}



double Factorial( int n )
{
    int factorial = 1;
    for( int i = 1; i < n; i++ )
        factorial = factorial * n;
    return (double) factorial;
}

Tree* JoinTreesWithSumAndCoef( Tree* left_tree, Tree* right_tree, char var, int n )
{
    //right_tree->root = _MUL( right_tree->root, _DIV( CreateNodeWithType( NUM_TYPE, 1 ), CreateNodeWithType( NUM_TYPE, Factorial( n ) ) ) );
    //right_tree->root = _MUL( right_tree->root, CreateNodeWithType( NUM_TYPE, Factorial( n )  ) );
    right_tree->root = _MUL( right_tree->root, _POW( CreateNodeWithType( VAR_TYPE, var ), CreateNodeWithType( NUM_TYPE, n ) ) );
    left_tree->root = _ADD(left_tree->root, right_tree->root );
    left_tree->size = left_tree->size + right_tree->size;
    return left_tree;
}

Tree* MaclaurinSeriesBeforeN( Dif* dif, char var, int n )
{
    if( n > 0 )
    {
        Tree* treeBeforeN = MaclaurinSeriesBeforeN( dif, var, n - 1 );
        dif->tree->root = DifferentiateNode( dif->tree->root, var);
        return JoinTreesWithSumAndCoef( treeBeforeN, CopyTreeForMaclaurin( dif->tree, var, 1 ), var, n );
    }
    else if( n == 0 )
    {
        return CopyTreeForMaclaurin( dif->tree, var, 1 );
    }
}



Tree* CopyTreeForMaclaurin( Tree* tree, char var, int isMaclaurin )
{
    Tree* new_tree = ( Tree* )calloc( 1, sizeof( Tree ) );
    new_tree->errors = tree->errors;
    new_tree->log = tree->log;
    new_tree->size = tree->size;
    new_tree->root = CopyNodesForMaclaurin( tree->root, var, isMaclaurin );
    //new_tree->root = tree->root;
    return new_tree;
}

Node* CopyNodesForMaclaurin( Node* node, char var, int isMaclaurin )
{
    Node* new_node = CopyNode( node );
    if( new_node->value->type == VAR_TYPE && ( char ) new_node->value->arg == var && isMaclaurin )
    {
        new_node->value->type = NUM_TYPE;
        new_node->value->arg = 0;
    }

    if( node->left )
        new_node->left = CopyNodesForMaclaurin( node->left, var, isMaclaurin );
    if( node->right )
        new_node->right = CopyNodesForMaclaurin( node->right, var, isMaclaurin );
    return new_node;
}