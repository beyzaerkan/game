#include "Oyun.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

Oyun initOyun()
{
  Oyun this;
  this = (Oyun)malloc(sizeof(struct Oyun));
  this->moneyOfTable = 0;
  this->depositedMoney = 0;
  this->round = 0;
  this->luckyNumber = 0;
  this->game = &game;
  this->richestPlayer = &richestPlayer;
  this->deinitOyun = &deinitOyun;
  return this;
}

// kursorun pozisyonunu belirlemek icin kullanilir
void gotoxy(int x, int y)
{
  COORD CRD;
  CRD.X = x;
  CRD.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CRD);
}

// dizideki en zengin kisiyi bulur
Kisi richestPlayer(Kisi *this, int playersLength)
{
  Kisi richestPlayer;
  richestPlayer = this[0]; // zengin kisinin ilk eleman oldugunu varsayar
  int i = 0;
  // listenin icinde dolasir
  while (i < playersLength - 1)
  {
    // eger zengin kisinin parasi ilk kisinin parasindan kucukse zengin kisi artik bir sonraki kisidir
    if (richestPlayer->money < this[i + 1] -> money)
    {
      richestPlayer = this[i + 1];
    }
    i++;
  }

  return richestPlayer;
}

void game(const Oyun this, Kisi *list, int *numbers, int numbersLength, int playersLength)
{
  Kisi kisi = initKisi(), rich = initKisi();

  // sayilar dizisi icinde dolasir
  for (int i = 0; i < numbersLength; i++)
  {
    this->luckyNumber = numbers[i]; // sansli sayiyi sirayla numbers dizisinden gelen elemana esitler

    // oyuncularin bulundugu listenin icinde dolasir (parametreden gelen list)
    for (int j = 0; j < playersLength; j++)
    {
      kisi = list[j]; // liste icinden sirayla oyunculari cagirir ve kisi degiskenine esitler

      
      if (kisi->money > 1000)
      {

        this->depositedMoney = kisi->ratio * kisi->money; // kisinin masaya yatirdigi parayi hesaplar
        this->moneyOfTable += this->depositedMoney;       // kisi parayi masaya yatirir
        kisi->money -= this->depositedMoney;              // kisi masaya parayi yatirdigi icin kendi parasindan eksilir

        // kisinin sayisi sansli sayiya esit ise
        if (kisi->number == this->luckyNumber)
        {
          double earnings = this->depositedMoney * 10; // kisi yatirdigi paranin 10 katini kazanir
          kisi->money += earnings;                     // kisinin kazanci kendi parasina eklenir
          this->moneyOfTable -= earnings;              // kisinin kazanci masadan odenir
        }
      }
    }

    this->round++; // turu artirir
    rich = this->richestPlayer(list, playersLength);
    system("cls");


    // listedeki oyuncular bittiginde oyun biter
    if (i + 1 == numbersLength)
    {
      int genislik = 45;
      int yukseklik = 10;

      gotoxy(50, 10);

      // ust kismi cizer
      for (int a = 0; a < genislik; a++)
      {
        printf("#");
      }

      // sag kenari cizer
      for (int x = 0; x < yukseklik; x++)
      {
        gotoxy(genislik - 1 + 50, x + 10);
        printf("##\n");
      }

      // tabani cizer
      for (int a = 0; a < genislik; a++)
      {
        gotoxy(genislik - a + 50, yukseklik - 1 + 10);
        printf("#");
      }

      // sol kenari cizer
      for (int x = 0; x < yukseklik; x++)
      {
        gotoxy(50, yukseklik - x - 1 + 10);
        printf("##\n");
      }

      gotoxy(52, 14);
      for (int a = 0; a < genislik - 3; a++)
      {
        printf("-");
      }

      gotoxy(67, 11);
      printf("TUR: %d", this->round);
      gotoxy(59, 12);
      printf("MASA BAKIYE: %.2f", this->moneyOfTable);
      gotoxy(67, 15);
      printf("OYUN BITTI");

      gotoxy(0, 25);
      return;
    }

    gotoxy(50, 10);
    printf("###############################################\n");
    gotoxy(50, 11);
    printf("##               SANSLI SAYI:                ##\n");
    gotoxy(50, 12);
    printf("###############################################\n");
    gotoxy(50, 13);
    printf("###############################################\n");
    gotoxy(50, 14);
    printf("##               TUR:                        ##\n");
    gotoxy(50, 15);
    printf("##       MASA BAKIYE:                        ##\n");
    gotoxy(50, 16);
    printf("##                                           ##\n");
    gotoxy(50, 17);
    printf("##-------------------------------------------##\n");
    gotoxy(50, 18);
    printf("##               EN ZENGIN KISI              ##\n");
    gotoxy(50, 19);
    printf("##                                           ##\n");
    gotoxy(50, 20);
    printf("##       BAKIYESI:                           ##\n");
    gotoxy(50, 21);
    printf("##                                           ##\n");
    gotoxy(50, 22);
    printf("###############################################");

    gotoxy(80, 11);
    printf("%d\n", this->luckyNumber);
    gotoxy(72, 14);
    printf("%d", this->round);
    gotoxy(72, 15);
    printf("%.2f", this->moneyOfTable);
    gotoxy(67, 19);
    printf("%s", rich->name);
    gotoxy(69, 20);
    printf("%.2f", rich->money);

    gotoxy(0, 25);
    Sleep(10);
  }
}

// oyun yapisinin kirici fonksiyonu
void deinitOyun(const Oyun this)
{
  if (this == NULL)
    return;
  free(this);
}
