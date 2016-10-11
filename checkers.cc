/*
Hannah Naetzker
CS 2401
Final Checkers Project
Checkers Implementation Class
Sets up checkers board and game
*/

#include "game.h"
#include "piece.h"
#include "colors.h"
#include "checkers.h"
#include <iostream>     
#include <string> 
#include <cstring>
#include <iomanip>
#include <queue>
#include <cassert>
#include <climits>

using namespace std;

namespace main_savitch_14
{

Checkers::Checkers()
{
	//sets up new game board and pieces
	int i;
	//sets up pieces for red side
	for(i=1; i<8; i+=2)
	{
		board[0][i].set_occupied(true);
		board[0][i].set_color("red");
	}
	for(i=0; i<8; i+=2)
	{
		board[1][i].set_occupied(true);
		board[1][i].set_color("red");
	}
	for(i=1; i<8; i+=2)
	{
		board[2][i].set_occupied(true);
		board[2][i].set_color("red");
	}
	
	//sets up pieces for black side
	for(i=0; i<8; i+=2)
	{
		board[5][i].set_occupied(true);
		board[5][i].set_color("white");
	}
	for(i=1; i<8; i+=2)
	{
		board[6][i].set_occupied(true);
		board[6][i].set_color("white");
	}
	for(i=0; i<8; i+=2)
	{
		board[7][i].set_occupied(true);
		board[7][i].set_color("white");
	}
}





void Checkers::restart()
{
	//sets up new game board and pieces
	int i;
	//first delete all occupied pieces on board
	for(i=0; i<8; i++)
	{
		for(int j=0; j<8; j++)
		{
			board[i][j].set_occupied(false);
			board[i][j].set_king(false);
		}
	}
	
	//sets up pieces for red side
	for(i=1; i<8; i+=2)
	{
		board[0][i].set_occupied(true);
		board[0][i].set_color("red");
	}
	for(i=0; i<8; i+=2)
	{
		board[1][i].set_occupied(true);
		board[1][i].set_color("red");
	}
	for(i=1; i<8; i+=2)
	{
		board[2][i].set_occupied(true);
		board[2][i].set_color("red");
	}
	
	//sets up pieces for black side
	for(i=0; i<8; i+=2)
	{
		board[5][i].set_occupied(true);
		board[5][i].set_color("white");
	}
	for(i=1; i<8; i+=2)
	{
		board[6][i].set_occupied(true);
		board[6][i].set_color("white");
	}
	for(i=0; i<8; i+=2)
	{
		board[7][i].set_occupied(true);
		board[7][i].set_color("white");
	}
	game::restart();
}




void Checkers::display_status()const
{
	//displays the current board and where the checkers are
	cout << "    A    B    C    D    E    F    G    H  \n";
	cout << "  ----------------------------------------\n";
	for(int i=0; i<8; i++)
	{
		//goes through 8 rows
		for(int k=0; k<3; k++)
		{
			//makes three lines of spaces to give square look
			if(k == 1)
			{
				//if its the middle row
				//included to determine if the @ symbol needs to be placed in the middle of the square based on occupancy
				cout << RESET << i+1 << "|";
				
				for(int j=0; j<8; j++)
				{
					//goes through 8 columns
					if(!board[i][j].is_occupied())
					{
						//if its a blank space
						if(i%2 == 0)
						{
							//if if an even row
							if(j%2 == 0)
								cout << B_MAGENTA << "     ";	//even column
							else	
								cout << B_BLACK << "     ";	//odd column
						}
						else
						{
							//if its an odd row
							if(j%2 == 0)
								cout << B_BLACK << "     ";	//even column
							else
								cout << B_MAGENTA << "     ";	//odd column
						}
					}
					else
					{
						//if its an occupied space
						if(i%2 == 0)
						{
							if(j%2 == 0)
								print_red_occupied(board[i][j]);
							else
								print_black_occupied(board[i][j]);
						}
						else
						{
							if(j%2 == 0)
								print_black_occupied(board[i][j]);
							else
								print_red_occupied(board[i][j]);
						}
					}
				}
				
			}
			else
			{
				//the top and bottom parts of a square piece
				//doesn't matter if occupied or not
				cout << RESET << " |";
				for(int j=0; j<8; j++)
				{
					if(i%2 == 0)
					{
						if(j%2 == 0)
							cout << B_MAGENTA << "     ";
						else
							cout << B_BLACK << "     ";
					}
					else
					{
						if(j%2 == 0)
							cout << B_BLACK << "     ";
						else
							cout << B_MAGENTA << "     ";
					}
				}
			}
			cout << RESET << endl;
		}
	}
}
















bool Checkers::is_legal(const string& move)const
{
	//checks if the move entered is legal following the rules of checkers
	int row1, row2, col1, col2;
	col1 = (int)(toupper(move[0])-'A');
	row1 = (int)(move[1] -'1');
	col2 = (int)(toupper(move[2])-'A');
	row2 = (int)(move[3] -'1');

	//outside bounds
	if(row1<0 || row1>7 || col1<0 || col1>7 || row2<0 || row2>7 || col2<0 || col2>7)
		return false;
	
	//if its trying to move to a red space
	if((row2%2 ==0 && col2%2 == 0) || (row2%2 == 1 && col2%2 == 1))
		return false;
	
	if(row1 == row2 && col1 == col2)
		return false;
	
	// target space is occupied
	if(board[row2][col2].is_occupied())
		return false;
	
	//if your trying to move nothing
	if(!board[row1][col1].is_occupied())
		return false;
	
	if(row1 == row2)
		return false;

	
	
	if(next_mover() == HUMAN)
	{
		//white move
		//if trying to go backwards when not a king
		if(row2>row1 && !board[row1][col1].is_king())
			return false;	

		if((row1 == row2+2 || row1 == row2+4) && (col1 == col2+2 || col1 == col2-2 || col1 == col2+4 || col1 == col2-4))
		{
			//checks if a jump is available and being made
			if(is_jump(move))
				return true;
		}		
		if(col1 == col2 && row1 == row2 + 4)
		{
			//checks if a jump is available and being made
			if(is_jump(move))
				return true;
		}
		if(board[row1][col1].is_king())
		{
			//check backwards cause king
			if((row1 == row2-2 || row1 == row2-4) && (col1 == col2+2 || col1 == col2-2 || col1 == col2+4 || col1 == col2-4))
			{
				//checks if a jump is available and being made
				if(is_jump(move))
					return true;
			}
			if(col1 == col2 && row1 == row2 - 4)
			{
				//checks if a jump is available and being made
				if(is_jump(move))
					return true;
			}
			//checking to move one
			if(row2 == row1+1)
			{
				if(col2 == col1+1 || col2 == col1-1)
					return true;
			}
		}
		if(row2 == row1-1)
		{
			//checking to go forward only one
			if(col2 == col1+1 || col2 == col1-1)
				return true;
		}
		
	}
	
	if(next_mover() == COMPUTER)
	{
		//red move
		//trying to go backwards when not a king
		if(row2<row1 && !board[row1][col1].is_king())
			return false;
		if((row1 == row2-2 || row1 == row2-4) && (col1 == col2+2 || col1 == col2-2 || col1 == col2+4 || col1 == col2-4))
		{
			//checks if a jump is available and being made
			if(is_jump(move))
				return true;
		}
		if(col1 == col2 && row1 == row2 - 4)
		{
			//checks if a jump is available and being made
			if(is_jump(move))
				return true;
		}
		if(board[row1][col1].is_king())
		{
			//check backwards for king
			if((row1 == row2+2 || row1 == row2+4) && (col1 == col2+2 || col1 == col2-2 || col1 == col2+4 || col1 == col2-4))
			{
				//checks if a jump is available and being made
				if(is_jump(move))
					return true;
			}
			if(col1 == col2 && row1 == row2 + 4)
			{	
				//checks if a jump is available and being made
				if(is_jump(move))
					return true;
			}	
			//checking to move one
			if(row2 == row1-1)
			{
				if(col2 == col1+1 || col2 == col1-1)
					return true;
			}
		}
		
		if(row2 == row1+1)
		{
			//checking to go forward only one
			if(col2 == col1+1 || col2 == col1-1)
				return true;
		}
	}
	return false;
}


















void Checkers::make_move(const std::string& move)
{
	//Makes move for user
	
	std::queue<int> rows;
	std::queue<int> cols;
	
	while(!rows.empty())
		rows.pop();
	while(!cols.empty())
		cols.pop();
	
	int row1, row2, col1, col2;
	col1 = (int)(toupper(move[0])-'A');
	row1 = (int)(move[1] -'1');
	col2 = (int)(toupper(move[2])-'A');
	row2 = (int)(move[3] -'1');
	//takes in row and col spots
	
	
	
	if(next_mover() == HUMAN && row1 != row2+1 && row1 != row2-1 && col1 != col2+1 && col1 != col2-1)
	{
		if(is_jump(move))
		{
		//white piece and jumping
		bool cont = true;
		bool some = false;
		int temp1 = row1;
		int temp2 = col1;
		while(cont)
		{	some = false;
			if(temp1>1 && temp2<6 && board[temp1-1][temp2+1].is_occupied() && board[temp1-1][temp2+1].get_color() == "red")
			{	
				if(!board[temp1-2][temp2+2].is_occupied())
				{
					//jumping up and to the right
					some = true;
					rows.push(temp1-1);
					cols.push(temp2+1);
					temp1 -= 2;
					temp2 += 2;
				}
				else 
					cont = false;
			}
			else if(temp1>1 && temp2>1 && board[temp1-1][temp2-1].is_occupied() && board[temp1-1][temp2-1].get_color() == "red")
			{
				if(!board[temp1-2][temp2-2].is_occupied())
				{
					//jumping up and to the left
					some = true;
					rows.push(temp1-1);
					cols.push(temp2-1);
					temp1 -= 2;
					temp2 -= 2;
				}
				else 
					cont = false;
			}
			if(temp1<=1)
				cont = false;
			else if(!board[temp1-1][temp2+1].is_occupied() && !board[temp1-1][temp2-1].is_occupied())
				cont = false;
			else if(board[temp1-1][temp2+1].get_color() != "red" && board[temp1-1][temp2-1].get_color() != "red")
				cont = false;
			if(some == false)
				cont = false;
		}
		temp1 = row1;
		temp2 = col1;
		cont = true;	
		if(board[temp1][temp2].is_king())
		{
			//king piece so checks backwards
			while(cont)
			{	some = false;
				if(temp1<6 && temp2<6 && board[temp1+1][temp2+1].is_occupied() && board[temp1+1][temp2+1].get_color() == "red")
				{
					if(!board[temp1+2][temp2+2].is_occupied())
					{
						//jumping down and to the right
						some = true;
						rows.push(temp1+1);
						cols.push(temp2+1);
						temp1 += 2;
						temp2 += 2;
					}
					else 
						cont = false;
				}
				else if(temp1<6 && temp2>1 && board[temp1+1][temp2-1].is_occupied() && board[temp1+1][temp2-1].get_color() == "red")
				{
					if(!board[temp1+2][temp2-2].is_occupied())
					{
						//jumping down and to the left
						some = true;
						rows.push(temp1+1);
						cols.push(temp2-1);
						temp1 += 2;
						temp2 -= 2;
					}
					else 
						cont = false;
				}
				if(temp1>=6)
					cont = false;
				else if(!board[temp1+1][temp2+1].is_occupied() && !board[temp1+1][temp2-1].is_occupied())
					cont = false;
				else if(board[temp1+1][temp2+1].get_color() != "white" && board[temp1+1][temp2-1].get_color() != "white")
					cont = false;
				if(some == false)
					cont = false;
			}
		}
		while(!rows.empty())
		{
			//deletes all the pieces that were jumped along the way
			delete_piece(rows.front(), cols.front());
			rows.pop();
			cols.pop();
		}
		}
	}
	
	
	
	
	
	
	if(next_mover() == COMPUTER && row1 != row2+1 && row1 != row2-1 && col1 != col2+1 && col1 != col2-1)
	{
		if(is_jump(move))
		{
		//red piece and jumping
		bool cont = true;
		bool some = false;	
		int temp1 = row1;
		int temp2 = col1;
		while(cont)
		{	some = false;
			if(temp1<6 && temp2<6 && board[temp1+1][temp2+1].is_occupied() && board[temp1+1][temp2+1].get_color() == "white")
			{
				if(!board[temp1+2][temp2+2].is_occupied())
				{
					//jumping down and to the right
					some = true;
					rows.push(temp1+1);
					cols.push(temp2+1);
					temp1 += 2;
					temp2 += 2;
				}
				else 
					cont = false;
			}
			else if(temp1<6 && temp2>1 && board[temp1+1][temp2-1].is_occupied() && board[temp1+1][temp2-1].get_color() == "white")
			{
				if(!board[temp1+2][temp2-2].is_occupied())
				{
					//jumping down and to the left
					some = true;
					rows.push(temp1+1);
					cols.push(temp2-1);
					temp1 += 2;
					temp2 -= 2;
				}
				else 
					cont = false;
			}
			if(temp1>=6)
				cont = false;
			else if(!board[temp1+1][temp2+1].is_occupied() && !board[temp1+1][temp2-1].is_occupied())
				cont = false;
			else if(board[temp1+1][temp2+1].get_color() != "white" && board[temp1+1][temp2-1].get_color() != "white")
				cont = false;
			if(some == false)
				cont = false;
		}
		temp1 = row1;
		temp2 = col1;
		cont = true;	
		if(board[temp1][temp2].is_king())
		{
			//king piece so checking to jump backwards
			while(cont)
			{	some = false;
				if(temp1>1 && temp2<6 && board[temp1-1][temp2+1].is_occupied() && board[temp1-1][temp2+1].get_color() == "white")
				{
					if(!board[temp1-2][temp2+2].is_occupied())
					{
					//jumping up and to the right
						some = true;
						rows.push(temp1-1);
						cols.push(temp2+1);
						temp1 -= 2;
						temp2 += 2;
					}
					else 
						cont = false;
				}
				else if(temp1>1 && temp2>1 && board[temp1-1][temp2-1].is_occupied() && board[temp1-1][temp2-1].get_color() == "white")
				{
					if(!board[temp1-2][temp2-2].is_occupied())
					{
						//jumping up and to the right
						some = true;
						rows.push(temp1-1);
						cols.push(temp2-1);
						temp1 -= 2;
						temp2 -= 2;
					}
					else 
						cont = false;
				}
				if(temp1<=1)
					cont = false;
				else if(!board[temp1-1][temp2+1].is_occupied() && !board[temp1-1][temp2-1].is_occupied())
					cont = false;
				else if(board[temp1-1][temp2+1].get_color() != "white" && board[temp1-1][temp2-1].get_color() != "white")
					cont = false;
				if(some == false)
					cont = false;
			}
		}
		while(!rows.empty())
		{
			//deletes all the pieces jumped along the way
			delete_piece(rows.front(), cols.front());
			rows.pop();
			cols.pop();
		}
		}
	}

	//sets to king if it makes it to the end
	if(row2 == 0 || row2 == 7)
		board[row1][col1].set_king(true);

	//moves piece to different spot
	board[row1][col1].set_occupied(false);
	board[row2][col2].set_occupied(true);
	board[row2][col2].set_color(board[row1][col1].get_color());
	board[row2][col2].set_king(board[row1][col1].is_king());
	game::make_move(move);
}












void Checkers::print_black_occupied(const Piece& p)const
{
	//prints on black space
	if(p.get_color() == "white")
	{
		if(p.is_king())
			cout << B_BLACK << WHITE << "  K  ";	//if its a white king
		else
			cout << B_BLACK << WHITE << "  @  ";	//if its a white piece
	}
	else
	{
		if(p.is_king())
			cout << B_BLACK << RED << "  K  ";	//if its a red king
		else
			cout << B_BLACK << RED << "  @  ";	//if its a red piece
	}
}

void Checkers::print_red_occupied(const Piece& p)const
{
	//prints on red space
	if(p.get_color() == "white")
	{
		if(p.is_king())
			cout << B_RED << WHITE << "  K  ";	//if its a white king
		else
			cout << B_RED << WHITE << "  @  ";	//if its a white piece
	}
	else
	{
		if(p.is_king())
			cout << B_RED << RED << "  K  ";	//if its a red king
		else
			cout << B_RED << RED << "  @  ";	//if its a red piece
	}
}

void Checkers::delete_piece(int row, int col)
{
	//deletes piece from boards views
	board[row][col].set_occupied(false);
	board[row][col].set_king(false);
	board[row][col].set_color("");
}














bool Checkers::is_game_over( ) const
{
	//checks if no moves can be made by a player
	int rsum=0;
	int wsum=0;
	//check if no red or white pieces
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<8; j++)
		{
			if(board[i][j].is_occupied())
			{
				if(board[i][j].get_color() == "red")
					rsum++;
				else
					wsum++;
			}
		}
	}
	if(rsum == 0 || wsum == 0)
		return true;
	return false;
}














