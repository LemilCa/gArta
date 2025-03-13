#if !defined(GARTA__DOUBLE_LINKED_LIST__H)
#define GARTA__DOUBLE_LINKED_LIST__H

///////////////////////////////////////////// Defines /////////////////////////////////////////////

#if !defined(GARTA__DOUBLE_LINKED_LIST_SIZE)
    #define GARTA__DOUBLE_LINKED_LIST_SIZE GARTA__SIZE
#endif /* !defined(GARTA__DOUBLE_LINKED_LIST_SIZE) */

////////////////////////////////////////////// Types //////////////////////////////////////////////

typedef GARTA__DOUBLE_LINKED_LIST_SIZE gArta_DoubleLinkedListSize;
typedef struct gArta_DoubleLinkedList *gArta_DoubleLinkedList;

////////////////////////////////////// Function Declarations //////////////////////////////////////

gArta_DoubleLinkedList gArta_DoubleLinkedList_create(const gArta_DoubleLinkedListSize capacity, gArta_DataInfos *dataInfos_pt);
gArta_DoubleLinkedList gArta_DoubleLinkedList_destroy(gArta_DoubleLinkedList doubleLinkedList);


int gArta_DoubleLinkedList_print(const gArta_DoubleLinkedList doubleLinkedList);


#endif /* !defined(GARTA__DOUBLE_LINKED_LIST__H) */


#if defined(GARTA__DOUBLE_LINKED_LIST__H)

////////////////////////////////////////////// Types //////////////////////////////////////////////

typedef struct gArta_DoubleLinkedListNode *gArta_DoubleLinkedListNode;
struct gArta_DoubleLinkedListNode {
    gArta_Data data;
    gArta_DoubleLinkedListNode previous, next;
};

struct gArta_DoubleLinkedList {
    gArta_DoubleLinkedListSize capacity;
    gArta_DataInfos *dataInfos_pt;

    gArta_DoubleLinkedListSize nbNodes;
    gArta_DoubleLinkedListNode first, last;
};

////////////////////////////////////// Function Declarations //////////////////////////////////////

void gArta_DoubleLinkedList_malloc(gArta_DoubleLinkedList *doubleLinkedList_pt);


void gArta_DoubleLinkedListNode_free(gArta_DoubleLinkedListNode node, gArta_Data (*destroy_data)(gArta_Data));
void gArta_DoubleLinkedListNodes_free(gArta_DoubleLinkedListNode node, gArta_Data (*destroy_data)(gArta_Data));

void gArta_DoubleLinkedListNode_print(int *print_pt, gArta_DoubleLinkedListNode node, int (*print_data)(gArta_Data));
void gArta_DoubleLinkedListNodes_print(int *print_pt, gArta_DoubleLinkedListNode node, int (*print_data)(gArta_Data));

/////////////////////////////////////// Function Definitions //////////////////////////////////////

gArta_DoubleLinkedList gArta_DoubleLinkedList_create(const gArta_DoubleLinkedListSize capacity, gArta_DataInfos *dataInfos_pt)
{
    if (capacity < 0) { gArta_Error_global_set(GARTA__ERROR__OUT_OF_BOUNDS); return NULL; }

    gArta_DoubleLinkedList doubleLinkedList; gArta_DoubleLinkedList_malloc(&doubleLinkedList);
    if (!gArta_Error_global_isNone()) { return doubleLinkedList; }

    doubleLinkedList -> capacity = capacity;
    doubleLinkedList -> dataInfos_pt = dataInfos_pt;

    doubleLinkedList -> nbNodes = 0;
    doubleLinkedList -> first = doubleLinkedList -> last = NULL;

    return doubleLinkedList;
}
gArta_DoubleLinkedList gArta_DoubleLinkedList_destroy(gArta_DoubleLinkedList doubleLinkedList)
{
    if (doubleLinkedList == NULL) { return NULL; }

    gArta_DoubleLinkedListNodes_free(doubleLinkedList -> first, doubleLinkedList -> dataInfos_pt -> destroy);
    if (!gArta_Error_global_isNone()) { return doubleLinkedList; }
    doubleLinkedList -> first = doubleLinkedList -> last = NULL;

    GARTA__FREE(doubleLinkedList);

    return NULL;
}


