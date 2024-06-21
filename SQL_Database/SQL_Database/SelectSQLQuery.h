#pragma once
#include "SQLQuery.h"
#include "Expression.h"

class SelectSQLQuery : public SQLQuery
{
public:
	SelectSQLQuery(Database& database, MyVector<MyString>&& cols, MyVector<MyString> tables, Expression* expression = nullptr);
	SQLResponse execute() override;

private:
	MyVector<MyString> cols;
	MyVector<MyString> tables;
	Expression* expression = nullptr;
};

