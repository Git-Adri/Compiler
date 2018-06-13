%{
#include <stdio.h>
#include <string.h>
#include "rule.tab.h"
//main" return tMAIN ;
%}


%%

[ \t\n]+	;



"(" return tPARO ;
")" return tPARF ;
"{" return tACCO ;
"}" return tACCF ;


"int" {yylval.str = strdup(yytext); return tINT ;}
"const" {yylval.str = strdup(yytext); return tCONST ;}
";" return tPV ;
"," return tVIRG ;

"+" return tPLUS ;
"-" return tMOINS ;
"*" return tMULT ;
"/" return tDIV ;
"=" return tEGAL ;
"==" return tDOUBLE_EGAL;
"!" return tDIFF ;
"<" return tINF ;
"<=" return tINFE;
">" return tSUP ;
">=" return tSUPE;
"void" return tVOID;

"if" return tIF ;
"else" return tELSE ;
"while" return tWHILE ;



"printf" return tIMPR ;

[a-zA-Z_]+ { yylval.str = strdup(yytext);
						return tID ;
			}
[0-9]+(e[0-9]+)?	{yylval.nb = atoi(yytext);
						return tNB ;
					}
