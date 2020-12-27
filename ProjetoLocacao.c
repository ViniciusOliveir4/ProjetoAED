#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 1000

int codCliente = 0;
int codVeiculo = 0;
int codLocacao = 0;

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
  int diaInicio;
  int diaDevolucao;
  int diaTotal;
  float valorDia;
  float despesaDia;
  float despesaTotal;
  float valorTotal;
} LOCACAO;

// Clientes
typedef struct {
    CLIENTE itemCli[MAX];
    int prim, ult, tam;
} ListaCliente;

void criarListaCliente(ListaCliente *C) {
    C->prim = 0;
    C->ult = 0;
    C->tam = 0;
}

int verificarListaClienteVazia(ListaCliente C) {
    return (C.prim == C.ult);
}

int verificarListaClienteCheia(ListaCliente C) {
    return (C.ult == MAX);
}

void inserirCliente(ListaCliente *C, CLIENTE X) {
    int i, j;

    if(verificarListaClienteCheia(*C)) {
        printf("\nA lista esta cheia (INSERIR CLIENTE)\n");
    } else {
        i = C->prim;
        while((i<C->ult) && (X.codigo>C->itemCli[i].codigo)) {
            i++;
        }
        if(i==C->ult) {
            C->itemCli[i] = X;
        } else {
            for(j=C->ult; j>i; j--){
                C->itemCli[j] = C->itemCli[j-1];
            }
            C->itemCli[i] = X;
        }
        C->ult++;
        C->tam++;
        printf("\nCLIENTE CADASTRADO COM SUCESSO\n");
    }
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
    int i;
    if(verificarListaClienteVazia(LC)) {
        printf("\nA lista esta vazia (LISTAR CLIENTES)\n");
    } else {
        printf("\n=======> LISTAGEM DOS CLIENTES <=======\n\n");
        for(i=LC.prim; i<LC.ult; i++) {
            exibirCliente(LC.itemCli[i]);
        }
    }
}

void consultarCliente(ListaCliente C, CLIENTE X) {
    int i;

    if(verificarListaClienteVazia(C)){
        printf("\nA lista esta vazia (CONSULTAR CLIENTE)\n");
    } else {
        i = C.prim;

        // Buscar cliente passando CPF por parametro
        while((i != C.ult) && (!strcmp(X.cpf, C.itemCli[i].cpf) == 0)){
            i++;
        }

        if((i == C.ult) || (!strcmp(X.cpf, C.itemCli[i-1].cpf))) {
            printf("\nCLIENTE COM O CPF %s NAO ENCONTRADO!\n", X.cpf);
        } else {
            exibirCliente(C.itemCli[i]);
        }
    }
}

void removerCliente(ListaCliente *C, CLIENTE *X) {
    int i, j;

    if(verificarListaClienteVazia(*C)) {
        printf("\nA lista esta vazia (REMOVER CLIENTE)\n");
    } else {

        i = C->prim;

        // Buscar cliente passando CPF por parametro
        while((i != C->ult) && (!strcmp(X->cpf, C->itemCli[i].cpf) == 0)){
            i++;
        }

        if((i == C->ult) || (!strcmp(X->cpf, C->itemCli[i-1].cpf))) {
            printf("\nCLIENTE COM O CPF %s NAO ENCONTRADO!\n", X->cpf);
        } else {

            int op;
            CLIENTE Y = *X;

            exibirCliente(Y);

            //Verificação de Segurança:
            printf("\nDESEJA REALMENTE REMOVER O CADASTRO DESTE CLIENTE? (DIGITE '1' PARA SIM OU '2' PARA NAO)\n");
            scanf("%d", &op);
            if(op == 1) {
                *X = C->itemCli[i];
                for(j=i; j<C->ult-1; j++) {
                    C->itemCli[j] = C->itemCli[j+1];
                }
                C->ult--;
                C->tam--;
                printf("\n\nCADASTRO DE CLIENTE REMOVIDO COM SUCESSO!\n\n");
            } else {
                printf("\n\nVOLTANDO AO MENU!\n\n");
            }
        }
    }
}

// Veículos
typedef struct {
    VEICULO itemVeic[MAX];
    int prim, ult, tam;
} ListaVeiculo;

void criarListaVeiculo(ListaVeiculo *V) {
    V->prim = 0;
    V->ult = 0;
    V->tam = 0;
}

int verificarListaVeiculoVazia(ListaVeiculo V) {
    return (V.prim == V.ult);
}

int verificarListaVeiculoCheia(ListaVeiculo V) {
    return (V.ult == MAX);
}

