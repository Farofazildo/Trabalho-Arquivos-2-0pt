#include<stdio.h>
#include<stdlib.h>
#include "prog2Utils.h" // biblioteca de funções auxiliares. Por exemplo editar informações de arquivos.

// aqui vão os protótipos de suas funções
// por exemplo
// função para mostrar menu na tela e ler opção digitada
int lerOpcao();

// Programa Principal 
main (){
		
    int quantidade=0;
    int opcao=1;
    
    do{
        puts("Padaria da dona Joana");
        
        opcao = lerOpcao();
        switch (opcao){
           case 1: // 1- Cadastrar Cliente
             break;

           case 2: // 2- Cadastrar Produto
             break;
             
           case 3:  // 3- Vender fiado
             break;
             
           case 4:  // 4- Vender a vista
             break;
       
           case 5:  // 5- Listar Clientes/Devedores
             break;
          
						case 6:  // 6- Fechar o caixa
						 
						 exit(0);
             break;

						default:
							printf("Opcao invalida, tente novamente.\n");
							break;
                      
        }while (opcao>0 && opcao<7);
     }


} // fim do main