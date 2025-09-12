/*
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 20/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
 */

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
 */

/* retorna um número aleatório entre min e max, inclusive. */
long aleat(long min, long max)
{
  {
    long a;
    // Utiliza a função "rand" para criar um número aleatório entre o min e o max.
    a = rand() % (max - min + 1) + min;
    return a;
  }
}

/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
long mdc(long a, long b)

{
  long aux;
  // Utiliza a função labs para retornar o valor absoluto de a e b.
  a = labs(a);
  b = labs(b);
  // Certifica-se de que o a seja maior do que o b.
  if (a < b)
  {
    aux = a;
    a = b;
    b = aux;
  }
  // Realiza a operação do algoritimo pegando o modulo da divisão do maior pelo menor, até o modulo ser 0.
  while (b > 0)
  {
    aux = a % b;
    a = b;
    b = aux;
  }
  return a;
}

/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc(long a, long b)
{
  long m;
  m = (a * b) / mdc(a, b);
  return m;
}

/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r(struct racional r)
{
  long simp;
  // Primeiro verica se o numero é válido para poder ser simplificado.
  if (valido_r(r))
  {
    simp = mdc(r.num, r.den);
    // Simplifica dividindo numerador e denominador pelo mdc guardado pela variável "simp".
    r.num = r.num / simp;
    r.den = r.den / simp;
    // Caso numerador e denominador sejam negativos retorna uma fração positiva.
    if ((r.num < 0) && (r.den < 0))
    {
      r.num = -r.num;
      r.den = -r.den;
    }
    else
    {
      // Caso somente o denominador seja negativo, inverte os sinais.
      if ((r.num > 0) && (r.den < 0))
      {
        r.num = -r.num;
        r.den = -r.den;
      }
    }
  }
  return r;
}

/* implemente as demais funções de racional.h aqui */

int valido_r(struct racional r)
{
  int val = 0;
  if (r.den != 0)
    val = 1;
  return val;
}

struct racional cria_r(long numerador, long denominador)
{
  struct racional rac;
  rac.num = numerador;
  rac.den = denominador;
  return rac;
}

struct racional sorteia_r(long min, long max)
{
  struct racional sort;
  /* Criei as variáveis numerador e denominador para receberem um número aleatório
     e serem chamados na função criar para virarem um racional fracional*/
  long numerador = aleat(min, max);
  long denominador = aleat(min, max);
  sort = cria_r(numerador, denominador);
  // O número racional sorteado (sort) é simplificado pela função simplifica_r.

  return sort;
}
/* Imprime um racional r, respeitando estas regras:
   - o racional deve ser impresso na forma simplificada;
   - não imprima espaços em branco e não mude de linha;
   - a saída deve ter o formato "num/den", a menos dos casos abaixo:
     - se o racional for inválido, imprime a mensagem "NaN" (Not a Number);
     - se o numerador for 0, imprime somente "0";
     - se o denominador for 1, imprime somente o numerador;
     - se o numerador e denominador forem iguais, imprime somente "1";
     - se o racional for negativo, o sinal "-" vem antes do numerador;
     - se numerador e denominador forem negativos, o racional é positivo. */
void imprime_r(struct racional r)
{
  // Verifica se o racional criado é valido.
  if (!valido_r(r))
    printf("NaN");
  else
  {
    r = simplifica_r(r);
    if ((r.num != 0) && (r.den != 1))
      printf("%ld/%ld", r.num, r.den);

    /* Verifica se há a necessidade de imprimir o denominador,
    pois se o numerador é 0 ou o denominador é 1,
    então há a necessidade de exibir apenas o numerador. */
    if ((r.num == 0) || (r.den == 1))
      printf("%ld", r.num);
  }
}
struct racional iguala_r(struct racional r, long m)
{
  r.num = r.num * (m / r.den);
  r.den = m;
  return r;
}
/* Compara dois racionais r1 e r2. Retorno: -2 se r1 ou r2 for inválido,
 * -1 se r1 < r2, 0 se r1 = r2 ou 1 se r1 > r2 */
int compara_r(struct racional r1, struct racional r2)
{
  float rac1, rac2;
  if (!valido_r(r1) || (!valido_r(r2)))
    return -2;
  else
  {
    //Descobre o número decimal representado na fração e compara eles para descobrir qual é maior
    rac1 = (float)r1.num / r1.den;
    rac2 = (float)r2.num / r2.den;
    if (rac1 > rac2)
      return 1;
    if (rac1 < rac2)
      return -1;
  }
  return 0;
}

/* Retorna a soma dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int soma_r(struct racional r1, struct racional r2, struct racional *r3)
{
  long m;
  if ((!valido_r(r1)) || (!valido_r(r2)) || (!r3))
    return 0;
  // Verifica o mmc das frações para poder encontrar frações equivalentes com o mesmo denominador.
  m = mmc(r1.den, r2.den);
  r1 = iguala_r(r1, m);
  r2 = iguala_r(r2, m);

  // Realiza a soma dos numeradores.
  r3->num = r1.num + r2.num;
  r3->den = m;
  return 1;
}

/* Retorna a subtracao dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int subtrai_r(struct racional r1, struct racional r2, struct racional *r3)
{
  long m;
  if ((r1.den != 0) && (r2.den != 0))
  {
    // Verifica o mmc das frações para poder encontrar frações equivalentes com o mesmo denominador.
    m = mmc(r1.den, r2.den);
    r1 = iguala_r(r1, m);
    r2 = iguala_r(r2, m);
  }
  // Realiza a subtração dos numeradores e simplifica.
  r3->num = r1.num - r2.num;
  r3->den = m;
  return 0;
}

/* Retorna a multiplicacao dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int multiplica_r(struct racional r1, struct racional r2, struct racional *r3)
{
  // Simplismente multiplica numerador por denominador e simplifica.
  r3->num = r1.num * r2.num;
  r3->den = r1.den * r2.den;
  return 0;
}

/* Retorna a divisao dos racionais r1 e r2 no parametro *r3.
 * Retorna 1 se a operacao foi bem sucedida ou
 *         0 se r1 ou r2 for inválido ou se *r3 for nulo */
int divide_r(struct racional r1, struct racional r2, struct racional *r3)
{
  /* Realiza a multiplicação cruzada entre numerador do racional 1 e denominador do racional 2,
  resultando no numerador do quoefciente.
   * Realiza a multiplicação cruzada entre denimunador do racional 1 e numerador do racional 2,
  resultando no denominador do quoefciente.
  e então simplifica */
  r3->num = r1.num * r2.den;
  r3->den = r1.den * r2.num;
  return 0;
}