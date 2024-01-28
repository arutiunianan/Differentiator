#include "dif.h"

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
    if( StrEqual( *str, "e", 1 ) )
    {
        (*str) += 1;
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
    if( StrEqual( *str, "lg", 2 ) )
    {
        (*str) += 2;
        *n     = LG;
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

    NEW_NODE( val );
    NEW_ARG( val, arg );
    NUM_ARG( arg, num );

    return val;
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
    {
        NEW_NODE( val );
        NEW_ARG( val, arg );
        VAR_ARG( arg, var );

        return val;
    }
    else
        return GetN( str );
}

Node* GetF( char **str )
{
    if( str == NULL || *str == NULL) return NULL;

    int oper = 0;

    ReadFunc( str, &oper );

    if( IsMathConst( oper ) )
    {
        NEW_NODE( node );
        NEW_ARG( node, arg );
        OPER_ARG( arg, IsMathConst( oper ) );

        return node;
    }
    else
    if( oper != 0 )
    {
        Node* val = GetP( str );
        assert( val != NULL );

        NEW_NODE( node );
        NEW_ARG( node, arg );
        OPER_ARG( arg, oper );

        CONNECT( node, val, left );
        
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
        NEW_NODE( node );
        NEW_ARG ( node, arg );
        OPER_ARG( arg,  SUB );

        NEW_NODE( L);
        NEW_ARG( L, AL );
        NUM_ARG ( AL, 0 );
        CONNECT( node, L, left );

        Node* R = GetP( str );
        assert( R != NULL );

        CONNECT(node, R, right);

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

        NEW_NODE( node);
        NEW_ARG( node, arg );
        OPER_ARG( arg, POW );

        CONNECT( node, val,  left );
        CONNECT( node, val2, right );

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

        NEW_NODE( node );
        NEW_ARG( node, arg );
        OPER_ARG( arg,  op );

        CONNECT( node, val,  left );
        CONNECT( node, val2, right );
        
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

        NEW_NODE( node );
        NEW_ARG ( node, arg );
        OPER_ARG( arg, op );

        CONNECT( node, val,  left );
        CONNECT( node, val2, right );
        
        val = node;
    }

    return val;
}

Node* GetG( char** str )
{
    if ( str == NULL || *str == NULL ) return NULL;

    Node* val = GetE( str );
    assert( val != NULL );

    if( **str != '.' )
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
    
    TreeDump(dif->tree, dif->tree->log);
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






