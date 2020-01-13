#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <io.h>

int quant = 0, sessao[100], incial = 0, qS[100];
const char dir[1000]={}, diretorio[] = "Filmes\\filme1\\", dirr[]= "Filmes\\Principal.txt"; // DEFINE O DIRETORIO PADRÃO A SER USADO


void resgate();

void list();

void cadastro();

void consulta(int x);

void vender(char dir1[250]);

void backup();

int main(){
	system("Color 0A");
	setlocale(LC_CTYPE, "Portuguese");
	if(incial == 0){ // Ao inciar o Programa ele apaga a pasta de Backup e cria a uma nova pasta Bakcup e Filmes.
		resgate();
		incial++;
	}
	char op;
	printf("Escolha uma opção: <L>istar Sessões <C>adastrar Sessão C<O>nsultar Sessão <V>ender Ingresso <S>air\n");
	scanf("%c", &op);
	fflush(stdin);
	
	switch(op){		// Escolhas do menu
	
		case 'L':
		case 'l':
			system ("Cls");
			system ("Color 0A");
			list();
			return main();
		break;

		case 'C':
		case 'c':
			system ("Cls");
			system ("Color 0A");
			cadastro();
			return main();
		break;

		case 'O':
		case 'o':
			system ("Cls");
			system ("Color 0A");
			consulta(0); // Mando um valor 0 para que não incie função vendas em uma comparação no final do escopo
			return main();

		break;
		
		case 'V':
		case 'v':
			system ("Cls");
			system ("Color 0A");
			consulta(1); // Mando um valor 1 para que incie função vendas em uma comparação no final do escopo
			return main();
		break;

		case 'S':
		case 's':
			system("Cls"); 
			backup(); // incia backup e encerra o programa
			
			
		break;
		
		default:
			system("Color 04");				// Caso escreva errada, muda a cor para vermelha e da um aviso de que esta errado.
			printf("Opção Invalida\n");
			system("Pause");
			system("Cls");
			return main();
			
	}
		
	return 0;
}

