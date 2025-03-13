#define GARTA__IMPLEMENTATION
#include "../src/gArta.h"
#include "../src/gArta-Queue.h"
#include "../test/simple.h"

#define CHECK_ERROR(_return_val_) \
    if (!gArta_Error_global_isNone()) { gArta_Error_global_print(); gArta_Error_global_reset(); printf("\n"); return (_return_val_); }


gArta_Queue main_Queue_create(const gArta_QueueSize CAPACITY, gArta_DataInfos *DATA_INFOS__PT);
gArta_Queue main_Queue_destroy(gArta_Queue QUEUE);


int main_Queue_print(const gArta_Queue QUEUE);


int main()
{
    gArta_DataInfos dataInfos = gArta_Test_dataInfos();
    
    gArta_Queue queue = main_Queue_create(10, &dataInfos);
    main_Queue_print(queue);
    printf("\n");

    queue = main_Queue_destroy(queue);
    main_Queue_print(queue);

    return EXIT_SUCCESS;
}


gArta_Queue main_Queue_create(const gArta_QueueSize CAPACITY, gArta_DataInfos *DATA_INFOS__PT)
{
    printf("queue create: ");
    gArta_Queue queue_create = gArta_Queue_create(CAPACITY, DATA_INFOS__PT);
    CHECK_ERROR(queue_create);
    printf("\n");

    printf("\t[capacity] ");
    printf("%d ", CAPACITY);
    printf("\n");

    printf("\t> ");
    printf("%p ", (void*)(queue_create));
    printf("\n");

    return queue_create;
}
gArta_Queue main_Queue_destroy(gArta_Queue QUEUE)
{
    printf("queue destroy: ");
    gArta_Queue queue_destroy = gArta_Queue_destroy(QUEUE);
    CHECK_ERROR(queue_destroy);
    printf("\n");

    printf("\t> ");
    printf("%p ", (void*)(queue_destroy));
    printf("\n");

    return queue_destroy;
}


int main_Queue_print(const gArta_Queue QUEUE)
{
    printf("queue print: ");
    int queue_print = gArta_Queue_print(QUEUE);
    CHECK_ERROR(queue_print);
    printf("\n");

    printf("\t> ");
    printf("%d ", queue_print);
    printf("\n");

    return queue_print;
}
