#include<stdio.h>
#include<stdlib.h>
#include "prog2Utils.h" // biblioteca de funções auxiliares. Por exemplo editar informações de arquivos.

// função para mostrar menu na tela e ler opção digitada
int lerOpcao();

// função para cadastrar cliente
void cadastrarCliente(FILE *cl);

//função para cadastrar produto
void cadastrarProduto(FILE *pr);

//Função para vender fiado
void venderFiado(FILE *pr,FILE *cl);

//Função para vender á vista
void venderAVista(FILE *pr);

//Função para listar clientes/devedores
void listarClientes(FILE *cl);

//Função para pagamento de dívida do cliente
void pagamentoCliente(FILE *cl);

// Programa Principal 
int main(void){
    //Declaração de variavéis
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

          case 3: // 4 - Pagamento de Cliente
             pagamentoCliente(cl);
             break;
           case 4:  // 4- Vender fiado
             venderFiado(pr,cl);
             break;
             
           case 5:  // 5- Vender a vista
             venderAVista(pr);
             break;
       
           case 6:  // 6- Listar Clientes/Devedores
             listarClientes(cl);
             break;
          
						case 7:  // 7- Fechar o caixa
						 
						 exit(0);
             break;

						default:
							printf("Opcao invalida, tente novamente.\n");
							break;
          }          
        }while (opcao>0 && opcao<8);
     }
 // fim do main

//Função para ler a opção desejada inserida pelo usuário
int lerOpcao(){
  int op;
  printf("\nDigite a opção desejada:\n1- Cadastrar Cliente\n2- Cadastrar Produto\n3- Pagamento de Cliente\n4- Vender Fiado\n5- Vender a vista\n6- Listar Clientes/Devedores\n7- Fechar o caixa\n: ");
  scanf("%d",&op);
  return op;
}

//Função para cadastrar cliente
void cadastrarCliente(FILE *cl){
  //Abertura de arquivo
  cl = fopen("clientes.txt","a");
  //Caso não seja possível abrir o arquivo           
  if(cl == NULL){
    printf("Erro na abertura de arquivo! \n");
    exit(1);
  }
  //Declaração de variavéis
  int idCliente;
  char nomeCliente[50];
  char enderecoCliente[200];
  char telefoneCliente[20];
  float saldoCliente;
  //Pedindo informações ao usuário
  printf("\nDigite o ID do cliente:");
  scanf("%d",&idCliente);
  
  printf("\nNome do cliente: ");
  int c; while ((c = getchar()) != '\n' && c != EOF);
  gets(nomeCliente);
  
  printf("\nDigite o endereço do cliente: ");
  gets(enderecoCliente);
  
  printf("\nDigite o telefone do cliente: ");
  gets(telefoneCliente);
  //Como saldo devedor sempre começa em 0 ao cadastrar cliente, não é necessário pedir ao usuário
  saldoCliente = 0.0;
  //Armazenando as informações em clientes.txt            
  fprintf(cl,"\n%d,%s,%s,%s,%.1f",idCliente,nomeCliente,enderecoCliente,telefoneCliente,saldoCliente);
              
  //Fechando o arquivo
  fclose(cl);
}

//Função para cadastrar produto
void cadastrarProduto(FILE *pr){
  //Abertura de arquivo
  pr = fopen("produtos.txt","a");
  //Caso não seja possível abrir o arquivo 
  if(pr == NULL){
  printf("Erro na abertura de arquivo! \n");
  exit(1);
  }
  //Declaração de variavéis
  int codProduto;
  char nomeProduto[100];
  float valorProduto;
  //Pedindo informações ao usuário
  printf("\nDigite o código do produto: ");
  scanf("%d",&codProduto);

  printf("\nDigite o nome do produto: ");
  int c; while ((c = getchar()) != '\n' && c != EOF);
  gets(nomeProduto);

  printf("\nDigite o valor do produto: ");
  scanf("%f",&valorProduto);
  //Armazenando as informações em produtos.txt
  fprintf(pr,"\n%d,%s,%.2f\n",codProduto,nomeProduto,valorProduto);
  //Fechando o arquivo
  fclose(pr);
}

