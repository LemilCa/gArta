#if !defined(GARTA__BOOLEAN__H)
#define GARTA__BOOLEAN__H

////////////////////////////////////////////// Types //////////////////////////////////////////////

typedef struct gArta_Boolean *gArta_Boolean;

////////////////////////////////////// Function Declarations //////////////////////////////////////

gArta_Boolean gArta_Boolean_create(const bool data);
gArta_Boolean gArta_Boolean_destroy(gArta_Boolean boolean);


int gArta_Boolean_print(const gArta_Boolean boolean);


#endif /* !defined(GARTA__BOOLEAN__H) */


#if defined(GARTA__IMPLEMENTATION)

////////////////////////////////////////////// Types //////////////////////////////////////////////

struct gArta_Boolean {
    bool data;
};

////////////////////////////////////// Function Declarations //////////////////////////////////////

void gArta_Boolean_malloc(gArta_Boolean *boolean_pt);


void gArta_bool_print(int *print_pt, const bool data);

/////////////////////////////////////// Function Definitions //////////////////////////////////////

gArta_Boolean gArta_Boolean_create(const bool data)
{
    gArta_Boolean boolean; gArta_Boolean_malloc(&boolean);
    if (!gArta_Error_global_isNone()) { return boolean; }

    boolean -> data = data;

    return boolean;
}
gArta_Boolean gArta_Boolean_destroy(gArta_Boolean boolean)
{
    if (boolean == NULL) { return NULL; }

    GARTA__FREE(boolean);

    return NULL;
}


int gArta_Boolean_print(const gArta_Boolean boolean)
{
    int print_val = 0, print_tmp;

    if (boolean == NULL) {
        print_tmp = printf("%p", NULL);
        if (print_tmp == EOF) { gArta_Error_global_set(GARTA__ERROR__PRINT); return EOF; }
        print_val += print_tmp;

        return print_val;
    }

    gArta_bool_print(&print_tmp, boolean -> data);
    if (!gArta_Error_global_isNone()) { return print_tmp; }
    print_val += print_tmp;

    return print_val;
}



void gArta_Boolean_malloc(gArta_Boolean *boolean_pt)
{
    gArta_Boolean boolean = GARTA__MALLOC(sizeof(struct gArta_Boolean));
    if (boolean == NULL) { gArta_Error_global_set(GARTA__ERROR__ALLOC); *boolean_pt = NULL; return; }

    *boolean_pt = boolean; return;
}


void gArta_bool_print(int *print_pt, const bool data)
{
    int print_val = 0, print_tmp;

    print_tmp = printf("%d", data);
    if (print_tmp == EOF) { gArta_Error_global_set(GARTA__ERROR__PRINT); *print_pt = print_tmp; }
    print_val += print_tmp;

    *print_pt = print_val; return;
}


#endif /* defined(GARTA__IMPLEMENTATION) */