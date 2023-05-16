//============================================================================
// Name        : 20I-0441_B_Sheheryar_Project.cpp
// Author      : Sheheryar Ramzan
// Roll No     : 20I-0441
// Section     : B
// Copyright   : (c) Reserved
// Description : Basic 2D Ludo game...
//============================================================================

#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
//#include "Board.h"
#include "util.h"
#include <iostream>
#include <fstream>
//#include "stdlib.h"
//#include "windows"

#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;
// seed the random numbers generator by current time (see the documentation of srand for further help)...


 
//Opening file highestscore1
int getmaxfromfile()	//function to get max score value from the file
{
//cout<<"intgetmax from file";
 fstream file;
 string s;
	file.open("highestscore1.txt",ios::in);

		if(file.is_open()){
			getline(file,s);
			file.close();
		}
		else{
			cout<<"Error opening file";
			return 0;
		}
			
return stoi(s);	//converting string to integer

}

void savemaxintofile(int max)	//function for saving maximum score into file
{

fstream file;
 string s;
	file.open("highestscore1.txt",ios::out);

		if(file.is_open()){
			file<<to_string(max);
			file.close();
		}
		else{
			cout<<"Error opening file";
		}
			
}


/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
 
void SetCanvasSize(int width, int height) {	//canvas size function 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

//creating structure for got
struct got
{
	int local_pos	=	-10;    //0 to 55 and 56 for pugging
	int global_pos;	//universal positions all over the board starting in a clock-wise order
	int default_pos;
	int status	=	-1; // -1 for home, 0 for active, 1 for pug
};

//creating structure for user
struct user
{
	got	g[4];
	int 	status; // -1 for inactive, 0 for active, 1 for winner
	int	c_pug	=	0;
	int 	score;
	int 	win_pos 	=	0;
};

user u[4];
int game_active	=	0; // is the overall game active or not
int d_value		=	0; // current dice value which has been rolled
int n_user		=	2; // number of user 2 or 4
int c_user		=	1; // which user is currently active and taking turn
int c_turn_active	=	0; // is current user will continue to take turn after dice has been rolled that is waiting for the selection of the goti to be moved
int c_active;				// how many users are currently active.. any one has won then they are not active
int pos 		=	0; // current winning position overall - default is 0
int hs=0;	//declaring highest score = 0 but in file it is set to default at 10

void GameDisplay();	//game display function declaration 
void next_turn();	//delcaration for a function of next_turn

void next_turn() //making of next turn function 
{
	if(d_value >=1 && d_value <=5)	
	{
		int inc;
		if(n_user == 2)
			inc 	=	2;
		else
			inc 	=	1;
		c_user +=	inc;
		c_user	=	c_user%5;
		if(c_user == 0)
			c_user = 1;	
	
		while(u[c_user-1].status == 1) // check for if one player win.. he is skipped and the other continue to play.
		{
			c_user +=	inc;
			c_user	=	c_user%5;
			if(c_user == 0)
				c_user = 1;	
		}		
	}		
	c_turn_active	=	0;	
}	
bool can_move(int c_u) //function to check whether got can move or not at a certain position 
{
	bool	flag 	=	false;
	for(int i=0;i<4;i++)
	{
		if((u[c_u-1].g[i].status == 0 && (56 - u[c_u-1].g[i].local_pos) >= d_value) || (u[c_u-1].g[i].status == -1 && d_value == 6))
			return true;
	}
	return false;
}			

void draw_got(int loc, int u)
{
//	cout<<" user is "<<u<<" and the color is "<<DARK_RED;

	int col;
//declaring different colors to variable col (making code modular by not writing colors over and over again)	
	if(u == 0)
	{
		col	=	DARK_RED;
	}
	else if(u==1)
	{
		col	=	GOLD;
	}
	else if(u==2)
	{
		col	=	DARK_GREEN;
	}
	else if(u==3)
	{
		col	=	LIGHT_BLUE;
	}
	
//drawing gots at different set positions(globally)
	if(loc == 0)
	{
		DrawCircle(325,75, 20,colors[col]);
	}
	else if(loc == 1)
	{
		DrawCircle(325,125,20,colors[col]);
	} 
	
	else if(loc == 2)
	{
		DrawCircle(325, 175,20, colors[col]);
	} 
	else if(loc == 3)
	{
		DrawCircle(325,225,20,colors[col]);
	} 
	else if(loc == 4)
	{
		DrawCircle(325,275,20,colors[col]);
	} 
	else if(loc == 5)
	{
		DrawCircle(275,325,20,colors[col]);
	} 
	else if(loc == 6)
	{
		DrawCircle(225,325,20,colors[col]);
	} 
	else if(loc == 7)
	{
		DrawCircle(175,325,20,colors[col]);
	} 
	else if(loc == 8)
	{
		DrawCircle(125,325,20,colors[col]);
	} 
	else if(loc == 9)
	{
		DrawCircle(75,325,20,colors[col]);
	} 
	else if(loc == 10)
	{
		DrawCircle(25,325,20,colors[col]);
	} 
	else if(loc == 11)
	{
		DrawCircle(25,375,20,colors[col]);
	} 
	else if(loc == 12)
	{
		DrawCircle(25,425,20,colors[col]);
	} 
	else if(loc == 13)
	{
		DrawCircle(75,425,20,colors[col]);
	} 
	else if(loc == 14)
	{
		DrawCircle(125,425,20,colors[col]);
	} 
	else if(loc == 15)
	{
		DrawCircle(175,425,20,colors[col]);
	} 
	else if(loc == 16)
	{
		DrawCircle(225,425,20,colors[col]);
	} 
	else if(loc == 17)
	{
		DrawCircle(275,425,20,colors[col]);
	} 
	else if(loc == 18)
	{
		DrawCircle(325,475,20,colors[col]);
	} 
	else if(loc == 19)
	{
		DrawCircle(325,525,20,colors[col]);
	} 
	else if(loc == 20)
	{
		DrawCircle(325,575,20,colors[col]);
	} 
	else if(loc == 21)
	{
		DrawCircle(325,625,20,colors[col]);
	} 
	else if(loc == 22)
	{
		DrawCircle(325,675,20,colors[col]);
	} 
	else if(loc == 23)
	{
		DrawCircle(325,725,20,colors[col]);
	} 
	else if(loc == 24)
	{
		DrawCircle(375,725,20,colors[col]);
	} 
	else if(loc == 25)
	{
		DrawCircle(425,725,20,colors[col]);
	} 
	else if(loc == 26)
	{
		DrawCircle(425,675,20,colors[col]);
	} 
	else if(loc == 27)
	{
		DrawCircle(425,625,20,colors[col]);
	} 
	else if(loc == 28)
	{
		DrawCircle(425,575,20,colors[col]);
	} 
	else if(loc == 29)
	{
		DrawCircle(425,525,20,colors[col]);
	} 
	else if(loc == 30)
	{
		DrawCircle(425,475,20,colors[col]);
	} 
	else if(loc == 31)
	{
		DrawCircle(475,425,20,colors[col]);
	} 
	else if(loc == 32)
	{
		DrawCircle(525,425,20,colors[col]);
	} 
	else if(loc == 33)
	{
		DrawCircle(575,425,20,colors[col]);
	} 
	else if(loc == 34)
	{
		DrawCircle(625,425,20,colors[col]);
	} 
	else if(loc == 35)
	{
		DrawCircle(675,425,20,colors[col]);
	} 
	else if(loc == 36)
	{
		DrawCircle(725,425,20,colors[col]);
	} 
	else if(loc == 37)
	{
		DrawCircle(725,375,20,colors[col]);
	} 
	else if(loc == 38)
	{
		DrawCircle(725,325,20,colors[col]);
	} 
	else if(loc == 39)
	{
		DrawCircle(675,325,20,colors[col]);
	} 
	else if(loc == 40)
	{
		DrawCircle(625,325,20,colors[col]);
	} 
	else if(loc == 41)
	{
		DrawCircle(575,325,20,colors[col]);
	} 
	else if(loc == 42)
	{
		DrawCircle(525,325,20,colors[col]);
	} 
	else if(loc == 43)
	{
		DrawCircle(475,325,20,colors[col]);
	} 
	else if(loc == 44)
	{
		DrawCircle(425,275,20,colors[col]);
	} 
	else if(loc == 45)
	{
		DrawCircle(425,225,20,colors[col]);
	} 
	else if(loc == 46)
	{
		DrawCircle(425,175,20,colors[col]);
	} 
	else if(loc == 47)
	{
		DrawCircle(425,125,20,colors[col]);
	} 
	else if(loc == 48)
	{
		DrawCircle(425,75,20,colors[col]);
	} 
	else if(loc == 49)
	{
		DrawCircle(425,25,20,colors[col]);
	} 
	else if(loc == 50)
	{
		DrawCircle(375,25,20,colors[col]);
	} 
	else if(loc == 51)
	{
		DrawCircle(325,25,20,colors[col]);
	} 
	
	//Home Runs in clockwise order
	//House Red home runs
	else if(loc == 101)
	{
		DrawCircle(375,75,20,colors[col]);
	} 
	else if(loc == 102)
	{
		DrawCircle(375,125,20,colors[col]);
	} 
	else if(loc == 103)
	{
		DrawCircle(375,175,20,colors[col]);
	} 
	else if(loc == 104)
	{
		DrawCircle(375,225,20,colors[col]);
	} 
	else if(loc == 105)
	{
		DrawCircle(375,275,20,colors[col]);
	} 
	
	//House Yellow Home Runs
	else if(loc == 106)
	{
		DrawCircle(75,375,20,colors[col]);
	} 
	else if(loc == 107)
	{
		DrawCircle(125,375,20,colors[col]);
	} 
	else if(loc == 108)
	{
		DrawCircle(175,375,20,colors[col]);
	} 
	else if(loc == 109)
	{
		DrawCircle(225,375,20,colors[col]);
	} 
	else if(loc == 110)
	{
		DrawCircle(275,375,20,colors[col]);
	} 
	
	//House Green Home Runs
	else if(loc == 111)
	{
		DrawCircle(375,675,20,colors[col]);
	} 
	else if(loc == 112)
	{
		DrawCircle(375,625,20,colors[col]);
	} 
	else if(loc == 113)
	{
		DrawCircle(375,575,20,colors[col]);
	} 
	else if(loc == 114)
	{
		DrawCircle(375,525,20,colors[col]);
	} 
	else if(loc == 115)
	{
		DrawCircle(375,475,20,colors[col]);
	} 
	
	//House Blue Home Runs
	else if(loc == 116)
	{
		DrawCircle(675,375,20,colors[col]);
	} 
	else if(loc == 117)
	{
		DrawCircle(625,375,20,colors[col]);
	} 
	else if(loc == 118)
	{
		DrawCircle(575,375,20,colors[col]);
	} 
	else if(loc == 119)
	{
		DrawCircle(525,375,20,colors[col]);
	} 
	else if(loc == 120)
	{
		DrawCircle(475,375,20,colors[col]);
	} 
	
	
	//Ghotes in respective houses
	//Red house ghotes
	else if(loc == 121)
		DrawCircle(125, 175,20,colors[col]);
	else if(loc == 122)
		DrawCircle(175, 175,20,colors[col]);
	else if(loc == 123)
		DrawCircle(125, 125,20,colors[col]);
	else if(loc == 124)
		DrawCircle(175, 125,20,colors[col]);
		
	//Yellow house ghotes
	else if(loc == 125)
		DrawCircle(125, 625,20,colors[col]);
	else if(loc == 126)
		DrawCircle(175, 625,20,colors[col]);
	else if(loc == 127)
		DrawCircle(125, 575,20,colors[col]);
	else if(loc == 128)
		DrawCircle(175, 575,20,colors[col]);
	
	//Green house ghotes
	else if(loc == 129)
		DrawCircle(575,625,20,colors[col]);
	else if(loc == 130)
		DrawCircle(625,625,20,colors[col]);
	else if(loc == 131)
		DrawCircle(575,575,20,colors[col]);
	else if(loc == 132)
		DrawCircle(625,575,20,colors[col]);
	
	//Blue house ghotes
	else if(loc == 133)
		DrawCircle(575,125,20, colors[col]);
	else if(loc == 134)
		DrawCircle(625,125,20, colors[col]);
	else if(loc == 135)
		DrawCircle(575,175,20, colors[col]);
	else if(loc == 136)
		DrawCircle(625,175,20, colors[col]);
		
	//Pug boxes and positions
	else if(loc == 137)
		DrawCircle(375,325,20, colors[col]);
	else if(loc == 138)
		DrawCircle(325,375,20, colors[col]);
	else if(loc == 139)
		DrawCircle(375,425,20, colors[col]);
	else if(loc == 140)
		DrawCircle(425,375,20, colors[col]);
		

}

void draw_all_got(user u[])	//function for drawing gots if user is active
{
	for(int i=0;i<4;i++)
	{
		if(u[i].status == 0)	//status = 0 refers to user being active
		{
			for(int j=0;j<4;j++)
			{
				draw_got(u[i].g[j].global_pos,i);
			}
		}
	}
}
void start_game(int n)		//start game function 
{
	hs = getmaxfromfile(); //callig function getmaxfromfile and storing it in variable hs
	
	//declarations
	int rel_pos;
	game_active	=	0;
	d_value	=	0; //d_value is dice value
	c_turn_active	=	0; //c_turn_active is  current turn active
	
	u[0].status 	=	0;
	u[0].score	=	0;
	u[0].c_pug	=	0;
	for(int i=0;i<4;i++)
	{
		u[0].g[i].global_pos	= (121+i);	//initial global position of goti in home 
		u[0].g[i].default_pos	= (121+i);	//backup of intial position to bring goti back to home 
	}			
	u[2].status	=	0;
	u[2].score	=	0;
	u[2].c_pug	=	0;
	for(int i=0;i<4;i++)
	{
		u[2].g[i].global_pos	= (129+i);			
		u[2].g[i].default_pos	= (129+i);			
	}
	if(n==2)
	{
		u[1].status 	=	-1;	
		u[3].status	=	-1;
		n_user		=	2;
		c_user		=	1;
		c_active	=	2;
	}
	if(n==4)
	{
		u[1].status 	=	0;	
		u[1].score	=	0;
		u[1].c_pug	=	0;
		for(int i=0;i<4;i++)
		{
			u[1].g[i].global_pos	= (125+i);	//for number of player = 4			
			u[1].g[i].default_pos	= (125+i);			
		}
		u[3].status	=	0;
		u[3].score	=	0;
		u[3].c_pug	=	0;
		for(int i=0;i<4;i++)
		{
			u[3].g[i].global_pos	= (133+i);			
			u[3].g[i].default_pos	= (133+i);			
		}
		n_user		=	4;
		c_user		=	1;
		c_active	=	4;
	}
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
			u[i].g[j].status 	=	-1;
	}
	cout<<"\n Number of users: "<<n;	
	
	GameDisplay();
}
/*
 * Main Canvas drawing function.
 * */
