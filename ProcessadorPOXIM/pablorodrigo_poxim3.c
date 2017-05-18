#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

	/*
	printf("#ARGS = %i\n", argc);
	printf("PROGRAMA = %s\n", argv[0]);
	printf("ARG1 = %s, ARG2 = %s\n", argv[1], argv[2]);
	*/

struct Node{
	unsigned int num;
	struct Node *prox;
};
typedef struct Node no;

//OPERA«’ES
int ContaLinhas(FILE* input);
void interrupcao(unsigned int hexaMemoria, unsigned int *reg, unsigned int *memoria, FILE* output);
void Operacao(unsigned int hexa, unsigned int *reg, unsigned int *memoria, FILE* output, no *PILHA);
void bun(unsigned int hexaMemoria, unsigned int *reg, unsigned int *memoria, FILE* output);
void beq(unsigned int hexaMemoria, unsigned int *reg, unsigned int *memoria, FILE* output);
void blt(unsigned int hexaMemoria, unsigned int *reg, unsigned int *memoria, FILE* output);
void bgt(unsigned int hexaMemoria, unsigned int *reg, unsigned int *memoria, FILE* output);
void bne(unsigned int hexaMemoria, unsigned int *reg, unsigned int *memoria, FILE* output);
void ble(unsigned int hexaMemoria, unsigned int *reg, unsigned int *memoria, FILE* output);
void bge(unsigned int hexaMemoria, unsigned int *reg, unsigned int *memoria, FILE* output);
void bzd (unsigned int hexaMemoria, unsigned int *reg, FILE* output);
void bnz (unsigned int hexaMemoria, unsigned int *reg, FILE* output);
void biv (unsigned int hexaMemoria, unsigned int *reg, FILE* output);
void bni (unsigned int hexaMemoria, unsigned int *reg, FILE* output, unsigned int *memoria);
void isr (unsigned int hexaMemoria, unsigned int *reg, FILE* output);
void reti (unsigned int hexaMemoria, unsigned int *reg, FILE* output);
void add(unsigned int memoria, unsigned int *reg, FILE* output);
void sub(unsigned int memoria, unsigned int *reg, FILE* output);
void mul(unsigned int memoria, unsigned int *reg, FILE* output);
void shr (unsigned int memoria, unsigned int *reg, FILE* output);
void shl (unsigned int memoria, unsigned int *reg, FILE* output);
void addi(unsigned int memoria, unsigned int *reg, FILE* output);
void subi(unsigned int memoria, unsigned int *reg, FILE* output);
void muli(unsigned int memoria, unsigned int *reg, FILE* output);
void divi(unsigned int memoria, unsigned int *reg, FILE* output);
void comp (unsigned int memoria, unsigned int *reg, FILE* output);
void divis(unsigned int memoria, unsigned int *reg, FILE* output);
void compi (unsigned int memoria, unsigned int *reg, FILE* output);
void e (unsigned int memoria, unsigned int *reg, FILE* output);
void ei(unsigned int memoria, unsigned int *reg, FILE* output);
void nao(unsigned int memoria, unsigned int *reg, FILE* output);
void naoi(unsigned int memoria, unsigned int *reg, FILE* output);
void ou(unsigned int memoria, unsigned int *reg, FILE* output);
void oui(unsigned int memoria, unsigned int *reg, FILE* output);
void call (unsigned int hexaMemoria, unsigned int *reg, FILE* output);
void ret (unsigned int hexaMemoria, unsigned int *reg, FILE* output);
void ouExclusivo(unsigned int memoria, unsigned int *reg, FILE* output);
void ouExclusivoi(unsigned int memoria, unsigned int *reg, FILE* output);
void ldw(unsigned int hexaMemoria, unsigned int *reg, unsigned int *memoria, FILE* output);
void ldb(unsigned int hexaMemoria, unsigned int *reg, unsigned int *memoria, FILE* output);
void stw(unsigned int hexaMemoria, unsigned int *reg, unsigned int *memoria, FILE* output);
void stb(unsigned int hexaMemoria, unsigned int *reg, unsigned int *memoria, FILE* output);
void push (unsigned int hexaMemoria, unsigned int *memoria, unsigned int *reg, FILE* output, no *PILHA);
void pop (unsigned int hexaMemoria, unsigned int *memoria, unsigned int *reg, FILE* output, no *PILHA);
// MEMORIA CACHE
int maiorIdade (int id);
char* validade(int validade);
void estatisticas(FILE* output);
void incrementaIdadeDados(unsigned int linha, int idConjunto, unsigned int idLinha);
void incrementaIdadeInstrucao(unsigned int linha, int idConjunto, unsigned int idLinha);
void memoriaCacheInstrucao(unsigned int *reg, unsigned int *memoria, FILE* output);
void memoriaCacheDados(unsigned int *reg, unsigned int *memoria, FILE*output, int func, unsigned int endereco);
void moveBloco(unsigned int linha, unsigned int endereco, unsigned int bloco, unsigned int *memoria ,int identificador);
// INTERRUP«’ES
int watchdog (unsigned int *reg, unsigned int cont, unsigned int en, unsigned int prioridade, FILE* output);
int fpu (unsigned int *memoria, unsigned int prioridade, int contfpu, FILE* output, unsigned int *reg);
unsigned int floatToIEEE754 (float num);
float IEEE754 (int num);
int calculaExpoente (float aux);
void console (FILE* output);


//EITA
	// VARIAVEIS MAIN
	unsigned int salto = 0;
	int qtdMemoria = 0;
	
	//VARIAVEIS TERMINAL
	unsigned int *terminal = NULL;
	unsigned int contTerminal = 0;
	
	//VARIVAIES WATCHDOG
	unsigned int cont = -1, en = 0, pcdog = 0; 
	
	//VARIAVEIS FPU
	int contfpu = 0, controle = 0;
	unsigned int f2200 = 0x2200, f2201 = 0x2201, f2202 = 0x2202, f2203 = 0x2203;
	unsigned int operacaoFPU = 0; //= memoria[control] & 0x0000000F; //= ((memoria[x]/100) & 0x7F800000), expY = ((memoria[y]/100) & 0x7F800000)
	float auxX = 0.0, auxY = 0.0, auxZ;
	int contX = 0, contY = 0;
	
	//VARIAVEIS OPERACAO
	unsigned int operacao = 0;
	unsigned int prioridade = 0; // Pode ser: 0, 1, 2, onde NVL 0 > NVL 1 > NVL 2
	int pendencia[3] = {0};
	
	//MEMORIA CACHE
	typedef struct {
		unsigned int set0[8][7]; 
		unsigned int set1[8][7];
		unsigned int miss, hit;
	}Cache;
	Cache cacheD, cacheI; 

	int indiceIdade = 0; 	
	// inicializar minhas matrizes, com valors no campo de validade

	unsigned int age, id, linha, palavra, bloco; 
	
	
// FIM VARIAVEIS

	
int main (int argc, char* argv[]){

// Algumas declaraÁıes. H·bito de n„o declarar globalmente, ent„o deixe-as ai. 
	FILE* input;
	FILE* output;
    unsigned int j = 0; // qtdLinhas = ContaLinhas(input)
	unsigned int *memoria = (unsigned int *) malloc(sizeof(unsigned int) * 0x8888);
	unsigned int reg[38] = {0}; // 32[PC], 33[IR], 34[ER], 35[FR], 36[CR], 37[IPC]

// Start. 
	terminal = (unsigned int *)malloc(sizeof(unsigned int) * 0x8888);
	input = fopen(argv[1], "r");
	output = fopen(argv[2], "w");

	if(input == NULL || output == NULL){ // verifico se o arquivo abriu corretamente..
		printf("Impossivel abrir o arquivo");
	}else{
		while (!feof(input) ){ // leio do arquivo e armazeno na 'memoria'
			fscanf(input, "%X", &memoria[qtdMemoria]);
			//printf("0x%08X\n", memoria[qtdMemoria]);
			qtdMemoria++;
			
		}
	}
	
//	printf("%d\n", qtdMemoria);
	fprintf(output, "[START OF SIMULATION]\n");
	
// Essa parte de pilha pode ignorar. Talvez na ultima parte do trabalho eu retire. 
	no *PILHA = (no *) malloc(sizeof(no));
	if(!PILHA){
		printf("NO MEMORY!\n");
	}else{
		PILHA->prox = NULL;
	}

// Loop principal. 
	do{
		if (salto != 0){
			Operacao(memoria[salto], reg, memoria, output, PILHA);
		}else{
			Operacao(memoria[j], reg, memoria, output, PILHA);
		}
		j++;
	}while( reg[32] != 0 );
	
	
// Ending. 
	if( contTerminal > 2 ){
		console(output);
		fprintf(output, "[END OF SIMULATION]");
		estatisticas(output);
		printf("\n\n------------------------NAO PODE SER REAL!---------------------------\n");
		free(PILHA);
		//fclose(input);
		//fclose(output);
	}else{
		fprintf(output, "[END OF SIMULATION]");
		estatisticas(output);
		printf("\n\n------------------------NAO PODE SER REAL!---------------------------\n");
		free(PILHA);
		//fclose(input);
		//fclose(output);
	}
	return 0;
}

// Inicio do 'sofrimento' 

int ContaLinhas(FILE* input){

	int qtdLinhas = 0;

	if(input == NULL){
		printf("Impossivel abrir o arquivo");
	}
	while(!feof(input)){
		if( (fgetc(input)) == '\n'){
			qtdLinhas++;
		}
	}
	fclose(input);
	return qtdLinhas;
}

