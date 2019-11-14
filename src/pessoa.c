#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "../include/pessoa.h"

int menu_Pessoa(){

	int opcao;

	printf("1 - Cadastrar\n");
	printf("2 - Listar\n");
	printf("3 - Consultar\n");
	printf("4 - Apagar\n");
	printf("5 - Voltar\n\n");

	printf("Digite a sua opcao\n");
	getchar(); // Para ele não pular linha.
	scanf("%d",&opcao);


	return opcao;
}

int menuListar_Pessoa(){

	int opcao;

	printf("\n");
	printf("1 - Ordenado por nome\n");
	printf("2 - Ordenado por data de nascimento\n");
	printf("3 - Filtrar por sexo\n");
	printf("4 - Filtrar por nome\n");
	printf("5 - Aniversariantes do mes\n\n");

	printf("Digite a sua opcao\n");
	scanf("%d",&opcao);

	return opcao;
}

int inserir_Pessoa(Pessoa lista[], int qtd){

	printf("\nDigite a Matricula\n");
	scanf("%d", &lista[qtd].matricula);
	getchar(); //Funciona melhor no Linux do que fflush(stdin)
	
	if (lista[qtd].matricula <= 0)
		return ERRO_CADASTRO_MATRICULA;

	printf("\nDigite o Nome\n");
	fgets(lista[qtd].nome, TAM_NOME, stdin);

	removerQuebraDeLinha(lista[qtd].nome, strlen(lista[qtd].nome));

	printf("\nDigite o Sexo\n");
	scanf("%c", &lista[qtd].sexo);
	
	lista[qtd].sexo = toupper(lista[qtd].sexo); //Converte Minuscula para Maiuscula
	if(lista[qtd].sexo != 'M' && lista[qtd].sexo != 'F')
		return ERRO_CADASTRO_SEXO;
	
	char nascimento[TAM_DATA];

	printf("\nDigite a data de nascimento no formato 99/99/9999\n");
	fgets(nascimento, TAM_DATA, stdin);
	getchar();
	

/*	if(validarData(nascimento, &lista[qtd].data_nascimento) == 0) Está dando algum erro na Funcao Validar Data.
		return ERRO_CADASTRO_DATA;
		*/
	printf("\nDigite o CPF no formato 999.999.999-99\n");
	fgets(lista[qtd].cpf, TAM_CPF, stdin);
	getchar();

	if(validarCPF(lista[qtd].cpf) == 0)
		return ERRO_CADASTRO_CPF;

	return SUCESSO_CADASTRO;

}

void printarMensagemDeErro_Pessoa(int codigo){
	printf("\nNao foi possivel fazer o Cadastro. Erro: ");
	switch(codigo){
		case ERRO_CADASTRO_MATRICULA:{
			printf("Matricula Invalida\n");
			break;
		}
		case ERRO_CADASTRO_SEXO:{
			printf("Sexo Invalido\n");
			break;
		}
		case ERRO_CADASTRO_CPF:{
			printf("CPF Invalido\n");
			break;
		}
		case ERRO_CADASTRO_DATA:{
			printf("Data Invalida\n");
			break;
		}
		default:{
			printf("Erro Desconhecido\n");
			break;
		}
	}
}

void gerenciarListagem_Pessoa(Pessoa lista[], int qtd, char cabecalho[50]){
	int opcao = menuListar_Pessoa();
	switch(opcao){
		case 1: {
			printf("%s", cabecalho);
			listar_Pessoa(lista, qtd, '-', "---");
			break;
		}
		case 2: {
			printf("Nao implementado\n\n");
			break;
		}
		case 3: {
			printf("\nDigite o sexo pelo qual deseja filtrar [m/f]\n");
			char sexo;
			scanf("%1c", &sexo);

			sexo = toupper(sexo);
			if(sexo == 'M' || sexo == 'F'){
				printf("%s", cabecalho);
				listar_Pessoa(lista, qtd, sexo, "---");
			}else{
				printf("Sexo Invalido\n");
			}
			break;
		}
		case 4: {
			char busca[TAM_NOME];
			int tamanhoBusca;
			do{
				printf("\nDigite o termo de busca\n");
				fgets(busca, TAM_NOME, stdin);
				removerQuebraDeLinha(busca, strlen(busca));
				if(strlen(busca) < 3)
					printf("Minimo de 3 caracteres\n");
			}while(strlen(busca) < 3);
			listar_Pessoa(lista, qtd, '-', busca);
			break;
		}
		case 5: {
			printf("Nao implementado\n\n");
			break;
		}
		default: {
			printf("\nOpcao Invalida\n");
			break;
		}
	}
}

