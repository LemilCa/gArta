#define GARTA__IMPLEMENTATION
#include "../src/gArta.h"
#include "../src/gArta-Stack.h"
#include "../test/simple.h"

#define CHECK_ERROR(_return_val_) \
    if (!gArta_Error_global_isNone()) { gArta_Error_global_print(); gArta_Error_global_reset(); printf("\n"); return (_return_val_); }


gArta_Stack main_Stack_create(const gArta_StackSize CAPACITY, gArta_DataInfos *DATA_INFOS__PT);
gArta_Stack main_Stack_destroy(gArta_Stack STACK);


int main_Stack_print(const gArta_Stack STACK);


int main()
{
    gArta_DataInfos dataInfos = gArta_Test_dataInfos();

    gArta_Stack stack = main_Stack_create(10, &dataInfos);
    main_Stack_print(stack);
    printf("\n");

    stack = main_Stack_destroy(stack);
    main_Stack_print(stack);

    return EXIT_SUCCESS;
}


gArta_Stack main_Stack_create(const gArta_StackSize CAPACITY, gArta_DataInfos *DATA_INFOS__PT)
{
    printf("stack create: ");
    gArta_Stack stack_create = gArta_Stack_create(CAPACITY, DATA_INFOS__PT);
    CHECK_ERROR(stack_create);
    printf("\n");

    printf("\t[capacity] ");
    printf("%d ", CAPACITY);
    printf("\n");

    printf("\t> ");
    printf("%p ", (void*)(stack_create));
    printf("\n");

    return stack_create;
}
gArta_Stack main_Stack_destroy(gArta_Stack STACK)
{
    printf("stack destroy: ");
    gArta_Stack stack_destroy = gArta_Stack_destroy(STACK);
    CHECK_ERROR(stack_destroy);
    printf("\n");

    printf("\t[stack] ");
    printf("%p ", (void*)(STACK));
    printf("\n");

    printf("\t> ");
    printf("%p ", (void*)(stack_destroy));
    printf("\n");

    return stack_destroy;
}


int main_Stack_print(const gArta_Stack STACK)
{
    printf("stack print: ");
    int stack_print = gArta_Stack_print(STACK);
    CHECK_ERROR(stack_print);
    printf("\n");

    printf("\t[stack] ");
    printf("%p ", (void*)(STACK));
    printf("\n");

    printf("\t> ");
    printf("%d ", stack_print);
    printf("\n");

    return stack_print;
}
