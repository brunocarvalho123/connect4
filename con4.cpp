/*
 * Made by Bruno Carvalho 	201508043  FCUP
*/

#include <iostream>
#include <list>
#include <climits>
#include <string>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>
#include <ctime>

using namespace std;

struct node {
	int depth;
	char config[6][7];
	bool isMax;
	int move;
};

void addIni(char inicial[6][7], node *&head){
	node *temp = new node;
	memcpy(temp->config, inicial, sizeof(temp->config));
	temp->depth = 0;
	temp->isMax = true;
	temp->move=1;
	head = temp;
}

node *add(char matriz[6][7], node *&pai, int move) {
	node *temp = new node;
	memcpy(temp->config, matriz, sizeof(temp->config));
	temp->depth = 1 + pai->depth;
	if(pai->isMax) temp->isMax=false;
	else temp->isMax=true;
	temp->move=move;
	return temp;
}

list<node*> q;		//list to queue the first nodes
list<node*> qq;		//list to queue the max nodes
list<node*> qqq;	//list to queue the min nodes


void remove(node *&head){
	if(head!=NULL)	delete head;
}

//checks final solution
bool isSolution(char config[6][7]){

	int nrX=0, nrO=0;

	for(int i=5; i>=0; i--){
		for(int j=6; j>=0; j--){
			//check horizontal
			if(j<4){
				for(int k=j; k<j+4; k++){
					if(config[i][k]!='X'){
						k=10;
						nrX--;
					}
					nrX++;
				}
				if (nrX==4) return true;
				for(int k=j; k<j+4; k++){
					if(config[i][k]!='O'){
						k=10;
						nrO--;
					}
					nrO++;
				}
				if (nrO==4) return true;
			}
			nrX=0; nrO=0;

			//check vertical
			if(i<3){
				for(int k=i; k<i+4; k++){
					if(config[k][j]!='X'){
						k=10;
						nrX--;
					}
					nrX++;
				}
				if (nrX==4) return true;
				for(int k=i; k<i+4; k++){
					if(config[k][j]!='O'){
						k=10;
						nrO--;
					}
					nrO++;
				}
				if (nrO==4) return true;
			}
			nrX=0; nrO=0;

			//check right diagonal
			if(i<3 && j<4){
				int l=j;
				for(int k=i; k<i+4; k++){
					if(config[k][l]!='X'){
						k=10;
						nrX--;
					}
					l++;
					nrX++;
				}
				if (nrX==4) return true;

				l=j;
				for(int k=i; k<i+4; k++){
					if(config[k][l]!='O'){
						k=10;
						nrO--;
					}
					l++;
					nrO++;
				}
				if (nrO==4) return true;
			}
			nrX=0; nrO=0;

			//check left diagonal
			if(i<3 && j>2){
				int l=j;
				for(int k=i; k<i+4; k++){
					if(config[k][l]!='X'){
						k=10;
						nrX--;
					}
					l--;
					nrX++;
				}
				if (nrX==4) return true;

				l=j;
				for(int k=i; k<i+4; k++){
					if(config[k][l]!='O'){
						k=10;
						nrO--;
					}
					l--;
					nrO++;
				}
				if (nrO==4) return true;
			}
			nrX=0; nrO=0;
		}
	}
	return false;
}

//checks if node is a leaf
bool isSolution2(char config[6][7]){

	int nrX=0, nrO=0;
	
	for(int i=5; i>=0; i--){
		for(int j=6; j>=0; j--){
			//check horizontal
			if(j<4){
				for(int k=j; k<j+4; k++){
					if(config[i][k]!='X'){
						k=10;
						nrX--;
					}
					nrX++;
				}
				if (nrX==4) return true;
				for(int k=j; k<j+4; k++){
					if(config[i][k]=='-'){
						if(i<5 && config[i+1][k] == '-'){
							k=10;
							nrO=-1;
						}
						else nrO--;
					}
					else if(config[i][k]=='X'){
						k=10;
						nrO=-1;
					}
					nrO++;
				}
				if (nrO>2) return true;
			}
			nrX=0; nrO=0;

			//check vertical
			if(i<3){
				for(int k=i; k<i+4; k++){
					if(config[k][j]!='X'){
						k=10;
						nrX--;
					}
					nrX++;
				}
				if (nrX==4) return true;
				for(int k=i; k<i+4; k++){
					if(config[k][j]=='-'){
						nrO--;
					}
					else if(config[k][j]=='X'){
						k=10;
						nrO=-1;
					}
					nrO++;
				}
				if (nrO>2) return true;
			}
			nrX=0; nrO=0;

			//check right diagonal
			if(i<3 && j<4){
				int l=j;
				for(int k=i; k<i+4; k++){
					if(config[k][l]!='X'){
						k=10;
						nrX--;
					}
					l++;
					nrX++;
				}
				if (nrX==4) return true;

				l=j;
				for(int k=i; k<i+4; k++){
					if(config[k][l]=='-'){
						if(k<5 && config[k+1][l] == '-'){
							k=10;
							nrO=-1;
						}
						else nrO--;
					}
					else if(config[k][l]=='X'){
						k=10;
						nrO=-1;
					}
					l++;
					nrO++;
				}
				if (nrO>2) return true;
			}
			nrX=0; nrO=0;

			//check left diagonal
			if(i<3 && j>2){
				int l=j;
				for(int k=i; k<i+4; k++){
					if(config[k][l]!='X'){
						k=10;
						nrX--;
					}
					l--;
					nrX++;
				}
				if (nrX==4) return true;

				l=j;
				for(int k=i; k<i+4; k++){
					if(config[k][l]=='-'){
						if(k<5 && config[k+1][l] == '-'){
							k=10;
							nrO=-1;
						}
						else nrO--;
					}
					else if(config[k][l]=='X'){
						k=10;
						nrO=-1;
					}
					l--;
					nrO++;
				}
				if (nrO>2) return true;
			}
			nrX=0; nrO=0;
		}
	}
	return false;
}

