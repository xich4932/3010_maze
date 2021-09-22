#include<iostream>
#include<cstring>
#include<cmath>
#include<time.h>
#include<cstdlib>
#include<vector>
#include"Player.h"

Player::Player(const std::string name, const bool is_human){
    name_ = name;
    is_human_ = is_human;
    if(is_human){
        pos_.col = 0;
        pos_.row = 0;
    }

}


void Player::ChangePoints(const int x){
    if(is_human_){
        points_ += x;
    }
}  
// You MUST implement the following functions

// TODO: implement the following functions
// set a new position for this player
void Player::SetPosition(Position pos){
    pos_.row = pos.row;
    pos_.col = pos.col;
}

// You may want to implement these functions as well
// ToRelativePosition is a function we used to translate positions
// into directions relative to the player (up, down, etc)
/* 

*/
std::string  Player::ToRelativePosition(Position other){
    std::string s = "";
    if(pos_.row < other.row){
        s += "R";
    }else if(pos_.row > other.row){
        s += "L";
    }
    if(pos_.col < other.col){
        s += "U";
    }else if(pos_.col > other.col){
        s += "D";
    }
    std::cout << s<<std::endl;
    return s;
}
/* 
if player can only move with less than 2 direction, enemy won't attack player
in case player are blocked and no way to escape
otherwise enemy will calculate the direction of player and chase behind
 */

Position Player::enemyStrategy(std::vector<SquareType> choice, std::vector<Position> po){
    //std::string str = ToRelativePosition(pos);
    
    //Position enemy_now = pos_;
    std::cout << po.size() << std::endl;
         int i = rand()%choice.size();
    while(SquareTypeStringify(choice[i]) == "Wall" || SquareTypeStringify(choice[i]) == "Treasure" ){
        i = rand()%choice.size();
    }
    return po[i];
}

