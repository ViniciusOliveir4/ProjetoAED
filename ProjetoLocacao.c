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

typedef struct{
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
}CLIENTE;

typedef struct{
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
}VEICULO;

typedef struct {
  CLIENTE cliente;
  VEICULO veiculo;
  DIA diaInicio;
  DIA diaDevolucao;
  DIA diaTotal;
  float valorDia;
  float despesaDia;
  float despesaTotal;
}LOCACAO;

// Clientes
typedef struct elemC {
  CLIENTE cli;
  struct elemC *prox;
} CaixaCliente;

typedef CaixaCliente *pC;

typedef struct {
  pC prim, ult;
  int qtd;
}ListaCliente;

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
  printf("======> CADASTRAR CLIENTE <======\n");
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
  printf("=======> DADOS DO CLIENTE <=======\n\n");
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

void listarTodosClientes(ListaCliente LC){
    pC c = LC.prim;

    while(c != LC.ult){
        exibirCliente(c->prox->cli);
        c = c->prox;
    }
}

void consultarCliente(ListaCliente C, CLIENTE X){
    pC p;

    p=C.prim;

    //buscar cliente passando cpf por parametro
    while ((p!=C.ult)&&( !(strcmp(X.cpf, p->prox->cli.cpf)==0)))
	     p=p->prox;

    if((p==C.ult)||(!(strcmp(X.cpf, p->prox->cli.cpf)==0)))
	     printf("\nCliente com o cpf %s nao encontrado!\n", X.cpf);
    else
        exibirCliente(p->prox->cli);

}

void removerCliente(ListaCliente *C, CLIENTE *X){
    pC p, q;

    p=C->prim;

    //buscar cliente passando cpf por parametro
    while ((p!=C->ult)&&( !(strcmp(X->cpf, p->prox->cli.cpf)==0)))
	     p=p->prox;

    if((p==C->ult)||(!(strcmp(X->cpf, p->prox->cli.cpf)==0)))
	     printf("\nCLIENTE COM O CPF %s NAO ENCONTRADO!\n", X->cpf);
    else{
        int op;
        CLIENTE Y = *X;

        exibirCliente(Y);
        //verificação de segurança
        printf("\nDESEJA REALMENTE REMOVER O CADASTRO DESTE CLIENTE?\n(DIGITE 1 PARA SIM OU 2 PARA NAO)\n");
        scanf("%d", &op);

        if(op == 1){
            q=p->prox;
            *X = q->cli;
            p->prox=q->prox;
            if(q==C->ult)
                C->ult=p;
            C->qtd--;
            free(q);
            printf("\n\nCADASTRO DE CLIENTE REMOVIDO COM SUCESSO!\n\n");
        }
        else
            printf("\n\nVOLTANDO AO MENU!\n\n");
    }
}

// Veículos
typedef struct elemenV{
  VEICULO veiculo;
  struct elemenV *prox;
} CaixaVeiculo;

typedef CaixaVeiculo *pV;

typedef struct {
  pV prim, ult;
  int qtd;
}ListaVeiculo;

void criarListaVeiculo(ListaVeiculo *lv) {
  lv->prim = (pV)malloc(sizeof(CaixaVeiculo));
  lv->ult = lv->prim;
  lv->prim->prox = NULL;
  lv->qtd = 0;
}

void inserirVeiculo(ListaVeiculo *lv, VEICULO veic){
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
  printf("=====> CADASTRAR VEICULO <=====\n\n");
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
  scanf("%d", &V->despesaDia);
  printf("\nENTRE COM O STATUS DO VEICULO (D = Disponivel | R = Reservado | M = Em Manutencao): ");
  fflush(stdin);
  V->status = getchar();
  printf("\n\n\n\nVEICULO CADASTRADO COM SUCESSO!\n");
  fflush(stdin);
  V->codigo = ++codVeiculo;
}

void exibirVeiculo(VEICULO V) {
  printf("=======> DADOS DO VEICULO <=======\n\n");
  printf("\n ========================== %3d =======================", V.codigo);
  printf("\n == FABRICANTE: %50s                                 ==", V.fabricante);
  printf("\n == PLACA: %50s                                      ==", V.placa);
  printf("\n == MODELO: %50s                                     ==", V.modelo);
  printf("\n == TIPO: %50s                                       ==", V.tipo);
  printf("\n == COR: %20s                                        ==", V.cor);
  printf("\n == TIPO DE COMBUSTIVEL: %20s                        ==", V.tipoCombustivel);
  printf("\n == ANO: %d                                          ==", V.ano);
  printf("\n == ALUGUEL POR DIA: %.2f                            ==", V.valorDia);
  printf("\n == DESPESA POR DIA: %.2f                            ==", V.despesaDia);
  printf("\n == STATUS: %c                                       ==", V.status);
  printf("\n ======================================================\n");
}

