#include "optimization.h"

void ChangeNode(Node* node, int type, double arg, Node* left, Node* right)
{
    assert(node != NULL);
    LEFT = left;
    RIGHT = right;
    node->value->arg = arg;
    node->value->type = type;
}

void ChangeNode(Node* node, int type, double arg)
{
    ChangeNode(node, type, arg, NULL, NULL);
}

void ChangeNode(Node* node, int type, double arg, Node* left)
{
    ChangeNode(node, type, arg, left, NULL);
}

void ChangeNode(Node* node, Node* copy_node)
{
    ChangeNode(node, copy_node->value->type, copy_node->value->arg, copy_node->left, copy_node->right);
}


void Optimization(Node* node)
{
    if(LEFT)
    {
        Optimization(LEFT);
    }
    if(RIGHT)
    {
        Optimization(RIGHT);
    }

    if (node->value->type == OPER_TYPE && (char) node->value->arg != 'p' && (char) node->value->arg != 'e')
    {
        switch((char) node->value->arg)
        {
        case MUL:
            if(LEFT->value->type == NUM_TYPE && (char) LEFT->value->arg == 0 || RIGHT->value->type == NUM_TYPE && (char) RIGHT->value->arg == 0)
            {
                ChangeNode(node, NUM_TYPE, 0);
            }
            else if(LEFT->value->arg == 1 && LEFT->value->type == NUM_TYPE)
            {
                ChangeNode(node, RIGHT);
            }
            else if(RIGHT->value->arg == 1 && RIGHT->value->type == NUM_TYPE)
            {
                ChangeNode(node, LEFT);
            }
            else if(LEFT->value->type == NUM_TYPE && RIGHT->value->type == NUM_TYPE)
            {
                ChangeNode(node, NUM_TYPE, LEFT->value->arg * RIGHT->value->arg);
            }
            else if(LEFT->value->type == VAR_TYPE && RIGHT->value->type == VAR_TYPE && LEFT->value->arg == RIGHT->value->arg)
            {
                ChangeNode(node, OPER_TYPE, POW, CreateNodeWithType(VAR_TYPE, RIGHT->value->arg), CreateNodeWithType(NUM_TYPE, 2));
            }
            break;

        case ADD:
            if(LEFT->value->arg == 0 && LEFT->value->type == NUM_TYPE)
            {
                ChangeNode(node, RIGHT);
            }
            else if(RIGHT->value->arg == 0 && RIGHT->value->type == NUM_TYPE)
            {
                ChangeNode(node, LEFT);
            }
            else if(LEFT->value->type == NUM_TYPE && RIGHT->value->type == NUM_TYPE)
            {
                ChangeNode(node, NUM_TYPE, LEFT->value->arg + RIGHT->value->arg);
            }
            else if(LEFT->value->type == VAR_TYPE && RIGHT->value->type == VAR_TYPE && LEFT->value->arg == RIGHT->value->arg)
            {
                ChangeNode(node, OPER_TYPE, MUL, CreateNodeWithType(NUM_TYPE, 2), CreateNodeWithType(VAR_TYPE, RIGHT->value->arg));
            }
            break;

        case SUB:
            if(RIGHT->value->arg == 0 && RIGHT->value->type == NUM_TYPE)
            {
                ChangeNode(node, LEFT);
            }
            else if(LEFT->value->type == NUM_TYPE && RIGHT->value->type == NUM_TYPE)
            {
                ChangeNode(node, NUM_TYPE, LEFT->value->arg - RIGHT->value->arg);
            }
            else if(LEFT->value->type == VAR_TYPE && RIGHT->value->type == VAR_TYPE && LEFT->value->arg == RIGHT->value->arg)
            {
                ChangeNode(node, NUM_TYPE, 0);
            }
            break;

        case DIV:
            if(LEFT->value->arg == 0 && LEFT->value->type == NUM_TYPE)
            {
                ChangeNode(node, NUM_TYPE, 0);
            }
            else if(LEFT->value->type == NUM_TYPE && RIGHT->value->type == NUM_TYPE && LEFT->value->arg == RIGHT->value->arg)
            {
                ChangeNode(node, NUM_TYPE, 1);
            }
            else if(LEFT->value->type == VAR_TYPE && RIGHT->value->type == VAR_TYPE && LEFT->value->arg == RIGHT->value->arg)
            {
                ChangeNode(node, NUM_TYPE, 1);
            }
            break;
        
        case POW:
            if(RIGHT->value->arg == 0 && RIGHT->value->type == NUM_TYPE)
            {
                ChangeNode(node, NUM_TYPE, 1);
            }
            else if(RIGHT->value->arg == 1 && RIGHT->value->type == NUM_TYPE)
            {
                ChangeNode(node, LEFT);
            }
            else if(LEFT->value->type == NUM_TYPE && RIGHT->value->type == NUM_TYPE)
            {
                ChangeNode(node, NUM_TYPE, pow(LEFT->value->arg, RIGHT->value->arg));
            }
            break;

        case LN:
            if((char) LEFT->value->arg == 'e')
            {
                ChangeNode(node, NUM_TYPE, 1);
            }
            break;

        case COS:
            if((char) LEFT->value->arg == 'p')
            {
                ChangeNode(node, NUM_TYPE, -1);
            }
            else if(LEFT->value->arg == 0)
            {
                ChangeNode(node, NUM_TYPE, 1);
            }
            break;

        case SIN:
            if((char) LEFT->value->arg == 'p' || LEFT->value->arg == 0)
            {
                ChangeNode(node, NUM_TYPE, 0);
            }
            break;

        default:
            break;
        }
    }
}
