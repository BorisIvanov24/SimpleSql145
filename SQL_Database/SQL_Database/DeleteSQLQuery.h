#pragma once
#include "SQLQuery.h"
#include "Expression.h"

class DeleteSQLQuery : public SQLQuery
{
public:
	DeleteSQLQuery(Database& db, MyString&& table, Expression* exp);
	SQLResponse execute() override;
	~DeleteSQLQuery();

private:
	MyString table;
	Expression* exp = nullptr;
};

