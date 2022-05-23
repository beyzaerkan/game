#ifndef DOSYA_H
#define DOSYA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Kisi.h"

struct Dosya
{
    char *fileName;
    int lengthOfFile;
    struct Dosya *(*initDosya)(char *);
    Kisi* (*readPerson)(struct Dosya *);
    int *(*readNumber)(struct Dosya *);
    void (*deinitDosya)(struct Dosya *);
};
typedef struct Dosya *Dosya;

Dosya initDosya(char *);
Kisi* readPerson(const Dosya);
int *readNumber(const Dosya);
void deinitDosya(const Dosya);

#endif
