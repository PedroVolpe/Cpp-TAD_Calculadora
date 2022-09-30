/*
NOME: ERIC AKIO UCHIYAMADA             
NOME: OLIVER KIERAN GALVÃO MCCORMACK   
NOME: PEDRO LOUREIRO MORONE BRANCO VOLPE  
*/

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <typeinfo>
#include "calculadora.h"
//-------------------------------------------------------------------------------------------

float Variaveis(std::string expressao)//verifica quantas variáveis existem na expressao
{
  int count = 0,i = 0;
  char caractere;
  while(caractere != '\0')
  {
    caractere = expressao[i];
    if(isalpha(caractere))
      count++;
    i++;    
  }
  return count;
}
//-------------------------------------------------------------------------------------------
Posfixa CreatePos()//Criar pilha para expressão posfixa
{
	Posfixa pilha;
	pilha.topo = 0;
	for (int i = 0; i < TAMANHO_MAXIMO; ++i)
		pilha.vet[i] = '\0';
	
	return pilha;
}
//-------------------------------------------------------------------------------------------
Operacao CreateOp()//Criar pilha para as operações
{
	Operacao pilha;
	pilha.topo = 0;
	for (int i = 0; i < TAMANHO_MAXIMO; ++i)
		pilha.vet[i] = 0;
	
	return pilha;
}
//-------------------------------------------------------------------------------------------
bool PushPos(Posfixa& pilha, char e)//inserir elemento na pilha
{
	// Verifica se a pilha está cheia.
	if (pilha.topo == TAMANHO_MAXIMO)
		return false;
	
	pilha.vet[pilha.topo] = e;
	++pilha.topo;
	return true;
}
//-------------------------------------------------------------------------------------------
bool PushOp(Operacao& pilha, float e)//inserir elemento na pilha
{
	// Verifica se a pilha está cheia.
	if (pilha.topo == TAMANHO_MAXIMO)
		return false;
	
	pilha.vet[pilha.topo] = e;
	++pilha.topo;
	return true;
}
//-------------------------------------------------------------------------------------------
char PopPos(Posfixa& pilha)//retirar elemento da pilha 
{
	// Verifica se a pilha está vazia.
	if (IsEmptyPos(pilha))
		return '\0';
	
	--pilha.topo;
	char aux = pilha.vet[pilha.topo];
	pilha.vet[pilha.topo] = '\0';
	return aux;
}
//-------------------------------------------------------------------------------------------
float PopOp(Operacao& pilha)//retirar elemento da pilha 
{
	// Verifica se a pilha está vazia.
	if (IsEmptyOp(pilha))
		return 0;
	
	--pilha.topo;
	float aux = pilha.vet[pilha.topo];
	pilha.vet[pilha.topo] = 0;
	return aux;
}
//-------------------------------------------------------------------------------------------
char TopPos(const Posfixa& pilha)//apresentar o topo da pilha
{
	// Verifica se a pilha está vazia.
	if (pilha.topo == 0)
		return '\0';
	
	return pilha.vet[pilha.topo - 1];
}
//-------------------------------------------------------------------------------------------
float TopOp(const Operacao& pilha)//apresentar o topo da pilha
{
	// Verifica se a pilha está vazia.
	if (pilha.topo == 0)
		return 0;
	
	return pilha.vet[pilha.topo - 1];
}
//-------------------------------------------------------------------------------------------
bool IsEmptyPos(const Posfixa& pilha)//verificar se a pilha está vazia
{
  if(pilha.topo == 0)
	  return true;
  return false;
}
//-------------------------------------------------------------------------------------------
bool IsEmptyOp(const Operacao& pilha)//verificar se a pilha está vazia
{
	if(pilha.topo == 0)
	  return true;
  return false;
}
//-------------------------------------------------------------------------------------------
//verificar se há número na entrada
bool IsInt(char a){
  if(a == '0' || a == '1' || a == '2' 
    || a == '3' || a == '4' || a == '5' 
    || a == '6' || a == '7' || a == '8' || a == '9')
    return false;
  return true;
}
//-------------------------------------------------------------------------------------------
// FUNÇÃO DE VALIDAÇÃO DE ENTRADA  

