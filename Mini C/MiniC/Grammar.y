
%language "C++"


%{
#include "Grammar.tab.h"
#include "SymbolNodes.h"
extern int yylex(yy::parser::semantic_type *yylval);
%}
%code requires{				/*oti grafoume metaferete autousio sto panw meros tou Grammar.tab.h */
#include "STNode.h"
}
%union{
	STNode *node;
}

%start compileUnit			/* arxiko sumbolo grammatikhs */
%token <node> NUMBER IDENTIFIER														/* termatikwn stoixeiwn */
%token <node> IF ELSE RETURN WHILE PLUS MINUS BREAK CONTINUE FUNCTION
%type <node> expression compileUnit statements statement compound_statement			/*	mh termartika */
%type <node> if_statement while_statement function_definition formal_args actual_args 

%nonassoc ELSE

%right '='
%left OR
%left AND
%nonassoc L G LE GE EQ NE
%left '+' '-'
%left '*' '/' 
%nonassoc NOT

%%

compileUnit : statements { 
							g_root = $$ = new CCompileUnit();
							$$->AddChild($1);
						 }
			| compileUnit statement { 
										g_root = $$ = new CCompileUnit();
										$$->AddChild($1);
										$$->AddChild($2);		
									}
			| function_definition   { 
										g_root = $$ = new CCompileUnit();
										$$->AddChild($1);	
								    }
			| compileUnit function_definition { 
											g_root = $$ = new CCompileUnit();
													$$->AddChild($1);
													$$->AddChild($2);
											  }	
		;

function_definition : FUNCTION IDENTIFIER '(' formal_args ')' compound_statement
								{
									$$ = new CFunctionDefinition();
									((CIDENTIFIER*) $2)->m_root = $$;
									$$->AddChild($2); //0
									$$->AddChild($4); //1
									$$->AddChild($6); //2
									
								}

				 | FUNCTION IDENTIFIER '(' ')' compound_statement
								{
									$$ = new CFunctionDefinition();
									((CIDENTIFIER*) $2)->m_root = $$;
									$$->AddChild($2);
									$$->AddChild($5);
								}
				;

formal_args : IDENTIFIER { 
							$$ = new CFormalArgs();
							$$->AddChild($1);
						 }

					| formal_args ',' IDENTIFIER { 
													$$ = new CFormalArgs();
													$$->AddChild($1);
													$$->AddChild($3);
												 }
				;


statements : statement			 { 
									$$ = new CStatements();
									$$->AddChild($1);
								 }
		|	statements statement {
									$$ = new CStatements();
									$$->AddChild($1);
									$$->AddChild($2);
								 }
		;

statement : expression ';'		 { 
									$$ = new CStatement();
									$$->AddChild($1);
								 }	
			| compound_statement
		 
			| if_statement { $$ = $1;}

			| while_statement { $$ = $1; }
		
			| BREAK ';' { 
							$$ = new CBreakStatement();
						}

			| CONTINUE ';' { 
								$$ = new CContinueStatement();
						   }
						
			| RETURN expression ';' {  
										$$ = new CRETURN();
										$$->AddChild($2);	
									}						 
			| ';'				{ 
									$$ = new CStatement();
								}
		;


if_statement : IF '(' expression ')' statement { 
													$$ = new CIfStatement();
													$$->AddChild($3);
													$$->AddChild($5);
											  }
			| IF '(' expression ')' statement  ELSE statement { 
																$$ = new CIfStatement();
																$$->AddChild($3);
																$$->AddChild($5);
																$$->AddChild($7);
															}
			;
while_statement : WHILE '(' expression ')' compound_statement { 
																$$ = new CWhileStatement();
																$$->AddChild($3);
																$$->AddChild($5);
															 }
				|  WHILE '(' expression ')' statement { 
														$$ = new CWhileStatement();
													    $$->AddChild($3);
													    $$->AddChild($5);
													  }
			;

compound_statement	: '{' '}' { $$ = new CCompoundStatement(); }
			  
			  | '{' statements '}' { 
										$$ = new CCompoundStatement();
										$$->AddChild($2);
								   }
			  ;



expression : NUMBER		{ $$ = $1; }	
		| IDENTIFIER	{ $$ = $1; }

		| IDENTIFIER '(' ')' { 
								$$ = new CFunctionCallExpression(); 
								$$->AddChild($1);
							 }

		| IDENTIFIER '(' actual_args  ')' { 
											$$ = new CFunctionCallExpression(); 
											$$->AddChild($1);
											$$->AddChild($3);
										  } 

		| IDENTIFIER PLUS { 
							$$ = new CPLUS();
							$$->AddChild($1);
						    $$->AddChild($2);
						  }
		| IDENTIFIER MINUS { 
							$$ = new CMINUS();
							$$->AddChild($1);
						    $$->AddChild($2);
						  }

		| IDENTIFIER '=' expression {	
										$$ = new CAssigment();
										$$->AddChild($1);
										$$->AddChild($3);
									}
		| expression '+' expression	{ 
										$$ = new CAddition();
										$$->AddChild($1);
										$$->AddChild($3);
									}
		| expression '-' expression { 
										$$ = new CSubtraction();
										$$->AddChild($1);
										$$->AddChild($3);
									}
		| expression '*' expression { 
										$$ = new CMultiplication();
										$$->AddChild($1);
										$$->AddChild($3);
									}
		| expression '/' expression { 
										$$ = new CDivision();
										$$->AddChild($1);
										$$->AddChild($3);
									}
		| '(' expression ')'	{ $$ = $2; }

		| expression L expression { 
									$$ = new CLess();
									$$->AddChild($1);	
									$$->AddChild($3);
								  }

		| expression G expression   { 
									  $$ = new CGreater();
									  $$->AddChild($1);	
									  $$->AddChild($3);
								    }

		| expression LE expression  { 
									  $$ = new CLessEqual();
									  $$->AddChild($1);	
									  $$->AddChild($3);
									}

		| expression GE expression  { 
									  $$ = new CGreaterEqual();
									  $$->AddChild($1);	
									  $$->AddChild($3);
									}

		| expression EQ expression  { 
									  $$ = new CEqual();
									  $$->AddChild($1);	
									  $$->AddChild($3);
								    }

		| expression NE expression  { 
									  $$ = new CNotEqual();
									  $$->AddChild($1);	
									  $$->AddChild($3);
								    }

		| expression AND expression { 
									  $$ = new CAnd();
									  $$->AddChild($1);	
									  $$->AddChild($3);	
									 }
									  
		| expression OR expression {  
									  $$ = new COr();
									  $$->AddChild($1);	
									  $$->AddChild($3);	
								   }

		| NOT expression { 
						   $$ = new CNot();
						   $$->AddChild($2);
						  }
		;

actual_args  : expression { 
							$$ = new CActualArgs();
							$$->AddChild($1);
						  }
			
		| actual_args ',' expression { 
									   $$ = new CActualArgs();
									   $$->AddChild($1);
									   $$->AddChild($3);
									  }
		;



%%



namespace yy{
	void parser::error (const location_type& loc, const std::string& msg){
		std::cerr << "error at" << loc << ": " << msg <<std::endl;
	}
	

}