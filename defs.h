#define NEW_NODE( NAME )                                   \
    Node* NAME = ( Node* )calloc( 1, sizeof( Node ) );      \
    if( NAME == NULL ) return NULL;

#define NEW_ARG( NODE, NAME )                                \
    value* NAME = ( value* )calloc( 1, sizeof( value ) );     \
    if  (NAME == NULL ) return NULL;                           \
    NODE->value = NAME;

#define OPER_ARG( ARG, OPER_ )  \
    ARG->type = OPER_TYPE;       \
    ARG->oper = OPER_;

#define NUM_ARG(ARG, NUM_)        \
    ARG->type = NUM_TYPE;          \
    ARG->num  = NUM_;

#define VAR_ARG(ARG, VAR_)            \
    ARG->type = VAR_TYPE;              \
    ARG->var  = VAR_;

#define CONNECT(PAR, CHI, SIDE)           \
    PAR->SIDE = CHI;                       \
    CHI->parent = PAR;

