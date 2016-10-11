#ifndef PIECE_H
#define PIECE_H

#include <string>

using namespace std;

namespace main_savitch_14
{

class Piece
{
	public:
		Piece(){occupied = false; color = ""; king = false;}
		bool is_occupied()const{return occupied;}
		void set_occupied(bool o){occupied = o;}
		string get_color()const{return color;}
		void set_color(string c){color = c;}
		bool is_king()const{return king;}
		void set_king(bool k){king = k;}
	private:
		bool occupied;
		string color;
		bool king;
		
};

}

#endif
