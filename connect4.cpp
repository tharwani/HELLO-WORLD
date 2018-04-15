#include<iostream>
#include<string>
#include<cstdlib>
#include<vector>
#include<malloc.h>
#include<math.h>

using namespace std;

char player,comp;

int max(int a,int b){
	if(a>b) return a;
	else return b;
}

int min(int a,int b){
	if(a>b) return b;
	else return a;
}

void print(char**s){
	int i,j;
	for(i=0;i<6;i++){
		for(j=0;j<7;j++){
			cout << *(*(s+i)+j) << " ";
		}
		cout<<endl;
	}
	cout << " " << endl;
}

int gameOver(char **s)
{
	int i,j;
	// rows check
	for(i=0;i<6;i++){
		for(j=0;j<4;j++){
			if((*(*(s+i)+j)==*(*(s+i)+j+1))&&(*(*(s+i)+j+1)==*(*(s+i)+j+2))&&(*(*(s+i)+j+2)==*(*(s+i)+j+3))){
				if (*(*(s+i)+j)==player)  return 20;
				else if (*(*(s+i)+j)==comp) return -20;
			}
		}
	}
	// columns check
	for(j=0;j<7;j++){
		for(i=0;i<3;i++){
			if((*(*(s+i)+j)==*(*(s+i+1)+j))&&(*(*(s+i+1)+j)==*(*(s+i+2)+j))&&(*(*(s+i+2)+j)==*(*(s+i+3)+j))){
				if (*(*(s+i)+j)==player)  return 20;
				else if (*(*(s+i)+j)==comp) return -20;
			}
		}
	}
	// diagonal check
	for(i=0;i<3;i++)
	{
		for(j=0;j<4;j++)
		{
			if((*(*(s+i)+j)==*(*(s+i+1)+j+1))&&(*(*(s+i+1)+j+1)==*(*(s+i+2)+j+2))&&(*(*(s+i+2)+j+2)==*(*(s+i+3)+j+3))){
					if (*(*(s+i)+j)==player)  return 20;
					else if (*(*(s+i)+j)==comp) return -20;
			}
		}
	}
	for(i=0;i<3;i++)
	{
		for(j=6;j>2;j--)
		{
			if((*(*(s+i)+j)==*(*(s+i+1)+j-1))&&(*(*(s+i+1)+j-1)==*(*(s+i+2)+j-2))&&(*(*(s+i+2)+j-2)==*(*(s+i+3)+j-3))){
					if (*(*(s+i)+j)==player)  return 20;
					else if (*(*(s+i)+j)==comp) return -20;
			}
		}
	}
	return 0;
}
int win_block(char**s,char t)
{
	int i,j;
	for(j=0;j<7;j++){
		for(i=5;i>=0;i--){
			if(s[i][j]=='_'){
				s[i][j]=t;
				if(gameOver(s)){
					s[i][j]='_';	
					return j;
				}
				s[i][j]='_';
				break;
			}
		}
	}
	return -1;
}

