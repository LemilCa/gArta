#define GARTA__IMPLEMENTATION
#include "../src/gArta.h"


int main_Error_print(const gArta_Error ERROR);

gArta_Error main_Error_global_get(void);
void main_Error_global_set(const gArta_Error ERROR);
void main_Error_global_reset(void);
int main_Error_global_print(void);
bool main_Error_global_isError(const gArta_Error ERROR);
bool main_Error_global_isNone(void);


int main_Type_print(const gArta_Type TYPE);


int main()
{
    main_Error_global_set(GARTA__ERROR__ALLOC);
    main_Error_global_print();
    printf("\n");

    main_Error_global_get();
    main_Error_global_reset();
    main_Error_global_print();
    printf("\n");

    main_Error_global_isNone();
    main_Error_global_isError(GARTA__ERROR__UNIMPLEMENTED);
    
    return EXIT_SUCCESS;
}


int main_Error_print(const gArta_Error ERROR)
{
    int Error_print_val;
    printf("error print: ");
    Error_print_val = gArta_Error_print(ERROR);
    printf("\n");

    printf("\t[error] ");
    printf("(%d) ", ERROR);
    char* error_str = gArta_Error_strings_get(ERROR);
    if (error_str != NULL) { printf("\"%s\"", error_str); }
    printf("\n");

    printf("\t> ");
    printf("%d", Error_print_val);
    printf("\n");

    return Error_print_val;
}

gArta_Error main_Error_global_get(void)
{
    gArta_Error Error_global_get_val;

    printf("error global get: ");
    Error_global_get_val = gArta_Error_global_get();
    printf("\n");

    printf("\t> ");
    char* return_str = gArta_Error_strings_get(Error_global_get_val);
    if (return_str != NULL) { printf("\"%s\" ", return_str); }
    printf("(%d) ", Error_global_get_val);
    printf("\n");

    return Error_global_get_val;
}
void main_Error_global_set(const gArta_Error ERROR)
{
    printf("error global set: ");
    gArta_Error_global_set(ERROR);
    printf("\n");

    printf("\t[error]: ");
    char* error_str = gArta_Error_strings_get(ERROR);
    if (error_str != NULL) { printf("\"%s\" ", error_str); }
    printf("(%d) ", ERROR);
    printf("\n");

    return;
}
void main_Error_global_reset(void)
{
    printf("error global reset: ");
    gArta_Error_global_reset();
    printf("\n");

    return;
}
int main_Error_global_print(void)
{
    int Error_global_print_val;

    printf("error global print: ");
    Error_global_print_val = gArta_Error_global_print();
    printf("\n");

    printf("\t> ");
    printf("%d ", Error_global_print_val);
    printf("\n");

    return Error_global_print_val;
}
bool main_Error_global_isError(const gArta_Error ERROR)
{
    bool Error_global_isError_val;
    
    printf("error global isError: ");
    Error_global_isError_val = gArta_Error_global_isError(ERROR);
    printf("\n");

    printf("\t> ");
    char* return_str = gArta_bool_strings_get(Error_global_isError_val);
    if (return_str != NULL) { printf("%s ", return_str); }
    printf("(%d) ", Error_global_isError_val);
    printf("\n");

    return Error_global_isError_val;
}
bool main_Error_global_isNone(void)
{
    bool Error_global_isNone_val;
    
    printf("error global isNone: ");
    Error_global_isNone_val = gArta_Error_global_isNone();
    printf("\n");

    printf("\t> ");
    char* return_str = gArta_bool_strings_get(Error_global_isNone_val);
    if (return_str != NULL) { printf("%s ", return_str); }
    printf("(%d) ", Error_global_isNone_val);
    printf("\n");

    return Error_global_isNone_val;
}


int main_Type_print(const gArta_Type TYPE)
{
    int Type_print_val;
    printf("type print: ");
    Type_print_val = gArta_Type_print(TYPE);
    printf("\n");

    printf("\t[type] ");
    printf("(%d) ", TYPE);
    char* type_str = gArta_Type_strings_get(TYPE);
    if (type_str != NULL) { printf("\"%s\"", type_str); }
    printf("\n");

    printf("\t> ");
    printf("%d", Type_print_val);
    printf("\n");

    return Type_print_val;
}
