#pragma once
#include <map>
#include <string>
#include "SymbolNodes.h"

using namespace std;
class STNode;
class SymbolTable {
public:
	map<string, STNode *> m_symbolTable;

	STNode* GetIdentifier(char* name);
};

extern SymbolTable g_symbolTable;