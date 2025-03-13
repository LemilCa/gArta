#if !defined(GARTA__QUEUE__H)
#define GARTA__QUEUE__H

///////////////////////////////////////////// Defines /////////////////////////////////////////////

#if !defined(GARTA__QUEUE_SIZE)
    #define GARTA__QUEUE_SIZE GARTA__SIZE
#endif /* !defined(GARTA__QUEUE_SIZE) */

////////////////////////////////////////////// Types //////////////////////////////////////////////

typedef GARTA__QUEUE_SIZE gArta_QueueSize;
typedef struct gArta_Queue *gArta_Queue;

////////////////////////////////////// Function Declarations //////////////////////////////////////

gArta_Queue gArta_Queue_create(const gArta_QueueSize capacity, gArta_DataInfos *dataInfos_pt);
gArta_Queue gArta_Queue_destroy(gArta_Queue queue);


int gArta_Queue_print(const gArta_Queue queue);


#endif /* !defined(GARTA__QUEUE__H) */


#if defined(GARTA__IMPLEMENTATION)

////////////////////////////////////////////// Types //////////////////////////////////////////////

typedef struct gArta_QueueNode *gArta_QueueNode;
struct gArta_QueueNode {
    gArta_Data data;
    gArta_QueueNode next;
};

struct gArta_Queue {
    gArta_QueueSize capacity;
    gArta_DataInfos *dataInfos_pt;

    gArta_Queue nbNodes;
    gArta_QueueNode tail, head;
};

////////////////////////////////////// Function Declarations //////////////////////////////////////

void gArta_Queue_malloc(gArta_Queue *queue_pt);


void gArta_QueueNode_free(gArta_QueueNode node, gArta_Data (*destroy_data)(gArta_Data));
void gArta_QueueNodes_free(gArta_QueueNode node, gArta_Data (*destroy_data)(gArta_Data));

void gArta_QueueNode_print(int *print_pt, const gArta_QueueNode node, int (*print_data)(const gArta_Data));
void gArta_QueueNodes_print(int *print_pt, const gArta_QueueNode node, int (*print_data)(const gArta_Data));

/////////////////////////////////////// Function Definitions //////////////////////////////////////

gArta_Queue gArta_Queue_create(const gArta_QueueSize capacity, gArta_DataInfos *dataInfos_pt)
{
    if (capacity < 0) { gArta_Error_global_set(GARTA__ERROR__OUT_OF_BOUNDS); return NULL; }

    gArta_Queue queue; gArta_Queue_malloc(&queue);
    if (!gArta_Error_global_isNone()) { return queue; }

    queue -> capacity = capacity;
    queue -> dataInfos_pt = dataInfos_pt;

    queue -> nbNodes = 0;
    queue -> tail = queue -> head = NULL;

    return queue;
}
gArta_Queue gArta_Queue_destroy(gArta_Queue queue)
{
    if (queue == NULL) { return NULL; }

    gArta_QueueNodes_free(queue -> tail, queue -> dataInfos_pt -> destroy);
    if (!gArta_Error_global_isNone()) { return queue; }
    queue -> tail = queue -> head = NULL;

    GARTA__FREE(queue);

    return NULL;
}


int gArta_Queue_print(const gArta_Queue queue)
{
    int print_val = 0, print_tmp;

    if (queue == NULL) {
        print_tmp = printf("%p", NULL);
        if (print_tmp == EOF) { gArta_Error_global_set(GARTA__ERROR__PRINT); return EOF; }
        print_val += print_tmp;

        return print_val;
    }

    gArta_QueueNodes_print(&print_tmp, queue -> tail, queue -> dataInfos_pt -> print);
    if (!gArta_Error_global_isNone()) { return print_tmp; }
    print_val += print_tmp;

    return print_val;
}



void gArta_Queue_malloc(gArta_Queue *queue_pt)
{
    gArta_Queue queue = GARTA__MALLOC(sizeof(struct gArta_Queue));
    if (queue == NULL) { gArta_Error_global_set(GARTA__ERROR__ALLOC); *queue_pt = NULL; return; }

    *queue_pt = queue; return;
}


void gArta_QueueNode_free(gArta_QueueNode node, gArta_Data (*destroy_data)(gArta_Data))
{
    node -> data = destroy_data(node -> data);
    if (!gArta_Error_global_isNone()) { return; }
    
    GARTA__FREE(node);

    return;
}
void gArta_QueueNodes_free(gArta_QueueNode node, gArta_Data (*destroy_data)(gArta_Data))
{
    if (node == NULL) { return; }

    gArta_QueueNode node_tmp;
    while (node != NULL) {
        node_tmp = node -> next;

        gArta_QueueNode_free(node_tmp, destroy_data);
        if (!gArta_Error_global_isNone()) { return; }

        node = node_tmp;
    }

    return;
}

void gArta_QueueNode_print(int *print_pt, const gArta_QueueNode node, int (*print_data)(const gArta_Data))
{
    int print_val = 0, print_tmp;

    print_tmp = print_data(node -> data);
    if (!gArta_Error_global_isNone()) { *print_pt = print_tmp; return; }
    print_val += print_tmp;

    *print_pt = print_val; return;
}
void gArta_QueueNodes_print(int *print_pt, const gArta_QueueNode node, int (*print_data)(const gArta_Data))
{
    int print_val = 0, print_tmp;

    if (node == NULL) {
        print_tmp = printf("Empty");
        if (print_tmp == EOF) { gArta_Error_global_set(GARTA__ERROR__PRINT); *print_pt = EOF; return; }
        print_val += print_tmp;

        *print_pt = print_val; return;
    }

    gArta_QueueNode node_tmp = node;

    gArta_QueueNode_print(&print_tmp, node_tmp, print_data);
    if (!gArta_Error_global_isNone()) { *print_pt = print_tmp; return; }
    print_val += print_tmp;

    node_tmp = node -> next;
    while (node_tmp != NULL) {
        print_tmp = printf(" -> ");
        if (print_tmp == EOF) { gArta_Error_global_set(GARTA__ERROR__PRINT); *print_pt = EOF; return; }
        print_val += print_tmp;

        gArta_QueueNode_print(&print_tmp, node_tmp, print_data);
        if (!gArta_Error_global_isNone()) { *print_pt = print_tmp; return; }
        print_val += print_tmp;
    }

    *print_pt = print_val; return;
}


#endif /* defined(GARTA__IMPLEMENTATION) */