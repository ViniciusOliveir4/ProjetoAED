/*
    SISTEMAS DE INFORMACAO - INF - UFG
    ALGORITMOS E ESTRUTURAS DE DADOS 1 - 2020-1
    PROFESSOR: EDMUNDO SERGIO SPOTO
    ALUNOS:
    201700605 - JUNNO LUCIO L. G. JACOB,
    201804676 -	LUCAS PEREIRA MATOS,
    201705645 - VINICIUS FERREIRA DE OLIVEIRA
    PROJETO FINAL - LOCADORA DE VEICULOS - ALOCAR SYSTEMS
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 200

int subOpcao;

// Entidades
typedef struct {
  int codigo;
  char nome[80];
  char data_nasc[40];
  char cpf[50];
  char endereco[80];
  char telefone[30];
  char email[50];
  int fezReserva;
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
  int qtdLocacoes;
  float valorTotal;
  char status[40];
  int numStatus;
} VEICULO;

typedef struct {
  int codigo;
  CLIENTE cliente;
  VEICULO veiculo;
  int diaInicio;
  int diaDevolucao;
  int diaTotal;
  float valorDia;
  float despesaDia;
  float despesaTotal;
  float valorTotal;
  float lucroLocacao;
} LOCACAO;

typedef struct {
  int codigo;
  VEICULO veiculo;
} MANUTENCAO;

// Clientes
typedef struct {
  CLIENTE itemCli[MAX];
  int prim, ult, tam;
  int contCodigos;
} ListaCliente;

void tcl_enter() {
  printf("\n\nTECLE 'ENTER' PARA CONTINUAR...");
  getchar();
}

void criarListaCliente(ListaCliente *LC) {
  LC->prim = 0;
  LC->ult = 0;
  LC->tam = 0;
  LC->contCodigos = 0;
}

int verificarListaClienteVazia(ListaCliente LC) { return (LC.prim == LC.ult); }

int verificarListaClienteCheia(ListaCliente LC) { return (LC.ult == MAX); }

void inserirCliente(ListaCliente *LC, CLIENTE X) {
  int i, j;

  if (verificarListaClienteCheia(*LC)) {
    printf("\nA lista esta cheia (INSERIR CLIENTE)\n");
    system("pause");
  } else {
    i = LC->prim;
    while ((i < LC->ult) && (X.codigo > LC->itemCli[i].codigo)) {
      i++;
    }
    if (i == LC->ult) {
      LC->itemCli[i] = X;
    } else {
      for (j = LC->ult; j > i; j--) {
        LC->itemCli[j] = LC->itemCli[j - 1];
      }
      LC->itemCli[i] = X;
    }
    LC->ult++;
    LC->tam++;
  }
}

void cadastrarCliente(CLIENTE *C, int codCliente) {
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
  C->fezReserva = 0;
  C->qtdLocacoes = 0;
  C->valorTotal = 0.00;
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
  printf("\nFEZ RESERVA: ");
  fflush(stdin);
  if (C.fezReserva > 0) {
    printf("SIM");
  } else {
    printf("NAO");
  }
  printf("\nQUANTIDADE DE LOCACOES: %d", C.qtdLocacoes);
  fflush(stdin);
  printf("\nVALOR TOTAL EM LOCACOES: R$ %.2f", C.valorTotal);
  fflush(stdin);
  printf("\n==================================\n");
}

void listarTodosClientes(ListaCliente LC) {
  int i;
  if (verificarListaClienteVazia(LC)) {
    printf("\nA lista esta vazia (LISTAR CLIENTES)\n");
    system("pause");
  } else {
    printf("\n=======> LISTAGEM DOS CLIENTES <=======\n\n");
    for (i = LC.prim; i < LC.ult; i++) {
      exibirCliente(LC.itemCli[i]);
    }
  }
}

void consultarCliente(ListaCliente LC, CLIENTE X) {
  int i;

  if (verificarListaClienteVazia(LC)) {
    printf("\nA lista esta vazia (CONSULTAR CLIENTE)\n");
    system("pause");
  } else {
    i = LC.prim;

    // Buscar cliente passando CPF por parametro
    while ((i != LC.ult) && (!strcmp(X.cpf, LC.itemCli[i].cpf) == 0)) {
      i++;
    }

    if ((i == LC.ult) || (!strcmp(X.cpf, LC.itemCli[i - 1].cpf))) {
      printf("\nCLIENTE COM O CPF %s NAO ENCONTRADO!\n", X.cpf);
    } else {
      exibirCliente(LC.itemCli[i]);
    }
  }
}

void removerCliente(ListaCliente *LC, CLIENTE *X) {
  int i, j;

  if (verificarListaClienteVazia(*LC)) {
    printf("\nA lista esta vazia (REMOVER CLIENTE)\n");
    system("pause");
  } else {

    i = LC->prim;

    // Buscar cliente passando CPF por parametro
    while ((i != LC->ult) && (!strcmp(X->cpf, LC->itemCli[i].cpf) == 0)) {
      i++;
    }

    if ((i == LC->ult) || (!strcmp(X->cpf, LC->itemCli[i - 1].cpf))) {
      printf("\nCLIENTE COM O CPF %s NAO ENCONTRADO!\n", X->cpf);
    } else {

      if (LC->itemCli[i].fezReserva > 0) {
        printf("\nNAO E POSSIVEL REMOVER CLIENTES COM RESERVAS EFETUADAS. "
               "CANCELE A LOCACAO PARA REMOVER O CLIENTE\n");
      } else {
        int op;
        CLIENTE Y = LC->itemCli[i];

        exibirCliente(Y);

        // Verificação de Segurança:
        printf("\nDESEJA REALMENTE REMOVER O CADASTRO DESTE CLIENTE? (DIGITE "
               "'1' PARA SIM OU '2' PARA NAO)\n");
        scanf("%d", &op);
        if (op == 1) {
          *X = LC->itemCli[i];
          for (j = i; j < LC->ult - 1; j++) {
            LC->itemCli[j] = LC->itemCli[j + 1];
          }
          LC->ult--;
          LC->tam--;
          printf("\n\nCADASTRO DE CLIENTE REMOVIDO COM SUCESSO!\n\n");
          system("pause");
        } else {
          printf("\n\nVOLTANDO AO MENU!\n\n");
          system("pause");
        }
      }
    }
  }
}

// Veículos
typedef struct {
  VEICULO itemVeic[MAX];
  int prim, ult, tam;
  int contCodigos;
} ListaVeiculo;

void criarListaVeiculo(ListaVeiculo *LV) {
  LV->prim = 0;
  LV->ult = 0;
  LV->tam = 0;
  LV->contCodigos = 0;
}

int verificarListaVeiculoVazia(ListaVeiculo LV) { return (LV.prim == LV.ult); }

int verificarListaVeiculoCheia(ListaVeiculo LV) { return (LV.ult == MAX); }

void inserirVeiculo(ListaVeiculo *LV, VEICULO X) {
  int i, j;

  if (verificarListaVeiculoCheia(*LV)) {
    printf("\nA lista esta cheia (INSERIR VEICULO)\n");
  } else {
    i = LV->prim;
    while ((i < LV->ult) && (X.codigo > LV->itemVeic[i].codigo)) {
      i++;
    }
    if (i == LV->ult) {
      LV->itemVeic[i] = X;
    } else {
      for (j = LV->ult; j > i; j--) {
        LV->itemVeic[j] = LV->itemVeic[j - 1];
      }
      LV->itemVeic[i] = X;
    }
    LV->ult++;
    LV->tam++;
  }
}

void cadastrarVeiculo(VEICULO *V, int codVeiculo) {
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

  printf("\n\n\n\nVEICULO CADASTRADO COM SUCESSO!\n");
  fflush(stdin);
  V->codigo = ++codVeiculo;
  V->qtdLocacoes = 0;
  V->valorTotal = 0.00;
  V->numStatus = 1;
  strcpy(V->status, "DISPONIVEL");
}

void exibirVeiculo(VEICULO V) {
  printf("\n=======> DADOS DO VEICULO <=======\n");
  fflush(stdin);
  printf("\n CODIGO: %d", V.codigo);
  fflush(stdin);
  printf("\n FABRICANTE: %s", V.fabricante);
  fflush(stdin);
  printf("\n PLACA: %s", V.placa);
  fflush(stdin);
  printf("\n MODELO: %s", V.modelo);
  fflush(stdin);
  printf("\n TIPO: %s", V.tipo);
  fflush(stdin);
  printf("\n COR: %s", V.cor);
  fflush(stdin);
  printf("\n TIPO DE COMBUSTIVEL: %s", V.tipoCombustivel);
  fflush(stdin);
  printf("\n ANO: %d", V.ano);
  fflush(stdin);
  printf("\n ALUGUEL POR DIA: R$ %.2f", V.valorDia);
  fflush(stdin);
  printf("\n DESPESA POR DIA: R$ %.2f", V.despesaDia);
  fflush(stdin);
  printf("\n STATUS: %s", V.status);
  fflush(stdin);
  printf("\n VEZES LOCADO: %d", V.qtdLocacoes);
  fflush(stdin);
  printf("\n LUCRO GERADO: R$ %.2f", V.valorTotal);
  fflush(stdin);
  printf("\n ======================================================\n");
}

void listarTodosVeiculos(ListaVeiculo LV) {
  int i;
  if (verificarListaVeiculoVazia(LV)) {
    printf("\nA lista esta vazia (LISTAR VEICULOS)\n");
    system("pause");
  } else {
    printf("\n=======> LISTAGEM DOS VEICULOS <=======\n\n");
    for (i = LV.prim; i < LV.ult; i++) {
      exibirVeiculo(LV.itemVeic[i]);
    }
  }
}

void consultarVeiculo(ListaVeiculo LV, VEICULO X) {
  int i;

  if (verificarListaVeiculoVazia(LV)) {
    printf("\nA lista esta vazia (CONSULTAR VEICULO)\n");
    system("pause");
  } else {
    i = LV.prim;

    // Buscar veiculo passando a placa por parametro
    while ((i != LV.ult) && (!strcmp(X.placa, LV.itemVeic[i].placa) == 0)) {
      i++;
    }

    if ((i == LV.ult) || (!strcmp(X.placa, LV.itemVeic[i - 1].placa) != 0)) {
      printf("\nVEICULO COM A PLACA %s NAO ENCONTRADO!\n", X.placa);
    } else {
      exibirVeiculo(LV.itemVeic[i]);
    }
  }
}

void removerVeiculo(ListaVeiculo *LV, VEICULO *X) {
  int i, j;

  if (verificarListaVeiculoVazia(*LV)) {
    printf("\nA lista esta vazia (REMOVER VEICULO)\n");
    system("pause");
  } else {

    i = LV->prim;

    // Buscar veiculo passando a placa por parametro
    while ((i != LV->ult) && (!strcmp(X->placa, LV->itemVeic[i].placa) == 0)) {
      i++;
    }

    if ((i == LV->ult) || (!strcmp(X->placa, LV->itemVeic[i - 1].placa))) {
      printf("\nVEICULO COM A PLACA %s NAO ENCONTRADO!\n", X->placa);
    } else {

      if (LV->itemVeic[i].numStatus == 1) {
        int op;
        VEICULO Y = LV->itemVeic[i];

        exibirVeiculo(Y);

        // Verificação de Segurança:
        printf("\nDESEJA REALMENTE REMOVER O CADASTRO DESTE VEICULO? (DIGITE "
               "'1' PARA SIM OU '2' PARA NAO)\n");
        scanf("%d", &op);
        if (op == 1) {
          *X = LV->itemVeic[i];
          for (j = i; j < LV->ult - 1; j++) {
            LV->itemVeic[j] = LV->itemVeic[j + 1];
          }
          LV->ult--;
          LV->tam--;
          printf("\n\nCADASTRO DE VEICULO REMOVIDO COM SUCESSO!\n\n");
          system("pause");
        } else {
          printf("\n\nVOLTANDO AO MENU!\n\n");
          system("pause");
        }
      } else {
        printf("\n\nNAO EH POSSIVEL REMOVER VEICULO COM STATUS RESERVADO OU EM "
               "MANUTENCAO\n\n");
        system("pause");
      }
    }
  }
}

// Locações
typedef struct {
  LOCACAO itemLoc[MAX];
  int prim, ult, tam;
  int contCodigos;
} ListaLocacao;

void criarListaLocacao(ListaLocacao *LL) {
  LL->prim = 0;
  LL->ult = 0;
  LL->tam = 0;
  LL->contCodigos = 0;
}

int verificarListaLocacaoVazia(ListaLocacao LL) { return (LL.prim == LL.ult); }

int verificarListaLocacaoCheia(ListaLocacao LL) { return (LL.ult == MAX); }

void inserirLocacao(ListaLocacao *LL, LOCACAO X) {
  int i, j;

  if (verificarListaLocacaoCheia(*LL)) {
    printf("\nA lista esta cheia (INSERIR LOCACAO)\n");
    system("pause");
  } else {
    i = LL->prim;
    while ((i < LL->ult) && (X.codigo > LL->itemLoc[i].codigo)) {
      i++;
    }
    if (i == LL->ult) {
      LL->itemLoc[i] = X;
    } else {
      for (j = LL->ult; j > i; j--) {
        LL->itemLoc[j] = LL->itemLoc[j - 1];
      }
      LL->itemLoc[i] = X;
    }
    LL->ult++;
    LL->tam++;
  }
}

int cadastrarLocacao(ListaCliente *LC, ListaVeiculo *LV, CLIENTE C, VEICULO V,
                     LOCACAO *L, int codLocacao) {
  int i, indiceCli, indiceVeic;
  int sucessoLocacao = 0;

  printf("\n=====> CADASTRAR LOCACAO <=====\n");

  printf("\nENTRE COM O CPF DO CLIENTE: \n");
  fflush(stdin);
  fgets(C.cpf, 50, stdin);

  if (verificarListaClienteVazia(*LC)) {
    printf("\nA lista esta vazia (LOCACAO CLIENTE)\n");
    sucessoLocacao = 1;
    system("pause");
  } else {
    i = LC->prim;

    // Buscar cliente passando CPF por parametro
    while ((i != LC->ult) && (!strcmp(C.cpf, LC->itemCli[i].cpf) == 0)) {
      i++;
    }

    if ((i == LC->ult) || (!strcmp(C.cpf, LC->itemCli[i - 1].cpf))) {
      printf("\nCLIENTE COM O CPF %s NAO ENCONTRADO!\n", C.cpf);
      sucessoLocacao = 1;
    } else {

      CLIENTE Y = LC->itemCli[i];
      L->cliente = Y;
      indiceCli = i;

      printf("\nENTRE COM A PLACA DO VEICULO: \n");
      fflush(stdin);
      fgets(V.placa, 50, stdin);

      if (verificarListaVeiculoVazia(*LV)) {
        printf("\nA lista esta vazia (LOCACAO VEICULO)\n");
        sucessoLocacao = 1;
        system("pause");
      } else {

        i = LV->prim;

        // Buscar veiculo passando a placa por parametro
        while ((i != LV->ult) &&
               (!strcmp(V.placa, LV->itemVeic[i].placa) == 0)) {
          i++;
        }

        if ((i == LV->ult) || (!strcmp(V.placa, LV->itemVeic[i - 1].placa))) {
          printf("\nVEICULO COM A PLACA %s NAO ENCONTRADO!\n", V.placa);
          sucessoLocacao = 1;
        } else {

          if (LV->itemVeic[i].numStatus == 1) {

            VEICULO Z = LV->itemVeic[i];
            L->veiculo = Z;
            indiceVeic = i;

            printf("\nENTRE COM O DIA INICIAL: ");
            fflush(stdin);
            scanf("%d", &L->diaInicio);
            while (L->diaInicio < 1 || L->diaInicio > 31) {
              printf("\nDIA INVALIDO. ENTRE COM O DIA INICIAL: ");
              fflush(stdin);
              scanf("%d", &L->diaInicio);
            }

            printf("\nENTRE COM O DIA DE DEVOLUCAO: ");
            fflush(stdin);
            scanf("%d", &L->diaDevolucao);
            while (L->diaDevolucao > 31 || L->diaDevolucao <= L->diaInicio) {
              printf("\nDIA INVALIDO. ENTRE COM O DIA DIA DE DEVOLUCAO: ");
              fflush(stdin);
              scanf("%d", &L->diaDevolucao);
            }

            printf("\n\n\n\nLOCACAO CADASTRADA COM SUCESSO!\n");
            fflush(stdin);

            L->codigo = ++codLocacao;
            L->diaTotal = L->diaDevolucao - L->diaInicio;
            L->valorDia = LV->itemVeic[indiceVeic].valorDia;
            L->despesaDia = LV->itemVeic[indiceVeic].despesaDia;
            L->despesaTotal = L->despesaDia * L->diaTotal;
            L->valorTotal = L->valorDia * L->diaTotal;
            L->lucroLocacao = L->valorTotal - L->despesaTotal;

            LV->itemVeic[indiceVeic].numStatus = 2;
            strcpy(LV->itemVeic[indiceVeic].status, "RESERVADO");
            LV->itemVeic[indiceVeic].qtdLocacoes++;
            LV->itemVeic[indiceVeic].valorTotal += L->lucroLocacao;

            LC->itemCli[indiceCli].fezReserva += 1;
            LC->itemCli[indiceCli].qtdLocacoes++;
            LC->itemCli[indiceCli].valorTotal += L->valorTotal;

          } else {
            printf("\nVEICULOS RESERVADOS OU EM MANUTENCAO NAO PODEM SER "
                   "ALUGADOS\n");
            sucessoLocacao = 1;
          }
        }
      }
    }
  }

  return sucessoLocacao;
}

void exibirLocacao(LOCACAO L) {
  printf("\n=======> DADOS DA LOCACAO <=======\n");
  fflush(stdin);
  printf("\n CODIGO: %d", L.codigo);
  fflush(stdin);
  printf("\n CLIENTE (NOME): %s", L.cliente.nome);
  fflush(stdin);
  printf("\n CLIENTE (CPF): %s", L.cliente.cpf);
  fflush(stdin);
  printf("\n VEICULO (MODELO): %s", L.veiculo.modelo);
  fflush(stdin);
  printf("\n VEICULO (PLACA): %s", L.veiculo.placa);
  fflush(stdin);
  printf("\n INICIO: %d/12/2020", L.diaInicio);
  fflush(stdin);
  printf("\n DEVOLUCAO: %d/12/2020", L.diaDevolucao);
  fflush(stdin);
  printf("\n DIAS TOTAIS: %d", L.diaTotal);
  fflush(stdin);
  printf("\n DESPESA POR DIA: R$ %.2f", L.despesaDia);
  fflush(stdin);
  printf("\n DESPESA TOTAL: R$ %.2f", L.despesaTotal);
  fflush(stdin);
  printf("\n VALOR POR DIA: R$ %.2f", L.valorDia);
  fflush(stdin);
  printf("\n VALOR TOTAL: R$ %.2f", L.valorTotal);
  fflush(stdin);
  printf("\n LUCRO: R$ %.2f", L.lucroLocacao);
  fflush(stdin);
  printf("\n ======================================================\n");
}

void listarTodasLocacoes(ListaLocacao LL) {
  int i;
  if (verificarListaLocacaoVazia(LL)) {
    printf("\nA lista esta vazia (LISTAR LOCACOES)\n");
    system("pause");
  } else {
    printf("\n=======> LISTAGEM DAS LOCACOES <=======\n\n");
    for (i = LL.prim; i < LL.ult; i++) {
      exibirLocacao(LL.itemLoc[i]);
    }
  }
}

void consultarLocacao(ListaLocacao LL, LOCACAO X) {
  int i;

  if (verificarListaLocacaoVazia(LL)) {
    printf("\nA lista esta vazia (CONSULTAR LOCACAO)\n");
    system("pause");
  } else {
    i = LL.prim;

    // Buscar locacao pelo codigo
    while ((i != LL.ult) && (X.codigo != LL.itemLoc[i].codigo)) {
      i++;
    }

    if ((i == LL.ult) || (X.codigo != LL.itemLoc[i].codigo)) {
      printf("\nLOCACAO COM O CODIGO %d NAO ENCONTRADO!\n", X.codigo);
      fflush(stdin);
    } else {
      exibirLocacao(LL.itemLoc[i]);
    }
  }
}

void removerLocacao(ListaCliente *LC, ListaVeiculo *LV, ListaLocacao *LL,
                    CLIENTE C, VEICULO V, LOCACAO *L) {
  int i, j, k;

  if (verificarListaLocacaoVazia(*LL)) {
    printf("\nA lista esta vazia (REMOVER LOCACAO)\n");
    system("pause");
  } else {

    i = LL->prim;

    // Buscar locacao pelo codigo
    while ((i != LL->ult) && (L->codigo != LL->itemLoc[i].codigo)) {
      i++;
    }

    if ((i == LL->ult) || (L->codigo != LL->itemLoc[i].codigo)) {
      printf("\nLOCACAO COM O CODIGO %d NAO ENCONTRADO!\n", L->codigo);
    } else {
      int op;
      LOCACAO Y = LL->itemLoc[i];
      C = LL->itemLoc[i].cliente;
      V = LL->itemLoc[i].veiculo;

      exibirLocacao(Y);

      // Verificação de Segurança:
      printf("\nDESEJA REALMENTE REMOVER O CADASTRO DESTA LOCACAO? (DIGITE '1' "
             "PARA SIM OU '2' PARA NAO)\n");
      scanf("%d", &op);
      if (op == 1) {

        k = LC->prim;

        while ((k != LC->ult) && (!strcmp(C.cpf, LC->itemCli[k].cpf) == 0)) {
          k++;
        }

        LC->itemCli[k].fezReserva--;
        LC->itemCli[k].qtdLocacoes--;
        LC->itemCli[k].valorTotal -= LL->itemLoc[i].valorTotal;

        k = LV->prim;

        while ((k != LV->ult) &&
               (!strcmp(V.placa, LV->itemVeic[k].placa) == 0)) {
          k++;
        }

        LV->itemVeic[k].numStatus = 1;
        strcpy(LV->itemVeic[k].status, "DISPONIVEL");
        LV->itemVeic[k].qtdLocacoes--;
        LV->itemVeic[k].valorTotal -= LL->itemLoc[i].lucroLocacao;

        *L = LL->itemLoc[i];
        for (j = i; j < LL->ult - 1; j++) {
          LL->itemLoc[j] = LL->itemLoc[j + 1];
        }

        LL->ult--;
        LL->tam--;
        printf("\n\nCADASTRO DE LOCACAO REMOVIDO COM SUCESSO!\n\n");
        system("pause");
      } else {
        printf("\n\nVOLTANDO AO MENU!\n\n");
        system("pause");
      }
    }
  }
}

// Manutenções
typedef struct {
  MANUTENCAO itemMan[MAX];
  int prim, ult, tam;
  int contCodigos;
} ListaManutencao;

void criarListaManutencao(ListaManutencao *LM) {
  LM->prim = 0;
  LM->ult = 0;
  LM->tam = 0;
  LM->contCodigos = 0;
}

int verificarListaManutencaoVazia(ListaManutencao LM) {
  return (LM.prim == LM.ult);
}

int verificarListaManutencaoCheia(ListaManutencao LM) {
  return (LM.ult == MAX);
}

void inserirManutencao(ListaManutencao *LM, MANUTENCAO X) {
  int i, j;

  if (verificarListaManutencaoCheia(*LM)) {
    printf("\nA lista esta cheia (INSERIR MANUTENCAO)\n");
    system("pause");
  } else {
    i = LM->prim;
    while ((i < LM->ult) && (X.codigo > LM->itemMan[i].codigo)) {
      i++;
    }
    if (i == LM->ult) {
      LM->itemMan[i] = X;
    } else {
      for (j = LM->ult; j > i; j--) {
        LM->itemMan[j] = LM->itemMan[j - 1];
      }
      LM->itemMan[i] = X;
    }
    LM->ult++;
    LM->tam++;
  }
}

int cadastrarManutencao(ListaVeiculo *LV, VEICULO V, MANUTENCAO *M,
                        int codManutencao) {
  int i, indiceVeic;
  int sucessoManutencao = 0;

  printf("\n=====> CADASTRAR MANUTENCAO <=====\n");

  printf("\nENTRE COM A PLACA DO VEICULO: \n");
  fflush(stdin);
  fgets(V.placa, 50, stdin);

  if (verificarListaVeiculoVazia(*LV)) {
    printf("\nA lista esta vazia (MANUTENCAO VEICULO)\n");
    sucessoManutencao = 1;
    system("pause");
  } else {

    i = LV->prim;

    // Buscar veiculo passando a placa por parametro
    while ((i != LV->ult) && (!strcmp(V.placa, LV->itemVeic[i].placa) == 0)) {
      i++;
    }

    if ((i == LV->ult) || (!strcmp(V.placa, LV->itemVeic[i - 1].placa))) {
      printf("\nVEICULO COM A PLACA %s NAO ENCONTRADO!\n", V.placa);
      sucessoManutencao = 1;
    } else {
      if (LV->itemVeic[i].numStatus == 1) {

        M->codigo = ++codManutencao;
        LV->itemVeic[i].numStatus = 3;
        strcpy(LV->itemVeic[i].status, "MANUTENCAO");

        VEICULO Y = LV->itemVeic[i];
        M->veiculo = Y;

        printf("\n\n\nMANUTENCAO CADASTRADA COM SUCESSO!\n");
        fflush(stdin);

      } else {
        printf("\nVEICULOS JA EM MANUTENCAO OU RESERVADOS NAO PODEM ENTRAR NA "
               "MANUTENCAO\n");
        sucessoManutencao = 1;
      }
    }
  }

  return sucessoManutencao;
}

void exibirManutencao(MANUTENCAO M) {
  printf("\n=======> DADOS DA MANUTENCAO <=======\n");
  fflush(stdin);
  printf("\n CODIGO: %d", M.codigo);
  fflush(stdin);
  printf("\n FABRICANTE: %s", M.veiculo.fabricante);
  fflush(stdin);
  printf("\n PLACA: %s", M.veiculo.placa);
  fflush(stdin);
  printf("\n MODELO: %s", M.veiculo.modelo);
  fflush(stdin);
  printf("\n TIPO: %s", M.veiculo.tipo);
  fflush(stdin);
  printf("\n COR: %s", M.veiculo.cor);
  fflush(stdin);
  printf("\n TIPO DE COMBUSTIVEL: %s", M.veiculo.tipoCombustivel);
  fflush(stdin);
  printf("\n ANO: %d", M.veiculo.ano);
  fflush(stdin);
  printf("\n ALUGUEL POR DIA: R$ %.2f", M.veiculo.valorDia);
  fflush(stdin);
  printf("\n DESPESA POR DIA: R$ %.2f", M.veiculo.despesaDia);
  fflush(stdin);
  printf("\n STATUS: %s", M.veiculo.status);
  fflush(stdin);
  printf("\n VEZES LOCADO: %d", M.veiculo.qtdLocacoes);
  fflush(stdin);
  printf("\n LUCRO GERADO: R$ %.2f", M.veiculo.valorTotal);
  fflush(stdin);
  printf("\n ======================================================\n");
}

void listarTodasManutencoes(ListaManutencao LM) {
  int i;
  if (verificarListaManutencaoVazia(LM)) {
    printf("\nA lista esta vazia (LISTAR MANUTENCOES)\n");
    system("pause");
  } else {
    printf("\n=======> LISTAGEM DAS MANUTENCOES <=======\n\n");
    for (i = LM.prim; i < LM.ult; i++) {
      exibirManutencao(LM.itemMan[i]);
    }
  }
}

void consultarManutencao(ListaManutencao LM, MANUTENCAO X) {
  int i;

  if (verificarListaManutencaoVazia(LM)) {
    printf("\nA lista esta vazia (CONSULTAR MANUTENCAO)\n");
    system("pause");
  } else {
    i = LM.prim;

    // Buscar veículo em manutenção passando a placa por parâmetro
    while ((i != LM.ult) &&
           (!strcmp(X.veiculo.placa, LM.itemMan[i].veiculo.placa) == 0)) {
      i++;
    }

    if ((i == LM.ult) ||
        (!strcmp(X.veiculo.placa, LM.itemMan[i - 1].veiculo.placa) != 0)) {
      printf("\nVEICULO COM A PLACA %s NAO ENCONTRADO!\n", X.veiculo.placa);
    } else {
      exibirManutencao(LM.itemMan[i]);
    }
  }
}

void removerManutencao(ListaVeiculo *LV, ListaManutencao *LM, VEICULO V,
                       MANUTENCAO *M) {
  int i, j, k;

  if (verificarListaManutencaoVazia(*LM)) {
    printf("\nA lista esta vazia (REMOVER MANUTENCAO)\n");
    system("pause");
  } else {

    i = LM->prim;

    // Buscar veiculo em manutencao passando a placa por parametro
    while ((i != LM->ult) &&
           (!strcmp(V.placa, LM->itemMan[i].veiculo.placa) == 0)) {
      i++;
    }

    if ((i == LM->ult) ||
        (!strcmp(V.placa, LM->itemMan[i - 1].veiculo.placa))) {
      printf("\nVEICULO COM A PLACA %s NAO ENCONTRADO!\n", V.placa);
      fflush(stdin);
    } else {

      int op;
      MANUTENCAO Y = LM->itemMan[i];
      V = LM->itemMan[i].veiculo;

      exibirManutencao(Y);

      // Verificação de Segurança:
      printf("\nDESEJA REALMENTE REMOVER O CADASTRO DESTA MANUTENCAO? (DIGITE "
             "'1' PARA SIM OU '2' PARA NAO)\n");
      scanf("%d", &op);

      if (op == 1) {
        k = LV->prim;
        while ((k != LV->ult) &&
               (!strcmp(V.placa, LV->itemVeic[k].placa) == 0)) {
          k++;
        }

        LV->itemVeic[k].numStatus = 1;
        strcpy(LV->itemVeic[k].status, "DISPONIVEL");

        *M = LM->itemMan[i];
        for (j = i; j < LM->ult - 1; j++) {
          LM->itemMan[j] = LM->itemMan[j + 1];
        }

        LM->ult--;
        LM->tam--;
        printf("\n\nCADASTRO DE MANUTENCAO REMOVIDO COM SUCESSO!\n\n");
        system("pause");
      } else {
        printf("\n\nVOLTANDO AO MENU!\n\n");
        system("pause");
      }
    }
  }
}

// Interface do Usuário
void menu() {
  system("cls");
  printf("\n\n***** SEJA BEM-VINDO! *****\n\n");
  printf("\tMENU\n\n");
  printf("1 - GERENCIAR CLIENTES\n");
  printf("2 - GERENCIAR VEICULOS\n");
  printf("3 - GERENCIAR LOCACOES\n");
  printf("4 - GERENCIAR MANUTENCAO\n");
  printf("5 - ESTATISTICAS E FATURAMENTO\n");
  printf("6 - SAIR E GRAVAR OS DADOS\n");
  printf("\nENTRE COM A OPCAO DESEJADA: ");
}

void submenuCliente() {
  system("cls");
  printf("\n\n***** CLIENTES *****\n\n");
  printf("1 - CADASTRAR CLIENTE\n");
  printf("2 - CONSULTAR CLIENTE\n");
  printf("3 - LISTAR CLIENTES\n");
  printf("4 - REMOVER CLIENTE\n");
  printf("5 - VOLTAR\n");
  printf("\nENTRE COM A OPCAO DESEJADA: ");
}

void submenuVeiculo() {
  system("cls");
  printf("\n\n***** VEICULOS *****\n\n");
  printf("1 - CADASTRAR VEICULO\n");
  printf("2 - CONSULTAR VEICULO\n");
  printf("3 - LISTAR VEICULOS\n");
  printf("4 - REMOVER VEICULO\n");
  printf("5 - VOLTAR\n");
  printf("\nENTRE COM A OPCAO DESEJADA: ");
}

void submenuLocacao() {
  system("cls");
  printf("\n\n***** LOCACOES *****\n\n");
  printf("1 - CADASTRAR LOCACAO\n");
  printf("2 - CONSULTAR LOCACAO\n");
  printf("3 - LISTAR LOCACOES\n");
  printf("4 - REMOVER LOCACAO\n");
  printf("5 - VOLTAR\n");
  printf("\nENTRE COM A OPCAO DESEJADA: ");
}

void submenuManutencao() {
  system("cls");
  printf("\n\n***** MANUTENCAO *****\n\n");
  printf("1 - INSERIR VEICULO\n");
  printf("2 - CONSULTAR VEICULO EM MANUTENCAO\n");
  printf("3 - LISTAR VEICULOS EM MANUTENCAO\n");
  printf("4 - RETIRAR VEICULO DA MANUTENCAO\n");
  printf("5 - VOLTAR\n");
  printf("\nENTRE COM A OPCAO DESEJADA: ");
}

// CRUDs
void switchCRUDCliente(ListaCliente *LC, CLIENTE *C) {

  int codCliente;

  CLIENTE AC;
  ListaCliente ALC;

  AC = *C;
  ALC = *LC;

  do {
    submenuCliente();
    scanf("%d", &subOpcao);

    switch (subOpcao) {
    case 1:
      system("cls");
      codCliente = ALC.contCodigos;
      cadastrarCliente(&AC, codCliente);
      inserirCliente(&ALC, AC);
      ALC.contCodigos++;
      tcl_enter();
      break;

    case 2:
      system("cls");
      printf("\nEntre com o cpf do cliente que deseja consultar:\n");
      fflush(stdin);
      fgets(AC.cpf, 50, stdin);
      consultarCliente(ALC, AC);
      tcl_enter();
      break;

    case 3:
      system("cls");
      listarTodosClientes(ALC);
      printf("\n FINAL DA LISTA \n");
      tcl_enter();
      break;

    case 4:
      system("cls");
      printf("\nEntre com o cpf do cliente que deseja remover:\n");
      fflush(stdin);
      fgets(AC.cpf, 50, stdin);
      removerCliente(&ALC, &AC);
      consultarCliente(ALC, AC);
      tcl_enter();
      break;

    case 5:
      system("cls");
      fflush(stdin);
      menu();
      break;

    default:
      printf("Selecione apenas uma das opcoes apresentadas! (1 a 5)\n");
    }
  } while (subOpcao != 5);

  *C = AC;
  *LC = ALC;
}

void switchCRUDVeiculo(ListaVeiculo *LV, VEICULO *V) {

  int codVeiculo;

  VEICULO AV;
  ListaVeiculo ALV;

  AV = *V;
  ALV = *LV;

  do {
    submenuVeiculo();
    scanf("%d", &subOpcao);

    switch (subOpcao) {
    case 1:
      system("cls");
      codVeiculo = ALV.contCodigos;
      cadastrarVeiculo(&AV, codVeiculo);
      inserirVeiculo(&ALV, AV);
      ALV.contCodigos++;
      tcl_enter();
      break;

    case 2:
      system("cls");
      printf("\nEntre com a placa do veiculo que deseja consultar:\n");
      fflush(stdin);
      fgets(AV.placa, 50, stdin);
      consultarVeiculo(ALV, AV);
      tcl_enter();
      break;

    case 3:
      system("cls");
      listarTodosVeiculos(ALV);
      printf("\n FINAL DA LISTA\n");
      tcl_enter();
      break;

    case 4:
      system("cls");
      printf("\nEntre com a placa do veiculo que deseja remover:\n");
      fflush(stdin);
      fgets(AV.placa, 50, stdin);
      removerVeiculo(&ALV, &AV);
      consultarVeiculo(ALV, AV);
      tcl_enter();
      break;

    case 5:
      system("cls");
      menu();
      break;

    default:
      printf("Selecione apenas uma das opcoes apresentadas! (1 a 5)\n");
      break;
    }

  } while (subOpcao != 5);

  *V = AV;
  *LV = ALV;
}

void switchCRUDLocacao(ListaCliente *LC, ListaVeiculo *LV, ListaLocacao *LL,
                       CLIENTE *C, VEICULO *V, LOCACAO *L) {

  int codLocacao;
  int sucessoLocacao = 0;

  CLIENTE AC;
  VEICULO AV;
  LOCACAO AL;
  ListaCliente ALC;
  ListaVeiculo ALV;
  ListaLocacao ALL;

  AC = *C;
  AV = *V;
  AL = *L;
  ALC = *LC;
  ALV = *LV;
  ALL = *LL;

  do {
    submenuLocacao();
    scanf("%d", &subOpcao);

    switch (subOpcao) {
    case 1:
      system("cls");
      codLocacao = ALL.contCodigos;
      sucessoLocacao =
          cadastrarLocacao(&ALC, &ALV, /*&*/ AC, /*&*/ AV, &AL, codLocacao);
      if (sucessoLocacao == 0) {
        inserirLocacao(&ALL, AL);
        ALL.contCodigos++;
      }
      tcl_enter();
      break;
    case 2:
      system("cls");
      printf("\nEntre com o codigo da locacao que deseja consultar:\n");
      fflush(stdin);
      scanf("%d", &AL.codigo);
      consultarLocacao(ALL, AL);
      tcl_enter();
      break;
    case 3:
      system("cls");
      listarTodasLocacoes(ALL);
      printf("\n FINAL DA LISTA \n");
      tcl_enter();
      break;
    case 4:
      system("cls");
      printf("\nEntre com o codigo da locacao que deseja remover:\n");
      fflush(stdin);
      scanf("%d", &AL.codigo);
      removerLocacao(&ALC, &ALV, &ALL, AC, AV, &AL);
      consultarLocacao(ALL, AL);
      tcl_enter();
      break;
    case 5:
      system("cls");
      menu();
      break;
    default:
      printf("Selecione apenas uma das opcoes apresentadas! (1 a 5)\n");
      break;
    }

  } while (subOpcao != 5);

  *C = AC;
  *V = AV;
  *L = AL;
  *LC = ALC;
  *LV = ALV;
  *LL = ALL;
}

