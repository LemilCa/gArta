#if !defined(GARTA__H)
#define GARTA__H

///////////////////////////////////////////// Includes ////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

///////////////////////////////////////////// Defines /////////////////////////////////////////////

#if !defined(GARTA__MALLOC)
    #define GARTA__MALLOC(_size_) malloc(_size_)
#endif /* !defined(GARTA__MALLOC) */

#if !defined(GARTA__CALLOC)
    #define GARTA__CALLOC(_nmemb_, _size_) calloc(_nmemb_, _size_)
#endif /* !defined(GARTA__CALLOC) */

#if !defined(GARTA__FREE)
    #define GARTA__FREE(_ptr_) free(_ptr_)
#endif /* !defined(GARTA__FREE) */


#if !defined(GARTA__SIZE)
    #define GARTA__SIZE int
#endif /* !defined(GARTA__SIZE) */

////////////////////////////////////////////// Types //////////////////////////////////////////////

typedef void* gArta_Data;

typedef enum {
    GARTA__ERROR__UNIMPLEMENTED = -2,
    GARTA__ERROR__UNKNOWN = -1,
    GARTA__ERROR__NONE = 0,

    GARTA__ERROR__ALLOC,
    GARTA__ERROR__PRINT,

    GARTA__ERROR__OUT_OF_BOUNDS,
} gArta_Error;

typedef enum {
    GARTA__TYPE__TEST = -2,
    GARTA__TYPE__UNKNOWN = -1,

/* Simple Types */
    GARTA__TYPE__INTEGER,
    GARTA__TYPE__BOOLEAN,
    GARTA__TYPE__CHARACTER,

/* Structures */
    GARTA__TYPE__ARRAY,
    GARTA__TYPE__LINKED_LIST,
    GARTA__TYPE__STACK,
    GARTA__TYPE__QUEUE,
    GARTA__TYPE__DOUBLE_LINKED_LIST,
/* Complex Types */

} gArta_Type;

typedef struct gArta_DataInfos gArta_DataInfos;

///////////////////////////////////////// Global Variables ////////////////////////////////////////

extern gArta_Error gArta_Error_global;

////////////////////////////////////// Function Declarations //////////////////////////////////////

int gArta_Error_print(const gArta_Error error);

gArta_Error gArta_Error_global_get(void);
void gArta_Error_global_set(const gArta_Error error);
void gArta_Error_global_reset(void);
int gArta_Error_global_print(void);
bool gArta_Error_global_isError(const gArta_Error error);
bool gArta_Error_global_isNone(void);


int gArta_Type_print(const gArta_Type type);


gArta_DataInfos gArta_DataInfos_create(const gArta_Type type, gArta_Data (*copy)(const gArta_Data), gArta_Data (*destroy)(gArta_Data), int (*print)(const gArta_Data), bool (*same)(const gArta_Data, const gArta_Data), int (*compare)(const gArta_Data, const gArta_Data));

gArta_DataInfos gArta_DataInfos_modify_type(const gArta_DataInfos source, const gArta_Type type);
gArta_DataInfos gArta_DataInfos_modify_copy(const gArta_DataInfos source, gArta_Data (*copy)(const gArta_Data));
gArta_DataInfos gArta_DataInfos_modify_destroy(const gArta_DataInfos source, gArta_Data (*destroy)(gArta_Data));
gArta_DataInfos gArta_DataInfos_modify_print(const gArta_DataInfos source, int (*print)(const gArta_Data));
gArta_DataInfos gArta_DataInfos_modify_same(const gArta_DataInfos source, bool (*same)(const gArta_Data, const gArta_Data));
gArta_DataInfos gArta_DataInfos_modify_compare(const gArta_DataInfos source, int (*compare)(const gArta_Data, const gArta_Data));

gArta_Data gArta_DataInfos_use_copy(const gArta_DataInfos dataInfos, const gArta_Data source);
gArta_Data gArta_DataInfos_use_destroy(const gArta_DataInfos dataInfos, gArta_Data data);
int gArta_DataInfos_use_print(const gArta_DataInfos dataInfos, const gArta_Data data);
bool gArta_DataInfos_use_same(const gArta_DataInfos dataInfos, const gArta_Data data_a, const gArta_Data data_b);
int gArta_DataInfos_use_compare(const gArta_DataInfos dataInfos, const gArta_Data data_a, const gArta_Data data_b);