void Operacao(unsigned int hexa, unsigned int *reg, unsigned int *memoria, FILE* output, no *PILHA){

	operacao = (hexa & 0xFC000000) >> 26;
	reg[33] = hexa; // IR = recebe a operacao que est√° sendo executada
	salto++;


    memoriaCacheInstrucao(reg, memoria, output);    
	switch(operacao){
		
		// ADD, SUB, MULT, DIV
		case 0x00: //printf("add\n");
			add(hexa, reg, output);
			break;
		case 0x01: //printf("add com imediato\n");
			addi(hexa, reg, output);
			break;
		case 0x02: //printf("sub\n");
			sub(hexa, reg, output);
			break;
		case 0x03: //printf("sub com imediato\n");
			subi(hexa, reg, output);
			break;
		case 0x04: //printf("mult\n");
			mul(hexa, reg, output);
			break;
		case 0x05: //printf("multi com imediato\n");
			muli(hexa, reg, output);
			break;
		case 0x06: //printf("div");
			divis(hexa, reg, output);
			break;
		case 0x07: //printf("div com imediato\n");
			divi(hexa, reg, output);
			break;

		// COMP, SHL, SHR
		case 0x08: //printf("comp\n");
			comp(hexa, reg, output);
			break;
		case 0x09: //printf("comp com imediato\n");
			compi(hexa, reg, output);
			break;
		case 0x0A: //printf("shiftL\n");
			shl(hexa, reg, output);
			break;
		case 0x0B: //printf("shiftR\n");
			shr(hexa, reg, output);
			break;

		// BOOL (AND, OR, NOT, XOR)
		case 0x0C: //printf("and\n");
			e(hexa, reg, output);
			break;
		case 0x0D: //printf("and com imediato\n");
			ei(hexa, reg, output);
			break;
		case 0x0E: //printf("not\n");
			nao(hexa, reg, output);
			break;
		case 0x0F: //printf("not com imediato\n");
			naoi(hexa, reg, output);
			break;
		case 0x10: //printf("or\n");
			ou(hexa, reg, output);
			break;
		case 0x11: //printf("or com imediato\n");
			oui(hexa, reg, output);
			break;
		case 0x12: //printf("xor\n");
			ouExclusivo(hexa, reg, output);
			break;
		case 0x13: //printf("xor com imediato \n");
			ouExclusivoi(hexa, reg, output);
			break;

		// ldw, stw, ldb, stb
		case 0x14: //printf("ldw\n");
			ldw(hexa, reg, memoria, output);
			break;
		case 0x15: //printf("ldb\n");
			ldb(hexa, reg, memoria, output);
			break;
		case 0x16: //printf("stw\n");
			stw(hexa, reg, memoria, output);
			break;
		case 0x17: //printf("stb\n");
			stb(hexa, reg, memoria, output);
		//	cont  = memoria[0x2020] & 0x7FFFFFFF;
        //   en = (memoria[0x2020] & 0x80000000) >> 31;
			break;

		case 0x18:
			//printf("push\n");
			push(hexa, memoria, reg, output, PILHA);
			break;
		case 0x19:
			//printf("pop\n");
			pop(hexa, memoria, reg, output, PILHA);
			break;

		//bun - desvio incondicional
		case 0x1A: //printf("bun\n");
			bun(hexa, reg, memoria, output);
			break;
		//beq, blt, bgt, bne, ble, bge - desvio condicional
		case 0x1B: //printf("beq\n");
			beq(hexa, reg, memoria, output);
			break;
		case 0x1C: //printf("blt\n");
			blt(hexa, reg, memoria, output);
			break;
		case 0x1D: //printf("bgt\n");
			bgt(hexa, reg, memoria, output);
			break;
		case 0x1E: //printf("bne\n");
			bne(hexa, reg, memoria, output);
			break;
		case 0x1F: //printf("ble\n");
			ble(hexa, reg, memoria, output);
			break;
		case 0x20: //printf("bge\n");
			bge(hexa, reg, memoria, output);
			break;

		case 0x21: //printf("bzd\n");
			bzd(hexa, reg,output);
			break;
		case 0x22: //printf("bzn\n");
			bnz(hexa, reg, output);
			break;
		case 0x23: //printf("biv\n");
			biv(hexa, reg, output);
			break;
		case 0x24: //printf("bni\n");
			bni(hexa, reg, output, memoria);
			break;

		case 0x25:
			//printf("call\n");
			call(hexa, reg, output);
			break;
		case 0x26:
			//printf("ret\n");
			ret(hexa, reg, output);
			break;

		case 0x27: //printf("isr\n");
			isr(hexa, reg, output);
			break;
		case 0x28: //printf("reti\n");
			reti(hexa, reg, output);
			break;

		//int - finaliza a execucao
		case 0x3F: //printf("int\n");
			interrupcao(hexa, reg, memoria, output);
			break;

		default: //printf("default\n");
			fprintf(output,"[INVALID INSTRUCTION @ 0x%08X]\n", reg[32]);
			//printf("PC: 0x%08X\n", reg[32]);
			reg[35] = (reg[35] & 0xFFFFFFDF);
			reg[35] = (reg[35] | 0x00000020);   // FR = |Reservado|IE|IV|OV|ZD|GT|LT|EQ|, IV = 1

			reg[36] = reg[32] >> 2; // CR
			reg[37] = reg[32]+4; // IPC
			reg[32] = 0x0000000C; // PC
			salto = reg[32] >> 2;
            fprintf(output, "[SOFTWARE INTERRUPTION]\n" );
			//printf("Comando invalido\n");
			break;
	}
	
	//fprintf(output, "memoria[0x2020] = 0x%08X\n", memoria[0x2020]);
	//fprintf(output, "cont: %d\n", cont);
	//fprintf(output, "reg[35] = 0x%08X\n", reg[35]);
	
	
	if (memoria[0x2020] != 0){
		if( (memoria[0x2020] & 0x7FFFFFFF) != 0x00000000 ){
			cont  = memoria[0x2020] & 0x7FFFFFFF;
			memoria[0x2020] = memoria[0x2020] & 0x80000000;
		}
    	en = (memoria[0x2020] & 0x80000000) >> 31;
		cont = watchdog(reg, cont, en, prioridade, output);
	}
	//if (memoria[f2203] != 0)
		contfpu = fpu(memoria, prioridade, contfpu, output, reg);		

	


	if( (pendencia[2] != 0) && (pendencia[1] == 0) && (pcdog == reg[32]) ){ //fpu pendente
		if( (reg[35] & 0x00000040) == 0x00000040){ // se o IE estiver ativado
			pendencia[2] = 0;
			// executa a interrupÁ„o
			prioridade = 2;
       		reg[36] = 0x01EEE754; // CR
       		reg[37] = reg[32]; // IPC
       		reg[32] = 0x00000008; // PC
       		salto = (reg[32] >> 2);
      		memoria[f2203] = memoria[f2203] & 0x00000020;
      		fprintf(output, "[HARDWARE INTERRUPTION %d]\n", prioridade);
		}
	}
	
//	fprintf(output, "cont: %d\n", cont);
	
	if( (pendencia[1] != 0)){ //watchdog pendente
		if( (reg[35] & 0x00000040) == 0x00000040){ // se eu IE estiver ativado
			pendencia[1] = 0; // apago pois estou executando a que tava pendente
			// executa a interrupÁ„o
			prioridade = 1;
            reg[36] = 0xE1AC04DA; // CR
            reg[37] = reg[32]; // IPC
            pcdog = reg[37];
            reg[32] = 0x00000004; // PC
            salto = (reg[32] >> 2);
            fprintf(output, "[HARDWARE INTERRUPTION %d]\n", prioridade);
		}
	}
		
}

int watchdog (unsigned int *reg, unsigned int cont, unsigned int en, unsigned int prioridade, FILE* output){
    // WATCHDOG -------------------------------------------------
    //printf("cont: %d\n", cont);
    //printf("en: %d\n", en);
    if (en == 1){
        if (cont == 0){
            if( (reg[35] & 0x00000040) == 0x00000040) {
                //reg[35] = reg[35] & 0xFFFFFFBF;
				prioridade = 1;
                reg[36] = 0xE1AC04DA; // CR
                reg[37] = reg[32]; // IPC
                pcdog = reg[37];
                reg[32] = 0x00000004; // PC
                salto = (reg[32] >> 2);
                fprintf(output, "[HARDWARE INTERRUPTION %d]\n", prioridade);
        	}else{
        		pendencia[1] = 1; //significa que eu tenho um watchdog pendente.   
			}
       }
    }
    
    cont--;
    // FIM WATCHDOG --------------------------------------------- 
    //printf("cont: %d\n", cont);
    return cont; 
}

void console (FILE* output){
	int i = 0;
	fprintf(output, "[TERMINAL]\n");
	for (i = 0; i < contTerminal; i++){
		fprintf(output, "%c", terminal[i]);
	}
	fprintf(output, "\n");
}

int fpu (unsigned int *memoria, unsigned int prioridade, int contfpu, FILE* output, unsigned int *reg){
	
	// Meu X, Y e Z auxiliares.. n„o vou operar nada em memoria
	auxX = (float) memoria[f2200];
	auxY = (float) memoria[f2201];
	//auxZ = (float) memoria[f2202];
	//Controle
	controle = memoria[f2203];
	//Operacao
	operacaoFPU = (memoria[f2203] & 0x0000000F); //pois o cÛdigo da operaÁ„o s„o os ultimos 5 digitos
		
	//Definindo a Operacao
	switch (operacaoFPU){
		case 0x00: 
			//Faz nada
			break;
		case 0x01:
			auxZ = auxX + auxY; // calculo a soma em variaveis float
			contX = calculaExpoente(auxX);
			contY = calculaExpoente(auxY);
			contfpu = abs( (contX - contY) + 1 ); // calculo o valor do contador
			memoria[f2202] = floatToIEEE754(auxZ); // atribuo a mem[z] o valor convertido em ieee 754
			break;
		case 0x02:
			auxZ = auxX - auxY;
			contX = calculaExpoente(auxX);
			contY = calculaExpoente(auxY);
			contfpu = abs( (contX - contY) + 1 );
			memoria[f2202] = floatToIEEE754(auxZ); 
			break;
		case 0x03:
			auxZ = auxX * auxY;
			contX = calculaExpoente(auxX);
			contY = calculaExpoente(auxY);
			contfpu = abs( (contX - contY) + 1 );
			memoria[f2202] = floatToIEEE754(auxZ);
			//printf("AQUI: 0x%08X\n", memoria[f2202]);
			break;
		case 0x04:
			if (auxY == 0.0){
				controle = controle & 0x0000000F; //apago o que tinha no bit de status
				controle = controle | 0x00000020; // ponho status para 1, sinalizando que deu erro.
				memoria[f2203] = controle; 
			}else{
				auxZ = auxX / auxY;
				contX = calculaExpoente(auxX);
				contY = calculaExpoente(auxY);
				contfpu = abs( (contX - contY) + 1 );
				memoria[f2202] = floatToIEEE754(auxZ);
			}
			break; 
		case 0x05:
			auxX =  auxZ;
			contfpu = 1; // Quantidade de ciclos constante para atribuicao, piso, teto, arredondamento
			memoria[f2200] = memoria[f2202];
			break;
		case 0x06: 
			auxY = auxZ;
			contfpu = 1;
			memoria[f2201] = memoria[f2202];
			break;
		case 0x07:
			//fprintf(output, "Z:%d\n", auxZ);
			memoria[f2202] = ceil(auxZ);
			//fprintf(output, "Z:%d\n", auxZ);
			contfpu = 1;
			//memoria[f2202] = auxZ; //floatToIEEE754( (unsigned int)auxZ );
			break;
		case 0x08:
			memoria[f2202] = floor(auxZ);
			contfpu = 1;
			//memoria[f2202] = (int)auxZ; //floatToIEEE754( (unsigned int) auxZ);
			break;
		case 0x09:
			memoria[f2202] = round(auxZ);
			//memoria[f2202] = (int)auxZ; //floatToIEEE754( (unsigned int) auxZ);
			contfpu = 1;
			break;
		default:
			controle = controle & 0x0000000F; //apago o que tinha no bit de status
			controle = controle | 0x00000020; // ponho status para 1, sinalizando que deu erro de instruÁ„o inv·lida
			memoria[f2203] = controle; 
			contfpu = 1;
			break;
	}
		
	//fprintf(output, "Z:0x%08X\n", memoria[f2202]);
		
	if (contfpu == 0){
		if( (reg[35] & 0x00000040) == 0x00000040){
        	//reg[35] = reg[35] & 0xFFFFFFBF;
			prioridade = 2;
            reg[36] = 0x01EEE754; // CR
            reg[37] = reg[32]; // IPC
            reg[32] = 0x00000008; // PC
            salto = (reg[32] >> 2);
            memoria[f2203] = memoria[f2203] & 0x00000020;
            fprintf(output, "[HARDWARE INTERRUPTION %d]\n", prioridade);
            //printf("PC: 0x%08X\n", reg[32]);
           // printf("salto: 0x%08X\n", salto);
        }else{
        	pendencia[2] = 2;
		}
	}
//	fprintf(output, "contfpu: %d\n", contfpu);
	//fprintf(output, "memoria[control]: 0x%08X\n", memoria[f2203]);
	//fprintf(output, "contfpu: %d\n", contfpu);
	
	contfpu--;
	controle = controle & 0x00000020;
	memoria[f2203] = controle;
//	printf("0x%08X\n", memoria[f2203]);
	//getchar();
	return contfpu;	
}

void memoriaCacheInstrucao(unsigned int *reg, unsigned int *memoria, FILE* output){

    id = (reg[32]*4 & 0xFFFFFF80) >> 7;
    linha = ((reg[32]) & 0x00000070) >> 4;
	palavra = (reg[33] & 0x0000000C) >> 2;  
	
	bloco = salto % 4;
	
	
	if ( cacheI.set0[linha][0] == 1 || cacheI.set1[linha][0] == 1){ // se meu dado est· disponivel no set0 ou set1
		cacheI.hit++; // acertÙ, miseravi
		if ( ( cacheI.set0[linha][0] == 1 && cacheI.set0[linha][2] == id) || (cacheI.set1[linha][0] == 1 && cacheI.set1[linha][2] == id) ){ // se meu identificador for igual
			//incrementar a idade de todas as outras linhas.. 
			
			cacheI.set0[linha][2] == id ? incrementaIdadeInstrucao(linha, 2, id)	: incrementaIdadeInstrucao(linha, 3, id); // o id È igual em set0? se sim, incremento em set0 se n„o incremento em set1 
			
			fprintf(output, "[CACHE I LINE %d READ HIT @ 0x%08X]\n", linha, reg[32]);
			fprintf(output, "[SET 0: %s, AGE %d, DATA 0x%08X 0x%08X 0x%08X 0x%08X]\n", validade(cacheI.set0[linha][0]), cacheI.set0[linha][1], cacheI.set0[linha][3], cacheI.set0[linha][4], cacheI.set0[linha][5], cacheI.set0[linha][6]);
			fprintf(output, "[SET 1: %s, AGE %d, DATA 0x%08X 0x%08X 0x%08X 0x%08X]\n", validade(cacheI.set1[linha][0]), cacheI.set1[linha][1],cacheI.set1[linha][3], cacheI.set1[linha][4], cacheI.set1[linha][5], cacheI.set1[linha][6]);
		
		}else{ // se meu id for diferente
			
			( (cacheI.set0[linha][0] == 1) && (cacheI.set0[linha][2] == id) ) ? incrementaIdadeInstrucao(linha, 2, id) : incrementaIdadeInstrucao(linha, 3, id);
			
			cacheI.miss++; // falta.
			fprintf(output, "[CACHE I LINE %d READ MISS @ 0x%08X]\n", linha, reg[32]);
			fprintf(output, "[SET 0: %s, AGE %d, DATA 0x%08X 0x%08X 0x%08X 0x%08X]\n", validade(cacheI.set0[linha][0]), cacheI.set0[linha][1], cacheI.set0[linha][3], cacheI.set0[linha][4], cacheI.set0[linha][5], cacheI.set0[linha][6]);
			fprintf(output, "[SET 1: %s, AGE %d, DATA 0x%08X 0x%08X 0x%08X 0x%08X]\n", validade(cacheI.set1[linha][0]), cacheI.set1[linha][1],cacheI.set1[linha][3], cacheI.set1[linha][4], cacheI.set1[linha][5], cacheI.set1[linha][6]);		
			
			// apÛs computar o miss tenho que mover o bloco da memoria para a cache
			if ( cacheI.set0[linha][0] == 1 ){ // se minha linha no set0 estiver com algum dado
				cacheI.set1[linha][0] = 1; 
				cacheI.set1[linha][2] = id;
				moveBloco(linha, salto, bloco, memoria, 1);  // 1 - representa cacheI.set1
			}else{ // sen„o
				cacheI.set0[linha][0] = 1; 
				cacheI.set0[linha][2] = id;
				moveBloco(linha, salto, bloco, memoria, 0); // 0 - representa cacheI.set0
			}
		}
	}else{ //significa que meu dado n„o est· disponivel nem no set0 e nem no set1
		
		( (cacheI.set0[linha][0] == 1) && (cacheI.set0[linha][2] == id) ) ? incrementaIdadeInstrucao(linha, 2, id) : incrementaIdadeInstrucao(linha, 3, id);
		
		cacheI.miss++; // falta.
		fprintf(output, "[CACHE I LINE %d READ MISS @ 0x%08X]\n", linha, reg[32]);
		fprintf(output, "[SET 0: %s, AGE %d, DATA 0x%08X 0x%08X 0x%08X 0x%08X]\n", validade(cacheI.set0[linha][0]), cacheI.set0[linha][1], cacheI.set0[linha][3], cacheI.set0[linha][4], cacheI.set0[linha][5], cacheI.set0[linha][6]);
		fprintf(output, "[SET 1: %s, AGE %d, DATA 0x%08X 0x%08X 0x%08X 0x%08X]\n", validade(cacheI.set1[linha][0]), cacheI.set1[linha][1],cacheI.set1[linha][3], cacheI.set1[linha][4], cacheI.set1[linha][5], cacheI.set1[linha][6]);		
		
		if ( cacheI.set0[linha][0] == 1 ){
				cacheI.set1[linha][0] = 1; 
				cacheI.set1[linha][2] = id;
				moveBloco(linha, salto, bloco, memoria, 1);  // 1 - representa cacheI.set1
			}else{
				cacheI.set0[linha][0] = 1; 
				cacheI.set0[linha][2] = id;
				moveBloco(linha, salto, bloco, memoria, 0);  // 0 - representa cacheI.set0
			}
	}
}

