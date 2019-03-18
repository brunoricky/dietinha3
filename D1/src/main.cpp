#include "Data.h"
#include <stdio.h>
#include <iostream>
#include <ilcplex/ilocplex.h>

void solve(Data& data);

int main(int argc, char** argv)
{
   if(argc != 2) // Se o número de argumentos do terminal for diferente de 2
   {
      printf("Usage:\n./bin instance\n"); 
      return 0;
   }

   Data data; 
   data.readData(argv[1]); // Lê o segundo argumento passado no "terminal" (Nome da instância - teste)

   solve(data);

   return 0;
}

void solve(Data& data)
{
   IloEnv env;
   IloModel modelo(env);

   ///////////////////////////////////////////////////////
   //variavel Xi: Xi = 1, se o item i é selecionado
   IloIntVarArray x(env, data.getNItems(), 0, IloInfinity);
   
   //adiciona a variavel x ao modelo
   for(int i = 0; i < data.getNItems(); i++){

	char var[100];
	sprintf(var, "X(%d)", i); // Dá o seguinte nome para a variável var: "X(i)"
	x[i].setName(var); //x[i] recebe o nome de var
	modelo.add(x[i]); // Adiciona ao modelo
}
   //fim das variaveis
   ///////////////////////////////////////////////////////

   /////////////////////////////////////////////////
   /////////////////////////Criando a Função Objetivo (FO) 
   IloExpr sumX(env); 
   for(int i = 0; i < data.getNItems(); i++)
   {
	sumX += data.getItemCost(i)*x[i]; // Faz o somatório do custo dos itens
	
   }
   // Adicionando a FO
   modelo.add(IloMinimize(env, sumX)); // Função objetivo que procura minimizar o custo
   //////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////
   //Restricoes

   //Restricoes (1): Atingir no mínimo 150 proteínas
    IloExpr sumP(env);
    for(int i = 0; i < data.getNItems(); i++) 
   {
	
	sumP += x[i]*data.getItemProtein(i); // Faz o somatório das proteínas dos itens escolhidos

	modelo.add(sumP >= 150); // Adiciona essa restrição ao modelo
	
   }
	

   //Restricoes (2): Atingir no mínimo 130 carboidratos
    IloExpr sumC(env);
    for(int i = 0; i < data.getNItems(); i++)
   {
	
	sumC += x[i]*data.getItemCarb(i); // Faz o somatório dos carbs dos itens escolhidos
	
	modelo.add(sumC >= 130); // Adiciona essa restrição ao modelo
   }
	
	
  //Restricoes (2): Atingir no mínimo 60 no valor de gorduras
   IloExpr sumG(env);
   for(int i = 0; i < data.getNItems(); i++)
   {
	
	sumG += x[i]*data.getItemFat(i); // Faz o somatório das fats dos itens escolhidos
	
	modelo.add(sumG >= 60); // Adiciona essa restrição ao modelo
   }
	


   //fim das restricoes
   ////////////////////////////////////////////////////////

   //resolve o modelo
   IloCplex bpp(modelo);
   bpp.setParam(IloCplex::TiLim,2*60*60); // Seta o tempo limite para execução
   bpp.setParam(IloCplex::Threads, 1);
   bpp.exportModel("modelo.lp");
   
   try
   {
      bpp.solve();
   }
   catch(IloException& e)
   {
	std::cout << e;
   }

   std::cout << "status:" << bpp.getStatus() << std::endl;
   std::cout << "valor total gasto:" << bpp.getObjValue() << std::endl;
   for(int i = 0; i < data.getNItems(); i++) 
   {
	   if(bpp.getValue(x[i]) > 0.001){
	     	  std::cout << bpp.getValue(x[i]) << "g do item " << i << std::endl;
	     }
	
   }
}