bool Valida(const std::string expre){
  Posfixa valida = CreatePos();
  const int tam = expre.length();
  
  // Verificar se todos os parentes abertos, são fechados, se não retorna falso(ERRO)
  for (int i = 0; i < tam; i++){
    if (expre[i] == '('){
      PushPos(valida, expre[i]);
    }
    else if (expre[i] == ')' && TopPos(valida) == '('){
      PopPos(valida);
    }
    else if (expre[i] == ')' && TopPos(valida) != '('){
      return false;
    }
    // Verifica se possui duas letras concatenadas na expressão infixa (Entrada invalida)
    else if (isalpha(expre[i]) && isalpha(expre[i+1])){
      return false;
    }
    // Verifica se há inteiros na expressão
    else if(!IsInt(expre[i]))
      return false;    
  }
  // esvazia pilha
  if (!IsEmptyPos(valida)){
    for(int j = 0; j < tam; j++){
      valida.vet[j] = '\0';
    }
    valida.topo = 0;
  }
  // verifica se as operações digitadas são validas e se não há numeros
  for (int k = 0; k < tam; k++){
    if(!isalpha(expre[k])){
      if(expre[k] == '+'
        || expre[k] == '*'
		    || expre[k] == '-'
		    || expre[k] == '/'
		    || expre[k] == '^'
        || expre[k] == '('
        || expre[k] == ')')
          return true;
    }
  }
  return false;
}
//-------------------------------------------------------------------------------------------
// Limpa a tela para melhor analise da execução
void ClearScreen()//limpar a tela
{
#if _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}
//-------------------------------------------------------------------------------------------
// Remove espaços da expressão e remove o tamanho extra
std::string RemoveEspacos(std::string frase){
  frase.erase(std::remove(frase.begin(), frase.end(), ' '), frase.end());
  return frase;
}

//-------------------------------------------------------------------------------------------
// Função para recolher a entrada do usuario ( expressao infixa )
std::string Entrada_expre(){
  std::string expressao, input;
  std::cout << "Digite a expressão sem espaços:" << std::endl;
  std::cin >> input;
  // converte para caracterem em CapsLk 
  for (int i = 0; input[i] != '\0'; i++){
    input[i] = (char)toupper(input[i]);
  }
  expressao = RemoveEspacos(input);
  // checa se entrada é valida, se não, pede para re-digitar
  while(!Valida(expressao)){
    std::cout << "ERRO*** Expressão inválida!\n";
    std::cout << "Digite uma expressão válida:" << std::endl;
    std::cin >> input;
    for (int i = 0; input[i] != '\0'; i++){
      input[i] = (char)toupper(input[i]);
    }
    expressao = RemoveEspacos(input);
  }
  return expressao;
}
//--------------------------------------------------------------------------------------
// Função para receber os valores das variaveis 
void Entrada_valores(std::string expressao, Variaveis_valores &variavel){
  int j = 0;
  for (int i = 0; expressao[i] != '\0'; i++){
    if(isalpha(expressao[i])){ //inserção de variável num vetor
      variavel.letras[j] = expressao[i];
      j++;
    }
  }
  int n_variaveis = Variaveis(expressao);
  for(int k = 0; k < n_variaveis; k++){ //inserir valor de cada variável
    std::cout << "Insira o valor da variavel " << variavel.letras[k] << ": ";
    std::cin >> variavel.valores[k];
    std::cout << "\n";
    
  }
}

//---------------------------------------------------------------------------------------
//define prioridades das operações e compara-os
bool Prioridade_simbolos(char elemento_topo, char elemento_atual){
  int prioridade_topo, prioridade_atual;
  //Verificando a prioridade do topo da pilha
  if (elemento_topo == '^')
    prioridade_topo = 3;
  else if(elemento_topo == '*' || elemento_topo == '/')
    prioridade_topo = 2;
  else if(elemento_topo == '+' || elemento_topo == '-')
    prioridade_topo = 1;
  else if(elemento_topo == '(')
    prioridade_topo = 0;
  // Verificando a prioridade do elemento atual
  if (elemento_atual == '^')
    prioridade_atual = 4;
  else if(elemento_atual == '*' || elemento_atual == '/')
    prioridade_atual = 2;
  else if(elemento_atual == '+' || elemento_atual == '-')
    prioridade_atual = 1;
  else if(elemento_atual == '(')
    prioridade_atual = 4;

  return (prioridade_atual > prioridade_topo);
  //retorna se a prioridade da expressão é maior que a do topo da pilha
}
//--------------------------------------------------------------------------------------------------
// Função de conversão da expressão infixa para posfixa
std::string Conversao(std::string expressao){
  Posfixa pilha_posfixa;
  pilha_posfixa = CreatePos();
  std::string expressao_posfixa;
  for(int i = 0; expressao[i] != '\0';i++){
    if(isalpha(expressao[i]))//verifica se o caractere eh uma letra
      expressao_posfixa += expressao[i];
    
    else if(expressao[i] == '(')//verifica se o caractere eh um "abre parenteses"
      PushPos(pilha_posfixa, expressao[i]);

    else if(expressao[i] == ')'){//se for "fecha parenteses", Pop até encontrar o '('
      while(TopPos(pilha_posfixa) != '('){
        expressao_posfixa += PopPos(pilha_posfixa);
      }
      PopPos(pilha_posfixa);
    }
    else if(expressao[i] == '*' || expressao[i] == '/'
         || expressao[i] == '+' || expressao[i] == '-'
         || expressao[i] == '^'){
      //se o caractere for um simbolo
      while(!Prioridade_simbolos(TopPos(pilha_posfixa),expressao[i])){
        //se prioridade eh menor, adiciona na expressao posfixa
        expressao_posfixa += PopPos(pilha_posfixa);
        break;
      }
      PushPos(pilha_posfixa,expressao[i]);//retirar o '(' da pilha
    }
  }
  while(!IsEmptyPos(pilha_posfixa)){ //concatenar o resto da pilha
    expressao_posfixa += PopPos(pilha_posfixa);
  }
  return expressao_posfixa; 
}

//--------------------------------------------------------------------------------------
//Realiza as operações com os valores das variáveis, obtendo o resultado final
float Resultado(std::string expressao_posfixa, Variaveis_valores variavel) 
{
  int i, j, n = sizeof(variavel.letras) / sizeof(char);
  float temp1, temp2;
  Operacao operacao = CreateOp(); //Cria a pilha para realizar as operações
  for(i = 0; i < expressao_posfixa.length(); i++) //Percorre a string expressao_posfixa
  {
    if(isalpha(expressao_posfixa[i])) //Se for uma letra
    {
      for(j = 0; (variavel.letras[j] != '\0' || j < n); j++) //Obtém a posição j do vetor variavel.letras
      {
        if(expressao_posfixa[i] == variavel.letras[j])
          break;
      }

      PushOp(operacao, variavel.valores[j]); //Coloca o valor na posição j do vetor variavel.valores na pilha operacao
    }

    else if(expressao_posfixa[i] == '+')//somar
    {
      temp1 = PopOp(operacao);
      temp2 = PopOp(operacao);
      PushOp(operacao, temp1+temp2);
    }

    else if(expressao_posfixa[i] == '-')//subtrair
    {
      temp1 = PopOp(operacao);
      temp2 = PopOp(operacao);
      PushOp(operacao, temp2-temp1);
    }

    else if(expressao_posfixa[i] == '*')//multiplicar
    {
      temp1 = PopOp(operacao);
      temp2 = PopOp(operacao);
      PushOp(operacao, temp1*temp2);
    }

    else if(expressao_posfixa[i] == '/')//divisão
    {
      temp1 = PopOp(operacao);
      temp2 = PopOp(operacao);
      PushOp(operacao, temp2/temp1);
    }

    else if(expressao_posfixa[i] == '^')//exponenciação
    {
      temp1 = PopOp(operacao);
      temp2 = PopOp(operacao);
      PushOp(operacao, pow(temp2,temp1));
    }
  }
  
  return PopOp(operacao);
}

//-------------------------------------------------------------------------------------𐐘
