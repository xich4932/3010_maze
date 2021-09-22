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
std::vector<std::string>  Player::ToRelativePosition(Position other){
    std::vector<std::string> tmp;
    if(pos_.row < other.row){
       tmp.push_back("RIGHT");
    }else if(pos_.row > other.row){
        tmp.push_back("LEFT");
       // s += "LEFT";
    }
    if(pos_.col < other.col){
        tmp.push_back("UP");
        //s += "UP";
    }else if(pos_.col > other.col){
        tmp.push_back("DOWN");
        //s += "DOWN";
    }
    //std::cout << "S: " <<  s <<std::endl;
    return tmp;
}


