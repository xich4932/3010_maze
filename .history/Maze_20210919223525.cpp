#include<iostream>
#include<vector>
#include<cstdlib>
#include<array>
#include"Maze.h"
#include<time.h>
//using namespace std;
//return true when the path is not in the vector
bool checkInPath(const int num, const std::vector<int> &vec){
    for(int d =0; d < vec.size(); d++){
        if(vec[d] == num) return true;
    }
    return false;
}


Board::Board(){
	rows_ = 4;
    cols_ = 4;
    generate();
}

Board::Board(int r, int c){
    rows_ = r;
    cols_ = c;
    generate();
}

void Board::displayUpdated(){
    for(int i = 0; i < rows_; i++){
        for(int d = 0; d < cols_; d++){
            if(checkInPath(4*i +d, path)){
                std::cout<< "*";
            }else{
                std::cout << "+" ;
            }
            
        }
        std::cout << std::endl;
	}
}

Maze::Maze(int r, int c){
    //generate (board_);
    Board *new_board = new Board(r, c);
}

std::vector<int> getDirection(int r, int c, int max_r, int max_c){
                        //{col,row} up left down right
    //int direction[4][2] ={{1,0},{0,1},{-1,0},{0,-1}};
    std::vector< int > ret;
    ret.push_back(-max_r); //up
    ret.push_back(1); //right
    ret.push_back(max_r); //down
    ret.push_back({-1}); //left
    if(r == 0){
        ret.erase(ret.begin()+3);
    }else if(r == max_r - 1){
        ret.erase(ret.begin()+1);
    }
    if(c == 0){
        ret.erase(ret.begin());
    }else if(c == max_c - 1){
        ret.erase(ret.begin()+2);
    }
    return ret;
}

void printer(std::vector<int> pri){
    for(int i  =0 ; i< pri.size(); i++){
        std::cout << pri[i] <<" ";
    }
    std::cout << std::endl;
}

void printer1(std::vector<std::array<int, 2>> pri){
    for(int d =0; d < pri.size(); d++){
        std::cout<<pri[d][0] <<" " << pri[d][1] <<std::endl;
    }
        
}


bool Board::generate(){ 
    int max_step = 1; //max step to reach exit is 8
    int visited[cols_][rows_];
    //vector<int> path;
    path.push_back(0);
    srand((unsigned ) time(NULL));
    int max = rows_ * cols_;
    visited[0][0] = 1;
    int start_r = 0;
    int start_c = 0;
    int end_c = cols_ - 1;
    int end_r = rows_ - 1;
    while(start_r != end_r && start_c != end_c && path.size() < 13 && max_step < 16){
        std::vector<std::array<int,2>> direction = getDirection(start_r, start_c, rows_, cols_);
        //printer1(direction);
        
        int curr = rand()%direction.size();
        std::cout << curr << std::endl;
        int temp_r = start_r + direction[curr][1];
        int temp_c = start_c + direction[curr][0];
        for(int r =0; r < cols_; r++){
            for(int y =0; y < rows_; y++){
                if(r == temp_c && y == temp_r){
                    std::cout << "2" << " ";
                }else{
                    std::cout << visited[r][y] << " ";
                }
                
            }
            std::cout << std::endl;
        }

        std::cout << direction[curr][0] << " " << direction[curr][1] << std::endl;
        if(visited[start_c + direction[curr][0]][start_r + direction[curr][1]]) continue;
        path.push_back(cols_*(start_c + direction[curr][0]) + start_r + direction[curr][1]);
       //max_step ++;
        
        start_c += direction[curr][0];
        start_r += direction[curr][1];
        visited[start_c][start_r] = 1;
        max_step ++;
        direction.clear();
        displayUpdated();
    }
    printer(path);
    if(start_r == end_r && start_c == end_c) return true;
    return false;
}

