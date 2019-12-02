#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

//------------STRUCTS------------//

// Struct de Dados
typedef struct{ // Dados do Cliente
    int Id;
	char Nome[25];
	char Cpf[25];
	char Tel[25];
	char Email[25];
	char Endereco[25];
}cliente;

struct Biblioteca{ // Dados da Biblioteca
	int Id;
	char Nome[25];
	char CNPJ[25];
	char Endereco[25];
	char tel[25];
};

typedef struct{// Dados do Livro
	int Id;
	char Nome[25];
	char Autor[25];
	char Editora[25];
}livro;

typedef struct{ // Struct de Usuario
    cliente cliente;
} USER;

typedef struct{ // Struct de Produto
    livro livro;
}PRODUTO;

typedef struct{ // Struct de Aluguel
    int clientID;
    int livroID;
}ALUGUEL;

// Struct Para Arvore
struct NO{ // Estrutura de Nó da Arvore Binaria
    int info;
    struct NO *esq;
    struct NO *dir;
};

typedef struct NO* ArvBin; // Struct Arvore Binaria

// Struct de Lista Sequencial

typedef struct lista Lista;

struct lista{
    int qtd;
    int valor[25];
};

//------------END STRUCTS------------//

void selection_sort(int *vetor[], int tam) {
  int i, j, min, aux;
  for (i = 0; i < (tam-1); i++)
  {
     min = i;
     for (j = (i+1); j < tam; j++) {
       if(vetor[j] < vetor[min])
         min = j;
     }
     if (vetor[i] != vetor[min]) {
       aux = vetor[i];
       vetor[i] = vetor[min];
       vetor[min] = aux;
     }
  }
}