void resgate(){ // Resgata filmes anteriores
	char c, backup[]="Backup\\Backup01", dir1[200]={}, copy[]= "xcopy /e /q Backup\\Backup01 Filmes\\", qntS[]="dir Filmes\\filme01 > sessao.txt", op;
	int quanti = 0, n, n1, escolha, erro = 1, aux;
	system("rd /s /q Filmes"); // Apaga a pasta Filmes
	system("Color 0A");
	mkdir("Filmes");	// Cria a pasta Filmes 
	mkdir("Backup");	// Cria a pasta Backup
	system("Cls");
	system("Color 0A");
	FILE *Arquivo;
	system("dir Backup > resgate.txt");	
	system("cls");
	strcpy(dir1, dir);
	strcat(dir1, "resgate.txt");
	Arquivo = fopen(dir1, "r");
	do{ // conta quantos arquivos existem
		c = getc(Arquivo);
		if(c == '\n') quanti ++;
		
	}while(c != EOF );
	fclose(Arquivo);
	system("del /q resgate.txt");
	system("cls");
	quanti -= 9;
	if(quanti >= 99){ // Se tiver 99 pastas ou mais, apaga a pasta Backup e cria de novo, assim zerando a quantidade de backup
		system("rd /s /q Backup");
		mkdir("Backup");
		system("Cls");
		quanti = 0;
	}
	if(quanti == 0)	return; // se não existir nenhum backup ele encerra a função

	do{ // Pergunta se gostaria de resgatar alguma sessão
		system("Color 0A");
		printf("Deseja resgatar as sessões? <S>im <N>ão\n");
		scanf("%c", &op);
		fflush(stdin);
		switch (op){
			case 's':
			case 'S':
				erro = 0;
			break;
			case 'n':
			case 'N':
				system("Cls");
				return;
			break;
			default:
				erro = 1;	
				system("Color 04");
				printf("Codigo Invalido\n");
				system("Pause");	
				system("Cls");
		}		
		
	}while(erro == 1);
	
	do{ // da a opção do usuario escolher qual backup vai trabalhar em cima
		system("Color 0A");
		printf("Existem %d backups, qual vc deseja transferir?\n", quanti);
		scanf("%d", &escolha);
		fflush(stdin);
		if(escolha > 0 && escolha <= quanti){
			erro = 0;
		}else{
			erro = 1;
			escolha = 0;
			system("Color 04");
			printf("Opção invalida\n");
			system("Pause");
		}
		
	}while(erro == 1);
	// O restante da função faz as preparações do programa
	aux = strlen(copy);
	aux -= 10;
	copy[aux] = (escolha/10)+48;
	copy[aux+1] = (escolha%10)+48;
	system(copy);
	
	system("dir Filmes > qntfilmes.txt");
	system("Cls");
	Arquivo = fopen("qntfilmes.txt", "r");
	quanti = 0;
	do{
		c = getc(Arquivo);
		if(c == '\n') quanti ++;
		
	}while(c != EOF );
	quanti -= 10;
	fclose(Arquivo);
	system("del /q qntfilmes.txt");
	system("Cls");
	quant = quanti;
	aux = strlen(qntS);
	aux -= 15;
	int cont = 0;
	for(int i = 0; i < quant; i++){
		qntS[aux] = ((i+1)/10) + 48;
		qntS[aux+1] = ((i+1)%10) + 48;
		system(qntS);
		Arquivo = fopen("sessao.txt", "r");
		quanti = 0;
		do{
			c = getc(Arquivo);
			if(c == '\n') quanti ++;
		
		}while(c != EOF );
		fclose(Arquivo);
		system("del /q sessao.txt");
		system("Cls");	
		quanti -= 9;
		qS[i+1] = quanti;
		printf("\n\n");
		for(int j = cont; j < quanti+cont; j++){
			sessao[j+i] = i+1;
		}
		cont += quanti-1;
	}
	system("Cls");
	return;
	
}

void list(){ // Lista as Sessões dentro Principal.txt que contem todos os filmes cadastrados, contendo o codigo, hora, data, e quantidade de poltronas disponiveis
	
	char c;
	
	FILE *principal;
	principal = fopen(dirr, "r");
	if(principal != NULL){	
		do{
		
			c = getc(principal);
			if(c != EOF){
				printf("%c", c);	
			}
							
			
		}while( c != EOF );
		printf("\n");
		system("Pause");
		system("Cls");
	} else{			// Caso não exista o .txt ele dá um aviso que não existe nenhum filme cadastrado
		system("Color 04");
		printf("Não existe nenhum filme cadastrado\n");
		system("Pause");
		system("CLS");
	}
	//fclose(film);
	return;
}

