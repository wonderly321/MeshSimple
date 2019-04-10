#include <iostream>
#include <cstdlib>
#include "../include/Simplification.h"
#include <gl/glut.h>
#include "../include/Point.h"
#include "../include/Face.h"

using namespace std;

//相机位置  
static GLdouble viewer[] = { 0, 0, 1};
//旋转角度  
static GLdouble theta[] = { 0, 0, 0 };
//顶点表  
vector<Point> vert;
//三角形信息表  
vector<Face> face;
//顶点个数  
int num_vertex = 0;
//三角形个数  
int num_triangle = 0;

void draw()
{
	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 1);
	for (int i = 0; i < num_triangle; i++)
	{
		int a = face[i].p[0] -1;
		int b = face[i].p[1]-1;
		int c = face[i].p[2]-1;
		glVertex3f(vert[a].cdt.x*5, vert[a].cdt.y*5, vert[a].cdt.z*5);
		glVertex3f(vert[b].cdt.x*5, vert[b].cdt.y*5, vert[b].cdt.z*5);
		glVertex3f(vert[c].cdt.x*5, vert[c].cdt.y*5, vert[c].cdt.z*5);
	}
	glEnd();
}

void myReshap(int width, int height)
{
	glClearColor(1, 1, 1, 1);
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (width <= height)
		glFrustum(-1, 1, -1 * (GLfloat)height / (GLfloat)width, 1 * (GLfloat)height / (GLfloat)width, 1, 5);
	else
		glFrustum(-1 * (GLfloat)width / (GLfloat)height, 1 * (GLfloat)width / (GLfloat)height, -1, 1, 1, 5);

	glMatrixMode(GL_MODELVIEW);
}

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(viewer[0], viewer[1], viewer[2], 0, 0, 0, 0, 1, 0);

	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);

	draw();

	glFlush();
	glutSwapBuffers();
}

void KeyboardFunc(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		theta[2]++;
		break;
	case GLUT_KEY_RIGHT:
		theta[2]--;
		break;
	case GLUT_KEY_UP:
		theta[0]--;
		break;
	case GLUT_KEY_DOWN:
		theta[0]++;

	default:
		break;
	}
	glutPostRedisplay();
}



int main(int argc, char** argv)
{
	if(argc != 4)
	{
		cout << "Parameters error." << endl;
		cout << "Usage: MeshSimple [inputPath] [outputPath] [ratio]" << endl;
		return 1;
	}
	Simplification s;
	s.setInput(string(argv[1]));
	s.setOutput(string(argv[2]));
	s.setRatio(atof(argv[3]));
	s.execute();
	s.saveFile(vert, face);
	
	num_vertex = vert.size();
	num_triangle = face.size();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(650, 450);
	glutCreateWindow("CG-After MeshSimplify");
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glutReshapeFunc(myReshap);
	glutDisplayFunc(myDisplay);
	glutSpecialFunc(KeyboardFunc);

	glutMainLoop();
	return 0;
}