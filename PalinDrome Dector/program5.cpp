/***********************************
 *Program:Connect four
 *Author:Chia-Ling Hu
 **********************************/
#include<iostream>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>

using namespace std;
int valid_num_player(string);
int valid_row(string);
int valid_col(string);
char** create_board(int,int);
void print_board(char**,int,int);
void emptyboard(char**,int,int);
bool has_empty_space(char**,int,int);
void change_turn(int*);
void good_put_twoplayer(char**,int,int,int*);
bool check_win(char**,int,int);
bool is_all_filled(char**,int,int);
void good_put_oneplayer(char**,int,int);

//check if the player num is valid
int valid_num_player(string playernum_str){
	while(playernum_str!="1"&& playernum_str!="2"){
		cout<<"Invalid player number!" <<endl;
		cout <<"Enter number of players: ";
		getline(cin,playernum_str);
	}
	return atoi(playernum_str.c_str());
}
//check if the row is valid
int valid_row(string row_str){
	int row = atoi(row_str.c_str());
	while(row>20 || row<4){
		cout <<"Invalid number of row!" <<endl;
		cout <<"Enter number of row: ";
		getline(cin,row_str);
		row = atoi(row_str.c_str());
	}
	return row;
}
//check if the column is valid
int valid_col(string col_str){
	int col = atoi(col_str.c_str());
	while(col>20 || col<4){	
		cout <<"Invalid number of col!" <<endl;
		cout <<"Enter number of col: ";
		getline(cin,col_str);
		col = atoi(col_str.c_str());
	}
	return col;
}
//create the board based with row and column size
char** create_board(int row, int col){
	char** b;
	b = new char *[row];
	for(int i=0;i<row;i++){
		b[i] = new char[col];
	}
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			b[i][j]=' ';
		}
	}
	return b;
}
//print the board
void print_board(char** board, int row, int col){
	for(int i=0;i<col;i++){
		cout << "  " << i+1 <<" ";
	}
	cout <<endl;
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			if(i%2==0 && j%2==0){
				cout <<"|\033[30;47m " << board[i][j] << " ";
			}
			else if (i%2 ==1 && j%2 ==1){
				cout << "|\033[30;47m " << board[i][j] << " ";
			}
			else {
				cout <<"|\033[0m " << board[i][j] << " ";
			}
			cout << "\033[0m";
		}
		cout <<endl;
	}
}
//set the board to empty
void emptyboard(char** b,int row, int col){
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			b[i][j]=' ';
		}
	}
}
//check if any empty space in choosen col
bool has_empty_space(char** b,int row, int col){
	for(int i=0;i<row;i++){
		if(b[i][col-1]==' '){
			return true;
		}
	}
	//cout <<"No empty space for this col" << endl;
	return false;
}
//change playerturn 
void change_turn(int *playerturn){
	if(*playerturn == 1){
		*playerturn = 2;
	}
	else{
		*playerturn = 1;
	}
}
//two player mood
void good_put_twoplayer(char** b,int row,int col,int* playerturn){
	int input_col;
	while(check_win(b,row,col)==false && is_all_filled(b,row,col)==false){
		if(*playerturn==1){		
			do{
				cout <<"Which cols do you want to choose(p1): ";
				cin >> input_col;
			}while(input_col<=0 || input_col >col || has_empty_space(b,row,input_col)==false);
			for(int i=row-1;i>=0;i--){
				if(b[i][input_col-1]==' '){
					b[i][input_col-1]='X';
					break;
				}	
			}
			print_board(b,row,col);
			if(check_win(b,row,col)==true){
				cout <<"Player 1 wins" <<endl;
				break;
			}
			else{
				change_turn(playerturn);
			}
		}
		else if(*playerturn==2){
			do{
				cout <<"Which cols do you want to choose(p2): ";
				cin >> input_col;
			}while(input_col<=0 || input_col >col || has_empty_space(b,row,input_col)==false);
			for(int i=row-1;i>=0;i--){
				if(b[i][input_col-1]==' '){
					b[i][input_col-1]='O';
					break;
				}	
			}
			print_board(b,row,col);
			if(check_win(b,row,col)==true){
				cout <<"Player 2 wins" <<endl;
				break;
			}
			else{
				change_turn(playerturn);
			}
		}
	}
}
//one player mood
void good_put_oneplayer(char** b,int row,int col,int* playerturn){
	int input_col,random_col;
	while(check_win(b,row,col)==false && is_all_filled(b,row,col)==false){
		if(*playerturn==1){		
			do{
				cout <<"Which cols do you want to choose: ";
				cin >> input_col;
			}while(input_col<=0 || input_col >col || has_empty_space(b,row,input_col)==false);
			for(int i=row-1;i>=0;i--){
				if(b[i][input_col-1]==' '){
					b[i][input_col-1]='X';
					break;
				}	
			}
			print_board(b,row,col);
			if(check_win(b,row,col)==true){
				cout <<"You win" <<endl;
				break;
			}
			else{
				change_turn(playerturn);
			}
		}
		else if(*playerturn==2){
			do{
				srand(time(NULL));
				random_col = rand()%col+1;
			}
			while(random_col<=0 || random_col >col || has_empty_space(b,row,random_col)==false);
			cout <<" Computer choose col " << random_col <<  endl;
			for(int i=row-1;i>=0;i--){
				if(b[i][random_col-1]==' '){
					b[i][random_col-1]='O';
					break;
				}	
			}
			print_board(b,row,col);
			if(check_win(b,row,col)==true){
				cout <<"Computer wins" <<endl;
				break;
			}
			else{
				change_turn(playerturn);
			}
		}
	}
}
// check if any player wins the game
bool check_win(char** b,int row, int col){
	//rows
	for(int i=0;i<row;i++){
		for(int j=0;j+3<col;j++){
			if(b[i][j]==b[i][j+1]&&b[i][j]==b[i][j+2]&&b[i][j]==b[i][j+3]&&(b[i][j]=='X'||b[i][j]=='O')){
				return true;
			}
		}
	}
	//cols	
	for(int j=0;j<col;j++){
		for(int i=0;i+3<row;i++){
			if(b[i][j]==b[i+1][j]&&b[i][j]==b[i+2][j]&&b[i][j]==b[i+3][j]&&(b[i][j]=='X'||b[i][j]=='O')){
				return true;
			}
		}
	}
	//digonals up left to down right
	for(int i=0;i+3<row;i++){
		for(int j=0;j+3<col;j++){
			if(b[i][j]==b[i+1][j+1]&&b[i][j]==b[i+2][j+2]&&b[i][j]==b[i+3][j+3]&&(b[i][j]=='X'||b[i][j]=='O')){
				return true;
			}
		}
	}
	// dignoals up right to down left
	for(int i=row-1;i>=3;i--){
		for(int j=0;j+3<col;j++){
			if(b[i][j]==b[i-1][j+1]&&b[i][j]==b[i-2][j+2]&&b[i][j]==b[i-3][j+3]&&(b[i][j]=='X'||b[i][j]=='O')){
				return true;
			}
		}
	}

	return false;
}
//check if all space is filled
bool is_all_filled(char** b ,int row, int col){
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++){
			if(b[i][j]==' '){
				return false;
			}
		}
	}
	return true;
}

int main(int argc, char*argv[]){
	int playernum,row,col;
	char **board;
	if(argc!=4){
		cout<<"Too many or few argument,please try again"<<endl;
		return -1;
	}
	else{
		playernum = valid_num_player(argv[1]);
		row = valid_row(argv[3]);
		col = valid_col(argv[2]);

	}
	board = create_board(row,col);
	print_board(board,row,col);
	emptyboard(board,row,col);
	int playerturn = 1;
	switch(playernum){
		case 1: 
			good_put_oneplayer(board,row,col,&playerturn);
			break;
		case 2:
			good_put_twoplayer(board,row,col,&playerturn);
			break;
	}
	if(is_all_filled(board,row,col)&&(check_win(board,row,col)==false)){
		cout <<"It's tie" << endl;
	}
	for(int i=0;i<row;i++){
		delete [] board[i];
	}
	delete [] board;
	
	return 0;
}

