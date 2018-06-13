typedef struct ligne {
char* id ;
char* type ; 
int val ;
int depth ; 
}ligne;

void ajouter_var (char* id, char* type, int depth);

int get_addr (char* id_wanted) ;

int get_last_addr() ;

void enlever_var ();

void enlever_var_depth (int depth);

void print_tab();

int ajouter_tmp ();

