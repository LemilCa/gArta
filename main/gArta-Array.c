#define GARTA__IMPLEMENTATION
#include "../src/gArta.h"
#include "../src/gArta-Array.h"
#include "../test/simple.h"

#define CHECK_ERROR(_return_val_) \
    if (!gArta_Error_global_isNone()) { gArta_Error_global_print(); gArta_Error_global_reset(); printf("\n"); return (_return_val_); }


gArta_Array main_Array_create(const gArta_ArraySize CAPACITY, gArta_DataInfos *DATA_INFOS__PT);
gArta_Array main_Array_destroy(gArta_Array ARRAY);


int main_Array_print(const gArta_Array ARRAY);


int main()
{
    gArta_DataInfos dataInfos = gArta_Test_dataInfos();

    gArta_Array array = main_Array_create(10, &dataInfos);
    main_Array_print(array);
    printf("\n");
    
    array = main_Array_destroy(array);
    main_Array_print(array);

    return EXIT_SUCCESS;
}


gArta_Array main_Array_create(const gArta_ArraySize CAPACITY, gArta_DataInfos *DATA_INFOS__PT)
{
    printf("array create: ");
    gArta_Array array_create = gArta_Array_create(CAPACITY, DATA_INFOS__PT);
    CHECK_ERROR(array_create);
    printf("\n");

    printf("\t[capacity]: ");
    printf("%d ", CAPACITY);
    printf("\n");

    printf("\t> ");
    printf("%p ", (void*)(array_create));
    printf("\n");

    return array_create;
}
gArta_Array main_Array_destroy(gArta_Array ARRAY)
{
    printf("array destroy: ");
    gArta_Array array_destroy = gArta_Array_destroy(ARRAY);
    CHECK_ERROR(array_destroy);
    printf("\n");

    printf("\t[array] ");
    printf("%p ", (void*)(ARRAY));
    printf("\n");

    printf("\t> ");
    printf("%p ", (void*)(array_destroy));
    printf("\n");

    return array_destroy;
}


int main_Array_print(const gArta_Array ARRAY)
{
    printf("array print: ");
    int array_print = gArta_Array_print(ARRAY);
    CHECK_ERROR(array_print);
    printf("\n");

    printf("\t[array] ");
    printf("%p ", (void*)(ARRAY));
    printf("\n");

    printf("\t> ");
    printf("%d ", array_print);
    printf("\n");

    return array_print;
}