void bubble_sort (int *vetor[], int tam) {
    int k, j, aux;

    for (k = 1; k < tam; k++) {

        for (j = 0; j < tam - k; j++) {

            if (vetor[j] > vetor[j + 1]) {
                aux          = vetor[j];
                vetor[j]     = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}


Lista* cria_lista(){
    Lista *li;
    li = (Lista*) malloc(sizeof(struct lista));
    if(li != NULL)
        li->qtd = 0;
    return li;
}

void libera_lista(Lista* li){
    free(li);
}

int tamanho_lista(Lista* li){
    if(li == NULL)
        return -1;
    else
        return li->qtd;
}
// int x = tamanho_lista(li);

int lista_cheia(Lista* li){
    if(li == NULL)
        return -1;
    return (li->qtd == 25);
}
//int x = lista_cheia(li);
// if(lista_cheia(li))

int lista_vazia(Lista* li){
    if(li == NULL)
        return -1;
    return(li->qtd == 0);
}
//int x = lista_vazia(li);
// if(lista_cheia(li))

int insere_lista(Lista* li, int valor){
    if(li == NULL)
        return 0; // Se for NULL RETORNA 0 PQ DEU ERRO NA INSERÇÃO
    if(lista_cheia(li))
        return 0;// Se a lista estiver cheia retorna 0 pq não pode inserir novos valores
    li->valor[li->qtd] = valor; // Adiciona o Valor (ID do Livro) na lista li->valor[0] = 1;
    li->qtd++; // Adiciona +1 na variavel qtd da lista pra saber quantos valores tem
    return 1; // Retorna 1 mostrando que foi inserido o Valor
}

int remove_lista(Lista* li, int id){
    if(li == NULL) return 0; // se for NULL não tem oque procurar
    if(li->qtd == 0) return 0; // se for vazia não tem oque procurar
    int k,i = 0;
    while(i < li->qtd && li->valor[i] != id) // Percorre a lista procurando o id
        i++;
    if(i == li->qtd) // Elemento não encontrado!
        return 0;
    for(k=i; k < li->qtd+1; k++)
        li->valor[k] = li->valor[k+1];
    li->qtd--;
    return 1;
}
// int x = remove_lista(li, idLivro);

void percorre_lista(Lista* li, PRODUTO * livro){
    int x;
    for(x = 0; x < li->qtd; x++){
        printf("========================================================\n\n");
        printf("Id Do Livro      %d\n\n", livro[x].livro.Id);
        printf("Nome do Livro:   %s\n", livro[x].livro.Nome);
        printf("Nome do Autor:   %s\n", livro[x].livro.Autor);
        printf("Nome do Editora: %s\n", livro[x].livro.Editora);
    }
}

ArvBin* cria_ArvBin(){ // Cria uma Arvore Binaria com a Raiz NULL
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

int estaVazia_ArvBin(ArvBin *raiz){ // Verifica de a Arvore Binaria esta Vazia verificando se a Raiz esta NULL
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

void percorrer_ArvBin(ArvBin *raiz, USER * usuario){ // Percorre a Arvore Binaria imprimindo os valores de Cliente
    if (raiz == NULL)
        return;
    if(*raiz != NULL){
        percorrer_ArvBin(&((*raiz)->esq),usuario);
        percorrer_ArvBin(&((*raiz)->dir), usuario);
        printf("========================================================\n\n");
        printf("ID:       %d\n\n", usuario[(*raiz)->info].cliente.Id);
        printf("Nome:     %s\n", usuario[(*raiz)->info].cliente.Nome);
        printf("Email:    %s\n", usuario[(*raiz)->info].cliente.Email);
        printf("CPF:      %s\n", usuario[(*raiz)->info].cliente.Cpf);
        printf("Tel:      %s\n", usuario[(*raiz)->info].cliente.Tel);
        printf("Endereço: %s\n\n\n", usuario[(*raiz)->info].cliente.Endereco);
    }
}

int insere_ArvBin(ArvBin* raiz, int valor){ // Percorre a Arvore binaria e insere o valor no local adequado
    if (raiz == NULL)
        return 0;
    struct NO* novo;
    novo = (struct NO*) malloc(sizeof(struct NO));
    if (novo == NULL)
        return 0;
    novo->info = valor;
    novo->dir = NULL;
    novo->esq = NULL;
    if(*raiz == NULL)
        *raiz = novo;
    else{
        struct NO* atual = *raiz;
        struct NO* ant = NULL;
        while (atual != NULL){ // Percorre os Nó da arvore ate chegar no NÓ folha
            ant = atual;
            if(valor == atual->info){
                free(novo);
                return 0; // Elemento ja existe!
            }
            if(valor > atual->info)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        if(valor > ant->info) // Insere como filho do NÓ folha
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;
}

struct NO* remove_atual(struct NO* atual){ // Remove 1 Valor da arvore binaria(Ja organizando no processo)
    struct NO *no1, *no2;
    if(atual->esq == NULL){//Sem filho a esquerda. Aponta para o filho da direita
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->esq;
    while(no2->dir != NULL){ // Procura filho mais a direita na sub árvore da esquerda.
        no1 = no2;
        no2 = no2->dir;
    }

    if(no1 != atual){ // Copia o filho mais a direita na sub-árvore esquerda para o lugar do nó removido.
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
};

int remove_ArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL) return 0;
    struct NO* ant = NULL;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info){
            if(atual == *raiz)
                *raiz = remove_atual(atual);
            else{
                if(ant->dir == atual)
                    ant->dir = remove_atual(atual);
                else
                    ant->esq = remove_atual(atual);
            }
            return 1;
        }
        ant = atual;
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
}

int consulta_ArvBin(ArvBin *raiz, int valor){ // Verifica se o valor esta na Arvore Binaria
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info){
            return 1;
        }
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}


// Popula as struct de Usuario e Produto (Cliente/Livro)
void popularBD(USER * usuario, PRODUTO * livro){
    for (int i = 0; i <= 24; i++){
        // Dados Cliente
        usuario[i].cliente.Id = -1;
        strcpy(usuario[i].cliente.Nome, "Nome");
        strcpy(usuario[i].cliente.Cpf, "cpf");
        strcpy(usuario[i].cliente.Tel, "tel");
        strcpy(usuario[i].cliente.Email, "email");
        strcpy(usuario[i].cliente.Endereco, "Endereco");
        // Dados Livro
        livro[i].livro.Id = -1;
        strcpy(livro[i].livro.Nome, "Nome");
        strcpy(livro[i].livro.Autor, "Autor");
        strcpy(livro[i].livro.Editora, "Editora");
    }
}



// Calcula o tamanho do Array Usuario(Cliente)
int tamanhoCliente(USER * usuario){
    int tam = 0;
    for (int i = 0; i <= 24; i++){
        if((strcmp (usuario[i].cliente.Nome, "Nome") == 0)){
            return tam;
        }else{
            tam+=1;
        }
	}
	return tam;
}

//CADASTRAR CLIENTES
void CadastrarCliente(USER * usuario, ALUGUEL * aluguel, ArvBin* raiz){
    int tam = tamanhoCliente(usuario);
    usuario[tam].cliente.Id = tam;
    printf("Informe o Nome Do Usuario: ");
    fgets(usuario[tam].cliente.Nome,100,stdin);
    printf("Informe o CPF Do Usuario: ");
    fgets(usuario[tam].cliente.Cpf,100,stdin);
    printf("Informe o Telefone Do Usuario: ");
    fgets(usuario[tam].cliente.Tel,100,stdin);
    printf("Informe o Email Do Usuario: ");
    fgets(usuario[tam].cliente.Email,100,stdin);
    printf("Informe o Endereço Do Usuario: ");
    fgets(usuario[tam].cliente.Endereco,100,stdin);
    aluguel[tam].clientID = tam;
    insere_ArvBin(raiz, tam);
	//popularAluguel(aluguel, tam); // Popular a Struct Aluguel
    /*printf(" Id: %i \n\n Nome: %s \n CPF: %s \n Tel: %s \n Email: %s \n Endereco: %s\n",
           usuario[tam].cliente.Id,
           usuario[tam].cliente.Nome,
           usuario[tam].cliente.Cpf,
           usuario[tam].cliente.Tel,
           usuario[tam].cliente.Email,
           usuario[tam].cliente.Endereco);*/
    printf("Cliente Cadastrado Com Sucesso!!!\n");
    system("PAUSE");
}

void AlterarCliente(USER * usuario, int ID){
    fflush(stdin);
    printf("\nAntigo Telefone: %s", usuario[ID].cliente.Tel);
    fflush(stdin);
    printf("Informe o Novo Telefone Do Usuario: ");
    fgets(usuario[ID].cliente.Tel,100,stdin);
    printf("\nAntigo Email: %s", usuario[ID].cliente.Email);
    printf("Informe o Novo Email Do Usuario: ");
    fgets(usuario[ID].cliente.Email,100,stdin);
    printf("\nAntigo Endereço: %s", usuario[ID].cliente.Endereco);
    printf("Informe o Novo Endereço Do Usuario: ");
    fgets(usuario[ID].cliente.Endereco,100,stdin);
    printf("Cliente Alterado Com Sucesso!!!\n");
    system("PAUSE");
}

// Calcula o Tamanho do Array de Produto(Livro)
int tamanhoLivro(PRODUTO * livro){
    int tam = 0;
    for (int i = 0; i <= 24; i++){
        if((strcmp (livro[i].livro.Nome, "Nome") == 0)){
            return tam;
        }else{
            tam+=1;
        }
	}
	return tam;
}

// CADASTRAR LIVROS
void CadastrarLivros(PRODUTO * livro, Lista* li){
    int tam = tamanhoLivro(livro);
    livro[tam].livro.Id = tam;
    printf("Informe o Nome Do Livro: ");
    fgets(livro[tam].livro.Nome,100,stdin);
    printf("Informe o Autor Do Livro: ");
    fgets(livro[tam].livro.Autor,100,stdin);
    printf("Informe a Editora Do Livro: ");
    fgets(livro[tam].livro.Editora,100,stdin);
    insere_lista(li, tam);
    /*printf(" Id: %i \n\n Nome: %s \n Autor: %s \n Editora: %s \n",
           livro[tam].livro.Id,
           livro[tam].livro.Nome,
           livro[tam].livro.Autor,
           livro[tam].livro.Editora);*/
    printf("LIVRO CADASTRADO COM SUCESSO!!!\n");
    system("PAUSE");
}


void popularAluguel(ALUGUEL * aluguel){
    for (int i = 0; i <= 24; i++){
        // Dados Cliente
        aluguel[i].clientID = -1;
    }
}

int tamanhoAluguel(ALUGUEL * aluguel){
    int tam = 0;
    for (int i = 0; i <= 24; i++){
            if(aluguel[i].clientID != -1){
                tam+=1;
            }
	}
	return tam;
}
// Faz o Armazenamento do Aluguel de Livro (IdLivro, IdCliente na Struct Aluguel)
void AluguelLivro(ALUGUEL * aluguel){
    int IdCliente;
    int IdLivro;
    printf("Qual o ID do Cliente que deseja Alugar um Livro? ");
    scanf("%d", &IdCliente);
    aluguel[IdCliente].clientID = IdCliente;
    fflush(stdin);
    printf("\nQual o ID do Livro que o Cliente Deseja Alugar? ");
    scanf("%d", &IdLivro);
    aluguel[IdCliente].livroID = IdLivro;
    fflush(stdin);
    system("PAUSE");
}


/*void bubbleSort(NFE nfe[100],NFE *nfeBS[100])
{
	for(int i = 0; i < 100; i++)
	{
		for(int k = 0; k < 99; k++)
		{
			if(strcmp(nfe[k].cliente.Nome,nfe[k+1].cliente.Nome)>0)
			{
				nfeBS[k] = &nfe[k+1];
			}
		}
	}
}*/

// printa o Menu de Opções da Biblioteca
int construirMenu(){
    system("cls");
    int opcao;
    printf("=========================\n");
    printf("     MENU BIBLIOTECA     \n");
    printf("=========================\n\n");
    printf("1.  Consultar Usuarios\n");
    printf("2.  Cadastrar Usuarios\n");
    printf("3.  Excluir Usuarios\n");
    printf("4.  Alterar Usuario\n");
    printf("5.  Aluguel de Livros\n");
    printf("6.  Devolução de Livros\n");
    printf("7.  Listar Livros Do Usuario\n");
    printf("---------------------\n");
    printf("8.  Listar Livros\n");
    printf("9.  Cadastrar Livros\n");
    printf("10. Excluir Livros\n");
    printf("11. Alterar Livros\n");
    printf("---------------------\n");
    printf("0. Sair\n");
    printf("\n");
    printf("Informe uma das opcoes de menu: ");
    scanf("%d", &opcao);
    fflush(stdin);
    system("cls");
    return opcao;
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Portuguese");
	//===================VARIAVEIS=========================//
	int opcao;
	int x;
	int idlivro;
	int idlivroUser;
	int idLivroAlter;
    Lista *li;
    li = cria_lista();
	USER usuario[25]; // Struct USER
	PRODUTO livro[25]; // Struct PRODUTO
	ALUGUEL aluguel[25]; // Struct ALUGUEL
	popularBD(usuario, livro); // Popular a Struct Usuario e Livro
    popularAluguel(aluguel);
	//ArvBin* raiz;
	ArvBin* raiz = cria_ArvBin(); // Cria a Arvore Binaria com a RAIZ = NULL
	//printf("%d", a);
	//if(estaVazia_ArvBin(raiz)){};

	//============================================//

	while (opcao != 0){
        opcao = construirMenu();
        if(opcao == 1){
            int x = estaVazia_ArvBin(raiz);
            if(x == 0){
                percorrer_ArvBin(raiz, usuario);
                system("PAUSE");
            }else{
                printf("A ARVORE ESTA VAZIA!!!\n\n");
                system("PAUSE");
            }
        }
        else if(opcao == 2){
            CadastrarCliente(usuario, aluguel, raiz);
        }
        else if(opcao == 3){
            int x = estaVazia_ArvBin(raiz);
            if(x == 0){
                percorrer_ArvBin(raiz, usuario);
            }else{
                printf("A ARVORE ESTA VAZIA!!!\n\n");
            }
                printf("===========================================\n\n");
                printf("\nQual o ID do Cliente que Deseja Excluir? ");
                scanf("%d", &x);
                remove_ArvBin(raiz, x);
                fflush(stdin);
                printf("CLIENTE EXCLUIDO COM SUCESSO!!!\n");
                system("PAUSE");
        }
        else if(opcao == 4){
            printf("Qual o ID do Cliente que Deseja Alterar?");
            scanf("%d", &x);
            AlterarCliente(usuario, x);
            fflush(stdin);
        }
        else if(opcao ==  5){
            AluguelLivro(aluguel);
        }
        else if(opcao == 6){
            printf("Qual o ID do Cliente que Deseja Devolver o Livro? ");
            scanf("%d", &x);
            aluguel[x].livroID = -1;
            fflush(stdin);
        }
        else if(opcao == 7){ // Mostra o Livro do Usuario
            printf("Qual o ID Do Usuario? ");
            scanf("%d", &idlivroUser);
            if(aluguel[idlivroUser].livroID != -1 && strcmp (livro[idlivroUser].livro.Nome, "Nome") != 0){
                printf("\n\nNome Cliente: %s", usuario[idlivroUser].cliente.Nome);
                printf("Nome Livro:   %s", livro[idlivroUser].livro.Nome);
                printf("Autor Livro:  %s\n", livro[idlivroUser].livro.Autor);
            }else{
                printf("Nenhum Livro Alugado!\n");
            }
            system("PAUSE");
            //LivrosUsuario();
        }
        else if(opcao == 8){ // Lista os Livros Cadastrados
            percorre_lista(li, livro);
            system("PAUSE");
        }
        else if(opcao == 9){ // Cadastra os Livros na struct
            CadastrarLivros(livro, li);
        }
        else if(opcao == 10){ // Exclui o Livro da lista
            printf("Qual o ID Do Livro que Deseja Excluir? ");
            scanf("%d", &idlivro);
            int teste = remove_lista(li, idlivro);
            fflush(stdin);
            if(teste){
                printf("Livro Excluido Com Sucesso!!!\n");
            }
            system("PAUSE");
            //ExcluirLivro();
        }
        else if(opcao == 11){ // Altera os Dados Do Livro Livro[ID]->livro->Valor
                printf("Qual o ID do Livro que Deseja Alterar? ");
                scanf("%d", &idLivroAlter);
                fflush(stdin);
                printf("Informe o Nome Do Livro: ");
                fgets(livro[idLivroAlter].livro.Nome,100,stdin);
                printf("Informe o Autor Do Livro: ");
                fgets(livro[idLivroAlter].livro.Autor,100,stdin);
                printf("Informe a Editora Do Livro: ");
                fgets(livro[idLivroAlter].livro.Editora,100,stdin);
        }
        system("cls");
	}
	return 0;
}
