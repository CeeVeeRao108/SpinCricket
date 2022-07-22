//The source code of our project is given below.
#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<string.h>
int d_sr[]={0,1,2,-1,3,4,-1,6};
int wkt=10;
int n;	
int  player1=1,player2=0,ball1=0,ball2=0,wkt1=0,wkt2=0,score1=0,score2=0;
GLfloat vertices[][2]={{0.0,0.0},{-1.0,-1.0},{-1.5,0.0},{-1.0,1.0},{0.0,1.5},{1.0,1.0},{1.5,0.0},{1.0,-1.0},{0.0,-1.5}};
GLfloat colors[][3]={{0.5,0.5,0.5},{1.0,0.0,0.0},{1.0,1.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},{1.0,0.0,1.0},{0.0,0.0,0.0},{0.0,1.0,1.0}};
/*This function places the ‘string’ in the specified location given by x and y variables*/
void characters(float x,float y,char *st)
{
	int l,i;
	l=strlen(st);
	glRasterPos2f(x,y);
	for(i=0;i<l;i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,st[i]);
	}
}
/* This function creates a box with different colors and also prints the runs associated with that color*/
void box(float x,float y,int z,char *st)
{
	glColor3fv(colors[z-1]);
	glBegin(GL_POLYGON);
	glVertex2f(x,y);
	glVertex2f(x+0.2,y);
	glVertex2f(x+0.2,y-0.2);
	glVertex2f(x,y-0.2);
	glEnd();
	characters(x,y-0.4,st);
}
/* This function creates a triangle with different colors at different position based on the arguments passed to it*/
void polygon(int x,int y,int z)
{
	glColor3fv(colors[y-1]);
	glBegin(GL_POLYGON);
	glVertex2fv(vertices[x]);
	glVertex2fv(vertices[y]);
	glVertex2fv(vertices[z]);
	glEnd();
}
/*This function points  to one of  the color in the octagon*/ 
void pointer()
{
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex2d(1.5,0.0);
	glVertex2d(1.7,0.2);
	glVertex2d(1.7,-0.2);
	glEnd();

	glColor3f(0.0,0.0,0.0);
	glLineWidth(10.0);
	glBegin(GL_LINES);
	glVertex2d(1.7,0.0);
	glVertex2d(2.7,0.0);
	glEnd();

	
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINES);
	glVertex2d(1.5,0.0);
	glVertex2d(1.7,-0.2);
	glVertex2d(1.7,-0.4);
	glEnd();
}
/* This function creates a octagon, by individually calling the polygon() function 8 times*/
void coloroct()
{
	polygon(0,8,1);
	polygon(0,1,2);
	polygon(0,2,3);
	polygon(0,3,4);
	polygon(0,4,5);
	polygon(0,5,6);
	polygon(0,6,7);
	polygon(0,7,8);
}
/* This function calls the box function 8 times to create the box with different colors and print scores assigned to it*/
void color_score()
{
	box(-1.4,1.9,7,"0");
	box(-1.0,1.9,8,"1");
	box(-0.6,1.9,1,"2");
	box(-0.2,1.9,2,"out");
	box(0.2,1.9,3,"3");
	box(0.6,1.9,4,"4");
	box(1.0,1.9,5,"out");
	box(1.4,1.9,6,"6");
}
int theta[]={0.0,0.0,0.0};
static GLint axis=1;
int x=0,y=0;
/* This function is used to display output on the screen*/
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0,1.0,1.0,1.0);
	glLoadIdentity();
	glTranslatef(0.0,0.0,-8.0);
	color_score();
	pointer();
	glRotatef(45+theta[0],0.0,0.0,0.1);
	coloroct();
	glFlush();
	glutSwapBuffers();
}
/* This function is used to rotate the octagon under the control of the player*/
void spinocta()
{
	theta[axis]+=7;
	if(theta[axis]>360.0) theta[axis]-=360.0;
	glutPostRedisplay();
}
/* This function is used to keep track of the scores of the player after each rotation*/
void scoreboard1(int j)
{
	ball1++;
	if(ball1<=n && wkt1<wkt)
	{
		if(d_sr[j]==-1)
		{
			wkt1++;
			printf("\tout\twkt=%d\n",wkt1);
		}
		else
		{
			score1+=d_sr[j];
			printf("\t%d\n",d_sr[j]);
		}
	}
	if(ball1==n || wkt1==wkt)
	{
		printf("final score of the player1=%d/%d\n",score1,wkt1);
		player1=0;
		player2=1;
		printf("\n\nTEAM2 turn\n");
	}
}
void scoreboard2(int j)
{
	ball2++;
	if(ball2<=n && wkt2<wkt)
	{
		if(d_sr[j]==-1)
		{
			wkt2++;
			printf("\tout\twkt=%d\n",wkt2);
		}
		else
		{
			score2+=d_sr[j];
			printf("\t%d\n",d_sr[j]);
		}
	}
}
/* This function is used to get the ‘pointer’ through which score can be evaluated*/
int get_j(int a)
{
	if(a>0 && a<=45)
		return 0;
	else if(a>45 && a<=90)
		return 1;
	else if(a>90 && a<=135)
		return 2;
	else if(a>135 && a<=180)
		return 3;
	else if(a>180 && a<=225)
		return 4;
	else if(a>225 && a<=270)
		return 5;
	else if(a>270 && a<=315)
		return 6;
	else
		return 7;
}
int click=0,finish=0;
/* This function is used to select the option and to enter the number of overs in the game*/