void switchCRUDManutencao(ListaVeiculo *LV, ListaManutencao *LM, VEICULO *V,
                          MANUTENCAO *M) {

  int codManutencao;
  int sucessoManutencao = 0;

  VEICULO AV;
  MANUTENCAO AM;
  ListaVeiculo ALV;
  ListaManutencao ALM;

  AV = *V;
  AM = *M;
  ALV = *LV;
  ALM = *LM;

  do {
    submenuManutencao();
    scanf("%d", &subOpcao);

    switch (subOpcao) {
    case 1:
      system("cls");
      codManutencao = ALM.contCodigos;
      sucessoManutencao = cadastrarManutencao(&ALV, AV, &AM, codManutencao);
      if (sucessoManutencao == 0) {
        inserirManutencao(&ALM, AM);
        ALM.contCodigos++;
      }
      tcl_enter();
      break;
    case 2:
      system("cls");
      printf("\nEntre com a placa do veiculo em manutencao que deseja "
             "consultar:\n");
      fflush(stdin);
      fgets(AM.veiculo.placa, 50, stdin);
      consultarManutencao(ALM, AM);
      tcl_enter();
      break;
    case 3:
      system("cls");
      listarTodasManutencoes(ALM);
      printf("\n FINAL DA LISTA\n ");
      tcl_enter();
      break;
    case 4:
      system("cls");
      printf(
          "\nEntre com a placa do veiculo em manutencao que deseja remover:\n");
      fflush(stdin);
      fgets(AV.placa, 50, stdin);
      removerManutencao(&ALV, &ALM, AV, &AM);
      tcl_enter();
      break;
    case 5:
      system("cls");
      menu();
      break;
    default:
      printf("Selecione apenas uma das opcoes apresentadas! (1 a 5)\n");

      break;
    }

  } while (subOpcao != 5);

  *V = AV;
  *M = AM;
  *LV = ALV;
  *LM = ALM;
}

