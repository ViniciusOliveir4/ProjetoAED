#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int codCliente=0;

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
    int codigo;
    char nome[80];
    char data_nasc[40];
    char cpf[50];
    char endereco [80];
    char telefone [30];
    char email[50];
    float descontoApp;
    int qtdLocacoes;
    float valorTotal;
}CLIENTE;

typedef struct{
    VEICULO veiculo;
    CLIENTE cliente;
    int tempoLocacao;
    float kilometragem;
    float despesa;
    float desconto;
    float valor;
}LOCACAO;

typedef struct Elem{
    CLIENTE cli;
    struct Elem *prox;
}Caixa;

typedef Caixa * ponteiro;

typedef struct{
    ponteiro prim, ult;
    int qtd;
}Lista;

void inicializarListaCliente(Lista *C){
    C->prim =(ponteiro)malloc(sizeof(Caixa));
    C->ult = C->prim;
    C->prim->prox = NULL;
    C->qtd=0;
}

void inserirCliente(Lista *C, CLIENTE X){
    ponteiro p, q;

    q = (ponteiro)malloc(sizeof(Caixa));
    q->cli = X;

    p=C->prim;
    while((p!=C->ult)&&(X.codigo>p->prox->cli.codigo))
        p=p->prox;
     q->prox=p->prox;
     p->prox=q;
     C->qtd++;

     if(p==C->ult)
         C->ult=q;
}

void exibeListaCliente(Lista C){
    ponteiro p;

    printf("\n ********");
    printf("\n * Cab  *");
    printf("\n * List *");
    printf("\n ***<>***");
    printf("\n     V   ");
    p=C.prim->prox;

    while(p!=NULL){
        printf("\n ********");
        printf("\n * %3d  *",p->cli.codigo);
        printf("\n *      *");
        printf("\n ***<>***");
        printf("\n     V   ");
        p=p->prox;
    }
}

void cadastrarCliente(CLIENTE *C){
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


void imprimirCliente(CLIENTE C){
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



int main(){

    CLIENTE X;
    Lista C;
    int i=2;
    ponteiro p=NULL;
    menu();


    inicializarListaCliente(&C);
    //testando funções

   while(i--){
        cadastrarCliente(&X);
        inserirCliente(&C, X);
    }

    p = C.prim;

    while(p!=C.ult){
        imprimirCliente(p->prox->cli);
        p=p->prox;
    }
    printf("\n FINAL DA LISTA\n ");

    return 0;
}
