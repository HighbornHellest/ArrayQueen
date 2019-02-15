// ArrayQueen.cpp : Defines the entry point for the console application.
//

/*TODO:
Solve:basic
Solve:backtmed (rotated)
Solve:advanced(mirrored and rotated)

*/

#include "stdafx.h"
#include "Header.h"


namespace Table_stuff
{

	void swap(int&i, int&j)
	{
		int temp = i;
		i = j;
		j = temp;

	}

	struct my_table
	{
		int table[TABLE][TABLE];
		int last = TABLE - 1;
		int TNOL = TABLE / 2;
		void rotate() //https://www.youtube.com/watch?v=Jtu6dJ0Cb94 for details (not mine)
		{
			int level = 0;
			while (level < TNOL)
			{
				for (int i = level; i < last; ++i)
				{
					swap(table[level][i], table[i][last]);
					swap(table[level][i], table[last][last - i + level]);
					swap(table[level][i], table[last - i + level][level]);
				}
				++level;
				--last;
			}

			last = TABLE - 1;

		}

	};

	void fill(my_table &A)
	{
		int count = 0;
		for (int i = 0; i < TABLE; ++i)
		{
			for (int j = 0; j < TABLE; ++j)
			{
				A.table[i][j] = count;
				++count;
			}
		}
		count = 0;
	};

	void out(my_table &A)
	{

		for (int i = 0; i < TABLE; ++i)
		{
			for (int j = 0; j < TABLE; ++j)
			{
				if (A.table[i][j] < 10)
				{
					std::cout << "[ " << A.table[i][j] << "]";
				}
				else
					std::cout << "[" << A.table[i][j] << "]";

			}
			std::cout << std::endl;
		}
	};
	void solve()
	{

		for (int i = 0; i < TABLE; ++i)
		{
			for (int j = 0; j < TABLE; ++j)
			{
				//auto XY = std::make_tuple(i, j);
			}
		}

	};
	void reset(my_table &A)
	{
		for (int i = 0; i < TABLE; ++i)
		{
			for (int j = 0; j < TABLE; ++j)
			{
				A.table[i][j] = 0;
				//++count;
			}
		}
	};

	

	int main()
	{

		Table_stuff::my_table table{ 0 };

		

		std::vector<Table_stuff::my_table> tables;
		Table_stuff::fill(table);
		Table_stuff::out(table);
		Table_stuff::reset(table);
		Table_stuff::out(table);
		//Table_stuff::hit_left(table, std::make_tuple(6,4) );
		//table.rotate();
		//std::cout << std::endl << std::endl;
		//out(table);






		std::getchar();

		return 0;
	}

}