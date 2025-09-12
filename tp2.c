
/*
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
 */

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
// GRR20245988
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

#define MAX 100
/* coloque aqui as funções auxiliares que precisar neste arquivo */
//Algoritmo bubble sort para ordenar o vetor
int bubbleSort(struct racional rac[], int n)
{
  int i, j;
  struct racional aux;

  for (i = 0; i < n - 1; i++)
  {
    for (j = i + 1; j < n; j++)
    {
      /*chama a função compara_r para verificar se o número no indice i do vetor é maior que o do indice j,
        se for então ele troca os números racionais de lugar*/
      if ((compara_r(rac[i], rac[j])) == 1)
      {
        aux = rac[j];
        rac[j] = rac[i];
        rac[i] = aux;
      }
    }
  }
  return 0;
}

/* programa principal */
int main()
{
  /* a completar! */
  /*Criei a struct do vetor, do auxiliar(aux) que vai ser usado na troca de inválido por válido,
    criei a struct adicao para guaradr o valor da soma
    e criei a variável ptr do tipo ponteiro para poder atualizar o valor de adicao na funçao soma_r*/
  struct racional rac[MAX], aux, adicao, *ptr;
  adicao.num = 0;
  adicao.den = 1;
  ptr = &adicao;
  /*Criei variáveis: n para ler o número da quantidade de racionais lidos;
    i e j para auxiliarem no loop de troca de invalidos-válidos;
    tam também para auxiliar na troca de inválidos-válidos, sem precisar alterar o n*/
  int n, i, j, tam;
  scanf("%d", &n);
  while ((n < 0) || (n > 100))
    scanf("%d", &n);
  for (i = 0; i < n; i++)
  {
    scanf("%ld", &rac[i].num);
    scanf("%ld", &rac[i].den);
  }
  // Imprime o vetor como foi lido
  printf("VETOR= ");
  for (i = 0; i < n; i++)
  {
    imprime_r(rac[i]);
    printf(" ");
  }
  printf("\n");

  // Algoritmo para remover os termos inválidos do vetor
  // Através do "for" o algoritmo define um índice pivô para verificar se é válido
  for (i = 0; i < n; i++)
  {
    tam = n;
    // Compara o primeiro índice do vetor com o último para ver se algum deles é inválido
    j = compara_r(rac[i], rac[n - 1]);
    if (j == -2)
    {
      // Verifica se o último é inválido, se for já elimina ele do vetor
      if (!valido_r(rac[n - 1]))
      {
        n -= 1;
        tam = n;
      }
      // Verifica se on primeiro é pivô é inválido, se for ele troca o número do pivo com o último número válido do vetor
      if (!valido_r(rac[i]))
      {
        /*Entra em loopin para se certificar de pegar o primeiro válido de trás para frente
          a condição de parada é se ele encontrar o número válido ou chegar no pivô (que significa q não existe número válido depois dele);
          "tam - 1" representa o índice do ultimo número válido*/
        while (!valido_r(rac[tam - 1]) && (tam - 1 > i))
          tam -= 1;
        // Se saiu do loop com o indice do número valido maior do que o do pivô, então ele troca eles de lugar
        if (i < tam - 1)
        {
          aux = rac[i];
          rac[i] = rac[tam - 1];
          rac[tam - 1] = aux;
        }
        /*Se o índice de "tam - 1" é igual ao indice do pivô, então não existe número válido depois do pivô, e ele decrementa 1,
          pois como ele foi eliminando os últimos inválidos, o pivô acabou sendo o último válido e ele é então apagado do vetor */
        if (i == tam - 1)
          n -= 1;
      }
    }
  }
  // Imprime o vetor sem os números inválidos
  printf("VETOR = ");
  for (i = 0; i < n; i++)
  {
    imprime_r(rac[i]);
    printf(" ");
  }
  printf("\n");

  // Função para ordenar o vetor pelo algoritmo de bubble sort
  bubbleSort(rac, n);

  // Imprime o vetor ordenado
  printf("VETOR = ");
  for (i = 0; i < n; i++)
  {
    imprime_r(rac[i]);
    printf(" ");
  }
  printf("\n");

  // Realiza a soma dos valores contidos no vetor e guardam na variável adicao, fazendo uso do ponteiro
  for (i = 0; i < n; i++)
    soma_r(rac[i], adicao, ptr);

  //Se a soma foi válida, imprime ela
  printf("SOMA = ");
  if (!soma_r(rac[i], adicao, ptr))
    imprime_r(adicao);
  printf("\n");

  return (0);
}
