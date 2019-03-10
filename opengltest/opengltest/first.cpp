#include <stdlib.h>
#include <GL/glut.h>
#include <cstdio>
 
int hh,ww,xx,yy;
 
void display(){
 
	glClear (GL_COLOR_BUFFER_BIT);
 
	glRectf (-1.0, -1.0, 1.0, 1.0);
 
	glutSwapBuffers ();
 
}
 
void myinit (void){
 
    glClearColor (0.0, 0.0, 0.0, 1.0);
 
    glColor3f (1.0, 1.0, 1.0);
 
    glShadeModel (GL_FLAT);
 
}
 
void mymenu(int value){
 
	if (value == 1){
		printf("直线\n");
	}
 
	if (value == 2){
		printf("矩形\n");
	}
 
}
 
/*  Main Loop
 *  Open window with initial window size, title bar, 
 *  RGBA display mode, and handle input events.
 */
 
int main(int argc, char** argv){
 
	glutInit(&argc,argv);
 
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
 
	glutInitWindowPosition(310,0);
 
	glutCreateWindow("实验内容1 菜单栏");
 
	myinit ();
 
	glutDisplayFunc(display);//注册显示回调函数
 
	glutCreateMenu(mymenu);//注册菜单回调函数
 
	glutAddMenuEntry("直线",1);//添加菜单项
 
	glutAddMenuEntry("矩形",2);
 
	glutAttachMenu(GLUT_RIGHT_BUTTON);//把当前菜单注册到指定的鼠标键
 
	glutMainLoop();
 
 
}