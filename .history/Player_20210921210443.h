#ifndef PLAYER_H
#define PLAYER_H
#include<iostream>
#include<vector>
#include<string>

//extern enum class SquareType;
//extern std::string SquareTypeStringify(SquareType);

struct Position {
	int row;
	int col;
	Position(): row(0), col(0) {};
	Position(int c, int r): row(r), col(c){};
	// already implemented for you!
	bool operator==(const Position &other) {
		return row == other.row && col == other.col;
	}
};


class Player {
public:
	// TODO: implement
	Player(const std::string name, const bool is_human);  // constructor
	
	// These are already implemented for you
	std::string get_name() const {return name_; }  // inline member function
	int get_points() const {return points_; }  // inline member function
	Position get_position() const {return pos_; }  // inline member function
	bool is_human() const {return is_human_; }  // inline member function


	Position enemyStrategy(std::vector<SquareType>, std::vector<Position>);
	void ChangePoints(const int x);  
	// You MUST implement the following functions

	// TODO: implement the following functions
	// set a new position for this player
	void SetPosition(Position pos);
	//
	

	// You may want to implement these functions as well
	// ToRelativePosition is a function we used to translate positions
	// into directions relative to the player (up, down, etc)
	std::vector<std::string> ToRelativePosition(Position other);

  // Either override operator<< for Player or implement the following function
	// Convert this player to a string representation of their name and points
	//std::string Stringify();

	// You may add other functions as needed/wanted

private:
	std::string name_;
	int points_ = 0;
	Position pos_;
	bool is_human_=0;

	// You may add other fields as needed

}; // class Player

#endif  // PLAYER_H