void cadastro(){ // Cadastra novas sessões e filmes
	int hora, aux, erro = 1, opc = 1, opc1=0, nsessao;
	char data[1000], nome[100], codS[1000], op, c[2]= " ", pasta[1000] = "Filmes\\filme01";
	float preco;
	quant++;
	pasta[12] = (quant / 10)+48;
	pasta[13] = (quant % 10)+48;

	
	
	do{ //Laço para a escrita do cadastro
	system("Cls");
	system ("Color 03");
		printf("**===============================================================================================**\n");
		printf("||                                                                                               ||\n");
		printf("|| -> Digite um código que não foi inserido anteriormente;                                       ||\n");	// Lista de instruções para uso 
		printf("|| -> O código deve ser descrito por \"S\" mais dois dígitos, representando a sessão;              ||\n");
		printf("|| -> Insira um hífen separando a sessão do horário;                                             ||\n");
		printf("|| -> No horário, devem ser escritos 2 digitos para a hora e minutos, com um \"h\" entre eles;     ||\n");
		printf("|| -> Caso haja mais de uma sessão por filme, estas devem ser separadas por vírgula e espaço;    ||\n");
		printf("|| -> Devem ser ser colocados em ordem crescente.                                                ||\n");
		printf("|| -> S01-08h30, S02-17h00;                                                                      ||\n");
		printf("|| -> Colocar a data dessa forma: dd/mm/aaaa;                                                    ||\n");
		printf("|| -> No valor do ingresso, não inserir um valor > 99 este deve ser separado com ponto;          ||\n");
		printf("|| -> O nome ou código não devem ter mais de 80 caracteres;                                      ||\n");
		printf("|| -> Caso queira voltar para o menu digite \"exit\" no nome do filme.                             ||\n");
		printf("||                                                                                               ||\n");
		printf("**_______________________________________________________________________________________________**\n\n");
		printf("Digite o nome do filme: ");
		scanf("%[^\n]", &nome);
		fflush(stdin);
		if(strcmp(nome, "exit") == 0){// faz uma condicional caso o usuario queira sair da tela de cadastro
			system("Color 0A");
			system("Cls");
			return;
		 } 
		printf("Digite o código da sessão: ");
		scanf("%[^\n]", &codS);
		fflush(stdin);
		printf("Digite a data da sessão: ");
		scanf("%[^\n]", &data);
		fflush(stdin);
		printf("Digite o preço do ingresso: ");
		scanf("%f", &preco);
		fflush(stdin);
		// Apresentação das informações digitadas pelo usuario para confirmação
		printf("\nNome do filme: %s\n", nome);
		printf("codigo do filme: %s\n", codS);
		printf("Data da sessão: %s\n", data);
		printf("Preço do ingresso: R$%.2f\n", preco);

		do{
			printf("Deseja modificar as informações? <S>im <N>ão\n"); // Da uma opção para redigitar caso alguma informação esteja errada
			scanf("%c", &op);
			fflush(stdin);
				switch (op){
					case 's':
					case 'S':
						erro = 0;		// Erro para 0 para que o usuario quando digitar S após um erro de escrita possa sair do laçõ dessa tela de seleção.
						opc = 1;
						system("Cls");		// Caso o usuario queira redigitar muda a variavel opc para 1, fazendo o do while repetir o processo de digitar os dados.
					break;
					case 'n':
					case 'N':
						aux = strlen(codS); //Pega o tamanho do codigo digitado pelo usuario
						erro = 0;
						for(int i = 0; i < 100; i++){
							if( 55+(i*55) >= aux && aux < 55+((i+1)*55)){ 
								aux -= 10*(i+1);
								break;
							}
						}
						aux /= 9;
						aux ++; // auxiliar passa por um processo para testar quantos codigos foram digitado
						if(aux < 1){
							printf("Informação(ões) incorreta(s)\n");
							system("Color 04");
							system("Pause");							
							system("Cls");							
						} 
						// testa se foi digitado corretament o codigo, data, nome do filme e preço do ingresso
						for(int sec = 0; sec < aux; sec++){
							if((strlen(codS)-9 == 0 || (strlen(codS)-9) % 11 == 0) && not(strlen(codS)-9 < 0) && sessao[(codS[(8*sec)+(3*sec)+1]-48)*10 + (codS[(8*sec)+(3*sec)+2]-48) - 1] == 0 && (codS[(8*sec)+(3*sec)+1] != codS[(8*(sec+1))+3*(sec+1)+1] || codS[(8*sec)+(3*sec)+2] != codS[(8*(sec+1))+3*(sec+1)+2] )&& preco < 100 && strlen(data) == 10 && codS[(8*sec) + (3*sec) +3] == '-' && codS[(8*sec)+(3*sec)+6] == 'h' && data[2] == '/' && data[5] == '/' && preco>=10 && (data[0] >= 48 && data[0] <= 51) && (data[1] >= 48 && data[1] <= 58) && ((data[3] == 48 && (data[4] >= 48 && data[4] <= 58)) || (data[3] == 49 && (data[4] >= 48 && data[4] <= 50))) && ((codS[(8*sec)+(3*sec)+1]-48)*10 + codS[(8*sec)+(3*sec)+2]-48 == 1 || sessao[((codS[(8*sec)+(3*sec)+1]-48)*10 + codS[(8*sec)+(3*sec)+2]-48)-2] != 0)){
								sessao[(codS[((8*sec) + (3*sec) + 1)]-48)*10 + (codS[((8*sec) + (3*sec) + 1)+1]-48)-1] = quant; 
								opc = 0;
							} else {	//Caso não digitado corretamente, força o usuario a digitar novamente e fica com as letras vermelhas
								opc = 1;
								printf("Informação(ões) incorreta(s)\n");
								system("Color 04");
								system("Pause");
								system("Cls");
								sec = aux;
								break;
							}
						}

					break;
					default: //digitar qualquer coisa que não seja "S" ou "N", faz com que o fique vemelho a tela e repita a opção de digitar o que deseja
						system("Color 04");
						erro = 1;
				}
		}while(erro == 1);
	
	}while(opc == 1);
	system("color 03");

	mkdir(pasta);
	qS[quant] = aux; // define qS com a quantidade de sessões daquele filme para fonte de comparação
	for(int sec = 0; sec < aux; sec++){	// Laço de repetição para criar um arquivo .txt dentro da pasta "filme/filmeXX/" aonde XX é o numero do filme

		char aux1[100] = {}, dir1[250]={};
		FILE *film;
		aux1[0] = 'S';
		aux1[1] = codS[(8*sec)+(3*sec)+1];
		aux1[2] = codS[(8*sec)+(3*sec)+2];
		strcat(dir1, dir);
		strcat(dir1, pasta);
		strcat(dir1, "\\");
		aux1[3] = '.'; aux1[4] = 't'; aux1[5]='x'; aux1[6] = 't';
 		strcat(dir1, aux1);		// Diretorio, aonde sera criado o .txt
		film = fopen(dir1, "w");
		if(film == NULL) {	//Caso o arquivo não seja criado, emite um aviso, quando o usuario clicar em algo, volta para o menu
		printf("Arquivo nao criado\n");
		system("Pause");
		system("Cls");
		return;
		}
		
		for(int i = 0; i < 10; i++){ // escreve uma matriz no .txt referente aos lugares
			for(int j = 0; j < 30; j++){
				fprintf(film, "0 "); 
			}
			if ( i != 9)	fprintf(film, "\n");
		}
		
		// armazena em sessão o numero do filme que ela esta relacionada
		
		fclose(film);
	}
	
	// Nessa parte ela fara com que todas as linhas tem 100 carracteres no .txt, para poder fazer uma matriz de caracter em vendas e manipular
	// Além é claro de armazenar as informações no Principal.txt
	FILE *principal;
	principal = fopen(dirr, "a");
	int t = 92 - strlen(codS);
	if(92 > t){
		for(int i = 0; i < t; i++)	strcat(codS, c);		
	}	
	
	
	fprintf(principal, "codigo: %s\n", codS);
	fprintf(principal, "data: %s", data);
	for(int i = 0; i < 84; i++)	fprintf(principal, " ");
	fprintf(principal, "\n");
	
	fprintf(principal, "o horario é: ");
	char codr[100]={}, cd[2]={};
	for(int i = 0; i < aux; i ++){
		cd[0] =  codS[((8*i) + (3*i) + 4)];
		strcat(codr, cd);
		cd[0] = codS[((8*i) + (3*i) + 4)+1];
		strcat(codr, cd);
		cd[0] = codS[((8*i) + (3*i) + 4)+2];
		strcat(codr, cd);
		cd[0] = codS[((8*i) + (3*i) + 4)+3];
		strcat(codr, cd);
		cd[0] = codS[((8*i) + (3*i) + 4)+4];
		strcat(codr, cd);
		
		if(i == aux - 1){
			break;
		}		
		strcat(codr, ", ");
	}
	t = 87 - strlen(codr);
	if(87 > t){
		for(int i = 0; i < t; i++)	strcat(codr, c);		
	}	
	
	
	fprintf(principal, codr);
	fprintf(principal, "\n");
	t = 100 - strlen(nome);
	if(100 > t){
		for(int i = 0; i < t; i++)	strcat(nome, c);		
	}
	
	fprintf(principal, "%s\n", nome);
	fprintf(principal, "Preço: R$%.2f", preco);
	for(int i = 0; i < 86; i++)	fprintf(principal, " ");
	fprintf(principal, "\n");
	fprintf(principal, "Poltronas disponiveis: ");
	char nts[77]={}, cts[8]={};
	for(int i = 0; i < aux; i++){
		strcpy(cts, "SXX-300");
		nsessao =  (codS[((8*i) + (3*i) + 1)]-48)*10 + (codS[((8*i) + (3*i) + 1)+1]-48);
		if(i != aux-1){
				cts[1] = (nsessao/10)+48;
				cts[2] = (nsessao%10)+48;
				strcat(cts, ", ");
				strcat(nts, cts);
		}else{
				cts[1] = (nsessao/10)+48;
				cts[2] = (nsessao%10)+48;
				strcat(nts, cts);
				break;
				
		}
	}
	t = 77 - strlen(nts);
	if(77 > t){
		for(int i = 0; i < t; i++)	strcat(nts, c);		
	}
	
	fprintf(principal, nts);
	fprintf(principal, "\n");
	for(int i = 0; i < 100; i++) fprintf(principal, " ");
	fprintf(principal, "\n");
	fclose(principal);
	system("Cls");
	return;
}

