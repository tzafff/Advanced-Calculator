#pragma once
#include <list>
#include <string>
#include <fstream>

using namespace std;

typedef enum nodeType {									/* type codes */
	NT_COMPILEUNIT, NT_COMPOUND_STATEMENT,NT_STATEMENTS, NT_STATEMENT,
	NT_EXPRESSION_NUMBER,NT_EXPRESSION_IDENTIFIER,
	NT_EXPRESSION_ADDITION, NT_EXPRESSION_SUBTRACTION,
	NT_EXPRESSION_MULTIPLICATION, NT_EXPRESSION_DIVISION,
	NT_EXPRESSION_ASSIGNMENT, NT_EXPRESSION_AND, NT_EXPRESSION_OR, NT_EXPRESSION_NOT, NT_EXPRESSION_LESS,
	NT_EXPRESSION_GREATER, NT_EXPRESSION_LESSEQUAL, NT_EXPRESSION_GREATEREQUAL,
	NT_EXPRESSION_EQUAL, NT_EXPRESSION_NOTEQUAL, NT_STATEMENT_IF, NT_STATEMENT_ELSE,
	NT_STATEMENT_RETURN, NT_STATEMENT_WHILE, NT_STATEMENT_PLUS, NT_STATEMENT_MINUS,
	NT_STATEMENT_BREAK, NT_STATEMENT_CONTINUE, NT_FUNCTION_DEFINITION, NT_FORMAL_ARGS,
	NT_ACTUAL_ARGS, NT_FUNCTION_CALL_EXPRESSION
}NodeType;


class STNode {
public:							/* methods */

	STNode(NodeType type);
	virtual ~STNode();

	NodeType GetNodeType();
	string GetGraphvizLabel();
	STNode *GetChild(int index);
	STNode *GetParent(int index = 0);

	void AddChild(STNode* node);

	virtual void Visit_SyntaxTreePrinter(ofstream* dotFile, STNode* parent);
	virtual int Visit_Eval();

protected:					/* pedia  */
	//	type of node
	NodeType m_nodeType;
	// label of node in the graphviz generated file
	string m_graphvizLabel;
	// serial number of the node
	int m_serial;
	// serial counter
	static int m_serialCounter;
	// children nodes list
	list<STNode*>* m_children;
	// parent nodes list
	list<STNode*>* m_parents;


	static int m_returnedValue;
	static bool m_breakVisit;
	static bool m_continueVisit;

};

extern STNode* g_root;