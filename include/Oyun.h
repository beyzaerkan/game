#ifndef OYUN_H
#define OYUN_H

#include <stdio.h>
#include <stdlib.h>
#include "Kisi.h"

struct Oyun
{
    double moneyOfTable;
    double depositedMoney;
    int round;
    int luckyNumber;
    void (*game)(struct Oyun*, Kisi*, int *, int, int);
    void (*deinitOyun)(struct Oyun*);
    Kisi (*richestPlayer)(Kisi* ,int);
};
typedef struct Oyun *Oyun;

Oyun initOyun();
void game(const Oyun, Kisi*, int *, int, int);
Kisi richestPlayer(Kisi* ,int);
void deinitOyun(const Oyun);
#endif