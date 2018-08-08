#include <string.h>
#include<stdio.h>
#include<windows.h>
#include <stdlib.h>
#include <GL/glut.h>
int m=0,n=0;
GLfloat the=0.0;
int reset=1;
int flag=0;
int rot=0;
int omega,alpha,beta;
int rig[4]={0,5,2,4};
int fro[4]={5,1,4,3};
char solver[500];
int stackpointer=-1;
int cubesolution=0;
int change=0,speed=1,aboutus=0,height,width;
char shuffle[18]={'q','w','e','a','s','d','w','s','a','q','d','e','s','a','d','e','w','q'};
GLfloat UpwardsScrollVelocity = -1.0;
float view=20.0;
char quote[6][80];
int numberOfQuotes=0,i;
static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 1;
static int counter=0;


typedef struct 
{ 
	GLfloat p1[3],p2[3],p3[3],p4[3],p5[3];
} room[3][3][12];
room block;
room temp;

GLfloat vertices[][3] ={
							{-1.5,-1.5,-1.5},{-0.5,-1.5,-1.5},{0.5,-1.5,-1.5}, {1.5,-1.5,-1.5},
							{-1.5,-0.5,-1.5},{-0.5,-0.5,-1.5},{0.5,-0.5,-1.5}, {1.5,-0.5,-1.5},
							{-1.5,0.5,-1.5},{-0.5,0.5,-1.5},{0.5,0.5,-1.5}, {1.5,0.5,-1.5},
							{-1.5,1.5,-1.5},{-0.5,1.5,-1.5},{0.5,1.5,-1.5}, {1.5,1.5,-1.5},

							{-1.5,-1.5,-0.5},{-0.5,-1.5,-0.5},{0.5,-1.5,-0.5}, {1.5,-1.5,-0.5},
							{-1.5,-0.5,-0.5},{-0.5,-0.5,-0.5},{0.5,-0.5,-0.5}, {1.5,-0.5,-0.5},
							{-1.5,0.5,-0.5},{-0.5,0.5,-0.5},{0.5,0.5,-0.5}, {1.5,0.5,-0.5},
							{-1.5,1.5,-0.5},{-0.5,1.5,-0.5},{0.5,1.5,-0.5}, {1.5,1.5,-0.5},

							{-1.5,-1.5,0.5},{-0.5,-1.5,0.5},{0.5,-1.5,0.5}, {1.5,-1.5,0.5},
							{-1.5,-0.5,0.5},{-0.5,-0.5,0.5},{0.5,-0.5,0.5}, {1.5,-0.5,0.5},
							{-1.5,0.5,0.5},{-0.5,0.5,0.5},{0.5,0.5,0.5}, {1.5,0.5,0.5},
							{-1.5,1.5,0.5},{-0.5,1.5,0.5},{0.5,1.5,0.5}, {1.5,1.5,0.5},

							{-1.5,-1.5,1.5},{-0.5,-1.5,1.5},{0.5,-1.5,1.5}, {1.5,-1.5,1.5},
							{-1.5,-0.5,1.5},{-0.5,-0.5,1.5},{0.5,-0.5,1.5}, {1.5,-0.5,1.5},
							{-1.5,0.5,1.5},{-0.5,0.5,1.5},{0.5,0.5,1.5}, {1.5,0.5,1.5},
							{-1.5,1.5,1.5},{-0.5,1.5,1.5},{0.5,1.5,1.5}, {1.5,1.5,1.5}
						};
GLfloat colors[][3] = {
						{1.0,1.0,0.0},{0.0,0.0,1.0},{1.0,0.0,0.0},{0.0,1.0,0.0},
						{0.0,1.0,1.0},{1.0,0.0,1.0},{1.0,1.0,1.0}, {0.0,0.0,0.0}
					  };
void toprotate();


void timeTick(void)
{
    if(UpwardsScrollVelocity< -600)
        view-=0.000011;
    if(view < 0) {view=20; UpwardsScrollVelocity = -1.0;}
	    UpwardsScrollVelocity -= 0.05;
	glutPostRedisplay();
}

