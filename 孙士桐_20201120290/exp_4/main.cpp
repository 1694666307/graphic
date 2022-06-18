//#include<Windows.h>
#include <glut.h>
#include <stdio.h>
#include <cmath>
#include <iostream>

const double TWO_PI = 6.2831853;

GLsizei winWidth = 400, winHeight = 400;
GLuint regHex;

class screenPt
{
public:
	screenPt();
	~screenPt();
	GLint getx() const {
		return x;
	}
	GLint gety() const {
		return y;
	}
	void setCoords(GLint xCoord, GLint yCoord) {
		x = xCoord;
		y = yCoord;
	}
private:
	GLint x, y;
};

screenPt::screenPt()
{
	x = y = 0;
}

screenPt::~screenPt()
{
}

void init(void)
{
	screenPt hexVertex, circCtr;
	GLdouble theta;
	GLint k;

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);//������ʾ������ɫΪ��ɫ

	circCtr.setCoords(winWidth/2, winHeight/2);
	regHex = glGenLists(1);
	glNewList(regHex, GL_COMPILE);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (k = 0; k < 6; k++)
	{
		theta = TWO_PI * k / 6.0;
		hexVertex.setCoords(circCtr.getx() + 150 * cos(theta), circCtr.gety() + 150 * sin(theta));
		std::cout << circCtr.getx() + 150 * cos(theta) << ' ' << circCtr.gety() + 150 * sin(theta) << std::endl;
		glVertex2i(hexVertex.getx(), hexVertex.gety());
	}

	glEnd();
	glEndList();

}

void regHexagon(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	glCallList(regHex);

	glFlush();
}

void winReshapeFcn(int newWidth, int newHeight) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)newWidth, 0.0, (GLdouble)newHeight);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    //��ʼ����ʾģʽ
	glutInitWindowSize(winWidth, winHeight);    //���ô��ڳߴ�
	glutInitWindowPosition(200, 100);    //���ô���λ��
	glutCreateWindow("�������������");    //��������
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);    //���ñ�����

	init();
	glutDisplayFunc(regHexagon);
	glutReshapeFunc(winReshapeFcn);

	glutMainLoop();    //�������ѭ��
	return 0;
}