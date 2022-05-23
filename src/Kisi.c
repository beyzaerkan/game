#include "Kisi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Kisi initKisi()
{
  Kisi this;
  this = (Kisi)malloc(sizeof(struct Kisi));
  this->name = malloc(30 * sizeof(char));
  this->money = 0;
  this->ratio = 0;
  this->number = 0;
  this->deinitKisi = &deinitKisi;
}

//  kisi yapisinin yikici fonksiyonu
void deinitKisi(const Kisi this)
{
  if (this == NULL)
    return;
  free(this);
}