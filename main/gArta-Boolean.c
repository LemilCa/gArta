#define GARTA__IMPLEMENTATION
#include "../src/gArta.h"
#include "../src/gArta-Boolean.h"

#define CHECK_ERROR(_return_val_) \
    if (!gArta_Error_global_isNone()) { gArta_Error_global_print(); gArta_Error_global_reset(); printf("\n"); return (_return_val_); }


gArta_Boolean main_Boolean_create(const bool DATA);
gArta_Boolean main_Boolean_destroy(gArta_Boolean BOOLEAN);


int main_Boolean_print(const gArta_Boolean BOOLEAN);


int main()
{
    gArta_Boolean boolean = main_Boolean_create(true);
    main_Boolean_print(boolean);
    printf("\n");

    boolean = main_Boolean_destroy(boolean);
    main_Boolean_create(boolean);

    return EXIT_SUCCESS;
}


gArta_Boolean main_Boolean_create(const bool DATA)
{
    printf("boolean create: ");
    gArta_Boolean boolean_create = gArta_Boolean_create(DATA);
    CHECK_ERROR(boolean_create);
    printf("\n");

    printf("\t[data]: ");
    printf("%d ", DATA);
    printf("\n");

    printf("\t> ");
    printf("%p ", (void*)(boolean_create));
    printf("\n");

    return boolean_create;
}
gArta_Boolean main_Boolean_destroy(gArta_Boolean BOOLEAN)
{
    printf("boolean destroy: ");
    gArta_Boolean boolean_destroy = gArta_Boolean_destroy(BOOLEAN);
    CHECK_ERROR(boolean_destroy);
    printf("\n");

    printf("\t[integer] ");
    printf("%p ", (void*)(boolean_destroy));
    printf("\n");

    return boolean_destroy;
}


int main_Boolean_print(const gArta_Boolean BOOLEAN)
{
    printf("boolean print: ");
    int boolean_print = gArta_Boolean_print(BOOLEAN);
    CHECK_ERROR(boolean_print);
    printf("\n");

    printf("\t[boolean] ");
    printf("%p ", (void*)(BOOLEAN));
    printf("\n");

    return boolean_print;
}