void memoriaCacheDados(unsigned int *reg, unsigned int *memoria, FILE* output, int func, unsigned int endereco){
	
	//endereco = endereco << 2;
	
	id = ( (endereco << 2) & 0xFFFFFF80) >> 7;
    linha = ( ( (endereco << 2)  & 0x00000070) >> 4);
	//palavra = (reg[33] & 0x0000000C) >> 2;
	
	bloco = endereco % 4;	

	// EndereÁos reservados n„o ativam a cache
	if ( (endereco << 2 != 0x880C) && (endereco << 2 != 0x8808) && (endereco << 2 != 0x8804) && (endereco << 2 != 0x8800) && (endereco << 2 != 0x8080)){
		
		if ( cacheD.set0[linha][0] == 1 || cacheD.set1[linha][0] == 1){ // se meu dado est· disponivel
			if ( ( cacheD.set0[linha][0] == 1 && cacheD.set0[linha][2] == id) || (cacheD.set1[linha][0] == 1 && cacheD.set1[linha][2] == id) ){ // se meu identificador for igual
				cacheD.hit++; // acertÙ, miseravi
				switch(func){  //func - serve para indicar se eu vim de uma funÁ„o de leitura ou escrita. 
					case 1: // leitura
					
						cacheD.set0[linha][2] == id ? incrementaIdadeDados(linha, 2, id)	: incrementaIdadeDados(linha, 3, id); // o id È igual em set0? se sim, incremento em set0 se n„o incremento em set1 
					
						fprintf(output, "[CACHE D LINE %d READ HIT @ 0x%08X]\n", linha, (endereco << 2));
						fprintf(output, "[SET 0: %s, AGE %d, DATA 0x%08X 0x%08X 0x%08X 0x%08X]\n", validade(cacheD.set0[linha][0]), cacheD.set0[linha][1], cacheD.set0[linha][3], cacheD.set0[linha][4], cacheD.set0[linha][5], cacheD.set0[linha][6]);
						fprintf(output, "[SET 1: %s, AGE %d, DATA 0x%08X 0x%08X 0x%08X 0x%08X]\n", validade(cacheD.set1[linha][0]), cacheD.set1[linha][1],cacheD.set1[linha][3], cacheD.set1[linha][4], cacheD.set1[linha][5], cacheD.set1[linha][6]);
						
							
						
					break;
					case 2: // escrita
						
						
						( (cacheD.set0[linha][0] == 1) && (cacheD.set0[linha][2] == id) ) ? incrementaIdadeDados(linha, 2, id) : incrementaIdadeDados(linha, 3, id);
						
						fprintf(output, "[CACHE D LINE %d WRITE HIT @ 0x%08X]\n", linha, (endereco << 2));
						fprintf(output, "[SET 0: %s, AGE %d, DATA 0x%08X 0x%08X 0x%08X 0x%08X]\n", validade(cacheD.set0[linha][0]), cacheD.set0[linha][1], cacheD.set0[linha][3], cacheD.set0[linha][4], cacheD.set0[linha][5], cacheD.set0[linha][6]);
						fprintf(output, "[SET 1: %s, AGE %d, DATA 0x%08X 0x%08X 0x%08X 0x%08X]\n", validade(cacheD.set1[linha][0]), cacheD.set1[linha][1],cacheD.set1[linha][3], cacheD.set1[linha][4], cacheD.set1[linha][5], cacheD.set1[linha][6]);						
					
						
						// como acertei e cai na escrita de dados, ent„o atualizo a cache, tenho que subistituir a linha que possui a maior idade. 
						if( (cacheD.set0[linha][0] == 1) && (cacheD.set0[linha][2] == id) ){
							
							indiceIdade = maiorIdade(0);
							
							cacheD.set0[linha][0] = 1; 
							cacheD.set0[linha][2] = id;
							
							moveBloco(linha, endereco, bloco, memoria, 2); // 2 - representa cacheD.set0
						
						}else if ( (cacheD.set1[linha][0] == 1) && (cacheD.set1[linha][2] == id) ){
						
							indiceIdade = maiorIdade(1);
							
							cacheD.set1[linha][0] = 1; 
							cacheD.set1[linha][2] = id;
							
							moveBloco(linha, endereco, bloco, memoria, 3); // 3 - representa cacheD.set1							
						}
					break;
					default: //?? 
					break;
				}
			}else{// id diferente
				cacheD.miss++;// falta.
				switch(func){ // func - serve para indicar se eu vim de uma funÁ„o de leitura ou escrita.
					case 1:	// leitura								
					
					( (cacheD.set0[linha][0] == 1) && (cacheD.set0[linha][2] == id) ) ? incrementaIdadeDados(linha, 2, id) : incrementaIdadeDados(linha, 3, id);
					
						fprintf(output, "[CACHE D LINE %d READ MISS @ 0x%08X]\n", linha, (endereco << 2));
						fprintf(output, "[SET 0: %s, AGE %d, DATA 0x%08X 0x%08X 0x%08X 0x%08X]\n", validade(cacheD.set0[linha][0]), cacheD.set0[linha][1], cacheD.set0[linha][3], cacheD.set0[linha][4], cacheD.set0[linha][5], cacheD.set0[linha][6]);
						fprintf(output, "[SET 1: %s, AGE %d, DATA 0x%08X 0x%08X 0x%08X 0x%08X]\n", validade(cacheD.set1[linha][0]), cacheD.set1[linha][1],cacheD.set1[linha][3], cacheD.set1[linha][4], cacheD.set1[linha][5], cacheD.set1[linha][6]);
						
						//Qual id È falso? Set0 ou Set1?
						
							if( (cacheD.set0[linha][0] == 1) ){
								
								indiceIdade = maiorIdade(1); 
								
								cacheD.set1[linha][0] = 1; 
								cacheD.set1[linha][2] = id;
								
								moveBloco(linha, endereco, bloco, memoria, 3); // 3 - representa cacheD.set1
							}else{
								
								indiceIdade = maiorIdade(0); 
								
								cacheD.set0[linha][0] = 1; 
								cacheD.set0[linha][2] = id;
							
								moveBloco(linha, endereco, bloco, memoria, 2); // 2 - representa cacheD.set0	
							}
					break;
					case 2: // escrita
					
					
						cacheD.set0[linha][0] == 1 ? incrementaIdadeDados(linha, 2, id) : incrementaIdadeDados(linha, 3, id);
						fprintf(output, "[CACHE D LINE %d WRITE MISS @ 0x%08X]\n", linha, (endereco << 2));
						fprintf(output, "[SET 0: %s, AGE %d, DATA 0x%08X 0x%08X 0x%08X 0x%08X]\n", validade(cacheD.set0[linha][0]), cacheD.set0[linha][1], cacheD.set0[linha][3], cacheD.set0[linha][4], cacheD.set0[linha][5], cacheD.set0[linha][6]);
						fprintf(output, "[SET 1: %s, AGE %d, DATA 0x%08X 0x%08X 0x%08X 0x%08X]\n", validade(cacheD.set1[linha][0]), cacheD.set1[linha][1],cacheD.set1[linha][3], cacheD.set1[linha][4], cacheD.set1[linha][5], cacheD.set1[linha][6]);					
						
						
						
					break;
					default: // ??
					break;
				}
			}	
		}else{ //significa que meu dado n„o est· disponivel
			cacheD.miss++; // computo falta de cache
			switch(func){ // func - serve para indicar se eu vim de uma funÁ„o de leitura ou escrita.
				case 1:	// leitura
				
					( (cacheD.set0[linha][0] == 1) && (cacheD.set0[linha][2] == id) ) ? incrementaIdadeDados(linha, 2, id) : incrementaIdadeDados(linha, 3, id);
				
					fprintf(output, "[CACHE D LINE %d READ MISS @ 0x%08X]\n", linha, (endereco << 2));
					fprintf(output, "[SET 0: %s, AGE %d, DATA 0x%08X 0x%08X 0x%08X 0x%08X]\n", validade(cacheD.set0[linha][0]), cacheD.set0[linha][1], cacheD.set0[linha][3], cacheD.set0[linha][4], cacheD.set0[linha][5], cacheD.set0[linha][6]);
					fprintf(output, "[SET 1: %s, AGE %d, DATA 0x%08X 0x%08X 0x%08X 0x%08X]\n", validade(cacheD.set1[linha][0]), cacheD.set1[linha][1], cacheD.set1[linha][3], cacheD.set1[linha][4], cacheD.set1[linha][5], cacheD.set1[linha][6]);
				
					if( cacheD.set0[linha][0] == 1) {
						indiceIdade = maiorIdade(1);
						
						cacheD.set1[linha][0] = 1; 
						cacheD.set1[linha][2] = id;

						moveBloco(linha, endereco, bloco, memoria, 3); // 3 - representa cacheD.set1					
					}else{
						indiceIdade = maiorIdade(0);
						
						cacheD.set0[linha][0] = 1; 
						cacheD.set0[linha][2] = id;

						moveBloco(linha, endereco, bloco, memoria, 2); // 2 - representa cacheD.set0
					}
				break;
				case 2:	//escrita
				
					cacheD.set0[linha][0] == 0 ? incrementaIdadeDados(linha, 2, id) : incrementaIdadeDados(linha, 3, id);
				
					fprintf(output, "[CACHE D LINE %d WRITE MISS @ 0x%08X]\n", linha, (endereco << 2));
					fprintf(output, "[SET 0: %s, AGE %d, DATA 0x%08X 0x%08X 0x%08X 0x%08X]\n", validade(cacheD.set0[linha][0]), cacheD.set0[linha][1], cacheD.set0[linha][3], cacheD.set0[linha][4], cacheD.set0[linha][5], cacheD.set0[linha][6]);
					fprintf(output, "[SET 1: %s, AGE %d, DATA 0x%08X 0x%08X 0x%08X 0x%08X]\n", validade(cacheD.set1[linha][0]), cacheD.set1[linha][1], cacheD.set1[linha][3], cacheD.set1[linha][4], cacheD.set1[linha][5], cacheD.set1[linha][6]);
				
					
				
				break;
				default: // ??
				break;
			}
		}
		func = 0;	
	}
}


int maiorIdade (int id){
	
	int i = 0;
	int max = 0;
	int indice = 0;
	
	if (id == 0){
		
		max = cacheD.set0[0][1];
		
		for (i = 1; i <= 7; i++){
			if (cacheD.set0[i][1] > max){
				indice = i; 
				max = cacheD.set0[i][1];
			}
		}		 
	}else{
		
		max = cacheD.set1[0][1];
		
		for (i = 1; i <= 7; i++){
			if (cacheD.set1[i][1] > max){
				indice = i; 
				max = cacheD.set1[i][1];
			}
		}
	}

	return indice;
}