int gArta_DoubleLinkedList_print(const gArta_DoubleLinkedList doubleLinkedList)
{
    int print_val = 0, print_tmp;

    if (doubleLinkedList == NULL) {
        print_tmp = printf("%p", NULL);
        if (print_tmp == EOF) { gArta_Error_global_set(GARTA__ERROR__PRINT); return EOF; }
        print_val += print_tmp;

        return print_val;
    }

    gArta_DoubleLinkedListNodes_print(&print_tmp, doubleLinkedList -> first, doubleLinkedList -> dataInfos_pt -> print);
    if (!gArta_Error_global_isNone()) { return print_tmp; }
    print_val += print_tmp;

    return print_val;
}



void gArta_DoubleLinkedList_malloc(gArta_DoubleLinkedList *doubleLinkedList_pt)
{
    gArta_DoubleLinkedList doubleLinkedList = GARTA__MALLOC(sizeof(struct gArta_DoubleLinkedList));
    if (doubleLinkedList == NULL) { gArta_Error_global_set(GARTA__ERROR__ALLOC); *doubleLinkedList_pt = NULL; return; }

    *doubleLinkedList_pt = doubleLinkedList; return;
}


void gArta_DoubleLinkedListNode_free(gArta_DoubleLinkedListNode node, gArta_Data (*destroy_data)(gArta_Data))
{
    node -> data = destroy_data(node -> data);
    if (!gArta_Error_global_isNone()) { return; }

    GARTA__FREE(node);

    return;
}
void gArta_DoubleLinkedListNodes_free(gArta_DoubleLinkedListNode node, gArta_Data (*destroy_data)(gArta_Data))
{
    if (node == NULL) { return; }

    gArta_DoubleLinkedListNode node_tmp;
    while (node != NULL) {
        node_tmp = node -> next;

        gArta_DoubleLinkedListNode_free(node_tmp, destroy_data);
        if (!gArta_Error_global_isNone()) { return; }

        node = node_tmp;
    }

    return;
}

void gArta_DoubleLinkedListNode_print(int *print_pt, gArta_DoubleLinkedListNode node, int (*print_data)(gArta_Data))
{
    int print_val = 0, print_tmp;

    print_tmp = print_data(node -> data);
    if (!gArta_Error_global_isNone()) { *print_pt = print_tmp; return; }
    print_val += print_tmp;

    *print_pt = print_val; return;
}
void gArta_DoubleLinkedListNodes_print(int *print_pt, gArta_DoubleLinkedListNode node, int (*print_data)(gArta_Data))
{
    int print_val = 0, print_tmp;

    if (node == NULL) {
        print_tmp = printf("Empty");
        if (print_tmp == EOF) { gArta_Error_global_set(GARTA__ERROR__PRINT); *print_pt = EOF; return; }
        print_val += print_tmp;

        *print_pt = print_val; return;
    }

    gArta_DoubleLinkedListNode node_tmp = node;

    gArta_DoubleLinkedListNode_print(&print_tmp, node_tmp, print_data);
    if (!gArta_Error_global_isNone()) { *print_pt = print_tmp; return; }
    print_val += print_tmp;

    node_tmp = node -> next;
    while (node_tmp != NULL) {
        print_tmp = printf(" -> ");
        if (print_tmp == EOF) { gArta_Error_global_set(GARTA__ERROR__PRINT); *print_pt = EOF; return; }
        print_val += print_tmp;

        gArta_DoubleLinkedListNode_print(&print_tmp, node_tmp, print_data);
        if (!gArta_Error_global_isNone()) { *print_pt = print_tmp; return; }
        print_val += print_tmp;
    }

    *print_pt = print_val; return;
}


#endif /* defined(GARTA__DOUBLE_LINKED_LIST__H) */