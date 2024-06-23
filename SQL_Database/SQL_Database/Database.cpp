#include "Database.h"
#include "SQLQueryFactory.h"
#include "SimpleTablePrinter.h"

Database::Database()
{
	tables = new Table * [8];
	size = 0;
	capacity = 8;
}

Database::Database(const MyString& filePath)
{
	this->filePath = filePath;
	loadFromBinaryFile();
}

Database::Database(const Database& other)
{
	copyFrom(other);
}

Database::Database(Database&& other) noexcept
{
	moveFrom(std::move(other));
}

Database& Database::operator=(const Database& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Database& Database::operator=(Database&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Database::~Database()
{
	saveToBinaryFile();
	free();
}

void Database::addTable(Table* table)
{
	if (size == capacity)
	{
		if (capacity == 0)
			resize(2);
		else
			resize(2 * capacity);
	}
	tables[size++] = table;
}

void Database::saveToBinaryFile() const
{
	std::ofstream ofs(filePath.c_str(), std::ios::binary | std::ios::out);

	if (!ofs.is_open())
		throw std::exception("Unable to open file!");

	filePath.saveToBinaryFile(ofs);

	ofs.write(reinterpret_cast<const char*>(&size), sizeof(size_t));

	for (int i = 0; i < size; i++)
	{
		MyString fileToSaveTable;

		fileToSaveTable += tables[i]->getName();
		fileToSaveTable += ".ss145";

		fileToSaveTable.saveToBinaryFile(ofs);

		tables[i]->saveToBinaryFile(fileToSaveTable);
	}
}

void Database::loadFromBinaryFile()
{
	free();

	std::ifstream ifs(filePath.c_str(), std::ios::binary | std::ios::in);

	if (!ifs.is_open())
		return;

	filePath.loadFromBinaryFile(ifs);

	ifs.read(reinterpret_cast<char*>(&size), sizeof(size_t));

	if (size != 0)
		tables = new Table* [size];

	capacity = size;

	for (int i = 0; i < size; i++)
	{
		tables[i] = new Table();

		MyString tableToLoad;

		tableToLoad.loadFromBinaryFile(ifs);

		tables[i]->loadFromBinaryFile(tableToLoad);

		//SimpleTablePrinter::getInstance().print(*tables[i], std::cout);
		//std::cout << "\nCols Count: "<<tables[i]->getColsCount() << " \nRowsCount: " << tables[i]->getRowsCount() << std::endl;
	}
}

size_t Database::getSize() const
{
	return size;
}

const Table& Database::getTable(unsigned index) const
{
	return *(tables[index]);
}

void Database::setValue(unsigned tableIndex, OptionalString&& value, unsigned rowIndex, unsigned colIndex)
{
	tables[tableIndex]->setValue(std::move(value), rowIndex, colIndex);
}

void Database::addValue(unsigned tableIndex, unsigned columnIndex, const OptionalString& value)
{
	tables[tableIndex]->addValue(value, columnIndex);
}

void Database::addColumn(unsigned tableIndex, Column* col)
{
	tables[tableIndex]->addColumn(col);
}

void Database::removeColumn(unsigned tableIndex, unsigned colIndex)
{
	tables[tableIndex]->removeColumn(colIndex);
}

void Database::setTableColumnName(unsigned tableIndex, unsigned colIndex, MyString&& newColName)
{
	tables[tableIndex]->setColumnName(colIndex, std::move(newColName));
}

void Database::removeRow(unsigned tableIndex, unsigned rowIndex)
{
	tables[tableIndex]->removeRow(rowIndex);
}

void Database::removeTable(unsigned tableIndex)
{
	size--;
}

SQLResponse Database::executeQuery(const MyString& query)
{
	SQLQuery* sql = SQLQueryFactory::makeQuery(query, *this);

	SQLResponse response = sql->execute();

	delete sql;

	return response;
}

void Database::copyFrom(const Database& other)
{
	tables = new Table * [other.capacity] {nullptr};
	
	for (int i = 0; i < other.size; i++)
	{
		tables[i] = new Table(*(other.tables[i]));
	}

	filePath = other.filePath;
	size = other.size;
	capacity = other.capacity;
}

void Database::moveFrom(Database&& other)
{
	tables = other.tables;
	other.tables = nullptr;

	filePath = std::move(filePath);
	size = other.size;
	capacity = other.capacity;
}

void Database::free()
{
	for (int i = 0; i < size; i++)
	{
		delete tables[i];
	}

	delete[] tables;
}

void Database::resize(size_t newCapacity)
{
	Table** temp = new Table* [newCapacity];

	for (int i = 0; i < size; i++)
	{
		temp[i] = tables[i];
	}

	delete[] tables;

	tables = temp;
}