bool Checkers::is_jump(const string& move)const
{
	//checks if the move is one of the possible jumps
	int row1, row2, col1, col2;
	col1 = (int)(toupper(move[0])-'A');
	row1 = (int)(move[1] -'1');
	col2 = (int)(toupper(move[2])-'A');
	row2 = (int)(move[3] -'1');
	
	int temp1, temp2;
		
	std::queue<int> r;
	std::queue<int> c;
	
	

	//checks if there is a possible jump for the current player
	if(next_mover() == HUMAN)
	{
		//white piece
		if(col1 == col2 && row1 - row2 <4)
			return false;
		if(col2 > col1 && col2-col1 >4)
			return false;
		if(col2 < col1 && col1-col2 >4)
			return false;
		bool cont = true;
		bool some = false;
		temp1 = row1;
		temp2 = col1;
		if(board[temp1][temp2].is_occupied() && board[temp1][temp2].get_color() == "white")
		{
			while(cont)
			{	some = false;
				if(temp1>1 && temp2<6 && board[temp1-1][temp2+1].is_occupied() && board[temp1-1][temp2+1].get_color() == "red")
				{
					if(!board[temp1-2][temp2+2].is_occupied())
					{	
						some = true;
						temp1 -= 2;
						temp2 += 2;
					}
					else 
						cont = false;
				}
				else if(temp1>1 && temp2>1 && board[temp1-1][temp2-1].is_occupied() && board[temp1-1][temp2-1].get_color() == "red")
				{
					if(!board[temp1-2][temp2-2].is_occupied())
					{
						some = true;
						temp1 -= 2;
						temp2 -= 2;
					}
					else 
						cont = false;
				}
				if(temp1<=1)
					cont = false;
				else if(!board[temp1-1][temp2+1].is_occupied() && !board[temp1-1][temp2-1].is_occupied())
					cont = false;
				else if(board[temp1-1][temp2+1].get_color() != "red" && board[temp1-1][temp2-1].get_color() != "red")
					cont = false;
				if(some == false)
					cont = false;
			}
			if(temp1 != row1)
			{
				r.push(temp1);
				c.push(temp2);
			}
			temp1 = row1;
			temp2 = col1;
			cont = true;
			if(board[temp1][temp2].is_king())
			{
				while(cont)
				{	some = false;
					if(temp1<6 && temp2<6 && board[temp1+1][temp2+1].is_occupied() && board[temp1+1][temp2+1].get_color() == "red")
					{
						if(!board[temp1+2][temp2+2].is_occupied())
						{
							some = true;
							temp1 += 2;
							temp2 += 2;
						}
						else 
							cont = false;
					}
					else if(temp1<6 && temp2>1 && board[temp1+1][temp2-1].is_occupied() && board[temp1+1][temp2-1].get_color() == "red")
					{
						if(!board[temp1+2][temp2-2].is_occupied())
						{
							some = true;
							temp1 += 2;
							temp2 -= 2;
						}
						else 
							cont = false;
					}
					if(temp1>=6)
						cont = false;
					else if(!board[temp1+1][temp2+1].is_occupied() && !board[temp1+1][temp2-1].is_occupied())
						cont = false;
					else if(board[temp1+1][temp2+1].get_color() != "red" && board[temp1+1][temp2-1].get_color() != "red")
						cont = false;
					if(some == false)
						cont = false;
				}
				if(temp1 != row1)
				{
					r.push(temp1);
					c.push(temp2);
				}
			}
		}
		bool done = false;
		while(!r.empty())
		{
			if(r.front() == row2 && c.front() == col2)
			{
				done = true;
			}
			r.pop();
			c.pop();
		}
		return done;
	}
	
	
	
	
	
	
	if(next_mover() == COMPUTER)
	{
		//red piece
		if(col1 == col2 && row2 - row1 <4)
			return false;
		if(col2 > col1 && col2-col1 >4)
			return false;
		if(col2 < col1 && col1-col2 >4)
			return false;
		bool cont = true;
		bool some = false;
		temp1 = row1;
		temp2 = col1;
		if(board[temp1][temp2].is_occupied() && board[temp1][temp2].get_color() == "red")
		{
			while(cont)
			{	some = false;
				if(temp1<6 && temp2<6 && board[temp1+1][temp2+1].is_occupied() && board[temp1+1][temp2+1].get_color() == "white")
				{
					if(!board[temp1+2][temp2+2].is_occupied())
					{
						some = true;
						temp1 += 2;
						temp2 += 2;
					}
					else 
						cont = false;
				}
				else if(temp1<6 && temp2>1 && board[temp1+1][temp2-1].is_occupied() && board[temp1+1][temp2-1].get_color() == "white")
				{
					if(!board[temp1+2][temp2-2].is_occupied())
					{
						some = true;
						temp1 += 2;
						temp2 -= 2;		
					}
					else 
						cont = false;
				}
				if(temp1>=6)
					cont = false;
				else if(!board[temp1+1][temp2+1].is_occupied() && !board[temp1+1][temp2-1].is_occupied())
					cont = false;
				else if(board[temp1+1][temp2+1].get_color() != "white" && board[temp1+1][temp2-1].get_color() != "white")
					cont = false;
				if(some == false)
					cont = false;
			}
			if(temp1 != row1)
			{
				r.push(temp1);
				c.push(temp2);
			}
			temp1 = row1;
			temp2 = col1;
			cont = true;
			if(board[temp1][temp2].is_king())
			{
				while(cont)
				{	some = false;
					if(temp1>1 && temp2<6 && board[temp1-1][temp2+1].is_occupied() && board[temp1-1][temp2+1].get_color() == "white")
					{
						if(!board[temp1-2][temp2+2].is_occupied())
						{
							some = true;
							temp1 -= 2;
							temp2 += 2;
						}
						else 
							cont = false;
					}
					else if(temp1>1 && temp2>1 && board[temp1-1][temp2-1].is_occupied() && board[temp1-1][temp2-1].get_color() == "white")
					{
						if(!board[temp1-2][temp2-2].is_occupied())
						{
							some = true;
							temp1 -= 2;
							temp2 -= 2;
						}
						else 
							cont = false;
					}
					if(temp1<=1)
						cont = false;
					else if(!board[temp1-1][temp2+1].is_occupied() && !board[temp1-1][temp2-1].is_occupied())
						cont = false;
					else if(board[temp1-1][temp2+1].get_color() != "white" && board[temp1-1][temp2-1].get_color() != "white")
						cont = false;
					if(some == false)
						cont = false;
				}
				if(temp1 != row1)
				{
					r.push(temp1);
					c.push(temp2);
				}
			}
		}
		bool done = false;
		while(!r.empty())
		{
			if(r.front() == row2 && c.front() == col2)
				done = true;
			r.pop();
			c.pop();
		}
		//if(done!=some)
			//return false;
		//display_status();
		return done;
	}
	return false;
}













