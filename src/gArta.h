#if !defined(GARTA_H_)
#define GARTA_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#if !defined(GARTADEF)
    #define GARTADEF static inline
#endif /* !defined(GARTADEF) */

#if !defined(GARTA_MALLOC)
    #define GARTA_MALLOC(_size_) malloc(_size_)
#endif /* !defined(GARTA_MALLOC) */
#if !defined(GARTA_FREE)
    #define GARTA_FREE(_ptr_) free(_ptr_)
#endif /* !defined(GARTA_FREE) */
#if !defined(GARTA_CALLOC)
    #define GARTA_CALLOC(_nmemb_, _size_) calloc(_nmemb_, _size_)
#endif  /* !defined(GARTA_CALLOC) */
#if !defined(GARTA_REALLOC)
    #define GARTA_REALLOC(_ptr_, _size_) realloc(_ptr_, _size_)
#endif /* !defined(GARTA_REALLOC) */


typedef void* gArta_Data;

typedef enum {
    GARTA_ERROR_UNIMPLEMENTED = -2,
    GARTA_ERROR_UNKNOWN = -1,
    GARTA_ERROR_NONE = 0,
} gArta_Error;

typedef enum {
    GARTA_TYPE_TEST = -2,
    GARTA_TYPE_UNKNOWN = -1,

/* Simple Types */
    GARTA_TYPE_INTEGER,
} gArta_Type;


GARTADEF void gArta_helloWorld(void);

int gArta_Error_print(const gArta_Error error);
int gArta_Type_print(const gArta_Type type);

extern gArta_Error gArta_Error_global;
gArta_Error gArta_Error_global_get(void);
void gArta_Error_global_set(const gArta_Error error);
void gArta_Error_global_reset(void);
int gArta_Error_global_print(void);
bool gArta_Error_global_isError(const gArta_Error error);
bool gArta_Error_global_isNone(void);


#endif /* !defined(GARTA_H_) */



#if defined(GARTA_IMPLEMENTATION)

typedef struct { gArta_Error value; char* string; } gArta_Error_Strings;
const gArta_Error_Strings GARTA_ERROR_STRINGS[] = {
    { GARTA_ERROR_UNIMPLEMENTED, "unimplemented" },
    { GARTA_ERROR_UNKNOWN      , "unknown"       },
    { GARTA_ERROR_NONE         , "none"          },
}; const size_t GARTA_ERROR_STRINGS_CAPACITY = sizeof(GARTA_ERROR_STRINGS) / sizeof(gArta_Error_Strings);
char *gArta_Error_strings_get(const gArta_Error value);

typedef struct { gArta_Type value; char* string; } gArta_Type_Strings;
const gArta_Type_Strings GARTA_TYPE_STRINGS[] = {
    { GARTA_TYPE_TEST   , "test"    },
    { GARTA_TYPE_UNKNOWN, "unknown" },

    { GARTA_TYPE_INTEGER, "integer" },
}; const size_t GARTA_TYPE_STRINGS_CAPACITY = sizeof(GARTA_TYPE_STRINGS) / sizeof(gArta_Type_Strings);
char *gArta_Type_strings_get(const gArta_Type value);


GARTADEF void gArta_helloWorld(void)
{
    printf("gArta: hello world!\n");
    return;
}

int gArta_Error_print(const gArta_Error error)
{
    char* error_str;
    return ((error_str = gArta_Error_strings_get(error)) == NULL) ?
        printf("#error{%d}", error) : printf("#error{%s}", error_str)
    ;
}
int gArta_Type_print(const gArta_Type type)
{
    char* type_str;
    return ((type_str = gArta_Type_strings_get(type)) == NULL) ?
        printf("#type{%d}", type) : printf("#type{%s}", type_str)
    ;
}

gArta_Error gArta_Error_global = GARTA_ERROR_NONE;
gArta_Error gArta_Error_global_get(void)
{
    return gArta_Error_global;
}
void gArta_Error_global_set(const gArta_Error error)
{
    gArta_Error_global = error;
    return;
}
void gArta_Error_global_reset(void)
{
    gArta_Error_global = GARTA_ERROR_NONE;
    return;
}
int gArta_Error_global_print(void)
{
    return gArta_Error_print(gArta_Error_global);
}
bool gArta_Error_global_isError(const gArta_Error error)
{
    return gArta_Error_global == error;
}
bool gArta_Error_global_isNone(void)
{
    return gArta_Error_global == GARTA_ERROR_NONE;
}

char *gArta_Error_strings_get(const gArta_Error value)
{
    for (size_t index = 0; index < GARTA_ERROR_STRINGS_CAPACITY; ++index) {
        if (value != GARTA_ERROR_STRINGS[index].value) { continue; }
        return GARTA_ERROR_STRINGS[index].string;
    } return NULL;
}
char *gArta_Type_strings_get(const gArta_Type value)
{
    for (size_t index = 0; index < GARTA_TYPE_STRINGS_CAPACITY; ++index) {
        if (value != GARTA_TYPE_STRINGS[index].value) { continue; }
        return GARTA_TYPE_STRINGS[index].string;
    } return NULL;
}

#endif /* defined(GARTA_IMPLEMENTATION) */