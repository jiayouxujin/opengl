#include <gl/glut.h>
#include <cstdio>
int iPointNum = 0;                     //��ȷ�������Ŀ
int x1=0,x2=0,y1=0,y2=0;               //ȷ���ĵ�����
int winWidth = 400, winHeight = 300;     //���ڵĿ�Ⱥ͸߶�
int Value=1;
void Initial(void)
{
       glClearColor(1.0f, 1.0f, 1.0f, 1.0f);        
}
 
void ChangeSize(int w, int h)
{
       winWidth = w;       winHeight = h;
       glViewport(0, 0, w, h);                 //ָ��������ʾ����
       glMatrixMode(GL_PROJECTION);      //����ͶӰ����
       glLoadIdentity();
       gluOrtho2D(0.0,winWidth,0.0,winHeight);
}
void ChangeSize(int value){
       glMatrixMode(GL_PROJECTION);      //����ͶӰ����
       glLoadIdentity();
	switch(value){
	case 1:
		gluOrtho2D(0.0,winWidth,0.0,winHeight);
		break;
	case 2:
		gluOrtho2D(0.0,winWidth,0.0,winHeight);
		break;
	case 3:
		gluOrtho2D(-winWidth/2,winWidth/2,-winHeight/2,winHeight/2);
		break;
	}
}
void mymenu(int value){
 Value=value;
 ChangeSize(value);
 glutPostRedisplay();
// printf("���е�����");
}
void MidBresenhan(int x1,int y1,int x2,int y2){
	int a,b;
	if(y2>y1) b=y2-y1;
	else b=y1-y2;
	if(x1>x2) a=x1-x2;
	else a=x2-x1;
	int x,y;
	  double d1,d2;
	 glBegin(GL_POINTS);
     x=0;
	 y=b;
	 d1=b*b+a*a*(-b+0.25);
	 glVertex2i(x,y);
	 glVertex2i(-x,-y);
	 glVertex2i(-x,y);
	 glVertex2i(x,-y);
     while(b*b*(x+1)<a*a*(y-0.5))
	 {
         if(d1<=0)
		 {
             d1+=b*b*(2*x+3);
			 x++;
		 }
         else
		 {
             d1+=b*b*(2*x+3)+a*a*(-2*y+2);
			 x++;
             y--;
         }
		glVertex2i(x,y);
		glVertex2i(-x,-y);
		glVertex2i(-x,y);
		glVertex2i(x,-y);
     }/*while�ϰ벿��*/
	  d2=-1;
	 //d2=b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b*b;
	 while(y>0)
	 {
		 if(d2<=0)
		 {
			 d2+=b*b*(2*x+2)+a*a*(-2*y+3);
			 x++;
			 y--;
		 }
		 else
		 {
			 d2+=a*a*(-2*y+3);
			 y--;
		 }
		glVertex2i(x,y);
		glVertex2i(-x,-y);
		glVertex2i(-x,y);
		glVertex2i(x,-y);
	 }
	  glEnd();
}
void Display(void)
{
       glClear(GL_COLOR_BUFFER_BIT);
	   glColor3f(1.0f, 0.0f, 0.0f);
       if(iPointNum >= 1&&Value==1)       {
              glBegin(GL_LINES);              //����ֱ�߶�
                     glVertex2i(x1,y1);
                     glVertex2i(x2,y2);
              glEnd();
       }
	   if(iPointNum >= 1&&Value==2)       {
		     glPolygonMode(GL_BACK,GL_LINE);
             glRecti(x1,y1,x2,y2);
       }
	   if(iPointNum>=1&&Value==3){
		   MidBresenhan(x1,y1,x2,y2);
	   }
	    glutSwapBuffers();                    //����������
}
 
void MousePlot(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
       if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)       {
              if(iPointNum == 0 || iPointNum == 2){
                     iPointNum = 1;
                     x1 = xMouse;         y1 = winHeight - yMouse;
              }
              else {
                     iPointNum = 2;
                     x2 = xMouse;         y2 = winHeight - yMouse;
                     glutPostRedisplay();                  //ָ���������»���
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
 
int main(int argc, char* argv[])
{
       glutInit(&argc, argv);
       glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   //ʹ��˫���漰RGBģ��
       glutInitWindowSize(400,300);
       glutInitWindowPosition(100,100);
       glutCreateWindow("ʵ��2 ��Բ���е�Bresenham");
       glutDisplayFunc(Display);
       glutReshapeFunc(ChangeSize);                //ָ�����������λص�����  
	   glutCreateMenu(mymenu);//ע��˵��ص�����
	   glutAddMenuEntry("ֱ��",1);//��Ӳ˵���
	   glutAddMenuEntry("����",2);
	   glutAddMenuEntry("��Բ",3);
	   glutAttachMenu(GLUT_RIGHT_BUTTON);//�ѵ�ǰ�˵�ע�ᵽָ��������
       glutMouseFunc(MousePlot);                  //ָ�������Ӧ����
       glutPassiveMotionFunc(PassiveMouseMove);    //ָ������ƶ���Ӧ����
       Initial();                                   
       glutMainLoop();                               
       return 0;
}