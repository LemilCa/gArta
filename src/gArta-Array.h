#if !defined(GARTA__ARRAY__H)
#define GARTA__ARRAY__H

///////////////////////////////////////////// Defines /////////////////////////////////////////////

#if !defined(GARTA__ARRAY_SIZE)
    #define GARTA__ARRAY_SIZE GARTA__SIZE
#endif /* !defined(GARTA__ARRAY_SIZE) */

////////////////////////////////////////////// Types //////////////////////////////////////////////

typedef GARTA__ARRAY_SIZE gArta_ArraySize;
typedef struct gArta_Array *gArta_Array;

////////////////////////////////////// Function Declarations //////////////////////////////////////

gArta_Array gArta_Array_create(const gArta_ArraySize capacity, gArta_DataInfos *dataInfos_pt);
gArta_Array gArta_Array_create_default(gArta_DataInfos *dataInfos_pt);
gArta_Array gArta_Array_copy(const gArta_Array source);
gArta_Array gArta_Array_destroy(gArta_Array array);


int gArta_Array_print(const gArta_Array array);


gArta_Data gArta_Array_get(const gArta_Array array, const gArta_ArraySize index);
gArta_Data gArta_Array_getCopy(const gArta_Array array, const gArta_ArraySize index);


gArta_Array gArta_Array_insert(gArta_Array array, const gArta_ArraySize index, const gArta_Data data);
gArta_Array gArta_Array_delete(gArta_Array array, const gArta_ArraySize index);
gArta_Array gArta_Array_remove(gArta_Array array, const gArta_Data data);

gArta_Array gArta_Array_fill(gArta_Array array, const gArta_Data data);
gArta_Array gArta_Array_erase(gArta_Array array);

gArta_Array gArta_Array_forEach(gArta_Array array, gArta_Data (*action)(gArta_Data));
gArta_Array gArta_Array_removeIf(gArta_Array array, bool (*filter)(const gArta_Data));


bool gArta_Array_isEmpty(const gArta_Array array);
bool gArta_Array_isFull(const gArta_Array array);
gArta_ArraySize gArta_Array_nbDatas(const gArta_Array array);

bool gArta_Array_contains(const gArta_Array array, const gArta_Data data);
gArta_ArraySize gArta_Array_indexOf(const gArta_Array array, const gArta_Data data);
gArta_ArraySize gArta_Array_lastIndexOf(const gArta_Array array, const gArta_Data data);


gArta_Array gArta_Array_reverse(gArta_Array array);


#endif /* !defined(GARTA__ARRAY__H) */


#if defined(GARTA__IMPLEMENTATION)

////////////////////////////////////////////// Types //////////////////////////////////////////////

typedef gArta_Data * gArta_ArrayDatas;

struct gArta_Array {
    gArta_ArraySize capacity;
    gArta_DataInfos *dataInfos_pt;

    gArta_ArraySize nbDatas;
    gArta_ArrayDatas datas;
};

////////////////////////////////////// Function Declarations //////////////////////////////////////

void gArta_Array_malloc(gArta_Array *array_pt);


void gArta_ArrayDatas_calloc(gArta_ArrayDatas *datas_pt, const gArta_ArraySize capacity);
void gArta_ArrayData_free(gArta_ArrayDatas datas, const gArta_ArraySize index, gArta_Data (*destroy_data)(gArta_Data));
void gArta_ArrayDatas_free(gArta_ArrayDatas datas, const gArta_ArraySize capacity, gArta_Data (*destroy_data)(gArta_Data));

void gArta_ArrayData_print(int *print_pt, const gArta_ArrayDatas datas, const gArta_ArraySize index, int (*print_data)(const gArta_Data));
void gArta_ArrayDatas_print(int *print_pt, const gArta_ArrayDatas datas, const gArta_ArraySize capacity, int (*print_data)(const gArta_Data));

/////////////////////////////////////// Function Definitions //////////////////////////////////////

