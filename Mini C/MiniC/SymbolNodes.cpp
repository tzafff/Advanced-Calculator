#pragma once
#include "SymbolNodes.h"
#include <iostream>
#include "SymbolTable.h"

CCompileUnit::CCompileUnit(): STNode(NodeType::NT_COMPILEUNIT) {}
CCompileUnit::~CCompileUnit() {}

CStatements::CStatements() : STNode(NodeType::NT_STATEMENTS) {}
CStatements::~CStatements() {}

CStatement::CStatement() : STNode(NodeType::NT_STATEMENT) {}
CStatement::~CStatement() {}

CAddition::CAddition() : STNode(NodeType::NT_EXPRESSION_ADDITION) {}
CAddition::~CAddition() {}

CSubtraction::CSubtraction() : STNode(NodeType::NT_EXPRESSION_SUBTRACTION) {}
CSubtraction::~CSubtraction() {}

CMultiplication::CMultiplication() : STNode(NodeType::NT_EXPRESSION_MULTIPLICATION) {}
CMultiplication::~CMultiplication() {}

CDivision::CDivision() : STNode(NodeType::NT_EXPRESSION_DIVISION) {}
CDivision::~CDivision() {}

CNUMBER::CNUMBER(char * text) : STNode(NodeType::NT_EXPRESSION_NUMBER) {
	m_number = atoi(text);
	m_graphvizLabel.append("_" + std::to_string(m_number));
}
CNUMBER::~CNUMBER() {}


void CCompileUnit::Visit_SyntaxTreePrinter(ofstream* dotFile, STNode* parent) {
	list<STNode*>::iterator it;

	if (parent == nullptr) {
		(*dotFile) << "digraph G{ \n";
		for (it = m_children->begin(); it != m_children->end(); it++) {
			(*it)->Visit_SyntaxTreePrinter(dotFile, this);
		}

		(*dotFile) << "}";
		dotFile->close();

	}
	else {
		STNode::Visit_SyntaxTreePrinter(dotFile, this);
	}

}

int CNUMBER::Visit_Eval() {
	return m_number;
}

int CAddition::Visit_Eval() {
	list<STNode*>::iterator it = m_children->begin();
	int result = (*it)->Visit_Eval();
	advance(it, 1);
	result += (*it)->Visit_Eval();
	return result;
}
int CSubtraction::Visit_Eval() {
	list<STNode*>::iterator it = m_children->begin();
	int result = (*it)->Visit_Eval();
	advance(it, 1);
	result -= (*it)->Visit_Eval();
	return result;
}
int CMultiplication::Visit_Eval() {
	list<STNode*>::iterator it = m_children->begin();
	int result = (*it)->Visit_Eval();
	advance(it, 1);
	result *= (*it)->Visit_Eval();
	return result;
}
int CDivision::Visit_Eval() {
	list<STNode*>::iterator it = m_children->begin();
	int result = (*it)->Visit_Eval();
	advance(it, 1);
	result /= (*it)->Visit_Eval();
	return result;
}

int CStatement::Visit_Eval() {
	list<STNode*>::iterator it;
	if (m_children->size() != 0) {
		it = m_children->begin();
		cout << "Result : " << (*it)->Visit_Eval() << endl;
	}
	return 0;
}


CIDENTIFIER::CIDENTIFIER(char*text) : STNode(NodeType::NT_EXPRESSION_IDENTIFIER) {
	m_name = (string)text;
	m_number = 0;
	m_name_ch = text;
	m_name_c = new char[m_name.length() + 1];
	strcpy_s(m_name_c, m_name.length() + 1, text);
	m_root = nullptr;
	m_graphvizLabel.append("_" + m_name);
}

CIDENTIFIER::~CIDENTIFIER() {}
int CIDENTIFIER::Visit_Eval() {
	return m_number;
}

CAssigment::CAssigment() :STNode(NodeType::NT_EXPRESSION_ASSIGNMENT) {}

CAssigment::~CAssigment() {}

int CAssigment::Visit_Eval() {
	list<STNode*>::iterator it = m_children->begin();
	CIDENTIFIER* id = dynamic_cast<CIDENTIFIER*>(*it);
	advance(it, 1);
	id->m_number = (*it)->Visit_Eval();
	cout << id->m_name << "=" << id->m_number << endl;
	return id->m_number;
}


CAnd::CAnd() : STNode(NodeType::NT_EXPRESSION_AND) {}
CAnd::~CAnd() {};

