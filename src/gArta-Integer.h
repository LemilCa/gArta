#if !defined(GARTA__INTEGER__H)
#define GARTA__INTEGER__H

////////////////////////////////////////////// Types //////////////////////////////////////////////

typedef struct gArta_Integer *gArta_Integer;

////////////////////////////////////// Function Declarations //////////////////////////////////////

gArta_Integer gArta_Integer_create(const int data);
gArta_Integer gArta_Integer_destroy(gArta_Integer integer);


int gArta_Integer_print(const gArta_Integer integer);


#endif /* !defined(GARTA__INTEGER__H) */


#if defined(GARTA__IMPLEMENTATION)

////////////////////////////////////////////// Types //////////////////////////////////////////////

struct gArta_Integer {
    int data;
};

////////////////////////////////////// Function Declarations //////////////////////////////////////

void gArta_Integer_malloc(gArta_Integer *integer_pt);


void gArta_int_print(int *print_pt, const int data);

/////////////////////////////////////// Function Definitions //////////////////////////////////////

gArta_Integer gArta_Integer_create(const int data)
{
    gArta_Integer integer; gArta_Integer_malloc(&integer);
    if (!gArta_Error_global_isNone()) { return integer; }

    integer -> data = data;

    return integer;
}
gArta_Integer gArta_Integer_destroy(gArta_Integer integer)
{
    if (integer == NULL) { return NULL; }

    GARTA__FREE(integer);

    return NULL;
}


int gArta_Integer_print(const gArta_Integer integer)
{
    int print_val = 0, print_tmp;

    if (integer == NULL) {
        print_tmp = printf("%p", NULL);
        if (print_tmp == EOF) { gArta_Error_global_set(GARTA__ERROR__PRINT); return EOF; }
        print_val += print_tmp;

        return print_val;
    }

    gArta_int_print(&print_tmp, integer -> data);
    if (!gArta_Error_global_isNone()) { return print_tmp; }
    print_val += print_tmp;

    return print_val;
}



void gArta_Integer_malloc(gArta_Integer *integer_pt)
{
    gArta_Integer integer = GARTA__MALLOC(sizeof(struct gArta_Integer));
    if (integer == NULL) { gArta_Error_global_set(GARTA__ERROR__ALLOC); *integer_pt = integer; return; }

    *integer_pt = integer; return;
}


void gArta_int_print(int *print_pt, const int data)
{
    int print_val = 0, print_tmp;

    print_tmp = printf("%d", data);
    if (print_tmp == EOF) { gArta_Error_global_set(GARTA__ERROR__PRINT); *print_pt = print_tmp; }
    print_val += print_tmp;

    *print_pt = print_val; return;
}


#endif /* defined(GARTA__IMPLEMENTATION) */