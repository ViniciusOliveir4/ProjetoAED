#include <stdio.h>
#include <stdlib.h>


typedef struct{
    char fabricante[50];
    char modelo[50];
    char tipo[50];
    char cor [20];
    char tipoCombustivel [20];
    char despesaLocacao[50];
    int ano;
    int qtd;   //quantidade de veiculos desse modelo
    int qtdLocado;
    int tempoLocado;
    float consumoKm;
    float valorLocacao;
    float kilometragem;
}VEICULO;

typedef struct{
    char nome[40];
    int idade;
    char cpf[50];
    char endereco [80];
    char telefone [30];
    char email[50];
    int qtdLocacoes;
    VEICULO veiculoPreferido;
    float tempoMedio;
    float kilometragemMedia;
    float valorLocacao;
    int kilometragem;
}PESSOA;

typedef struct{
    VEICULO veiculo;
    PESSOA cliente;
    int tempoLocacao;
    float kilometragem;
    float despesa;
    float desconto;
    float valor;
}LOCACAO;

void cadastrarCliente(PESSOA *P){
    printf("=====> CADASTRAR CLIENTE <=====\n\n");
    printf("\nENTRE COM O NOME DO CLIENTE: ");
    fflush(stdin);
    fgets(P->nome, 40, stdin);
    printf("\nENTRE COM A IDADE: ");
    scanf("%d", &P->idade);
    printf("\nENTRE COM O CPF: ");
    fflush(stdin);
    fgets(P->cpf, 50, stdin);
    printf("\nENTRE COM O ENDERECO DO CLIENTE: ");
    fflush(stdin);
    fgets(P->endereco, 80, stdin);
    printf("\nENTRE COM O TELEFONE DO CLIENTE: ");
    fflush(stdin);
    fgets(P->telefone, 30, stdin);
    printf("\nENTRE COM O E-MAIL DO CLIENTE: ");
    fflush(stdin);
    fgets(P->email, 50, stdin);
    printf("\n\n\n\nCLIENTE CADASTRADO COM SUCESSO\n");
    fflush(stdin);
}

void cadastrarVeiculo(VEICULO *V){
    printf("=====> CADASTRAR VEICULO<=====\n\n");
    printf("\nENTRE COM O FABRICANTE: ");
    fflush(stdin);
    fgets(V->fabricante, 50, stdin);
    printf("\nENTRE COM O MODELO: ");
    fflush(stdin);
    fgets(V->modelo, 50, stdin);
    printf("\nENTRE COM O TIPO: ");
    fflush(stdin);
    fgets(V->tipo, 50, stdin);
    printf("\nENTRE COM O COR: ");
    fflush(stdin);
    fgets(V->cor, 20, stdin);
    printf("\nENTRE COM O TIPO DE COMBUSTIVEL: ");
    fflush(stdin);
    fgets(V->tipoCombustivel, 20, stdin);
    printf("\nENTRE COM O ANO: ");
    scanf("%d", &V->ano);
    printf("\nENTRE COM A KILOMETRAGEM: ");
    scanf("%f", &V->kilometragem);
    printf("\nENTRE COM O VALOR DO ALUGUEL: ");
    scanf("%f", &V->valorLocacao);
    printf("\nENTRE COM A QUANTIDADE DE VEICULOS DESSE MODELO: ");
    scanf("%d", &V->qtd);
    printf("\n\n\n\nVEICULO CADASTRADO COM SUCESSO\n");
    fflush(stdin);
}


void menu(){
    printf("***** SEJA BEM-VINDO! *****\n\n");
    printf("\tMENU\n\n");
    printf("1 - CADASTRAR\n");
    printf("2 - CONSULTAR\n");
    printf("3 - LISTAR VEICULOS\n");
    printf("4 - LISTAR CLIENTES\n");
    printf("7 - SAIR\n");
    printf("\n\nENTRE COM A OPCAO DESEJADA: ");
}
