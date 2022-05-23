#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Kisi.h"
#include "Dosya.h"
#include "Oyun.h"

int main()
{
  // Kisiler.txt'yi okumak icin dosya yapisini cagirir
  Dosya kisilerTxt = initDosya("Kisiler.txt");

  // okudugu listeyi kisiler adli listeye atar
  Kisi *players = kisilerTxt->readPerson(kisilerTxt);

  // Sayilar.txt'yi okumak icin dosya yapisini cagirir
  Dosya sayilarTxt = initDosya("Sayilar.txt");

  // okudugu listeyi numbers adli diziye atar
  int *numbers = sayilarTxt->readNumber(sayilarTxt);

  // oyunu cagirir
  Oyun oyun = initOyun();
  oyun->game(oyun, players, numbers, sayilarTxt->lengthOfFile, kisilerTxt->lengthOfFile);

  oyun->deinitOyun(oyun);
  
  // oyuncular icin bellekten ayirdigi yeri bosaltir
  for (int i = 0; i < kisilerTxt->lengthOfFile; i++)
  {
    free(players[i]);
  }

  // sayilar icin bellekten ayirdigi yeri bosaltir
  for (int i = 0; i < sayilarTxt->lengthOfFile; i++)
  {
    free(&numbers[i]);
  }
  return 0;
}