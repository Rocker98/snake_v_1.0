#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

using namespace std;

bool gameOver;
const int width =20;
const int hight =20;
int x,y,fruitX,fruitY,score;
int tailX[100],tailY[100];
int nTail;
enum eDirection 
{
	STOP=0,LEFT,RIGHT,UP,DOWN
};
eDirection dir;
int main()
{
    void setup();
    void draw();
    void logic();
    void input();

        setup();
        while(!gameOver)
        {
        	draw();
            input();
            logic();
            Sleep(100);
        }
}

void setup()
{
	
    gameOver=false;
    dir=STOP;
    x=width/2;
    y=hight/2;
    srand(time(0));
    fruitX = 1+(rand()%(width-1));
    fruitY = 1+(rand()%(hight-1));
    score =0;
}

void draw()
{
	system("cls");
	for(int i=0;i<width+1;i++)
	cout<<"#";
	cout<<endl;
	
	for(int i=0;i<width;i++)
	{
		for(int j=0;j<hight;j++)
		{
			if(j==0)
			cout<<"#";
			else if(j==y&&i==x)
			cout<<"O";
			else if(j==fruitY&&i==fruitX)
			cout<<"F";
			else
			{
				bool print=false;
				for(int k=0;k<nTail;k++)
				{
					if(tailX[k]==i&&tailY[k]==j)
					{
						cout<<"o";
						print=true;
					}
				}
				if(!print)
				cout<<" ";
			} 
			if(j==hight-1)
			cout<<"#";
		}
		cout<<endl;
	}
	
	for(int i=0;i<width+1;i++)
	cout<<"#";
	cout<<endl;
	cout<<"Score :"<<score<<endl;
}

void input()
{
	if(_kbhit())
	{
		switch(_getch())
		{
			case 'a':
				dir=LEFT;
				break;
			case 'd':
				dir=RIGHT;
				break;	
			case 'w':
				dir=UP;
				break;
			case 's':
				dir=DOWN;
				break;
				
		}
		
	}

}

void logic()
{
	int prevX=tailX[0];
	int prevY=tailY[0];
	int prev2X,prev2Y;
	tailX[0]=x;
	tailY[0]=y;
	for(int i=1;i<nTail;i++)
	{
		prev2X=tailX[i];
		prev2Y=tailY[i];
		tailX[i]=prevX;
		tailY[i]=prevY;
		prevX=prev2X;
		prevY=prev2Y;		
	}
	
	switch(dir)
	{
		case LEFT:
			y--;
			break;
		case RIGHT:
			y++;
			break;	
		case UP:
			x--;
			break;
		case DOWN:
			x++;
			break;
		default:
		break;	
	}
/*	if(x<=0||x>=width||y<0||y>hight)
	gameOver=true;*/
	
	if(x<0)
	{
		x=width;
	}
	if(x>width)
	x=0;
	if(y<0)
	y=hight;
	if(y>hight)
	y=0;
	
	for(int i=0;i<nTail;i++)
	{
		if(tailX[i]==x && tailY[i]==y)
		gameOver=true;
	}
	if(x==fruitX&&y==fruitY)
	{
		score+=10;
		srand(time(0));
    	fruitX = 1+(rand()%(width-1));
    	fruitY = 1+(rand()%(hight-1));
    	nTail++;
	}
}

