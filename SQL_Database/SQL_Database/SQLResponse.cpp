#include "SQLResponse.h"

SQLResponse::SQLResponse(const MyString& message)
{
	this->message = message;
}

SQLResponse::SQLResponse(MyString&& message)
{
	this->message = std::move(message);
}

const MyString& SQLResponse::getMessage() const
{
	return message;
}