//Função para vender fiado
void venderFiado(FILE *pr, FILE *cl){
  //Abertura de arquivos
  pr = fopen("produtos.txt","a+");
  cl = fopen("clientes.txt","a+");
  //Caso não seja possível abrir o arquivo 
  if(pr == NULL || cl == NULL){
  printf("Erro na abertura de arquivo! \n");
  exit(1);
  }
  //Declaração de variavéis
  int idCliente;
  int codProduto;
  int qtd;
  int continuarInserindo = 1;
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

  //While para inserção contínua de produtos em uma lista de compras
  while(continuarInserindo==1){
  printf("\nDigite o Código do produto: ");
  scanf("%d",&codProduto);
    
  printf("\nDigite a quantidade comprada: ");
  scanf("%d",&qtd);
  //Aqui as informações do produto são buscadas
  while( fscanf(pr,"%d,%[^,],%f",&codProdutocheck,nomeProdutocheck,&valorProdutocheck) != EOF){
    //Se as informações inseridas baterem com um produto de produtos.txt, seu valor e quantidade comprada serão somados ao preço total no checkout
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
  //Ao fim, mostra o total a ser pago
  printf("\nTotal a ser pago: %.2f",somacheckout);
  //Como a função "editFile" utiliza um valor em char para atualizar determinado índice em arquivo, precisamos transformar a variável "somacheckout" que atualmente está como float, para char. Para isso, utilizamos a função "sprintf"
  char somaEmChar[10];
  sprintf(somaEmChar, "%.2f", somacheckout);
  //Atualização do saldo devedor do cliente
  editFile("clientes.txt",",",idCliente,4,somaEmChar);
  //Fechando arquivos
  fclose(pr);
  fclose(cl);
}
//Função para vender á vista
void venderAVista(FILE *pr){
  //Abertura de arquivo
  pr = fopen("produtos.txt","a+");
  //Caso não seja possível abrir o arquivo 
  if(pr == NULL){
  printf("Erro na abertura de arquivo! \n");
  exit(1);
  }
  //Declaração de variavéis
  int codProduto;
  int qtd;
  int continuarInserindo = 1;
  int contadorProdutos=0;
  float somacheckout = 0;
  int codProdutocheck;
  char nomeProdutocheck[100];
  float valorProdutocheck;
  
  //While para inserção contínua de produtos em uma lista de compras
  while(continuarInserindo==1){
  contadorProdutos+=1;
  printf("\nDigite o Código do produto: ");
  scanf("%d",&codProduto);
    
  printf("\nDigite a quantidade comprada: ");
  scanf("%d",&qtd);
  //Se as informações inseridas baterem com um produto de produtos.txt, seu valor e quantidade comprada serão somados ao preço total no checkout
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
  //Ao fim, mostra o total a ser pago
  printf("\nTotal a ser pago: %.2f",somacheckout);

  //Fechando arquivo
  fclose(pr);
}

//Função para Listar Clientes/Devedores
void listarClientes(FILE *cl){
  //Abertura de arquivo
  cl = fopen("clientes.txt","r");

  //Declaração de variavéis
  int idCliente;
  char nomeCliente[50];
  char enderecoCliente[200];
  char telefoneCliente[20];
  float saldoCliente;
  int opcaoListar;
  
  //Pergunta ao usuário qual opção ele deseja
  printf("\n1 - Listar todos os clientes\n2 - Listar somente devedores\n: ");
  scanf("%d",&opcaoListar);

  //Lista todos os clientes de "clientes.txt"
  if(opcaoListar==1){
    while(fscanf(cl,"%d,%[^,],%[^,],%[^,],%f",&idCliente,nomeCliente,enderecoCliente,telefoneCliente,&saldoCliente) != EOF){
      printf("\n\nID: %d",idCliente);
      printf("\nNome: %s",nomeCliente);
      printf("\nEndereço: %s",enderecoCliente);
      printf("\nTelefone: %s",telefoneCliente);
      printf("\nSaldo devedor: %.2f",saldoCliente);
    }
    //Lista todos clientes com saldo devedor maior que 0
  }else{
    while(fscanf(cl,"%d,%[^,],%[^,],%[^,],%f",&idCliente,nomeCliente,enderecoCliente,telefoneCliente,&saldoCliente) != EOF){
    if(saldoCliente>0){
      printf("\n\nID: %d",idCliente);
      printf("\nNome: %s",nomeCliente);
      printf("\nEndereço: %s",enderecoCliente);
      printf("\nTelefone: %s",telefoneCliente);
      printf("\nSaldo devedor: %.2f",saldoCliente);
      }
    }
  }
  //Fechando arquivo
  fclose(cl);
}

//Função para pagamento de cliente
void pagamentoCliente(FILE *cl){
  //Abertura de arquivo
  cl = fopen("clientes.txt","r");
  
  //Declaração de variavéis
  int idCliente;
  int idCliente2;
  float valorPago;
  char nomeCliente[50];
  char lixo2[200];
  char lixo3[20];
  float saldoCliente;
  int opcaoListar;
  
  //Pedindo informaçções ao usuário
  printf("\nDigite o ID do cliente: ");
  scanf("%d",&idCliente);
  printf("\nDigite o valor pago: ");
  scanf("%f",&valorPago);
  //Busca informações em "clientes.txt", endereço e telefone são declaradas como "lixo" pois não serão utilizadas nessa função
  while(fscanf(cl,"%d,%[^,],%[^,],%[^,],%f",&idCliente2,nomeCliente,lixo2,lixo3,&saldoCliente) != EOF){
    //Se o id de cliente inserido bater com um dentro de "clientes.txt", mostra o nome do cliente, sua dívida antiga e sua dívida após o pagamento
    if(idCliente2 == idCliente){
      printf("\nNome: %s",nomeCliente);
      printf("\nDívida antiga: %.2f",saldoCliente);
      saldoCliente -= valorPago;
      printf("\nDívida atual: %.2f",saldoCliente);
      valorPago = saldoCliente;
      }
    }
  //Como a função "editFile" utiliza um valor em char para atualizar determinado índice em arquivo, precisamos transformar a variável "valorPago" que atualmente está como float, para char. Para isso, utilizamos a função "sprintf"
  char valorEmChar[10];
  sprintf(valorEmChar, "%.2f", valorPago);
  //Atualização do saldo devedor do cliente
  editFile("clientes.txt",",",idCliente,4,valorEmChar);
  //Fechando arquivo
  fclose(cl);
}