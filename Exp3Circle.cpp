#include<GL/glut.h>
#include<iostream>
using namespace std;
int r;
void E_way(int x,int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x+320,y+240); // Point in the first octant
	glVertex2i(y+320,x+240);// Point in the fifth octant
	glVertex2i(y+320,-x+240);// Point in the seventh octant
	glVertex2i(x+320,-y+240);// Point in the fourth octant
	glVertex2i(-x+320,-y+240);// Point in the third octant
	glVertex2i(-y+320,-x+240);//Point in the eighth octant
	glVertex2i(-y+320,x+240);// Point in the sixth octant
	glVertex2i(-x+320,y+240);// Point in the second octant
	glEnd();
}
void B_circle()
{
	glClear(GL_COLOR_BUFFER_BIT);//clears screen before drawing
	int x=0,y=r;
	int d=3-2*r;
	while(x<=y)
	{
		E_way(x,y);
		if(d<0)
		{
			d=d+4*x+6;
		}
		else
		{
			d=d+4*(x-y)+10;
			y--;
		}
		x++;
	}
	glFlush();//ensures all points are drawn	
}
void init()
{
	glClearColor(1,1,1,0);
	glColor3f(1,0,0);
	gluOrtho2D(0,640,0,480);
}
int main(int argc,char **argv)
{
        cout<<"\n enter radius\t";
	cin>>r;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,480);
	glutCreateWindow("Circle");
	init();
	glutDisplayFunc(B_circle);
	glutMainLoop();
	return 0;
}
