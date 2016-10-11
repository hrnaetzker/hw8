/*
Hannah Naetzker
CS 2401
Final Checkers Project
Checkers Definition Class
Sets up checkers board and game
*/

#include "piece.h"
#include "colors.h"

#ifndef CHECKERS_H
#define CHECKERS_H

#include "game.h"

namespace main_savitch_14
{

class Checkers : public game
{
	public:
		Checkers();	//Constructor
		void restart();
		void display_status()const;
		bool is_legal(const std::string& move)const;
		void make_move(const std::string& move);

		game* clone()const;
		void compute_moves(std::queue<std::string>& moves)const;
		int evaluate()const;
		
		//Help Functions I decided to include
		void print_black_occupied(const Piece& p)const;
		void print_red_occupied(const Piece& p)const;
		void delete_piece(int row, int col);
		bool is_jump(const std::string& move)const;

		bool is_game_over( ) const;
	private:
		//Variables
		Piece board[8][8];
};

}

#endif
