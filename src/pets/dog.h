#ifndef DOG_H
#define DOG_H

#include "pets.h"

typedef struct
{
    const char *name;
    int age;
    const char *color;
    PetFunctionRefTable *funcRefTable;
} Dog;

void patDog(void *self, char *response);
void createDog(Dog *dog, const char *name, int age, const char *color);

#endif // DOG_H