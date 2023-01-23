#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct indice{
  int posicao;
  struct Palavra *palavra;
  struct Indice *predecessor;
  struct Indice *sucessor;
  struct Indice *proximo;
} Indice;

typedef struct palavra{
  char *valor;
  struct Indice *indice;
  struct Indice *ultimo;
} Palavra;

//Estrutura Princial
typedef struct trie
{
   char* chave;
   struct trie *filho;
   struct trie *proxima;
   struct Palavra *palavra;
} Trie;


Trie* InsereAbaixo(Trie *pai, char *s, int pos);
