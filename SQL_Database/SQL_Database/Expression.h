#pragma once
#include "Table.h"

class Expression
{
public:
	virtual bool evaluate(const Table& table, unsigned rowIndex) const = 0;
	virtual ~Expression() = default;
};

