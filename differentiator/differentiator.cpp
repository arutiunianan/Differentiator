#include "differentiator.h"

#define CONNECT(PAR, CHI, SIDE)           \
    PAR->SIDE = CHI;                       \
    CHI->parent = PAR;

int GetFileSize(FILE* text, int start)
{
    assert(text != NULL);
    assert(start >= 0);
    fseek(text, 0, SEEK_END);
    int fileSize = ftell(text) - start;
    fseek(text, 0, start);
    return fileSize;
}

int IsMathConst(char op)
{
    if(op == EXP || op == PI)
        return op;

    return 0;
}

int StrEqual(const char* l, const char* r, int len)
{
    if(l == NULL || r == NULL) 
    {
        return 0;
    }

    for(int i = 0; i < len; i++)
    {
        if (l[i] != r[i]) 
        {
            return 0;
        }
    }

    return 1;
}

Node* CreateNodeWithType(int type, double arg)
{
    Node* node = (Node*)calloc(1, sizeof(Node));
    if(node == NULL) 
    {
        return NULL;
    }
    value* argum = (value*)calloc(1, sizeof(value));
    if  (argum == NULL) 
    {
        return NULL;
    }
    argum->type = type;
    argum->arg = arg;
    node->value = argum;
    return node;
}

Node* CreateNodeWithType(int type, double arg, Node* val)
{
    Node* node = CreateNodeWithType(type, arg);
    if(node == NULL) 
    {
        return NULL;
    }
    CONNECT(node, val, left);
    return node;
}

Node* CreateNodeWithType(int type, double arg, Node* val1, Node* val2)
{
    Node* node = CreateNodeWithType(type, arg);
    if(node == NULL) 
    {
        return NULL;
    }
    CONNECT(node, val1, left);
    CONNECT(node, val2, right);
    return node;
}

int ReadFunc(char** str, int* n)
{
    assert(str != NULL);
    assert(str != NULL);
    int status = 1;

    if(StrEqual(*str, "pi", 2))
    {
        (*str) += 2;
        *n = PI;
    }
    else if(StrEqual(*str, "exp", 1))
    {
        (*str) += 3;
        *n = EXP;
    }
    else if(StrEqual(*str, "sin", 3))
    {
        (*str) += 3;
        *n = SIN;
    }
    else if(StrEqual(*str, "cos", 3))
    {
        (*str) += 3;
        *n    = COS;
    }
    else if(StrEqual(*str, "ln", 2))
    {
        (*str) += 2;
        *n     = LN;
    }
    else if(StrEqual(*str, "sh", 2))
    {
        (*str) += 2;
        *n     = SH;
    }
    else if(StrEqual(*str, "ch", 2))
    {
        (*str) += 2;
        *n     = CH;
    }
    else
    {
        *n = 0;
        status = 0;
    }

    return status;
}

Node* GetN(char** str)
{
    if (str == NULL || *str == NULL) 
    {
        return NULL;
    }

    double num = 0;
    int check = 0;
    sscanf(*str, "%lf%n", &num, &check);
    
    if(check == 0)
        return NULL;
    (*str) += check;

    return CreateNodeWithType(NUM_TYPE, num);
}

Node* GetV(char** str)
{
    if (str == NULL || *str == NULL) 
    {
        return NULL;
    }

    char var = 0;
    if ('a' <= **str && **str <= 'z')
    {
        var = **str;
        (*str)++;
    }

    if(var != 0)
    {
        return CreateNodeWithType(VAR_TYPE, var);
    }
    else
    {
        return GetN(str);
    }
}

Node* GetF(char** str)
{
    if(str == NULL || *str == NULL) 
    {
        return NULL;
    }

    int oper = 0;

    ReadFunc(str, &oper);

    if(IsMathConst(oper))
    {
        return CreateNodeWithType(OPER_TYPE, IsMathConst(oper));
    }
    else if(oper != 0)
    {
        Node* val = GetP(str);
        assert(val != NULL);

        Node* node = CreateNodeWithType(OPER_TYPE, oper, val);
        
        return node;
    }
    else
    {
        return GetV(str);
    }
}

Node* GetP(char** str)
{
    if(str == NULL || *str == NULL) 
    {
        return NULL;
    }

    int multiplier = 1;

    while(**str == '+' || **str == '-')
    {
        if (*((*str)++) == '-')
        {
            multiplier *= -1;
        }
    }
    
    if(multiplier == -1)
    {
        Node* R = GetP(str);
        assert(R != NULL);
        Node* node = CreateNodeWithType(OPER_TYPE, SUB, CreateNodeWithType(NUM_TYPE, 0), R);

        return node;
    }
    if (**str == '(')
    {
        (*str)++;

        Node* val = GetE(str);
        assert(val != NULL);

        if(**str != ')')
        {
            return NULL;
        }
        else
        {
            (*str)++;
        }

        return val;
    }
    else
    {
        return GetF(str);
    }
}

