#define GARTA__IMPLEMENTATION
#include "../src/gArta.h"
#include "../src/gArta-DoubleLinkedList.h"
#include "../test/simple.h"

#define CHECK_ERROR(_return_val_) \
    if (!gArta_Error_global_isNone()) { gArta_Error_global_print(); gArta_Error_global_reset(); printf("\n"); return (_return_val_); }


gArta_DoubleLinkedList main_DoubleLinkedList_create(const gArta_DoubleLinkedListSize CAPACITY, gArta_DataInfos *DATA_INFOS__PT);
gArta_DoubleLinkedList main_DoubleLinkedList_destroy(gArta_DoubleLinkedList DOUBLE_LINKED_LIST);


int main_DoubleLinkedList_print(const gArta_DoubleLinkedList DOUBLE_LINKED_LIST);


int main() {
    gArta_DataInfos dataInfos = gArta_Test_dataInfos();

    gArta_DoubleLinkedList doubleLinkedList = main_DoubleLinkedList_create(10, &dataInfos);
    main_DoubleLinkedList_print(doubleLinkedList);
    printf("\n");

    doubleLinkedList = main_DoubleLinkedList_destroy(doubleLinkedList);
    main_DoubleLinkedList_print(doubleLinkedList);

    return EXIT_SUCCESS;
}


gArta_DoubleLinkedList main_DoubleLinkedList_create(const gArta_DoubleLinkedListSize CAPACITY, gArta_DataInfos *DATA_INFOS__PT)
{
    printf("doubleLinkedList create: ");
    gArta_DoubleLinkedList doubleLinkedList_create = gArta_DoubleLinkedList_create(CAPACITY, DATA_INFOS__PT);
    CHECK_ERROR(doubleLinkedList_create);
    printf("\n");

    printf("\t[capacity] ");
    printf("%d ", CAPACITY);
    printf("\n");

    printf("\t> ");
    printf("%p ", (void*)(doubleLinkedList_create));
    printf("\n");

    return doubleLinkedList_create;
}
gArta_DoubleLinkedList main_DoubleLinkedList_destroy(gArta_DoubleLinkedList DOUBLE_LINKED_LIST)
{
    printf("doubleLinkedList destroy: ");
    gArta_DoubleLinkedList doubleLinkedList_destroy = gArta_DoubleLinkedList_destroy(DOUBLE_LINKED_LIST);
    CHECK_ERROR(doubleLinkedList_destroy);
    printf("\n");

    printf("\t[doubleLinkedList] ");
    printf("%p ", (void*)(DOUBLE_LINKED_LIST));
    printf("\n");

    printf("\t> ");
    printf("%p ", (void*)(doubleLinkedList_destroy));
    printf("\n");

    return doubleLinkedList_destroy;
}


int main_DoubleLinkedList_print(const gArta_DoubleLinkedList DOUBLE_LINKED_LIST)
{
    printf("doubleLinkedList print: ");
    int doubleLinkedList_print = gArta_DoubleLinkedList_print(DOUBLE_LINKED_LIST);
    CHECK_ERROR(doubleLinkedList_print);
    printf("\n");

    printf("\t[doubleLinkedList] ");
    printf("%p ", (void*)(DOUBLE_LINKED_LIST));
    printf("\n");

    printf("\t> ");
    printf("%d ", doubleLinkedList_print);
    printf("\n");

    return doubleLinkedList_print;
}