void moveBloco(unsigned int linha, unsigned int endereco, unsigned int bloco, unsigned int *memoria ,int identificador){
		
	switch (identificador){
		case 0: // cache instruÁ„o, set0
			cacheI.set0[linha][3] = memoria[endereco - bloco];
			if( (endereco - bloco) + 1 > qtdMemoria){
				cacheI.set0[linha][4] = memoria[0];
			}else if ((endereco - bloco) + 2 > qtdMemoria){
				cacheI.set0[linha][4] = memoria[0];
				cacheI.set0[linha][5] = memoria[1];
			}else if ((endereco - bloco) + 3 > qtdMemoria){
				cacheI.set0[linha][4] = memoria[0];
				cacheI.set0[linha][5] = memoria[1];
				cacheI.set0[linha][6] = memoria[2];
			}else{
				cacheI.set0[linha][4] = memoria[(endereco - bloco) + 1];
				cacheI.set0[linha][5] = memoria[(endereco - bloco) + 2];
				cacheI.set0[linha][6] = memoria[(endereco - bloco) + 3];
			}
		break;
		
		case 1: // cache instruÁ„o, set1 
			cacheI.set1[linha][3] = memoria[endereco - bloco];
			if( (endereco - bloco) + 1 > qtdMemoria){
				cacheI.set1[linha][4] = memoria[0];
			}else if ((endereco - bloco) + 2 > qtdMemoria){
				cacheI.set1[linha][4] = memoria[0];
				cacheI.set1[linha][5] = memoria[1];
			}else if ((endereco - bloco) + 3 > qtdMemoria){
				cacheI.set1[linha][4] = memoria[0];
				cacheI.set1[linha][5] = memoria[1];
				cacheI.set1[linha][6] = memoria[2];
			}else{
				cacheI.set1[linha][4] = memoria[(endereco - bloco) + 1];
				cacheI.set1[linha][5] = memoria[(endereco - bloco) + 2];
				cacheI.set1[linha][6] = memoria[(endereco - bloco) + 3];
			}
		break;
	
		case 2: // cache dados, set0
		
			cacheD.set0[linha][3] = memoria[endereco - bloco];
			cacheD.set0[linha][4] = memoria[(endereco - bloco) + 1];
			cacheD.set0[linha][5] = memoria[(endereco - bloco) + 2];
			cacheD.set0[linha][6] = memoria[(endereco - bloco) + 3];
			
			if( (endereco - bloco) + 1 > qtdMemoria){
				cacheD.set0[linha][4] = memoria[0];
			}else if ((endereco - bloco) + 2 > qtdMemoria){
				cacheD.set0[linha][4] = memoria[0];
				cacheD.set0[linha][5] = memoria[1];
			}else if ((endereco - bloco) + 3 > qtdMemoria){
				cacheD.set0[linha][4] = memoria[0];
				cacheD.set0[linha][5] = memoria[1];
				cacheD.set0[linha][6] = memoria[2];
			}else{
				cacheD.set0[linha][4] = memoria[(endereco - bloco) + 1];
				cacheD.set0[linha][5] = memoria[(endereco - bloco) + 2];
				cacheD.set0[linha][6] = memoria[(endereco - bloco) + 3];
			}
		break;
		
		case 3:  //cache dados, set1
	
			cacheD.set1[linha][3] = memoria[endereco - bloco];
			cacheD.set1[linha][4] = memoria[(endereco - bloco) + 1];
			cacheD.set1[linha][5] = memoria[(endereco - bloco) + 2];
			cacheD.set1[linha][6] = memoria[(endereco - bloco) + 3];
				
			if( (endereco - bloco) + 1 > qtdMemoria){
				cacheD.set1[linha][4] = memoria[0];
			}else if ((endereco - bloco) + 2 > qtdMemoria){
				cacheD.set1[linha][4] = memoria[0];
				cacheD.set1[linha][5] = memoria[1];
			}else if ((endereco - bloco) + 3 > qtdMemoria){
				cacheD.set1[linha][4] = memoria[0];
				cacheD.set1[linha][5] = memoria[1];
				cacheD.set1[linha][6] = memoria[2];
			}else{
				cacheD.set1[linha][4] = memoria[(endereco - bloco) + 1];
				cacheD.set1[linha][5] = memoria[(endereco - bloco) + 2];
				cacheD.set1[linha][6] = memoria[(endereco - bloco) + 3];
			}
		break;
		
		default:
		break;
	}
}

void incrementaIdadeDados(unsigned int linha, int idConjunto, unsigned int idLinha){

/* 
	Identificador - Varivavel que ira decidir se estou no set0 ou no set1. set0 - 2 , set1 - 3
	Linha - Varivavel que indica qual linha na cache estou trabalhando
*/
	int i = 0; // auxiliar..
	
	if(idConjunto == 2){ // set0
		if(cacheD.set0[linha][0] == 1 && cacheD.set0[linha][2] == idLinha) { //se a linha que estou for v·lida...	
			cacheD.set0[linha][1] = 0; //apago a idade da linha que usei
			for(i = 0; i <= 7; i++){
				if (linha != i)
					cacheD.set0[i][0] == 1 ? cacheD.set0[i][1]++ : cacheD.set0[i][1] == 0; //incremento todas as do set0 (que s„o v·lidas)
				cacheD.set1[i][0] == 1 ? cacheD.set1[i][1]++ : cacheD.set1[i][1] == 0; //incremento todas as do set1 (que s„o v·lidas)
			}// fim for
		}else{//fim if, a linha que estou È inv·lida.
			for(i = 0; i <= 7; i++){
				cacheD.set0[i][0] == 1 ? cacheD.set0[i][1]++ : cacheD.set0[i][1] == 0; //incremento todas as do set0 (que s„o v·lidas)
				cacheD.set1[i][0] == 1 ? cacheD.set1[i][1]++ : cacheD.set1[i][1] == 0; //incremento todas as do set1 (que s„o v·lidas)
			}// fim for
		}// fim else
	}// fim identificador
	
	else{// set 1
		if(cacheD.set1[linha][0] == 1 && cacheD.set1[linha][2] == idLinha){ // se a linha for v·lida...
			cacheD.set1[linha][1] = 0; // apago a idade da linha que usei
			for(i = 0; i <= 7; i++){
				if (linha !=i )
					cacheD.set1[i][0] == 1 ? cacheD.set1[i][1]++ : cacheD.set1[i][1] == 0;
				cacheD.set0[i][0] == 1 ? cacheD.set0[i][1]++ : cacheD.set0[i][1] == 0;
			}// fim for
		}else{ //linha È inv·lida. Ent„o tenho que incrementar todas as v·lidas menos ela. 
			for(i = 0; i <= 7; i++){
				cacheD.set1[i][0] == 1 ? cacheD.set1[i][1]++ : cacheD.set1[i][1] == 0;
				cacheD.set0[i][0] == 1 ? cacheD.set0[i][1]++ : cacheD.set0[i][1] == 0;
			}// fim for
		}// fim else
	} // fim identificador
}

void incrementaIdadeInstrucao(unsigned int linha, int idConjunto, unsigned int idLinha){

/* 
	Identificador - Varivavel que ira decidir se estou no set0 ou no set1. set0 - 2 , set1 - 3
	Linha - Varivavel que indica qual linha na cache estou trabalhando
*/
	int i = 0; // auxiliar..
	
	if(idConjunto == 2){ // set0
		if(cacheI.set0[linha][0] == 1 && cacheI.set0[linha][2] == idLinha) { //se a linha que estou for v·lida...	
			cacheI.set0[linha][1] = 0; //apago a idade da linha que usei
			for(i = 0; i <= 7; i++){
				if (linha != i)
					cacheI.set0[i][0] == 1 ? cacheI.set0[i][1]++ : cacheI.set0[i][1] == 0; //incremento todas as do set0 (que s„o v·lidas)
				cacheI.set1[i][0] == 1 ? cacheI.set1[i][1]++ : cacheI.set1[i][1] == 0; //incremento todas as do set1 (que s„o v·lidas)
			}// fim for
		}else{//fim if, a linha que estou È inv·lida.
			for(i = 0; i <= 7; i++){
				cacheI.set0[i][0] == 1 ? cacheI.set0[i][1]++ : cacheI.set0[i][1] == 0; //incremento todas as do set0 (que s„o v·lidas)
				cacheI.set1[i][0] == 1 ? cacheI.set1[i][1]++ : cacheI.set1[i][1] == 0; //incremento todas as do set1 (que s„o v·lidas)
			}// fim for
		}// fim else
	}// fim identificador
	
	else{// set 1
		if(cacheI.set1[linha][0] == 1 && cacheI.set1[linha][2] == idLinha){ // se a linha for v·lida...
			cacheI.set1[linha][1] = 0; // apago a idade da linha que usei
			for(i = 0; i <= 7; i++){
				if (linha !=i )
					cacheI.set1[i][0] == 1 ? cacheI.set1[i][1]++ : cacheI.set1[i][1] == 0;
				cacheI.set0[i][0] == 1 ? cacheI.set0[i][1]++ : cacheI.set0[i][1] == 0;
			}// fim for
		}else{ //linha È inv·lida. Ent„o tenho que incrementar todas as v·lidas menos ela. 
			for(i = 0; i <= 7; i++){
				cacheI.set1[i][0] == 1 ? cacheI.set1[i][1]++ : cacheI.set1[i][1] == 0;
				cacheI.set0[i][0] == 1 ? cacheI.set0[i][1]++ : cacheI.set0[i][1] == 0;
			}// fim for
		}// fim else
	} // fim identificador
}


char* validade(int validade){
	
	if (validade == 0)
		return "INVALID";
	else
		return "VALID";
	
}

void estatisticas(FILE* output){
	int totalD = cacheD.hit + cacheD.miss, totalI = cacheI.hit + cacheI.miss;
	int porHit = 0, porMiss = 0;

	porHit = (cacheD.hit * 100)/totalD;	
	porMiss = 100 - porHit;	
	fprintf(output, "\n[CACHE D STATISTICS] #Hit = %d (%d%%), #Miss = %d (%d%%)\n", cacheD.hit, porHit, cacheD.miss, porMiss);
	
	porHit = 0; porMiss = 0;
	
	porHit = ( cacheI.hit * 100)/totalI;
	porMiss = 100 - porHit;
	fprintf(output, "[CACHE I STATISTICS] #Hit = %d (%d%%), #Miss = %d (%d%%)", cacheI.hit, porHit, cacheI.miss, porMiss);
}

int calculaExpoente (float aux){
	int cont = 0, cont2 = 0;
	unsigned int num = (int)aux;	
	float aux2 = 0;
	//Calculando o expoente de x e y	
	while (aux/2 >= 1){
		cont++;
		aux = (aux/2); 
	}
	
	if (cont == 30){
		num = IEEE754(num);
		aux2 = aux; 
		
		while (aux2/2 >= 1){
			cont2++;
			aux2 = (aux2/2); 
		}	
		return cont2;
	}
	
	return cont;
}

unsigned int floatToIEEE754 (float num) {
	
	union PrecisaoUnicaIEEE754 {
		struct{
			unsigned int fracionaria : 23;
			unsigned int exp : 8;
			unsigned int sinal : 1;
		}raw;
		float f;
	}floatNumber;
	floatNumber.f = num;
	return (floatNumber.raw.sinal << 31) + (floatNumber.raw.exp << 23) + (floatNumber.raw.fracionaria);
}

//Operacoes

void add(unsigned int memoria, unsigned int *reg, FILE* output){

	unsigned int x = 0, y = 0, z = 0, ex = 0, ey = 0, ez = 0;
	uint64_t temp = 0;
	
	y = (memoria & 0x0000001F);
	x = (memoria & 0x000003E0) >> 5;
	z = (memoria & 0x00007C00) >> 10;

	ey = (memoria & 0x00008000) >> 10;
	ex = (memoria & 0x00010000) >> 11;
	ez = (memoria & 0x00020000) >> 12;

	reg[32] = reg[32] + 4; // incremento o PC, instru√ß√£o sequencial
	
	if ( (z+ez) != 0 ){
		temp = (uint64_t)reg[(x+ex)] + (uint64_t)reg[(y+ey)];
		reg[(z+ez)] = reg[(x+ex)] + reg[(y+ey)];
	}else{
		reg[0] = 0; 
	}
		//printf("salto: 0x%08X\n", salto);
		//printf("PC: 0x%08X\n", reg[32]);

	reg[35] = (reg[35] & 0xFFFFFFEF);
	if(temp > 0xFFFFFFFF) {		//          31-5    4  3  2  1  0
		//reg[35] = (reg[35] & 0xFFFFFFEF); // MUDEI AQUI, acrescentei essa linha..
		reg[35] = (reg[35] | 0x00000010);   // FR = |Reservado|OV|ZD|GT|LT|EQ|, Overflow = 1
	}
	fprintf(output, "add r%d, r%d, r%d\n", (z+ez), (x+ex), (y+ey) );
	fprintf(output ,"[U] FR = 0x%08X, R%d = R%d + R%d = 0x%08X\n", reg[35], (z+ez), (x+ex), (y+ey), reg[(z+ez)]);
}