#endif /* !defined(GARTA__H) */


#if defined(GARTA__IMPLEMENTATION)

////////////////////////////////////////////// Types //////////////////////////////////////////////

typedef struct { bool value; char* string; } gArta_bool_Strings;
typedef struct { gArta_Error value; char* string; } gArta_Error_Strings;
typedef struct { gArta_Type value; char* string; } gArta_Type_Strings;

struct gArta_DataInfos {
    gArta_Type type;
    gArta_Data (*copy)(const gArta_Data);
    gArta_Data (*destroy)(gArta_Data);
    int (*print)(const gArta_Data);
    bool (*same)(const gArta_Data, const gArta_Data);
    int (*compare)(const gArta_Data, const gArta_Data);
};

///////////////////////////////////////// Global Variables ////////////////////////////////////////

gArta_Error gArta_Error_global = GARTA__ERROR__NONE;

//////////////////////////////////////// Constant Variables ///////////////////////////////////////

const gArta_bool_Strings gArta_bool_strings [] = {
    { false, "false" },
    { true, "true" }
}; const size_t gArta_bool_strings_capacity = sizeof(gArta_bool_strings) / sizeof(gArta_bool_Strings);

const gArta_Error_Strings gArta_Error_strings [] = {
    { GARTA__ERROR__UNIMPLEMENTED, "unimplemented" },
    { GARTA__ERROR__UNKNOWN      , "unknown"       },
    { GARTA__ERROR__NONE         , "none"          },

    { GARTA__ERROR__ALLOC, "alloc" },
    { GARTA__ERROR__PRINT, "print" },

    { GARTA__ERROR__OUT_OF_BOUNDS, "out of bounds" },
}; const size_t gArta_Error_strings_capacity = sizeof(gArta_Error_strings) / sizeof(gArta_Error_Strings);


const gArta_Type_Strings gArta_Type_strings [] = {
    { GARTA__TYPE__TEST   , "test"    },
    { GARTA__TYPE__UNKNOWN, "unknown" },

    { GARTA__TYPE__INTEGER  , "integer"   },
    { GARTA__TYPE__BOOLEAN  , "boolean"   },
    { GARTA__TYPE__CHARACTER, "character" },

    { GARTA__TYPE__ARRAY             , "array"              },
    { GARTA__TYPE__LINKED_LIST       , "linked list"        },
    { GARTA__TYPE__STACK             , "stack"              },
    { GARTA__TYPE__QUEUE             , "queue"              },
    { GARTA__TYPE__DOUBLE_LINKED_LIST, "double linked list" },
}; const size_t gArta_Type_strings_capacity = sizeof(gArta_Type_strings) / sizeof(gArta_Type_Strings);

////////////////////////////////////// Function Declarations //////////////////////////////////////

char* gArta_bool_strings_get(const bool value);
char* gArta_Error_strings_get(const gArta_Error value);
char* gArta_Type_strings_get(const gArta_Type value);

/////////////////////////////////////// Function Definitions //////////////////////////////////////

int gArta_Error_print(const gArta_Error error)
{
    char* error_str = gArta_Error_strings_get(error);

    return (error_str == NULL) ?
        printf("#error{%d}", error) :
        printf("#error{%s}", error_str)
    ;
}

gArta_Error gArta_Error_global_get(void)
{
    return gArta_Error_global;
}
void gArta_Error_global_set(const gArta_Error error)
{
    gArta_Error_global = error; return;
}
void gArta_Error_global_reset(void)
{
    gArta_Error_global = GARTA__ERROR__NONE; return;
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
    return gArta_Error_global == GARTA__ERROR__NONE;
}


int gArta_Type_print(const gArta_Type type)
{
    char* type_str = gArta_Type_strings_get(type);

    return (type_str == NULL) ?
        printf("#type{%d}", type) :
        printf("#type{%s}", type_str)
    ;
}