void consulta(int x){ // Mostra os lugares disponiveis e ocupados da sessão, por meio de codigo digitado pelo usuario
	// X é o valor de comparação para que execute ou não a vendas
	int erro = 0;
	
	char exit[5],dir1[250]={};

	do{	// Laço de repetição caso o usuario digite um codigo inexistente
		system("color 0A");
		char cod[10], c, pasta[250] = "Filmes\\filme01", cod1[3] = {}, dir2[250]={};
		int aux, filme, codValor;
		
		strcpy(dir2, dir);
		printf("Digite \"exit\" caso queria voltar para menu\n\n");
		printf("Coloque codigo da sessão: ");
		scanf("%s", &cod);
		fflush(stdin);
		if (strcmp (cod, "exit" ) == 0){ // Caso o usuario queria voltar para o menu, ele digitará "exit"
			system("Color 0A");
			system("Cls");
			return;
		}		
		// Deste ponto ate a lonha "strcpy(dir1, dir2)" é a contrução do diretorio para ser aberto
		// O dir1 vai ser usado para enviar o diretorio para a função vendas, para que facilite o processo
		codValor = ((cod[1]-48)*10 + (cod[2]-48)) - 1;
		filme = sessao[codValor];
		pasta[12] = (filme/10)+48;
		pasta[13] = (filme%10)+48;
		
		strcat(dir2, pasta);
		strcat(dir2, "\\");
		cod1[0] = cod[0]; cod1[1] = cod[1]; cod1[2] = cod[2];
		strcat(dir2, cod1);
		strcat(dir2, ".txt");
		strcpy(dir1, dir2);
		FILE *film;
		film = fopen(dir2, "r");

		
		int venda[10][30], contadorL = 0, contadorC = 0;
		
		if(film != NULL && (cod[0] == 's' || cod[0] == 'S')){ // Verifica se abre o diretorio baseado no codigo digitado
			if(x == 1){ // caso o X seja igual a 1 ele incia o vendas enviando o diretorio
				vender(dir1);
			} else printf("\n");
			erro = 0;
			system("Color 0A");
			do{ // passa a matriz do .txt para uma matriz chamada vendas 
				c = getc(film);	
				if(c != EOF && c != 32){
					if(c == 49){
						venda[contadorL][contadorC] = 1;
						if(contadorL == 9){
							contadorL = 0;
							contadorC++;
						}else{
							contadorC++;	
				
						}
					}
					if(c == 48){
						venda[contadorL][contadorC] = 0;
						if(contadorL == 9){
							contadorL = 0;
							contadorC++;
						}else{
							contadorC++;	
						}	
					}
				}		
			}while( c != EOF );
			
			//Escreve na tela a matriz vendas, a onde estara os lugares
			printf("  | [01][02][03][04][05][06][07][08][09][10][11][12][13][14][15][16][17][18][19][20][21][21][23][24][25][26][27][28][29][30]|\n");
			printf("--+-------------------------------------------------------------------------------------------------------------------------|\n");	
			for(int i = 0; i < 10; i++){ 
				if(i != 0) printf("0");
				printf("%d", 10-i);
				printf("| ");
				for(int j = 0; j < 30; j++){
					if(venda[i][j] == 0){
						printf("[  ]");
					}else printf("[XX]");
				}
				printf("|\n");
				printf("--+-------------------------------------------------------------------------------------------------------------------------|\n");
			}
	
	
	
		}else{ // Caso o codigo seja invalido, faz com que o usuario redigite o codigo e define a cor das letras como vermelha
			printf("Codigo invalido\n");
			erro = 1;
			system("Color 04");
			system("Pause");
			system("Cls");
		}
		//fclose(film);
	}while(erro == 1);	
	
	printf("\n");
	
	system("Pause");
	system("Cls");
	return;
}

