#pragma once
#include "AlterTableSQLQuery.h"

class RenameColumnSQLQuery : public AlterTableSQLQuery
{
public:
	RenameColumnSQLQuery(Database& db, MyString&& table, MyString&& colName, MyString&& newColName);
	SQLResponse execute() override;

private:
	MyString colName;
	MyString newColName;
};

