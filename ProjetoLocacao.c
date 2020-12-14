#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int codCliente = 0;
int codVeiculo = 0;
int codLocacao = 0;

int subOpcao;

// Entidades
/*typedef struct {
  int dia;
  int mes;
  int ano;
} DIA;*/

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
  char placa[50];
  char tipo[50];
  char cor[20];
  char tipoCombustivel[20];
  int ano;
  float valorDia;
  float despesaDia;
  char status;
} VEICULO;

typedef struct {
  int codigo;
  CLIENTE cliente;
  VEICULO veiculo;
  /*DIA diaInicio;
  DIA diaDevolucao;
  DIA diaTotal;*/
  int diaInicio;
  int diaDevolucao;
  int diaTotal;
  float valorDia;
  float despesaDia;
  float despesaTotal;
  float valorTotal;
} LOCACAO;

// Clientes
typedef struct elemC {
  CLIENTE cli;
  struct elemC *prox;
} CaixaCliente;

typedef CaixaCliente *pC;

typedef struct {
  pC prim, ult;
  int qtd;
} ListaCliente;

void criarListaCliente(ListaCliente *C) {
  C->prim = (pC)malloc(sizeof(CaixaCliente));
  C->ult = C->prim;
  C->prim->prox = NULL;
  C->qtd = 0;
}

