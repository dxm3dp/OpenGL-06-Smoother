
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

// 渲染场景的方法
void RenderScene()
{
	int i;
	GLfloat x = 700.0f;
	GLfloat y = 500.0f;
	GLfloat r = 50.0f;
	GLfloat angle = 0.0f;

	// 清除颜色缓冲区和深度缓冲区
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 设置绘图的颜色为白色
	glColor3f(1.0f, 1.0f, 1.0f);
	// 设置画点的大小为1.0
	glPointSize(1.0f);
	// 绘制小号的顶点
	glBegin(GL_POINTS);
		for (i = 0; i < SMALL_STARS; ++i) {
			glVertex2fv(vSmallStars[i]);
		}
	glEnd();

	// 设置画点的大小为3.0
	glPointSize(3.0f);
	// 绘制中号的顶点
	glBegin(GL_POINTS);
	for(i = 0; i< MEDIUM_STARS; i++)
		glVertex2fv(vMediumStars[i]);
	glEnd();

	// 设置画点的大小为5.0
	glPointSize(5.0f);
	// 绘制大号的顶点
	glBegin(GL_POINTS);
	for(i = 0; i < LARGE_STARS; i++)
		glVertex2fv(vLargeStars[i]);
	glEnd();

	// 绘制三角形
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y);
		for (angle = 0; angle < 2.0f * 3.141592f; angle += 0.1f){
			glVertex2f(x + (float)cos(angle) * r, y + (float)sin(angle) * r);
			glVertex2f(x + r, y);
		}
	glEnd();

	// 设置线宽为3.5
	glLineWidth(3.5);
	// 绘制一条线带
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

	// 交换缓冲区，显示画面
	glutSwapBuffers();
}

// 设置渲染状态的方法
void SetupRC()
{
	int i;
	// 初始化小号顶点的位置数组
	for (i = 0; i < SMALL_STARS; ++i) {
		vSmallStars[i][0] = (GLfloat)(rand() % SCREEN_X);
		vSmallStars[i][1] = (GLfloat)(rand() % (SCREEN_Y - 100)) + 100.0f;
	}
	// 初始化中号顶点的位置数组
	for(i = 0; i < MEDIUM_STARS; i++)
	{
		vMediumStars[i][0] = (GLfloat)(rand() % SCREEN_X * 10)/10.0f;
		vMediumStars[i][1] = (GLfloat)(rand() % (SCREEN_Y - 100))+100.0f;
	}
	// 初始化大号顶点的位置数组
	for(i = 0; i < LARGE_STARS; i++)
	{
		vLargeStars[i][0] = (GLfloat)(rand() % SCREEN_X*10)/10.0f;
		vLargeStars[i][1] = (GLfloat)(rand() % (SCREEN_Y - 100)*10.0f)/ 10.0f +100.0f;
	}
	// 设置清除颜色为黑色
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
}

// 处理右键菜单的方法
void ProcessMenu(int value)
{
	switch(value)
	{
	case 1:
		// 设置混合因子
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// 启用混合
		glEnable(GL_BLEND);
		// 启用点平滑处理
		glEnable(GL_POINT_SMOOTH);
		// 设置为画面最优的方式
		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
		// 启用直线平滑处理
		glEnable(GL_LINE_SMOOTH);
		// 设置为画面最优的方式
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		// 启用多边形平滑处理
		glEnable(GL_POLYGON_SMOOTH);
		// 设置为画面最优的方式
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		break;
	case 2:
		// 关闭混合
		glDisable(GL_BLEND);
		// 关闭点平滑处理
		glDisable(GL_POINT_SMOOTH);
		// 关闭直线平滑处理
		glDisable(GL_LINE_SMOOTH);
		// 关闭多边形平滑处理
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
	// 创建右键菜单
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