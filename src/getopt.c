//getopt_h

#include "getopt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variaveis globais para o manuseio de opções 
char *optarg; // Argumento de opção
int optind;   // Índice de argumento seguinte
int optopt;   // Opção não reconhecida
int opterr;   // Controle de mensagens de erro

int getopt_long(int argc, char *const argv[], const char *optstring, const struct option *longopts, int *longindex) {
    static int optindex = 1;
    static int subindex = 1;
    const char *arg = argv[optindex];
    const struct option *opt;

    if (optindex >= argc || argv[optindex][0] != '-') {
        return -1; // No more options
    }

    if (arg[0] == '-' && arg[1] == '-') {
        // Long option
        arg += 2;
        for (opt = longopts; opt->name; ++opt) {
            int len = strlen(opt->name);
            if (strncmp(arg, opt->name, len) == 0) {
                if (arg[len] == '\0') {
                    // Exact match
                    optarg = NULL;
                    if (opt->has_arg == required_argument) {
                        if (optindex + 1 < argc) {
                            optarg = argv[++optindex];
                        } else {
                            if (opterr) {
                                fprintf(stderr, "Option '--%s' requires an argument\n", opt->name);
                            }
                            return '?';
                        }
                    }
                    if (opt->flag) {
                        *(opt->flag) = opt->val;
                        return 0;
                    } else {
                        return opt->val;
                    }
                } else if (arg[len] == '=') {
                    // Option with argument
                    if (opt->has_arg == no_argument) {
                        if (opterr) {
                            fprintf(stderr, "Option '--%s' doesn't allow an argument\n", opt->name);
                        }
                        return '?';
                    }
                    optarg = &arg[len + 1];
                    if (opt->flag) {
                        *(opt->flag) = opt->val;
                        return 0;
                    } else {
                        return opt->val;
                    }
                }
            }
        }

        // Unknown option
        if (opterr) {
            fprintf(stderr, "Unknown option '--%s'\n", arg);
        }
        return '?';
    } else {
        // Short option
        char optchar = arg[subindex];
        const char *optdecl = strchr(optstring, optchar);
        if (!optdecl) {
            if (opterr) {
                fprintf(stderr, "Unknown option '-%c'\n", optchar);
            }
            return '?';
        }
        if (optdecl[1] == ':') {
            // Option with argument
            if (arg[subindex + 1] != '\0') {
                optarg = &arg[subindex + 1];
            } else if (optindex + 1 < argc) {
                optarg = argv[++optindex];
            } else {
                if (opterr) {
                    fprintf(stderr, "Option '-%c' requires an argument\n", optchar);
                }
                return '?';
            }
            optindex++;
            subindex = 1;
        } else {
            optarg = NULL;
            if (arg[++subindex] == '\0') {
                subindex = 1;
                optindex++;
            }
        }
        return optchar;
    }
}
