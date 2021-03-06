// ArrayQueen.cpp : Defines the entry point for the console application.
//

/*TODO:
Solve:basic
Solve: NxM table
Solve: unique
Debug: queen for some reason

current: unique

clean up the name space mess

*/
/*
hu:
megoldás ötlet. Leteszek egy királynőt. összeszámolom a lehetséges, maradék helyeket ahová tehetek még.
ez n darab. -> a táblának van n darab örököse. Mind az összes örökösre leteszek egy királynőt.
vissza az elejére.

addig amíg: le nincs téve a 8 királynő vagy nincs több hely

en:
solving idea. place one queen, take into account all of the remaining places where a queen can be placed.
that's N number. -> the table has N number of "inherited". To all of these child tables put down a queen.
back to square 1.
as long as there are no places left, OR all queens have been placed

*/

#include "stdafx.h"
#include "Header.h"


namespace Table_stuff
{
	

	int depth = 0;
   

	//class for a table. Holds it's conents.
	typedef struct my_table
	{
		mutable	int table[TABLE][TABLE];
		mutable	std::string _string;
		mutable	unsigned long long _hash;
		
		//XY is the palce of the QUEEN!!!!
		bool operator== (const my_table rhv) const
		{
			if (_hash == rhv._hash)
			{
				return true;
			}
			return false;
		}
		
		bool operator< (const my_table rhv) const
		{
			if(_hash < rhv._hash)
				{
				return true;
				}
			return false;
		}

		inline void tostring()
		{
			_string = "";
			for (int i = 0; i < TABLE; ++i)
			{
				for (int j = 0; j < TABLE; ++j)
				{
					_string += table[i][j];
				}
			}
		}

		inline void rehashme()
		{
			tostring();
			_hash = std::hash<std::string>{}(_string);
		};

		inline void firsthash()
		{
			_hash = std::hash<std::string>{}(_string);
		}
		
		mutable bool rein = true;
		 int bingocoung;
	};
	
	std::set<my_table> endlist;
	std::set<my_table> final_list;
	

