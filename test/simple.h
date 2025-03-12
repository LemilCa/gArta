#if !defined(GARTA__TEST)
#define GARTA__TEST

#include <time.h>

typedef struct gArta_Test { int data; } *gArta_Test;

const gArta_Test gArta_tests [] = {
    &(struct gArta_Test){ 13 },
    &(struct gArta_Test){ 786 },
    &(struct gArta_Test){ 0 },
    &(struct gArta_Test){ -5 },
    &(struct gArta_Test){ 445 },
    &(struct gArta_Test){ 56 },
    &(struct gArta_Test){ -12 },
    NULL
}; const size_t gArta_tests_capacity = sizeof(gArta_tests) / sizeof(gArta_Test);

gArta_Test gArta_Test_createDefault(void);
gArta_Test gArta_Test_createRandom(void);
gArta_Test gArta_Test_getRandom(void);

gArta_Data gArta_Test_copy(const gArta_Data source_dt);
gArta_Data gArta_Test_destroy(gArta_Data test_dt);
int gArta_Test_print(const gArta_Data test_dt);
bool gArta_Test_same(const gArta_Data test_a_dt, const gArta_Data test_b_dt);
int gArta_Test_compare(const gArta_Data test_a_dt, const gArta_Data test_b_dt);

gArta_DataInfos gArta_Test_dataInfos(void);



gArta_Test gArta_Test_createDefault(void)
{
    return &(struct gArta_Test){ 0 };
}
gArta_Test gArta_Test_createRandom(void)
{
    srand(time(NULL));

    return &(struct gArta_Test){ rand() % 1000 - 500 };
}
gArta_Test gArta_Test_getRandom(void)
{
    srand(time(NULL));

    return gArta_tests[rand() % gArta_tests_capacity];
}

gArta_Data gArta_Test_copy(const gArta_Data source_dt)
{
    gArta_Test source = (gArta_Test)(source_dt);
    if (source == NULL) { return NULL; }

    gArta_Test test = GARTA__MALLOC(sizeof(struct gArta_Test));
    if (test == NULL) { return NULL; }
    test -> data = source -> data;

    return (gArta_Data)(test);
}
gArta_Data gArta_Test_destroy(gArta_Data test_dt)
{
    gArta_Test test = (gArta_Test)(test_dt);
    if (test == NULL) { return NULL; }

    GARTA__FREE(test);

    return NULL;
}
int gArta_Test_print(const gArta_Data test_dt)
{
    gArta_Test test = (gArta_Test)(test_dt);
    if (test == NULL) { return printf("*"); }

    return printf("%d", test -> data);
}
bool gArta_Test_same(const gArta_Data test_a_dt, const gArta_Data test_b_dt)
{
    gArta_Test test_a = (gArta_Test)(test_a_dt);
    gArta_Test test_b = (gArta_Test)(test_b_dt);
    if (test_a == test_b) { return true; }
    if (test_a == NULL || test_b == NULL) { return false; }

    return test_a -> data == test_b -> data;
}
int gArta_Test_compare(const gArta_Data test_a_dt, const gArta_Data test_b_dt)
{
    gArta_Test test_a = (gArta_Test)(test_a_dt);
    gArta_Test test_b = (gArta_Test)(test_b_dt);
    if (test_a == test_b) { return 0; }
    if (test_a == NULL) { return 1; }
    if (test_b == NULL) { return -1; }

    if (test_a -> data < test_b -> data) { return -1; }
    if (test_a -> data > test_b -> data) { return 1; }
    return 0;
}

gArta_DataInfos gArta_Test_dataInfos(void)
{
    return gArta_DataInfos_create(
        GARTA__TYPE__TEST,
        gArta_Test_copy,
        gArta_Test_destroy,
        gArta_Test_print,
        gArta_Test_same,
        gArta_Test_compare
    );
}

#endif /* !defined(GARTA__TEST) */