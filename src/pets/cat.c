#include "cat.h"
#include <clib/alib_protos.h>

void patCat(void *self, char *response)
{
    Cat *cat = (Cat *)self;
    strcpy(response, cat->name);
    strcat(response, " says Meow!");
}

void createCat(Cat *cat, const char *name, int age, const char *color)
{
    if (cat == NULL)
    {
        return;
    }

    cat->name = name;
    cat->age = age;
    cat->color = color;

    // Initialize function reference table
    cat->funcRefTable = (PetFunctionRefTable *)malloc(sizeof(PetFunctionRefTable));
    if (cat->funcRefTable)
    {
        cat->funcRefTable->patAnimal = patCat;
    }
}