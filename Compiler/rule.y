%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "tab_symboles.h"
	#include "tab_instructions.h"
	char * type;
	int yylex(void);
	void yyerror(char*);
%}

%union {
	int nb;
	char* str;
}

%token tVIRG
%token tPV
%token tIMPR
%token tACCO
%token tACCF
%token tPLUS
%token tMOINS
%token tMULT
%token tDIV
%token tEGAL
%token tPARO
%token tPARF
%token tCONST
%token tID
%token tNB
%token tINT
%token tVOID
%token tWHILE
%token tIF
%token tELSE
%token tDOUBLE_EGAL
%token tDIFF
%token tINF
%token tINFE
%token tSUP
%token tSUPE

%left tEGAL
%left tDOUBLE_EGAL tDIFF tINF tINFE tSUP tSUPE
%left tPLUS tMOINS
%left tMULT tDIV

%nonassoc tTRUC
%nonassoc tELSE

%type <str> tID tINT type
%type <nb> tNB bloc_if_action bloc_else_action 

%%
start:fonctions ;

fonctions:
	  fonction fonctions
	|
	;

fonction:
	  type tID tPARO args tPARF body
	;

type: tINT {type = "int";};

args:arg args_suite
	| 
	;

args_suite: tVIRG arg args_suite
	| 
	; 

arg: type tID ;

body:
	tACCO instrs tACCF
	;

instrs:
	instr instrs
	|
	;

instr:
	appel_fonction
	| declaration_variables
	| calcul
	| printf
	| bloc_if
	| bloc_while
	;






bloc_while : tWHILE tPARO operation tPARF body_while
		  		{ printf("On a reconnu un bloc while\n");};

body_while : tACCO instrs tACCF 
		 | instr tPV;





bloc_if_action:
	{		
		ajouter_instr(7, get_last_addr()-1, 9);
		ajouter_instr(15, -1, 9); 
		enlever_var();
		$$ = get_last_instr_addr() -1;} ;


bloc_else_action:
	{ ajouter_instr(14, -1, 222 ); 
	  $$ = get_last_instr_addr() -1;} ;

bloc_if : tIF tPARO operation tPARF bloc_if_action body_if
		  		{ patchInstr($5, get_last_instr_addr()); } %prec tTRUC 
		  | tIF tPARO operation tPARF bloc_if_action body_if
				bloc_else_action tELSE { patchInstr($5, get_last_instr_addr()); } body_if { patchInstr($7 , get_last_instr_addr()); };


body_if : tACCO instrs tACCF 
		 | instr tPV;


appel_fonction:
	tID tPARO valeurs tPARF tPV ;

printf : tIMPR tPARO operation tPARF tPV 
		{printf("Ok, on a un Print\n");};

decl: type tID {ajouter_var($2, type, 1);} decl_affect ;

decl_affect : | tEGAL operation { 
	ajouter_instr(7, get_last_addr(), 0);
	enlever_var(); 
	//On récupère la valeur et on l'inscrit au bon endroit dans la mémoire
	ajouter_instr(8, get_last_addr()-1, 0);
	 } ;

declaration_variables:
	decl declaration_variables_suite tPV;

declaration_variables_suite: tVIRG tID {ajouter_var($2, type, 1);} declaration_variables_suite
							| ;

valeurs: operation valeurs_suite
		| 
		;

valeurs_suite: tVIRG operation valeurs_suite
				| 
				;

valeur_ar: tID
		  {
		  ajouter_instr(7, get_addr($1), 0);
		  ajouter_instr(8, ajouter_tmp(), 0);}
		| tNB 
		  {
		  ajouter_instr(6, 0, $1);
		  ajouter_instr(8, ajouter_tmp(), 0);
		  }
		| appel_fonction ;


operation : operation tPLUS operation {
				ajouter_instr(7, get_last_addr(), 1);
				ajouter_instr(7, get_last_addr()-1, 0);
				ajouter_instr(1, 0, 1);
				ajouter_instr(8, get_last_addr()-2, 0);
				enlever_var();
				}
			| operation tMOINS operation {
				ajouter_instr(7, get_last_addr(), 1);
				ajouter_instr(7, get_last_addr()-1, 0);
				ajouter_instr(3, 0, 1);
				ajouter_instr(8, get_last_addr()-2, 0);
				enlever_var();
				}
			| operation tMULT operation {
				ajouter_instr(7, get_last_addr(), 1);
				ajouter_instr(7, get_last_addr()-1, 0);
				ajouter_instr(2, 0, 1);
				ajouter_instr(8, get_last_addr()-2, 0);
				enlever_var();
				}
			| operation tDIV operation {
				ajouter_instr(7, get_last_addr(), 1);
				ajouter_instr(7, get_last_addr()-1, 0);
				ajouter_instr(4, 0, 1);
				ajouter_instr(8, get_last_addr()-2, 0);
				enlever_var();
				}
			| operation tDOUBLE_EGAL operation {
				ajouter_instr(7, get_last_addr(), 1);
				ajouter_instr(7, get_last_addr()-1, 0);
				ajouter_instr(9, 0, 1);
				ajouter_instr(8, get_last_addr()-2, 0);
				enlever_var();
				}
			| operation tINF operation {
				ajouter_instr(7, get_last_addr(), 1);
				ajouter_instr(7, get_last_addr()-1, 0);
				ajouter_instr(10, 0, 1);
				ajouter_instr(8, get_last_addr()-2, 0);
				enlever_var();
				}
			| operation tINFE operation {
				ajouter_instr(7, get_last_addr(), 1);
				ajouter_instr(7, get_last_addr()-1, 0);
				ajouter_instr(11, 0, 1);
				ajouter_instr(8, get_last_addr()-2, 0);
				enlever_var();
				}
			| operation tSUP operation {
				ajouter_instr(7, get_last_addr(), 1);
				ajouter_instr(7, get_last_addr()-1, 0);
				ajouter_instr(12, 0, 1);
				ajouter_instr(8, get_last_addr()-2, 0);
				enlever_var();
				}
			| operation tSUPE operation {
				ajouter_instr(7, get_last_addr(), 1);
				ajouter_instr(7, get_last_addr()-1, 0);
				ajouter_instr(13, 0, 1);
				ajouter_instr(8, get_last_addr()-2, 0);
				enlever_var();
				}
			| tPARO operation tPARF
			| valeur_ar ;

calcul: tID tEGAL operation tPV {
		int a = get_addr($1);
		ajouter_instr(7, get_last_addr() - 1, 0);
		ajouter_instr(8, a, 0);
		enlever_var(); } ;

%%

void yyerror(char *err) {
	extern int yylineno;
	printf("error: %s (%d)\n", err, yylineno);
	exit(1);
}

int main(){

	printf("On parse le code c\n");
	yyparse();
	printf("Voici la table des instructions générés :\n");
	print_tab_instr();

} 
