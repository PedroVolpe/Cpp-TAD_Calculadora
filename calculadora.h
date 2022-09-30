/*
NOME: ERIC AKIO UCHIYAMADA              
NOME: OLIVER KIERAN GALVÃO MCCORMACK      
NOME: PEDRO LOUREIRO MORONE BRANCO VOLPE  
*/

#ifndef __CALCULADORA_H_
#define __CALCULADORA_H_

#include <iostream>

const int TAMANHO_MAXIMO = 35;

struct Posfixa //pilha para transformar a entrada em posfixa
{
  char vet[TAMANHO_MAXIMO];
  int topo;
};

struct Operacao //pilha para executar operações
{
  float vet[TAMANHO_MAXIMO];
  int topo;
};

struct Variaveis_valores{ //estrutura para armazanar as variáveis e seus valores
  char letras[26];
  float valores[26];
};

Posfixa CreatePos();
Operacao CreateOp();
bool PushPos(Posfixa& pilha, char e);
bool PushOp(Operacao& pilha, float e);
char PopPos(Posfixa& pilha);
float PopOp(Operacao& pilha);
char TopPos(const Posfixa& pilha);
float TopOp(const Operacao& pilha);
bool IsEmptyPos(const Posfixa& pilha);
bool IsEmptyOp(const Operacao& pilha);
bool Valida(const std::string expre);
float Variaveis(std::string expressao);
void ClearScreen();
std::string Entrada_expre();
void Entrada_valores(std::string expressao, Variaveis_valores &variavel);
bool Prioridade_simbolos(char elemento_topo, char elemento_atual);
std::string Conversao(std::string expressao);
float Resultado(std::string expressao_posfixa, Variaveis_valores variavel);
bool IsInt(char a);

#endif