void listar_Pessoa(Pessoa lista[], int qtd, char sexo, char busca[TAM_NOME]){
	int i;

	ordenarListaPorNome(lista, qtd);

	for(i = 0; i < qtd; i++){
		if((sexo == '-' || lista[i].sexo == toupper(sexo)) && (strcmp(busca, "---") == 0 || strstr(lista[i].nome, busca) - lista[i].nome >= 0)){
			printf("------\n");
			printf("Matricula: %d\n", lista[i].matricula);
			printf("Nome: %s\n", lista[i].nome);
			printf("Sexo: %c\n", lista[i].sexo);
			printf("Data de Nascimento %d/%d/%d\n", lista[i].data_nascimento.dia, lista[i].data_nascimento.mes, lista[i].data_nascimento.ano);
			printf("CPF: %s\n", lista[i].cpf);
		}
	}

	printf("------\n\n");
}

void ordenarListaPorNome(Pessoa lista[], int max){
    Pessoa aux;
    int k, j;
    for (k = 0; k < max - 1; k++) {
        for (j = 0; j < max - k - 1; j++) {
            if (strcmp(lista[j].nome, lista[j + 1].nome) > 0) {
                aux = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = aux;
            }
        }
    }
}

int validarCPF(char string[TAM_CPF]){
	char cpf[11];
	strcpy(cpf, string);
    removerChar(cpf, TAM_CPF, '-');
    removerChar(cpf, TAM_CPF, '.');
    
    int i, j, continua = 1;
    
    for(j = 1; j <= 10; j++)
        if(cpf[j - 1] == cpf[j])
            continua = 0;
        else
            continua = 1;
    
    if(continua == 0)
        return 0;
    
    int soma = 0;
    for(i = 10, j = 0; i >= 2; i--, j++)
        soma += (cpf[j] - '0') * i;
    
    int verificador = (soma * 10) % 11;
    
    if(verificador == 10)
        verificador = 0;
    
    if(verificador != (cpf[9] - '0'))
        return 0;
    
    soma = 0;
    for(i = 11, j = 0; i >= 2; i--, j++)
        soma += (cpf[j] - '0') * i;
    
    verificador = (soma * 10) % 11;
    
    if(verificador == 10)
        verificador = 0;
    
    
    return verificador == (cpf[10] - '0');
}

void removerChar(char string[], int tamanho, char remover){
	int i, j;
	for(i = j = 0; j < tamanho; i++, j++){
		if(string[j] == remover)
			j++;
		string[i] = string[j];
	}
	string[i + 1] = '\0';
}

int validarData(char strData[TAM_DATA], Data* data){
	int tamanhoCompactado = 8;
	char nascimento[TAM_DATA];
	strcpy(nascimento, strData);
	removerChar(nascimento, TAM_DATA, '/');
	if(strlen(nascimento) != tamanhoCompactado)
		return 0;

	int i, valido = 1;
	for(i = 0; i < tamanhoCompactado && valido == 1; i++)
		if(nascimento[i] < 48 || nascimento[i] > 57)
			valido = 0;
	
	if(valido == 0)
		return valido;

	int dia, mes, ano;
	dia = ((nascimento[0] - '0') * 10) + (nascimento[1] - '0');
	mes = ((nascimento[2] - '0') * 10) + (nascimento[3] - '0');
	if(mes < 1 || mes > 12)
		return 0;
	
	ano = ((nascimento[4] - '0') * 1000) + ((nascimento[5] - '0') * 100) + ((nascimento[6] - '0') * 10) + (nascimento[7] - '0');
	Data dataA = dataAtual();
	if(ano < 1900 || ano > dataA.ano)
		return 0;

	if (((dia >= 1 && dia <= 31) && (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)) ||
		(dia == 29 && mes == 2 && (ano % 400 == 0 || (ano % 4 == 0 && ano % 100 != 0))) ||
		((dia >= 1 && dia <= 30) && (mes == 4 || mes == 6 || mes == 9 || mes == 11)) ||
		((dia >= 1 && dia <= 28) && (mes == 2))){

		data->dia = dia;
		data->mes = mes;
		data->ano = ano;

		return 1;
	}

	return 0;
}

Data dataAtual(){
	Data data;
	time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);
    data.dia = tm.tm_mday;
    data.mes = tm.tm_mon + 1;
    data.ano = tm.tm_year + 1900;
    return data;
}

void removerQuebraDeLinha(char string[], int tamanho){
	if(string[tamanho - 1] == '\n')
		string[tamanho - 1] = '\0';
}