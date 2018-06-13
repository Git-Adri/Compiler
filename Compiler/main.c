#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int index_act=0;
int registres[16];
int memoire[16];

typedef struct { int indice; char* instr; int arg1; int arg2; } Instruction; 

void print_tab(Instruction tab_instruction[]){
	int i =0;	
	
	for (i; i < index_act; i++){
		printf("index_act= %d instruction = %s arg1= %d, arg2= %d\n", tab_instruction[i].indice, tab_instruction[i].instr, tab_instruction[i].arg1, tab_instruction[i].arg2);
	}

}

void print_mem(int tab_mem[]){
	int i =0;	
	
	for (i; i < 16; i++){
		printf("index_act= %d valeur = %d\n",i, tab_mem[i]);
	}

}


void print_reg(int tab_reg[]){
	int i =0;	
	
	for (i; i < 16; i++){
		printf("index_act= %d valeur = %d\n",i, tab_reg[i]);
	}

}

void interpreteur(Instruction tab_instruction[]){

	int i =0;

	for (i; i < index_act; i++){
		
		if (strcmp(tab_instruction[i].instr,"ADD")==0){

			registres[tab_instruction[i].arg1]=registres[tab_instruction[i].arg1]+registres[tab_instruction[i].arg2];

		}

		else if (strcmp(tab_instruction[i].instr,"SOU")==0){

			registres[tab_instruction[i].arg1]=registres[tab_instruction[i].arg1]-registres[tab_instruction[i].arg2];

		}

		else if (strcmp(tab_instruction[i].instr,"MUL")==0){

			registres[tab_instruction[i].arg1]=registres[tab_instruction[i].arg1]*registres[tab_instruction[i].arg2];

		}

		else if (strcmp(tab_instruction[i].instr,"DIV")==0){

			registres[tab_instruction[i].arg1]=registres[tab_instruction[i].arg1]/registres[tab_instruction[i].arg2];

		}

		else if (strcmp(tab_instruction[i].instr,"COP")==0){

			registres[tab_instruction[i].arg1]=registres[tab_instruction[i].arg2];

		}

		else if (strcmp(tab_instruction[i].instr,"AFC")==0){

			registres[tab_instruction[i].arg1]=tab_instruction[i].arg2;

		}

		else if (strcmp(tab_instruction[i].instr,"LOAD")==0){

			registres[tab_instruction[i].arg2]=memoire[tab_instruction[i].arg1];
 			printf("Je LOAD l'index %d de la mémoire, sa valeur est %d. Je le met à l'index %d dans les registres \n" ,tab_instruction[i].arg1, memoire[tab_instruction[i].arg1], tab_instruction[i].arg2);

		}

		else if (strcmp(tab_instruction[i].instr,"STORE")==0){
			
			memoire[tab_instruction[i].arg1]=registres[tab_instruction[i].arg2];
 			printf("Je STORE l'index %d des registres, sa valeur est %d. Je le met à l'index %d dans la mémoire \n" ,tab_instruction[i].arg2, registres[tab_instruction[i].arg2], tab_instruction[i].arg1);

		}

		else if (strcmp(tab_instruction[i].instr,"EQU")==0){
			printf("Je compare %d et %d \n", registres[tab_instruction[i].arg2],registres[tab_instruction[i].arg1]);
			if (registres[tab_instruction[i].arg2]==registres[tab_instruction[i].arg1]){
				registres[tab_instruction[i].arg1] = 1;
			}

			else {registres[tab_instruction[i].arg1] = 0;}

		}

		else if (strcmp(tab_instruction[i].instr,"INF")==0){
			if (registres[tab_instruction[i].arg2]<registres[tab_instruction[i].arg1]){
				registres[tab_instruction[i].arg1] = 1;
			}

			else {registres[tab_instruction[i].arg1] = 0;}

		}

		else if (strcmp(tab_instruction[i].instr,"INFE")==0){
			if (registres[tab_instruction[i].arg2]<=registres[tab_instruction[i].arg1]){
				registres[tab_instruction[i].arg1] = 1;
			}

			else {registres[tab_instruction[i].arg1] = 0;}

		}

		else if (strcmp(tab_instruction[i].instr,"SUP")==0){
			if (registres[tab_instruction[i].arg2]>registres[tab_instruction[i].arg1]){
				registres[tab_instruction[i].arg1] = 1;
			}

			else {registres[tab_instruction[i].arg1] = 0;}

		}

		else if (strcmp(tab_instruction[i].instr,"SUPE")==0){
			if (registres[tab_instruction[i].arg2]<=registres[tab_instruction[i].arg1]){
				registres[tab_instruction[i].arg1] = 1;
			}

			else {registres[tab_instruction[i].arg1] = 0;}

		}


		else if (strcmp(tab_instruction[i].instr,"JMP")==0){

			i = tab_instruction[i].arg1-1;

		}

		else if (strcmp(tab_instruction[i].instr,"JMPC")==0){

			if (registres[tab_instruction[i].arg2]==0){
				i = tab_instruction[i].arg1-1;
			}

		}

		else {
		
			printf("Vous n'avez pas rentre une instruction correcte!");

	  	}

	}

}


