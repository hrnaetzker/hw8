// File: game.cxx
/*
Hannah Naetzker
CS 2401
Game Implementation Class given to us
*/

#include <cassert>    // Provides assert
#include <climits>    // Provides INT_MAX and INT_MIN
#include <iostream>   // Provides cin, cout
#include <queue>      // Provides queue<string>
#include <string>     // Provides string
#include <cstring>
#include "game.h"     // Provides definition of game class
#include "checkers.h"
#include "piece.h"
#include "colors.h"
using namespace std;

namespace main_savitch_14
{
    //*************************************************************************
    // STATIC MEMBER CONSTANTS
    // const int game::SEARCH_LEVELS;
    
    //*************************************************************************
    // PUBLIC MEMBER FUNCTIONS

    game::who game::play( )
    // The play function should not be overridden. It plays one round of the
    // game, with the human player moving first and the computer second.
    // The return value is the winner of the game (or NEUTRAL for a tie).
    {
	restart( );
	
	while (!is_game_over( ))
	{
	    display_status( );
	    if (last_mover( ) == COMPUTER)
		make_human_move( );
	    else
		make_computer_move( );
	}
	display_status( );
	display_message("GAME OVER\n");
	if(move_number %2 == 0)
			display_message("CONGRATS PLAYER\n");
		else
			display_message("SORRY COMPUTER WON\n");
	return HUMAN;
    }


    
    //*************************************************************************
    // OPTIONAL VIRTUAL FUNCTIONS (overriding these functions is optional)

    void game::display_message(const string& message) const
    {
	cout << message;
    }

    string game::get_user_move( ) const
    {
	string answer;
	
	display_message("Your move, please (ex. A6B5, a6b5): ");
	cin >> answer;
	return answer;
    }

    game::who game::winning( ) const
    {
	int value = evaluate( ); // Evaluate based on move that was just made.

	if (value > 0)
	    return last_mover( );
	else if (value < 0)
	    return next_mover( );
	else
	    return NEUTRAL;
    }



    //\*************************************************************************
    // PRIVATE FUNCTIONS (these are the same for every game)

    int game::eval_with_lookahead(int look_ahead, int beat_this)
    // Evaluate a board position with lookahead.
    // --int look_aheads:  How deep the lookahead should go to evaluate the move.
    // --int beat_this: Value of another move that we?re considering. If the
    // current board position can't beat this, then cut it short.
    // The return value is large if the position is good for the player who just
    // moved. 
    {
    	queue<string> moves;   // All possible opponent moves
	int value;             // Value of a board position after opponent moves
    	int best_value;        // Evaluation of best opponent move
    	game* future;          // Pointer to a future version of this game
	
        // Base case:
	if (look_ahead == 0 || is_game_over( ))
	{
	    if (last_mover( ) == COMPUTER)
	            return evaluate( );
	    else
		return -evaluate( );
	}

        // Recursive case:
        // The level is above 0, so try all possible opponent moves. Keep the
	// value of the best of these moves from the opponent's perspective.
    	compute_moves(moves); 
		assert(!moves.empty( ));
    	best_value = INT_MIN;
    	while (!moves.empty( ))
    	{
	    future = clone( );
	    future->make_move(moves.front( ));
	    value = future->eval_with_lookahead(look_ahead-1, best_value);
	    delete future;
	    if (value > best_value)
	    {
		if (-value <= beat_this)
		    return INT_MIN + 1; // Alpha-beta pruning
		best_value = value;
	    }
	    moves.pop( );
    	}

    	// The value was calculated from the opponent's perspective.
    	// The answer we return should be from player's perspective, so multiply times -1:
    	return -best_value;
    }

    void game::make_computer_move( )
    {
	queue<string> moves;
	int value;
	int best_value;
	string best_move;
	game* future;
	
	// Compute all legal moves that the computer could make.
	compute_moves(moves);
	//assert(!moves.empty( ));
	
	// Evaluate each possible legal move, saving the index of the best
	// in best_index and saving its value in best_value.
	best_value = INT_MIN;
	while (!moves.empty( ))
	{
	    future = clone( );
	    future->make_move(moves.front( ));
	    value = future->eval_with_lookahead(SEARCH_LEVELS, best_value);
	    delete future;
	    if (value >= best_value)
	    {
		best_value = value;
		best_move = moves.front( );
	    }
	    moves.pop( );
	}
	    
	// Make the best move.
	cout << "best move " << best_move << endl;
	make_move(best_move);
    }

    void game::make_human_move( )
    {
        string move;
	string mov = "";
	bool m = false;
	std::queue<std::string>moves;
	while(!moves.empty())
		moves.pop();
		display_message("When jumping please put end destination\n");
		display_message("For list of possible moves type \"list\"\n");

		//made so that user could see possible moves
		//also checks here if move is one of possible moves
		while(m == false)
		{	
			move = "";	
			mov.clear();
			move = get_user_move( );
			compute_moves(moves);
			if(move == "list")
			{
				cout << "Possible Moves: \n";
				while(!moves.empty())
				{
					cout << moves.front() << endl;
					moves.pop();
				}
			}
			else
			{
			mov+=(toupper(move[0]));
			mov+=move[1];	
			mov+=(toupper(move[2]));
			mov+=move[3];	
			while(!moves.empty())
			{	cout << moves.front() << endl;
				if(mov == moves.front())
				{
					m = true;
				}
				moves.pop();
			}
			if(m == false)
				display_message("Illegal move.\n");
			}
		}
		make_move(move);
    }

}

	

