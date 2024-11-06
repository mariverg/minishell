#include <stdlib.h>		///mallocs
#include <unistd.h>		///writes

int strsize(char *c);
int ischar(char c, char *ca);
int charpos(char *c, char *ca);
int charamount(char *c, char *ca);
int strscmp(char *ca, char *cb);
int strxsize(char **c);
int inmap(char **map, int x, int y);

char *dupstr(char *c);
char *sumstrs(char *ca, char *cb);
char *trimstr(char *c, int left, int right);
char *cutstr(char *c, int i);
char *delchars(char *c, char *dels, int erase);

char **sumxstrs(char **ca, char **cb);

char **strdivide(char *c, char *ca);
char **strxplode(char *c, char *ca);
char **strdisolve(char *c, char *ca);
void freestrs(char **c);
void prntstrs(char **c);

int findstr(char *c, char *target);
int findstrrow(char **c, char *target);

char **excludeliteral(char *c, char *exclusor);