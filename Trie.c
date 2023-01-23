#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Trie.h"
Palavra *pIns = NULL;

//Criando a árvore Trie

Trie* criaTrie(char *c)
{
   Trie *t = (Trie*)malloc(sizeof(Trie));
   t->chave = malloc(sizeof(c));
   strcpy(t->chave, &c);
   t->filho = NULL;
   t->proxima = NULL;
   t->palavra = NULL;
   return t;
}

//Criando Palavra

Palavra* criaPalavra(int tamanho){
  Palavra* p = (Palavra*)malloc(sizeof(Palavra));
  p->valor = (char*)malloc(tamanho);
  p->indice = NULL;
}

//Adicionando Palavra na Trie

Trie* AdicionarPalavra(Trie *t, char *str, int pos)
{
   const int n = strlen(str);
   int i = 0;
   int inseriu = 0;
   Trie* pai = NULL;
   Trie* cabeca = t;
   while(i<n && inseriu == 0){
      while(t != NULL && t->chave[0] != str[i]){
        pai = t;
        t = t->proxima;
      }
      if(t == NULL){
         t = criaTrie(str[i]);
         if (cabeca == NULL){cabeca = t;}
         if (pai != NULL){
           pai->proxima = t;
         }
         inseriu = 1;
         t = InsereAbaixo(t, str, ++i);
      }else{
        if(t->filho == NULL){
          inseriu = 1;
          t = InsereAbaixo(t, str, ++i);
        }else{
          pai = t;
          t = t->filho;
          i++;
        }
      }
   }
   Palavra *p = NULL;
   if (t->palavra){
     p = t->palavra;
   }else{
     p = criaPalavra(n);
     strcpy(p->valor, str);
     t->palavra = p;
   }
   adicionaIndice(p, pos);

  pIns = p;
  return cabeca;
}

//Função InsereAbaixo

Trie* InsereAbaixo(Trie *pai, char *s, int pos){
  const int n = strlen(s);
  int i = 0;
  char c = NULL;
  Trie *t = NULL;
  for(i = pos; i<n; i++){
      c = s[i];
      t = criaTrie(c);
      pai->filho = t;
      pai = t;
   }
   if(!t){
     t = pai;
   }
   return t;
}

//Adiciona Indice na Trie

void adicionaIndice(Palavra *p, int pos){
  Indice *i = (Indice*)malloc(sizeof(Indice));
  Indice *i2 = NULL;
  Indice *ant = NULL;
  i->posicao = pos;
  i->palavra = p;
  if(pIns){
    i->predecessor = pIns->ultimo;
    i2 = pIns->ultimo;
    i2->sucessor = i;
  }
  i->sucessor = NULL;
  if (p->indice == NULL ){
    i->proximo = NULL;
    p->indice = i;
  }else{
    ant = p->indice;
    while(ant->posicao > i->posicao || ant->proximo ){
      ant = ant->proximo;
    }

    if (ant->posicao == i->posicao){
      printf("\n Esta palavra já foi inserida no texto");
    }else{
      i->proximo = ant->proximo;
      ant->proximo = i;
    }
  }
  p->ultimo = i;
}

//Busca Palavra

Palavra* BuscaPalavra(Trie *t, const char *str)
{
  int n = strlen(str);
  int i=0;
  while (t!= NULL && i<n){
    if(t->chave[0] == str[i]){
      i++;
      if(i < n){
        t = t->filho;
      }
    }else{
      t= t->proxima;
    }
  }

  if (t == NULL){
    return NULL;
  }else{
    if (t->palavra != NULL){
      return t->palavra;
    }else{
      return NULL;
    }
  }
}

//Busca tem toda a Trie Palavras

void Busca_So_Palavra(Trie *t){
  if (t->filho){
    Busca_So_Palavra(t->filho);
  }
  if (t->proxima){
    Busca_So_Palavra(t->proxima);
  }
  if(t->palavra){
    Mostra_So_Palavra(t->palavra);
  }
}

//Busca tem toda a Trie Posicao

void Busca_So_Posicao(Trie *t){
  if (t->filho){
    Busca_So_Posicao(t->filho);
  }
  if (t->proxima){
    Busca_So_Posicao(t->proxima);
  }
  if(t->palavra){
    Mostra_So_Posicao(t->palavra);
  }
}

//Calculando Altura da Trie

int calculaQuantidade(Trie *t){
 int a= 0;
  if(t->filho){
    a = calculaAltura(t->filho);
  }
  if(t->proxima){
    a = calculaAltura(t->proxima);
  }
  return a;
}

//Busca por Tamanho

void BuscaPorTamanho(Trie *t, int hAtual, int h){
  if (t->filho && hAtual < h){
    BuscaPorTamanho(t->filho, hAtual+1, h);
  }
  if (h>=hAtual && t->proxima){
    BuscaPorTamanho(t->proxima, hAtual, h);
  }
  if(h == hAtual && t->palavra){
    MostraPalavra(t->palavra);
  }
}

//Busca por Tamanho Repetida

void BuscaPorTamanhoRepetida(Trie *t, int hAtual, int h){
  Indice* c = NULL;
  Palavra *p;
  if (t->filho && hAtual < h){
    BuscaPorTamanho(t->filho, hAtual+1, h);
  }
  if (h>hAtual && t->proxima){
    BuscaPorTamanho(t->proxima, hAtual, h);
  }
  if(h == hAtual && t->palavra){
    p = t->palavra;
    c = p->indice;
    if (c->proximo){
      MostraPalavra(t->palavra);
    }
  }
}

//Calculando Altura da Trie
int calculaAltura(Trie *t, int maiorh, int hAtual){
 int a= hAtual;
  if(t->filho){
    a = calculaAltura(t->filho, maiorh, hAtual+1);
  }
  if(a>maiorh){maiorh = a;}
  if(t->proxima){
    a = calculaAltura(t->proxima, maiorh, hAtual);
  }
  if(a>maiorh){maiorh = a;}
  return maiorh;
}

//Mostra Palavra

void MostraPalavra(Palavra *p){
  Indice *i = p->indice;
  while(i != NULL){
    printf(" Palavra = %s \n", p->valor);
    printf(" Posicao %d\n", i->posicao);
    i = i->proximo;
  }
}

//Mostra só posicao

void Mostra_So_Posicao(Palavra *p){
  Indice *i = p->indice;
  while(i != NULL){
    printf(" Posicao %d\n", i->posicao);
    i = i->proximo;
  }
}

//Mosta só palavra

void Mostra_So_Palavra(Palavra *p){
  Indice *i = p->indice;
  while(i != NULL){
    printf(" Palavra = %s \n", p->valor);
    i = i->proximo;
  }
}


