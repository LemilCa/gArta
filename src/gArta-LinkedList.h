#if !defined(GARTA__LINKED_LIST__H)
#define GARTA__LINKED_LIST__H

///////////////////////////////////////////// Defines /////////////////////////////////////////////

#if !defined(GARTA__LINKED_LIST_SIZE)
    #define GARTA__LINKED_LIST_SIZE GARTA__SIZE
#endif /* !defined(GARTA__LINKED_LIST_SIZE) */

////////////////////////////////////////////// Types //////////////////////////////////////////////

typedef GARTA__LINKED_LIST_SIZE gArta_LinkedListSize;
typedef struct gArta_LinkedList *gArta_LinkedList;

////////////////////////////////////// Function Declarations //////////////////////////////////////

gArta_LinkedList gArta_LinkedList_create(const gArta_LinkedListSize capacity, gArta_DataInfos *dataInfos_pt);
gArta_LinkedList gArta_LinkedList_destroy(gArta_LinkedList linkedList);


int gArta_LinkedList_print(const gArta_LinkedList linkedList);


#endif /* defined(GARTA__LINKED_LIST__H) */


#if defined(GARTA__IMPLEMENTATION)

////////////////////////////////////////////// Types //////////////////////////////////////////////

typedef struct gArta_LinkedListNode *gArta_LinkedListNode;
struct gArta_LinkedListNode {
    gArta_Data data;
    gArta_LinkedListNode next;
};

struct gArta_LinkedList {
    gArta_LinkedListSize capacity;
    gArta_DataInfos *dataInfos_pt;

    gArta_LinkedListSize nbNodes;
    gArta_LinkedListNode first;
};

////////////////////////////////////// Function Declarations //////////////////////////////////////

void gArta_LinkedList_malloc(gArta_LinkedList *linkedList_pt);


void gArta_LinkedListNode_free(gArta_LinkedListNode node, gArta_Data (*destroy_data)(gArta_Data));
void gArta_LinkedListNodes_free(gArta_LinkedListNode node, gArta_Data (*destroy_data)(gArta_Data));

void gArta_LinkedListNode_print(int *print_pt, const gArta_LinkedListNode node, int (*print_data)(const gArta_Data));
void gArta_LinkedListNodes_print(int *print_pt, const gArta_LinkedListNode node, int (*print_data)(const gArta_Data));

/////////////////////////////////////// Function Definitions //////////////////////////////////////

gArta_LinkedList gArta_LinkedList_create(const gArta_LinkedListSize capacity, gArta_DataInfos *dataInfos_pt)
{
    if (capacity < 0) { gArta_Error_global_set(GARTA__ERROR__OUT_OF_BOUNDS); return NULL; }

    gArta_LinkedList linkedList; gArta_LinkedList_malloc(&linkedList);
    if (!gArta_Error_global_isNone()) { return linkedList; }

    linkedList -> capacity = capacity;
    linkedList -> dataInfos_pt = dataInfos_pt;

    linkedList -> nbNodes = 0;
    linkedList -> first = NULL;

    return linkedList;
}
gArta_LinkedList gArta_LinkedList_destroy(gArta_LinkedList linkedList)
{
    if (linkedList == NULL) { return NULL; }

    gArta_LinkedListNodes_free(linkedList -> first, linkedList -> dataInfos_pt -> destroy);
    if (!gArta_Error_global_isNone()) { return linkedList; }
    linkedList -> first = NULL;

    GARTA__FREE(linkedList);

    return NULL;
}


int gArta_LinkedList_print(const gArta_LinkedList linkedList)
{
    int print_val = 0, print_tmp;

    if (linkedList == NULL) {
        print_tmp = printf("%p", NULL);
        if (print_tmp == EOF) { gArta_Error_global_set(GARTA__ERROR__PRINT); return EOF; }
        print_val += print_tmp;

        return print_val;
    }

    gArta_LinkedListNodes_print(&print_tmp, linkedList -> first, linkedList -> dataInfos_pt -> print);
    if (!gArta_Error_global_isNone()) { return print_tmp; }
    print_val += print_tmp;

    return print_val;
}



void gArta_LinkedList_malloc(gArta_LinkedList *linkedList_pt)
{
    gArta_LinkedList linkedList = GARTA__MALLOC(sizeof(struct gArta_LinkedList));
    if (linkedList == NULL) { gArta_Error_global_set(GARTA__ERROR__ALLOC); *linkedList_pt = NULL; return; }

    *linkedList_pt = linkedList; return;
}


void gArta_LinkedListNode_free(gArta_LinkedListNode node, gArta_Data (*destroy_data)(gArta_Data))
{
    node -> data = destroy_data(node -> data);
    if (!gArta_Error_global_isNone()) { return; }
    
    GARTA__FREE(node);

    return;
}
void gArta_LinkedListNodes_free(gArta_LinkedListNode node, gArta_Data (*destroy_data)(gArta_Data))
{
    if (node == NULL) { return; }

    gArta_LinkedListNode node_tmp;
    while (node != NULL) {
        node_tmp = node -> next;

        gArta_LinkedListNode_free(node, destroy_data);
        if (!gArta_Error_global_isNone()) { return; }
        node = node_tmp;
    }

    return;
}

void gArta_LinkedListNode_print(int *print_pt, const gArta_LinkedListNode node, int (*print_data)(const gArta_Data))
{
    int print_val = 0, print_tmp;

    print_tmp = print_data(node -> data);
    if (!gArta_Error_global_isNone()) { *print_pt = print_tmp; return; }
    print_val += print_tmp;

    *print_pt = print_val; return;
}
void gArta_LinkedListNodes_print(int *print_pt, const gArta_LinkedListNode node, int (*print_data)(const gArta_Data))
{
    int print_val = 0, print_tmp;

    if (node == NULL) {
        print_tmp = printf("Empty");
        if (print_tmp == EOF) { gArta_Error_global_set(GARTA__ERROR__PRINT); *print_pt = EOF; return; }
        print_val += print_tmp;

        *print_pt = print_val; return;
    }

    gArta_LinkedListNode node_tmp = node;

    gArta_LinkedListNodes_print(&print_tmp, node_tmp, print_data);
    if (!gArta_Error_global_isNone()) { *print_pt = print_tmp; return; }
    print_val += print_tmp;

    node_tmp = node_tmp -> next;

    while (node_tmp != NULL) {
        print_tmp = printf(" -> ");
        if (print_tmp == EOF) { gArta_Error_global_set(GARTA__ERROR__PRINT); *print_pt = EOF; return; }
        print_val += print_tmp;

        gArta_LinkedListNodes_print(&print_tmp, node_tmp, print_data);
        if (!gArta_Error_global_isNone()) { *print_pt = print_tmp; return; }
        print_val += print_tmp;
    }

    *print_pt = print_val; return;
}


#endif /* defined(GARTA__IMPLEMENTATION) */