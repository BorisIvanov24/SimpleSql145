#pragma once
#include "MyString.h"

class SQLResponse
{
public:
	SQLResponse() = default;
	SQLResponse(const MyString& message);
	SQLResponse(MyString&& message);

	const MyString& getMessage() const;
private:
	MyString message;
};

