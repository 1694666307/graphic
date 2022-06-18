//#include<Windows.h>
#include <glut.h>
#include <stdio.h>
#include <cmath>
#include <iostream>

using namespace std;

typedef float Color[3];
int dir[8][2] = { 1,0,0,1,-1,0,0,-1,1,1,1,-1,-1,1,-1,-1 };

void putpixel(int x, int y)
{
	glPointSize(2.0f);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();	
	
}

void getpixel(int x, int y, Color ans) {
	glReadPixels(x, y, 1, 1,GL_RGB,GL_FLOAT, ans);
}

int eq(Color x, Color y) {
	if (x[0] == y[0] && x[1] == y[1] && x[2] == y[2])return 1;
	return 0;
}

int fill(int x, int y) {
	Color now, next;
	getpixel(x, y, now);
	putpixel(x, y);
	for (int i = 0; i < 4; i++) {
		getpixel(x + dir[i][0], y + dir[i][1], next);
		if (eq(now, next)) {
			fill(x + dir[i][0], y + dir[i][1]);
		}
	}
	return 0;
}

GLsizei winWidth = 400, winHeight = 400;

void polygon() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);//������ʾ������ɫΪ��ɫ
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	glLineWidth(5);
	glVertex2f(100, 100);
	glVertex2f(100, 250);
	glVertex2f(250, 100);
	glEnd();
	glFlush();
}

void init(void)
{

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
}

void Display()    //��ʾ����
{
	glClear(GL_COLOR_BUFFER_BIT);    //�����ɫ��ջ
	//for (int i = 0; i < 300; i++) {
	//	putpixel(i, 50);
	//}
	polygon();
	glColor3f(0.0, 1.0, 0.0);
	fill(120, 120);
	/*
	test();
	glClear(GL_COLOR_BUFFER_BIT);

	glCallList(regHex);

	glFlush();*/
	//��ջ�����ָ��
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    //��ʼ����ʾģʽ
	glutInitWindowSize(winWidth, winHeight);    //���ô��ڳߴ�
	glutInitWindowPosition(200, 100);    //���ô���λ��
	glutCreateWindow("�������������");    //��������
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);    //���ñ�����
	glColor3f(1.0f, 0.0f, 0.0f);    //���û�����ɫ

	init();
	glutDisplayFunc(Display);

	glutMainLoop();    //�������ѭ��
	return 0;
}