void addi(unsigned int memoria, unsigned int *reg, FILE* output){
	unsigned int x = 0, y = 0, imediato = 0;
	uint64_t temp = 0;

	x = (memoria & 0x000003E0) >> 5;
	y = (memoria & 0x0000001F);
	imediato = (memoria & 0x03FFFC00) >> 10;
	
	reg[32] = reg[32] + 4; // incremento o PC, instru√ß√£o sequencial
	
	if( x != 0){

		temp = (uint64_t)reg[y] + (uint64_t)imediato;
		reg[x] = reg[y] + imediato;
	}else{
		reg[x] = 0; 
	}

	reg[35] = (reg[35] & 0xFFFFFFEF);
	if(temp > 0xFFFFFFFF) {		//          31-5    4  3  2  1  0
		//reg[35] = (reg[35] & 0xFFFFFFEF); // MUDEI AQUI, acrescentei essa linha..
		reg[35] = (reg[35] | 0x00000010);   // FR = |Reservado|OV|ZD|GT|LT|EQ|, Overflow = 1
	}

	fprintf(output, "addi r%d, r%d, %d\n", x, y, imediato);
	fprintf(output, "[F] FR = 0x%08X, R%d = R%d + 0x%04X = 0x%08X\n", reg[35], x, y, imediato, reg[x]);

	//printf("addi r%d, r%d, %d\n", x, y, imediato);
	//printf("[F] FR = 0x%08X, R%d = R%d + 0x%04X = 0x%08X\n", reg[35], x, y, imediato, reg[x]);
//	getchar();

}

void sub(unsigned int memoria, unsigned int *reg, FILE* output){

	unsigned int x = 0, y = 0, z = 0, ex = 0, ey = 0, ez = 0;
	uint64_t temp = 0;
	
	y = (memoria & 0x0000001F);
	x = (memoria & 0x000003E0) >> 5;
	z = (memoria & 0x00007C00) >> 10;

	ey = (memoria & 0x00008000) >> 10;
	ex = (memoria & 0x00010000) >> 11;
	ez = (memoria & 0x00020000) >> 12;

	reg[32] = reg[32] + 4; // incremento o PC, instru√ß√£o sequencial
	
	if((z+ez) != 0){
		temp = (uint64_t)reg[x+ex] - (uint64_t)reg[y+ey];
		reg[z+ez] = reg[x+ex] - reg[y+ey];
	}else{
		reg[z+ez] = 0;
	}
	
	reg[35] = (reg[35] & 0xFFFFFFEF);
	if(temp > 0xFFFFFFFF) {		//          31-5    4  3  2  1  0
		//reg[35] = (reg[35] & 0xFFFFFFEF); // MUDEI AQUI, acrescentei essa linha..
		reg[35] = (reg[35] | 0x00000010);   // FR = |Reservado|OV|ZD|GT|LT|EQ|, Overflow = 1
	}
	fprintf(output, "sub r%d, r%d, r%d\n", (z+ez), (x+ex), (y+ey) );
	fprintf(output, "[U] FR = 0x%08X, R%d = R%d - R%d = 0x%08X\n", reg[35], (z+ez), (x+ex), (y+ey), reg[z+ez]);
}

void subi(unsigned int memoria, unsigned int *reg, FILE* output){

	unsigned int x = 0, y = 0, imediato = 0;
	uint64_t temp = 0;
	
	x = (memoria & 0x000003E0) >> 5;
	y = (memoria & 0x0000001F);
	imediato = (memoria & 0x03FFFC00) >> 10;

	reg[32] = reg[32] + 4; // incremento o PC, instru√ß√£o sequencial

	if(x != 0){
		temp = (uint64_t)reg[y] - (uint64_t)imediato;
		reg[x] = reg[y] - imediato;
	}else{
		reg[x] = 0; 
	}
	reg[35] = (reg[35] & 0xFFFFFFEF);	
	//fprintf(output, "0x%X - 0x%04X\n", reg[y], imediato);
	if(temp > 0xFFFFFFFF) {		//          31-5    4  3  2  1  0
		//reg[35] = (reg[35] & 0xFFFFFFEF); // MUDEI AQUI, acrescentei essa linha..
		reg[35] = (reg[35] | 0x00000010);   // FR = |Reservado|OV|ZD|GT|LT|EQ|, Overflow = 1
	}
	fprintf(output, "subi r%d, r%d, %d\n", x, y, imediato);
	fprintf(output, "[F] FR = 0x%08X, R%d = R%d - 0x%04X = 0x%08X\n", reg[35], x, y, imediato, reg[x]);
}

void mul(unsigned int memoria, unsigned int *reg, FILE* output){

	unsigned int x = 0, y = 0, z = 0, ex = 0, ey = 0, ez = 0;
	uint64_t temp = 0;
	
	y = (memoria & 0x0000001F);
	x = (memoria & 0x000003E0) >> 5;
	z = (memoria & 0x00007C00) >> 10;

	ey = (memoria & 0x00008000) >> 10;
	ex = (memoria & 0x00010000) >> 11;
	ez = (memoria & 0x00020000) >> 12;

	reg[32] = reg[32] + 4; // incremento o PC, instru√ß√£o sequencial
	
	if((z+ez) != 0){
		temp = (uint64_t)reg[x+ex] * (uint64_t)reg[y+ey];
		reg[z+ez] = reg[x+ex] * reg[y+ey];
	}else{
		reg[z+ez] = 0; 
	}
	
	reg[35] = (reg[35] & 0xFFFFFFEF); // seto 0 o OV
	if(temp > 0xFFFFFFFF) {					//          31-5    4  3  2  1  0
		//reg[35] = (reg[35] & 0xFFFFFFEF);
		reg[35] = (reg[35] | 0x00000010);   // FR = |Reservado|OV|ZD|GT|LT|EQ|, Overflow = 1
		reg[34] = (temp & 0xFFFFFFFF00000000) >> 32; //armazeno a extens√£o no ER
	}
	fprintf(output, "mul r%d, r%d, r%d\n", z+ez, x+ex, y+ey);
	fprintf(output, "[U] FR = 0x%08X, ER = 0x%08X, R%d = R%d * R%d = 0x%08X\n", reg[35], reg[34], (z+ez), (x+ex), (y+ey), reg[z+ez]);
}

void muli(unsigned int memoria, unsigned int *reg, FILE* output){

	unsigned int x = 0, y = 0, imediato = 0;
	uint64_t temp = 0;

	x = (memoria & 0x000003E0) >> 5;
	y = (memoria & 0x0000001F);
	imediato = (memoria & 0x03FFFC00) >> 10;

	reg[32] = reg[32] + 4; // incremento o PC, instru√ß√£o sequencial

	if(x != 0){
		temp = (uint64_t)reg[y] * (uint64_t)imediato;
		reg[x] = reg[y] * imediato;
 	}else{
 	    reg[x] = 0; 
	 }
	reg[35] = (reg[35] & 0xFFFFFFEF); // seto 0 o OV
	if(temp > 0xFFFFFFFF) {
	//	reg[35] = (reg[35] & 0xFFFFFFEF);   //          31-5    4  3  2  1  0
		reg[35] = (reg[35] | 0x00000010);   // FR = |Reservado|OV|ZD|GT|LT|EQ|, Overflow = 1
		reg[34] = (temp & 0xFFFFFFFF00000000) >> 32;
	}
	fprintf(output, "muli r%d, r%d, %d\n", x, y, imediato);
	fprintf(output, "[F] FR = 0x%08X, ER = 0x%08X, R%d = R%d * 0x%04X = 0x%08X\n", reg[35], reg[34], x, y, imediato, reg[x]);

}

void divis(unsigned int memoria, unsigned int *reg, FILE* output){

	unsigned int x = 0, y = 0, z = 0, ex = 0, ey = 0, ez = 0;
	uint64_t temp = 0;
	
	y = (memoria & 0x0000001F);
	x = (memoria & 0x000003E0) >> 5;
	z = (memoria & 0x00007C00) >> 10;

	ey = (memoria & 0x00008000) >> 10;
	ex = (memoria & 0x00010000) >> 11;
	ez = (memoria & 0x00020000) >> 12;

	reg[32] = reg[32] + 4; // incremento o PC, instru√ß√£o sequencial
	reg[35] = (reg[35] & 0xFFFFFFEF);

	if(reg[y+ey] == 0){ // fazer a mascara, fazer um OR, se houver divisao por zero, se nao houver, continuo a instrucao de divisao
		reg[35] = (reg[35] & 0xFFFFFFF7);
		reg[35] = (reg[35] | 0x00000008);   // FR = |Reservado|OV|ZD|GT|LT|EQ|, Zero Division = 1
		//printf("ZD\n");
		if( (reg[35] & 0x00000040) == 0x00000040) {
			reg[36] = 0x00000001; // CR
			reg[37] = reg[32]; // IPC
			reg[32] = 0x0000000C; // PC
			salto = reg[32] >> 2;
			//reg[35] = (reg[35] & 0xFFFFFFBF);
            fprintf(output, "div r%d, r%d, r%d\n", (z+ez), (x+ex), (y+ey));
            fprintf(output, "[U] FR = 0x%08X, ER = 0x%08X, R%d = R%d / R%d = 0x%08X\n", reg[35], reg[34], (z+ez), (x+ex), (y+ey), reg[z+ez]); // MUDEI AQUI, tava reg[z], coloquei reg[z+ez]
		    fprintf(output, "[SOFTWARE INTERRUPTION]\n" );
        }else{
        	fprintf(output, "div r%d, r%d, r%d\n", (z+ez), (x+ex), (y+ey));
			fprintf(output, "[U] FR = 0x%08X, ER = 0x%08X, R%d = R%d / R%d = 0x%08X\n", reg[35], reg[34], (z+ez), (x+ex), (y+ey), reg[z+ez]); // MUDEI AQUI, tava reg[z], coloquei reg[z+ez]	
		}
	}else{
		if( (z+ez) != 0 ){
		
			temp = (uint64_t)reg[x+ex] / (uint64_t)reg[y+ey];
			reg[34] = reg[x+ex] % reg[y+ey]; // ER = reg[x] mod reg[y]
			reg[z+ez] = reg[x+ex] / reg[y+ey];
		}else{
			reg[z+ez] = 0; 
		}	 


		if(temp > 0xFFFFFFFF) {		//          31-5    4  3  2  1  0  ---- fazer a m√°scara e o OR
			reg[35] = (reg[35] & 0xFFFFFFEF);
			reg[35] = reg[35] | 0x00000010;   // FR = |Reservado|OV|ZD|GT|LT|EQ|, Overflow = 1
		}
        fprintf(output, "div r%d, r%d, r%d\n", (z+ez), (x+ex), (y+ey));
        fprintf(output, "[U] FR = 0x%08X, ER = 0x%08X, R%d = R%d / R%d = 0x%08X\n", reg[35], reg[34], (z+ez), (x+ex), (y+ey), reg[z+ez]); // MUDEI AQUI, tava reg[z], coloquei reg[z+ez]
    }
	//printf("div\n");
}

void divi(unsigned int memoria, unsigned int *reg, FILE* output){

	unsigned x = 0, y = 0, imediato = 0;
	uint64_t temp = 0;

	x = (memoria & 0x000003E0) >> 5;
	y = (memoria & 0x0000001F);
	imediato = (memoria & 0x03FFFC00) >> 10;

	reg[32] = reg[32] + 4; // incremento o PC, instru√ß√£o sequencial
	//reg[35] = (reg[35] & 0xFFFFFFEF);

	if(imediato == 0){
		reg[35] = (reg[35] & 0xFFFFFFF7);
        reg[35] = (reg[35] | 0x00000008);   // FR = |Reservado|OV|ZD|GT|LT|EQ|, Zero Division = 1
        //printf("ZD\n");
        if( (reg[35] & 0x00000040) == 0x00000040){
            reg[36] = 0x00000001; // CR
            reg[37] = reg[32]; // IPC
            reg[32] = 0x0000000C; // PC
            salto = reg[32] >> 2;
            //reg[35] = (reg[35] & 0xFFFFFFBF);
            fprintf(output, "divi r%d, r%d, %d\n", x, y, imediato);
            fprintf(output, "[F] FR = 0x%08X, ER = 0x%08X, R%d = R%d / 0x%04X = 0x%08X\n", reg[35], reg[34], x, y, imediato, reg[x]); // MUDEI AQUI, tava reg[z], coloquei reg[z+ez]
            fprintf(output, "[SOFTWARE INTERRUPTION]\n" );
        }else{
       		fprintf(output, "divi r%d, r%d, %d\n", x, y, imediato);
        	fprintf(output, "[F] FR = 0x%08X, ER = 0x%08X, R%d = R%d / 0x%04X = 0x%08X\n", reg[35], reg[34], x, y, imediato, reg[x]); // MUDEI AQUI, tava reg[z], coloquei reg[z+ez]
		}				
	}else{
		
		if (x != 0){	
			reg[34] = reg[y] % imediato; // ER = reg[x] mod imediato
			temp = (uint64_t)reg[x] / (uint64_t)imediato;
			reg[x] = reg[y] / imediato;
		}else{
			reg[x] = 0; 
		}
		
		
		if(temp > 0xFFFFFFFF) {		//          31-5    4  3  2  1  0
			reg[35] = (reg[35] & 0xFFFFFFEF);
			reg[35] = (reg[35] | 0x00000010);   // FR = |Reservado|OV|ZD|GT|LT|EQ|, Overflow = 1
		}
        fprintf(output, "divi r%d, r%d, %d\n", x, y, imediato);
        fprintf(output, "[F] FR = 0x%08X, ER = 0x%08X, R%d = R%d / 0x%04X = 0x%08X\n", reg[35], reg[34], x, y, imediato, reg[x]);
	}
}

