#pragma once
#include "SQLQuery.h"

class AlterTableSQLQuery : public SQLQuery
{
public:
	AlterTableSQLQuery(Database& db, MyString&& table);
	SQLResponse execute() override = 0;
protected:
	MyString table;
};

