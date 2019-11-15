#ifndef PESSOA_H
#define PESSOA_H

#define SUCESSO_CADASTRO 1
#define ERRO_CADASTRO_MATRICULA 2
#define ERRO_CADASTRO_SEXO 3
#define ERRO_CADASTRO_CPF 4
#define ERRO_CADASTRO_DATA 5

#define TAM_NOME 100

typedef struct pessoa{
	int matricula;
	Data data_nascimento;
	char nome[TAM_NOME];
	char cpf[TAM_CPF];
	char sexo;
} Pessoa;

int menu_Pessoa();

int menuListar_Pessoa();

void gerenciarListagem_Pessoa(Pessoa lista[], int quantidade, char cabecalho[50]);

int inserir_Pessoa(Pessoa lista[], int quantidade);

void printarMensagemDeErro_Pessoa(int codigo);

void listar_Pessoa(Pessoa lista[], int quantidade);

void ordenarListaPorNome(Pessoa lista[], int max);

int filtrarPorSexo(Pessoa listaIn[], int quantidadeIn, char sexo, Pessoa listaOut[]);

int filtrarPorNome(Pessoa listaIn[], int quantidadeIn, char busca[TAM_NOME], Pessoa listaOut[]);

int filtrarAniversariantes(Pessoa listaIn[], int quantidadeIn, int mes, Pessoa listaOut[]);

#endif
