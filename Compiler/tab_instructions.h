typedef struct ligne_instr {
int instruc ;
int param1 ;
int param2 ; 
}ligne_instr;

void ajouter_instr (int instr, int param1, int param2);

void patchInstr(int indOrig, int indDest);

int get_addr_instr (int instr, int param1, int param2);

int get_last_instr_addr();

void print_tab_instr();


