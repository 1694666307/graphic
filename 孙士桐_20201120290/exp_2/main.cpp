//#include<Windows.h>
#include<glut.h>
#include <stdio.h>
#include <cmath>


void setPixel(int x, int y)
{
	glPointSize(5.0f);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();

}
void lineBres(int x0, int y0, int xEnd, int yEnd) {
	int dx = fabs(xEnd - x0), dy = fabs(yEnd - y0);
	int p = 2 * dy - dx;
	int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
	int x, y;
	if (x0 > xEnd) {
		x = xEnd;
		y = yEnd;
		xEnd = x0;
	}
	else {
		x = x0;
		y = y0;
	}
	setPixel(x, y);
	while (x < xEnd) {
		x++;
		if (p < 0)
			p += twoDy;
		else {
			y++;
			p += twoDyMinusDx;
		}
		setPixel(x, y);
	}

}
void ProBresenham(int x0, int y0, int x1, int y1)    //改进的Bresenham算法
{
	int x, y, dx, dy, e;
	dx = x1 - x0;
	dy = y1 - y0;
	e = -dx;
	x = x0;
	y = y0;
	while (x <= x1) {/*
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();*/
		setPixel(x, y);
		x++;
		e = e + 2 * dy;
		if (e > 0) {
			y++;
			e = e - 2 * dx;
		}
	}
}

void init(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);//设置显示窗口颜色为白色
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0f, 200.0f, 0.0f, 150.0f);//设置规划参数
}

void myDisplay() {
	int x0, y0, xEnd, yEnd;
	printf_s("请输入点坐标（用空格作为分隔符，起点在前，终点在后）：");
	scanf_s("%d %d %d %d", &x0, &y0, &xEnd, &yEnd);
	lineBres(x0, y0, xEnd, yEnd);
}
void Display()    //显示函数
{
	int x0, y0, xEnd, yEnd;
	glClear(GL_COLOR_BUFFER_BIT);    //清空颜色堆栈
	printf_s("请输入点坐标（用空格作为分隔符，起点在前，终点在后）：");
	scanf_s("%d %d %d %d", &x0, &y0, &xEnd, &yEnd);
	ProBresenham(x0, y0, xEnd, yEnd);//画直线
 //清空缓冲区指令
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);    //初始化显示模式
	glutInitWindowSize(600, 600);    //设置窗口尺寸
	glutInitWindowPosition(200, 100);    //设置窗口位置
	glutCreateWindow("改进Bresenham算法");    //创建窗口
	glutDisplayFunc(&myDisplay);    //注册显示函数
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);    //设置背景颜色，完全不透明
	glColor3f(1.0f, 0.0f, 0.0f);    //设置画笔颜色
	glMatrixMode(GL_PROJECTION);            //设置投影
	gluOrtho2D(0.0, 600, 0.0, 600);    //设置投影区域
	glutMainLoop();    //进入程序循环

}