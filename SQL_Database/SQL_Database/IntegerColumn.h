#pragma once
#include "Column.h"
#include "Cell.hpp"
#include "MyVector.hpp"

class IntegerColumn : public Column
{
public:

private:
	MyVector<Cell<int>> rows;
};

