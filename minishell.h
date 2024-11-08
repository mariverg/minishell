typedef struct s_comand {
	char *c;
	char **cc;
	char **env;
	int operator;
	int in;
	int out;
} t_comand;

t_comand *newcom(char *c, char **cc, char **env);

pid_t ejecuta(t_comand *tc, pid_t entrada);

void copitofile(t_comand *tc);
void readfromfile(t_comand *tc);

void execver(t_comand *tc);