// Estatísticas e Previsão de Faturamento
void estatisticasPrevisaoFaturamento(ListaCliente *LC, ListaVeiculo *LV,
                                     ListaLocacao *LL) {

  int i;
  int qtdCliTotal = 0, qtdCliComRes = 0, qtdCliSemRes = 0;
  int qtdVeicTotal = 0, qtdVeicDisp = 0, qtdVeicLoc = 0, qtdVeicMan = 0;
  int qtdLocTotal = 0;
  float valorLocacoes = 0.0, despesaLocacoes = 0.0, lucroLocacoes = 0.0;

  qtdCliTotal = LC->tam;
  qtdVeicTotal = LV->tam;
  qtdLocTotal = LL->tam;

  for (i = LC->prim; i < LC->ult; i++) {
    if (LC->itemCli[i].fezReserva > 0) {
      qtdCliComRes++;
    }
  }

  qtdCliSemRes = qtdCliTotal - qtdCliComRes;

  for (i = LV->prim; i < LV->ult; i++) {
    if (LV->itemVeic[i].numStatus == 1) {
      qtdVeicDisp++;
    } else if (LV->itemVeic[i].numStatus == 2) {
      qtdVeicLoc++;
    } else if (LV->itemVeic[i].numStatus == 3) {
      qtdVeicMan++;
    }
  }

  for (i = LL->prim; i < LL->ult; i++) {
    valorLocacoes += LL->itemLoc[i].valorTotal;
    despesaLocacoes += LL->itemLoc[i].despesaTotal;
    lucroLocacoes += LL->itemLoc[i].lucroLocacao;
  }

  printf("\n\n************* ESTATISTICAS *************\n\n");
  printf("\n--------- CLIENTES ---------\n");
  printf("\nClientes com reservas: %d\n", qtdCliComRes);
  printf("\nClientes sem reservas: %d\n", qtdCliSemRes);
  printf("\nTOTAL DE CLIENTES: %d\n", qtdCliTotal);
  printf("\n--------- VEICULOS ---------\n");
  printf("\nVeiculos disponiveis: %d\n", qtdVeicDisp);
  printf("\nVeiculos reservados: %d\n", qtdVeicLoc);
  printf("\nVeiculos em manutencao: %d\n", qtdVeicMan);
  printf("\nTOTAL DE VEICULOS: %d\n", qtdVeicTotal);
  printf("\n\n******** PREVISAO DE FATURAMENTO ********\n\n");
  printf("Ate 31/12/2020\n");
  printf("\n--------- LOCACOES ---------\n");
  printf("\nReservas de locacoes: %d\n", qtdLocTotal);
  printf("\nValor total das locacoes: R$ %.2f\n", valorLocacoes);
  printf("\nDespesa total das locacoes: R$ %.2f\n", despesaLocacoes);
  printf("\nFATURAMENTO: R$ %.2f\n", lucroLocacoes);
  printf("\n----------------------------\n");
  printf("\n0 - VOLTAR\n");

  int opcao;
  scanf("%d", &opcao);

  while (opcao != 0) {
    system("cls");
    printf("OPCAO INVALIDA: aperte 0 para voltar ao menu principal!\n");
    scanf("%d", &opcao);
  }
}

