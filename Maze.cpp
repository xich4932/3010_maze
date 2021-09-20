#include<iostream>
#include<vector>
#include"Maze.h"
using namespace std;

Board::Board(){
	rows_ = 4;
    cols_ = 4;
}

Board::Board(int r, int c){
    rows_ = r;
    cols_ = c;
}

void Board::displayUpdated(){
    for(int i = 0; i < rows_; i++){
        for(int d = 0; d < cols_; d++){
            std::cout << "⬜️" ;
        }
        std::cout << std::endl;
	}
}

Maze::Maze(){
    generate();
}

vector<int> getDirection(int r, int c, int max_r, int max_c){
                        //{col,row} up left down right
    int direction[4][2] ={{1,0},{0,1},{-1,0},{0,-1}};
    std::vector<std::array<int, 2>> ret;
    ret.push_back({1,0}); //up
    ret.push_back({0,1}); //right
    ret.push_back({-1,0}); //down
    ret.push_back({0,-1}); //left
    if(r == 0){
        ret.erase(ret.begin()+3);
    }else if(r == max_r - 1){
        ret.erase(ret.begin()+1);
    }
    if(r == 0) ret.push_back()
}

void generate(){
    visited[board_.get_cols()][board_.get_rows()];
    vevtor<int> path;
    path.push_back(0);    
                            
    
    while(path[path.size()-1] != ){
        
    }
}

