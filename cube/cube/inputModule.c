/*
 * OpenGL demonstration program for ICS Computer Graphics courses
 * $Id: inputModule.c,v 1.2 2002/04/03 00:36:06 mshafae Exp $
 *
 */

#include <signal.h>
//#include <unistd.h>

#include "inputModule.h"

static int motionMode;
static int startX;
static int startY;
static GLfloat angle = 20;    /* in degrees */
static GLfloat angle2 = 0;   /* in degrees */
static GLfloat xdistance = 0.0;
static GLfloat ydistance = 0.0;
static GLfloat zdistance = 20.0;


void readKeyboard( unsigned char key, int x, int y ){
  switch( key ){
  case  0x1B: /* esc */
  case  'q':
//    kill( getpid(), SIGHUP );
    break;
  case ' ':

    break;
  case ',':

    break;
  case '.':

    break;
  case 'r':
    /* reset initial view parameters */
    angle = 20;
    angle2 = 30;
    xdistance = 0.0;
    ydistance = 0.0;
    zdistance = 5.0;
    break;
  default:
    break;
  }
  glutPostRedisplay( );
}

void readSpecialKeys( int key, int x, int y ){
  switch( key ){
  case GLUT_KEY_UP:

    break;
  case GLUT_KEY_DOWN:

    break;
  case GLUT_KEY_RIGHT:

    break;
  case GLUT_KEY_LEFT:

    break;
  }
  glutPostRedisplay( );
}

void mouseButtHandler(int button, int state, int x, int y)
{
  motionMode = 0;

  switch( button ){
  case GLUT_LEFT_BUTTON:
    if( state == GLUT_DOWN ){
      /* Rotate object */
      motionMode = 1;
      startX = x;
      startY = y;
    }
    break;
  case GLUT_MIDDLE_BUTTON:
    if( state == GLUT_DOWN ){
      /* Translate object */
      motionMode = 2;
      startX = x;
      startY = y;
    }
    break;
  case GLUT_RIGHT_BUTTON:
    if( state == GLUT_DOWN ){
      /* Zoom */
      motionMode = 3;
      startX = x;
      startY = y;
    }
    break;
  }
  glutPostRedisplay( );
}

void mouseMoveHandler( int x, int y ){
  switch(motionMode){
  case 0:
    /* No mouse button is pressed... do nothing */
    /* return; */
    break;

  case 1:
    /* Calculate the rotations */
    angle = angle + (x - startX);
    angle2 = angle2 + (y - startY);
    startX = x;
    startY = y;
    break;

  case 2:
    xdistance = xdistance - (x - startX)/100.0;
    ydistance = ydistance - (y - startY)/100.0;
    startX = x;
    startY = y;
    break;

  case 3:
    zdistance = zdistance - (y - startY)/10.0;
    startX = x;
    startY = y;
    break;
  }

  glutPostRedisplay( );
}

float vecLength(float x, float y, float z){
    return sqrtf(powf(x,2) + powf(y,2) + powf(z,2));
    
}

void normalizeVector(float vec[]){
    float arr[3] = {0,0,0};
    
    for (int i = 0; i < 3; ++i){
        arr[i] = vec[i];
        printf("%f", arr[i]);
    }
    
    float len = vecLength(vec[0], vec[1], vec[2]);
    printf("%f", len);
    for (int i = 0; i < 3; ++i) {
        vec[i] = arr[i]/len;
        printf(" ");
        printf("%f", vec[i]);
    }
}

GLfloat* crossProduct(GLfloat *a, GLfloat *b)
{
    //malloc(sizeof(int) * size);
    float *Product = malloc(sizeof(float) *3);
    
    //Cross product formula
    Product[0] = (a[1] * b[2]) - (a[2] * b[1]);
    Product[1] = (a[2] * b[0]) - (a[0] * b[2]);
    Product[2] = (a[0] * b[1]) - (a[1] * b[0]);
    for (int i = 0; i< 3; ++i) {
        printf(" ");
        printf("%f", Product[i]);
    }
 
    return Product;
}

