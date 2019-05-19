// ArrayQueen.cpp : Defines the entry point for the console application.
//

/*TODO:
Solve:basic
Solve:backtmed (rotated)
Solve:advanced(mirrored and rotated)

*/
/*
megoldás ötlet. Leteszek egy királynőt. összeszámolom a lehetséges, maradék helyeket ahová tehetek még.
ez n darab. -> a táblának van n darab örököse. Mind az összes örökösre leteszek egy királynőt.
vissza az elejére.

addig amíg: le nincs téve a 8 királynő vagy nincs több hely


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

		//works as intentded don't bother!!!
		void hit_left( std::pair<int, int> XY)
		{

			if ((std::get<0>(XY) < 1 || std::get<1>(XY) > TABLE))
			{
				return;
			}
			else
			{

				table[std::get<1>(XY) - 1][std::get<0>(XY) - 1] = HITTED;
				hit_left({ --std::get<0>(XY), std::get<1>(XY) }); //balra ütés
			}

		};


		//ütéspédda 3,2 -> a 2. sorban, üti a 3. helyet
		void hit_down(std::pair<int, int> XY) // works as intended don't touch it!
		{
			
			
			if (std::get<1>(XY) > TABLE)
			{
				return;	
			}
			else
			{

				table[std::get<1>(XY) - 1][std::get<0>(XY) - 1] = HITTED;
				hit_down({ std::get<0>(XY), ++std::get<1>(XY) });
			}

		};
		
		//X
		void hit_up_right(std::pair<int, int >XY)
		{
			if (std::get<0>(XY) < 0 || std::get<1>(XY) < 0 || std::get<0>(XY) > TABLE)
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
			hit_up_left(XY); //good
			hit_up_right(XY); //good
			hit_down_left(XY); //good
			hit_down_right(XY);  //good



			table[std::get<0>(XY) - 1][std::get<1>(XY) - 1] = QUEEN;
		};
		void hit_lines(std::pair<int, int> XY) // works as intended don't touch it!
		{
			//ütéspédda 3,2 -> a 2. sorban, üti a 3. helyet
			std::pair<int, int> temp = XY;
			temp.first = 8;
			hit_left (temp);	
			temp = XY;
			temp.second = 1;
			hit_down (temp);
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
				{
					
					std::cout << "[" << (char)A.table[i][j] << "]";
				}

			}
			std::cout << std::endl;
		}
	
	};
	
	void solve(my_table &A, int D )
	{
		if (D > 8)
			return;

		std::list <std::pair<int, int>> possible_placements;
		
		//new depth placenets.
		for (int i = 1; i < TABLE; ++i)
		{

			for (int j = 0; j < TABLE; ++j)
			{
				if (A.table[i][j] == FREE)
				{
					possible_placements.push_back(std::pair<int, int>(i, j));
					
				}
			}
		}
		if (possible_placements.size() == 0)
			return;
		//possible palcements
		for (auto it = possible_placements.begin(); it != possible_placements.end(); ++it)
		{
			std::cout << it->first <<  " " << it->second << std::endl;
			
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

		Table_stuff::fill(*table);
		

		///ütéspédda 3,2 -> a 2. sorban, üti a 3. helyet


		//ütéspédda 3,2 -> a 2. sorban, üti a 3. helyet

		table->HIT(std::pair<int,int>(1,1));
	

		Table_stuff::out(*table);


		//Table_stuff::hit_left(table, std::make_tuple(6,4) );
		//table.rotate();
		//std::cout << std::endl << std::endl;
		//out(table);



		solve(*table, 0);


		std::getchar();

		return 0;
	}

