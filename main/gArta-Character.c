#define GARTA__IMPLEMENTATION
#include "../src/gArta.h"
#include "../src/gArta-Character.h"

#define CHECK_ERROR(_return_val_) \
    if (!gArta_Error_global_isNone()) { gArta_Error_global_print(); gArta_Error_global_reset(); printf("\n"); return (_return_val_); }


gArta_Character main_Character_create(const char DATA);
gArta_Character main_Character_destroy(gArta_Character CHARACTER);


int main_Character_print(const gArta_Character CHARACTER);


int main()
{
    gArta_Character character = main_Character_create('p');
    main_Character_print(character);
    printf("\n");

    character = main_Character_destroy(character);
    main_Character_print(character);

    return EXIT_SUCCESS;
}


gArta_Character main_Character_create(const char DATA)
{
    printf("character create: ");
    gArta_Character character_create = gArta_Character_create(DATA);
    CHECK_ERROR(character_create);
    printf("\n");

    printf("\t[data]: ");
    printf("%c ", DATA);
    printf("\n");

    printf("\t> ");
    printf("%p ", (void*)(character_create));
    printf("\n");

    return character_create;
}
gArta_Character main_Character_destroy(gArta_Character CHARACTER)
{
    printf("character destroy: ");
    gArta_Character character_destroy = gArta_Character_destroy(CHARACTER);
    CHECK_ERROR(character_destroy);
    printf("\n");

    printf("\t[character] ");
    printf("%p ", (void*)(CHARACTER));
    printf("\n");

    printf("\t> ");
    printf("%p ", (void*)(character_destroy));
    printf("\n");

    return character_destroy;
}


int main_Character_print(const gArta_Character CHARACTER)
{
    printf("character print: ");
    int character_print = gArta_Character_print(CHARACTER);
    CHECK_ERROR(character_print);
    printf("\n");

    printf("\t[character] ");
    printf("%p ", (void*)(CHARACTER));
    printf("\n");

    printf("\t> ");
    printf("%d ", character_print);
    printf("\n");

    return character_print;
}
