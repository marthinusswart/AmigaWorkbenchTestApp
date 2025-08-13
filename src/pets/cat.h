#ifndef CAT_H
#define CAT_H

#include "pets.h"

typedef struct
{
    const char *name;
    int age;
    const char *color;
    PetFunctionRefTable *funcRefTable;
} Cat;

void patCat(void *self, char *response);
void createCat(Cat *cat, const char *name, int age, const char *color);

#endif // CAT_H