//board evaluation function
int eval(char config[6][7]){

	int nrX=0, nrO=0, val=0, flag1=0, flag2=0;

	for(int i=5; i>=0; i--){
		for(int j=6; j>=0; j--){
			//check horizontal
			if(j<4){
				for(int k=j; k<j+4; k++){
					if(config[i][k]=='-'){
						nrX--;
					}
					else if(config[i][k]=='O'){
						k=10;
						nrX=-1;
					}
					nrX++;
				}

				if (nrX==4) flag1++;
				else if (nrX==3) val=val+50;
				else if (nrX==2) val=val+10;
				else if (nrX==1) val++;

				for(int k=j; k<j+4; k++){
					if(config[i][k]=='-'){
						if(i<5 && config[i+1][k] == '-'){
							k=10;
							nrO=-1;
						}
						else nrO--;
					}
					else if(config[i][k]=='X'){
						k=10;
						nrO=-1;
					}
					nrO++;
				}
				if (nrO>2) flag2++;
				else if (nrO==2) val=val-50;
				else if (nrO==1) val=val-5;
			}
			nrX=0; nrO=0;

			//check vertical
			if(i<3){
				for(int k=i; k<i+4; k++){
					if(config[k][j]=='-'){
						nrX--;
					}
					else if(config[k][j]=='O'){
						k=10;
						nrX=-1;
					}
					nrX++;
				}
				if (nrX==4) flag1++;
				else if (nrX==3) val=val+50;
				else if (nrX==2) val=val+10;
				else if (nrX==1) val++;

				for(int k=i; k<i+4; k++){
					if(config[k][j]=='-'){
						nrO--;
					}
					else if(config[k][j]=='X'){
						k=10;
						nrO=-1;
					}
					nrO++;
				}
				if (nrO>2) flag2++;
				else if (nrO==2) val=val-50;
				else if (nrO==1) val=val-5;
			}
			nrX=0; nrO=0;

			//check right diagonal
			if(i<3 && j<4){
				int l=j;
				for(int k=i; k<i+4; k++){
					if(config[k][l]=='-'){
						nrX--;
					}
					else if(config[k][l]=='O'){
						k=10;
						nrX=-1;
					}
					l++;
					nrX++;
				}
				if (nrX==4) flag1++;
				else if (nrX==3) val=val+50;
				else if (nrX==2) val=val+10;
				else if (nrX==1) val++;

				l=j;
				for(int k=i; k<i+4; k++){
					if(config[k][l]=='-'){
						if(k<5 && config[k+1][l] == '-'){
							k=10;
							nrO=-1;
						}
						else nrO--;
					}
					else if(config[k][l]=='X'){
						k=10;
						nrO=-1;
					}
					l++;
					nrO++;
				}
				if (nrO>2) flag2++;
				else if (nrO==2) val=val-50;
				else if (nrO==1) val=val-5;
			}
			nrX=0; nrO=0;

			//check left diagonal
			if(i<3 && j>2){
				int l=j;
				for(int k=i; k<i+4; k++){
					if(config[k][l]=='-'){
						nrX--;
					}
					else if(config[k][l]=='O'){
						k=10;
						nrX=-1;
					}
					l--;
					nrX++;
				}
				if (nrX==4) flag1++;
				else if (nrX==3) val=val+50;
				else if (nrX==2) val=val+10;
				else if (nrX==1) val++;

				l=j;
				for(int k=i; k<i+4; k++){
					if(config[k][l]=='-'){
						if(k<5 && config[k+1][l] == '-'){
							k=10;
							nrO=-1;
						}
						else nrO--;
					}
					else if(config[k][l]=='X'){
						k=10;
						nrO=-1;
					}
					l--;
					nrO++;
				}
				if (nrO>2) flag2++;
				else if (nrO==2) val=val-50;
				else if (nrO==1) val=val-5;
			}
			nrX=0; nrO=0;
		}
	}

	if (flag1!=0) return val+512*flag1;
	else if(flag2!=0) return val-512*flag2;
	else return val;
}

