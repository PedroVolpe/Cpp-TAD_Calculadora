/*
NOME: ERIC AKIO UCHIYAMADA                
NOME: OLIVER KIERAN GALVÃO MCCORMACK      
NOME: PEDRO LOUREIRO MORONE BRANCO VOLPE  
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <cmath>
#include "calculadora.h"


int main() 
{

  Variaveis_valores variavel;
  
  int menu,count = 0;
  std::string expressao, input;
  char caractere;
  std::string expressao_posfixa;
  float resposta = 0;

  
  //-------------------------------------------------------------------------------------------
  // MENU
  do
  {
    ClearScreen();
    std::cout << "//-------------------------------------------------//\n";
    std::cout << "Calculadora com notação polonesa reversa.\n";
    std::cout << "Menu: \n";
    std::cout << "1 - Realizar entrada da expressão" << std::endl;
    std::cout << "2 - Entrada dos valores das variáveis" << std::endl;
    std::cout << "3 - Conversão da expressão para notação posfixa" << std:: endl;
    std::cout << "4 - Resultado da expressão" << std::endl;
    std::cout << "5 - Encerrar programa" << std::endl;
    
    std::cout << "\nExpressão Infixa: " << expressao << std::endl;
    std::cout << "Expressão Posfixa: " << expressao_posfixa << std::endl;
    std::cout << "Resultado da operação: " << resposta << std::endl;
    std::cout << "//-------------------------------------------------//\n";
    std::cin >> menu;
   
    
    switch (menu){

    case 1://Realizar entrada da expressão
      {
      expressao = Entrada_expre();
      break;
      }
      
    case 2://Entrada dos valores das variáveis
      {
      Entrada_valores(expressao, variavel);
      break;
      }
    case 3://"Conversão da expressão para notação posfixa"
      {
      expressao_posfixa = Conversao(expressao);
      break;
      }
    case 4://"Resultado da expressão"
      resposta = Resultado(expressao_posfixa,variavel);
      break;
  
    case 5:
      std::cout << "FIM\n";  
      break;

    default:
      std::cout << "ERRO*** Opção inválida!\n\n";
      break;
    }
  
  }while (menu != 5);
  return 0;
}
