#pragma once
#include "SQLQuery.h"

class InsertIntoSQLQuery : public SQLQuery
{
public:
	InsertIntoSQLQuery(Database& database, MyString&& tableName, MyVector<MyString>&& cols,
					   MyVector<MyVector<OptionalString>>&& values);
					  
	SQLResponse execute() override;

	InsertIntoSQLQuery(const InsertIntoSQLQuery& other) = delete;
	InsertIntoSQLQuery& operator=(const InsertIntoSQLQuery& other) = delete;

private:
	MyString tableName;
	MyVector<MyString> cols;
	MyVector<MyVector<OptionalString>> values;
};

