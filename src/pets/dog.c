#include "dog.h"
#include <clib/alib_protos.h>

void patDog(void *self, char *response)
{
    Dog *dog = (Dog *)self;
    strcpy(response, dog->name);
    strcat(response, " says Woof!");
}

void createDog(Dog *dog, const char *name, int age, const char *color)
{
    if (dog == NULL)
    {
        return; // Handle error: invalid parameters
    }

    dog->name = malloc(strlen(name) + 1);
    dog->age = age;
    dog->color = malloc(strlen(color) + 1);

    if (dog->name)
    {
        strcpy((char *)dog->name, name);
    }

    if (dog->color)
    {
        strcpy((char *)dog->color, color);
    }

    // Initialize function reference table
    dog->funcRefTable = (PetFunctionRefTable *)malloc(sizeof(PetFunctionRefTable));
    if (dog->funcRefTable)
    {
        dog->funcRefTable->patAnimal = patDog;
    }
}