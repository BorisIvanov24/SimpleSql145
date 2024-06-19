#pragma once
#include "SQLQuery.h"

class SQLQueryFactory
{
public:
	static SQLQuery* makeQuery(const MyString& str, Database& db);
};

