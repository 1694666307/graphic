#include<glut.h>
#include<math.h>
#include<Windows.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
GLsizei winWidth = 800, winHeight = 600;
GLuint regHex;//��ʾ���ʶ
/*�����������귶Χ*/
GLfloat xwcMin = 0.0, xwcMax = 225.0;
GLfloat ywcMin = 0.0, ywcMax = 225.0;
class wcPt3d
{
public:
	GLfloat x, y, z;

};
typedef GLfloat Matrix4x4[4][4];
Matrix4x4 matComposite;//3D�任���Ͼ���
const GLdouble pi = 3.14159;

static void init(void)
{
	//��ʼ���������������

	glClearColor(1.0, 1.0, 1.0, 0.0);//����Ϊ��ɫ����


}

void Matrix4x4SetIdentity(Matrix4x4 matIdent4x4)
{
	//����һ����λ����
	GLint row, col;
	for (row = 0; row < 4; ++row)
		for (col = 0; col < 4; ++col)
		{
			matIdent4x4[row][col] = (row == col);
		}
}
void matrix4x4Premultiply(Matrix4x4 m1, Matrix4x4 m2)
{
	//����ĳ˷������������M2��
	GLint row, col;
	Matrix4x4 matTemp;
	for (row = 0; row < 4; ++row)
		for (col = 0; col < 4; col++)
		{
			matTemp[row][col] = m1[row][0] * m2[0][col] + m1[row][1] * m2[1][col] + m1[row][2] * m2[2][col] + m1[row][3] * m2[3][col];
		}
	for (row = 0; row < 4; ++row)
		for (col = 0; col < 4; col++)
		{
			m2[row][col] = matTemp[row][col];
		}

}
void translate3D(GLfloat tx, GLfloat ty, GLfloat tz)
{
	/*ͨ��ƫ����tx,ty����ƽ�ƾ���matTransl֮����ͨ������ĳ˷���ʵ�ֶ����ƽ��*/
	Matrix4x4 matTransl;//ƽ�ƾ���
	Matrix4x4SetIdentity(matTransl);
	matTransl[0][3] = tx;
	matTransl[1][3] = ty;
	matTransl[2][3] = ty;
	/*����˷���ƽ��*/
	matrix4x4Premultiply(matTransl, matComposite);
}
void rotate3d(wcPt3d p1, wcPt3d p2, GLfloat theta)
{

	Matrix4x4 matRot;//��ת����
	GLfloat axisVecLength = sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.x - p1.x) + (p2.z - p1.z) * (p2.z - p1.z));
	GLfloat cosTheta = cos(theta);
	GLfloat oneC = 1 - cosTheta;
	GLfloat sinTheta = sin(theta);
	GLfloat ux = (p2.x - p1.x) / axisVecLength;
	GLfloat uy = (p2.y - p1.y) / axisVecLength;
	GLfloat uz = (p2.z - p1.z) / axisVecLength;

	/*����ת����ƽ�Ƶ�ԭ��*/
	translate3D(-p1.x, -p1.y, -p1.z);
	Matrix4x4SetIdentity(matRot);
	matRot[0][0] = ux * ux * oneC + cosTheta;
	matRot[0][1] = ux * uy * oneC - uz * sinTheta;
	matRot[0][2] = ux * uz * oneC + uy * sinTheta;
	matRot[1][0] = uy * uz * oneC + uz * sinTheta;
	matRot[1][1] = uy * uy * oneC + cosTheta;
	matRot[1][2] = uy * uz * oneC + uy * sinTheta;
	matRot[2][0] = uz * ux * oneC - uy * sinTheta;
	matRot[2][1] = uz * uy * oneC + ux * sinTheta;
	matRot[2][2] = uz * uz * oneC + cosTheta;
	matrix4x4Premultiply(matRot, matComposite);
	translate3D(p1.x, p1.y, p1.z);//ƽ�ƻ�ԭ����λ��

}

void translate3d(GLint nverts, wcPt3d* verts)
{
	//���󶥵��븴�ϱ任����ĳ˷����õ�����任��ĵ�
	GLint k;
	GLfloat temp;
	for (k = 0; k < nverts; ++k)
	{
		temp = verts[k].x * matComposite[0][0] + verts[k].y * matComposite[0][1] + matComposite[0][2];
		verts[k].y = verts[k].x * matComposite[1][0] + verts[k].y * matComposite[1][1] + matComposite[1][2];
		verts[k].x = temp;
	}
}
void triangle(wcPt3d* verts)
{
	//���һ���ռ�������
	GLint k;
	glBegin(GL_TRIANGLES);
	cout << "��ǰ��������Ϊ��";
	for (k = 0; k < 3; ++k)
	{
		glVertex3f(verts[k].x, verts[k].y, verts[k].z);
		cout << verts[k].x << "," << verts[k].y << "," << verts[k].z << endl;
	}
	glEnd();

}
void displayFcn()
{
	GLint nverts = 3;
	wcPt3d verts[3] = { { 50, 50 ,0 }, {200, 50,0 }, { 50, 200,0 } };//����һ��������
	GLdouble theta = pi / 4.0;//��ת45��
	wcPt3d p1, p2;
	p1.x = 0; p1.y = 0; p1.z = 0;
	p2.x = 0; p2.y = 0; p2.z = 1;//������ת��Ϊ(0,0,1)
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 1.0);
	triangle(verts);//��ɫ������Ϊԭʼ������
	Matrix4x4SetIdentity(matComposite);
	rotate3d(p1, p2, theta);//��ת
	glColor3f(1.0, 0.0, 0.0);//��ɫΪ�ƶ����������
	triangle(verts);
	translate3d(nverts, verts);
	glColor3f(0.0, 1.0, 1.0);//��ɫΪ�ƶ����������
	triangle(verts);
	glFlush();


}
void winReshapeFcn(int newWidth, int newHeight)
{
	//�����ض��κ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//����ǰ���û�����ϵ��ԭ���Ƶ�����Ļ���ģ�������һ����λ����
	glOrtho(xwcMin, xwcMax, ywcMin, ywcMax, -55, 0);
	glClear(GL_COLOR_BUFFER_BIT);


} int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 20);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Rotate 3D Object");
	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
	return 0;
}