#define FILE_TO_EXECUTE "main/gArta-Floating.c"


#if defined(FILE_TO_EXECUTE)
    #include FILE_TO_EXECUTE
#endif /* defined(FILE_TO_EXECUTE) */


#if !defined(FILE_TO_EXECUTE)

#define GARTA__IMPLEMENTATION
#include "src/gArta.h"
#include "test/simple.h"


int main()
{
    printf("hello world!\n");
    
    return EXIT_SUCCESS;
}


#endif /* !defined(FILE_TO_EXECUTE) */