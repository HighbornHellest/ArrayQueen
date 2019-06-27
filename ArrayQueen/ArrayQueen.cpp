// ArrayQueen.cpp : Defines the entry point for the console application.
//

/*TODO:
Solve:basic
Solve:backtmed (rotated)
Solve:advanced(mirrored and rotated)
proper SOC (separation of concerns)
proper OCP (open - close principle)

*/
/*
megoldás ötlet. Leteszek egy királynőt. összeszámolom a lehetséges, maradék helyeket ahová tehetek még.
ez n darab. -> a táblának van n darab örököse. Mind az összes örökösre leteszek egy királynőt.
vissza az elejére.

addig amíg: le nincs téve a 8 királynő vagy nincs több hely


solving idea. place one queen, take into account all of the remaining places where a queen can be placed.
that's N number. -> the table has N number of "inherited". To all of these child tables put down a queen.
back to square 1.
as long as there are no places left, OR all queens have been placed

*/

#include "stdafx.h"
#include "Header.h"


namespace Table_stuff
{
	//swaps the contents of 2 integers
	void swap(int&i, int&j)
	{
		int temp = i;
		i = j;
		j = temp;

	}

	

	//class for a table. Holds it's conents.
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
	};


	//gives properties to the table \\ probably should use class(){0} tbh
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

	//sets contents of a table to 0
	void reset(int A[TABLE][TABLE])
	{
		for (int i = 0; i < TABLE; ++i)
		{
			for (int j = 0; j < TABLE; ++j)
			{
				A[i][j] = FREE;
				//++count;
			}
		}
	};
	//table copy
	//copies A into B, returns B
	auto CopyTable(int A[TABLE][TABLE], int B[TABLE][TABLE])
	{
		for (int i = 0; i < TABLE; ++i)
		{
			for (int j = 0; j < TABLE; ++j)
			{
				B[i][j] = A[i][j];
			}
		}

	}

	//solves the queen problem for a specific placement of 1 or more queens || D is the number of queens that are down
	void solve_for(int A[TABLE][TABLE], int D = 0)
	{
		

		if (D > 4)
		{
			//std::cout << "depth is over 8, going back..." << D << std::endl;
			//out(A);
			//if number of queens = TABLE, table -> out
			
				/*int NoQ = 0;
				for (int i = 0; i < TABLE; ++i)
				{

					for (int j = 0; j < TABLE; ++j)
					{
						if (A[i][j] == QUEEN)
						{
							++NoQ;
						}
					}
				}
				if (NoQ == TABLE)
				{
					out(A);
				}*/
			
			out(A);
			return;
		}
		
		//lehetséges lépések listája
		//list of possible placements
		std::list <std::pair<int, int>> possible_placements;
		

		//look for new depth placenets.
		for (int i = 1; i < TABLE; ++i)
		{

			for (int j = 1; j < TABLE; ++j)
			{
				if (A[i-1][j-1] == FREE)
				{

					possible_placements.push_back(std::pair<int, int>(i, j));
					
						//std::cout << "possible placement at: " << i << " " << j << std::endl;
						//std::cout << "["<< (char)A[i-1][j-1] << "]" << std::endl;
					

					
				}
			}
		}
		
		//if non found go back
		if (possible_placements.size() == 0)
		{
			//std::cout << "no possible placements have been found. Current depth is: " << D << std::endl;
		    
			

			return;
		}
		
		//take the possibe step
		for (auto it = possible_placements.begin(); it != possible_placements.end(); ++it)
		{
			//create and manage temp table, so that next cycle gets a clean table
			
			int temp[TABLE][TABLE];
			CopyTable(A, temp);
			//hit @ value of it

			HIT(temp, *it);
			if (D == TABLE)
			{
				//out(temp);
				
				
			}

			solve_for(temp, D+1);


		}





	};
	//---solv f end
	


	

}
	

	int main()
	{
		auto start = std::chrono::steady_clock::now();
		Table_stuff::my_table *table = new Table_stuff::my_table();
		

		Table_stuff::fill(*table);
		
		// a 0 a sorok az 1 az oszolopok
		//									pos   0: ,pos  1:
		/*HIT(table->table,std::pair<int,int>(      8,       8 ));
	

		Table_stuff::out(table->table);*/


		//Table_stuff::hit_left(table, std::make_tuple(6,4) );
		//table.rotate();
		//std::cout << std::endl << std::endl;
		//out(table);


		

		Table_stuff::solve_for(table->table);

		auto end = std::chrono::steady_clock::now();
		auto diff = end - start;
		std::cout << std::chrono::duration <double, std::milli>(diff).count() << " ms" << std::endl;

		std::cout << "waiting for input to end";
		std::getchar();

		return 0;
	}

