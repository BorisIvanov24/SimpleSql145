#include "ShowTablesSQLQuery.h"
#include <sstream>
#pragma warning(disable : 4996)

static void print(const Database& database, const MyString& header, size_t longestStrSize,
			      std::ostream& os)
{
	os << '+';
	for (int i = 0; i < longestStrSize + 2; i++)
		os << '-';
	os << '+' << std::endl;

	os << "| " << header << " |" << std::endl;
	
	os << '+';
	for (int i = 0; i < longestStrSize + 2; i++)
		os << '-';
	os << '+' << std::endl;

	for (int i = 0; i < database.getSize(); i++)
	{
		os << "| " << database.getTable(i).getName();
		int startIndex = database.getTable(i).getName().getSize();
		for (int j = startIndex; j < longestStrSize; j++)
		{
			os << ' ';
		}
		os << " |" << std::endl;

		os << '+';
		for (int i = 0; i < longestStrSize + 2; i++)
			os << '-';
		os << '+' << std::endl;
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
	header += "database";
	size_t longestStrSize = header.getSize();

	//calculating the size of the longest string
	for (int i = 0; i < database.getSize(); i++)
	{
		size_t currentStrSize = database.getTable(i).getName().getSize();
		if (currentStrSize > longestStrSize)
			longestStrSize = currentStrSize;
	}

	//printing
	std::stringstream ss("");

	print(database, header, longestStrSize, ss);

	char buffer[64];
	MyString str("\n");

	str += _itoa(database.getSize(), buffer, 10);

	if (database.getSize() > 1)
		str += " rows in set\n";
	else
		str += " row in set\n";

	ss << str;

	return SQLResponse(ss.str().c_str());
}
