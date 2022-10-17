%option noyywrap

%{
#include "SymbolNodes.h"
#include "Grammar.tab.h"
#include "SymbolTable.h"
#define YY_DECL int yylex(yy::parser::semantic_type *yylval)
typedef yy::parser::token token;

%}


%%


";" {return ';';}
"+" {return '+';}
"-" {return '-';}
"*" {return '*';}
"/" {return '/';}
"=" {return '=';}
"," {return ',';}
"(" { return '(';}
")" { return ')';}
"{" { return '{';}
"}" { return '}';}
"<" { return token::L;}
">" { return token::G;}
"<=" { return token::LE;}
">=" { return token::GE;}
"==" { return token::EQ;}
"!=" { return token::NE;}
"&&" { return token::AND;}
"||" { return token::OR;}
"!" { return token::NOT;}
"if" { return token::IF;}
"else" { return token::ELSE;}
"return" { return token::RETURN;}
"break" { return token::BREAK;}
"continue" { return token::CONTINUE;}
"while" { return token::WHILE;}
"function" { return token::FUNCTION;}
"++" { return token::PLUS;}
"--" { return token::MINUS;}

"0"|[1-9][0-9]* {	yylval->node = new CNUMBER(yytext);				
					return token::NUMBER; }

[a-zA-Z][a-zA-Z0-9_]* {	yylval->node = g_symbolTable.GetIdentifier(yytext);
						return token::IDENTIFIER; }
[ \n\r\t]+ ;

%%