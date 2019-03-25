#include <stdio.h>
#include <stdlib.h>
#include<Gl/glut.h>     
#include <cmath>  
#include <iostream>
using namespace std;
#define random(x)(rand()%x)

int winWidth = 400, winHeight = 300;     //窗口的宽度和高度
int iPointNum = 0;                     //已确定点的数目
int x1=0,x2=0,y3=0,y2=0;               //确定的点坐标

void drawline(double cd[]);

void Initial(void){
	glPolygonMode(GL_BACK,GL_LINE);
	double line[100];  
   
	for(int i=0;i<100;i++){
	line[i]=random(winWidth-100);}
    glClear(GL_COLOR_BUFFER_BIT);  
    glViewport(0, 0, 600, 600);  
    glColor3f(0, 0, 0);  
	drawline(line);
}
void drawpolygon(double cd[])   
{  
    glBegin(GL_LINE_LOOP);   
    glLineWidth(10);  
    for (int i = 0; i < 8; i = i + 2) {  
        glVertex2f(cd[i], cd[i + 1]);  
    }  
    glEnd();  
}  
  
void drawline(double cd[])   
{  
    glBegin(GL_LINES);     
    glLineWidth(10);  
    for (int i = 0; i < 100; i = i + 2) {  
        glVertex2f(cd[i], cd[i + 1]);  
    }  
    glEnd();  
}  
 
 
 void putpixel(int x, int y)  
{  
    glColor3f(1.0, 0.0, 0.0);        
    glPointSize(3.0f);  
    glBegin(GL_POINTS);  
    glVertex2f(x, y);  
    glEnd();  
    glFlush();  
}  
 
  void DDALine(int x0,int y0,int x1,int y3)  
{  
    int dx,dy,epsl,k;  
    float x,y,xIncre,yIncre;  
    dx=x1-x0;  
    dy=y3-y0;  
    x=x0;  
    y=y0;  
    if(abs(dx)>abs(dy))  
        epsl=abs(dx);  
    else  
        epsl=abs(dy);  
    xIncre=(float)dx/(float)epsl;  
    yIncre=(float)dy/(float)epsl;  
    for(k=0;k<=epsl;k++)  
    {  
        putpixel(int(x+0.5),(int)(y+0.5));  
        x+=xIncre;  
        y+=yIncre;  
    }  
}  
 
 
 
int LBLineClipTest(float p,float q,float &umax,float &umin)
{
	float r=0.0;  
  
	if(p<0.0)
	{
		r=q/p;
		if(r>umin)   	
			return 0; 
		else if(r>umax)	
				umax = r;
	}
 
	else if(p>0.0) 
	{
     	r=q/p;
    	
		if(r<umax)      
			return 0; 
     	else if(r<umin)      	
				umin = r;
	}
	
	else if(q<0.0)    
			return 0; 
	return 1;
}
 
void LBLineClip(float xwl,float xwr,float ywb,float ywt,float x1,float y3,float x2,float y2)
{	
	float umax,umin,deltax,deltay,i1,j1;
	deltax=x2-x1;
	deltay=y2-y3;
	umax=0.0;
	umin=1.0;
 
	if(LBLineClipTest(-deltax,x1-xwl,umax,umin))
	{
		if(LBLineClipTest(deltax,xwr-x1,umax,umin)) 
		{		
			if(LBLineClipTest(-deltay,y3-ywb,umax,umin))
			{
				if(LBLineClipTest(deltay,ywt-y3,umax,umin))  
				{
					i1=int(x1+umax*deltax+0.5);
					j1=int(y3+umax*deltay+0.5);
					x2=int(x1+umin*deltax+0.5);
					y2=int(y3+umin*deltay+0.5);
					cout<<i1<<" "<<j1<<" "<<x2<<" "<<y2<<endl;
					DDALine(i1,j1,x2,y2);
				}
				
			}
		}
	}
}
 
 
void display()  
 {  
	double re[8] = {200, 200, 400, 200, 400, 400, 200, 400}; 
	if(iPointNum >= 1)       {
             glRecti(x1,y3,x2,y2);
       }
    //drawpolygon(re); 
          
    //LBLineClip(200, 400, 200, 400, 500, 500,100, 0); 
	 glutSwapBuffers();                    //交换缓冲区
	glFlush();  
	 //glutPostRedisplay();
 }
void MousePlot(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
       if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)       {
              if(iPointNum == 0 || iPointNum == 2){
                     iPointNum = 1;
                     x1 = xMouse;         y3 = winHeight - yMouse;
              }
              else {
                     iPointNum = 2;
                     x2 = xMouse;         y2 = winHeight - yMouse;
                     glutPostRedisplay();                  //指定窗口重新绘制
              }
       }
       if(button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN){
              iPointNum = 0;
              glutPostRedisplay();
       }
}
 void PassiveMouseMove (GLint xMouse, GLint yMouse)
{
       if(iPointNum == 1)       {
              x2 = xMouse;
              y2 = winHeight - yMouse;    
              glutPostRedisplay();
       }    
}
int main(int argc,  char **argv)
{
   	 glutInit(&argc, argv);  
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RED);  
     glutInitWindowSize(600, 600);  
     glutInitWindowPosition(100, 100);    
     glutCreateWindow("实验3 直线段裁剪");    
	 glClearColor(1, 1, 1, 0.0);  
	 glMatrixMode(GL_PROJECTION);  
     gluOrtho2D(0.0, winWidth, 0.0, winHeight);  
     glutDisplayFunc(display);
	 glutMouseFunc(MousePlot);                  //指定鼠标响应函数
     glutPassiveMotionFunc(PassiveMouseMove);    //指定鼠标移动响应函数
	 Initial();
     glutMainLoop();   
	 return 0;
}
 