game* Checkers::clone()const
{
	return new Checkers(*this);
}















void Checkers::compute_moves(std::queue<std::string>& moves)const
{
	//build strings that are like user moves
	//if string is legal, push into queue moves.push(queue)
	string m = "";
	bool jump = false;
	if(next_mover() == HUMAN)
	{
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<8; j++)
		{
			if(board[i][j].is_occupied() && board[i][j].get_color() == "white")
			{
				m = "";
				if(j==0)m+="A";
				if(j==1)m+="B";
				if(j==2)m+="C";
				if(j==3)m+="D";
				if(j==4)m+="E";
				if(j==5)m+="F";
				if(j==6)m+="G";
				if(j==7)m+="H";
				if(i==0)m+="1";
				if(i==1)m+="2";
				if(i==2)m+="3";
				if(i==3)m+="4";
				if(i==4)m+="5";
				if(i==5)m+="6";
				if(i==6)m+="7";
				if(i==7)m+="8";
				//sets spot of piece
				
				for(int k=0; k<8; k++)
				{
					if(k%2 == 0)
					{
						for(int n=1; n<8; n+=2)
						{
							if(n==1)m += "B";
							if(n==3)m += "D";
							if(n==5)m += "F";
							if(n==7)m += "H";
							if(k==0)m+="1";
							if(k==2)m+="3";
							if(k==4)m+="5";
							if(k==6)m+="7";
							//sets spot of space to move to
							if(is_legal(m))
							{
								if(jump == true)
								{
									if(i != k+1 && i != k-1 && j != n+1 && j != n-1)
									moves.push(m);
								}
								if(i != k+1 && i != k-1 && j != n+1 && j != n-1)
								{
									jump = true;
									while(!moves.empty())
										moves.pop();
									moves.push(m);
								}
								else
								{
									moves.push(m);
				
								}
							}
							m = m.substr(0,2);
						}
					}
					else
					{
						for(int n=0; n<8; n+=2)
						{
							if(n==0)m += "A";
							if(n==2)m += "C";
							if(n==4)m += "E";
							if(n==6)m += "G";	
							if(k==1)m+="2";
							if(k==3)m+="4";
							if(k==5)m+="6";
							if(k==7)m+="8";
							//sets spot of space to move to
							if(is_legal(m))
							{
								if(jump == true)
								{
									if(i != k+1 && i != k-1 && j != n+1 && j != n-1)
									moves.push(m);
								}
								if(i != k+1 && i != k-1 && j != n+1 && j != n-1)
								{
									jump = true;
									while(!moves.empty())
										moves.pop();
									moves.push(m);
								}
								else
								{
									moves.push(m);
				
								}
							}
							m = m.substr(0,2);
						}
					}
				}
			}
		}
	}
	}
	else if(next_mover() == COMPUTER)
	{
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<8; j++)
		{
			if(board[i][j].is_occupied() && board[i][j].get_color() == "red")
			{
				m = "";
				if(j==0)m+="A";
				if(j==1)m+="B";
				if(j==2)m+="C";
				if(j==3)m+="D";
				if(j==4)m+="E";
				if(j==5)m+="F";
				if(j==6)m+="G";
				if(j==7)m+="H";
				if(i==0)m+="1";
				if(i==1)m+="2";
				if(i==2)m+="3";
				if(i==3)m+="4";
				if(i==4)m+="5";
				if(i==5)m+="6";
				if(i==6)m+="7";
				if(i==7)m+="8";
				//sets spot of piece
				
				for(int k=0; k<8; k++)
				{
					if(k%2 == 0)
					{
						for(int n=1; n<8; n+=2)
						{
							if(n==1)m += "B";
							if(n==3)m += "D";
							if(n==5)m += "F";
							if(n==7)m += "H";
							if(k==0)m+="1";
							if(k==2)m+="3";
							if(k==4)m+="5";
							if(k==6)m+="7";
							//sets spot of space to move to
							if(is_legal(m))
							{
								if(jump == true)
								{
									if(i != k+1 && i != k-1 && j != n+1 && j != n-1)
									moves.push(m);
								}
								if(i != k+1 && i != k-1 && j != n+1 && j != n-1)
								{
									jump = true;
									while(!moves.empty())
										moves.pop();
									moves.push(m);
								}
								else
								{
									moves.push(m);
					
								}
							}
							m = m.substr(0,2);
						}
					}
					
					
					else
					{
						for(int n=0; n<8; n+=2)
						{
							if(n==0)m += "A";
							if(n==2)m += "C";
							if(n==4)m += "E";
							if(n==6)m += "G";	
							if(k==1)m+="2";
							if(k==3)m+="4";
							if(k==5)m+="6";
							if(k==7)m+="8";
							//sets spot of space to move to
							if(is_legal(m))
							{
								if(jump == true)
								{
									if(i != k+1 && i != k-1 && j != n+1 && j != n-1)
									moves.push(m);
								}
								if(i != k+1 && i != k-1 && j != n+1 && j != n-1)
								{
									jump = true;
									while(!moves.empty())
										moves.pop();
									moves.push(m);
								}
								else
								{
									moves.push(m);
				
								}
							}
							m = m.substr(0,2);
						}
					}
				}
			}
		}
	}
	}
}











int Checkers::evaluate()const
{
	//compute all moves then go through each move and see which is best
	//if there are jumps available which jumps the most people
	int eval = 0;
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<8; j++)
		{
			if(board[i][j].is_occupied())
			{
				if(board[i][j].get_color() == "red")
					if(board[i][j].is_king())
						eval+=2;
					else
						eval++;
				else
					if(board[i][j].is_king())
						eval-=2;
					else
						eval--;
			}
		}
	}
	return eval;
}


}
