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


		//XY is the palce of the QUEEN!!!!
		//std::<0>(XY) -> oszlop helye
		//std::<1>(XY) -> sor    helye

		//+
		void hit_left( std::pair<int, int> XY) //5 8
		{

			if ((std::get<0>(XY) < 1 || std::get<1>(XY) > TABLE))
			{
				return;
			}
			else
			{

				table[std::get<1>(XY) - 1][std::get<0>(XY) - 1] = HITTED;
				hit_left({ --std::get<0>(XY), std::get<1>(XY) });
			}

		};
		void hit_right(std::pair<int, int> XY)
		{
			if (XY.first < 0 || XY.second < 0)
			{
				throw "Bad_argument_exception";
			}
			else
			{
				for (int i = std::get<0>(XY)-1; i < TABLE; ++i)
				{
					table[std::get<1>(XY)-1][i] = HITTED;
				}
			}
			table[std::get<0>(XY) - 1][std::get<1>(XY) - 1] = QUEEN;

		};
		void hit_down(std::pair<int, int> XY)
		{
			if (XY.first <= 0 || XY.second <= 0)
			{
				throw "Bad_argument_exception";
			}
			else
			{
				for (int i = std::get<1>(XY)-1; i < TABLE; ++i)
				{
					table[i][std::get<1>(XY)-1] = HITTED;
				}
			}
			table[std::get<0>(XY) - 1][std::get<1>(XY) - 1] = QUEEN;

		};
		void hit_up(std::pair<int, int> XY)
		{
			if (XY.first < 0 || XY.second < 0)
			{
				throw "Bad_argument_exception";
			}
			else
			{
				for (int i = std::get<1>(XY) - 1; i >= 0; --i)
				{
					table[i][std::get<1>(XY) - 1] = HITTED;
				}
			}
			table[std::get<0>(XY) - 1][std::get<1>(XY) - 1] = QUEEN;

		};
		//X
		void hit_up_right(std::pair<int, int >XY)
		{
			if (std::get<0>(XY) <= 0 || std::get<1>(XY) <= 0)
			{
				return;
			}
			else
			{
				
				table[std::get<1>(XY) - 1][std::get<0>(XY)-1] = HITTED;
				hit_up_right({ ++std::get<0>(XY), --std::get<1>(XY) });
			}

		};
		void hit_up_left(std::pair<int, int> XY)
		{
			if (std::get<0>(XY) <= 0 || std::get<1>(XY) <= 0)
			{
				return;
			}
			else
			{

				table[std::get<1>(XY) - 1][std::get<0>(XY) - 1] = HITTED;
				hit_up_left({ --std::get<0>(XY), --std::get<1>(XY) });
			}
		}
		void hit_down_right(std::pair<int, int>XY)
		{
			if (std::get<0>(XY) > TABLE || std::get<1>(XY) > TABLE)
			{
				return;
			}
			else
			{

				table[std::get<1>(XY) - 1][std::get<0>(XY) - 1] = HITTED;
				hit_down_right({ ++std::get<0>(XY), ++std::get<1>(XY) });
			}
		}
		void hit_down_left(std::pair<int, int>  XY)
		{
			if ((std::get<0>(XY) < 1 || std::get<1>(XY) > TABLE))
			{
				return;
			}
			else
			{

				table[std::get<1>(XY) - 1][std::get<0>(XY) - 1] = HITTED;
				hit_down_left({ --std::get<0>(XY), ++std::get<1>(XY) });
			}
		}
		
		//X and + united
		void hit_cross(std::pair<int, int> XY)
		{
			hit_up_left(XY);
			hit_up_right(XY);
			hit_down_left(XY);
			hit_down_right(XY);



			table[std::get<0>(XY) - 1][std::get<1>(XY) - 1] = QUEEN;
		};
		void hit_lines(std::pair<int, int> XY)
		{
			hit_left (XY);
			hit_right(XY);
			hit_up   (XY);
			hit_down (XY);
		}
		//all
		void HIT(std::pair<int, int> XY)
		{
			hit_lines(XY);
			hit_cross(XY);
		}

	};

	void fill(my_table &A)
	{
		int count = 0;
		for (int i = 0; i < TABLE; ++i)
		{
			for (int j = 0; j < TABLE; ++j)
			{
				A.table[i][j] = FREE;
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
					std::cout << "[ " << (char)A.table[i][j] << "]";
				}
				else
					std::cout << "[" << (char)A.table[i][j] << "]";

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
				A.table[i][j] = FREE;
				//++count;
			}
		}
	};
}
	

	int main()
	{

		Table_stuff::my_table *table = new Table_stuff::my_table();

		

		std::vector<Table_stuff::my_table> tables;
		Table_stuff::fill(*table);
		
		table->hit_left({8,8});
		std::cout << "\n";
		Table_stuff::out(*table);
		//Table_stuff::hit_left(table, std::make_tuple(6,4) );
		//table.rotate();
		//std::cout << std::endl << std::endl;
		//out(table);






		std::getchar();

		return 0;
	}

