%{
#include "parser.tab.h"
#include <string.h>

extern char current_input[1024];
extern int input_length;
%}

%%

1       { current_input[input_length++] = '1'; return A; }
0       { current_input[input_length++] = '0'; return B; }
\n      return NEWLINE;
.       return yytext[0];
%%

int yywrap() {
    return 1;
}
