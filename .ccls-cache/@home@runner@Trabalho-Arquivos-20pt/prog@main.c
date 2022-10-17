#include<stdio.h>
#include<stdlib.h>
#include "prog2Utils.h" // biblioteca de funções auxiliares. Por exemplo editar informações de arquivos.

// aqui vão os protótipos de suas funções
// por exemplo
// função para mostrar menu na tela e ler opção digitada
int lerOpcao();
// função para cadastrar cliente
void cadastrarCliente(FILE *cl);
//função para cadastrar produto
void cadastrarProduto(FILE *pr);
//Função para vender fiado
void venderFiado(FILE *pr,FILE *cl);

// Programa Principal 
int main(void){
    FILE *pr;
    FILE *cl;
    int quantidade=0;
    int opcao=1;
    
    do{
        puts("\n\nPadaria da Dona Joana");
        
        opcao = lerOpcao();
        switch(opcao){
           case 1: // 1- Cadastrar Cliente
              cadastrarCliente(cl);
             
              break;
          
           case 2: // 2- Cadastrar Produto
             cadastrarProduto(pr);

             break;
             
           case 3:  // 3- Vender fiado
             venderFiado(pr,cl);
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
          }          
        }while (opcao>0 && opcao<7);
     }
 // fim do main

//Função para ler a opção desejada inserida pelo usuário
int lerOpcao(){
  int op;
  printf("\nDigite a opção desejada:\n1- Cadastrar Cliente\n2- Cadastrar Produto\n3- Vender Fiado\n4- Vender a vista\n5- Listar Clientes/Devedores\n6- Fechar o caixa\n: ");
  scanf("%d",&op);
  return op;
}

//Função para cadastrar cliente
void cadastrarCliente(FILE *cl){
  cl = fopen("clientes.txt","a");
             
  if(cl == NULL){
  printf("Erro na abertura de arquivo! \n");
  exit(1);
  }
  int idCliente;
  char nomeCliente[50];
  char enderecoCliente[200];
  char telefoneCliente[20];
  float saldoCliente;

  printf("\nDigite o ID do cliente:");
  scanf("%d",&idCliente);
  
  printf("\nNome do cliente: ");
  int c; while ((c = getchar()) != '\n' && c != EOF);
  gets(nomeCliente);
  
  printf("\nDigite o endereço do cliente: ");
  gets(enderecoCliente);
  
  printf("\nDigite o telefone do cliente: ");
  gets(telefoneCliente);
  saldoCliente = 0.0;
              
  fprintf(cl,"%d,%s,%s,%s,%.1f",idCliente,nomeCliente,enderecoCliente,telefoneCliente,saldoCliente);
              

  fclose(cl);
}

//Função para cadastrar produto
void cadastrarProduto(FILE *pr){
  pr = fopen("produtos.txt","a");

  if(pr == NULL){
  printf("Erro na abertura de arquivo! \n");
  exit(1);
  }

  int codProduto;
  char nomeProduto[100];
  float valorProduto;

  printf("\nDigite o código do produto: ");
  scanf("%d",&codProduto);

  printf("\nDigite o nome do produto: ");
  int c; while ((c = getchar()) != '\n' && c != EOF);
  gets(nomeProduto);

  printf("\nDigite o valor do produto: ");
  scanf("%f",&valorProduto);

  fprintf(pr,"%d,%s,%.2f\n",codProduto,nomeProduto,valorProduto);

  fclose(pr);
}

void venderFiado(FILE *pr, FILE *cl){
  pr = fopen("produtos.txt","a+");
  cl = fopen("clientes.txt","a+");

  if(pr == NULL || cl == NULL){
  printf("Erro na abertura de arquivo! \n");
  exit(1);
  }
  int idCliente;
  int codProduto;
  int qtd;
  int continuarInserindo = 1;
  int contadorProdutos=0;
  float somacheckout = 0;
  int codProdutocheck;
  char nomeProdutocheck[100];
  float valorProdutocheck;
  int lixo;
  char lixo1;
  char lixo2;
  char lixo3;
  float valorDívida;
  
  
  printf("\nDigite o ID do cliente: ");
  scanf("%d",&idCliente);


  while(continuarInserindo==1){
  contadorProdutos+=1;
  printf("\nDigite o Código do produto: ");
  scanf("%d",&codProduto);
    
  printf("\nDigite a quantidade comprada: ");
  scanf("%d",&qtd);
  
  while( fscanf(pr,"%d,%[^,],%f",&codProdutocheck,nomeProdutocheck,&valorProdutocheck) != EOF){ 
    if(codProduto == codProdutocheck){
      somacheckout += valorProdutocheck * qtd;
      printf("\nNome do produto: %s",nomeProdutocheck);
      printf("\nValor do(a) %s: %.2f",nomeProdutocheck,valorProdutocheck);
    }
  } 
  rewind(pr);
  printf("\nDeseja inserir mais um produto?\n1-Sim\n2-Não\n: ");
  scanf("%d",&continuarInserindo);
  }
  printf("\nTotal a ser pago: %.2f",somacheckout);

char somaEmChar[10];
sprintf(somaEmChar, "%f", somacheckout);
  
  editFile("clientes.txt",",",idCliente,4,somaEmChar);
}