void inserirVeiculo(ListaVeiculo *V, VEICULO X) {
    int i, j;

    if(verificarListaVeiculoCheia(*V)) {
        printf("\nA lista esta cheia (INSERIR VEICULO)\n");
    } else {
        i = V->prim;
        while((i<V->ult) && (X.codigo>V->itemVeic[i].codigo)) {
            i++;
        }
        if(i==V->ult) {
            V->itemVeic[i] = X;
        } else {
            for(j=V->ult; j>i; j--){
                V->itemVeic[j] = V->itemVeic[j-1];
            }
            V->itemVeic[i] = X;
        }
        V->ult++;
        V->tam++;
        printf("\nVEICULO CADASTRADO COM SUCESSO\n");
    }
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
    int i;
    if(verificarListaVeiculoVazia(LV)) {
        printf("\nA lista esta vazia (LISTAR VEICULOS)\n");
    } else {
        printf("\n=======> LISTAGEM DOS VEICULOS <=======\n\n");
        for(i=LV.prim; i<LV.ult; i++) {
            exibirVeiculo(LV.itemVeic[i]);
        }
    }
}

void consultarVeiculo(ListaVeiculo V, VEICULO X) {
    int i;

    if(verificarListaVeiculoVazia(V)){
        printf("\nA lista esta vazia (CONSULTAR VEICULO)\n");
    } else {
        i = V.prim;

        // Buscar veiculo passando a placa por parametro
        while((i != V.ult) && (!strcmp(X.placa, V.itemVeic[i].placa) == 0)){
            i++;
        }

        if((i == V.ult) || (!strcmp(X.placa, V.itemVeic[i-1].placa) != 0)) {
            printf("\nVEICULO COM A PLACA %s NAO ENCONTRADO!\n", X.placa);
        } else {
            exibirVeiculo(V.itemVeic[i]);
        }
    }
}

void removerVeiculo(ListaVeiculo *V, VEICULO *X) {
    int i, j;

    if(verificarListaVeiculoVazia(*V)) {
        printf("\nA lista esta vazia (REMOVER VEICULO)\n");
    } else {

        i = V->prim;

        // Buscar veiculo passando a placa por parametro
        while((i != V->ult) && (!strcmp(X->placa, V->itemVeic[i].placa) == 0)){
            i++;
        }

        if((i == V->ult) || (!strcmp(X->placa, V->itemVeic[i-1].placa) != 0)) {
            printf("\nVEICULO COM A PLACA %s NAO ENCONTRADO!\n", X->placa);
        } else {

            if(V->itemVeic[i-1].status == 'D'){
                int op;
                VEICULO Y = *X;

                exibirVeiculo(Y);

                //Verificação de Segurança:
                printf("\nDESEJA REALMENTE REMOVER O CADASTRO DESTE VEICULO? (DIGITE '1' PARA SIM OU '2' PARA NAO)\n");
                scanf("%d", &op);
                if(op == 1) {
                    *X = V->itemVeic[i];
                    for(j=i; j<V->ult-1; j++) {
                        V->itemVeic[j] = V->itemVeic[j+1];
                    }
                    V->ult--;
                    V->tam--;
                    printf("\n\nCADASTRO DE VEICULO REMOVIDO COM SUCESSO!\n\n");
                } else {
                    printf("\n\nVOLTANDO AO MENU!\n\n");
                }
            } else {
                printf("\n\nNAO EH POSSIVEL REMOVER VEICULO COM STATUS R(Reservado) OU ""M(Manutencao)\n\n");
            }
        }
    }
}

// Locações
typedef struct {
    LOCACAO itemLoc[MAX];
    int prim, ult, tam;
} ListaLocacao;

void criarListaLocacao(ListaLocacao *L) {
    L->prim = 0;
    L->ult = 0;
    L->tam = 0;
}

int verificarListaLocacaoVazia(ListaLocacao L) {
    return (L.prim == L.ult);
}

int verificarListaLocacaoCheia(ListaLocacao L) {
    return (L.ult == MAX);
}

