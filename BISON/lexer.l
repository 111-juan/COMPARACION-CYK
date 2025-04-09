%{
#include "parser.tab.h"
%}

%%
1       return A;
0       return B;
\n      return NEWLINE;
.       return yytext[0];
%%

int yywrap() {
    return 1;
}
