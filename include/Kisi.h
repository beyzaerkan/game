#ifndef KISI_H
#define KISI_H

#include <stdio.h>
#include <stdlib.h>

struct Kisi
{
    char *name;
    double money;
    double ratio;
    int number;
    void (*deinitKisi)(struct Kisi *);
};

typedef struct Kisi *Kisi;

Kisi initKisi();
void deinitKisi(const Kisi);

#endif