	//gives properties to the table \\ probably should use class(){0} tbh
	void fill(my_table &A)
	{
		//int count = 0;
		for (int i = 0; i < TABLE; ++i)
		{
			for (int j = 0; j < TABLE; ++j)
			{
				A.table[i][j] = FREE;
				//	++count;
			}
		}
		//count = 0;
	};
	void fill2(int A[TABLE][TABLE])
	{
		//int count = 0;
		for (int i = 0; i < TABLE; ++i)
		{
			for (int j = 0; j < TABLE; ++j)
			{
				A[i][j] = FREE;
				//	++count;
			}
		}
		//count = 0;
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
	//copies 1 into 2, returns 2
	//void * memcpy ( void * destination, const void * source, size_t num );
	inline void CopyTable(int A[TABLE][TABLE], int B[TABLE][TABLE])
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
	void solve_for(int A[TABLE][TABLE])
	{
		int Q = 0;
		//std::cout << "belépek";
		//list of possible placements
		std::list <std::pair<int, int>> possible_placements;
	
		
		//if -> have all log, else nothing

		//look for new depth placenets. and count the queens
		for (int i = 0; i < TABLE; ++i)
		{

			for (int j = 0; j < TABLE; ++j)
			{
				if (A[i][j] == FREE)
				{

					possible_placements.emplace_back(i,j);		
				}			
				if (A[i][j] == QUEEN)
				{
					//std::cout << "itt";
					++Q;
				}
			}
		}
		
	
		
		//if non found go back
		if (possible_placements.size() == 0)
		{	
			//if (Q == TABLE)
		//	{
				//out(A);
				my_table temp;
				{
					for (int i = 0; i < TABLE; ++i)
					{
						for (int j = 0; j < TABLE; ++j)
						{
							temp.table[i][j] = A[i][j];
							temp._string += A[i][j]; //no need to use tostring here, as shouldn't iterate again.
						}
					}
				}
				//temp._hash = std::hash<std::string>{}(temp._string);
				temp.firsthash();
				temp.bingocoung = endlist.size() + 1;
				endlist.insert(temp);


			

			//	Q = 0;
				//found_tables.emplace_back(A);//EZ ERRORT DOB!!!!

		//	}
			return;
		}


		int temp[TABLE][TABLE];
		
		//take the possibe step
		//for (auto it = possible_placements.begin(); it != possible_placements.end(); ++it)
		for (auto it : possible_placements)
		{
			
			fillh(temp);
			CopyTable(A, temp);
			
			//std::cout << std::get<0>(*it) << "," << std::get<1>(*it) << std::endl;
			
			//hit @ value of it
			//HIT(temp, *it);
			HIT_bishop(temp, it);
			
			//out(temp, depth);
			;
			++depth;
			solve_for(temp);
			--depth;
		}
		possible_placements.empty();

	};
	
	//swaps the contents of 2 integers
	inline void swap(int& i, int& j)
	{
		int temp = i;
		i = j;
		j = temp;

	}

	//rotates table in place
	void rotate(Table_stuff::my_table &it) //https://www.youtube.com/watch?v=Jtu6dJ0Cb94 for details (not mine)
	{
		int last = TABLE - 1;
		int TNOL = TABLE / 2;


		int level = 0;
		while (level < TNOL)
		{
			for (int i = level; i < last; ++i)
			{
				swap(it.table[level][i], it.table[i][last]);
				swap(it.table[level][i], it.table[last][last - i + level]);
				swap(it.table[level][i], it.table[last - i + level][level]);
			}
			++level;
			--last;
		}
		last = TABLE - 1;

	}



	//flips solution horizontally
	void FMH(Table_stuff::my_table &it) //flip matrix horizontally 
	{

		int temp;
		for (int i = 0; i < TABLE/2; ++i)
		{
			for (int j = 0; j < TABLE; ++j)
			{
				temp = it.table[i][j];
				it.table[i][j] = it.table[(TABLE -1) -i][j];
				it.table[(TABLE - 1) - i][j] = temp;
			}
		}


	}

	//flip matrix vertically
	void FMV(Table_stuff::my_table &it)
	{

		int temp;
		for (int i = 0; i < TABLE; ++i)
		{
			for (int j = 0; j < TABLE/2; ++j)
			{
				temp = it.table[i][j];
				it.table[i][j] = it.table[i][(TABLE - 1) - j];
				it.table[i][(TABLE - 1) - j] = temp;
			}
		}

	}


	bool similar(Table_stuff::my_table lhv, Table_stuff::my_table rhv)
	{
		for (int i = 0; i < TABLE; ++i)
		{
			for (int j = 0; j < TABLE; ++j)
			{
				if (lhv.table[i][j] != rhv.table[i][j])
				{
					return false;
				}
			}
		}
		return true;

	}

	//checks if solution is unique or not
	//unique: not a mirror and/or rotataion of a previous one
	

	void final_res(std::set<Table_stuff::my_table> &endl) 	
	{		
		/*std::cout << endl.size() << " start size!" << std::endl;
		for (auto it = endl.begin(); it!=endl.end(); it++)
		{
			my_table temp = *it;
			for (int i = 0; i < 4; ++i)
			{
				rotate(temp);
				temp.rehashme();
				for (auto it2 = endl.begin(); it2 != endl.end(); ++it2)
				{
					
					if (it2->bingocoung != temp.bingocoung)
					{
						out(it2->table);
						out(temp.table);

						if (it2->_hash == temp._hash)
						{
							it = endl.erase(it);
						}
					}
				}

			}	
		}*/
		auto it = endl.begin();
		auto it2 = endl.begin();
		my_table temp;
		while (it != endl.end())
		{
			for (int i = 0; i < TABLE; i++)
			{
				for (int j = 0; j < TABLE; j++)
				{
					temp.table[i][j] = it->table[i][j];
				}
			}
			temp._string = it->_string;
			temp._hash = it->_hash;
			temp.bingocoung = it->bingocoung;
			temp.rein = true;
			it = endl.erase(it);

			for (int i = 0; i < 5; i++)
			{
				//check if rotated once exists.
				
				FMV(temp);
				temp.rehashme();

				if (endl.count(temp))
				{
					
					break;
				}
				FMV(temp);

				//check if other flip exists

				FMV(temp);
				temp.rehashme();
				if (endl.count(temp))
				{
					temp.rein = false;
					break;
				}
				FMV(temp);


				//check if rotation exists
				rotate(temp);
				temp.rehashme();
				if (endl.count(temp))
				{
					temp.rein = false;
					break;
				}


			}
			if(temp.rein)
				endl.insert(temp);
	
		//	std::cout << "new element being watched" << std::endl;			
		}

		std::cout << endl.size() << " was the finel size! ree" << std::endl;
		
	}
	

}
	

	int main()
	{
		
		auto start = std::chrono::steady_clock::now();
		Table_stuff::my_table *table = new Table_stuff::my_table();
		Table_stuff::myfile.open("kimenet.txt", std::fstream::app);

		Table_stuff::fill(*table);
		
		//Table_stuff::out(table->table);
		Table_stuff::solve_for(table->table);

		std::cout << Table_stuff::endlist.size() << std::endl;
		std::cout << "working on uniqueness " << std::ednl;
		
		final_res(Table_stuff::endlist);
		for (auto it : Table_stuff::endlist)
		{
			Table_stuff::out(it.table);
		}


		std::cout << Table_stuff::endlist.size() << " was the final size" << std::endl;

		auto end = std::chrono::steady_clock::now();
		auto diff = end - start;
		std::cout << std::chrono::duration <double, std::milli>(diff).count() << " ms" << std::endl;
		std::cout << "waiting for input to end" << std::endl;

	


		Table_stuff::myfile.close();
		std::getchar();

		return 0;
	}
