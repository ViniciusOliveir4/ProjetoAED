#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int codCliente = 0;
int codVeiculo = 0;

// Entidades
typedef struct {
  int dia;
  int mes;
  int ano;
} DIA;

typedef struct {
  int codigo;
  char nome[80];
  char data_nasc[40];
  char cpf[50];
  char endereco[80];
  char telefone[30];
  char email[50];
  float descontoApp;
  int qtdLocacoes;
  float valorTotal;
} CLIENTE;

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
  CLIENTE cliente;
  VEICULO veiculo;
  DIA diaInicio;
  DIA diaDevolucao;
  DIA diaTotal;
  float valorDia;
  float despesaDia;
  float despesaTotal;
} LOCACAO;

// Clientes
typedef struct Elem {
  CLIENTE cli;
  struct Elem *prox;
} Caixa;

typedef Caixa *ponteiro;

typedef struct {
  ponteiro prim, ult;
  int qtd;
} Lista;

void criarListaCliente(Lista *C) {
  C->prim = (ponteiro)malloc(sizeof(Caixa));
  C->ult = C->prim;
  C->prim->prox = NULL;
  C->qtd = 0;
}

void inserirCliente(Lista *C, CLIENTE X) {
  ponteiro p, q;

  q = (ponteiro)malloc(sizeof(Caixa));
  q->cli = X;

  p = C->prim;
  while ((p != C->ult) && (X.codigo > p->prox->cli.codigo))
    p = p->prox;
  q->prox = p->prox;
  p->prox = q;
  C->qtd++;

  if (p == C->ult)
    C->ult = q;
}

void exibeListaCliente(Lista C) {
  ponteiro p;

  printf("\n ********");
  printf("\n * Cab  *");
  printf("\n * List *");
  printf("\n ***<>***");
  printf("\n     V   ");
  p = C.prim->prox;

  while (p != NULL) {
    printf("\n ********");
    printf("\n * %3d  *", p->cli.codigo);
    printf("\n *      *");
    printf("\n ***<>***");
    printf("\n     V   ");
    p = p->prox;
  }
}

void cadastrarCliente(CLIENTE *C) {
  printf("=====> CADASTRAR CLIENTE <=====\n\n");
  printf("\nENTRE COM O NOME DO CLIENTE: ");
  fflush(stdin);
  fgets(C->nome, 80, stdin);
  printf("\nENTRE COM A DATA DE NASCIMENTO: ");
  fflush(stdin);
  fgets(C->data_nasc, 40, stdin);
  printf("\nENTRE COM O CPF: ");
  fflush(stdin);
  fgets(C->cpf, 50, stdin);
  printf("\nENTRE COM O ENDERECO DO CLIENTE: ");
  fflush(stdin);
  fgets(C->endereco, 80, stdin);
  printf("\nENTRE COM O TELEFONE DO CLIENTE: ");
  fflush(stdin);
  fgets(C->telefone, 30, stdin);
  printf("\nENTRE COM O E-MAIL DO CLIENTE: ");
  fflush(stdin);
  fgets(C->email, 50, stdin);
  printf("\n\n\n\nCLIENTE CADASTRADO COM SUCESSO\n");
  fflush(stdin);
  C->codigo = ++codCliente;
}

void exibirCliente(CLIENTE C) {
  printf("\nDADOS DO CLIENTE\n\n");
  fflush(stdin);
  printf("\nCODIGO DO CLIENTE: %d", C.codigo);
  fflush(stdin);
  printf("\nNOME DO CLIENTE: %s", C.nome);
  fflush(stdin);
  printf("\nDATA DE NASCIMENTO: %s", C.data_nasc);
  fflush(stdin);
  printf("\nCPF: %s", C.cpf);
  fflush(stdin);
  printf("\nENDERECO: %s", C.endereco);
  fflush(stdin);
  printf("\nTELEFONE: %s", C.telefone);
  fflush(stdin);
  printf("\nE-MAIL: %s", C.email);
  fflush(stdin);
  printf("\n--------------------------------\n");
}

// Veículos
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

void removerVeiculo(ListaVeiculo *lv, VEICULO *V) {
  v p, q;
  p = lv->prim;
  while ((p != lv->ult) && (V->codigo > p->prox->veiculo.codigo))
    p = p->prox;
  if ((p == lv->ult) || (V->codigo != p->prox->veiculo.codigo)) {
    printf("\n O veículo procurado não está na lista!\n");
    strcpy(V->modelo, "Ninguém");
  } else {
    q = p->prox;
    *V = q->veiculo;
    p->prox = q->prox;
    if (q == lv->ult)
      lv->ult = p;
    lv->qtd--;
    free(q);
  }
}

void exibirVeiculo(VEICULO V) {
  printf("\n ========================== %3d =======================", V.codigo);
  printf("\n == FABRICANTE: %50s                                 ==", V.fabricante);
  printf("\n == MODELO: %50s                                     ==", V.modelo);
  printf("\n == TIPO: %50s                                       ==", V.tipo);
  printf("\n == COR: %20s                                        ==", V.cor);
  printf("\n == TIPO DE COMBUSTÍVEL: %20s                        ==", V.tipoCombustivel);
  printf("\n == ANO: %d                                          ==", V.ano);
  printf("\n == ALUGUEL POR DIA: %.2f                            ==", V.valorDia);
  printf("\n == DESPESA POR DIA: %.2f                            ==", V.despesaDia);
  printf("\n == STATUS: %c                                       ==", V.status);
  printf("\n ======================================================\n");
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
  printf("\nENTRE COM O STATUS DO VEÍCULO (D = Disponível | R = Reservado | M "
         "= Em Manutenção): ");
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

int main() {

  CLIENTE X;
  Lista C;
  int i = 2;
  ponteiro p = NULL;
  menu();

  criarListaCliente(&C); // testando funções

  while (i--) {
    cadastrarCliente(&X);
    inserirCliente(&C, X);
  }

  p = C.prim;

  while (p != C.ult) {
    exibirCliente(p->prox->cli);
    p = p->prox;
  }
  printf("\n FINAL DA LISTA\n ");

  return 0;
}