void listarTodosVeiculos(ListaVeiculo LV){
    pV c = LV.prim;

    while(c != LV.ult){
        exibirVeiculo(c->prox->veiculo);
        c = c->prox;
    }
}

void consultarVeiculo(ListaVeiculo LV, VEICULO X){
    pV p;

    p=LV.prim;

    //buscar veiculo passando a placa por parametro
    while ((p!=LV.ult)&&( !(strcmp(X.placa, p->prox->veiculo.placa)==0)))
	     p=p->prox;

    if((p==LV.ult)||(!(strcmp(X.placa, p->prox->veiculo.placa)==0)))
	     printf("\nVEICULO COM A PLACA %s NAO ENCONTRADO!\n", X.placa);
    else
        exibirVeiculo(p->prox->veiculo);
}

void removerVeiculo(ListaVeiculo *LV, VEICULO *X){
    pV p, q;
    p=LV->prim;

    //buscar cliente passando cpf por parametro
    while ((p!=LV->ult)&&( !(strcmp(X->placa, p->prox->veiculo.placa)==0)))
	     p=p->prox;

    if((p==LV->ult)||(!(strcmp(X->placa, p->prox->veiculo.placa)==0)))
	     printf("\nVEICULO COM A PLACA %s NAO ENCONTRADO!\n", X->placa);
    else{
        if(p->prox->veiculo.status == 'D'){

            int op;
            VEICULO Y = *X;

            exibirVeiculo(Y);
            //verificação de segurança
            printf("\nDESEJA REALMENTE REMOVER O CADASTRO DESTE VEICULO?\n(DIGITE 1 PARA SIM OU 2 PARA NAO)\n");
            scanf("%d", &op);

            if(op == 1){
                q=p->prox;
                *X = q->veiculo;
                p->prox=q->prox;
                if(q==LV->ult)
                    LV->ult=p;
                LV->qtd--;
                free(q);
                printf("\n\nCADASTRO DE VEICULO REMOVIDO COM SUCESSO!\n\n");
            }
            else{
                printf("\n\nVOLTANDO AO MENU!\n\n");
            }
        }
        else{
            printf("\n\nNAO EH POSSIVEL REMOVER VEICULO COM STATUS R(Reservado) OU M(Manutencao)\n\n");
        }

    }
}

void menu() {
  printf("=====> SEJA BEM-VINDO! <=====\n\n");
  printf("\tMENU\n\n");
  printf("1 - GERENCIAR CLIENTES\n");
  printf("2 - GERENCIAR VEICULOS\n");
  printf("3 - GERENCIAR LOCACOES\n");
  printf("4 - GERENCIAR MANUTENCAO\n");
  printf("5 - PREVISAO DE FATURAMENTO\n");
  printf("6 - SAIR\n");
  printf("\nENTRE COM A OPCAO DESEJADA: ");
}

int main() {

    CLIENTE X;
    VEICULO Z;
    ListaCliente LC;
    ListaVeiculo LV;
    int i = 2;
    pV v = NULL;
    pC c = NULL;

    criarListaCliente(&LC);
    criarListaVeiculo(&LV);


    // testando funções
    while(i--){
        //cadastrarCliente(&X);
        //inserirCliente(&LC, X);
        cadastrarVeiculo(&Z);
        inserirVeiculo(&LV, Z);
    }

    printf("\nInforme a placa que deseja consultar: ");
    fflush(stdin);
    fgets(Z.placa, 50, stdin);
    consultarVeiculo(LV, Z);

    printf("\nInforme a placa do veiculo que deseja remover: ");
    fflush(stdin);
    fgets(Z.placa, 50, stdin);
    removerVeiculo(&LV, &Z);


    printf("\nInforme a placa do veiculo que deseja remover: ");
    fflush(stdin);
    fgets(Z.placa, 50, stdin);
    removerVeiculo(&LV, &Z);

    listarTodosVeiculos(LV);





    /*printf("\nInforme o cpf que deseja consultar: ");
    fflush(stdin);
    fgets(X.cpf, 50, stdin);
    consultarCliente(LC, X);

    printf("\nInforme o cpf do cliente que deseja remover: ");
    fflush(stdin);
    fgets(X.cpf, 50, stdin);
    removerCliente(&LC, &X);



    listarTodosClientes(LC);*/


    return (0);
}