// Comparacao e Deslocamento

void comp (unsigned int memoria, unsigned int *reg, FILE* output){

	unsigned int x = 0, y = 0, ex = 0, ey = 0;

	x = (memoria & 0x000003E0) >> 5;
	ex = (memoria & 0x00010000) >> 11;
	y = (memoria & 0x0000001F);
	ey = (memoria & 0x00008000) >> 10;

	reg[32] = reg[32] + 4; // incremento o PC, instru√ß√£o sequencial
	reg[35] = (reg[35] & 0xFFFFFFF8); // zero meus campos EQ LT GT

	//reg[35] = (reg[35] & 0xFFFFFFEF);

	if(reg[x+ex] == reg[y+ey]){
		//reg[35] = (reg[35] & 0xFFFFFFFE);
		reg[35] = (reg[35] | 0x00000001);   // FR = |Reservado|OV|ZD|GT|LT|EQ|, Equal = 1
		//printf("E igual\n");
	}else if (reg[x+ex] > reg[y+ey]){
		//reg[35] = (reg[35] & 0xFFFFFFFB);
		reg[35] = (reg[35] | 0x00000004);   // FR = |Reservado|OV|ZD|GT|LT|EQ|, Gran = 1
		//printf("E maior\n");
	}else if (reg[x+ex] < reg[y+ey]){
		//reg[35] = (reg[35] & 0xFFFFFFFD);
		reg[35] = (reg[35] | 0x00000002);   // FR = |Reservado|OV|ZD|GT|LT|EQ|, Less = 1
		//printf("E menor\n");
	}


	fprintf(output, "cmp r%d, r%d\n", (x+ex), (y+ey) );
	fprintf(output, "[U] FR = 0x%08X\n", reg[35]);
}

void compi(unsigned int memoria, unsigned int *reg, FILE* output){

	unsigned x = 0, imediato = 0;

	x = (memoria & 0x000003E0) >> 5;
	imediato = (memoria & 0x03FFFC00) >> 10;

	reg[32] = reg[32] + 4; // incremento o PC, instru√ß√£o sequencial
	reg[35] = (reg[35] & 0xFFFFFFF8); // zero meus campos EQ LT GT
	
	if(reg[x] == imediato){
		reg[35] = (reg[35] | 0x00000001);   // FR = |Reservado|OV|ZD|GT|LT|EQ|, Equal = 1
	}else if (reg[x] > imediato){
		reg[35] = (reg[35] | 0x00000004);   // FR = |Reservado|OV|ZD|GT|LT|EQ|, Gran = 1
	}else if (reg[x] < imediato){
		reg[35] = (reg[35] | 0x00000002);   // FR = |Reservado|OV|ZD|GT|LT|EQ|, Less = 1
	}

	fprintf(output, "cmpi r%d, %d\n", x, imediato);
	fprintf(output, "[F] FR = 0x%08X\n", reg[35]);
//	printf("cmpi r%d, %d\n", x, imediato);
//	printf("[F] FR = 0x%08X\n", reg[35]);

	//getchar();
}

void shl(unsigned int memoria, unsigned int *reg, FILE* output){

	unsigned int x = 0, y = 0, z = 0, ex = 0, ey = 0, ez = 0;
	uint64_t temp = 0;
	
	y = (memoria & 0x0000001F);
	x = (memoria & 0x000003E0) >> 5;
	z = (memoria & 0x00007C00) >> 10;

	ey = (memoria & 0x00008000) >> 10;
	ex = (memoria & 0x00010000) >> 11;
	ez = (memoria & 0x00020000) >> 12;

	//printf("regz: 0x%016X\n", reg[z+ez]);
	temp = ((uint64_t)reg[34] << 32) + (uint64_t)reg[x+ex];
	temp = temp << ((y+ey)+1);
	//printf("TEMP: 0x%08X\n", temp);
	if ( (z+ez) != 0 )
		reg[z+ez] = temp & 0xFFFFFFFF;
	reg[34] = (temp & 0xFFFFFFFF00000000) >> 32 ;

	fprintf(output, "shl r%d, r%d, %d\n", (z+ez), (x+ex), (y+ey) );
	fprintf(output, "[U] ER = 0x%08X, R%d = R%d << %d = 0x%08X\n", reg[34],(z+ez), (x+ex), ((y+ey)+1), reg[ez+z] );

	reg[32] = reg[32] + 4; // incremento o PC, instru√ß√£o sequencial
//	printf("shl r%d, r%d, %d\n", (z+ez), (x+ex), (y+ey) );
//	printf("[U] ER = 0x%08X, R%d = R%d << %d = 0x%08X\n", reg[34],(z+ez), (x+ex), ((y+ey)+1), reg[ez+z] );

	//getchar();
}

void shr(unsigned int memoria, unsigned int *reg, FILE* output){

	unsigned int x = 0, y = 0, z = 0, ex = 0, ey = 0, ez = 0;
	uint64_t temp = 0;
	
	y = (memoria & 0x0000001F);
	x = (memoria & 0x000003E0) >> 5;
	z = (memoria & 0x00007C00) >> 10;

	ey = (memoria & 0x00008000) >> 10;
	ex = (memoria & 0x00010000) >> 11;
	ez = (memoria & 0x00020000) >> 12;

	//printf("regz: 0x%016X\n", reg[z+ez]);
	temp = ((uint64_t)reg[34] << 32) + (uint64_t)reg[x+ex];
	temp = temp >> ((y+ey)+1);
	//printf("TEMP: 0x%08X\n", temp);
	if ( (z+ez) != 0 )
		reg[z+ez] = temp & 0xFFFFFFFF;
	reg[34] = (temp & 0xFFFFFFFF00000000) >> 32 ;


	fprintf(output, "shr r%d, r%d, %d\n", (z+ez), (x+ex), (y+ey) );
	fprintf(output, "[U] ER = 0x%08X, R%d = R%d >> %d = 0x%08X\n", reg[34],(z+ez), (x+ex), ((y+ey)+1), reg[ez+z] );

	reg[32] = reg[32] + 4; // incremento o PC, instru√ß√£o sequencial
}

//Operacoes Booleanas

void e (unsigned int memoria, unsigned int *reg, FILE* output){  

	unsigned int x, y, z, ex, ey, ez;
	y = (memoria & 0x0000001F);
	x = (memoria & 0x000003E0) >> 5;
	z = (memoria & 0x00007C00) >> 10;

	ey = (memoria & 0x00008000) >> 10;
	ex = (memoria & 0x00010000) >> 11;
	ez = (memoria & 0x00020000) >> 12;

	reg[32] = reg[32] + 4; // incremento o PC, instru√ß√£o sequencial

	if(z+ez != 0)
		reg[z+ez] = reg[x+ex] & reg[y+ey];

	fprintf(output, "and r%d, r%d, r%d\n", (z+ez), (x+ex), (y+ey) );
	fprintf(output, "[U] R%d = R%d & R%d = 0x%08X\n", (z+ez), (x+ex), (y+ey), reg[z+ez] );

}

void ei (unsigned int memoria, unsigned int *reg, FILE* output){

	unsigned int x, y, imediato;

	x = (memoria & 0x000003E0) >> 5;
	y = (memoria & 0x0000001F);
	imediato = (memoria & 0x03FFFC00) >> 10;

	reg[32] = reg[32] + 4; // incremento o PC, instru√ß√£o sequencial

	if (x != 0)
		reg[x] = reg[y] & imediato;

	fprintf(output, "andi r%d, r%d, %d\n", x, y, imediato );
	fprintf(output, "[F] R%d = R%d & 0x%04X = 0x%08X\n", x, y, imediato, reg[x] );

}

void nao (unsigned int memoria, unsigned int *reg, FILE* output){

	unsigned int x, y, ex, ey;
	y = (memoria & 0x0000001F);
	x = (memoria & 0x000003E0) >> 5;

	ey = (memoria & 0x00008000) >> 10;
	ex = (memoria & 0x00010000) >> 11;


	reg[32] = reg[32] + 4; // incremento o PC, instru√ß√£o sequencial

	if ((x+ex) != 0)
		reg[x+ex] = ~reg[y+ey];

	fprintf(output, "not r%d, r%d\n", (x+ex), (y+ey) );
	fprintf(output, "[U] R%d = ~R%d = 0x%08X\n", (x+ex), (y+ey), reg[x+ex] );

}

void naoi (unsigned int memoria, unsigned int *reg, FILE* output){

	unsigned int x, imediato;

	x = (memoria & 0x000003E0) >> 5;
	imediato = (memoria & 0x03FFFC00) >> 10;

	reg[32] = reg[32] + 4; // incremento o PC, instru√ß√£o sequencial

	if (x != 0)
		reg[x] = ~imediato;

	fprintf(output, "noti r%d, %d\n", x, imediato );
	fprintf(output, "[F] R%d = ~0x%04X = 0x%08X\n", x, imediato, reg[x] );

}

void ou (unsigned int memoria, unsigned int *reg, FILE* output){

	unsigned int x, y, z, ex, ey, ez;
	y = (memoria & 0x0000001F);
	x = (memoria & 0x000003E0) >> 5;
	z = (memoria & 0x00007C00) >> 10;

	ey = (memoria & 0x00008000) >> 10;
	ex = (memoria & 0x00010000) >> 11;
	ez = (memoria & 0x00020000) >> 12;

	reg[32] = reg[32] + 4; // incremento o PC, instru√ß√£o sequencial

	if ((z+ez) != 0 )
		reg[z+ez] = reg[x+ex] | reg[y+ey];

	fprintf(output, "or r%d, r%d, r%d\n", (z+ez), (x+ex), (y+ey) );
	fprintf(output, "[U] R%d = R%d | R%d = 0x%08X\n", (z+ez), (x+ex), (y+ey), reg[z+ez] );

//	printf("or r%d, r%d, r%d\n", (z+ez), (x+ex), (y+ey) );
//	printf("[U] R%d = R%d | R%d = 0x%08X\n", (z+ez), (x+ex), (y+ey), reg[z+ez] );

//	getchar();
}

void oui (unsigned int memoria, unsigned int *reg, FILE* output){

	unsigned int x, y, imediato;

	x = (memoria & 0x000003E0) >> 5;
	y = (memoria & 0x0000001F);
	imediato = (memoria & 0x03FFFC00) >> 10;

	reg[32] = reg[32] + 4; // incremento o PC, instru√ß√£o sequencial

	if (x != 0)
		reg[x] = reg[y] | imediato;

	fprintf(output, "ori r%d, r%d, %d\n", x, y, imediato );
	fprintf(output, "[F] R%d = R%d | 0x%04X = 0x%08X\n", x, y, imediato, reg[x] );

}

void ouExclusivo (unsigned int memoria, unsigned int *reg, FILE* output){

	unsigned int x, y, z, ex, ey, ez;
	y = (memoria & 0x0000001F);
	x = (memoria & 0x000003E0) >> 5;
	z = (memoria & 0x00007C00) >> 10;

	ey = (memoria & 0x00008000) >> 10;
	ex = (memoria & 0x00010000) >> 11;
	ez = (memoria & 0x00020000) >> 12;

	reg[32] = reg[32] + 4; // incremento o PC, instru√ß√£o sequencial

	if ((z+ez) != 0)
		reg[z+ez] = reg[x+ex] ^ reg[y+ey];

	fprintf(output, "xor r%d, r%d, r%d\n", (z+ez), (x+ex), (y+ey) );
	fprintf(output, "[U] R%d = R%d ^ R%d = 0x%08X\n", (z+ez), (x+ex), (y+ey), reg[z+ez] );

}

