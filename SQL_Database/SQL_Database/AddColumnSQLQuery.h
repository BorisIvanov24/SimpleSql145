#pragma once
#include "AlterTableSQLQuery.h"

class AddColumnSQLQuery : public AlterTableSQLQuery
{
public:
	AddColumnSQLQuery(Database& db, MyString&& table, MyString&& colName, ColumnType type);
	SQLResponse execute() override;
private:
	MyString colName;
	ColumnType type;
};

