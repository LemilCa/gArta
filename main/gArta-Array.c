#define GARTA__IMPLEMENTATION
#include "../src/gArta.h"
#include "../src/gArta-Array.h"
#include "../test/simple.h"

#define CHECK_ERROR(_return_val_) \
    if (!gArta_Error_global_isNone()) { gArta_Error_global_print(); gArta_Error_global_reset(); printf("\n"); return (_return_val_); }


gArta_Array main_Array_create(const gArta_ArraySize CAPACITY, gArta_DataInfos *DATA_INFOS__PT);
gArta_Array main_Array_destroy(gArta_Array ARRAY);


int main_Array_print(const gArta_Array ARRAY);


gArta_Array main_Array_insert(gArta_Array ARRAY, const gArta_ArraySize INDEX, const gArta_Data DATA);

gArta_Array main_Array_fill(gArta_Array ARRAY, const gArta_Data DATA);
gArta_Array main_Array_erase(gArta_Array ARRAY);


gArta_ArraySize main_Array_nbDatas(const gArta_Array ARRAY);


int main()
{
    srand(time(NULL));
    gArta_ArraySize CAPACITY = 10;
    gArta_DataInfos DATA_INFOS = gArta_Test_dataInfos();

    gArta_Array array = main_Array_create(CAPACITY, &DATA_INFOS);
    main_Array_print(array);
    main_Array_nbDatas(array);
    printf("\n");

    array = main_Array_fill(array, gArta_Test_getRandom());
    main_Array_print(array);
    main_Array_nbDatas(array);
    printf("\n");

    array = main_Array_erase(array);
    main_Array_print(array);
    main_Array_nbDatas(array);
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


gArta_Array main_Array_insert(gArta_Array ARRAY, const gArta_ArraySize INDEX, const gArta_Data DATA)
{
    printf("array insert: ");
    gArta_Array array_insert = gArta_Array_insert(ARRAY, INDEX, DATA);
    CHECK_ERROR(array_insert);
    printf("\n");

    printf("\t[array] ");
    printf("%p ", (void*)(ARRAY));
    printf("\n");

    printf("\t[index] ");
    printf("%d ", INDEX);
    printf("\n");

    printf("\t[data] ");
    gArta_Test_print((gArta_Test)(DATA));
    printf("\n");

    printf("\t> ");
    printf("%p ", (void*)(array_insert));
    printf("\n");

    return array_insert;
}

gArta_Array main_Array_fill(gArta_Array ARRAY, const gArta_Data DATA)
{
    printf("array fill: ");
    gArta_Array array_fill = gArta_Array_fill(ARRAY, DATA);
    CHECK_ERROR(array_fill);
    printf("\n");

    printf("\t[array] ");
    printf("%p ", (void*)(ARRAY));
    printf("\n");

    printf("\t[data] ");
    gArta_Test_print(DATA);
    printf("\n");

    printf("\t> ");
    printf("%p ", (void*)(array_fill));
    printf("\n");

    return array_fill;
}
gArta_Array main_Array_erase(gArta_Array ARRAY)
{
    printf("array erase: ");
    gArta_Array array_erase = gArta_Array_erase(ARRAY);
    CHECK_ERROR(array_erase);
    printf("\n");

    printf("\t[array] ");
    printf("%p ", (void*)(ARRAY));
    printf("\n");

    printf("\t> ");
    printf("%p ", (void*)(array_erase));
    printf("\n");

    return array_erase;
}


gArta_ArraySize main_Array_nbDatas(const gArta_Array ARRAY)
{
    printf("array nbDatas: ");
    gArta_ArraySize array_nbDatas = gArta_Array_nbDatas(ARRAY);
    CHECK_ERROR(array_nbDatas);
    printf("\n");

    printf("\t[array] ");
    printf("%p ", (void*)(ARRAY));
    printf("\n");

    printf("\t> ");
    printf("%d ", array_nbDatas);
    printf("\n");

    return array_nbDatas;
}

