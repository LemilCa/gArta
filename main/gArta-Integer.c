#define GARTA__IMPLEMENTATION
#include "../src/gArta.h"
#include "../src/gArta-Integer.h"

#define CHECK_ERROR(_return_val_) \
    if (!gArta_Error_global_isNone()) { gArta_Error_global_print(); gArta_Error_global_reset(); printf("\n"); return (_return_val_); }


gArta_Integer main_Integer_create(const int DATA);
gArta_Integer main_Integer_destroy(gArta_Integer INTEGER);


int main_Integer_print(const gArta_Integer INTEGER);


int main()
{
    gArta_Integer integer = main_Integer_create(18);
    main_Integer_print(integer);

    integer = gArta_Integer_destroy(integer);
    main_Integer_print(integer);

    return EXIT_SUCCESS;
}


gArta_Integer main_Integer_create(const int DATA)
{
    printf("integer create: ");
    gArta_Integer integer_create = gArta_Integer_create(DATA);
    CHECK_ERROR(integer_create);
    printf("\n");

    printf("\t[data]: ");
    printf("%d ", DATA);
    printf("\n");

    printf("\t> ");
    printf("%p ", (void*)(integer_create));

    return integer_create;
}
gArta_Integer main_Integer_destroy(gArta_Integer INTEGER)
{
    printf("integer destroy: ");
    gArta_Integer integer_destroy = gArta_Integer_destroy(INTEGER);
    CHECK_ERROR(integer_destroy);
    printf("\n");

    printf("\t[integer] ");
    printf("%p ", (void*)(INTEGER));
    printf("\n");

    printf("\t> ");
    printf("%p ", (void*)(integer_destroy));
    printf("\n");

    return integer_destroy;
}


int main_Integer_print(const gArta_Integer INTEGER)
{
    printf("integer destroy: ");
    int integer_print = gArta_Integer_print(INTEGER);
    CHECK_ERROR(integer_print);
    printf("\n");

    printf("\t[integer] ");
    printf("%p ", (void*)(INTEGER));
    printf("\n");

    printf("\t> ");
    printf("%d ", integer_print);
    printf("\n");

    return integer_print;
}