void RenderToDisplay()
{
    int l,lenghOfQuote, i;
    glTranslatef(0.0, -100, UpwardsScrollVelocity);
    glRotatef(-20, 1.0, 0.0, 0.0);
    glScalef(0.1, 0.1, 0.1);
    for(l=0;l<numberOfQuotes;l++)
    {
        lenghOfQuote = (int)strlen(quote[l]);
        glPushMatrix();
        glTranslatef(-(lenghOfQuote*37), -(l*200), 0.0);
        for (i = 0; i < lenghOfQuote; i++)
        {
            glColor3f((UpwardsScrollVelocity/10)+300+(l*10),(UpwardsScrollVelocity/10)+300+(l*10),0.0);
            glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[l][i]);
        }
        glPopMatrix();
    }
}

void made(int a, int b,int c,int d)
{
	glBegin(GL_LINE_LOOP);
	glPointSize(5.0);
	glColor3f(1,1,1);
	glVertex3fv(vertices[a]);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
	glEnd();
}

void face(room blo)
{
	for(int q=0;q<3;q++)
	{
		for(int w=0;w<3;w++)
		{
			for(int r=0;r<1;r++)
			{
				glBegin(GL_POLYGON);
				glColor3fv(blo[q][w][r].p5);
				glVertex3fv(blo[q][w][r].p1);
				glVertex3fv(blo[q][w][r].p2);
				glVertex3fv(blo[q][w][r].p3);
				glVertex3fv(blo[q][w][r].p4);
				glEnd();
			}
		}
	}
}

void facerot(room blo,int q,int w,int r)
{
	glBegin(GL_POLYGON);
	glColor3fv(blo[q][w][r].p5);
	glVertex3fv(blo[q][w][r].p1);
	glVertex3fv(blo[q][w][r].p2);
	glVertex3fv(blo[q][w][r].p3);
	glVertex3fv(blo[q][w][r].p4);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glPointSize(5.0);
	glColor3f(1,1,1);
	glVertex3fv(blo[q][w][r].p1);
	glVertex3fv(blo[q][w][r].p2);
	glVertex3fv(blo[q][w][r].p3);
	glVertex3fv(blo[q][w][r].p4);
	glEnd();				
}

void polygon(int a, int b, int c , int d,int e,int i,int j)
{
	int k=e;
	if(i<3)
	{
		if(j<3)
		{
			if(k<6)
				{
					for(int g=0;g<3;g++)
					{
						block[i][j][k].p1[g]=vertices[a][g];
						block[i][j][k].p2[g]=vertices[b][g];
						block[i][j][k].p3[g]=vertices[c][g];
						block[i][j][k].p4[g]=vertices[d][g];
						block[i][j][k].p5[g]=colors[e][g];
					}
				}
		 }
	}
	made(a,b,c,d);
}

void back(void)
{
	polygon(0,1,5,4,0,0,0);
	polygon(4,5,9,8,0,1,0);
	polygon(1,2,6,5,0,0,1);
	polygon(5,6,10,9,0,1,1);
	polygon(2,3,7,6,0,0,2);
	polygon(6,7,11,10,0,1,2);
	polygon(10,11,15,14,0,2,2);
	polygon(9,10,14,13,0,2,1);
	polygon(8,9,13,12,0,2,0);
}

void right(void)
{
	polygon(3,19,23,7,1,0,2);
	polygon(7,23,27,11,1,1,2);
	polygon(19,35,39,23,1,0,1);
	polygon(23,39,43,27,1,1,1);
	polygon(35,51,55,39,1,0,0);
	polygon(39,55,59,43,1,1,0);
	polygon(43,59,63,47,1,2,0);
	polygon(11,27,31,15,1,2,2);
	polygon(27,43,47,31,1,2,1);
}

void left(void)
{
	polygon(0,4,20,16,3,0,0);
	polygon(20,4,8,24,3,1,0);
	polygon(32,16,20,36,3,0,1);
	polygon(36,20,24,40,3,1,1);
	polygon(48,32,36,52,3,0,2);
	polygon(52,36,40,56,3,1,2);
	polygon(56,40,44,60,3,2,2);
	polygon(28,24,8,12,3,2,0);
	polygon(40,24,28,44,3,2,1);
}

void front(void)
{
	polygon(48,49,53,52,2,0,0);
	polygon(52,53,57,56,2,1,0);
	polygon(49,50,54,53,2,0,1);
	polygon(53,54,58,57,2,1,1);
	polygon(50,51,55,54,2,0,2);
	polygon(54,55,59,58,2,1,2);
	polygon(58,59,63,62,2,2,2);
	polygon(57,58,62,61,2,2,1);
	polygon(56,57,61,60,2,2,0);

}

