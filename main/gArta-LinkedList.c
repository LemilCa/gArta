#define GARTA__IMPLEMENTATION
#include "../src/gArta.h"
#include "../src/gArta-LinkedList.h"
#include "../test/simple.h"


gArta_LinkedList main_LinkedList_create(const gArta_LinkedListSize CAPACITY, gArta_DataInfos *DATA_INFOS__PT);
gArta_LinkedList main_LinkedList_destroy(gArta_LinkedList LINKED_LIST);


int main_LinkedList_print(const gArta_LinkedList LINKED_LIST);


int main()
{
    gArta_DataInfos dataInfos = gArta_Test_dataInfos();

    gArta_LinkedList linkedList = main_LinkedList_create(10, &dataInfos);
    main_LinkedList_print(linkedList);
    printf("\n");

    linkedList = main_LinkedList_destroy(linkedList);
    main_LinkedList_print(linkedList);

    return EXIT_SUCCESS;
}


gArta_LinkedList main_LinkedList_create(const gArta_LinkedListSize CAPACITY, gArta_DataInfos *DATA_INFOS__PT)
{
    printf("linkekList create: ");
    gArta_LinkedList linkedList_create = gArta_LinkedList_create(CAPACITY, DATA_INFOS__PT);
    if (!gArta_Error_global_isNone()) { gArta_Error_global_print(); gArta_Error_global_reset(); printf("\n"); return linkedList_create; }
    printf("\n");

    printf("\t-capacity: ");
    printf("%d", CAPACITY);
    printf("\n");

    printf("\t$ %p\n", (void*)(linkedList_create));

    return linkedList_create;
}
gArta_LinkedList main_LinkedList_destroy(gArta_LinkedList LINKED_LIST)
{
    printf("linkedList destroy: ");
    gArta_LinkedList linkedList_destroy = gArta_LinkedList_destroy(LINKED_LIST);
    printf("\n");

    printf("\t$ %p\n", (void*)(linkedList_destroy));

    return linkedList_destroy;
}


int main_LinkedList_print(const gArta_LinkedList LINKED_LIST)
{
    printf("linkedList print: ");
    int linkedList_print = gArta_LinkedList_print(LINKED_LIST);
    printf("\n");

    printf("\t>return: ");
    printf("%d", linkedList_print);
    printf("\n");

    return linkedList_print;
}