gArta_Array gArta_Array_create(const gArta_ArraySize capacity, gArta_DataInfos *dataInfos_pt)
{
    if (capacity < 0) { gArta_Error_global_set(GARTA__ERROR__OUT_OF_BOUNDS); return NULL; }

    gArta_Array array; gArta_Array_malloc(&array);
    if (!gArta_Error_global_isNone()) { return array; }

    array -> capacity = capacity;
    array -> dataInfos_pt = dataInfos_pt;

    array -> nbDatas = 0;
    gArta_ArrayDatas_calloc(&array -> datas, capacity);
    if (!gArta_Error_global_isNone()) { return array; }

    return array;
}
gArta_Array gArta_Array_destroy(gArta_Array array)
{
    if (array == NULL) { return NULL; }

    gArta_ArrayDatas_free(array -> datas, array -> capacity, array -> dataInfos_pt -> destroy);
    if (!gArta_Error_global_isNone()) { return array; }
    array -> datas = NULL;

    GARTA__FREE(array);

    return NULL;
}


int gArta_Array_print(const gArta_Array array)
{
    int print_val = 0, print_tmp;

    if (array == NULL) {
        print_tmp = printf("%p", NULL);
        if (print_tmp == EOF) { gArta_Error_global_set(GARTA__ERROR__PRINT); return EOF; }
        print_val += print_tmp;

        return print_val;
    }

    gArta_ArrayDatas_print(&print_tmp, array -> datas, array -> capacity, array -> dataInfos_pt -> print);
    if (!gArta_Error_global_isNone()) { return print_tmp; }
    print_val += print_tmp;

    return print_val;
}



void gArta_Array_malloc(gArta_Array *array_pt)
{
    gArta_Array array = GARTA__MALLOC(sizeof(struct gArta_Array));
    if (array == NULL) { gArta_Error_global_set(GARTA__ERROR__ALLOC); *array_pt = NULL; return; }

    *array_pt = array; return;
}


void gArta_ArrayDatas_calloc(gArta_ArrayDatas *datas_pt, const gArta_ArraySize capacity)
{
    if (capacity == 0) { *datas_pt = NULL; return; }

    gArta_ArrayDatas datas = GARTA__CALLOC(capacity, sizeof(gArta_Data));
    if (datas == NULL) { gArta_Error_global_set(GARTA__ERROR__ALLOC); *datas_pt = NULL; return; }

    *datas_pt = datas; return;
}
void gArta_ArrayData_free(gArta_ArrayDatas datas, const gArta_ArraySize index, gArta_Data (*destroy_data)(gArta_Data))
{
    datas[index] = destroy_data(datas[index]);
    if (!gArta_Error_global_isNone()) { return; }

    return;
}
void gArta_ArrayDatas_free(gArta_ArrayDatas datas, const gArta_ArraySize capacity, gArta_Data (*destroy_data)(gArta_Data))
{
    if (datas == NULL) { return; }

    for (gArta_ArraySize index = 0; index < capacity; ++ index) {
        gArta_ArrayData_free(datas, index, destroy_data);
        if (!gArta_Error_global_isNone()) { return; }
    }

    GARTA__FREE(datas);

    return;
}

void gArta_ArrayData_print(int *print_pt, const gArta_ArrayDatas datas, const gArta_ArraySize index, int (*print_data)(const gArta_Data))
{
    int print_val = 0, print_tmp;

    print_tmp = print_data(datas[index]);
    if (!gArta_Error_global_isNone()) { *print_pt = print_tmp; }
    print_val += print_tmp;

    *print_pt = print_val; return;
}
void gArta_ArrayDatas_print(int *print_pt, const gArta_ArrayDatas datas, const gArta_ArraySize capacity, int (*print_data)(const gArta_Data))
{
    int print_val = 0, print_tmp;

    if (datas == NULL) {
        print_tmp = printf("Empty");
        if (print_tmp == EOF) { gArta_Error_global_set(GARTA__ERROR__PRINT); *print_pt = EOF; return; }
        print_val += print_tmp;

        *print_pt = print_val; return;
    }

    for (gArta_ArraySize index = 0; index < capacity; ++ index) {
        print_tmp = printf("[");
        if (print_tmp == EOF) { gArta_Error_global_set(GARTA__ERROR__PRINT); *print_pt = EOF; return; }
        print_val += print_tmp;

        gArta_ArrayData_print(&print_tmp, datas, index, print_data);
        if (!gArta_Error_global_isNone()) { *print_pt = print_tmp; return; }
        print_val += print_tmp;

        print_tmp = printf("]");
        if (print_tmp == EOF) { gArta_Error_global_set(GARTA__ERROR__PRINT); *print_pt = EOF; return; }
        print_val += print_tmp;
    }

    *print_pt = print_val; return;
}


#endif /* defined(GARTA__IMPLEMENTATION) */