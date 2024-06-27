#include "ExpressionFactory.h"
#include "GreaterThanExpression.h"
#include "LowerThanExpression.h"
#include "EqualExpression.h"
#include "ConjunctionExpression.h"
#include "DisjunctionExpression.h"

//Priemame che izrazut e pravilno skobuvan
//primer: ((field1) > (2)) and ((field2) = (2.34))
Expression* ExpressionFactory::makeExpression(const MyString& str)
{
	unsigned index = 0;
	unsigned counter = 0;
	std::cout << str << std::endl;
	//select cityName, population from cities where (country) = (Bulgaria)
	//(country) = (Bulgaria)
	//size : 22
	//index : 10
	//index + 3 : 13
	do
	{
		if (str[index] == '(')
			counter++;

		if (str[index] == ')')
			counter--;

		index++;
	} while (counter != 0);

	index++;
	
	switch (str[index])
	{
		case '>':
		{
			//std::cout << str.substr(1, index - 3) << " " << str.substr(index + 3, strlen(str.c_str()) - index - 4) << std::endl;

			return new GreaterThanExpression(str.substr(1, index - 3), str.substr(index + 3, strlen(str.c_str()) - index - 4));
		}
		case '<':
		{
			//std::cout << str.substr(1, index - 3) << " " << str.substr(index + 3, strlen(str.c_str()) - index - 4) << std::endl;
			return new LowerThanExpression(str.substr(1, index - 3), str.substr(index + 3, strlen(str.c_str()) - index - 4));
		}
		case '=':
		{
			//std::cout << str.substr(1, index - 3) << " " << str.substr(index + 3, strlen(str.c_str()) - index - 4) << std::endl;
			//std::cout << str.getSize() << std::endl;
			return new EqualExpression(str.substr(1, index - 3), str.substr(index + 3, strlen(str.c_str()) - index - 4));
		}
		case 'a':
		{
			//std::cout <<str.substr(1, index - 3) << " " << str.substr(index + 5, strlen(str.c_str()) - index - 6) <<std::endl;
			return new ConjunctionExpression(makeExpression(str.substr(1, index - 3)),
										     makeExpression(str.substr(index + 5, strlen(str.c_str()) - index - 6)));
		}
		case 'o':
		{
			//std::cout << str.substr(1, index - 3) << " " << str.substr(index + 4, strlen(str.c_str()) - index - 5) << std::endl;

			return new DisjunctionExpression(makeExpression(str.substr(1, index - 3)),
				                             makeExpression(str.substr(index + 4, strlen(str.c_str()) - index - 5)));
		}
		default:
		{
			return nullptr;
		}
	}
}

