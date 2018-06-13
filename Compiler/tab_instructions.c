#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tab_instructions.h"

int index_instr = 0;
struct ligne_instr tab_instruction[1024];

void ajouter_instr (int instr, int param1, int param2){

	
		tab_instruction[index_instr].instruc = instr;
		tab_instruction[index_instr].param1 = param1;
		tab_instruction[index_instr].param2 = param2;
		index_instr++;
		printf("On ajoute une instruction : nom= %d , param1= %d, param2 = %d\n", instr , param1, param2) ;

}

void patchInstr(int indOrig, int indDest){
	tab_instruction[indOrig].param1 = indDest;
}
	

int get_addr_instr (int instr, int param1, int param2){
	int index = -1 ;
	int i =0;
	for(i; i< index_instr; i++){
		if(tab_instruction[i].instruc==instr && tab_instruction[i].param1 == param1 && tab_instruction[i].param2==param2){
			index = i ;
		}
	}

	if (index == -1){
		printf("\nAttention on a pas trouvé l'instruction recherchée\n") ;
	}
	return index ;
}


int get_last_instr_addr(){return index_instr;}


void print_tab_instr(){
	printf("   Instruc   |   P1    | P2 |\n");
	int i =0;
	for(i; i< index_instr; i++){
		printf("%02x   %d  |   %d       |     %d      |\n" , i, tab_instruction[i].instruc , tab_instruction[i].param1, tab_instruction[i].param2);
		printf("@# %02x%04x%04x\n" , tab_instruction[i].instruc , tab_instruction[i].param1, tab_instruction[i].param2);
	}
	printf("Nombre de ligne dans le tableau : %d\n", index_instr);
}

