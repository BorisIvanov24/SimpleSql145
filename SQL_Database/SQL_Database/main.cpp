#include "Database.h"

/*
Expression-a zaduljitelno skobuvan po sledniq nachin:
    Where ((col2) = (Boris)) or ((col3) < (3.125))

ne se poddurjat izrazi ot sledniq vid:
	Where (col2) > (col3)

*/

int main()
{
	Database db("DatabaseBoris.db");


	MyString sql;

	//create table test_table (field1 int, field2 real)
	//insert into test_table (field1, field2) values (1, 0), (2, 0), (3, 0), (4, 0)
	//update test_table set field2=1.0 where (field1) > (2)
	//update test_table set field2=2.0 where ((field1) > (2)) and ((field1) < (4))
	
	while (true)
	{
		std::cin >> sql;
		if (sql == "exit")
			break;

		std::cout << db.executeQuery(sql).getMessage() << std::endl;
	}
	
}