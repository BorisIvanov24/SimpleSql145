#include "ShowTablesSQLQuery.h"
#pragma warning(disable : 4996)

static void print(const Database& database, const MyString& header, size_t longestStrSize)
{
	std::cout << '+';
	for (int i = 0; i < longestStrSize + 2; i++)
		std::cout << '-';
	std::cout << '+' << std::endl;

	std::cout << "| " << header << " |" << std::endl;
	
	std::cout << '+';
	for (int i = 0; i < longestStrSize + 2; i++)
		std::cout << '-';
	std::cout << '+' << std::endl;

	for (int i = 0; i < database.getSize(); i++)
	{
		std::cout << "| " << database.getTable(i).getName();
		int startIndex = database.getTable(i).getName().getSize();
		for (int j = startIndex; j < longestStrSize; j++)
		{
			std::cout << ' ';
		}
		std::cout << " |" << std::endl;

		std::cout << '+';
		for (int i = 0; i < longestStrSize + 2; i++)
			std::cout << '-';
		std::cout << '+' << std::endl;
	}
}

ShowTablesSQLQuery::ShowTablesSQLQuery(Database& database) : SQLQuery(database)
{
}

SQLResponse ShowTablesSQLQuery::execute()
{
	if (database.getSize() == 0)
	{
		return SQLResponse("Empty set");
	}

	MyString header("Tables_in_");
	header += database.getName();
	size_t longestStrSize = header.getSize();

	//calculating the size of the longest string
	for (int i = 0; i < database.getSize(); i++)
	{
		size_t currentStrSize = database.getTable(i).getName().getSize();
		if (currentStrSize > longestStrSize)
			longestStrSize = currentStrSize;
	}

	//printing
	print(database, header, longestStrSize);

	char buffer[64];
	MyString str(_itoa(database.getSize(), buffer, 10));

	if(database.getSize() > 1)
	return SQLResponse(str+= " rows in set");
	else
	return SQLResponse(str += " row in set");
}