void makeDesc(node *nodeT){
	char board[6][7];
	memcpy(board, nodeT->config, sizeof(board));
	int move;
	for(int j=0; j<7; j++){
		for(int i=5; i>=0; i--){
			if (board[i][j] == '-' && nodeT->isMax){
				board[i][j] = 'X';
				move=j+1;
				qq.push_front(add(board, nodeT, move));
				board[i][j] = '-';
				i=-1;
			}
			else if (board[i][j] == '-' && !nodeT->isMax){
				board[i][j] = 'O';
				move=j+1;
				qqq.push_front(add(board, nodeT, move));
				board[i][j] = '-';
				i=-1;
			}
		}
	}
}

//makes the descendents for the first nodes
void makeDesc2(node *nodeT){
	char board[6][7];
	memcpy(board, nodeT->config, sizeof(board));
	int move;

	for(int j=0; j<7; j++){
		for(int i=5; i>=0; i--){
			if (board[i][j] == '-'){
				board[i][j] = 'X';
				move=j+1;
				q.push_front(add(board, nodeT, move));
				board[i][j] = '-';
				i=-1;
			}
		}
	}
}

void printBoard(char board[6][7], int jogada){

	cout << "1 2 3 4 5 6 7\n";

	for(int i=0; i<6; i++){
		for(int j=0; j<7; j++){
			if(board[i][j] == 'X')
				cout <<"\033[1;31m" << board[i][j] << "\033[0m"  << " ";
			else if(board[i][j] == 'O')
				cout <<"\033[1;34m" << board[i][j] << "\033[0m"  << " ";
			else
				cout << board[i][j] << " ";
		}
		cout << endl;
	}
	if(jogada != 0){
		for(int i=0; i<7; i++){
			if(i+1==jogada) cout << "^ ";
			else cout << "  ";
		}
		cout << endl;
	}
}

//function for player v player
int playP(char board[6][7]){
	int jogada;
	cin >> jogada;
	while(jogada > 7 || jogada < 1){
		cout << "\nInvalid play!\nChoose a number between 1 and 7!\n";
		cin >> jogada;
	}

	while(board[0][jogada-1] != '-'){
		cout << "\nThere is no room in that column!\n";
		cout << "Choose a different number!\n";
		cin >> jogada;
	}
	return jogada;
}

//function for player v player
void jogoP(char board[6][7]) {
	
	int jogada=0, turno=1, n=0;

	while(!isSolution(board) && n < 42){
		
		cout << endl;
		printBoard(board, jogada);
		
		if(turno == 1){
			cout << "\nIt is now \033[1;31mX\033[0m's turn.\n";
			cout << "Make a move by choosing your coordinates to play\n";
		}
		else {
			cout << "\nIt is now \033[1;34mO\033[0m's turn.\n";
			cout << "Make a move by choosing your coordinates to play\n";
		}
		
		jogada = playP(board);
		
		for(int i=5; i>=0; i--){
			if (board[i][jogada-1] == '-' && turno==1){
				board[i][jogada-1] = 'X';
				i=-1;
			}
			else if (board[i][jogada-1] == '-' && turno==-1){
				board[i][jogada-1] = 'O';
				i=-1;
			}
		}
		
		turno = turno*-1;
		n++;
	}
	
	if (n == 42) cout << "\nDraw!\n\n";
	else if (turno > 0) cout << "\n\033[1;34mO\033[0m wins!\n\n";
	else if (turno < 0) cout << "\n\033[1;31mX\033[0m wins!\n\n";
	
	printBoard(board, jogada);
}

//checks if the board is full
int nPlays(char config[6][7]){
	for(int i=0; i<6; i++){
		for(int j=0; j<7; j++){
			if(config[i][j] == '-') return 0;
		}
	}
	return 1;
}

int minimax(node *head, int maxD){
	int bestVal;

	if(isSolution2(head->config)){
		return eval(head->config)/(head->depth);
	}

	if(nPlays(head->config)==1) return 0;

	if(head->depth>maxD){
		return eval(head->config)/(head->depth)+16;
	}

	if(head->isMax){
		bestVal=INT_MIN;
		makeDesc(head);
		while (qq.size() > 0) {
			node *u = qq.front(); qq.pop_front();
			bestVal= max(bestVal, minimax(u,maxD));
			remove(u);
		}
		return bestVal;
	}

	else{
		bestVal=INT_MAX;
		makeDesc(head);
		while (qqq.size() > 0) {
			node *u = qqq.front(); qqq.pop_front();
			bestVal= min(bestVal, minimax(u,maxD));
			remove(u);
		}
		return bestVal;
	}
}