void ouExclusivoi (unsigned int memoria, unsigned int *reg, FILE* output){

	unsigned int x, y, imediato;

	x = (memoria & 0x000003E0) >> 5;
	y = (memoria & 0x0000001F);
	imediato = (memoria & 0x03FFFC00) >> 10;

	reg[32] = reg[32] + 4; // incremento o PC, instru√ß√£o sequencial

	if (x != 0)
		reg[x] = reg[y] ^ imediato;

	fprintf(output, "xori r%d, r%d, %d\n", x, y, imediato );
	fprintf(output, "[F] R%d = R%d ^ 0x%04X = 0x%08X\n", x, y, imediato, reg[x] );

}

// Leitura e Escrita

void ldw (unsigned int hexaMemoria, unsigned int *reg, unsigned int *memoria, FILE* output){

	unsigned int x, y, imediato;

	x = (hexaMemoria & 0x000003E0) >> 5;  // valor do arquivo AND mascara
	y = (hexaMemoria & 0x0000001F);
	imediato = (hexaMemoria & 0x03FFFC00) >> 10;

	reg[32] = reg[32] + 4; // incremento o PC, instru√ß√£o sequencial

	if (x != 0)
		reg[x] = memoria[(reg[y] + imediato)]; //reg[x] =  o que tem nessa posi√ß√£o de memoria ......... memoria[(reg[y] + imediato) << 2] d√° errado!

	memoriaCacheDados(reg, memoria, output, 1, (reg[y] + imediato));

	fprintf(output, "ldw r%d, r%d, 0x%04X\n", x, y, imediato);
	fprintf(output, "[F] R%d = MEM[(R%d + 0x%04X) << 2] = 0x%08X\n", x, y, imediato, reg[x]);

	//printf("ldw r%d, r%d, 0x%04X\n", x, y, imediato);
	//printf("[F] R%d = MEM[(R%d + 0x%04X) << 2] = 0x%08X\n", x, y, imediato, reg[x]);
	//getchar();
}

void ldb (unsigned int hexaMemoria, unsigned int *reg, unsigned int *memoria, FILE* output){

	unsigned int x = 0, y = 0, imediato = 0;
	int palavra = 0, aux = 0, aux2 = 0, aux3 = 0;

	x = (hexaMemoria & 0x000003E0) >> 5;  // valor do arquivo AND mascara
	y = (hexaMemoria & 0x0000001F);
	imediato = (hexaMemoria & 0x03FFFC00) >> 10;

	reg[32] = reg[32] + 4; // incremento o PC, instru√ß√£o sequencial

	aux2 = (reg[y] + imediato) >> 2;
	aux = reg[y] + imediato; 

	aux3 = aux - (aux2*4);

	if (x != 0) {
		//mod = (reg[y] + imediato) % 4;
		palavra = memoria[(reg[y] + imediato) >> 2]; //reg[x] =  o que tem nessa posi√ß√£o de memoria   
        //fprintf(output, "mod: %d\n", mod);
        //fprintf(output, "ldb - memoria[0x%08X] = 0x%08X\n", ((reg[y] + imediato) >> 2), palavra);
    	switch (aux3){
         	case 0: reg[x] = (palavra & 0xFF000000) >> 24; break;
         	case 1: reg[x] = (palavra & 0x00FF0000) >> 16; break;
         	case 2: reg[x] = (palavra & 0x0000FF00) >> 8; break;
         	case 3: reg[x] = (palavra & 0x000000FF); break;
         	default: break;
    	}
    }else{
    	reg[x] = 0; 
	}
	
	memoriaCacheDados(reg, memoria, output, 1, aux);
	
	fprintf(output, "ldb r%d, r%d, 0x%04X\n", x, y, imediato);
	fprintf(output, "[F] R%d = MEM[R%d + 0x%04X] = 0x%02X\n", x, y, imediato, reg[x]);

	//printf("ldb r%d, r%d, 0x%04X\n", x, y, imediato);
	//printf("[F] R%d = MEM[R%d + 0x%04X] = 0x%02X\n", x, y, imediato, reg[x]);
	//getchar();
}

void stw (unsigned int hexaMemoria, unsigned int *reg, unsigned int *memoria, FILE* output){

	unsigned int x, y, imediato;

	x = (hexaMemoria & 0x000003E0) >> 5;  // valor do arquivo AND mascara
	y = (hexaMemoria & 0x0000001F);
	imediato = (hexaMemoria & 0x03FFFC00) >> 10;

	if ((reg[x]+imediato) == 0x2222){
		terminal[contTerminal] = (reg[y] & 0x000000FF);
		contTerminal++;	
	}else{
		reg[32] = reg[32] + 4; // incremento o PC, instru√ß√£o sequencial
		memoria[(reg[x] + imediato)] = reg[y];
		memoriaCacheDados(reg, memoria, output, 2, (reg[x] + imediato));
	}	
	
	//printf("[F] MEM[(0x%08X)] = R%d = 0x%08X\n", (reg[x] + imediato), y, reg[y]);
	fprintf(output, "stw r%d, 0x%04X, r%d\n", x, imediato, y);
	fprintf(output, "[F] MEM[(R%d + 0x%04X) << 2] = R%d = 0x%08X\n", x, imediato, y, reg[y]);

	//printf("stw r%d, 0x%04X, r%d\n", x, imediato, y);
	//printf("[F] MEM[(R%d + 0x%04X) << 2] = R%d = 0x%08X\n", x, imediato, y, reg[y]);

	//getchar();
}

void stb (unsigned int hexaMemoria, unsigned int *reg, unsigned int *memoria, FILE* output){

	unsigned int x = 0, y = 0, imediato = 0, byte = 0;
	int posicao = 0, aux = 0, aux2 = 0;

	x = (hexaMemoria & 0x000003E0) >> 5;  // valor do arquivo AND mascara
	y = (hexaMemoria & 0x0000001F);
	imediato = (hexaMemoria & 0x03FFFC00) >> 10;

	reg[32] = reg[32] + 4; // incremento o PC, instru√ß√£o sequencial

	byte = (reg[y] & 0x000000FF);
	//mod = (reg[y] + imediato) % 4; 
	posicao = (reg[x] + imediato) >> 2; 
	
	aux2 = reg[x] + imediato; 
	aux = aux2 - (posicao*4);
	
	if ( posicao == 0x2222){
		memoria[posicao] = byte;
		terminal[contTerminal] = byte;
		contTerminal++;	
	}else{
		switch (aux){
			case 0:
				memoria[posicao] = memoria[posicao] & 0x00FFFFFF; 
				memoria[posicao] = memoria[posicao] | (byte << 24); break;
			case 1: 
				memoria[posicao] = memoria[posicao] & 0xFF00FFFF;
				memoria[posicao] = memoria[posicao] | (byte << 16); break;
			case 2: 
				memoria[posicao] = memoria[posicao] & 0xFFFF00FF;
				memoria[posicao] = memoria[posicao] | (byte << 8); break;
			case 3: 
				memoria[posicao] = memoria[posicao] & 0xFFFFFF00;
				memoria[posicao] = memoria[posicao] | (byte); break;
			default: break;
		}
		
		memoriaCacheDados(reg, memoria, output, 2, aux2);
		
	}
	
	//fprintf(output, "stb - memoria[0x%08X] = 0x%08X\n", ((reg[x] + imediato) >> 2), memoria[(reg[x] + imediato) >> 2]);
	//printf("[F] MEM[(0x%08X)] = R%d = 0x%08X\n", (reg[x] + imediato), y, aux);
	fprintf(output, "stb r%d, 0x%04X, r%d\n", x, imediato, y);
	fprintf(output, "[F] MEM[R%d + 0x%04X] = R%d = 0x%02X\n", x, imediato, y, byte);
	//printf("stb r%d, 0x%04X, r%d\n", x, imediato, y);
	//printf("[F] MEM[R%d + 0x%04X] = R%d = 0x%X\n", x, imediato, y, aux);

	//getchar();
}

// Controle de Fluxo

void bun(unsigned int hexaMemoria, unsigned int *reg, unsigned int *memoria, FILE* output){

	unsigned int PC = (hexaMemoria & 0x03FFFFFF) << 2; //atribuo ao pc_temp o IM26 << 2
	salto = (hexaMemoria & 0x03FFFFFF);

	//printf("PC = 0x%08X\n", PC);
	//printf("SALTO PARA A LINHA: %d\n", salto);
	//printf("PC >> 2 = %d\n", PC >> 2);

	reg[32] = PC; // PC = IM26, instru√ß√£o de desvio..
	fprintf(output, "bun 0x%08X\n", salto);
	fprintf(output, "[S] PC = 0x%08X\n", reg[32]);

//	printf("bun 0x%08X\n", salto);
//	printf("[S] PC = 0x%08X\n", reg[32]);

	//getchar();
	//Operacao(memoria[salto], reg, memoria);
	//return salto;
}

void beq(unsigned int hexaMemoria, unsigned int *reg, unsigned int *memoria, FILE* output){

	unsigned int PC = reg[32];
	unsigned int im26 = hexaMemoria & 0x03FFFFFF;
	// FR = |Reservado|OV|ZD|GT|LT|EQ|, Equal = 1
	if ( (reg[35] & 0x00000001) == 0x00000001){ // se o meu FR operado com minha mascara do FR, me retornar a mascara, significa que tem 1 no equal
		salto = (hexaMemoria & 0x03FFFFFF); // MUDEI AQUI, todas as comparacoes, coloquei salto em cima
		PC = (hexaMemoria & 0x03FFFFFF) << 2; //atribuo ao pc_temp o IM26 << 2
		reg[32] = PC;
	}else{
		reg[32] = reg[32] + 4; // incremento o PC, como n√£o √© igual eu n√£o desvio, s√≥ incremento...
	}

	fprintf(output, "beq 0x%08X\n", im26);
	fprintf(output, "[S] PC = 0x%08X\n", reg[32]);

//	printf("beq 0x%08X\n", im26);
//	printf("[S] PC = 0x%08X\n", reg[32]);

	//getchar();
	//reg[32] = PC;
}

void blt(unsigned int hexaMemoria, unsigned int *reg, unsigned int *memoria, FILE* output){

	unsigned int PC = reg[32];
	unsigned int im26 = hexaMemoria & 0x03FFFFFF;
	// FR = |Reservado|OV|ZD|GT|LT|EQ|, Less = 1
	if ( (reg[35] & 0x00000002) == 0x00000002){ // se o meu FR operado com minha mascara do FR, me retornar a mascara, significa que tem 1 no less
		salto = (hexaMemoria & 0x03FFFFFF);
		PC = (hexaMemoria & 0x03FFFFFF) << 2; //atribuo ao pc_temp o IM26 << 2
		reg[32] = PC;
	}else{
		reg[32] = reg[32] + 4; // incremento o PC, como n√£o √© igual eu n√£o desvio, s√≥ incremento...
	}

	fprintf(output, "blt 0x%08X\n", im26);
	fprintf(output, "[S] PC = 0x%08X\n", reg[32]);

}

void bgt(unsigned int hexaMemoria, unsigned int *reg, unsigned int *memoria, FILE* output){

	unsigned int PC = reg[32];
	unsigned int im26 = hexaMemoria & 0x03FFFFFF;
	//unsigned int bgt = hexaMemoria & 0x03FFFFFF;
	// FR = |Reservado|OV|ZD|GT|LT|EQ|, Gran = 1
	if ( (reg[35] & 0x00000004) == 0x00000004){ // se o meu FR operado com minha mascara do FR, me retornar a mascara, significa que tem 1 no gran
		salto = (hexaMemoria & 0x03FFFFFF);
		PC = (hexaMemoria & 0x03FFFFFF) << 2; //atribuo ao pc_temp o IM26 << 2
		reg[32] = PC;
	}else{
		reg[32] = reg[32] + 4; // incremento o PC, como n√£o √© igual eu n√£o desvio, s√≥ incremento...
		//printf("NAO FAZ NADA BGT\n");
	}

	fprintf(output, "bgt 0x%08X\n", im26);
	fprintf(output, "[S] PC = 0x%08X\n", reg[32]);

}

void bne(unsigned int hexaMemoria, unsigned int *reg, unsigned int *memoria, FILE* output){

	unsigned int PC = reg[32];
	unsigned int im26 = hexaMemoria & 0x03FFFFFF;
	
	//FR = |Reservado|OV|ZD|GT|LT|EQ|, Equal = 0
	if ( (reg[35] & 0x00000001) == 0x00000000){ // se o meu FR operado com minha mascara do FR, me retornar 0, significa que tem 0 no equal
		salto = (hexaMemoria & 0x03FFFFFF);
		PC = (hexaMemoria & 0x03FFFFFF) << 2; //atribuo ao pc_temp o IM26 << 2
		reg[32] = PC;
	}else{
		reg[32] = reg[32] + 4; //incremento o PC, como n√£o √© igual eu n√£o desvio, s√≥ incremento...
	}

	fprintf(output, "bne 0x%08X\n", im26);   // some salto+18 que pega, s√≥ deus sabe o porque
	fprintf(output, "[S] PC = 0x%08X\n", reg[32]);
}