void bottom(void)
{
	polygon(0,1,17,16,4,0,0);
	polygon(16,17,33,32,4,1,0);
	polygon(32,33,49,48,4,2,0);
	polygon(1,2,18,17,4,0,1);
	polygon(17,18,34,33,4,1,1);
	polygon(33,34,50,49,4,2,1);
	polygon(50,51,35,34,4,2,2);
	polygon(34,35,19,18,4,1,2);
	polygon(18,19,3,2,4,0,2);
}

void up(void)
{
	polygon(12,13,29,28,5,2,0);
	polygon(28,29,45,44,5,1,0);
	polygon(44,45,61,60,5,0,0);
	polygon(13,14,30,29,5,2,1);
	polygon(29,30,46,45,5,1,1);
	polygon(45,46,62,61,5,0,1);
	polygon(14,15,31,30,5,2,2);
	polygon(30,31,47,46,5,1,2);
	polygon(46,47,63,62,5,0,2);
}

void Key(unsigned char Key, int x, int y)
{ 
	switch(Key)
	{
		case 'w':{
					the=0;
					omega=2 ;
					flag=1;
					rot=1;
					reset=0;
					alpha=1;
				
					if(solver[stackpointer]=='w')
							{stackpointer--	;}
					else
						for(int i=0;i<3;i++)
						{
							solver[++stackpointer]='w';
						}
					break;
				 }
		case 'a':{
					omega=1 ;
					the=0;
					alpha=0 ;
					flag=1;
					rot=1;
					reset=0;
					if(solver[stackpointer]=='a')
							{stackpointer--	;}
					else
						for(int i=0;i<3;i++)
						{
							solver[++stackpointer]='a';
						}
					break;
				 }
		case 's':{	
					the=0;
					omega=0 ;
					flag=1;
					rot=1;
					reset=0;
					alpha=1;
					if(solver[stackpointer]=='s')
							{stackpointer--	;}
					else
						for(int i=0;i<3;i++)
						{
							solver[++stackpointer]='s';
						}
					break;
				  }	
		case 'd': {
					omega=1 ;
					the=0;
					alpha=2 ;
					flag=1;
					rot=1;
					reset=0;
					if(solver[stackpointer]=='d')
							{stackpointer--	;}
					else
						for(int i=0;i<3;i++)
						{
							solver[++stackpointer]='d';
						}
					break;
				  }	
		case 'q':{
					beta=2;
					omega=1 ;
					the=0;
					alpha=1 ;
					flag=1;
					rot=1;
					reset=0;
					if(solver[stackpointer]=='q')
							{stackpointer--	;}
					else
						for(int i=0;i<3;i++)
						{
							solver[++stackpointer]='q';
						}
					break;
				}
		case 'e':{
					beta=0;
					omega=1 ;
					the=0;
					alpha=1 ;
					flag=1;
					rot=1;
					reset=0;
					if(solver[stackpointer]=='e')
							{stackpointer--	;}
					else
						for(int i=0;i<3;i++)
						{
							solver[++stackpointer]='e';
						}
					break;
				}
		case'+':{
					speed++;
					break;
				}
		case'-':
				{
					speed--;
					break;
				}
		case 'c':
				{
					if(change==0)
						glClearColor(1,1,1,1);
					else if(change==1)
						glClearColor(0,0,0,0);
					else if(change==2)
						glClearColor(0.5,0.5,0.5,0);
					change++;
					if(change>2)
						change=change-3;
					break;
				}
		case 27: 
				exit(1); 
				break;
	}
}

void cubesolver(int y)
{
	char k;
	if(stackpointer!=-1)
	{
		k=solver[stackpointer--];
		switch(k)
		{
			case 'w':{
					the=0;
					omega=2 ;
					flag=1;
					rot=1;
					reset=0;
					alpha=1;
			
				 break;}
			case 'a':{
					omega=1 ;
					the=0;
					alpha=0 ;
					flag=1;
					rot=1;
					reset=0;
					break;}
			case 's':{	the=0;
					omega=0 ;
					flag=1;
					rot=1;
					reset=0;
					alpha=1;
					break;
					}	
			case 'd':{omega=1 ;
					the=0;
					alpha=2 ;
					flag=1;
					rot=1;
					reset=0;
					break;
					}	
			case 'q':{beta=2;
					omega=1 ;
					the=0;
					alpha=1 ;
					flag=1;
					rot=1;
					reset=0;
			
					break;
					}
			case 'e':{beta=0;
					omega=1 ;
					the=0;
					alpha=1 ;
					flag=1;
					rot=1;
					reset=0;
					break;
					}
			}
			if(cubesolution==1)
				glutTimerFunc(500,cubesolver,0);
			glutPostRedisplay();
	}
	
}