Node* GetW(char** str)
{
    if(str == NULL || *str == NULL) 
    {
        return NULL;
    }

    Node* val = GetP(str);
    assert(val != NULL);

    if(**str == '^')
    {
        (*str)++;
        Node* val2 = GetW(str);
        assert(val2 != NULL);

        Node* node = CreateNodeWithType(OPER_TYPE, POW, val, val2);

        val = node;
    }
    return val;
}

Node* GetT(char** str)
{
    if(str == NULL || *str == NULL) 
    {
        return NULL;
    }

    Node* val = GetW(str);
    assert(val != NULL);
    
    while(**str == '*' || **str == '/')
    {
        int op = **str;
        (*str)++;

        Node* val2 = GetW(str);
        assert(val2 != NULL);

        Node* node = CreateNodeWithType(OPER_TYPE, op, val, val2);
        val = node;
    }

    return val;
}

Node* GetE(char** str)
{
    if (str == NULL || *str == NULL) 
    {   
        return NULL;
    }

    Node* val = GetT(str);
    assert(val != NULL);

    while(**str == '+' || **str == '-')
    {
        char op = **str;
        (*str)++;

        Node* val2 = GetT(str);
        assert(val2 != NULL);

        Node* node = CreateNodeWithType(OPER_TYPE, op, val, val2);

        val = node;
    }
    return val;
}

Node* GetG(char** str)
{
    if (str == NULL || *str == NULL) 
    {
        return NULL;
    }

    Node* val = GetE(str);
    assert(val != NULL);

    if(**str != '#')
    {
        return NULL;
    }
    else
    {
        (*str)++;
    }
    return val;
}

int TreeFill(Dif_file* dif_file)
{
    assert(dif_file != NULL);
    if(dif_file->tree == NULL) 
    {
        return TREE_IS_NULL;
    }
         
    int file_size = GetFileSize(dif_file->input, SEEK_SET);
    assert(file_size >= 0);

    char* buffer = (char*)calloc(file_size + 1, sizeof(char));
    assert(buffer != NULL);
    fread(buffer, sizeof(char), file_size, dif_file->input);
    buffer[file_size] = '\0';

    dif_file->tree->root = GetG(&buffer);
    TreeDump(dif_file->tree, dif_file->tree->log);
}

void DifCtor(Dif_file* dif_file, const char* input)
{
    assert(dif_file != NULL);
    assert(input != NULL);

    dif_file->tree = (Tree*)calloc(1, sizeof(Tree));
    assert(dif_file->tree != NULL);
    TreeCtor(dif_file->tree);

    dif_file->tex = fopen("tex/tex.tex", "wb");
    StartLatex(dif_file->tex);

    dif_file->input = fopen(input, "r");
}

void DifDtor(Dif_file* dif_file)
{
    assert(dif_file != NULL);

    TreeDtor(dif_file->tree);
    fclose(dif_file->input);

    EndLatex(dif_file->tex);
    fclose(dif_file->tex);
}

void DifferentiateNTimes(Dif_file* dif_file, char var, int n)
{
    for(int i = 0; i < n; i++)
    {
        dif_file->tree->root = DifferentiateNode(dif_file->tree->root, var);
    }
}

Node* DifferentiateNode(Node* node, char var)
{    
    if(node == NULL)
    {
        return NULL;
    }

    if(NUM_TYPE == node->value->type || (char) node->value->arg == 'p' || (char) node->value->arg == 'e')
    {
        Node* new_node = CreateNodeWithType(NUM_TYPE, 0);
        return new_node;
    }

    if (VAR_TYPE == node->value->type)
    {
        Node* new_node = CreateNodeWithType(NUM_TYPE, (char) node->value->arg == var);
        return new_node;
    }

    Node* new_node = NULL;
    if(OPER_TYPE == node->value->type)
    {
        switch ((char) node->value->arg)
        {
            #define OPER_DEF(value, designation, differentiate_code, tech_code)  \
            case designation:                                                     \
                differentiate_code;                                                \
                break;                                                              \
                
            #include "defs.h"
            #undef OPER_DEF
        }
    }
    return new_node;
}
