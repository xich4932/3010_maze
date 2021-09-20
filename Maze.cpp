#include<iostream>
#include<vector>
#include<cstdlib>
#include"Maze.h"
#include<time.h>
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
    if(c == 0) ret.push_back(){
        ret.erase(ret.begin());
    }else if(c == max_c - 1){
        ret.erase(ret.begin()+2);
    }
    return ret;
}

void generate(){
    visited[board_.get_cols()][board_.get_rows()];
    path.push_back(0);
    int start_r = 0;
    int start_c = 0;
    int end_c = board_.get_cols() - 1;
    int end_r = board_.get_rows() - 1;
    while(start_r != end_r && start_c != end_c){
        vevtor<int> direction = getDirection(0,0,board_.get_rows(), board_.get_cols());
        srand((unsigned ) time(NULL));
        int curr = rand()%direction.size();
        start_c +=direction[curr][0];
        start_r +=direction[curr][1];
        direction.clear();

    }

}

