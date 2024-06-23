#pragma once
#include "Table.h"

class TablePrinter
{
public:
	virtual void print(const Table& table, std::ostream& os) const = 0;
	virtual ~TablePrinter() = default;
};

 