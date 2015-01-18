
#include "../HeadFile/gltools.h"
#include "../HeadFile/math3d.h"
#include <math.h>

#define SMALL_STARS 100
M3DVector2f vSmallStars[SMALL_STARS];

#define MEDIUM_STARS 40
M3DVector2f vMediumStars[MEDIUM_STARS];

#define LARGE_STARS 15
M3DVector2f vLargeStars[LARGE_STARS];

#define SCREEN_X    800
#define SCREEN_Y    600

// ��Ⱦ�����ķ���
void RenderScene()
{
	int i;
	GLfloat x = 700.0f;
	GLfloat y = 500.0f;
	GLfloat r = 50.0f;
	GLfloat angle = 0.0f;

	// �����ɫ����������Ȼ�����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// ���û�ͼ����ɫΪ��ɫ
	glColor3f(1.0f, 1.0f, 1.0f);
	// ���û���Ĵ�СΪ1.0
	glPointSize(1.0f);
	// ����С�ŵĶ���
	glBegin(GL_POINTS);
		for (i = 0; i < SMALL_STARS; ++i) {
			glVertex2fv(vSmallStars[i]);
		}
	glEnd();

	// ���û���Ĵ�СΪ3.0
	glPointSize(3.0f);
	// �����кŵĶ���
	glBegin(GL_POINTS);
	for(i = 0; i< MEDIUM_STARS; i++)
		glVertex2fv(vMediumStars[i]);
	glEnd();

	// ���û���Ĵ�СΪ5.0
	glPointSize(5.0f);
	// ���ƴ�ŵĶ���
	glBegin(GL_POINTS);
	for(i = 0; i < LARGE_STARS; i++)
		glVertex2fv(vLargeStars[i]);
	glEnd();

	// ����������
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y);
		for (angle = 0; angle < 2.0f * 3.141592f; angle += 0.1f){
			glVertex2f(x + (float)cos(angle) * r, y + (float)sin(angle) * r);
			glVertex2f(x + r, y);
		}
	glEnd();

	// �����߿�Ϊ3.5
	glLineWidth(3.5);
	// ����һ���ߴ�
	glBegin(GL_LINE_STRIP);
		glVertex2f(0.0f, 25.0f);
		glVertex2f(50.0f, 100.0f);
		glVertex2f(100.0f, 25.0f);
		glVertex2f(225.0f, 125.0f);
		glVertex2f(300.0f, 50.0f);
		glVertex2f(375.0f, 100.0f);
		glVertex2f(460.0f, 25.0f);
		glVertex2f(525.0f, 100.0f);
		glVertex2f(600.0f, 20.0f);
		glVertex2f(675.0f, 70.0f);
		glVertex2f(750.0f, 25.0f);
		glVertex2f(800.0f, 90.0f);    
	glEnd();

	// ��������������ʾ����
	glutSwapBuffers();
}

// ������Ⱦ״̬�ķ���
void SetupRC()
{
	int i;
	// ��ʼ��С�Ŷ����λ������
	for (i = 0; i < SMALL_STARS; ++i) {
		vSmallStars[i][0] = (GLfloat)(rand() % SCREEN_X);
		vSmallStars[i][1] = (GLfloat)(rand() % (SCREEN_Y - 100)) + 100.0f;
	}
	// ��ʼ���кŶ����λ������
	for(i = 0; i < MEDIUM_STARS; i++)
	{
		vMediumStars[i][0] = (GLfloat)(rand() % SCREEN_X * 10)/10.0f;
		vMediumStars[i][1] = (GLfloat)(rand() % (SCREEN_Y - 100))+100.0f;
	}
	// ��ʼ����Ŷ����λ������
	for(i = 0; i < LARGE_STARS; i++)
	{
		vLargeStars[i][0] = (GLfloat)(rand() % SCREEN_X*10)/10.0f;
		vLargeStars[i][1] = (GLfloat)(rand() % (SCREEN_Y - 100)*10.0f)/ 10.0f +100.0f;
	}
	// ���������ɫΪ��ɫ
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
}

// �����Ҽ��˵��ķ���
void ProcessMenu(int value)
{
	switch(value)
	{
	case 1:
		// ���û������
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// ���û��
		glEnable(GL_BLEND);
		// ���õ�ƽ������
		glEnable(GL_POINT_SMOOTH);
		// ����Ϊ�������ŵķ�ʽ
		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
		// ����ֱ��ƽ������
		glEnable(GL_LINE_SMOOTH);
		// ����Ϊ�������ŵķ�ʽ
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		// ���ö����ƽ������
		glEnable(GL_POLYGON_SMOOTH);
		// ����Ϊ�������ŵķ�ʽ
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		break;
	case 2:
		// �رջ��
		glDisable(GL_BLEND);
		// �رյ�ƽ������
		glDisable(GL_POINT_SMOOTH);
		// �ر�ֱ��ƽ������
		glDisable(GL_LINE_SMOOTH);
		// �رն����ƽ������
		glDisable(GL_POLYGON_SMOOTH);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
	if(h == 0)
		h = 1;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0.0, SCREEN_X, 0.0, SCREEN_Y);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Smoother Demo");
	// �����Ҽ��˵�
	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Antialiased Rendering",1);
	glutAddMenuEntry("Normal Rendering",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();

	return 0;
}