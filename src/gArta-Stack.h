#if !defined(GARTA__STACK__H)
#define GARTA__STACK__H

///////////////////////////////////////////// Defines /////////////////////////////////////////////

#if !defined(GARTA__STACK_SIZE)
    #define GARTA__STACK_SIZE GARTA__SIZE
#endif /* !defined(GARTA__STACK_SIZE) */

////////////////////////////////////////////// Types //////////////////////////////////////////////

typedef GARTA__STACK_SIZE gArta_StackSize;
typedef struct gArta_Stack *gArta_Stack;

////////////////////////////////////// Function Declarations //////////////////////////////////////

gArta_Stack gArta_Stack_create(const gArta_StackSize capacity, gArta_DataInfos *dataInfos_pt);
gArta_Stack gArta_Stack_destroy(gArta_Stack stack);


int gArta_Stack_print(const gArta_Stack stack);


#endif /* !defined(GARTA__STACK__H) */


#if defined(GARTA__IMPLEMENTATION)

////////////////////////////////////////////// Types //////////////////////////////////////////////

typedef struct gArta_StackNode *gArta_StackNode;
struct gArta_StackNode {
    gArta_Data data;
    gArta_StackNode next;
};

struct gArta_Stack {
    gArta_StackSize capacity;
    gArta_DataInfos *dataInfos_pt;

    gArta_StackSize nbNodes;
    gArta_StackNode top;
};

////////////////////////////////////// Function Declarations //////////////////////////////////////

void gArta_Stack_malloc(gArta_Stack *stack_pt);


void gArta_StackNode_free(gArta_StackNode node, gArta_Data (*destroy_data)(gArta_Data));

void gArta_StackNode_print(int *print_dt, gArta_StackNode node, int (*print_data)(const gArta_Data));

/////////////////////////////////////// Function Definitions //////////////////////////////////////

gArta_Stack gArta_Stack_create(const gArta_StackSize capacity, gArta_DataInfos *dataInfos_pt)
{
    if (capacity < 0) { gArta_Error_global_set(GARTA__ERROR__OUT_OF_BOUNDS); return NULL; }

    gArta_Stack stack; gArta_Stack_malloc(&stack);
    if (!gArta_Error_global_isNone()) { return stack; }

    stack -> capacity = capacity;
    stack -> dataInfos_pt = dataInfos_pt;

    stack -> nbNodes = 0;
    stack -> top = NULL;

    return stack;
}
gArta_Stack gArta_Stack_destroy(gArta_Stack stack)
{
    if (stack == NULL) { return NULL; }

    gArta_StackNode_free(stack -> top, stack -> dataInfos_pt -> destroy);
    if (!gArta_Error_global_isNone()) { return stack; }
    stack -> top = NULL;

    GARTA__FREE(stack);

    return NULL;
}


int gArta_Stack_print(const gArta_Stack stack)
{
    int print_val = 0, print_tmp;

    if (stack == NULL) {
        print_tmp = printf("%p", NULL);
        if (print_tmp == EOF) { gArta_Error_global_set(GARTA__ERROR__PRINT); return EOF; }
        print_val += print_tmp;

        return print_val;
    }

    gArta_StackNode_print(&print_tmp, stack -> top, stack -> dataInfos_pt -> print);
    if (!gArta_Error_global_isNone()) { return print_tmp; }
    print_val += print_tmp;

    return print_val;
}



void gArta_Stack_malloc(gArta_Stack *stack_pt)
{
    gArta_Stack stack = GARTA__MALLOC(sizeof(struct gArta_Stack));
    if (stack == NULL) { gArta_Error_global_set(GARTA__ERROR__ALLOC); *stack_pt = NULL; return; }

    *stack_pt = stack; return;
}


void gArta_StackNode_free(gArta_StackNode node, gArta_Data (*destroy_data)(gArta_Data))
{
    if (node == NULL) { return; }

    gArta_StackNode node_tmp;
    while (node != NULL) {
        node_tmp = node -> next;

        node -> data = destroy_data(node -> data);
        if (!gArta_Error_global_isNone()) { return; }

        GARTA__FREE(node);

        node = node_tmp;
    }

    return;
}

void gArta_StackNode_print(int *print_dt, gArta_StackNode node, int (*print_data)(const gArta_Data))
{
    int print_val = 0, print_tmp;

    if (node == NULL) {
        print_tmp = printf("Empty");
        if (print_tmp == EOF) { gArta_Error_global_set(GARTA__ERROR__PRINT); *print_dt = EOF; return; }
        print_val += print_tmp;

        *print_dt = print_val; return;
    }

    gArta_StackNode node_tmp = node;

    print_tmp = print_data(node_tmp -> data);
    if (!gArta_Error_global_isNone()) { *print_dt = print_tmp; return; }
    print_val += print_tmp;

    node_tmp = node_tmp -> next;
    while(node_tmp != NULL) {
        print_tmp = printf(" -> ");
        if (print_tmp == EOF) { gArta_Error_global_set(GARTA__ERROR__PRINT); *print_dt = EOF; return; }
        print_val += print_tmp;

        print_tmp = print_data(node_tmp -> data);
        if (!gArta_Error_global_isNone()) { *print_dt = print_tmp; return; }
        print_val += print_tmp;
    }

    *print_dt = print_val; return;
}


#endif /* defined(GARTA__IMPLEMENTATION) */