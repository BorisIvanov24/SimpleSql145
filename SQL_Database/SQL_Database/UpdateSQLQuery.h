#pragma once
#include "Expression.h"
#include "SQLQuery.h"

class UpdateSQLQuery : public SQLQuery
{
public:
	UpdateSQLQuery(Database& db, MyString&& table, MyString&& colName,
				   MyString&& value, Expression* exp);
	SQLResponse execute() override;
	~UpdateSQLQuery();
private:
	MyString table;
	MyString colName;
	MyString value;
	Expression* exp;
};

