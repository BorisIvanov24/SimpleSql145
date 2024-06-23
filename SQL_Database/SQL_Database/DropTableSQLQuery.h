#pragma once
#include "SQLQuery.h"

class DropTableSQLQuery : public SQLQuery
{
public:
	DropTableSQLQuery(Database& db, MyString&& table);
	SQLResponse execute() override;

private:
	MyString table;
};

