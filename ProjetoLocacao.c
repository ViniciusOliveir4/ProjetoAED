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
  char status[1];
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
  printf("\n == STATUS: %c                                       ==", V.status[1]);
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
  scanf("%f", &V->despesaDia);
  printf("\nENTRE COM O STATUS DO VEÍCULO (D = Disponível | R = Reservado | M = Em Manutenção): ");
  fflush(stdin);
  fgets(V->status, 1, stdin);
  printf("\n\n\n\nVEICULO CADASTRADO COM SUCESSO!\n");
  fflush(stdin);
  V->codigo = ++codVeiculo;
}

// Interface do Usuário
void submenuCliente() {
  printf("***** CLIENTES *****\n\n");
  printf("1 - CADASTRAR CLIENTE\n");
  printf("2 - CONSULTAR CLIENTE\n");
  printf("3 - LISTAR CLIENTES\n");
  printf("4 - REMOVER CLIENTE\n");
  printf("5 - VOLTAR\n");
  printf("\nENTRE COM A OPÇÃO DESEJADA: ");
}

void submenuVeiculo() {
  printf("***** VEÍCULOS *****\n\n");
  printf("1 - CADASTRAR VEÍCULO\n");
  printf("2 - CONSULTAR VEÍCULO\n");
  printf("3 - LISTAR VEÍCULOS\n");
  printf("4 - REMOVER VEÍCULO\n");
  printf("5 - VOLTAR\n");
  printf("\nENTRE COM A OPÇÃO DESEJADA: ");
}

void submenuLocacao() {
  printf("***** LOCAÇÕES *****\n\n");
  printf("1 - CADASTRAR LOCAÇÃO\n");
  printf("2 - CONSULTAR LOCAÇÃO\n");
  printf("3 - LISTAR LOCAÇÕES\n");
  printf("4 - REMOVER LOCAÇÃO\n");
  printf("5 - VOLTAR\n");
  printf("\nENTRE COM A OPÇÃO DESEJADA: ");
}

void submenuManutencao() {
  printf("***** MANUTENÇÃO *****\n\n");
  printf("1 - INSERIR VEÍCULO\n");
  printf("2 - LISTAR VEÍCULOS EM MANUTENÇÃO\n");
  printf("3 - RETIRAR VEÍCULO DA MANUTENÇÃO\n");
  printf("4 - VOLTAR\n");
  printf("\nENTRE COM A OPÇÃO DESEJADA: ");
}

/* void previsaoFaturamento() {
  printf("***** PREVISÃO DE FATURAMENTO *****\n\n");
  printf("Até 31/12/2020\n");
  printf("Reservas: %d\n");
  printf("Valor Total das Reservas: R$ %.2f\n");
  printf("Custo Total das Reservas: R$ %.2f\n");
  printf("\n\nFaturamento: R$ %.2f\n");
  printf("\n0 - VOLTAR");
} */

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

//CRUDs
void switchCRUDCliente(int subOpcao) {
  Lista lc;
  ponteiro p = NULL;
  CLIENTE C;
  criarListaCliente(&C);

  do {
    switch (subOpcao) {
    case 1:
      cadastrarCliente(&C);
      inserirCliente(&lc, C);
      break;

    case 2:
      printf("\nEntre com o código do cliente que deseja consultar:\n");
      scanf("%d", &C.codigo);
      // consultarCliente(lc, C);
      break;

    case 3:
      p = lc.prim;
      while (p != lc.ult) {
        exibirCliente(p->prox->cli);
        p = p->prox;
      }
      printf("\n FINAL DA LISTA\n ");
      break;

    case 4:
      printf("\nEntre com o código do cliente que deseja remover:\n");
      scanf("%d", &C.codigo);
      // removerCliente(&lc, &C);
      printf("\nCLIENTE REMOVIDO COM SUCESSO!\n");
      // consultarCliente(lc, C);
      break;

    case 5:
      menu();
      break;

    default: 
      printf("Selecione apenas uma das opções apresentadas! (1 a 5)\n\n");
      submenuCliente();
      scanf("%d", &subOpcao);
      switchCRUDCliente(subOpcao);
      break;
    }
  } while (subOpcao != 5);
}

void switchCRUDVeiculo(int subOpcao) {
  ListaVeiculo lv;
  v veic = NULL;
  VEICULO V;
  // criarListaVeiculo(&V);

  do {
    switch (subOpcao) {
    case 1:
      cadastrarVeiculo(&V);
      inserirVeiculo(&lv, V);
      break;

    case 2:
      printf("\nEntre com o código do veículo que deseja consultar:\n");
      scanf("%d", &V.codigo);
      // consultarVeiculo(lv, V);
      break;

    case 3:
      veic = lv.prim;
      while (veic != lv.ult) {
        exibirVeiculo(veic->prox->veiculo);
        veic = veic->prox;
      }
      printf("\n FINAL DA LISTA\n ");
      break;

    case 4:
      printf("\nEntre com o código do veículo que deseja remover:\n");
      scanf("%d", &V.codigo);
      removerVeiculo(&lv, &V);
      printf("\nVEÍCULO REMOVIDO COM SUCESSO!\n");
      // consultarVeiculo(lv, V);
      break;

    case 5:
      menu();
      break;
    }
  } while (subOpcao != 5);
}

// Função Principal
int main(void) {
  int opcao, subOpcao;

  do {
  menu();
  scanf("%d", &opcao);
  switch (opcao) {
  case 1:
    submenuCliente();
    scanf("%d", &subOpcao);
    switchCRUDCliente(subOpcao);
    break;

  case 2:
    submenuVeiculo();
    scanf("%d", &subOpcao);
    switchCRUDVeiculo(subOpcao);
    break;

  case 3:
    submenuLocacao();
    // scanf("%d", &subOpcao);
    // switchCRUDLocacao(subOpcao);
    break;

  case 4:
    submenuManutencao();
    // scanf("%d", &subOpcao);
    // switchCRUDManutencao(subOpcao);
    break;

  case 5:
    // previsaoFaturamento();
    break;

  case 6:
    printf("\n MUITO OBRIGADO POR USAR NOSSO SISTEMA!\n");
    printf("\n ------ Feito por AloCar Systems ------\n");
    break;
  }
} while (opcao != 6);

  return 0;
}