void vender(char dir1[250]){ //venda de  lugares
	system("Cls");
	char c, princ[100000], princc[1000][100];
	int aux, erro = 0, contadorL=0, contadorC=0, venda[10][30], in, jn, quantidade, aux1, aux0 = strlen(dir1), aux2 = 0;
	FILE *principal;
	principal = fopen(dirr, "r");
	
	do{ // le o arquivo principal e passa para um vetor de caracter
		c = fgetc(principal);
		if(c != EOF){
			princ[contadorC] = c;
			contadorC++;
		}
		
	}while(c != EOF );
	contadorC=0;
	
	for(int i = 0; i < (quant*7); i++){ // passsa as informações do vertor para uma matriz para que facilite o uso
		for(int j=0; j < 100; j++){
			princc[i][j] = princ[contadorC];
			contadorC++;
		}
		contadorC++;
	}
	
	fclose(principal);
	// lê o diretorio para que possa encontrar a possição que esta a quantidade de poltronas
	aux = ((dir1[aux0 - 10]-48) * 10) + (dir1[aux0 - 9]-48);
	aux1 = ((dir1[aux0 - 6]-48)*10) + (dir1[aux0 - 5]-48); // Filmes\\Filme02\\S02.txt
	if(aux != 1){
		for(int i = 0; i < aux; i++) aux1 -= qS[i];
	}
	if(aux>1) aux2=2*(aux-1);
	// quantidade é igual a quantidade de poltronas livre no Principal.txt
	quantidade = ((princc[(aux*5)+aux2][27+((aux1-1)*9)]-48)*100) + (princc[(aux*5)+aux2][27+((aux1-1)*9)+1]-48)*10 + (princc[(aux*5)+aux2][27+((aux1-1)*9)+2]-48);	
	if(quantidade == 0){
		system("Color 04");
		printf("Sem cadeiras disponiveis\n");
		system("Pause");
		return;
	}
	FILE *film;
	film = fopen(dir1, "r");
	contadorL = 0; contadorC = 0;
	do{ // passa a matriz do .txt para uma matriz chamada vendas 
		c = getc(film);	
		if(c != EOF && c != 32){
			if(c == 49){
				venda[contadorL][contadorC] = 1;
				if(contadorL == 9){
					contadorL = 0;
					contadorC++;
				}else{
					contadorC++;	
				
				}
			}
			if(c == 48){
				venda[contadorL][contadorC] = 0;
				if(contadorL == 9){
					contadorL = 0;
					contadorC++;
				}else{
					contadorC++;	
				}
			}
		}		
	}while( c != EOF );			
	
	contadorL = 0;
	fclose(film);
	
	do{ // laço que se repete até que o usuario insira uma poltrona valida
		system("Color 0A");
		printf("  | [01][02][03][04][05][06][07][08][09][10][11][12][13][14][15][16][17][18][19][20][21][21][23][24][25][26][27][28][29][30]|\n");
		printf("--+-------------------------------------------------------------------------------------------------------------------------|\n");	
		for(int i = 0; i < 10; i++){ 
			if(i != 0) printf("0");
			printf("%d", 10-i);
			printf("| ");
			for(int j = 0; j < 30; j++){
				if(venda[i][j] == 0){
					printf("[  ]");
				}else printf("[XX]");
			}
			printf("|\n");
			printf("--+-------------------------------------------------------------------------------------------------------------------------|\n");
		}
		erro = 0;
		printf("\nObs: coloque escreva fileira espaço o numero da poltrona\ndessa forma: 5 11;\n\n"); // Intrução de uso
		printf("Escolha a fileira e numero da poltrona: ");
		scanf("%d %d", &in, &jn);
		in--;
		in = 10-in;
		if(in > 0 && jn <= 30){
			if(venda[in-1][jn-1] == 0){ // verifica se poltrona já esta sendo usada
				system("Color 0A");
				erro = 0;
				venda[in-1][jn-1] = 1;
		
			}else{ // caso já esteja ela faz com que o usuario redigite o codigo
				printf("Cadeira já ocupada\n");
				erro = 1;
				system("Color 04");
				system("pause");
				system("Cls");
			}
		} else {
				printf("Essa cadeira não existe\n");
				erro = 1;
				system("Color 04");
				system("Pause");
				system("Cls");
		}

	}while(erro == 1);
	
	fclose(film);
	film = fopen(dir1, "w");
	
	for(int i = 0; i < 10; i++){ // rescreve a matriz no .txt
		for(int j = 0; j < 30; j++){
			fprintf(film, "%d ", venda[i][j]);		
			}
		fprintf(film, "\n");
	}
	fclose(film);
	principal = fopen(dirr, "w");
	quantidade--; // subtrai uma unidade de quantidade
	//passa o valor de quantidade para a matriz de caracter
	princc[(aux*5)+aux2][27+((aux1-1)*9)] = (quantidade/100)+48;
	quantidade %= 100;
	princc[(aux*5)+aux2][27+((aux1-1)*9)+1] = (quantidade/10)+48;
	princc[(aux*5)+aux2][27+((aux1-1)*9)+2] = (quantidade%10)+48;
	for(int i = 0; i < ((quant)*7); i++){ // reescreve no Principal.txt com a alteração de poltronas livres
		for(int j = 0; j < 100; j++){
			fprintf(principal, "%c", princc[i][j]);
		}
		fprintf(principal, "\n");
	}
	system("Cls");
	fclose(film);
	fclose(principal);
	fflush(stdin);
	return;
}

void backup(){ // Move a pasta Filmes para o Backup
	char c, backup[]="Backup\\Backup01", dir1[200], copy[200]= "xcopy /e /q Filmes Backup\\Backup01\\";
	int quant = 0, n, n1;
	FILE *Arquivo;
	system("dir Backup > Backup.txt");	
	strcpy(dir1, dir);
	strcat(dir1, "Backup.txt");
	Arquivo = fopen(dir1, "r");
	do{
		c = getc(Arquivo);
		if(c == '\n') quant ++;
		
	}while(c != EOF );
	fclose(Arquivo);
	quant -= 8;
	printf("%d\n", quant);
	n = strlen(backup);
	backup[n-2] = (quant/10)+48;
	backup[n-1] = (quant%10)+48;
	printf("%s\n", backup);
	mkdir(backup);
	
	n1 = strlen(copy);
	copy[n1-3] = (quant/10)+48;
	copy[n1-2] = (quant%10)+48;	
	system(copy);
	system("del /q Backup.txt");
	system("rd /s /q Filmes");
	system("Cls");	
	return;
}