int CAnd::Visit_Eval() {
	list<STNode*>::iterator it = m_children->begin();
	int result1 = (*it)->Visit_Eval();
	advance(it, 1);
	int result2 = (*it)->Visit_Eval();

	return (result1 && result2);
}

COr::COr() : STNode(NodeType::NT_EXPRESSION_OR) {}
COr::~COr() {};

int COr::Visit_Eval() {
	list<STNode*>::iterator it = m_children->begin();
	int result1 = (*it)->Visit_Eval();
	advance(it, 1);
	int result2 = (*it)->Visit_Eval();
	return (result1 || result2);
}

CNot::CNot() : STNode(NodeType::NT_EXPRESSION_NOT) {}
CNot::~CNot() {};

int CNot::Visit_Eval() {
	list<STNode*>::iterator it = m_children->begin();
	int result = (*it)->Visit_Eval();
	return !result;
}

CLess::CLess() : STNode(NodeType::NT_EXPRESSION_LESS) {}
CLess::~CLess() {};

int CLess::Visit_Eval() {
	list<STNode*>::iterator it = m_children->begin();
	int result1 = (*it)->Visit_Eval();
	advance(it, 1);
	int result2 = (*it)->Visit_Eval();
	return result1 < result2;
}

CGreater::CGreater() : STNode(NodeType::NT_EXPRESSION_GREATER) {}
CGreater::~CGreater() {};

int CGreater::Visit_Eval() {
	list<STNode*>::iterator it = m_children->begin();
	int result1 = (*it)->Visit_Eval();
	advance(it, 1);
	int result2 = (*it)->Visit_Eval();
	return result1 > result2;
}

CLessEqual::CLessEqual() : STNode(NodeType::NT_EXPRESSION_LESSEQUAL) {}
CLessEqual::~CLessEqual() {};

int CLessEqual::Visit_Eval() {
	list<STNode*>::iterator it = m_children->begin();
	int result1 = (*it)->Visit_Eval();
	advance(it, 1);
	int result2 = (*it)->Visit_Eval();
	return result1 <= result2;
}

CGreaterEqual::CGreaterEqual() : STNode(NodeType::NT_EXPRESSION_GREATEREQUAL) {}
CGreaterEqual::~CGreaterEqual() {};

int CGreaterEqual::Visit_Eval() {
	list<STNode*>::iterator it = m_children->begin();
	int result1 = (*it)->Visit_Eval();
	advance(it, 1);
	int result2 = (*it)->Visit_Eval();
	return result1 >= result2;
}

CEqual::CEqual() : STNode(NodeType::NT_EXPRESSION_EQUAL) {}
CEqual::~CEqual() {};

int CEqual::Visit_Eval() {
	list<STNode*>::iterator it = m_children->begin();
	int result1 = (*it)->Visit_Eval();
	advance(it, 1);
	int result2 = (*it)->Visit_Eval();
	return result1 == result2;
}

CNotEqual::CNotEqual() : STNode(NodeType::NT_EXPRESSION_NOTEQUAL) {}
CNotEqual::~CNotEqual() {};

int CNotEqual::Visit_Eval() {
	list<STNode*>::iterator it = m_children->begin();
	int result1 = (*it)->Visit_Eval();
	advance(it, 1);
	int result2 = (*it)->Visit_Eval();
	return result1 != result2;
}

CIfStatement::CIfStatement() : STNode(NodeType::NT_STATEMENT_IF) {}
CIfStatement::~CIfStatement() {}

int CIfStatement::Visit_Eval() {
	STNode* condition = GetChild(0);
	STNode* true_body = GetChild(1);
	STNode* false_body;
	if (condition->Visit_Eval()) {
		true_body->Visit_Eval();
	}
	else if (m_children->size() > 2) {
		false_body = GetChild(2);
		false_body->Visit_Eval();
	}

	return 0;
}

CCompoundStatement::CCompoundStatement() : STNode(NodeType::NT_COMPOUND_STATEMENT) {}
CCompoundStatement::~CCompoundStatement() {}

CRETURN::CRETURN() : STNode(NodeType::NT_STATEMENT_RETURN) {}
CRETURN::~CRETURN() {}

int CRETURN::Visit_Eval() {
	STNode* tmp = GetChild(0);
	m_returnedValue = tmp->Visit_Eval();
	return m_returnedValue;
}

CWhileStatement::CWhileStatement() : STNode(NodeType::NT_STATEMENT_WHILE) {}
CWhileStatement::~CWhileStatement() {}