// Arquivos
void gravarClientes(ListaCliente LC) {
  FILE *fp;
  fp = fopen("arquivoClientes.dat", "wb");
  if (fp == NULL) {
    printf("\nErro ao gravar o arquivo.\n");
    return;
  } else {
    // printf("Arquivo binario criado com sucesso!\n");
    fwrite(&LC, sizeof(ListaCliente), 1, fp);
  }
  fclose(fp);
}

void carregarClientes(ListaCliente *LC) {
  FILE *fp;
  fp = fopen("arquivoClientes.dat", "rb");
  if (fp == NULL) {
    printf("\nErro ao carregar o arquivo.\n");
    return;
  } else {
    fread(&(*LC), sizeof(ListaCliente), 1, fp);
    fclose(fp);
  }
}

void gravarVeiculos(ListaVeiculo LV) {
  FILE *fp;
  fp = fopen("arquivoVeiculos.dat", "wb");
  if (fp == NULL) {
    printf("\nErro ao gravar o arquivo.\n");
    return;
  } else {
    // printf("Arquivo binario criado com sucesso!\n");
    fwrite(&LV, sizeof(ListaVeiculo), 1, fp);
  }
  fclose(fp);
}

void carregarVeiculos(ListaVeiculo *LV) {
  FILE *fp;
  fp = fopen("arquivoVeiculos.dat", "rb");
  if (fp == NULL) {
    printf("\nErro ao carregar o arquivo.\n");
    return;
  } else {
    fread(&(*LV), sizeof(ListaVeiculo), 1, fp);
    fclose(fp);
  }
}

