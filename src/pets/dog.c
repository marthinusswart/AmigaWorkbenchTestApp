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

    dog->name = name;
    dog->age = age;
    dog->color = color;

    // Initialize function reference table
    dog->funcRefTable = (PetFunctionRefTable *)malloc(sizeof(PetFunctionRefTable));
    if (dog->funcRefTable)
    {
        dog->funcRefTable->patAnimal = patDog;
    }
}