void inserirCliente(ListaCliente *C, CLIENTE X) {
  pC p, q;

  q = (pC)malloc(sizeof(CaixaCliente));
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

void cadastrarCliente(CLIENTE *C) {
  printf("\n======> CADASTRAR CLIENTE <======\n");
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
  printf("\n\nCLIENTE CADASTRADO COM SUCESSO\n");
  fflush(stdin);
  C->codigo = ++codCliente;
}

void exibirCliente(CLIENTE C) {
  printf("\n=======> DADOS DO CLIENTE <=======\n\n");
  fflush(stdin);
  printf("\nCODIGO DO CLIENTE: %d", C.codigo);
  printf("\n");
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
  printf("\n==================================\n");
}

void listarTodosClientes(ListaCliente LC) {
  pC c = LC.prim;

  while (c != LC.ult) {
    exibirCliente(c->prox->cli);
    c = c->prox;
  }
}

void consultarCliente(ListaCliente C, CLIENTE X) {
  pC p;

  p = C.prim;

  // Buscar cliente passando CPF por parâmetro
  while ((p != C.ult) && (!(strcmp(X.cpf, p->prox->cli.cpf) == 0)))
    p = p->prox;

  if ((p == C.ult) || (!(strcmp(X.cpf, p->prox->cli.cpf) == 0)))
    printf("\nCliente com o cpf %s nao encontrado!\n", X.cpf);
  else
    exibirCliente(p->prox->cli);
}

void removerCliente(ListaCliente *C, CLIENTE *X) {
  pC p, q;

  p = C->prim;

  // Buscar cliente passando CPF por parâmetro
  while ((p != C->ult) && (!(strcmp(X->cpf, p->prox->cli.cpf) == 0)))
    p = p->prox;

  if ((p == C->ult) || (!(strcmp(X->cpf, p->prox->cli.cpf) == 0)))
    printf("\nCLIENTE COM O CPF %s NAO ENCONTRADO!\n", X->cpf);
  else {
    int op;
    CLIENTE Y = *X;

    exibirCliente(Y);
    // Verificação de Segurança
    printf("\nDESEJA REALMENTE REMOVER O CADASTRO DESTE CLIENTE?\n(DIGITE 1 "
           "PARA SIM OU 2 PARA NAO)\n");
    scanf("%d", &op);

    if (op == 1) {
      q = p->prox;
      *X = q->cli;
      p->prox = q->prox;
      if (q == C->ult)
        C->ult = p;
      C->qtd--;
      free(q);
      printf("\n\nCADASTRO DE CLIENTE REMOVIDO COM SUCESSO!\n\n");
    } else
      printf("\n\nVOLTANDO AO MENU!\n\n");
  }
}

// Veículos
typedef struct elemV {
  VEICULO veiculo;
  struct elemV *prox;
} CaixaVeiculo;

typedef CaixaVeiculo *pV;

typedef struct {
  pV prim, ult;
  int qtd;
} ListaVeiculo;

void criarListaVeiculo(ListaVeiculo *lv) {
  lv->prim = (pV)malloc(sizeof(CaixaVeiculo));
  lv->ult = lv->prim;
  lv->prim->prox = NULL;
  lv->qtd = 0;
}

void inserirVeiculo(ListaVeiculo *lv, VEICULO veic) {
  pV p, q;

  q = (pV)malloc(sizeof(CaixaVeiculo));
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

void cadastrarVeiculo(VEICULO *V) {
  printf("\n=====> CADASTRAR VEICULO <=====\n");
  printf("\nENTRE COM O FABRICANTE: ");
  fflush(stdin);
  fgets(V->fabricante, 50, stdin);
  printf("\nENTRE COM A PLACA: ");
  fflush(stdin);
  fgets(V->placa, 50, stdin);
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
  fflush(stdin);
  scanf("%d", &V->ano);
  printf("\nENTRE COM O VALOR DO ALUGUEL POR DIA DO VEICULO: ");
  fflush(stdin);
  scanf("%f", &V->valorDia);
  printf("\nENTRE COM A DESPESA POR DIA DO VEICULO: ");
  fflush(stdin);
  scanf("%f", &V->despesaDia);
  printf("\nENTRE COM O STATUS DO VEICULO (D = Disponivel | R = Reservado | M "
         "= Em Manutencao): ");
  fflush(stdin);
  V->status = getchar();
  printf("\n\n\n\nVEICULO CADASTRADO COM SUCESSO!\n");
  fflush(stdin);
  V->codigo = ++codVeiculo;
}

void exibirVeiculo(VEICULO V) {
  printf("\n=======> DADOS DO VEICULO <=======\n");
  printf("\n ========================== %3d =======================", V.codigo);
  printf("\n FABRICANTE: %50s", V.fabricante);
  printf("\n PLACA: %50s", V.placa);
  printf("\n MODELO: %50s", V.modelo);
  printf("\n TIPO: %50s", V.tipo);
  printf("\n COR: %20s", V.cor);
  printf("\n TIPO DE COMBUSTIVEL: %20s", V.tipoCombustivel);
  printf("\n ANO: %d", V.ano);
  printf("\n ALUGUEL POR DIA: %.2f", V.valorDia);
  printf("\n DESPESA POR DIA: %.2f", V.despesaDia);
  printf("\n STATUS: %c", V.status);
  printf("\n ======================================================\n");
}

void listarTodosVeiculos(ListaVeiculo LV) {
  pV c = LV.prim;

  while (c != LV.ult) {
    exibirVeiculo(c->prox->veiculo);
    c = c->prox;
  }
}

void consultarVeiculo(ListaVeiculo LV, VEICULO X) {
  pV p;

  p = LV.prim;

  // buscar veiculo passando a placa por parametro
  while ((p != LV.ult) && (!(strcmp(X.placa, p->prox->veiculo.placa) == 0)))
    p = p->prox;

  if ((p == LV.ult) || (!(strcmp(X.placa, p->prox->veiculo.placa) == 0)))
    printf("\nVEICULO COM A PLACA %s NAO ENCONTRADO!\n", X.placa);
  else
    exibirVeiculo(p->prox->veiculo);
}

void removerVeiculo(ListaVeiculo *LV, VEICULO *X) {
  pV p, q;
  p = LV->prim;

  // buscar cliente passando cpf por parametro
  while ((p != LV->ult) && (!(strcmp(X->placa, p->prox->veiculo.placa) == 0)))
    p = p->prox;

  if ((p == LV->ult) || (!(strcmp(X->placa, p->prox->veiculo.placa) == 0)))
    printf("\nVEICULO COM A PLACA %s NAO ENCONTRADO!\n", X->placa);
  else {
    if (p->prox->veiculo.status == 'D') {

      int op;
      VEICULO Y = *X;

      exibirVeiculo(Y);
      // verificação de segurança
      printf("\nDESEJA REALMENTE REMOVER O CADASTRO DESTE VEICULO?\n(DIGITE 1 "
             "PARA SIM OU 2 PARA NAO)\n");
      scanf("%d", &op);

      if (op == 1) {
        q = p->prox;
        *X = q->veiculo;
        p->prox = q->prox;
        if (q == LV->ult)
          LV->ult = p;
        LV->qtd--;
        free(q);
        printf("\n\nCADASTRO DE VEICULO REMOVIDO COM SUCESSO!\n\n");
      } else {
        printf("\n\nVOLTANDO AO MENU!\n\n");
      }
    } else {
      printf("\n\nNAO EH POSSIVEL REMOVER VEICULO COM STATUS R(Reservado) OU "
             "M(Manutencao)\n\n");
    }
  }
}

// Locações
typedef struct elemL {
  LOCACAO locacao;
  struct elemL *prox;
} CaixaLocacao;

typedef CaixaLocacao *pL;

typedef struct {
  pL prim, ult;
  int qtd;
} ListaLocacao;

void criarListaLocacao(ListaLocacao *lc) {
  lc->prim = (pL)malloc(sizeof(CaixaLocacao));
  lc->ult = lc->prim;
  lc->prim->prox = NULL;
  lc->qtd = 0;
}

void inserirLocacao(ListaLocacao *ll, LOCACAO loc) {
  pL p, q;

  q = (pL)malloc(sizeof(CaixaLocacao));
  q->locacao = loc;

  p = ll->prim;
  while ((p != ll->ult) && (loc.codigo > p->prox->locacao.codigo)) {
    p = p->prox;
  }
  q->prox = p->prox;
  p->prox = q;
  ll->qtd++;
  if (p == ll->ult) {
    ll->ult = q;
  }
}

void cadastrarLocacao(LOCACAO *L, CLIENTE C, VEICULO V) {
  printf("\n=====> CADASTRAR LOCACAO <=====\n");
  printf("\nENTRE COM O CODIGO DO CLIENTE: ");
  fflush(stdin);
  scanf("%d", &C.codigo);
  printf("\nENTRE COM O CODIGO DO VEICULO: ");
  fflush(stdin);
  scanf("%d", &V.codigo);
  printf("\nENTRE COM O DIA INICIAL DA LOCACAO: ");
  fflush(stdin);
  scanf("%d", &L->diaInicio);
  printf("\nENTRE COM O DIA DA DEVOLUCAO: ");
  fflush(stdin);
  scanf("%d", &L->diaDevolucao);
  printf("\n\n\n\nLOCACAO CADASTRADA COM SUCESSO!\n");
  fflush(stdin);
  L->diaTotal = L->diaDevolucao - L->diaInicio;
  L->despesaTotal = (V.despesaDia) * (L->diaTotal);
  L->valorTotal = ((V.valorDia) * (L->diaTotal));
  L->codigo = ++codLocacao;
}

void exibirLocacao(LOCACAO L) {
  printf("\n=======> DADOS DA LOCACAO <=======\n\n");
  fflush(stdin);
  printf("\nCODIGO DO CLIENTE: %d", L.cliente.codigo);
  printf("\n");
  fflush(stdin);
  printf("\nNOME DO CLIENTE: %s", L.cliente.nome);
  fflush(stdin);
  printf("\nCODIGO DO VEICULO: %d", L.veiculo.codigo);
  printf("\n");
  fflush(stdin);
  printf("\nMODELO DO VEICULO: %s", L.veiculo.modelo);
  fflush(stdin);
  printf("\nDATA INICIAL DA LOCACAO: %d/12/2020", L.diaInicio);
  fflush(stdin);
  printf("\nDATA DE DEVOLUCAO: %d/12/2020", L.diaDevolucao);
  fflush(stdin);
  printf("\nDURACAO DA LOCACAO: %d DIAS", L.diaTotal);
  fflush(stdin);
  printf("\nCUSTO DA LOCACAO: R$ %.2f", L.despesaTotal);
  fflush(stdin);
  printf("\nVALOR DA LOCACAO: R$ %.2f", L.valorTotal);
  fflush(stdin);
  printf("\n==================================\n");
}

void listarTodasLocacoes(ListaLocacao LL) {
  pL l = LL.prim;

  while (l != LL.ult) {
    exibirLocacao(l->prox->locacao);
    l = l->prox;
  }
}

void consultarLocacao(ListaLocacao L, LOCACAO X) {
  pL p;

  p = L.prim;

  // Buscar locação pelo código
  while ((p != L.ult) && (X.codigo != 0 && p->prox->locacao.codigo != 0)) {
    p = p->prox;
  }

  if ((p == L.ult) || (X.codigo != 0 && p->prox->locacao.codigo != 0)) {
    printf("\nLOCACAO COM O CODIGO %d NAO ENCONTRADA!\n", X.codigo);
  } else {
    exibirLocacao(p->prox->locacao);
  }
}

void removerLocacao(ListaLocacao *LL, LOCACAO *X) {
  pL p, q;
  p = LL->prim;

  // Buscar locação pelo código
  while ((p != LL->ult) && (X->codigo != 0 && p->prox->locacao.codigo != 0)) {
    p = p->prox;
  }

  if ((p == LL->ult) || (X->codigo != 0 && p->prox->locacao.codigo != 0)) {
    printf("\nLOCACAO COM O CODIGO %d NAO ENCONTRADA!\n", X->codigo);
  } else {

    int op;
    LOCACAO Y = *X;

    exibirLocacao(Y);
    // Verificação de Segurança
    printf("\nDESEJA REALMENTE REMOVER ESTA LOCACAO?\n(DIGITE 1 PARA SIM OU 2 "
           "PARA NAO)\n");

    if (op == 1) {
      q = p->prox;
      *X = q->locacao;
      p->prox = q->prox;
      if (q == LL->ult) {
        LL->ult = p;
      }
      LL->qtd--;
      free(q);
      printf("\n\nREGISTRO DE LOCACAO REMOVIDO COM SUCESSO!\n\n");
    } else {
      printf("\n\nVOLTANDO AO MENU!\n\n");
    }
  }
}

// Interface do Usuário
void menu() {
  printf("\n\n***** SEJA BEM-VINDO! *****\n\n");
  printf("\tMENU\n\n");
  printf("1 - GERENCIAR CLIENTES\n");
  printf("2 - GERENCIAR VEÍCULOS\n");
  printf("3 - GERENCIAR LOCAÇÕES\n");
  printf("4 - GERENCIAR MANUTENÇÃO\n");
  printf("5 - PREVISÃO DE FATURAMENTO\n");
  printf("6 - SAIR\n");
  printf("\nENTRE COM A OPÇÃO DESEJADA: ");
}

void submenuCliente() {
  printf("\n\n***** CLIENTES *****\n\n");
  printf("1 - CADASTRAR CLIENTE\n");
  printf("2 - CONSULTAR CLIENTE\n");
  printf("3 - LISTAR CLIENTES\n");
  printf("4 - REMOVER CLIENTE\n");
  printf("5 - VOLTAR\n");
  printf("\nENTRE COM A OPÇÃO DESEJADA: ");
}

void submenuVeiculo() {
  printf("\n\n***** VEÍCULOS *****\n\n");
  printf("1 - CADASTRAR VEÍCULO\n");
  printf("2 - CONSULTAR VEÍCULO\n");
  printf("3 - LISTAR VEÍCULOS\n");
  printf("4 - REMOVER VEÍCULO\n");
  printf("5 - VOLTAR\n");
  printf("\nENTRE COM A OPÇÃO DESEJADA: ");
}

void submenuLocacao() {
  printf("\n\n***** LOCAÇÕES *****\n\n");
  printf("1 - CADASTRAR LOCAÇÃO\n");
  printf("2 - CONSULTAR LOCAÇÃO\n");
  printf("3 - LISTAR LOCAÇÕES\n");
  printf("4 - REMOVER LOCAÇÃO\n");
  printf("5 - VOLTAR\n");
  printf("\nENTRE COM A OPÇÃO DESEJADA: ");
}

void submenuManutencao() {
  printf("\n\n***** MANUTENÇÃO *****\n\n");
  printf("1 - INSERIR VEÍCULO\n");
  printf("2 - LISTAR VEÍCULOS EM MANUTENÇÃO\n");
  printf("3 - RETIRAR VEÍCULO DA MANUTENÇÃO\n");
  printf("4 - VOLTAR\n");
  printf("\nENTRE COM A OPÇÃO DESEJADA: ");
}

void previsaoFaturamento() {
  int reservas = 395;
  float valor_total = reservas * 12.00;
  float custo_total = reservas * 2.50;
  float faturamento = valor_total - custo_total;

  printf("\n\n***** PREVISÃO DE FATURAMENTO *****\n\n");
  printf("Até 31/12/2020\n");
  printf("Reservas: %d\n", reservas);
  printf("Valor Total das Reservas: R$ %.2f\n", valor_total);
  printf("Custo Total das Reservas: R$ %.2f\n", custo_total);
  printf("\nFaturamento: R$ %.2f\n", faturamento);
  printf("\n0 - VOLTAR\n");

  int opcao;
  scanf("%d", &opcao);

  while (opcao != 0) {
    printf("OPÇÃO INVÁLIDA: aperte 0 para voltar ao menu principal!\n");
    scanf("%d", &opcao);
  }
}

// CRUDs
void switchCRUDCliente() {
  ListaCliente lc;
  pC p = NULL;
  CLIENTE C;
  criarListaCliente(&lc);

  do {
    submenuCliente();
    scanf("%d", &subOpcao);

    switch (subOpcao) {
    case 1:
      cadastrarCliente(&C);
      inserirCliente(&lc, C);
      break;

    case 2:
      printf("\nEntre com o cpf do cliente que deseja consultar:\n");
      scanf("%d", &C.cpf);
      consultarCliente(lc, C);
      break;

    case 3:
      listarTodosClientes(lc);
      printf("\n FINAL DA LISTA\n ");
      break;

    case 4:
      printf("\nEntre com o cpf do cliente que deseja remover:\n");
      scanf("%d", &C.cpf);
      removerCliente(&lc, &C);
      printf("\nCLIENTE REMOVIDO COM SUCESSO!\n");
      consultarCliente(lc, C);
      break;

    case 5:
      menu();
      break;

    default:
      printf("Selecione apenas uma das opções apresentadas! (1 a 5)\n");
      submenuCliente();
      scanf("%d", &subOpcao);
      switchCRUDCliente(subOpcao);
      break;
    }
  } while (subOpcao != 5);
}

void switchCRUDVeiculo() {
  ListaVeiculo lv;
  pV veic = NULL;
  VEICULO V;
  criarListaVeiculo(&lv);

  do {
    submenuVeiculo();
    scanf("%d", &subOpcao);

    switch (subOpcao) {
    case 1:
      cadastrarVeiculo(&V);
      inserirVeiculo(&lv, V);
      break;

    case 2:
      printf("\nEntre com a placa do veículo que deseja consultar:\n");
      scanf("%d", &V.placa);
      consultarVeiculo(lv, V);
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
      printf("\nEntre com a placa do veículo que deseja remover:\n");
      scanf("%d", &V.placa);
      removerVeiculo(&lv, &V);
      printf("\nVEÍCULO REMOVIDO COM SUCESSO!\n");
      consultarVeiculo(lv, V);
      break;

    case 5:
      menu();
      break;

    default:
      printf("Selecione apenas uma das opções apresentadas! (1 a 5)\n");
      submenuVeiculo();
      scanf("%d", &subOpcao);
      switchCRUDVeiculo(subOpcao);
      break;
    }
  } while (subOpcao != 5);
}

void switchCRUDLocacao(int subOpcao) {
  ListaVeiculo lv;
  ListaCliente lc;
  ListaLocacao ll;
  pL loc = NULL;
  LOCACAO L;
  VEICULO V;
  CLIENTE C;
  criarListaLocacao(&ll);

  do {
    submenuLocacao();
    scanf("%d", &subOpcao);

    switch (subOpcao) {
    case 1:
      cadastrarLocacao(&L, C, V);
      inserirLocacao(&ll, L);
      break;

    case 2:
      printf("\nEntre com o codigo da locacao que deseja consultar:\n");
      scanf("%d", &L.codigo);
      consultarLocacao(ll, L);
      break;

    case 3:
      loc = ll.prim;
      while (loc != ll.ult) {
        exibirLocacao(loc->prox->locacao);
        loc = loc->prox;
      }
      printf("\n FINAL DA LISTA \n");
      break;

    case 4:
      printf("Entre com o codigo da locacao que deseja remover:\n");
      scanf("%d", &L.codigo);
      removerLocacao(&ll, &L);
      printf("\n LOCACAO REMOVIDA COM SUCESSO! \n");
      consultarLocacao(ll, L);
      break;

    case 5:
      menu();
      break;

    default:
      printf("Selecione apenas uma das opcoes apresentadas! (1 a 5)\n");
      submenuLocacao();
      scanf("%d", &subOpcao);
      switchCRUDLocacao(subOpcao);
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
      switchCRUDCliente();
      break;

    case 2:
      switchCRUDVeiculo();
      break;

    case 3:
      switchCRUDLocacao();
      break;

    case 4:
      submenuManutencao();
      // scanf("%d", &subOpcao);
      // switchCRUDManutencao(subOpcao);
      break;

    case 5:
      previsaoFaturamento();
      break;

    case 6:
      printf("\nMUITO OBRIGADO POR USAR NOSSO SISTEMA!\n");
      printf("\n------ Feito por AloCar Systems ------\n");
      break;

    default:
      printf("\nENTRADA INVÁLIDA: Selecione apenas uma das opções "
             "apresentadas! (1 a 6)\n");
    }
  } while (opcao != 6);

  return 0;
}