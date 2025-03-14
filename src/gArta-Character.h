#if !defined(GARTA__CHARACTER__H)
#define GARTA__CHARACTER__H

////////////////////////////////////////////// Types //////////////////////////////////////////////

typedef struct gArta_Character *gArta_Character;

////////////////////////////////////// Function Declarations //////////////////////////////////////

gArta_Character gArta_Character_create(const char data);
gArta_Character gArta_Character_destroy(gArta_Character character);


int gArta_Character_print(const gArta_Character character);


#endif /* !defined(GARTA__CHARACTER__H) */


#if defined(GARTA__IMPLEMENTATION)

////////////////////////////////////////////// Types //////////////////////////////////////////////

struct gArta_Character {
    char data;
};

////////////////////////////////////// Function Declarations //////////////////////////////////////

void gArta_Character_malloc(gArta_Character *character_pt);


void gArta_char_print(int *print_pt, const char data);

/////////////////////////////////////// Function Definitions //////////////////////////////////////

gArta_Character gArta_Character_create(const char data)
{
    gArta_Character character; gArta_Character_malloc(&character);
    if (!gArta_Error_global_isNone()) { return character; }

    character -> data = data;

    return character;
}
gArta_Character gArta_Character_destroy(gArta_Character character)
{
    if (character == NULL) { return NULL; }

    GARTA__FREE(character);

    return NULL;
}


int gArta_Character_print(const gArta_Character character)
{
    int print_val = 0, print_tmp;

    if (character == NULL) {
        print_tmp = printf("%p", NULL);
        if (print_tmp == EOF) { gArta_Error_global_set(GARTA__ERROR__PRINT); return EOF; }
        print_val += print_tmp;

        return print_val;
    }

    gArta_char_print(&print_tmp, character -> data);
    if (!gArta_Error_global_isNone()) { return print_tmp; }
    print_val += print_tmp;

    return print_val;
}



void gArta_Character_malloc(gArta_Character *character_pt)
{
    gArta_Character character = GARTA__MALLOC(sizeof(struct gArta_Character));
    if (character == NULL) { gArta_Error_global_set(GARTA__ERROR__ALLOC); *character_pt = NULL; return; }

    *character_pt = character; return;
}


void gArta_char_print(int *print_pt, const char data)
{
    int print_val = 0, print_tmp;

    print_tmp = printf("%c", data);
    if (print_tmp == EOF) { gArta_Error_global_set(GARTA__ERROR__PRINT); *print_pt = print_tmp; }
    print_val += print_tmp;

    *print_pt = print_val; return;
}


#endif /* defined(GARTA__IMPLEMENTATION) */