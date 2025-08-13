#ifndef PETS_H
#define PETS_H

typedef struct
{
    void (*patAnimal)(void *self, char *response);
} PetFunctionRefTable;

// extern void patAnimal(void *self, char *response);
#endif // PETS_H