void ble(unsigned int hexaMemoria, unsigned int *reg, unsigned int *memoria, FILE* output){

	unsigned int PC = reg[32];
	unsigned int im26 = hexaMemoria & 0x03FFFFFF;
	// FR = |Reservado|OV|ZD|GT|LT|EQ|, Less = 1 ||  FR = |Reservado|OV|ZD|GT|LT|EQ|, Equal = 1
	if ( ((reg[35] & 0x00000002) == 0x00000002) || ((reg[35] & 0x00000001) == 0x00000001) ){ // se o meu FR operado com minha mascara do FR, me retornar a mascara, significa que tem 1 no less
		salto = (hexaMemoria & 0x03FFFFFF);
		PC = (hexaMemoria & 0x03FFFFFF) << 2; //atribuo ao pc_temp o IM26 << 2
		reg[32] = PC;
	}else{
		reg[32] = reg[32] + 4; // incremento o PC, como n√£o √© igual eu n√£o desvio, s√≥ incremento...
	}

	fprintf(output, "ble 0x%08X\n", im26);
	fprintf(output, "[S] PC = 0x%08X\n", reg[32]);


}

void bge(unsigned int hexaMemoria, unsigned int *reg, unsigned int *memoria, FILE* output){

	unsigned int PC = reg[32];
	unsigned int im26 = hexaMemoria & 0x03FFFFFF;
		// FR = |Reservado|OV|ZD|GT|LT|EQ|, Gran = 1 ||  FR = |Reservado|OV|ZD|GT|LT|EQ|, Equal = 1
	if ( ((reg[35] & 0x00000004) == 0x00000004) || ((reg[35] & 0x00000001) == 0x00000001) ){
		salto = (hexaMemoria & 0x03FFFFFF);
		PC = (hexaMemoria & 0x03FFFFFF) << 2; //atribuo ao pc_temp o IM26 << 2
		reg[32] = PC;
		//printf("Entrei no IF\n");
	}else{
		//printf("N√£o entrei no IF\n");
		reg[32] = reg[32] + 4; // incremento o PC, como n√£o √© igual eu n√£o desvio, s√≥ incremento...
	}

	fprintf(output, "bge 0x%08X\n", im26);
	fprintf(output, "[S] PC = 0x%08X\n", reg[32]);

}

void interrupcao (unsigned int hexaMemoria, unsigned int *reg, unsigned int *memoria, FILE* output){
	unsigned int imediato = hexaMemoria & 0x03FFFFFF;


	if (imediato == 0 ){
		reg[36] = 0;
		reg[32] = imediato;
        fprintf(output, "int %d\n", imediato);
        fprintf(output, "[S] CR = 0x%08X, PC = 0x%08X\n", reg[36], reg[32]);
	}else{
		reg[36] = imediato;
		reg[37] = reg[32] + 4;
		reg[32] = 0x0000000C;
		salto = reg[32] >> 2;
        fprintf(output, "int %d\n", imediato);
        fprintf(output, "[S] CR = 0x%08X, PC = 0x%08X\n", reg[36], reg[32]);
        fprintf(output, "[SOFTWARE INTERRUPTION]\n");
    }

}

void call (unsigned int hexaMemoria, unsigned int *reg, FILE* output){

	unsigned int x, y, imediato;

	x = (hexaMemoria & 0x000003E0) >> 5;
	y = (hexaMemoria & 0x0000001F);
	imediato = (hexaMemoria & 0x03FFFC00) >> 10;

	//printf("VIM AQUI\n");

	if (x != 0)
		reg[x] = (reg[32] + 4) >> 2 ;
	reg[32] = (reg[y] + imediato) << 2;
	salto = reg[y] + imediato;

	fprintf(output, "call r%d, r%d, 0x%04X\n", x, y, imediato);
	fprintf(output, "[F] R%d = (PC + 4) >> 2 = 0x%08X, PC = (R%d + 0x%04X) << 2 = 0x%08X\n", x, reg[x], y, imediato, reg[32]);

//	printf("call r%d, r%d, 0x%04X\n", x, y, imediato);
//	printf("[F] R%d = (PC + 4) >> 2 = 0x%08X, PC = (R%d + 0x%04X) << 2 = 0x%08X\n", x, reg[x], y, imediato, reg[32]);
//	getchar();
}

void ret (unsigned int hexaMemoria, unsigned int *reg, FILE* output){

	unsigned int x;
	x = (hexaMemoria & 0x000003E0) >> 5;

	//printf("0x%08X\n", reg[32]);

	reg[32] = reg[x] << 2 ;
	salto = reg[x];
	//printf("PC: 0x%08X\n", reg[32]);
	//printf("salto: 0x%08X\n", salto);

	fprintf(output, "ret r%d\n", x);
	fprintf(output, "[F] PC = R%d << 2 = 0x%08X\n",x, reg[32]);

}

float IEEE754 (int num){
	
	int i;
	double fracionaria = 0;
	for (i = 0; i < 23; i++) {
		if ( (num & (0x00400000 >> i) ) != 0 ){
			fracionaria += pow(2,(-1)*(1 + i));
		}
	}
	uint32_t expoente = ((num & 0x7F800000) >> 23) - 127;
	uint32_t sinal = (num & 0x80000000) >> 31;
	
	return pow(-1, sinal) * (1 + fracionaria) * pow(2, expoente);
}

void push (unsigned int hexaMemoria, unsigned int *memoria, unsigned int *reg, FILE* output, no *PILHA){

	unsigned int x, y, ex, ey, aux;
	//no *novo = (no *) malloc(sizeof(no));

	y = (hexaMemoria & 0x0000001F);
	x = (hexaMemoria & 0x000003E0) >> 5;
	ey = (hexaMemoria & 0x00008000) >> 10;
	ex = (hexaMemoria & 0x00010000) >> 11;

	aux = reg[x+ex]--;            // decremento reg[x]

	//novo->num = reg[y+ey]; //atribuo o valor a novo n√≥..
	//novo->prox = NULL; // seto proximo == NULL

	if( y+ey == 32 )
		memoria[aux] = salto-1;
	else
		memoria[aux] = reg[y+ey];
		
	memoriaCacheDados(reg, memoria, output, 2, aux);

	fprintf(output, "push r%d, r%d\n", (x+ex), (y+ey));
	fprintf(output, "[U] MEM[R%d--] = R%d = 0x%08X\n", (x+ex), (y+ey), memoria[aux]); // MUDEI AQUI, de reg[y+ey] para memoria[aux]

	reg[32] = reg[32] + 4; // incremento o PC, como n√£o √© igual eu n√£o desvio, s√≥ incremento...
}

void pop (unsigned int hexaMemoria, unsigned int *memoria, unsigned int *reg, FILE* output, no *PILHA){

	unsigned int x, y, ex, ey, aux;

	y = (hexaMemoria & 0x0000001F);
	x = (hexaMemoria & 0x000003E0) >> 5;
	ey = (hexaMemoria & 0x00008000) >> 10;
	ex = (hexaMemoria & 0x00010000) >> 11;


	aux = ++reg[y+ey];
	if ((x+ex) != 0 )
		reg[x+ex] = memoria[aux];

	memoriaCacheDados(reg, memoria, output, 1, aux);

	fprintf(output, "pop r%d, r%d\n", (x+ex), (y+ey));
	fprintf(output, "[U] R%d = MEM[++R%d] = 0x%08X\n", (x+ex), (y+ey), reg[x+ex]);
	//free(ultimo);
	//}

	reg[32] = reg[32] + 4; // incremento o PC,

}

void bzd (unsigned int hexaMemoria, unsigned int *reg, FILE* output){

	unsigned int PC = reg[32];
	unsigned int im26 = hexaMemoria & 0x03FFFFFF;

	// FR = |Reservado|IE|IV|OV|ZD|GT|LT|EQ|, Equal = 1
	if ( (reg[35] & 0x00000008) == 0x00000008){
			PC = (hexaMemoria & 0x03FFFFFF) << 2 ;
			salto = (hexaMemoria & 0x03FFFFFF);
			reg[32] = PC;
	}else{
		reg[32] = reg[32] + 4;

	}
	fprintf(output, "bzd 0x%08X\n", im26);
	fprintf(output, "[S] PC = 0x%08X\n", reg[32]);

//	printf("Salto: 0x%08X\n", salto);
//	getchar();
}

void bnz (unsigned int hexaMemoria, unsigned int *reg, FILE* output){

	unsigned int PC = reg[32];
	unsigned int im26 = hexaMemoria & 0x03FFFFFF;

	// FR = |Reservado|IE|IV|OV|ZD|GT|LT|EQ|, Equal = 1
	if ( (reg[35] & 0x00000008) == 0x00000000){
			PC = (hexaMemoria & 0x03FFFFFF) << 2 ; //atribuo ao pc_temp o IM26
			salto = (hexaMemoria & 0x03FFFFFF);
			reg[32] = PC;
	}else{
		reg[32] = reg[32] + 4; // incremento o PC, como n√£o √© igual eu n√£o desvio, s√≥ incremento...
	}
	fprintf(output, "bnz 0x%08X\n", im26);
	fprintf(output, "[S] PC = 0x%08X\n", reg[32]);
}

void biv (unsigned int hexaMemoria, unsigned int *reg, FILE* output){

	unsigned int PC = reg[32];
	unsigned int im26 = hexaMemoria & 0x03FFFFFF;

	//printf("FR = 0x%08X\n", reg[35]);
	// FR = |Reservado|IE|IV|OV|ZD|GT|LT|EQ|, Equal = 1
	if ( (reg[35] & 0x00000020) == 0x00000020){
			salto = im26;
			PC = (hexaMemoria & 0x03FFFFFF) << 2 ; //atribuo ao pc_temp o IM26
			reg[32] = PC;
	}else{
		reg[32] = reg[32] + 4;
	}
	fprintf(output, "biv 0x%08X\n", im26);
	fprintf(output, "[S] PC = 0x%08X\n", reg[32]);
}

void bni (unsigned int hexaMemoria, unsigned int *reg, FILE* output, unsigned int *memoria){

	unsigned int PC = reg[32];
	unsigned int im26 = hexaMemoria & 0x03FFFFFF;

	// FR = |Reservado|IE|IV|OV|ZD|GT|LT|EQ|, Equal = 1
	if ( (reg[35] & 0x00000020) == 0x00000000){
			salto = im26;
			PC = (hexaMemoria & 0x03FFFFFF) << 2 ; //atribuo ao pc_temp o IM26
			reg[32] = PC;
	}else{
		reg[32] = reg[32] + 4; // incremento o PC, como n√£o √© igual eu n√£o desvio, s√≥ incremento...
		//printf("NAO FAZ NADA BGT\n");
	}
	fprintf(output, "bni 0x%08X\n", im26);
	fprintf(output, "[S] PC = 0x%08X\n", reg[32]);
}

void isr (unsigned int hexaMemoria, unsigned int *reg, FILE* output){

	unsigned int x, y, imediato;
	y = (hexaMemoria & 0x0000001F);
	//ey = (hexaMemoria & 0x00008000) >> 10;
	x = (hexaMemoria & 0x000003E0) >> 5;
	//ex = (hexaMemoria & 0x00010000) >> 11;

	imediato = (hexaMemoria & 0x03FFFC00) >> 10;

	//printf("salto: 0x%08X\n", salto);
	//printf("PC: 0x%08X\n", reg[32]);
	//IPC = PC >> 2

	reg[x] = reg[37] >> 2; //
	reg[y] = reg[36];

	reg[32] = imediato << 2;
	salto = imediato;

//	printf("salto: 0x%08X\n", salto);
//	printf("PC: 0x%08X\n", reg[32]);
	
	fprintf(output, "isr r%d, r%d, 0x%04X\n", (x), (y), imediato);
	fprintf(output, "[F] R%d = IPC >> 2 = 0x%08X, R%d = CR = 0x%08X, PC = 0x%08X\n", (x), reg[x], (y), reg[y], reg[32]);

  //           printf("isr r%d, r%d, 0x%04X\n", (x+ex), (y+ey), imediato);
 //         printf("[F] R%d = IPC >> 2 = 0x%08X, R%d = CR = 0x%08X, PC = 0x%08X\n", (x+ex), reg[x+ex], (y+ey), reg[y+ey], reg[32]);

}

void reti (unsigned int hexaMemoria, unsigned int *reg, FILE* output){

	unsigned int x;
	x = (hexaMemoria & 0x000003E0) >> 5;
	//printf("0x%08X\n", reg[32]);
	reg[32] = reg[x] << 2 ;
	salto = reg[x];
	//printf("0x%08X\n", reg[32]);
	fprintf(output, "reti r%d\n", x);
	fprintf(output, "[F] PC = R%d << 2 = 0x%08X\n",x, reg[32]);
	//fprintf(output, "memoria[0x%08X] = 0x%08X\n", salto, memoria[salto]);

}

