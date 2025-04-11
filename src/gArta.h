#if !defined(GARTA_H_)
#define GARTA_H_

#include <stdio.h>
#include <stdlib.h>

#if !defined(GARTADEF)
    #define GARTADEF static inline
#endif /* !defined(GARTADEF) */


GARTADEF void gArta_helloWorld(void);

#endif /* !defined(GARTA_H_) */



#if defined(GARTA_IMPLEMENTATION)

GARTADEF void gArta_helloWorld(void)
{
    printf("gArta: hello world!\n");
    return;
}

#endif /* defined(GARTA_IMPLEMENTATION) */