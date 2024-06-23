#include "Table.h"
#include "SimpleTablePrinter.h"

Table::Table(const Table& other)
{
	copyFrom(other);
}

Table::Table(Table&& other) noexcept
{
	moveFrom(std::move(other));
}

Table& Table::operator=(const Table& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Table& Table::operator=(Table&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Table::~Table()
{
	free();
}

Table::Table(const MyString& name)
{
	this->name = name;
}

Table::Table(MyString&& name)
{
	this->name = std::move(name);
}

const MyString& Table::getName() const
{
	return name;
}

size_t Table::getColumnsCount() const
{
	return size;
}

ColumnType Table::getColumnType(unsigned index) const
{
	return columns[index]->getColumnType();
}

void Table::addColumn(Column* ptr)
{
	resize();
	columns[size++] = ptr;

	if (ptr->getSize() > rowsCount)
		rowsCount = ptr->getSize();

	fillEmpty();

	
}

void Table::removeColumn(unsigned index)
{
	if (index >= size)
		throw std::invalid_argument("Out of range!");

	Column** temp = new Column* [size - 1];
	unsigned currentIndex = 0;

	for (int i = 0; i < size; i++)
	{
		if (i == index)
			continue;

		temp[currentIndex] = columns[i];
		currentIndex++;
	}

	delete[] columns;

	size--;
	columns = temp;
}

void Table::removeRow(unsigned index)
{

	for (int i = 0; i < size; i++)
	{
		columns[i]->removeValue(index);
	}
	
	rowsCount--;

}

const MyString& Table::getColumnName(unsigned index) const
{
	return (columns[index]->getName());
}

void Table::saveToBinaryFile(const MyString& fileName) const
{
	std::ofstream ofs(fileName.c_str(), std::ios::binary | std::ios::out);

	if (!ofs.is_open())
		throw std::invalid_argument("Couldn't open file");

	name.saveToBinaryFile(ofs);

	ofs.write(reinterpret_cast<const char*>(&size), sizeof(size_t));
	ofs.write(reinterpret_cast<const char*>(&rowsCount), sizeof(size_t));

	for (int i = 0; i < size; i++)
	{
		columns[i]->saveToBinaryFile(ofs);
	}
}

void Table::loadFromBinaryFile(const MyString& fileName)
{
	free();

	std::ifstream ifs(fileName.c_str(), std::ios::binary | std::ios::in);

	if (!ifs.is_open())
		throw std::invalid_argument("Couldn't open file");

	name.loadFromBinaryFile(ifs);

	ifs.read(reinterpret_cast<char*>(&size), sizeof(size_t));
	ifs.read(reinterpret_cast<char*>(&rowsCount), sizeof(size_t));

	if (size != 0)
	columns = new Column* [size];

	for (int i = 0; i < size; i++)
	{
		columns[i] = new Column();
		columns[i]->loadFromBinaryFile(ifs);
	}
}

const OptionalString& Table::getValue(unsigned rowIndex, unsigned colIndex) const
{
	if (rowIndex >= rowsCount || colIndex >= size)
		throw std::invalid_argument("Out of range!");

	return columns[colIndex]->getValue(rowIndex);
}

void Table::setValue(OptionalString&& value, unsigned rowIndex, unsigned colIndex)
{
	/*if (rowIndex >= rowsCount || colIndex >= size)
		throw std::invalid_argument("Out of range!");*/

	if (rowIndex >= this->rowsCount)
		rowsCount = rowIndex + 1;

	columns[colIndex]->setValue(std::move(value), rowIndex);

	fillEmpty();
}

void Table::addValue(const OptionalString& value, unsigned columnIndex)
{
	columns[columnIndex]->addValue(value);
	rowsCount++;
}

void Table::setColumnName(unsigned colIndex, MyString&& newColName)
{
	columns[colIndex]->setName(std::move(newColName));
}

size_t Table::getRowsCount() const
{
	return rowsCount;
}

size_t Table::getColsCount() const
{
	return size;
}

void Table::copyFrom(const Table& other)
{
	name = other.name;

	columns = new Column* [other.size];

	for (int i = 0; i < other.size; i++)
	{
		columns[i] = new Column(*(other.columns[i]));
	}

	size = other.size;
	rowsCount = other.rowsCount;
}

void Table::moveFrom(Table&& other)
{
	name = std::move(other.name);

	columns = other.columns;
	other.columns = nullptr;

	size = other.size;
	rowsCount = other.rowsCount;
}

void Table::free()
{
	for (int i = 0; i < size; i++)
	{
		delete columns[i];
	}

	delete[] columns;
}

void Table::resize()
{
	Column** temp = new Column* [size + 1];

	for (int i = 0; i < size; i++)
	{
		temp[i] = columns[i];
	}

	delete[] columns;
	columns = temp;
}

void Table::fillEmpty()
{
	for (int i = 0; i < size; i++)
	{
		while (columns[i]->getSize() < rowsCount)
		{
			columns[i]->addNullValue();
		}
	}
}
