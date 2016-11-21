/*
 * OpenGL demonstration program for ICS Computer Graphics courses
 * $Id: sceneModule.c,v 1.1 2002/04/03 00:00:43 mshafae Exp $
 *
 */

#define _USE_MATH_DEFINES

#include <math.h>

#include "sceneModule.h"
static GLfloat angleSpinner = 0;
static float cubeColors[6][4] =
{
  {0.8, 0.8, 0.8, 1.0},
  {0.8, 0.0, 0.0, 1.0},
  {0.0, 0.8, 0.0, 1.0},
  {0.0, 0.0, 0.8, 1.0},
  {0.0, 0.8, 0.8, 1.0},
  {0.8, 0.0, 0.8, 1.0},
};

static float cubeColors2[1][4] =
{
    {0.8, 0.8, 0.0, 1.0},
};

static float cubeVertexes[6][4][4] =
{
  {
    {-1.0, -1.0, -1.0, 1.0},
    {-1.0, -1.0, 1.0, 1.0},
    {-1.0, 1.0, 1.0, 1.0},
    {-1.0, 1.0, -1.0, 1.0}},

  {
    {1.0, 1.0, 1.0, 1.0},
    {1.0, -1.0, 1.0, 1.0},
    {1.0, -1.0, -1.0, 1.0},
    {1.0, 1.0, -1.0, 1.0}},

  {
    {-1.0, -1.0, -1.0, 1.0},
    {1.0, -1.0, -1.0, 1.0},
    {1.0, -1.0, 1.0, 1.0},
    {-1.0, -1.0, 1.0, 1.0}},

  {
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, -1.0, 1.0},
    {-1.0, 1.0, -1.0, 1.0},
    {-1.0, 1.0, 1.0, 1.0}},

  {
    {-1.0, -1.0, -1.0, 1.0},
    {-1.0, 1.0, -1.0, 1.0},
    {1.0, 1.0, -1.0, 1.0},
    {1.0, -1.0, -1.0, 1.0}},

  {
    {1.0, 1.0, 1.0, 1.0},
    {-1.0, 1.0, 1.0, 1.0},
    {-1.0, -1.0, 1.0, 1.0},
    {1.0, -1.0, 1.0, 1.0}}
};

void my_GL_translate(float x, float y, float z) {
	// Translation matrix stored column wise
	GLfloat tr[4][4] = { 1.0, 0.0, 0.0, 0.0, 
						 0.0, 1.0, 0.0, 0.0, 
						 0.0, 0.0, 1.0, 0.0, 
						 x, y, z, 1.0 };
	glMultMatrixf(&tr);
}

void my_GL_rotate(float angle, float x, float y, float z) {
	float c = cos(angle*M_PI/180);
	float s = sin(angle*M_PI/180);
	// Normalize xyz ??
	// Rotation matrix stored column wise
	GLfloat rot[4][4] = { x*x*(1-c)+c, y*x*(1-c)+z*s, x*z*(1-c)-y*s, 0.0,
						  x*y*(1-c)-z*s, y*y*(1-c)+c, y*z*(1-c)+x*s, 0.0,
						  x*z*(1-c)+y*s, y*z*(1-c)-x*s, z*z*(1-c)+c, 0.0,
						  0.0, 0.0, 0.0, 1.0 };
	glMultMatrixf(&rot);
}

void my_GL_scale(float x, float y, float z) {
	// Scale matrix stored column wise
	GLfloat sc[4][4] = { x, 0.0, 0.0, 0.0,
		0.0, y, 0.0, 0.0,
		0.0, 0.0, z, 0.0,
		0.0, 0.0, 0.0, 1.0 };
	glMultMatrixf(&sc);
}

void drawScene( ){
  int i;
  glPushMatrix();
  angleSpinner = angleSpinner + 1;
  //glRotatef( angleSpinner, 0.0, 1.0, 0.0 );
  my_GL_rotate(angleSpinner, 0.0, 1.0, 0.0);

  // Draw spinner cube
  for (i = 0; i < 6; ++i) {
    glBegin(GL_POLYGON);
    glColor3fv(&cubeColors[i][0]);
	GLfloat mat_shininess[] = { 50.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, &cubeColors[i][0]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &cubeColors[i][0]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
    glVertex4fv(&cubeVertexes[i][0][0]);
    glVertex4fv(&cubeVertexes[i][1][0]);
    glVertex4fv(&cubeVertexes[i][2][0]);
    glVertex4fv(&cubeVertexes[i][3][0]);
    glEnd();
  }
  glPopMatrix();
  
  glPushMatrix();
  //glRotatef( angleSpinner, 0.0, 1.0, 0.0 );
  my_GL_rotate(angleSpinner, 0.0, 1.0, 0.0);
  //glTranslatef(4, 0, 0);
  my_GL_translate(4, 0, 0);
  //glScalef(.5, .5, .5);
  my_GL_scale(.5, .5, .5);

  // Draw revolver cube
  for (i = 0; i < 6; ++i) {
     glBegin(GL_POLYGON);
     glColor3fv(&cubeColors2[0][0]);
	 GLfloat mat_shininess[] = { 50.0 };
	 glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, &cubeColors2[0][0]);
	 glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &cubeColors2[0][0]);
	 glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
     glVertex4fv(&cubeVertexes[i][0][0]);
     glVertex4fv(&cubeVertexes[i][1][0]);
     glVertex4fv(&cubeVertexes[i][2][0]);
     glVertex4fv(&cubeVertexes[i][3][0]);
     glEnd();
  }
  glPopMatrix();
}

void lightScene() {

	GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 3.0, 0.0, 0.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	glEnable(GL_LIGHTING);  // Light ON/OFF
	glEnable(GL_LIGHT0);	// Activate light 0

}