//GLfloat** multMat(GLfloat **a, GLfloat **b)
//{
//    int i, j, k;
//    
//    GLfloat *arr[4];
//    for (i=0; i<4; i++)
//        arr[i] = (GLfloat *)malloc(4 * sizeof(GLfloat));
//    int sum = 0;
//    //Multiplication Logic
//    for (i = 0; i < 4; i++) {
//        for (j = 0; j < 4; j++) {
//            sum = 0;
//            for (k = 0; k < 4; k++) {
//                sum = sum + a[i][k] * b[k][j];
//            }
//            arr[i][j] = sum;
//        }
//    }
//    return arr;
//}

void multMat(GLfloat a[][4], GLfloat b[][4], GLfloat arr[][4])
{
    // Initializing elements of matrix mult to 0.
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
        {
            arr[i][j]=0;
        }
    
    // Multiplying matrix a and b and storing in array mult.
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            for(int k = 0; k < 4; ++k)
            {
                arr[i][j] += a[i][k] * b[k][j];
            }
}

void my_GL_lookAt(float eyeX, float eyeY, float eyeZ, float atX, float atY, float atZ, float upX, float upY, float upZ){
    
    GLfloat f[3] = { atX - eyeX, atY - eyeY, atZ - eyeZ };
    float up[3] = {upX, upY, upZ};
    GLfloat mat[4][4];

    //normatlize f
    printf("%lu", sizeof(f));
    normalizeVector(f);
    float *side = crossProduct(f, up);

    normalizeVector(side);
    
    //Recompute up as: up = side x forward
    float *up_normalized = crossProduct(side, f);
    normalizeVector(up_normalized);
    
    mat[0][0] = side[0];
    mat[1][0] = side[1];
    mat[2][0] = side[2];
    mat[3][0] = 0.0;
    
    //
    mat[0][1] = up_normalized[0];
    mat[1][1] = up_normalized[1];
    mat[2][1] = up_normalized[2];
    mat[3][1] = 0.0;
    
    //
    mat[0][2] = -f[0];
    mat[1][2] = -f[1];
    mat[2][2] = -f[2];
    mat[3][2] = 0.0;
    
    mat[0][3] = mat[1][3] = mat[2][3] = 0.0;
    mat[3][3] = 1.0;

    
    glMultMatrixf(mat);
    glTranslatef(-eyeX, -eyeY, -eyeZ);
    
    
}



void setUserView(){
    glLoadIdentity( );
    
    //  glTranslatef(-distanceX, distanceY, -distanceZ);
    //  glRotatef( anglex, 1.0, 0.0, 0.0 );
    //  glRotatef( angley, 0.0, 1.0, 0.0 );
    
    // The code below should have exactly the same behavior as the three
    //lines above.
    GLdouble eyeX, eyeY, eyeZ;
    GLdouble atX = 0, atY = 0, atZ = 0;
    GLdouble upX = 0, upY = 1, upZ = 0;
    
    
    
    while(angle2 < 0)
        angle2 += 360;
    
    while(angle2 >= 360)
        angle2 -= 360;
    
    if (angle2 > 90 && angle2 < 270)
        upY = -1;
    
    double radian_x = angle2 * (M_PI / 180), radian_y = angle * (M_PI / 180);
    
    eyeX = xdistance * cos(radian_y) - sin(radian_y) * sin(radian_x) *
    ydistance - sin(radian_y) * cos(radian_x) * zdistance;
    
    eyeY = -cos(radian_x) * ydistance + sin(radian_x) * zdistance;
    
    eyeZ = sin(radian_y) * xdistance - cos(radian_y) * sin(radian_x) *
    ydistance + cos(radian_y) * cos(radian_x) * zdistance;
    
    my_GL_lookAt(eyeX, eyeY, eyeZ, atX, atY, atZ, upX, upY, upZ);
}

