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

	do
	{
		if (str[index] == '(')
			counter++;

		if (str[index] == ')')
			counter--;

		index++;
	} while (counter != 0);

	index++;

	//((col2) = (Boris)) and ((col3) = (3.14))
	//(col2) > (34.4)
	switch (str[index])
	{
		case '>':
		{
			return new GreaterThanExpression(str.substr(1, index - 3), str.substr(index + 3, str.getSize() - index - 4));
		}
		case '<':
		{
			//std::cout << str.substr(1, index - 3) << " " << str.substr(index + 3, str.getSize() - index - 4) << std::endl;
			return new LowerThanExpression(str.substr(1, index - 3), str.substr(index + 3, str.getSize() - index - 4));
		}
		case '=':
		{
			//std::cout << str.substr(1, index - 3) << " " << str.substr(index + 3, str.getSize() - index - 4) << std::endl;
			return new EqualExpression(str.substr(1, index - 3), str.substr(index + 3, str.getSize() - index - 4));
		}
		case 'a':
		{
			//std::cout <<str.substr(1, index - 3) << " " << str.substr(index + 5, str.getSize() - index - 6) <<std::endl;
			return new ConjunctionExpression(makeExpression(str.substr(1, index - 3)),
										     makeExpression(str.substr(index + 5, str.getSize() - index - 6)));
		}
		case 'o':
		{
			//std::cout << str.substr(1, index - 3) << " " << str.substr(index + 4, str.getSize() - index - 5) << std::endl;

			return new DisjunctionExpression(makeExpression(str.substr(1, index - 3)),
				                             makeExpression(str.substr(index + 4, str.getSize() - index - 5)));
		}
		default:
		{
			return nullptr;
		}
	}
}

