#include <iostream>

#define VISITED -1

using namespace std;

int BOARD_SIZE;
int board[20][20];

void mark_move(int square_x, square_y) {

	board[square_x][square_y] = VISITED;

}

int main(int argc, char *argv[]) {

	int num_of_marked_square, square_x, square_y;

	cin>>BOARD_SIZE;
	
	cin>>num_of_marked_square;
	for(int i=0; i<num_of_marked_square; i++) {
		cin>>square_x>>square_y;
		mark_move(square_x, square_y);
	}

	return 0;
}
