#pragma once
#include "Expression.h"

class ExpressionFactory
{
public:
	static Expression* makeExpression(const MyString& str);
};

