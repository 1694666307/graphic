#include <glut.h>
#include <cstdio>

#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

GLsizei winWidth = 400, winHeight = 300;

int x1 = 150, y1 = 50, x2 = 50, y2 = 250, XL = 100, XR = 300, YB = 100, YT = 200;  //(x1,y1)、(x2,y2)为直线段的端点，XL为左边界，XR为右边界，YB为下边界，YT为上边界
int x1_init, y1_init, x2_init, y2_init;  //将直线段端点备份，以便画出裁剪前的直线段
int first = 0;

int encode(int x, int y)
{
    int c = 0;
    if (x < XL) c |= LEFT;
    if (x > XR) c |= RIGHT;
    if (y < YB) c |= BOTTOM;
    if (y > YT) c |= TOP;
    return c;
}

void CS_LineClip()  //Cohen-Sutherland裁剪算法
{
    int x, y;
    int code1, code2, code;
    code1 = encode(x1, y1);
    code2 = encode(x2, y2);
    x1_init = x1;
    y1_init = y1;
    x2_init = x2;
    y2_init = y2;

    while (code1 != 0 || code2 != 0)
    {
        if (code1 & code2)
            return;
        if (code1 != 0)
            code = code1;
        else
            code = code2;

        if (LEFT & code)
        {
            x = XL;
            y = y1 + (y2 - y1) * (XL - x1) / (x2 - x1);
        }
        else if (RIGHT & code)
        {
            x = XR;
            y = y1 + (y2 - y1) * (XR - x1) / (x2 - x1);
        }
        else if (BOTTOM & code)
        {
            y = YB;
            x = x1 + (x2 - x1) * (YB - y1) / (y2 - y1);
        }
        else if (TOP & code)
        {
            y = YT;
            x = x1 + (x2 - x1) * (YT - y1) / (y2 - y1);
        }
        if (code == code1)
        {
            x1 = x; y1 = y; code1 = encode(x1, y1);
        }
        else
        {
            x2 = x; y2 = y; code2 = encode(x2, y2);
        }
    }

}

void polyline(GLint button, GLint action, GLint xMouse, GLint yMouse) {
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
        printf("left");
        if (first == 0) {
            printf(" 1\n");
            first = 1;
            x1 = xMouse;
            y1 = winHeight - yMouse;
        }
        else {
            printf(" 2\n");
            first = 0;
            x2 = xMouse;
            y2 = winHeight - yMouse;
        }
    }
    if (button == GLUT_MIDDLE_BUTTON && action == GLUT_DOWN) {
        printf("middle\n");
        //清空
        first = 0;
        glClearColor(1.0, 1.0, 1.0, 0.0);  //设置背景颜色
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0, 0.0, 0.0);
        glPointSize(2);
        glBegin(GL_LINE_LOOP);
        glVertex2i(XL, YT);
        glVertex2i(XL, YB);
        glVertex2i(XR, YB);
        glVertex2i(XR, YT);
        glEnd();
        glFlush();
    }
    if (button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN) {
        printf("right\n");
        //裁剪并绘制
        CS_LineClip();  //执行一次裁剪算法
        glColor3f(1.0, 0.0, 0.0);
        glPointSize(2);
        //绘制未裁剪前的线段
        glBegin(GL_LINES);
        glVertex2i(x1_init, y1_init);
        glVertex2i(x2_init, y2_init);
        glEnd();
        glFlush();
        //绘制裁剪后的线段
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
        glEnd();
        glFlush();
    }
}

void winReshapeFcn(GLint newWidth, GLint newHeight) {
    glViewport(0, 0, newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, GLdouble(newWidth), 0.0, GLdouble(newHeight));

    winWidth = newWidth;
    XR = winWidth - 100;
    winHeight = newHeight;
    YT = winHeight - 100;
}

void init()  //初始化函数
{
    glClearColor(1.0, 1.0, 1.0, 0.0);  //设置背景颜色
    glMatrixMode(GL_PROJECTION);       // 设置投影参数
    gluOrtho2D(0.0, 600.0, 0.0, 400.0); // 设置场景的大小
}

void mydisplay()  //显示函数
{
    //绘制方形边界
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(2);
    glBegin(GL_LINE_LOOP);
    glVertex2i(XL, YT);
    glVertex2i(XL, YB);
    glVertex2i(XR, YB);
    glVertex2i(XR, YT);
    glEnd();
    glFlush();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Cohen-Sutherland裁剪算法");
    init();

    glutDisplayFunc(&mydisplay);
    glutReshapeFunc(winReshapeFcn);
    glutMouseFunc(polyline);

    glutMainLoop();
    return 0;
}