#include <windows.h>
#include <glut.h>
#include <stdlib.h>
#include<math.h>
void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);  // ָ�������ɫ������ɫ��Ϊ��ɫ
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);   //ָ����ά����ϵ�б���ʾ������
}

void lineSegment(void)
{
    glClear(GL_COLOR_BUFFER_BIT);  // �����ʾ����
    glColor3f(0.0, 0.4, 0.2);      // ָ��ǰ��ɫ����ǰ������ɫ��Ϊ��ɫ
    glBegin(GL_LINES);
    glVertex2i(180, 15);       // ָ������
    glVertex2i(10, 145);
    glEnd();
    glFlush();     // ʹ����������ӳ����Ļ��
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);                         // ��ʼ GLUT.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   //�趨��ʾģʽ
    glutInitWindowPosition(500, 200);   // �趨����λ��
    glutInitWindowSize(400, 300);      // �趨���ڴ�С
    glutCreateWindow("An Example OpenGL Program");
    // ��ǰ��ָ�������������ڣ������崰������
    init();                            // ����һЩ��ʼ������
    glutDisplayFunc(lineSegment);       // ָ�����ƵĻص�����
    glutMainLoop();          // ��������ѭ�����ȴ��¼�����
}