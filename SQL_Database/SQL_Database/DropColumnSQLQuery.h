#pragma once
#include "AlterTableSQLQuery.h"

class DropColumnSQLQuery : public AlterTableSQLQuery
{
public:
	DropColumnSQLQuery(Database& db, MyString&& table, MyString&& colName);
	SQLResponse execute() override;
	
private:
	MyString colName;
};

