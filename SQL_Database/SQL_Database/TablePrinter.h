#pragma once
#include "Table.h"

class TablePrinter
{
public:
	virtual void print(const Table& table) const = 0;
	virtual ~TablePrinter() = default;
};

 