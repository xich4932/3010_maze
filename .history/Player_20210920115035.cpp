#include<iostream>
#include<cstring>
#include<cmath>

#include"Player.h"

Player::Player(const std::string name, const bool is_human){
    name_ = name;
    is_human_ = is_human;
    if(is_human){
        pos_.col = 0;
        pos_.row = 0;
    }
}

void Player::enemyStrategy(){
    int turn = rand() % 1;
}