int main()
{

    FILE* fichier = NULL;

	Instruction tab_instruction[1024];

    fichier = fopen("asm", "r");

	int instruction_size=3; 
	int argument_size=5;

	char instruction[instruction_size];
	char argument[argument_size];		


    if (fichier != NULL)

    {


		while (fgets(instruction, instruction_size, fichier)!=NULL){ // On lit le num de 'instruction


			tab_instruction[index_act].indice = index_act;

			if (strcmp(instruction, "01")==0){
				tab_instruction[index_act].instr="ADD";
			}
	
			else if(strcmp(instruction, "02")==0){
				tab_instruction[index_act].instr="MUL";
			}

			else if(strcmp(instruction, "03")==0){
				tab_instruction[index_act].instr="SOU";
			}

			else if(strcmp(instruction, "04")==0){
				tab_instruction[index_act].instr="DIV";
			}

			else if(strcmp(instruction, "05")==0){
				tab_instruction[index_act].instr="COP";
			}

			else if(strcmp(instruction, "06")==0){
				tab_instruction[index_act].instr="AFC";
			}

			else if(strcmp(instruction, "07")==0){
				tab_instruction[index_act].instr="LOAD";
			}

			else if(strcmp(instruction, "08")==0){
				tab_instruction[index_act].instr="STORE";
			}

			else if(strcmp(instruction, "09")==0){
				tab_instruction[index_act].instr="EQU";
			}

			else if(strcmp(instruction, "0a")==0){
				tab_instruction[index_act].instr="INF";
			}

			else if(strcmp(instruction, "0b")==0){
				tab_instruction[index_act].instr="INFE";
			}

			else if(strcmp(instruction, "0c")==0){
				tab_instruction[index_act].instr="SUP";
			}

			else if(strcmp(instruction, "0d")==0){
				tab_instruction[index_act].instr="SUPE";
			}

			else if(strcmp(instruction, "0e")==0){
				tab_instruction[index_act].instr="JMP";
			}

			else if(strcmp(instruction, "0f")==0){
				tab_instruction[index_act].instr="JMPC";
			}

			fgets(argument, argument_size, fichier);

			tab_instruction[index_act].arg1=atoi(argument);

			fgets(argument, argument_size, fichier);

			tab_instruction[index_act].arg2=atoi(argument);

			fseek(fichier, 1, SEEK_CUR);	//on change de ligne
			index_act++;		
		}

		interpreteur(tab_instruction);
				printf("index act : %d\n", index_act);
		printf("##############TABLEAU INSTRUCTION#############\n");
		print_tab(tab_instruction);
		printf("##############TABLEAU MEMOIRE#############\n");
		print_mem(memoire);
		printf("##############REGISTRES#############\n");
		print_reg(registres);
        fclose(fichier); // On ferme le fichier qui a été ouvert
	
    }

    else

    {

        // On affiche un message d'erreur si on veut

        printf("Impossible d'ouvrir le fichier test.txt");

    }

    return 0;
}
