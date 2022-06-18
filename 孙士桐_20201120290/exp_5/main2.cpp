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
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);//设置显示窗口颜色为白色
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

void Display()    //显示函数
{
	glClear(GL_COLOR_BUFFER_BIT);    //清空颜色堆栈
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
	//清空缓冲区指令
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    //初始化显示模式
	glutInitWindowSize(winWidth, winHeight);    //设置窗口尺寸
	glutInitWindowPosition(200, 100);    //设置窗口位置
	glutCreateWindow("绘制填充六边形");    //创建窗口
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);    //设置背景颜
	glColor3f(1.0f, 0.0f, 0.0f);    //设置画笔颜色

	init();
	glutDisplayFunc(Display);

	glutMainLoop();    //进入程序循环
	return 0;
}