gArta_DataInfos gArta_DataInfos_create(const gArta_Type type, gArta_Data (*copy)(const gArta_Data), gArta_Data (*destroy)(gArta_Data), int (*print)(const gArta_Data), bool (*same)(const gArta_Data, const gArta_Data), int (*compare)(const gArta_Data, const gArta_Data))
{
    return (gArta_DataInfos) {
        .type = type,
        .copy = copy,
        .destroy = destroy,
        .print = print,
        .same = same,
        .compare = compare
    };
}

gArta_DataInfos gArta_DataInfos_modify_type(const gArta_DataInfos source, const gArta_Type type)
{
    return (gArta_DataInfos) {
        .type = type,
        .copy = source.copy,
        .destroy = source.destroy,
        .print = source.print,
        .same = source.same,
        .compare = source.compare
    };
}
gArta_DataInfos gArta_DataInfos_modify_copy(const gArta_DataInfos source, gArta_Data (*copy)(const gArta_Data))
{
    return (gArta_DataInfos) {
        .type = source.type,
        .copy = copy,
        .destroy = source.destroy,
        .print = source.print,
        .same = source.same,
        .compare = source.compare
    };
}
gArta_DataInfos gArta_DataInfos_modify_destroy(const gArta_DataInfos source, gArta_Data (*destroy)(gArta_Data))
{
    return (gArta_DataInfos) {
        .type = source.type,
        .copy = source.copy,
        .destroy = destroy,
        .print = source.print,
        .same = source.same,
        .compare = source.compare
    };
}
gArta_DataInfos gArta_DataInfos_modify_print(const gArta_DataInfos source, int (*print)(const gArta_Data))
{
    return (gArta_DataInfos) {
        .type = source.type,
        .copy = source.copy,
        .destroy = source.destroy,
        .print = print,
        .same = source.same,
        .compare = source.compare
    };
}
gArta_DataInfos gArta_DataInfos_modify_same(const gArta_DataInfos source, bool (*same)(const gArta_Data, const gArta_Data))
{
    return (gArta_DataInfos) {
        .type = source.type,
        .copy = source.copy,
        .destroy = source.destroy,
        .print = source.print,
        .same = same,
        .compare = source.compare
    };
}
gArta_DataInfos gArta_DataInfos_modify_compare(const gArta_DataInfos source, int (*compare)(const gArta_Data, const gArta_Data))
{
    return (gArta_DataInfos) {
        .type = source.type,
        .copy = source.copy,
        .destroy = source.destroy,
        .print = source.print,
        .same = source.same,
        .compare = compare
    };
}

gArta_Data gArta_DataInfos_use_copy(const gArta_DataInfos dataInfos, const gArta_Data source)
{
    return dataInfos.copy(source);
}
gArta_Data gArta_DataInfos_use_destroy(const gArta_DataInfos dataInfos, gArta_Data data)
{
    return dataInfos.destroy(data);
}
int gArta_DataInfos_use_print(const gArta_DataInfos dataInfos, const gArta_Data data)
{
    return dataInfos.print(data);
}
bool gArta_DataInfos_use_same(const gArta_DataInfos dataInfos, const gArta_Data data_a, const gArta_Data data_b)
{
    return dataInfos.same(data_a, data_b);
}
int gArta_DataInfos_use_compare(const gArta_DataInfos dataInfos, const gArta_Data data_a, const gArta_Data data_b)
{
    return dataInfos.compare(data_a, data_b);
}



char* gArta_bool_strings_get(const bool value)
{
    for (size_t index = 0; index < gArta_bool_strings_capacity; ++ index) {
        if (value != gArta_bool_strings[index].value) { continue; }

        return gArta_bool_strings[index].string;
    }

    return NULL;
}
char* gArta_Error_strings_get(const gArta_Error value)
{
    for (size_t index = 0; index < gArta_Error_strings_capacity; ++ index) {
        if (value != gArta_Error_strings[index].value) { continue; }

        return gArta_Error_strings[index].string;
    }

    return NULL;
}
char* gArta_Type_strings_get(const gArta_Type value)
{
    for (size_t index = 0; index < gArta_Type_strings_capacity; ++ index) {
        if (value != gArta_Type_strings[index].value) { continue; }

        return gArta_Type_strings[index].string;
    }

    return NULL;
}


#endif /* defined(GARTA__IMPLEMENTATION) */