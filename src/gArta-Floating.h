#if !defined(GARTA__FLOATING__H)
#define GARTA__FLOATING__H

////////////////////////////////////////////// Types //////////////////////////////////////////////

typedef struct gArta_Floating *gArta_Floating;

////////////////////////////////////// Function Declarations //////////////////////////////////////

gArta_Floating gArta_Floating_create(const float data);
gArta_Floating gArta_Floating_destroy(gArta_Floating floating);


int gArta_Floating_print(const gArta_Floating floating);


#endif /* !defined(GARTA__FLOATING__H) */


#if defined(GARTA__IMPLEMENTATION)

////////////////////////////////////////////// Types //////////////////////////////////////////////

struct gArta_Floating {
    float data;
};

////////////////////////////////////// Function Declarations //////////////////////////////////////

void gArta_Floating_malloc(gArta_Floating *floating_pt);


void gArta_float_print(int *print_pt, const float data);

/////////////////////////////////////// Function Definitions //////////////////////////////////////

gArta_Floating gArta_Floating_create(const float data)
{
    gArta_Floating floating; gArta_Floating_malloc(&floating);
    if (!gArta_Error_global_isNone()) { return floating; }

    floating -> data = data;

    return floating;
}
gArta_Floating gArta_Floating_destroy(gArta_Floating floating)
{
    if (floating == NULL) { return NULL; }

    GARTA__FREE(floating);

    return NULL;
}


int gArta_Floating_print(const gArta_Floating floating)
{
    int print_val = 0, print_tmp;

    if (floating == NULL) {
        print_tmp = printf("%p", NULL);
        if (print_tmp == EOF) { gArta_Error_global_set(GARTA__ERROR__PRINT); return EOF; }
        print_val += print_tmp;

        return print_val;
    }

    gArta_float_print(&print_tmp, floating -> data);
    if (!gArta_Error_global_isNone()) { return print_tmp; }
    print_val += print_tmp;

    return print_val;
}



void gArta_Floating_malloc(gArta_Floating *floating_pt)
{
    gArta_Floating floating = GARTA__MALLOC(sizeof(struct gArta_Floating));
    if (floating == NULL) { gArta_Error_global_set(GARTA__ERROR__ALLOC); *floating_pt = NULL; return; }

    *floating_pt = floating; return;
}


void gArta_float_print(int *print_pt, const float data)
{
    int print_val = 0, print_tmp;

    print_tmp = printf("%f", data);
    if (print_tmp == EOF) { gArta_Error_global_set(GARTA__ERROR__PRINT); *print_pt = print_tmp; }
    print_val += print_tmp;

    *print_pt = print_val; return;
}


#endif /* !defined(GARTA__IMPLEMENTATION) */