void gravarLocacoes(ListaLocacao LL) {
  FILE *fp;
  fp = fopen("arquivoLocacoes.dat", "wb");
  if (fp == NULL) {
    printf("\nErro ao gravar o arquivo.\n");
    return;
  } else {
    // printf("Arquivo binario criado com sucesso!\n");
    fwrite(&LL, sizeof(ListaLocacao), 1, fp);
  }
  fclose(fp);
}

void carregarLocacoes(ListaLocacao *LL) {
  FILE *fp;
  fp = fopen("arquivoLocacoes.dat", "rb");
  if (fp == NULL) {
    printf("\nErro ao carregar o arquivo.\n");
    return;
  } else {
    fread(&(*LL), sizeof(ListaLocacao), 1, fp);
    fclose(fp);
  }
}

void gravarManutencoes(ListaManutencao LM) {
  FILE *fp;
  fp = fopen("arquivoManutencoes.dat", "wb");
  if (fp == NULL) {
    printf("\nErro ao gravar o arquivo.\n");
    return;
  } else {
    // printf("Arquivo binario criado com sucesso!\n");
    fwrite(&LM, sizeof(ListaManutencao), 1, fp);
  }
  fclose(fp);
}

void carregarManutencoes(ListaManutencao *LM) {
  FILE *fp;
  fp = fopen("arquivoManutencoes.dat", "rb");
  if (fp == NULL) {
    printf("\nErro ao carregar o arquivo.\n");
    return;
  } else {
    fread(&(*LM), sizeof(ListaManutencao), 1, fp);
    fclose(fp);
  }
}

