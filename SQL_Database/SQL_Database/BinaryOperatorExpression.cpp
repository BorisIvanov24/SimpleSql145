#include "BinaryOperatorExpression.h"

BinaryOperatorExpression::BinaryOperatorExpression(MyString&& left, MyString&& right)
{
	this->left = std::move(left);
	this->right = std::move(right);
}
