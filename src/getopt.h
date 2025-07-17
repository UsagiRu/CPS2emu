#ifndef GETOPT_H_
#define GETOPT_H_

// Define structures and constants
struct option {
    const char *name;
    int has_arg;
    int *flag;
    int val;
};

#define no_argument       0
#define required_argument 1
#define optional_argument 2

// Variaveis globais para o manuseio de opções 
extern char *optarg; // Argumento de opção
extern int optind;   // Índice de argumento seguinte
extern int optopt;   // Opção não reconhecida
extern int opterr;   // Controle de mensagens de erro

// Prototipo da função getopt_long
int getopt_long(int argc, char *const argv[], const char *optstring, const struct option *longopts, int *longindex);

#endif /* GETOPT_H_ */