int main() {

  int opcao, verificaMenu = 0;

  CLIENTE C;
  VEICULO V;
  LOCACAO L;
  MANUTENCAO M;
  ListaCliente LC;
  ListaVeiculo LV;
  ListaLocacao LL;
  ListaManutencao LM;

  /*criarListaCliente(&LC);
  criarListaVeiculo(&LV);
  criarListaLocacao(&LL);
  criarListaManutencao(&LM);*/

  carregarClientes(&LC);
  carregarVeiculos(&LV);
  carregarLocacoes(&LL);
  carregarManutencoes(&LM);

  do {
    if (verificaMenu == 0) {
      menu();
      verificaMenu = 1;
    }
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      system("cls");
      switchCRUDCliente(&LC, &C);
      break;

    case 2:
      system("cls");
      switchCRUDVeiculo(&LV, &V);
      break;

    case 3:
      system("cls");
      switchCRUDLocacao(&LC, &LV, &LL, &C, &V, &L);
      break;

    case 4:
      system("cls");
      switchCRUDManutencao(&LV, &LM, &V, &M);
      break;

    case 5:
      system("cls");
      estatisticasPrevisaoFaturamento(&LC, &LV, &LL);
      verificaMenu = 0;
      tcl_enter();
      break;

    case 6:
      system("cls");
      printf("\nTODAS AS ALTERACOES FORAM GRAVADAS COM SUCESSO!\n");
      printf("\nMUITO OBRIGADO POR USAR NOSSO SISTEMA!\n");
      printf("\n------ Feito por AloCar Systems ------\n");
      gravarClientes(LC);
      gravarVeiculos(LV);
      gravarLocacoes(LL);
      gravarManutencoes(LM);
      tcl_enter();
      break;
    default:
      printf("\nENTRADA INVALIDA: Selecione apenas uma das opcoes "
             "apresentadas! (1 a 6)\n");
    }

  } while (opcao != 6);

  return 0;
}
