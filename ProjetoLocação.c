#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int codVeiculo = 0;

// Entidades
typedef struct {
  int dia;
  int mes;
  int ano;
} DIA;

typedef struct {
  int codigo;
  char fabricante[50];
  char modelo[50];
  char tipo[50];
  char cor[20];
  char tipoCombustivel[20];
  int ano;
  float valorDia;
  float despesaDia;
  char status;
} VEICULO;

typedef struct {
  char nome[40];
  int idade;
  char cpf[50];
  char endereco[80];
  char telefone[30];
  char email[50];
  int qtdLocacoes;
  VEICULO veiculoPreferido;
  float tempoMedio;
  float kilometragemMedia;
  float valorLocacao;
  int kilometragem;
} CLIENTE;

typedef struct {
  CLIENTE cliente;
  VEICULO veiculo;
  DIA diaInicio;
  DIA diaDevolucao;
  DIA diaTotal;
  float valorDia;
  float despesaDia;
  float despesaTotal;
} LOCACAO;

// Listas
typedef struct elementoVeiculo {
  VEICULO veiculo;
  struct elementoVeiculo *prox;
} Veiculo;

typedef Veiculo *v;

typedef struct {
  v prim, ult;
  int qtd;
} ListaVeiculo;

void criarListaVeiculo(ListaVeiculo *lv) {
  lv->prim = (v)malloc(sizeof(Veiculo));
  lv->ult = lv->prim;
  lv->prim->prox = NULL;
  lv->qtd = 0;
}

void inserirVeiculo(ListaVeiculo *lv, VEICULO veic) {
  v p, q;

  q = (v)malloc(sizeof(Veiculo));
  q->veiculo = veic;

  p = lv->prim;
  while ((p != lv->ult) && (veic.codigo > p->prox->veiculo.codigo))
    p = p->prox;
    q->prox = p->prox;
    p->prox = q;
    lv->qtd++;
  if (p == lv->ult)
    lv->ult = q;
}

void cadastrarCliente(PESSOA *P) {
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

void cadastrarVeiculo(VEICULO *V) {
  printf("=====> CADASTRAR VEÍCULO <=====\n\n");
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
  printf("\nENTRE COM O TIPO DE COMBUSTÍVEL: ");
  fflush(stdin);
  fgets(V->tipoCombustivel, 20, stdin);
  printf("\nENTRE COM O ANO: ");
  scanf("%d", &V->ano);
  printf("\nENTRE COM O VALOR DO ALUGUEL POR DIA DO VEÍCULO: ");
  scanf("%f", &V->valorDia);
  printf("\nENTRE COM A DESPESA POR DIA DO VEÍCULO: ");
  scanf("%d", &V->despesaDia);
  printf("\nENTRE COM O STATUS DO VEÍCULO (D = Disponível | R = Reservado | M = Em Manutenção): ");
  fflush(stdin);
  fgets(V->status, 1, stdin);
  printf("\n\n\n\nVEICULO CADASTRADO COM SUCESSO!\n");
  fflush(stdin);
  V->codigo = ++codVeiculo;
}

void menu() {
  printf("***** SEJA BEM-VINDO! *****\n\n");
  printf("\tMENU\n\n");
  printf("1 - GERENCIAR CLIENTES\n");
  printf("2 - GERENCIAR VEÍCULOS\n");
  printf("3 - GERENCIAR LOCAÇÕES\n");
  printf("4 - GERENCIAR MANUTENÇÃO\n");
  printf("5 - PREVISÃO DE FATURAMENTO\n");
  printf("6 - SAIR\n");
  printf("\nENTRE COM A OPÇÃO DESEJADA: ");
}