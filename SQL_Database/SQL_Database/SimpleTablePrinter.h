#pragma once
#include "TablePrinter.h"

class SimpleTablePrinter : public TablePrinter
{
public:
	static SimpleTablePrinter& getInstance();
	void print(const Table& table) const override;
};

