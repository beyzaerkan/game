#include "Dosya.h"
#include "Kisi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Dosya initDosya(char *file)
{
  Dosya this;
  this = (Dosya)malloc(sizeof(struct Dosya));
  this->fileName = file;
  this->lengthOfFile = 0;
  this->readPerson = &readPerson;
  this->readNumber = &readNumber;
  this->deinitDosya = &deinitDosya;
  return this;
}

// kisiler dosyasini okur
Kisi *readPerson(const Dosya this)
{
  FILE *file = fopen(this->fileName, "r");

  // dosyayi bulamadigi durum
  if (file == NULL)
  {
    printf("File not found\n");
    exit(1);
  }

  char line[50];

  int count = 0;

  // dosyanin uzunlugunu bulur
  while (fgets(line, 50, file))
  {
    count++;
  }

  this->lengthOfFile = count; // dosyanin uzunlugunu sayaca esitler
  fclose(file);

  file = fopen(this->fileName, "r");

  Kisi *list = malloc(sizeof(struct Kisi) * count); // liste icin dosyanin uzunlugu kadar yer ayirir
  int j = 0;

  // dosyayi tekrardan okur
  while (fgets(line, 50, file))
  {
    Kisi kisi = initKisi();
    char *token;
    token = strtok(line, "#"); // satiri '#' karakterine gore ayirir
    int i = 0;
    while (token != NULL)
    {
      if (i == 0)
        strcpy(kisi->name, token);
      if (i == 1)
        kisi->money = atof(token);
      if (i == 2)
        kisi->ratio = atof(token);
      if (i == 3)
        kisi->number = atoi(token);
      token = strtok(NULL, "#");
      i++;
    }

    list[j] = kisi; // kisiyi listeye sirayla atar
    j++;
  }
  fclose(file);

  return list;
}

// sayilar dosyasini okur
int *readNumber(const Dosya this)
{
  FILE *file = fopen(this->fileName, "r");
  if (file == NULL)
  {
    printf("File not found\n");
    exit(1);
  }
  char line[4];
  int k = 0;
  int count = 0;

  // dosyanin uzunlugunu bulur
  while (fgets(line, 4, file))
  {
    count++;
  }
  this->lengthOfFile = count; // dosyanin uzunlugunu sayaca esitler

  fclose(file);

  file = fopen(this->fileName, "r");
  int *numbers = (int *)malloc((count - 1) * sizeof(int)); // liste icin dosyanin uzunlugu kadar yer ayirir

  while (fgets(line, 4, file))
  {
    numbers[k] = atoi(line); // okunan sayilari numbers adli diziye atar
    k++;
  }

  fclose(file);
  return numbers;
}

//  dosya yapisinin yikici fonksiyonu
void deinitDosya(const Dosya this)
{
  if (this == NULL)
    return;
  free(this);
}