void shuffler(int faltu)
{
	int shu;
		shu=rand()%18;
		Key(shuffle[shu],0,0);
		printf("%d\n",shu);
		if(counter<10)
		{
			counter++;
			glutTimerFunc(500,shuffler,0);
		}
		else
			counter=0;

}

void row()
{
	if(omega==2)
		{
		for( int y=0;y<3;y++)
		{
			for(int g=0;g<3;g++)
				temp[omega][y][0].p5[g]=block[omega][2-y][3].p5[g];	
		}
		for( int y=0;y<3;y++)
		{
			for(int v=3;v>1;v--)
			{	
				for(int g=0;g<3;g++)
					block[omega][y][v].p5[g]=block[omega][y][v-1].p5[g];
			}
		}
		for( int y=0;y<3;y++)
			for(int g=0;g<3;g++)
					block[omega][y][1].p5[g]=block[omega][2-y][0].p5[g];
		for( int y=0;y<3;y++)	
			for(int g=0;g<3;g++)
				block[omega][y][0].p5[g]=temp[omega][y][0].p5[g];
		for(int g=0;g<3;g++)
		{
			temp[0][0][0].p5[g]=block[0][1][5].p5[g]; 
			temp[1][1][1].p5[g]=block[0][0][5].p5[g];
			block[0][1][5].p5[g]=block[1][2][5].p5[g];
			block[1][2][5].p5[g]=block[2][1][5].p5[g];
			block[2][1][5].p5[g]=block[1][0][5].p5[g];
			block[1][0][5].p5[g]=temp[0][0][0].p5[g];
			block[0][0][5].p5[g]=block[0][2][5].p5[g];
			block[0][2][5].p5[g]=block[2][2][5].p5[g];
			block[2][2][5].p5[g]=block[2][0][5].p5[g];
			block[2][0][5].p5[g]=temp[1][1][1].p5[g];
		}
	}
	else if(omega==0)
	{
		for( int y=0;y<3;y++)
		{
			for(int g=0;g<3;g++)
				temp[omega][y][0].p5[g]=block[omega][2-y][0].p5[g];
		}
		for( int y=0;y<3;y++)
			for(int g=0;g<3;g++)
					block[omega][y][0].p5[g]=block[omega][2-y][1].p5[g];
		for( int y=0;y<3;y++)
		{
			for(int v=1;v<3;v++)
			{	
				for(int g=0;g<3;g++)
					block[omega][y][v].p5[g]=block[omega][y][v+1].p5[g];
			}
		}
		for( int y=0;y<3;y++)
			for(int g=0;g<3;g++)
					block[omega][y][3].p5[g]=temp[omega][y][0].p5[g];
		
		for(int g=0;g<3;g++)
			{		
				temp[0][0][0].p5[g]=block[0][1][4].p5[g]; 
				temp[1][1][1].p5[g]=block[0][0][4].p5[g];
				block[0][1][4].p5[g]=block[1][2][4].p5[g];
				block[1][2][4].p5[g]=block[2][1][4].p5[g];
				block[2][1][4].p5[g]=block[1][0][4].p5[g];
				block[1][0][4].p5[g]=temp[0][0][0].p5[g];
				block[0][0][4].p5[g]=block[0][2][4].p5[g];
				block[0][2][4].p5[g]=block[2][2][4].p5[g];
				block[2][2][4].p5[g]=block[2][0][4].p5[g];
				block[2][0][4].p5[g]=temp[1][1][1].p5[g];
			}
	}
	else if(alpha==2)
	{
		for( int y=0;y<3;y++)
		{
			for(int g=0;g<3;g++)
				temp[y][alpha][0].p5[g]=block[2-y][alpha][rig[0]].p5[g];
		}
	
		for( int y=0;y<3;y++)
		{
			for(int g=0;g<3;g++)
				block[y][alpha][rig[0]].p5[g]=block[2-y][alpha][rig[1]].p5[g];
		}
		for( int y=0;y<3;y++)
		{
			for(int v=1;v<3;v++)
			{	
				for(int g=0;g<3;g++)
					block[y][alpha][rig[v]].p5[g]=block[y][alpha][rig[v+1]].p5[g];
			}
			for(int g=0;g<3;g++)
				block[y][alpha][rig[3]].p5[g]=temp[y][alpha][0].p5[g];
		}
		for(int g=0;g<3;g++)
		{	
			temp[0][0][0].p5[g]=block[0][1][1].p5[g]; 
			temp[1][1][1].p5[g]=block[0][0][1].p5[g];
			block[0][1][1].p5[g]=block[1][2][1].p5[g];
			block[1][2][1].p5[g]=block[2][1][1].p5[g];
			block[2][1][1].p5[g]=block[1][0][1].p5[g];
			block[1][0][1].p5[g]=temp[0][0][0].p5[g];
			block[0][0][1].p5[g]=block[0][2][1].p5[g];
			block[0][2][1].p5[g]=block[2][2][1].p5[g];
			block[2][2][1].p5[g]=block[2][0][1].p5[g];
			block[2][0][1].p5[g]=temp[1][1][1].p5[g];
		}
	}
	else if(alpha==0)
	{
		for( int y=0;y<3;y++)
		{
			for(int g=0;g<3;g++)
				temp[y][alpha][0].p5[g]=block[2-y][alpha][rig[3]].p5[g];
		}
		for( int y=0;y<3;y++)
		{
			for(int v=3;v>1;v--)
			{	
				for(int g=0;g<3;g++)
					block[y][alpha][rig[v]].p5[g]=block[y][alpha][rig[v-1]].p5[g];
			}
		}
		for( int y=0;y<3;y++)
			for(int g=0;g<3;g++)
					block[y][alpha][rig[1]].p5[g]=block[2-y][alpha][rig[0]].p5[g];
		for( int y=0;y<3;y++)	
			for(int g=0;g<3;g++)
					block[y][alpha][rig[0]].p5[g]=temp[y][alpha][0].p5[g];
		
		for(int g=0;g<3;g++)
		{
			temp[0][0][0].p5[g]=block[0][1][3].p5[g]; 
			temp[1][1][1].p5[g]=block[0][0][3].p5[g];
			block[0][1][3].p5[g]=block[1][2][3].p5[g];
			block[1][2][3].p5[g]=block[2][1][3].p5[g];
			block[2][1][3].p5[g]=block[1][0][3].p5[g];
			block[1][0][3].p5[g]=temp[0][0][0].p5[g];
			block[0][0][3].p5[g]=block[0][2][3].p5[g];
			block[0][2][3].p5[g]=block[2][2][3].p5[g];
			block[2][2][3].p5[g]=block[2][0][3].p5[g];
			block[2][0][3].p5[g]=temp[1][1][1].p5[g];

		}

	}
	else if(beta==2)
	{
		for( int y=0;y<3;y++)
		{
			for(int g=0;g<3;g++)
				temp[y][beta][0].p5[g]=block[y][2][fro[3]].p5[g];
		}
		for( int y=0;y<3;y++)
			for(int g=0;g<3;g++)
				block[y][2][fro[3]].p5[g]=block[2][2-y][fro[2]].p5[g];
		for( int y=0;y<3;y++)
			for(int g=0;g<3;g++)
				block[2][y][fro[2]].p5[g]=block[y][0][fro[1]].p5[g];
		for( int y=0;y<3;y++)
			for(int g=0;g<3;g++)
				block[y][0][fro[1]].p5[g]=block[0][2-y][fro[0]].p5[g];
		for( int y=0;y<3;y++)	
			for(int g=0;g<3;g++)
					block[0][y][fro[0]].p5[g]=temp[y][beta][0].p5[g];
		
		for(int g=0;g<3;g++)
		{
			temp[0][0][0].p5[g]=block[0][1][2].p5[g]; 
			temp[1][1][1].p5[g]=block[0][0][2].p5[g];
			block[0][1][2].p5[g]=block[1][2][2].p5[g];
			block[1][2][2].p5[g]=block[2][1][2].p5[g];
			block[2][1][2].p5[g]=block[1][0][2].p5[g];
			block[1][0][2].p5[g]=temp[0][0][0].p5[g];
			block[0][0][2].p5[g]=block[0][2][2].p5[g];
			block[0][2][2].p5[g]=block[2][2][2].p5[g];
			block[2][2][2].p5[g]=block[2][0][2].p5[g];
			block[2][0][2].p5[g]=temp[1][1][1].p5[g];

		}

	}
	else if(beta==0)
	{
		for( int y=0;y<3;y++)
		{
			for(int g=0;g<3;g++)
				temp[y][beta][0].p5[g]=block[2][y][fro[0]].p5[g];
		}
		for( int y=0;y<3;y++)
			for(int g=0;g<3;g++)
				block[2][y][fro[0]].p5[g]=block[2-y][2][fro[1]].p5[g];
		for( int y=0;y<3;y++)
			for(int g=0;g<3;g++)
				block[y][2][fro[1]].p5[g]=block[0][y][fro[2]].p5[g];
		for( int y=0;y<3;y++)
			for(int g=0;g<3;g++)
				block[0][y][fro[2]].p5[g]=block[2-y][0][fro[3]].p5[g];
		for( int y=0;y<3;y++)	
			for(int g=0;g<3;g++)
					block[y][0][fro[3]].p5[g]=temp[y][beta][0].p5[g];
		for(int g=0;g<3;g++)
		{
			temp[0][0][0].p5[g]=block[0][1][0].p5[g]; 
			temp[1][1][1].p5[g]=block[0][0][0].p5[g];
			block[0][1][0].p5[g]=block[1][0][0].p5[g];
			block[1][0][0].p5[g]=block[2][1][0].p5[g];
			block[2][1][0].p5[g]=block[1][2][0].p5[g];
			block[1][2][0].p5[g]=temp[0][0][0].p5[g];
			block[0][0][0].p5[g]=block[2][0][0].p5[g];
			block[2][0][0].p5[g]=block[2][2][0].p5[g];
			block[2][2][0].p5[g]=block[0][2][0].p5[g];
			block[0][2][0].p5[g]=temp[1][1][1].p5[g];
		}

	}
}	