void inserirLocacao(ListaLocacao *L, LOCACAO X) {
    int i, j;

    if(verificarListaLocacaoCheia(*L)) {
        printf("\nA lista esta cheia (INSERIR LOCACAO)\n");
    } else {
        i = L->prim;
        while((i<L->ult) && (X.codigo>L->itemLoc[i].codigo)) {
            i++;
        }
        if(i==L->ult) {
            L->itemLoc[i] = X;
        } else {
            for(j=L->ult; j>i; j--){
                L->itemLoc[j] = L->itemLoc[j-1];
            }
            L->itemLoc[i] = X;
        }
        L->ult++;
        L->tam++;
        printf("\nLOCACAO CADASTRADA COM SUCESSO\n");
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
    int i;
    if(verificarListaLocacaoVazia(LL)) {
        printf("\nA lista esta vazia (LISTAR LOCACOES)\n");
    } else {
        printf("\n=======> LISTAGEM DAS LOCACOES <=======\n\n");
        for(i=LL.prim; i<LL.ult; i++) {
            exibirLocacao(LL.itemLoc[i]);
        }
    }
}

void consultarLocacao(ListaLocacao L, LOCACAO X) {
    int i;

    if(verificarListaLocacaoVazia(L)){
        printf("\nA lista esta vazia (CONSULTAR LOCACAO)\n");
    } else {
        i = L.prim;

        // Buscar locacao pelo codigo
        while((i != L.ult) && (X.codigo!=0 && L.itemLoc[i].codigo!=0)){
            i++;
        }

        if((i == L.ult) || (X.codigo!=0 && L.itemLoc[i].codigo!=0)) {
            printf("\nLOCACAO COM O CODIGO %d NAO ENCONTRADO!\n", X.codigo);
        } else {
            exibirLocacao(L.itemLoc[i]);
        }
    }
}

void removerLocacao(ListaLocacao *L, LOCACAO *X) {
    int i, j;

    if(verificarListaLocacaoVazia(*L)) {
        printf("\nA lista esta vazia (REMOVER LOCACAO)\n");
    } else {

        i = L->prim;

        // Buscar locacao pelo codigo
        while((i != L->ult) && (X->codigo!=0 && L->itemLoc[i].codigo!=0)){
            i++;
        }

        if((i == L->ult) || (X->codigo!=0 && L->itemLoc[i].codigo!=0)) {
            printf("\nLOCACAO COM O CODIGO %d NAO ENCONTRADO!\n", X->codigo);
        } else {

            int op;
            LOCACAO Y = *X;

            exibirLocacao(Y);

            //Verificação de Segurança:
            printf("\nDESEJA REALMENTE REMOVER O CADASTRO DESTA LOCACAO? (DIGITE '1' PARA SIM OU '2' PARA NAO)\n");
            scanf("%d", &op);
            if(op == 1) {
                *X = L->itemLoc[i];
                for(j=i; j<L->ult-1; j++) {
                    L->itemLoc[j] = L->itemLoc[j+1];
                }
                L->ult--;
                L->tam--;
                printf("\n\nCADASTRO DE LOCACAO REMOVIDO COM SUCESSO!\n\n");
            } else {
                printf("\n\nVOLTANDO AO MENU!\n\n");
            }
        }
    }
}


// Interface do Usuário
void menu() {
  printf("\n\n***** SEJA BEM-VINDO! *****\n\n");
  printf("\tMENU\n\n");
  printf("1 - GERENCIAR CLIENTES\n");
  printf("2 - GERENCIAR VEICULOS\n");
  printf("3 - GERENCIAR LOCACOES\n");
  printf("4 - GERENCIAR MANUTENCAO\n");
  printf("5 - PREVISAO DE FATURAMENTO\n");
  printf("6 - SAIR\n");
  printf("\nENTRE COM A OPCAO DESEJADA: ");
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
    CLIENTE C;
    ListaCliente lc;

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
            printf("\nEntre com o cpf do clinte que deseja consultar:\n");
            fflush(stdin);
            fgets(C.cpf, 50, stdin);
            //scanf("%d", &C.cpf);
            consultarCliente(lc, C);
            break;

        case 3:
            listarTodosClientes(lc);
            printf("\n FINAL DA LISTA \n");
            break;

        case 4:
          printf("\nEntre com o cpf do cliente que deseja remover:\n");
          fflush(stdin);
          fgets(C.cpf, 50, stdin);
          removerCliente(&lc, &C);
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
    }while(subOpcao != 5);
}

void switchCRUDVeiculo() {

  VEICULO V;
  ListaVeiculo lv;
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
      fflush(stdin);
      fgets(V.placa, 50, stdin);
      consultarVeiculo(lv, V);
      break;

    case 3:
      listarTodosVeiculos(lv);
      printf("\n FINAL DA LISTA\n ");
      break;

    case 4:
      printf("\nEntre com a placa do veículo que deseja remover:\n");
      fflush(stdin);
      fgets(V.placa, 50, stdin);
      removerVeiculo(&lv, &V);
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

void switchCRUDLocacao() {
  LOCACAO L;
  VEICULO V;
  CLIENTE C;
  ListaVeiculo lv;
  ListaCliente lc;
  ListaLocacao ll;
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
      listarTodasLocacoes(ll);
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

int main() {

    int opcao;

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
            printf("\nENTRADA INVALIDA: Selecione apenas uma das opcoes apresentadas! (1 a 6)\n");
        }

    }while(opcao != 6);

    return 0;
}



