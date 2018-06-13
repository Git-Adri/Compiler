all:compiler
lex.yy.c: compiler.l
	./flex compiler.l
rule.tab.c: rule.y
	~/bison/bin/bison -d -v rule.y
compiler: lex.yy.c rule.tab.c
	gcc -g -std=c99 -o compiler lex.yy.c tab_symboles.c tab_instructions.c rule.tab.c libfl.a ~/bison/lib/liby.a

clean:
	rm -rf compiler lex.yy.c rule.tab.c
test: compiler
	./compiler<test.c
	./compiler<test.c  | grep @ | cut -d" " -f2 > asm
