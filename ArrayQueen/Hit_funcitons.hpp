#pragma once
#include "Header.h"


//bugfixed
void Right_left(int table[TABLE][TABLE], std::pair<int, int> XY)
{//0 sor, 1 oszlop
	
	if (std::get<1>(XY) < 0)
	{
		return;
	}
	else
	{

	table[std::get<0>(XY)][std::get<1>(XY)] = HITTED;
	//std::cout << "hitting: " << std::get<0>(XY) << " "<< std::get<1>(XY) << std::endl ;

		Right_left(table ,{ std::get<0>(XY), --std::get<1>(XY) }); //balra ütés
	}

};




void up_down(int table[TABLE][TABLE],  std::pair<int, int> XY) // works as intended don't touch it!
{

	//0 sor 1 oszlop
	if (std::get<0>(XY) == TABLE)
	{
		//std::cout << "REEEE";
		return;
	}
	else
	{
	table[std::get<0>(XY)][std::get<1>(XY)] = HITTED;
    // std::cout << "put to:" << std::get<0>(XY) << " " << std::get<1>(XY) << std::endl;

		up_down(table,{ ++std::get<0>(XY), std::get<1>(XY) });
	}

};

//X
void hit_up_right(int table[TABLE][TABLE], std::pair<int, int >XY) //looks good 
{
	if (std::get<0>(XY) < 0 || std::get<1>(XY) < 0 || std::get<0>(XY) > TABLE-1 || std::get<1>(XY) > TABLE-1)
	{
		return;
	}
	else
	{
		
			table[std::get<0>(XY)][std::get<1>(XY)] = HITTED;
		hit_up_right(table,{ --std::get<0>(XY), ++std::get<1>(XY) });
	}

};
//hits to the right too. actually hits through X axis
void hit_up_left(int table[TABLE][TABLE], std::pair<int, int> XY)
{
	if (std::get<0>(XY) < 0 || std::get<1>(XY) < 0)
	{
		return;
	}
	else
	{
		
		table[std::get<0>(XY)][std::get<1>(XY)] = HITTED;
		hit_up_left(table,{ --std::get<0>(XY), --std::get<1>(XY) });
	}
}
void hit_down_right(int table[TABLE][TABLE], std::pair<int, int>XY)
{
	if (std::get<0>(XY) > TABLE-1 || std::get<1>(XY) > TABLE-1)
	{
		return;
	}
	else
	{
		
			table[std::get<0>(XY)][std::get<1>(XY)] = HITTED;
		//::Table_stuff::out(table);
		//std::cout << "put to:" << std::get<0>(XY) -1 << " " << std::get<1>(XY)-1 << std::endl;
		hit_down_right(table,{ ++std::get<0>(XY), ++std::get<1>(XY) });
	}
}
void hit_down_left(int table[TABLE][TABLE], std::pair<int, int>  XY) //100% debugged
{
	//std::cout << std::get<0>(XY) << std::endl;
	//std::cout << std::get<1>(XY) << std::endl;


	
	if( !( (std::get<0>(XY) >= 0) && (std::get<0>(XY) < TABLE) && (std::get<1>(XY)) >= 0 && (std::get<1>(XY) < TABLE)) )
	{
		

		return;
	}
	else
	{
			table[std::get<0>(XY)][std::get<1>(XY)] = HITTED;
		hit_down_left(table,{ ++std::get<0>(XY), --std::get<1>(XY) });
		//a 0 a lefelé, az 1 pedig a jobbra.
	}
}

//X and + united
void hit_cross(int table[TABLE][TABLE], std::pair<int, int> XY)
{
	hit_up_left(table, XY); //good | does not cause stack corruption
	
	hit_up_right(table, XY); //good
	hit_down_left(table, XY); //good | last debugged 2020 05 29
	hit_down_right(table, XY);  //good

};
void hit_lines(int table[TABLE][TABLE], std::pair<int, int> XY) // works as intended don't touch it!
{
	//az 1 az oszolopok, a 0 a sorok. a csalás az az, hogy egyből a tábla méretre állítom
	//így nem kell függvényt írni arra, hogy jobbra is legyen ütés.
	//működik!
	auto temp = XY;
	temp.second = TABLE-1;
	Right_left(table, temp);
	//----------------------------------------------------

	temp = XY;
	temp.first = 0;
	up_down(table, temp);
}
//all

void HIT_queen(int table[TABLE][TABLE], std::pair<int, int> XY)
{
	
	///seems good
	
	hit_lines(table, XY);
	
	
	hit_cross(table,XY);
	
	
	//királynő helyezése UTOLJÁRA
	//placing the queen as LAST

   	table[std::get<0>(XY)][std::get<1>(XY)] = QUEEN;

}
void HIT_rook(int table[TABLE][TABLE], std::pair<int, int> XY)
{
	hit_lines(table, XY);

	
		table[std::get<0>(XY)][std::get<1>(XY)] = ROOK;

	//Table_stuff::out(table);
}
void HIT_bishop(int table[TABLE][TABLE], std::pair<int, int> XY)
{
	hit_cross(table, XY);
	
	table[std::get<0>(XY)][std::get<1>(XY)] = BISHOP;
	//Table_stuff::out(table);
}

void fillh(int table[TABLE][TABLE])
{
	
	for (int i = 0; i < TABLE; ++i)
	{
		for (int j = 0; j < TABLE; ++j)
		{
			table[i][j] = FREE;
			
		}
	}

};