void toprotate()
{
	if(omega==2)
	{	
		glRotatef(theta[0], 1.0, 0.0, 0.0);
		glRotatef(theta[1], 0.0, 1.0, 0.0);
		glRotatef(theta[2], 0.0, 0.0, 1.0);
		for(int h=0;h<2;h++)
		{
			for(int f=0;f<3;f++)
			{
				for(int v=0;v<4;v++)
				{
					facerot(block,h,f,v);
				}
			}
				
		}
		for(int h=0;h<3;h++)
		{
			for(int f=0;f<3;f++)
			{
				facerot(block,h,f,4);
			}
		}
		glPushMatrix();
		glRotatef(the, 0.0, -1.0, 0.0);
		for(int f=0;f<3;f++)
		{
			for(int v=0;v<4;v++)
				facerot(block,omega,f,v);
		}
		for(int f=0;f<3;f++)
		{
			for(int v=0;v<3;v++)
				facerot(block,f,v,5);
		}
		glPopMatrix();
		if(rot==0)
		{
			the=0;
			if(flag==1)
			{	
				row();
				flag=0;
			}
		}
	}
	else if(omega==0)
	{	
		glRotatef(theta[0], 1.0, 0.0, 0.0);
		glRotatef(theta[1], 0.0, 1.0, 0.0);
		glRotatef(theta[2], 0.0, 0.0, 1.0);
		for(int h=1;h<3;h++)
		{
			for(int f=0;f<3;f++)
			{
				for(int v=0;v<4;v++)
				{
					facerot(block,h,f,v);
				}
			}	
		}
		for(int h=0;h<3;h++)
		{
			for(int f=0;f<3;f++)
			{
				facerot(block,h,f,5);
			}
		}
		glPushMatrix();
		glRotatef(the, 0.0, 1.0, 0.0);
		for(int f=0;f<3;f++)
		{
			for(int v=0;v<4;v++)
				facerot(block,omega,f,v);
		}
		for	(int f=0;f<3;f++)
		{
			for(int v=0;v<3;v++)
				facerot(block,f,v,4);
		} 
		glPopMatrix();
		if(rot==0)
		{
			the=0;
			if(flag==1)
			{	
				row();
				flag=0;
			}
		}	
	}
	else if(alpha==0)
	{
		glRotatef(theta[0], 1.0, 0.0, 0.0);
		glRotatef(theta[1], 0.0, 1.0, 0.0);
		glRotatef(theta[2], 0.0, 0.0, 1.0);
		for(int f=1;f<3;f++)
		{
			for(int h=0;h<3;h++)
			{
				for(int v=0;v<4;v++)
					facerot(block,h,f,rig[v]);
			}		
		}
		for(int h=0;h<3;h++)
		{
			for(int f=0;f<3;f++)
			{
				facerot(block,h,f,1);
			}
		}
		glPushMatrix();
	
		glRotatef(the, 1.0, 0.0, 0.0);
		for(int f=0;f<3;f++)
		{
			for(int v=0;v<4;v++)
				facerot(block,f,alpha,rig[v]);
		}
		for(int f=0;f<3;f++)
		{
			for(int v=0;v<3;v++)
				facerot(block,f,v,3);
		}
		glPopMatrix();
		if(rot==0)
		{
			the=0;
			if(flag==1)
			{	
				row();
				flag=0;
			}
		}
	}
	else if(alpha==2)
	{
		glRotatef(theta[0], 1.0, 0.0, 0.0);
		glRotatef(theta[1], 0.0, 1.0, 0.0);
		glRotatef(theta[2], 0.0, 0.0, 1.0);
		for(int f=0;f<2;f++)
		{
			for(int h=0;h<3;h++)
				{
					for(int v=0;v<4;v++)
						{
							facerot(block,h,f,rig[v]);
						}
					}
				
		}
		for(int h=0;h<3;h++)
		{
			for(int f=0;f<3;f++)
				{
					facerot(block,h,f,3);
		}
		}
		glPushMatrix();
		glRotatef(the,-1.0, 0.0, 0.0);
		for(int f=0;f<3;f++)
			{
				for(int v=0;v<4;v++)
					facerot(block,f,alpha,rig[v]);
			}
			for(int f=0;f<3;f++)
			{
				for(int v=0;v<3;v++)
					facerot(block,f,v,1);
			}
	
			glPopMatrix();
		if(rot==0)
		{
			the=0;
			if(flag==1)
			{	
				row();
				flag=0;
			}
		}
		}
	else if(beta==2)
		{
		glRotatef(theta[0], 1.0, 0.0, 0.0);
		glRotatef(theta[1], 0.0, 1.0, 0.0);
		glRotatef(theta[2], 0.0, 0.0, 1.0);
		for(int h=0;h<3;h++)
				{
					facerot(block,1,h,5);
					facerot(block,2,h,5);
					facerot(block,h,1,1);
					facerot(block,h,2,1);
					facerot(block,1,h,4);
					facerot(block,0,h,4);
					facerot(block,h,1,3);
					facerot(block,h,0,3);
				}
				

		
		for(int h=0;h<3;h++)
		{
			for(int f=0;f<3;f++)
			{
				facerot(block,h,f,0);
			}
		}
		glPushMatrix();
		glRotatef(the,0.0, 0.0,-1.0);
		for(int h=0;h<3;h++)
			{
				
			facerot(block,0,h,5);
			facerot(block,h,0,1);
			facerot(block,2,h,4);
			facerot(block,h,2,3);
			}
			for(int f=0;f<3;f++)
			{
				for(int v=0;v<3;v++)
					facerot(block,f,v,2);
			}
	
			glPopMatrix();
		if(rot==0)
		{
			the=0;
			if(flag==1)
			{	
				row();
				flag=0;
			}
		}
		}
	else if(beta==0)
		{
		glRotatef(theta[0], 1.0, 0.0, 0.0);
		glRotatef(theta[1], 0.0, 1.0, 0.0);
		glRotatef(theta[2], 0.0, 0.0, 1.0);
		for(int h=0;h<3;h++)
				{
					facerot(block,1,h,5);
					facerot(block,0,h,5);
					facerot(block,h,1,1);
					facerot(block,h,0,1);
					facerot(block,1,h,4);
					facerot(block,2,h,4);
					facerot(block,h,1,3);
					facerot(block,h,2,3);
				}
		for(int h=0;h<3;h++)
		{
			for(int f=0;f<3;f++)
				{
					facerot(block,h,f,2);
		}
		}
		glPushMatrix();
		glRotatef(the,0.0, 0.0, 1.0);
		for(int h=0;h<3;h++)
			{
				
			facerot(block,2,h,5);
			facerot(block,h,2,1);
			facerot(block,0,h,4);
			facerot(block,h,0,3);
			}
			for(int f=0;f<3;f++)
			{
				for(int v=0;v<3;v++)
					facerot(block,f,v,0);
			}
	
			glPopMatrix();
		if(rot==0)
		{
			the=0;
			if(flag==1)
			{	
				row();
				flag=0;
			}
		}
		}

	
}