int minimax(char **s,int depth,int alpha,int beta,bool turn,int d) // d is my depth of minimax
{
	if(gameOver(s)) return gameOver(s);
	if (depth==42) return 0;
	if (d==11){
		if (abs(alpha)>abs(beta)) return -40;
		else if (abs(alpha)<abs(beta)) return 40;
		return 0;
	}
	if (turn)
	{
		int v=-1000;
		int i,j;
		if(win_block(s,comp)!=-1)
		{
		        j=win_block(s,comp);
			for(i=5;i>=0;i--){
				if(*(*(s+i)+j)=='_'){
					*(*(s+i)+j)=comp;
					v=max(v,minimax(s,depth+1,alpha,beta,!turn,d+1));
					alpha=max(v,alpha);
					*(*(s+i)+j)='_';
					break;
				}
			}
			return v;
		}
		else if(win_block(s,player)!=-1)
		{
		        j=win_block(s,player);
			for(i=5;i>=0;i--){
				if(*(*(s+i)+j)=='_'){
					*(*(s+i)+j)=comp;
					v=max(v,minimax(s,depth+1,alpha,beta,!turn,d+1));
					alpha=max(v,alpha);
					*(*(s+i)+j)='_';
					break;
				}
			}
			return v;
		}
		else
		{
			for(j=0;j<7;j++){
				int f=0;
				for(i=5;i>=0;i--){
					if (*(*(s+i)+j)=='_'){
						*(*(s+i)+j)=comp;
						v=max(v,minimax(s,depth+1,alpha,beta,!turn,d+1));
						alpha=max(v,alpha);
						*(*(s+i)+j)='_';
						if(beta<=alpha){
							f=1;
							break;
						}
						break;
					}	
				}
				if(f) break;
			}
			return v;
		}
	}
	else
	{
		
		int v = 1000;
		int i,j;
		if(win_block(s,player)!=-1)
		{
		        j=win_block(s,player);
			for(i=5;i>=0;i--){
				if(*(*(s+i)+j)=='_'){
					*(*(s+i)+j)=player;
					v=min(v,minimax(s,depth+1,alpha,beta,!turn,d+1));
					beta=min(v,beta);
					*(*(s+i)+j)='_';
					break;
				}
			}
			return v;
		}
		else if(win_block(s,comp)!=-1)
		{
		        j=win_block(s,comp);
			for(i=5;i>=0;i--){
				if(*(*(s+i)+j)=='_'){
					*(*(s+i)+j)=player;
					v=min(v,minimax(s,depth+1,alpha,beta,!turn,d+1));
					beta=min(v,beta);
					*(*(s+i)+j)='_';
					break;
				}
			}
			return v;
		}
		else
		{
			for(j=0;j<7;j++){
				int f=0;
				for(i=5;i>=0;i--){
					if (*(*(s+i)+j)=='_'){
						*(*(s+i)+j)=player;
						v=min(v,minimax(s,depth+1,alpha,beta,!turn,d+1));
						beta=min(v,beta);
						*(*(s+i)+j)='_';
						if(beta<=alpha){
							f=1;
							break;
						}
						break;
					}	
				}
				if(f) break;
			}
			return v;
		}
	}
}

int bestMove(char** s,int depth){
	int i,j,v=0;
	int best=-1;
	if(win_block(s,comp)!=-1) return win_block(s,comp);
	else if(win_block(s,player)!=-1) return win_block(s,player);
	for(j=0;j<7;j++){
		for(i=5;i>=0;i--){
			if(*(*(s+i)+j)=='_'){
				*(*(s+i)+j)=comp;
				//print(s);
				int y = minimax(s,depth,-1000,1000,false,0);
				*(*(s+i)+j)='_';
				//cout << y << endl;
				if(y<v){
					best=j;
				}
				v=min(v,y);
				break;
			}
		}
	}
	//cout << best << endl;
	if(best==-1)
	{
		for(i=5;i>=0;i--){
			for(j=0;j<7;j++){
				if(s[i][j]==player){
					if(j==0){
						if(s[i][j+1]=='_') best=j+1;
						else best=j;		
					}
					else if(j==6){
						if(s[i][j-1]=='_') best=j-1;
						else best=j;
					}
					else{
						if(s[i][j+1]=='_') best=j+1;
						else if(s[i][j-1]=='_') best=j-1;
						else best=j;
					}
					break;
				}
			}
			if(best!=-1) break;
		}
	}
	return best;		
}
	
int main()
{
	char** s;
	s = (char **)malloc(6*sizeof(char *));
        int z=0;
        while(z!=6)
	{
		*(s+z)=(char *)malloc(7*sizeof(char));
		z++;
	}
	z=1;
	int i;
	for(i=0;i<6;i++){
		for(int j=0;j<7;j++){
			*(*(s+i)+j)='_';
		}
	}
	i=0;
        cout << "please choose ur colour.." << endl;
	cin >> player;
	while((player!='r')&&(player!='y')){
		cout << "wrong input try again u dumb*ss.." << endl;
		cin >> player;
	}
	comp = 'r'+'y'-player;
	int inpt;
	int out;
	while(z!=42)
	{
		if(gameOver(s)==-20){
			cout << "f u" << endl;
			break;
		}
		cout << "please enter ur column no.." << endl;
		cin >> inpt;
		while(inpt>6||inpt<0){
			cout << "sahi se daal na inpt" << endl;
			cin >> inpt;
		}
		for(i=5;i>=0;i--){
			if(*(*(s+i)+inpt)=='_'){
				*(*(s+i)+inpt)=player;
				break;
			}
		}
		i=0;
		print(s);
		z++;
		if(gameOver(s)==20){
			cout<< "congrats" << endl;
			break;
		}
		int y = bestMove(s,z);
		if(y==-1){
			cout << "thats an fu**ing error..,." << endl;
			break;
		}
		for(i=5;i>=0;i--){
			if(*(*(s+i)+y)=='_'){
				*(*(s+i)+y)=comp;
				break;
			}
		}
		print(s);
		i=0;
		z++;
	}
	return 0;
}	