//Board *b;
void GameDisplay()/**/{ //Game display function (board drawing)
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

	// Start Button
	DrawSquare(800,660,120,colors[NAVY]);
	DrawString(810,710, "Two Player", colors[MISTY_ROSE]);
	DrawString(810,680, "Start Game", colors[MISTY_ROSE]);
	DrawSquare(940,660,120,colors[NAVY]);
	DrawString(950,710, "Four Player", colors[MISTY_ROSE]);
	DrawString(950,680, "Start Game", colors[MISTY_ROSE]);

	DrawSquare(830,100,200,colors[BLACK]);//End Square on screen


	int inc,user = 0;
	for(int i=0;i<n_user;i++)
	{
		if(n_user == 2)
			inc 	=	2;
		else
			inc 	=	1;
	
		DrawString(840,250-i*40, "Player "+to_string(i+1)+":\t"+to_string(u[user].score), colors[MISTY_ROSE]);
		user 		+=	inc;
	}		
	DrawString(840,50, "Highest Score:  "+to_string(hs), colors[MISTY_ROSE]);	//displaying highest score
//	c_turn_active	=	0;	
	
	
	//Big Colored squares
	DrawSquare(0,0,300,colors[RED]);
	DrawSquare(450,0,300,colors[NAVY]);
	DrawSquare(0,450,300,colors[YELLOW]);
	DrawSquare(450,450,300,colors[LIME]);
	
	//WHite circle inside big square 
	DrawCircle(150, 150,125, colors[WHITE]);
	DrawCircle(600, 150,125, colors[WHITE]);
	DrawCircle(150, 600,125, colors[WHITE]);
	DrawCircle(600, 600,125, colors[WHITE]);
	
	//Another circle inside circle in houses respectively 
	DrawCircle(150,150,100,colors[RED]);
	DrawCircle(600,150,100,colors[NAVY]);
	DrawCircle(150,600,100,colors[YELLOW]);
	DrawCircle(600,600,100,colors[LIME]);
	
	DrawCircle(150,150,90,colors[WHITE]);
	DrawCircle(600,150,90,colors[WHITE]);
	DrawCircle(150,600,90,colors[WHITE]);
	DrawCircle(600,600,90,colors[WHITE]);
	

	DrawSquare(50,400,50,colors[YELLOW]); //STOP
	DrawSquare(50,350,50,colors[YELLOW]);
	DrawSquare(100,350,50,colors[YELLOW]);
	DrawSquare(150,350,50,colors[YELLOW]);
	DrawSquare(200,350,50,colors[YELLOW]);
	DrawSquare(250,350,50,colors[YELLOW]);
	DrawSquare(300,50,50,colors[RED]);	//STOP
	DrawSquare(350,50,50,colors[RED]);	
	DrawSquare(350,100,50,colors[RED]);	
	DrawSquare(350,150,50,colors[RED]);	
	DrawSquare(350,200,50,colors[RED]);	
	DrawSquare(350,250,50,colors[RED]);	
	
	DrawSquare(400,650,50,colors[LIME]);	//STOP
	DrawSquare(350,650,50,colors[LIME]);
	DrawSquare(350,600,50,colors[LIME]);
	DrawSquare(350,550,50,colors[LIME]);
	DrawSquare(350,500,50,colors[LIME]);
	DrawSquare(350,450,50,colors[LIME]);
	DrawSquare(650,300,50,colors[NAVY]);	//STOP
	DrawSquare(650,350,50,colors[NAVY]);
	DrawSquare(600,350,50,colors[NAVY]);
	DrawSquare(550,350,50,colors[NAVY]);
	DrawSquare(500,350,50,colors[NAVY]);
	DrawSquare(450,350,50,colors[NAVY]);
	
	// White boxes
	DrawSquare(0,300,50,colors[WHITE]);
	DrawSquare(0,350,50,colors[WHITE]);
	DrawSquare(50,300,50,colors[WHITE]);
	DrawSquare(150,300,50,colors[WHITE]);
	DrawSquare(100,300,50,colors[RED]);  //STOP
	DrawSquare(200,300,50,colors[WHITE]);
	DrawSquare(250,300,50,colors[WHITE]);
	DrawSquare(0,400,50,colors[WHITE]);
	DrawSquare(100,400,50,colors[WHITE]);
	DrawSquare(150,400,50,colors[WHITE]);
	DrawSquare(200,400,50,colors[WHITE]);
	DrawSquare(250,400,50,colors[WHITE]);
	DrawSquare(300,0,50,colors[WHITE]);
	DrawSquare(350,0,50,colors[WHITE]);
	DrawSquare(400,0,50,colors[WHITE]);
	DrawSquare(300,100,50,colors[WHITE]);
	DrawSquare(300,150,50,colors[WHITE]);
	DrawSquare(300,200,50,colors[WHITE]);
	DrawSquare(300,250,50,colors[WHITE]);
	DrawSquare(400,50,50,colors[WHITE]);
	DrawSquare(400,100,50,colors[NAVY]);	//Stop
	DrawSquare(400,150,50,colors[WHITE]);
	DrawSquare(400,200,50,colors[WHITE]);
	DrawSquare(400,250,50,colors[WHITE]);
	DrawSquare(450,300,50,colors[WHITE]);
	DrawSquare(500,300,50,colors[WHITE]);
	DrawSquare(550,300,50,colors[WHITE]);
	DrawSquare(600,300,50,colors[WHITE]);
	DrawSquare(700,300,50,colors[WHITE]);
	DrawSquare(700,350,50,colors[WHITE]);
	DrawSquare(700,400,50,colors[WHITE]);
	DrawSquare(650,400,50,colors[WHITE]);
	DrawSquare(600,400,50,colors[LIME]);	//Stop
	DrawSquare(550,400,50,colors[WHITE]);
	DrawSquare(500,400,50,colors[WHITE]);
	DrawSquare(450,400,50,colors[WHITE]);
	DrawSquare(300,450,50,colors[WHITE]);
	DrawSquare(300,500,50,colors[WHITE]);
	DrawSquare(300,600,50,colors[YELLOW]);	//Stop
	DrawSquare(300,550,50,colors[WHITE]);
	DrawSquare(300,650,50,colors[WHITE]);
	DrawSquare(300,700,50,colors[WHITE]);
	DrawSquare(350,700,50,colors[WHITE]);
	DrawSquare(400,700,50,colors[WHITE]);
	DrawSquare(400,600,50,colors[WHITE]);
	DrawSquare(400,550,50,colors[WHITE]);
	DrawSquare(400,500,50,colors[WHITE]);
	DrawSquare(400,450,50,colors[WHITE]);
	
	
	//Border of each home x-axis
	DrawLine(0,300,750,300,2,colors[BLACK]);
	DrawLine(0,450,750,450,2,colors[BLACK]);
	
	//border of each home y-axis
	DrawLine(300,0,300,750,2,colors[BLACK]);
	DrawLine(450,0,450,750,2,colors[BLACK]);
	
	//3-way path x-axis
	DrawLine(0,350,750,350,2,colors[BLACK]);
	DrawLine(0,400,750,400,2,colors[BLACK]);
	
	//3-way oath Y-axis
	DrawLine(350,0,350,750,2,colors[BLACK]);
	DrawLine(400,0,400,750,2,colors[BLACK]);
	
	//Home box
	DrawTriangle(300,300,375,375,300,450,colors[YELLOW]);
	DrawTriangle(300,450,375,375,450,450,colors[LIME]);
	DrawTriangle(300,300,375,375,450,300,colors[RED]);
	DrawTriangle(450,450,375,375,450,300,colors[BLUE]);
	
	//Home Diaognals
	DrawLine(300,450,450,300,2,colors[BLACK]);
	DrawLine(450,450,300,300,2,colors[BLACK]);
	
	//3-way Paths Y-Axis
	DrawLine(300,50,450,50,2,colors[BLACK]);
	DrawLine(300,100,450,100,2,colors[BLACK]);
	DrawLine(300,150,450,150,2,colors[BLACK]);
	DrawLine(300,200,450,200,2,colors[BLACK]);
	DrawLine(300,250,450,250,2,colors[BLACK]);
	
	
	//3-way paths X-Axis
	DrawLine(500,300,500,450,2,colors[BLACK]);
	DrawLine(550,300,550,450,2,colors[BLACK]);
	DrawLine(600,300,600,450,2,colors[BLACK]);
	DrawLine(650,300,650,450,2,colors[BLACK]);
	DrawLine(700,300,700,450,2,colors[BLACK]);
	
	DrawLine(50,300,50,450,2,colors[BLACK]);
	DrawLine(100,300,100,450,2,colors[BLACK]);
	DrawLine(150,300,150,450,2,colors[BLACK]);
	DrawLine(200,300,200,450,2,colors[BLACK]);
	DrawLine(250,300,250,450,2,colors[BLACK]);
	
	if(game_active == 1)
	{
		draw_all_got(u);
		if(c_turn_active	==	0)
		{
			DrawSquare(910,480,70,colors[NAVY]);
			DrawString(920, 500, "DICE",colors[MISTY_ROSE]);
		}
		else if(!can_move(c_user))	
		{	
			//displaying on game window
			DrawString(800, 520, "You got: ",colors[MISTY_ROSE]); 
			DrawString(900, 520, to_string(d_value),colors[MISTY_ROSE]);
			DrawString(800, 480, "But cannot move.",colors[MISTY_ROSE]);
			DrawSquare(910,350,100,colors[NAVY]);
			DrawString(920, 400, "Next Player",colors[MISTY_ROSE]);
		
		}
		else
		{
			DrawString(800, 520, "You got: ",colors[MISTY_ROSE]); 
			DrawString(900, 520, to_string(d_value),colors[MISTY_ROSE]);
		
		}
		DrawString(800, 610, "Current Turn: ",colors[MISTY_ROSE]); 
		DrawString(950, 610, "Player "+to_string(c_user),colors[MISTY_ROSE]);

	}
	else if(game_active == 2)
	{
		DrawSquare(910,380,150,colors[NAVY]);
		for(int i=0;i<4;i++)
		{
			if(u[i].win_pos == 1)
			{
				DrawString(920, 4700, "Player "+to_string(i+1)+" won the Game.", colors[MISTY_ROSE]); // You can write the code to save it in the file here
			}
		}
	}
	glutSwapBuffers(); // do not modify this line..

}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...

	} else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {

	} else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {

	}

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {

	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 'b' || key == 'B') //Key for placing the bomb
			{
		//do something if b is pressed
		cout << "b pressed" << endl;

	}
	
	if(key == ' ') //dice rolling by space
	{
		if(game_active == 1)
		{
			if(c_turn_active	==	0)
			{
				srand ((unsigned) time(NULL));
				d_value	=	rand()%6+1;
				c_turn_active	=	1;
				GameDisplay();
				
			}
		}

	}
	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000.0, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {

	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
 
bool is_stop(int loc)
{
	if(loc == 0 || loc == 8 || loc == 13 || loc == 21 || loc == 26 || loc == 34 || loc == 39 || loc == 47) 
		return true;
	else
		return false;
}
void move(int click_loc)
{
	int k_i	=	-1;
	if(c_turn_active == 1)	//dice is rolled and now got has to move 
	{ 
		for(int i=0;i<4;i++)
		{
			if(u[c_user-1].g[i].global_pos == click_loc)	//checking user of home clicks which got
			{
				if(u[c_user-1].g[i].local_pos + d_value >56) //a box clicked with goti requiring less number for pugging
					break;
				u[c_user-1].g[i].global_pos	+= d_value;	//moves got to new position
				u[c_user-1].score 		+= d_value;
				if(u[c_user-1].g[i].local_pos <= 50)	//not in home runs yet
					u[c_user-1].g[i].global_pos	=	u[c_user-1].g[i].global_pos % 52;
				u[c_user-1].g[i].local_pos	+= d_value;

				cout<<"\nCurrent location of click "<<click_loc<<", and global pos: "<<u[c_user-1].g[i].global_pos<<", and local pos: "<<u[c_user-1].g[i].local_pos<<"\n";
				
				if(!is_stop(u[c_user-1].g[i].global_pos) || u[c_user-1].g[i].local_pos >50)
				{
					if(u[c_user-1].g[i].local_pos == 56)	//goti pugg gaye
					{
						u[c_user-1].g[i].status 	=	1;
						u[c_user-1].g[i].global_pos	=	136+c_user;	//moves goti in respective home triangle
						u[c_user-1].score 		+= 	15; // adding socre for pug
						u[c_user-1].c_pug++;
						if(u[c_user-1].c_pug == 4)
						{
							u[c_user-1].status	=	1;
							if (u[c_user-1].score>hs){
							hs = u[c_user-1].score;
							savemaxintofile(hs);
							}
							u[c_user-1].win_pos 	=	++pos;
							c_active--;
							if(c_active == 1)
								game_active	=	2;
						}
						next_turn();
						break;	
					}
					if(u[c_user-1].g[i].local_pos >50)	//home run 
					{
						u[c_user-1].g[i].global_pos	=	100+(5*(c_user-1))+u[c_user-1].g[i].local_pos - 50;	//goti pug from which number
										cout<<"\nCurrent location of click "<<click_loc<<", and global pos: "<<u[c_user-1].g[i].global_pos<<", and local pos: "<<u[c_user-1].g[i].local_pos<<"\n";

						next_turn();
						break;
					}
					cout<<"\nCurrent location is not a stop";
					for(int j=0;j<4;j++)
					{
						if(j == c_user-1)	//checking whether the got ahead is of the same color or not(killing process)
						{
							continue;
						}
						k_i 	=	-1;
						for(int k=0;k<4;k++)
						{
							
							if(u[c_user-1].g[i].global_pos == u[j].g[k].global_pos && u[c_user-1].g[i].status == 0) 
							{
								if(k_i == -1)
									k_i 	=	k; //k_i is killer index
								else
								{
									k_i 	=	5; //block made by another got
									
								}
							}
						}
						if(k_i > -1 && k_i<5)
						{
							u[j].g[k_i].global_pos	=	u[j].g[k_i].default_pos;//after killing back to home
							u[j].g[k_i].local_pos	=	-10;  
							u[j].g[k_i].status	=	-1;
							u[c_user-1].score 	+= 	10; //killing socre
							break;
						}
					}
				}
//				if(d_value >=1 && d_value <=5)
				next_turn();
				break;	
			}
		}
	}
	GameDisplay();

}

void MouseClicked(int button, int state, int x, int y) {	//Moving ghotes by mouse click using stored positions(click_loc)

	cout<<"\n"<<x<<"  "<<y;
	int click_loc	=	-1;
	if(x>300 &&x <350 &&y >700 && y<750)
	{
		click_loc	=	0;	//storing position of every box of board
		move(click_loc); //calling move function on the postion(global) according to the board
	}
	else if(x>300 &&x <350 &&y >650 && y<700)
	{
		click_loc	=	1;
		move(click_loc);
	} 
	else if(x>300 &&x <350 &&y >600 && y<650)
	{
		click_loc	=	2;
		move(click_loc);
	} 
	else if(x>300 &&x <350 &&y >550 && y<600)
	{
		click_loc	=	3;
		move(click_loc);
	} 
	else if(x>300 &&x <350 &&y >500 && y<550)
	{
		click_loc	=	4;
		move(click_loc);
	} 
	else if(x>250 &&x <300 &&y >450 && y<500)
	{
		click_loc	=	5;
		move(click_loc);
	} 
	else if(x>200 &&x <250 &&y >450 && y<500)
	{
		click_loc	=	6;
		move(click_loc);
	} 
	else if(x>150 &&x <200 &&y >450 && y<500)
	{
		click_loc	=	7;
		move(click_loc);
	} 
	else if(x>100 &&x <150 &&y >450 && y<500)
	{
		click_loc	=	8;
		move(click_loc);
	} 
	else if(x>50 &&x <100 &&y >450 && y<500)
	{
		click_loc	=	9;
		move(click_loc);
	} 
	else if(x>0 &&x <50 &&y >450 && y<500)
	{
		click_loc	=	10;
		move(click_loc);
	} 
	else if(x>0 &&x <50 &&y >400 && y<450)
	{
		click_loc	=	11;
		move(click_loc);
	} 
	else if(x>0 &&x <50 &&y >350 && y<400)
	{
		click_loc	=	12;
		move(click_loc);
	} 
	else if(x>50 &&x <100 &&y >350 && y<400)
	{
		click_loc	=	13;
		move(click_loc);
	} 
	else if(x>100 &&x <150 &&y >350 && y<400)
	{
		click_loc	=	14;
		move(click_loc);
	} 
	else if(x>150 &&x <200 &&y >350 && y<400)
	{
		click_loc	=	15;
		move(click_loc);
	} 
	else if(x>200 &&x <250 &&y >350 && y<400)
	{
		click_loc	=	16;
		move(click_loc);
	} 
	else if(x>250 &&x <300 &&y >350 && y<400)
	{
		click_loc	=	17;
		move(click_loc);
	} 
	else if(x>300 &&x <350 &&y >300 && y<350)
	{
		click_loc	=	18;
		move(click_loc);
	} 
	else if(x>300 &&x <350 &&y >250 && y<300)
	{
		click_loc	=	19;
		move(click_loc);
	} 
	else if(x>300 &&x <350 &&y >200 && y<250)
	{
		click_loc	=	20;
		move(click_loc);
	} 
	else if(x>300 &&x <350 &&y >150 && y<200)
	{
		click_loc	=	21;
		move(click_loc);
	} 
	else if(x>300 &&x <350 &&y >100 && y<150)
	{
		click_loc	=	22;
		move(click_loc);
	} 
	else if(x>300 &&x <350 &&y >50 && y<100)
	{
		click_loc	=	23;
		move(click_loc);
	} 
	else if(x>350 &&x <400 &&y >50 && y<100)
	{
		click_loc	=	24;
		move(click_loc);
	} 
	else if(x>400 &&x <450 &&y >50 && y<100)
	{
		click_loc	=	25;
		move(click_loc);
	} 
	else if(x>400 &&x <450 &&y >100 && y<150)
	{
		click_loc	=	26;
		move(click_loc);
	} 
	else if(x>400 &&x <450 &&y >150 && y<200)
	{
		click_loc	=	27;
		move(click_loc);
	} 
	else if(x>400 &&x <450 &&y >200 && y<250)
	{
		click_loc	=	28;
		move(click_loc);
	} 
	else if(x>400 &&x <450 &&y >250 && y<300)
	{
		click_loc	=	29;
		move(click_loc);
	} 
	else if(x>400 &&x <450 &&y >300 && y<350)
	{
		click_loc	=	30;
		move(click_loc);
	} 
	else if(x>450 &&x <500 &&y >350 && y<400)
	{
		click_loc	=	31;
		move(click_loc);
	} 
	else if(x>500 &&x <550 &&y >350 && y<400)
	{
		click_loc	=	32;
		move(click_loc);
	} 
	else if(x>550 &&x <600 &&y >350 && y<400)
	{
		click_loc	=	33;
		move(click_loc);
	} 
	else if(x>600 &&x <650 &&y >350 && y<400)
	{
		click_loc	=	34;
		move(click_loc);
	} 
	else if(x>650 &&x <700 &&y >350 && y<400)
	{
		click_loc	=	35;
		move(click_loc);
	} 
	else if(x>700 &&x <750 &&y >350 && y<400)
	{
		click_loc	=	36;
		move(click_loc);
	} 
	else if(x>700 &&x <750 &&y >400 && y<450)
	{
		click_loc	=	37;
		move(click_loc);
	} 
	else if(x>700 &&x <750 &&y >450 && y<500)
	{
		click_loc	=	38;
		move(click_loc);
	} 
	else if(x>650 &&x <700 &&y >450 && y<500)
	{
		click_loc	=	39;
		move(click_loc);
	} 
	else if(x>600 &&x <650 &&y >450 && y<500)
	{
		click_loc	=	40;
		move(click_loc);
	} 
	else if(x>550 &&x <600 &&y >450 && y<500)
	{
		click_loc	=	41;
		move(click_loc);
	} 
	else if(x>500 &&x <550 &&y >450 && y<500)
	{
		click_loc	=	42;
		move(click_loc);
	} 
	else if(x>450 &&x <500 &&y >450 && y<500)
	{
		click_loc	=	43;
		move(click_loc);
	} 
	else if(x>400 &&x <450 &&y >500 && y<550)
	{
		click_loc	=	44;
		move(click_loc);
	} 
	else if(x>400 &&x <450 &&y >550 && y<600)
	{
		click_loc	=	45;
		move(click_loc);
	} 
	else if(x>400 &&x <450 &&y >600 && y<650)
	{
		click_loc	=	46;
		move(click_loc);
	} 
	else if(x>400 &&x <450 &&y >650 && y<700)
	{
		click_loc	=	47;
		move(click_loc);
	} 
	else if(x>400 &&x <450 &&y >700 && y<750)
	{
		click_loc	=	48;
		move(click_loc);
	} 
	else if(x>400 &&x <450 &&y >750 && y<800)
	{
		click_loc	=	49;
		move(click_loc);
	} 
	else if(x>350 &&x <400 &&y >750 && y<800)
	{
		click_loc	=	50;
		move(click_loc);
	} 
	else if(x>300 &&x <350 &&y >750 && y<800)
	{
		click_loc	=	51;
		move(click_loc);
	} 
	else if(x>350 &&x <400 &&y >700 && y<750)
	{
		click_loc	=	101;
		move(click_loc);
	} 
	else if(x>350 &&x <400 &&y >650 && y<700)
	{
		click_loc	=	102;
		move(click_loc);
	} 
	else if(x>350 &&x <400 &&y >600 && y<650)
	{
		click_loc	=	103;
		move(click_loc);
	} 
	else if(x>350 &&x <400 &&y >550 && y<600)
	{
		click_loc	=	104;
		move(click_loc);
	} 
	else if(x>350 &&x <400 &&y >500 && y<550)
	{
		click_loc	=	105;
		move(click_loc);
	} 

	else if(x>50 &&x <100 &&y >400 && y<450)
	{
		click_loc	=	106;
		move(click_loc);
	} 
	else if(x>100 &&x <150 &&y >400 && y<450)
	{
		click_loc	=	107;
		move(click_loc);
	} 
	else if(x>150 &&x <200 &&y >400 && y<450)
	{
		click_loc	=	108;
		move(click_loc);
	} 
	else if(x>200 &&x <250 &&y >400 && y<450)
	{
		click_loc	=	109;
		move(click_loc);
	} 
	else if(x>250 &&x <300 &&y >400 && y<450)
	{
		click_loc	=	110;
		move(click_loc);
	} 
	else if(x>350 &&x <400 &&y >100 && y<150)
	{
		click_loc	=	111;
		move(click_loc);
	} 
	else if(x>350 &&x <400 &&y >150 && y<200)
	{
		click_loc	=	112;
		move(click_loc);
	} 
	else if(x>350 &&x <400 &&y >200 && y<250)
	{
		click_loc	=	113;
		move(click_loc);
	} 
	else if(x>350 &&x <400 &&y >250 && y<300)
	{
		click_loc	=	114;
		move(click_loc);
	} 
	else if(x>350 &&x <400 &&y >300 && y<350)
	{
		click_loc	=	115;
		move(click_loc);
	} 

	else if(x>650 &&x <700 &&y >400 && y<450)
	{
		click_loc	=	116;
		move(click_loc);
	} 
	else if(x>600 &&x <650 &&y >400 && y<450)
	{
		click_loc	=	117;
		move(click_loc);
	} 
	else if(x>550 &&x <600 &&y >400 && y<450)
	{
		click_loc	=	118;
		move(click_loc);
	} 
	else if(x>500 &&x <550 &&y >400 && y<450)
	{
		click_loc	=	119;
		move(click_loc);
	} 
	else if(x>450 &&x <500 &&y >400 && y<450)
	{
		click_loc	=	120;
		move(click_loc);
	} 

	else if(x>100 &&x <150 &&y >600 && y<650)
	{
		click_loc	=	121; // house first got for red
		if(c_turn_active == 1 && d_value == 6 && c_user == 1)
		{
			u[0].g[0].global_pos	=	0;
			u[0].g[0].local_pos	=	0;
			u[0].g[0].status	=	0;
			next_turn();	//calling next turn function after getting a six
			GameDisplay();
			
		}
	}
	else if(x>150 &&x <200 &&y >600 && y<650)
	{
		click_loc	=	122; // house 2nd got for red
		if(c_turn_active == 1 && d_value == 6 && c_user == 1)
		{
			u[0].g[1].global_pos	=	0;
			u[0].g[1].local_pos	=	0;
			u[0].g[1].status	=	0;
			next_turn();
			GameDisplay();
			
		}
	} 
	else if(x>100 &&x <150 &&y >650 && y<700)
	{
		click_loc	=	123; // house 3rd got for red
		if(c_turn_active == 1 && d_value == 6 && c_user == 1)
		{
			u[0].g[2].global_pos	=	0;
			u[0].g[2].local_pos	=	0;
			u[0].g[2].status	=	0;
			next_turn();
			GameDisplay();
			
		}
	} 
	else if(x>150 &&x <200 &&y >650 && y<700)
	{
		click_loc	=	124; // house fourth got for red
		if(c_turn_active == 1 && d_value == 6 && c_user == 1)
		{
			u[0].g[3].global_pos	=	0;
			u[0].g[3].local_pos	=	0;
			u[0].g[3].status	=	0;
			next_turn();
			GameDisplay();
			
		}
	} 
	else if(x>100 &&x <150 &&y >150 && y<200)
	{
		click_loc	=	125; // house first got for yellow
		if(c_turn_active == 1 && d_value == 6 && c_user == 2)
		{
			u[1].g[0].global_pos	=	13;
			u[1].g[0].local_pos	=	0;
			u[1].g[0].status	=	0;
			next_turn();
			GameDisplay();
			
		}
	}
	else if(x>150 &&x <200 &&y >150 && y<200)
	{
		click_loc	=	126; // house 2nd got for yellow
		if(c_turn_active == 1 && d_value == 6 && c_user == 2)
		{
			u[1].g[1].global_pos	=	13;
			u[1].g[1].local_pos	=	0;
			u[1].g[1].status	=	0;
			next_turn();
			GameDisplay();
			
		}
	} 
	else if(x>100 &&x <150 &&y >200 && y<250)
	{
		click_loc	=	127; // house third got for yellow
		if(c_turn_active == 1 && d_value == 6 && c_user == 2)
		{
			u[1].g[2].global_pos	=	13;
			u[1].g[2].local_pos	=	0;
			u[1].g[2].status	=	0;
			next_turn();
			GameDisplay();
			
		}
	} 
	else if(x>150 &&x <200 &&y >200 && y<250)
	{
		click_loc	=	128; // house 4th got for yellow
		if(c_turn_active == 1 && d_value == 6 && c_user == 2)
		{
			u[1].g[3].global_pos	=	13;
			u[1].g[3].local_pos	=	0;
			u[1].g[3].status	=	0;
			next_turn();
			GameDisplay();
			
		}
	} 
	else if(x>550 &&x <600 &&y >150 && y<200)
	{
		click_loc	=	129; // house first got for lime
		if(c_turn_active == 1 && d_value == 6 && c_user == 3)
		{
			u[2].g[0].global_pos	=	26;
			u[2].g[0].local_pos	=	0;
			u[2].g[0].status	=	0;
			next_turn();
			GameDisplay();
			
		}

	}
	else if(x>600 &&x <650 &&y >150 && y<200)
	{
		click_loc	=	130; // house second got for lime
		if(c_turn_active == 1 && d_value == 6 && c_user == 3)
		{
			u[2].g[1].global_pos	=	26;
			u[2].g[1].local_pos	=	0;
			u[2].g[1].status	=	0;
			next_turn();
			GameDisplay();
			
		}
	} 
	else if(x>550 &&x <600 &&y >200 && y<250)
	{
		click_loc	=	131; // house third got for lime
		if(c_turn_active == 1 && d_value == 6 && c_user == 3)
		{
			u[2].g[2].global_pos	=	26;
			u[2].g[2].local_pos	=	0;
			u[2].g[2].status	=	0;
			next_turn();
			GameDisplay();
			
		}
	} 
	else if(x>600 &&x <650 &&y >200 && y<250)
	{
		click_loc	=	132; // house fourth got for lime
		if(c_turn_active == 1 && d_value == 6 && c_user == 3)
		{
			u[2].g[3].global_pos	=	26;
			u[2].g[3].local_pos	=	0;
			u[2].g[3].status	=	0;
			next_turn();
			GameDisplay();
			
		}
	} 
	else if(x>550 &&x <600 &&y >600 && y<650)
	{
		click_loc	=	133; // house first got for blue
		if(c_turn_active == 1 && d_value == 6 && c_user == 4)
		{
			u[3].g[0].global_pos	=	39;
			u[3].g[0].local_pos	=	0;
			u[3].g[0].status	=	0;
			next_turn();
			GameDisplay();
			
		}
	} 
	else if(x>600 &&x <650 &&y >600 && y<650)
	{
		click_loc	=	134; // house second got for blue
		if(c_turn_active == 1 && d_value == 6 && c_user == 4)
		{
			u[3].g[1].global_pos	=	39;
			u[3].g[1].local_pos	=	0;
			u[3].g[1].status	=	0;
			next_turn();
			GameDisplay();
			
		}
	} 
	else if(x>550 &&x <600 &&y >650 && y<700)
	{
		click_loc	=	135; // house third got for blue
		if(c_turn_active == 1 && d_value == 6 && c_user == 4)
		{
			u[3].g[2].global_pos	=	39;
			u[3].g[2].local_pos	=	0;
			u[3].g[2].status	=	0;
			next_turn();
			GameDisplay();
			
		}
	} 
	else if(x>600 &&x <650 &&y >650 && y<700)
	{
		click_loc	=	136; // house fourth got for blue
		if(c_turn_active == 1 && d_value == 6 && c_user == 4)
		{
			u[3].g[3].global_pos	=	39;
			u[3].g[3].local_pos	=	0;
			u[3].g[3].status	=	0;
			next_turn();
			GameDisplay();
			
		}
	} 
	else if(x>810 &&x <930 &&y >20 && y<130)
	{
		start_game(2); // 2 player button event handling
		game_active 	=	1;

	} 
	else if(x>950 &&x <1070 &&y >20 && y<130)
	{
		start_game(4); // 2 player butto event handling
		game_active 	=	1;
	} 
	else if(game_active == 1 && c_turn_active == 0 && x>920 &&x <1000 &&y >250 && y<320)
	{
		//Dice functionality 
		srand ((unsigned) time(NULL));
		d_value	=	rand()%6+1;
		c_turn_active	=	1;
		GameDisplay();
		
	}
	else if(game_active == 1 && c_turn_active == 1 && x>910 &&x <1010 &&y > 350 && y<450)
	{
		cout<<"\nIn changing user.. current user is: "<<c_user<<", and th dice value is "<<d_value;
		if(!can_move(c_user))
		{
			cout<<"\n changing the user";
			next_turn();
			c_turn_active = 	0;
			GameDisplay();
		}
	} 
	else
	{
		click_loc	=	-1;
	}
	
		cout<<"\nClick Location "<<click_loc;
	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
//		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{

	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	hs = getmaxfromfile();

	//b = new Board(60, 60); // create a new board object to use in the Display Function ...

	int width = 1066, height = 800; // i have set my window size to be 800 x 600
	//b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(0, 0); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("PF Project"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...
	

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
