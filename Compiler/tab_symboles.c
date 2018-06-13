#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tab_symboles.h"

int index_var = 0;
struct ligne tab[1024];


void ajouter_var (char* id, char* type, int depth){

	int present = 0 ;
printf("index: %d\n", index_var);
	int i =0;
	for(i; i< index_var; i++){
		if(strcmp(tab[i].id , id)==0 && strcmp(tab[i].id , "tmp")!=0){
			present = 1 ;
		}
	}
	if(present==0){
		tab[index_var].id = id;
		tab[index_var].type = type;
		tab[index_var].depth = depth;
		index_var++;
		printf("On ajoute un ligne : id=%s  , type= %s, profondeur = %d\n", id , type, depth) ;
	}
}	


int get_addr(char *s) {
	for (int i=index_var - 1; i >= 0 ; i--) {
		if (!strcmp(s, tab[i].id)) {
			return i;
		}
	}
	return -1;
}

int get_last_addr (){
	return index_var ;
}


void enlever_var (){
	index_var-- ;
	printf("On viens d'effacer une valeur de la table des symboles\n");
}


void enlever_var_depth (int depth){
	int debut = -1 ;
	for(int i=0 ; i < index_var ; i++){
		if(tab[i].depth == depth && debut==-1){
			debut= i ;
		} 
	}
	index_var = index_var-(index_var-debut);
	
}


void print_tab(){
	printf("   ID   |   Type    | Profondeur |\n");
	for(int i=0; i< index_var; i++){
		printf("   %s  |   %s       |     %d      |\n" , tab[i].id , tab[i].type, tab[i].depth);
	}
	printf("Nombre de ligne dans le tableau : %d\n", index_var);
}


int ajouter_tmp (){
	if (index_var < 0 || index_var >= 1024) {
		printf("Erreur d'indice\n");
		exit(1);
	} else {
		tab[index_var].id = "tmp";
		tab[index_var].type = "int";
		tab[index_var].depth = 0;
		index_var++;
		printf("On ajoute un ligne var tmp");
	}
	return index_var;
}