void myKeyboardFunc(unsigned char key,int x,int y)
{
        
	switch(key)
	{
	case 'q':
			exit(0);
			break;
     
	}
}
/* This function is used for spinning the octagon, by pressing the left mouse button the octagon will rotate and pressing the right mouse button the octagon will stop rotating*/
void mouse(int btn,int state,int x,int y)
{
	int j;
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		click=1;
		axis=0;
	}
	if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
	{
		if(click==1)
		{
			axis=2;
			j=get_j(theta[0]);
			if(player1==1 && player2==0)
			{
				if(ball1%6==0)
					printf("over%d\n",ball1/6+1);
				scoreboard1(j);
			}
			else if(player1==0 && player2==1 && finish==0)
			{
				if(ball2%6==0)
					printf("over%d\n",ball2/6+1);
				scoreboard2(j);
				if(score2>score1 || ball2==n ||wkt2==wkt)
				{
					printf("final score of player2=%d/%d\n",score2,wkt2);
					if(score1>score2)
						printf("TEAM1 wins\n");
					else if(score1<score2)
						printf("TEAM2 wins\n");
					else
						printf("tie\n");
					finish=1;
				}
			}
			click=0;
		}
	}
}
/* This function is used to callback function refers the height and width of the new window. The reshape callback invokes a display function*/
void myReshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
glLoadIdentity();
	if(w<=h)
		glOrtho(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w,2.0*(GLfloat)h/(GLfloat)w,-10.0,10.0);
	else 
		glOrtho(-2.0*(GLfloat)w/(GLfloat)h,2.0*(GLfloat)w/(GLfloat)h,-2.0,2.0,-10.0,10.0);
	glMatrixMode(GL_MODELVIEW);
}
int main(int argc,char **argv)
{

    
      printf("Enter the no. of overs:\t");
	scanf("%d",&n);
        printf("\n'INSTRUCTIONS'\npress 'q' to exit\nclick 'left mouse button'  to start spin\nclick 'right mouse button' to stop spinning\n");
	printf("TEAM1's turn\n");
	if(n==0)
	{
		printf("zero balls entered\n");
		exit(0);
	}
	n=n*6;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(700,200);
	glutInitWindowSize(600,600);
	glutCreateWindow("Board Cricket");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutIdleFunc(spinocta);
	glutKeyboardFunc(myKeyboardFunc);
	glutMouseFunc(mouse);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}




                      
