void world()
{
	
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	back();
	left();
	right();
	front();
	up();
	bottom();
	for(int h=0;h<3;h++)
	{
		for(int f=0;f<3;f++)
			{
				for(int v=0;v<6;v++)
				facerot(block,h,f,v);
			}
		
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	if(aboutus==0)
	{
		if(reset==1)
			world();
		else
			toprotate();
	}
	else if(aboutus==1)
	{
	  gluLookAt(0.0, 30.0, 150.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	  RenderToDisplay();
	}
	glFlush();
	glutSwapBuffers();
}

void myReshape(int w, int h)
{
	 width=w;
	 height=h;
	 glViewport(0, 0, w, h);
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 if(aboutus==0)
	 { 
		if (w <= h)
			glOrtho(-3.0, 3.0, -3.0 * (GLfloat) h / (GLfloat) w,
			3.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
		else
			glOrtho(-3.0 * (GLfloat) w / (GLfloat) h,
			3.0 * (GLfloat) w / (GLfloat) h, -3.0, 3.0, -10.0, 10.0);
	 }	
	 else
		gluPerspective(60, 1.0, 1.0, 3200);
	glMatrixMode(GL_MODELVIEW);
}

void spinCube()
{
	if(rot==1)
	{
		if(the>=0&&the<=90)
				the+=speed;
		else
		{ 
			rot=0;
		}
	}	
	if(speed<1)
		speed=1;
	if(theta[1]> 360.0) 
		theta[1] -= 360.0;
	if(theta[0] > 360.0) 
		theta[0] -= 360.0;
	if(aboutus==1)
		timeTick();
	glutPostRedisplay();
	
}

void mouse1(int x,int y)
{
	
	if(x>m)
	{	theta[1]++;
		the+=0.2;
		m=x;
	}
	else if(x==m)
	{
				
		m=x;
	}
	else
	{
		theta[1]--;
		m=x;
	}
	if(y>n)
	{
		theta[0]++;
		n=y;
	}
	else if(y==n)
	{
		n=y;
	}
	else
	{
		theta[0]--;
		n=y;
	}
		
}

void option(int n)
{
	if(n==1)
	{
		reset=1;
		aboutus=0;
		stackpointer=-1;
		myReshape(width,height);
	}
	else if(n==2)
	{	
		shuffler(0);
		aboutus=0;
	} 
	else if(n==3)
	{	
		aboutus=0;
		//printf("%d",stackpointer);
		cubesolver(1);
		cubesolution=0;
	}
	else if(n==4)
	{
		aboutus=0;
		cubesolution=1;
		cubesolver(1);
		//printf("%d",stackpointer);
	}
	else if(n==5)
	{	
		if(change==0)
			glClearColor(1,1,1,1);
		else if(change==1)
			glClearColor(0,0,0,0);
		else if(change==2)
			glClearColor(0.5,0.5,0.5,0);
		change++;
		if(change>2)
			change=change-3;
	}
	else if(n==6)
	{
		aboutus=1;
		myReshape(width,height);
		
	}
	else if(n==7)
		exit(0);
}

void main(int argc, char **argv)
{ 	
	strcpy(quote[0]," Rubix cube is a 3-D combination puzzle invented in 1974.");
	strcpy(quote[1],"The inverter of rubix cube is ERNO RUBIX. ");
	strcpy(quote[2],"This is a 3-d simulation of real 3-D Rubix Cube .");
	strcpy(quote[3],"This is design and develop by ");
	strcpy(quote[4]," BHUVNESH TENGURIA");
	numberOfQuotes=5;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Spin a Color Cube");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutIdleFunc(spinCube);
	glutKeyboardFunc(Key);
	glutMotionFunc(mouse1);
	glLineWidth(6);
	glutCreateMenu(option);
	glutAddMenuEntry("NEW GAME",1);
	glutAddMenuEntry("START GAME",2); 
	glutAddMenuEntry("CUBE 1-step solver",3);
	glutAddMenuEntry("FULL CUBE SOLVER",4); 
	glutAddMenuEntry("CHANGE BACK-GROUND",5);
	glutAddMenuEntry("ABOUT US",6);
	glutAddMenuEntry("EXIT ",7);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glEnable(GL_DEPTH_TEST); 
	glutMainLoop();
}
