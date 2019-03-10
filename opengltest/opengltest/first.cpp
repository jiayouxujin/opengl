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
		printf("ֱ��\n");
	}
 
	if (value == 2){
		printf("����\n");
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
 
	glutCreateWindow("ʵ������1 �˵���");
 
	myinit ();
 
	glutDisplayFunc(display);//ע����ʾ�ص�����
 
	glutCreateMenu(mymenu);//ע��˵��ص�����
 
	glutAddMenuEntry("ֱ��",1);//��Ӳ˵���
 
	glutAddMenuEntry("����",2);
 
	glutAttachMenu(GLUT_RIGHT_BUTTON);//�ѵ�ǰ�˵�ע�ᵽָ��������
 
	glutMainLoop();
 
 
}