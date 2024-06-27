#pragma once
#include "SQLQuery.h"

class InnerJoinSQLQuery : public SQLQuery
{
public:
	InnerJoinSQLQuery(Database& db, MyVector<MyString>&& colNames, MyString&& table1,
		              MyString&& table2, MyString&& col1Expression, MyString&& col2Expression);
	SQLResponse execute() override;
	

private:
	MyVector<MyString> colNames;
	MyString table1;
	MyString table2;
	MyString col1Expression;
	MyString col2Expression;
};

