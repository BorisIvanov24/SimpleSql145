#include "Database.h"

/*
Expression-a zaduljitelno skobuvan po sledniq nachin:
    Where ((col2) = (Boris)) or ((col3) < (3.125))

ne se poddurjat izrazi ot sledniq vid:
	Where (col2) > (col3)

*/

int main()
{
	Database db("DataBase1.db");


	MyString sql;

	//create table test_table (field1 int, field2 real)
	//insert into test_table (field1, field2) values (1, 0), (2, 0), (3, 0), (4, 0)
	//update test_table set field2=1.0 where (field1) > (2)
	//update test_table set field2=2.0 where ((field1) > (2)) and ((field1) < (4))
	//update cities set country=United_Arab_Emirates where (country) = (UnitedArabEmirates)

	while (true)
	{
		std::cin >> sql;
		if (sql == "exit")
			break;

		std::cout << db.executeQuery(sql).getMessage() << std::endl;
	}

}

/*
create table join_test_one (field1 int, field2 text)
create table join_test_two (field1_2 int, field2_2 text)

insert into join_test_one (field1, field2) values (1, one), (2, two)
insert into join_test_two (field1_2, field2_2) values (1, edno), (3, dve)

select * from join_test_one
select * from join_test_two

select * from join_test_one join join_test_two on field1=field1_2

select field1, field2, field2_2 from join_test_one join join_test_two on field1=field1_2

select * from stadiums join worldCupGames on stadiumName=stadiumNameYears
*/