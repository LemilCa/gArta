#define GARTA__IMPLEMENTATION
#include "../src/gArta.h"
#include "../src/gArta-Floating.h"

#define CHECK_ERROR(_return_val_) \
    if (!gArta_Error_global_isNone()) { gArta_Error_global_print(); gArta_Error_global_reset(); printf("\n"); return (_return_val_); }


gArta_Floating main_Floating_create(const float DATA);
gArta_Floating main_Floating_destroy(gArta_Floating FLOATING);


int main_Floating_print(const gArta_Floating FLOATING);


int main()
{
    gArta_Floating floating = main_Floating_create(58.3f);
    main_Floating_print(floating);
    printf("\n");

    floating = main_Floating_destroy(floating);
    main_Floating_print(floating);

    return EXIT_SUCCESS;
}


gArta_Floating main_Floating_create(const float DATA)
{
    printf("floating create: ");
    gArta_Floating floating_create = gArta_Floating_create(DATA);
    CHECK_ERROR(floating_create);
    printf("\n");

    printf("\t[data]: ");
    printf("%f ", DATA);
    printf("\n");

    printf("\t> ");
    printf("%p ", (void*)(floating_create));
    printf("\n");

    return floating_create;
}
gArta_Floating main_Floating_destroy(gArta_Floating FLOATING)
{
    printf("floating destroy: ");
    gArta_Floating floating_destroy = gArta_Floating_destroy(FLOATING);
    CHECK_ERROR(floating_destroy);
    printf("\n");

    printf("\t[floating] ");
    printf("%p ", (void*)(floating_destroy));
    printf("\n");

    printf("\t> ");
    printf("%p ", (void*)(floating_destroy));
    printf("\n");

    return floating_destroy;
}


int main_Floating_print(const gArta_Floating FLOATING)
{
    printf("floating print: ");
    int floating_print = gArta_Floating_print(FLOATING);
    CHECK_ERROR(floating_print);
    printf("\n");

    printf("\t[floating] ");
    printf("%p ", (void*)(FLOATING));
    printf("\n");

    printf("\t> ");
    printf("%d ", floating_print);
    printf("\n");

    return floating_print;
}

