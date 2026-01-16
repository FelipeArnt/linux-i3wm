//cmd [arg]* [ | cmd[arg]* ]*
//    [ [> filename] ] [ [< filename] ] [ [>& filename] ] [ [>> filename] ] [ [>>& filename] ]* [&]




%{
#include <string.h>
#include "y.tab.h"
%}
%%
\n
{
return NEWLINE;
}
[ \t]
{
/* Discard spaces and tabs */
}
">"
{
return GREAT;
}
"<"
{
return LESS;
}
">>"
{
return GREATGREAT;
">&"
{
ra
ft
}
return GREATAMPERSAND;
}
“|”
{
return PIPE;
}
“&”
{
return AMPERSAND;
D
}
[^ \t\n][^ \t\n]* {
yylval.string_val = strdup(yytext);
return WORD;
}
/* Add more tokens here */
.
{
/* Caracter inválido no input */
return NOTOKEN;
}
%%
