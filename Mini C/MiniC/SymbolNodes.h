#pragma once
#include "STNode.h"

class CCompileUnit : public STNode {
public:
	CCompileUnit();
	virtual ~CCompileUnit();
	void Visit_SyntaxTreePrinter(ofstream* dotFile, STNode* parent) override;
};

class CStatements : public STNode {
public:
	CStatements();
	virtual ~CStatements();
};

class CStatement : public STNode {
public:
	CStatement();
	virtual ~CStatement();

	int Visit_Eval() override;
};

class CAddition : public STNode {
public:
	CAddition();
	virtual ~CAddition();
	int Visit_Eval() override;
};

class CSubtraction : public STNode {
public:
	CSubtraction();
	virtual ~CSubtraction();
	int Visit_Eval() override;
};

class CMultiplication : public STNode {
public:
	CMultiplication();
	virtual ~CMultiplication();
	int Visit_Eval() override;
};

class CDivision : public STNode {
public:
	CDivision();
	virtual ~CDivision();
	int Visit_Eval() override;
};

class CNUMBER : public STNode {
public:
	int m_number;

	CNUMBER(char* text);
	virtual ~CNUMBER();
	int Visit_Eval() override;
};

class CIDENTIFIER : public STNode {
public:
	int m_number;
	string m_name;
	char* m_name_c;
	char* m_name_ch;
	STNode* m_root;

	CIDENTIFIER(char* text);
	virtual ~CIDENTIFIER();

	int Visit_Eval() override;

};

class CAssigment : public STNode {
public:
	CAssigment();
	virtual ~CAssigment();

	int Visit_Eval() override;
};


class CAnd : public STNode {
public:
	CAnd();
	virtual ~CAnd();
	int Visit_Eval() override;
};

class COr : public STNode {
public:
	COr();
	virtual ~COr();
	int Visit_Eval() override;
};

class CNot : public STNode {
public:
	CNot();
	virtual ~CNot();
	int Visit_Eval() override;
};

class CLess : public STNode {
public:
	CLess();
	virtual ~CLess();
	int Visit_Eval() override;
};

class CGreater : public STNode {
public:
	CGreater();
	virtual ~CGreater();
	int Visit_Eval() override;
};

class CLessEqual : public STNode {
public:
	CLessEqual();
	virtual ~CLessEqual();
	int Visit_Eval() override;
};

class CGreaterEqual : public STNode {
public:
	CGreaterEqual();
	virtual ~CGreaterEqual();
	int Visit_Eval() override;
};

class CEqual : public STNode {
public:
	CEqual();
	virtual ~CEqual();
	int Visit_Eval() override;
};

class CNotEqual : public STNode {
public:
	CNotEqual();
	virtual ~CNotEqual();
	int Visit_Eval() override;
};


class CIfStatement : public STNode {
public:
	CIfStatement();
	virtual ~CIfStatement();
	int Visit_Eval() override;
};

class CCompoundStatement : public STNode {
public:
	CCompoundStatement();
	virtual ~CCompoundStatement();
};

class CRETURN : public STNode {
public:
	CRETURN();
	virtual ~CRETURN();
	int Visit_Eval() override;
};

class CWhileStatement : public STNode {
public:
	CWhileStatement();
	virtual ~CWhileStatement();
	int Visit_Eval() override;
};

class CPLUS : public STNode {
public:
	CPLUS();
	virtual ~CPLUS();
	int Visit_Eval() override;
};

class CMINUS : public STNode {
public:
	CMINUS();
	virtual ~CMINUS();
	int Visit_Eval() override;
};

class CBreakStatement : public STNode {
public:
	CBreakStatement();
	virtual ~CBreakStatement();
	int Visit_Eval() override;
};

class CContinueStatement : public STNode {
public:
	CContinueStatement();
	virtual ~CContinueStatement();
	int Visit_Eval() override;
};

class CFunctionDefinition : public STNode {
public:
	CFunctionDefinition();
	virtual ~CFunctionDefinition();
};

class CFormalArgs : public STNode {
public:
	CFormalArgs();
	virtual ~CFormalArgs();
};


class CFunctionCallExpression : public STNode {
public:
	CFunctionCallExpression();
	virtual ~CFunctionCallExpression();
	int Visit_Eval() override;
};

class CActualArgs : public STNode {
public:
	CActualArgs();
	virtual ~CActualArgs();
};

int GetFormalArguments(CFormalArgs* root, list<STNode*>* formal_args);
int GetActualArguments(CActualArgs* root, list<STNode*>* actual_args);