int CWhileStatement::Visit_Eval() {
	STNode* condition = GetChild(0);
	STNode* body = GetChild(1);
	while (condition->Visit_Eval()) {
		body->Visit_Eval();
		if (m_breakVisit)
			break;

	}
	m_breakVisit = false;
	return 0;
}

CPLUS::CPLUS() : STNode(NodeType::NT_STATEMENT_PLUS) {}
CPLUS::~CPLUS() {}

int CPLUS::Visit_Eval() {
	STNode* it = GetChild(0);
	CIDENTIFIER* id = dynamic_cast<CIDENTIFIER*>(it);
	id->m_number = (it)->Visit_Eval() + 1;
	cout << id->m_name << "=" << id->m_number << endl;
	return id->m_number;

}

CMINUS::CMINUS() : STNode(NodeType::NT_STATEMENT_MINUS) {}
CMINUS::~CMINUS() {}

int CMINUS::Visit_Eval() {
	STNode* it = GetChild(0);
	CIDENTIFIER* id = dynamic_cast<CIDENTIFIER*>(it);
	id->m_number = (it)->Visit_Eval() - 1;
	cout << id->m_name << "=" << id->m_number << endl;
	return id->m_number;

}

CBreakStatement::CBreakStatement() : STNode(NodeType::NT_STATEMENT_BREAK) {}
CBreakStatement::~CBreakStatement() {}

int CBreakStatement::Visit_Eval() {
	m_breakVisit = true;
	return 0;
}

CContinueStatement::CContinueStatement() : STNode(NodeType::NT_STATEMENT_CONTINUE) {}
CContinueStatement::~CContinueStatement() {}

int CContinueStatement::Visit_Eval() {
	m_continueVisit = true;
	return 0;
}


CFunctionDefinition::CFunctionDefinition() :STNode(NodeType::NT_FUNCTION_DEFINITION) {}
CFunctionDefinition::~CFunctionDefinition() {}

CFormalArgs::CFormalArgs() :STNode(NodeType::NT_FORMAL_ARGS) {}
CFormalArgs::~CFormalArgs() {}

CActualArgs::CActualArgs() : STNode(NodeType::NT_ACTUAL_ARGS) {}
CActualArgs::~CActualArgs() {}

CFunctionCallExpression::CFunctionCallExpression() :STNode(NodeType::NT_FUNCTION_CALL_EXPRESSION) {}
CFunctionCallExpression::~CFunctionCallExpression() {}

int CFunctionCallExpression::Visit_Eval() {
	char* f_name = ((CIDENTIFIER*)GetChild(0))->m_name_c;
	CIDENTIFIER* f_id = (CIDENTIFIER*)g_symbolTable.GetIdentifier(f_name);

	CFunctionDefinition* fun_def = (CFunctionDefinition*)f_id->m_root;

	//2. store actuall args in a list
	CActualArgs* f_a_args = (CActualArgs*)GetChild(1);
	list<STNode*>* actual_args = new list<STNode*>;
	GetActualArguments(f_a_args, actual_args);

	//3. store formal args in a list
	CFormalArgs* f_f_args = (CFormalArgs*)fun_def->GetChild(1);
	list<STNode*>* formal_args = new list<STNode*>;
	GetFormalArguments(f_f_args, formal_args);

	list<STNode*>::iterator formal_it;
	list<STNode*>::iterator actual_it;
	for (formal_it = formal_args->begin(), actual_it = actual_args->begin();
		formal_it != formal_args->end(); formal_it++, actual_it++) {

		dynamic_cast<CIDENTIFIER*>(*formal_it)->m_number = (*actual_it)->Visit_Eval();
	}

	fun_def->GetChild(2)->Visit_Eval();

	return STNode::m_returnedValue;

}

int GetActualArguments(CActualArgs* root, list<STNode*>* actual_args) {
	if (dynamic_cast<CActualArgs*>(root->GetChild(0)) != nullptr) {
		CActualArgs* next = dynamic_cast<CActualArgs*>(root->GetChild(0));
		GetActualArguments(next, actual_args);
		actual_args->push_back(root->GetChild(1));
	}
	else {
		actual_args->push_back(root->GetChild(0));
	}
	return actual_args->size();
}

int GetFormalArguments(CFormalArgs* root, list<STNode*>* formal_args) {
	if (dynamic_cast<CFormalArgs*>(root->GetChild(0)) != nullptr) {
		CFormalArgs* next = dynamic_cast<CFormalArgs*>(root->GetChild(0));
		GetFormalArguments(next, formal_args);
		formal_args->push_back(root->GetChild(1));
	}
	else {
		formal_args->push_back(root->GetChild(0));
	}
	return formal_args->size();
}