int alphabeta(node *head, int alpha, int beta, int maxD){
	int bestVal;

	if(isSolution2(head->config)){
		return eval(head->config)/(head->depth);
	}

	if(nPlays(head->config)==1) return 0;

	if(head->depth>maxD){
		return eval(head->config)/(head->depth)+16;
	}

	if(head->isMax){
		bestVal=INT_MIN;
		makeDesc(head);
		while (qq.size() > 0) {
			node *u = qq.front(); qq.pop_front();
			bestVal= max(bestVal, alphabeta(u, alpha, beta, maxD));
			if(bestVal >= beta){
				return bestVal;
			}
			alpha = max(alpha, bestVal);
		}
		return bestVal;
	}

	else{
		bestVal=INT_MAX;
		makeDesc(head);
		while (qqq.size() > 0) {
			node *u = qqq.front(); qqq.pop_front();
			bestVal= min(bestVal, alphabeta(u, alpha, beta, maxD));
			if(bestVal <= alpha){
				return bestVal;
			}
			beta = min(beta, bestVal);
		}
		return bestVal;
	}
}

int playAI(char board[6][7]){
	node *head = new node;
	addIni(board, head);
	makeDesc2(head);
	int bestVal=INT_MIN, temp=bestVal, bestMove;
	int maxD = 5;   //max depth
	int mode = 1;	//0 for minimax   //1 for alphabeta

	//minimax
	if(mode==0) {
		while(q.size()>0) {
			node *u = q.front(); q.pop_front();
			bestVal= max(bestVal, minimax(u, maxD));
			if(temp<bestVal){
				bestMove=u->move;
				temp=bestVal;
			}
			remove(u);
		}
	}

	//alphabeta
	else {
		while(q.size()>0){
			node *u = q.front(); q.pop_front();
			bestVal= max(bestVal, alphabeta(u, INT_MIN, INT_MAX, maxD));
			if(temp<bestVal){
				bestMove=u->move;
				temp=bestVal;
			}
			remove(u);
		}
	}
	return bestMove;
}

void jogoAI(char board[6][7], int first){
	int jogada=0, turno;

	if (first==1) turno=1;
	else if (first==2) turno=-1;
	else{
		srand(time(0));
		int v = rand() % 100;
		cout << v << endl;
		if (v>49) turno=1;
		else turno=-1;
	}

	while(!isSolution(board) && nPlays(board)!=1){

		cout << endl;
		printBoard(board, jogada);

		if(turno == 1){
			cout << "\nIt is now \033[1;31mX\033[0m's turn.\n";
			cout << "Make a move by choosing your coordinates to play\n";
			jogada = playAI(board);
		}
		else {
			cout << "\nIt is now \033[1;34mO\033[0m's turn.\n";
			cout << "Make a move by choosing your coordinates to play\n";
			if(first!=4) jogada = playP(board);
			else{
				jogada = playAI(board);
			}
		}

		for(int i=5; i>=0; i--){
			if (board[i][jogada-1] == '-' && turno==1){
				board[i][jogada-1] = 'X';
				i=-1;
			}
			else if (board[i][jogada-1] == '-' && turno==-1){
				board[i][jogada-1] = 'O';
				i=-1;
			}
		}

		turno = turno*-1;
	}

	if (nPlays(board)==1) cout << "\nDraw!\n\n";
	else if (turno > 0) cout << "\n\033[1;34mO\033[0m wins!\n\n";
	else if (turno < 0) cout << "\n\033[1;31mX\033[0m wins!\n\n";
	printBoard(board, jogada);

}

int main() {

	char config[6][7];

	for(int i=0; i<6; i++){
		for(int j=0; j<7; j++){
			config[i][j]='-';
		}
	}
	
	int resp;
	
	//AI v AI has alot of problems!
	cout << "1)P v P    2)P v AI    3)AI v AI\n";
	cin >> resp;
	int first;

	if (resp == 1) jogoP(config);
	else if(resp == 2){
		cout << "Who goes first?\n1)AI   2)Player   3)Random\n";
		cin >> first;
		while(first > 3 || first < 1){
			cout << "\nERROR\n\n";
			cout << "Who goes first?\n1)AI   2)Player   3)Random\n";
			cin >> first;
		}
		jogoAI(config, first);
	}
	else if(resp == 3){
		jogoAI(config, 4);
	}
	else cout << "ERROR\n";

	return 0;
}
