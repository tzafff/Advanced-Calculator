#include "STNode.h"
STNode* g_root = nullptr;
int STNode::m_serialCounter = 0;
int STNode::m_returnedValue = 0;
bool STNode::m_breakVisit = false;
bool STNode::m_continueVisit = false;

const char* g_nodeTypeLabels[] = {				/* alfarithmhtika for type codes */
	"COMPILEUNIT", "NT_COMPOUND_STATEMENT", "STATEMENTS","STATEMENT",
	"NUMBER", "IDENTIFIER", "ADDITION", "SUBTRACTION",
	"MULTIPLICATION","DIVISION","ASSIGNMENT","AND","OR","NOT","LESS","GREATER","LESSEQUAL","GREATEREQUAL","EQUAL","NOTEQUAL","IF","ELSE",
	"RETURN","WHILE","PLUS","MINUS","BREAK","CONTINUE","FUNCTION DEFINITION","FORMAL ARGS",
	"ACTUAL ARGS","FUNCTION CALL"
};

STNode::STNode(NodeType type) {
	m_nodeType = type;
	m_serial = m_serialCounter++;
	m_children = new list<STNode*>;
	m_parents = new list<STNode*>;
	m_graphvizLabel = _strdup(g_nodeTypeLabels[m_nodeType]);
	m_graphvizLabel.append("_" + std::to_string(m_serial));
}

STNode::~STNode() {
	list<STNode*>::iterator it;
	for (it = m_children->begin(); it != m_children->end(); it++) {
		delete* it;
	}
	delete m_children;
	delete m_parents;
}

void STNode::AddChild(STNode* node) {
	m_children->push_back(node);
	node->m_parents->push_back(this);
}

STNode* STNode::GetChild(int index) {
	list<STNode*>::iterator it = m_children->begin();
	advance(it, index);
	return *it;
}

STNode* STNode::GetParent(int index) {
	list<STNode*>::iterator it = m_parents->begin();
	advance(it, index);
	return *it;
}

void STNode::Visit_SyntaxTreePrinter(ofstream* dotFile, STNode* parent) {
	list<STNode*>::iterator it;

	(*dotFile) << "\"" << parent->GetGraphvizLabel() << "\"->\"" << GetGraphvizLabel() << "\";\n";

	for (it = m_children->begin(); it != m_children->end(); it++) {
		(*it)->Visit_SyntaxTreePrinter(dotFile, this);
	}
}


int STNode::Visit_Eval() {
	list<STNode*>::iterator it;
	for (it = m_children->begin(); it != m_children->end(); it++) {
		(*it)->Visit_Eval();
	}
	return 0;
}

NodeType STNode::GetNodeType() {
	return m_nodeType;
}

string STNode::GetGraphvizLabel() {
	return m_graphvizLabel;
}