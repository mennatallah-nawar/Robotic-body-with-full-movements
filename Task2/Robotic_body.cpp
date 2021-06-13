#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.14

static int Rightshoulder = 0, Rightelbow = 0, inner_rightarm = 0, Leftshoulder = 0, Leftelbow = 0, inner_leftarm,
Rightleg = 0, Rightleg_side = 0, Rightknee = 0, Leftleg = 0, Leftleg_side = 0, Leftknee = 0;
int moving, startx, starty;


GLfloat angle = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;   /* in degrees */

double eye[] = { 0.0, 0.0, 5.0 };
double center[] = { 0.0, 0.0, 0.0 };
double up[] = { 0.0, 1.0, 0.0 };

void rotatePoint(double a[], double theta, double p[])
{

    double temp[3];
    temp[0] = p[0];
    temp[1] = p[1];
    temp[2] = p[2];

    temp[0] = -a[2] * p[1] + a[1] * p[2];
    temp[1] = a[2] * p[0] - a[0] * p[2];
    temp[2] = -a[1] * p[0] + a[0] * p[1];

    temp[0] *= sin(theta);
    temp[1] *= sin(theta);
    temp[2] *= sin(theta);

    temp[0] += (1 - cos(theta)) * (a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
    temp[1] += (1 - cos(theta)) * (a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
    temp[2] += (1 - cos(theta)) * (a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

    temp[0] += cos(theta) * p[0];
    temp[1] += cos(theta) * p[1];
    temp[2] += cos(theta) * p[2];

    p[0] = temp[0];
    p[1] = temp[1];
    p[2] = temp[2];
}

void crossProduct(double a[], double b[], double c[])
{
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(double a[])
{
    double norm;
    norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
    norm = sqrt(norm);
    a[0] /= norm;
    a[1] /= norm;
    a[2] /= norm;
}

// Rotation about vertical direction
void lookRight()
{
    rotatePoint(up, PI / 8, eye);
}

void lookLeft()
{
    rotatePoint(up, -PI / 8, eye);
}

// Rotation about horizontal direction

void lookUp()
{
    double horizontal[3];
    double look[] = { center[0] - eye[0], center[1] - eye[1], center[2] - eye[2] };
    crossProduct(up, look, horizontal);
    normalize(horizontal);
    rotatePoint(horizontal, PI / 8, eye);
    rotatePoint(horizontal, PI / 8, up);
}

void lookDown()
{
    double horizontal[3];
    double look[] = { center[0] - eye[0], center[1] - eye[1], center[2] - eye[2] };
    crossProduct(up, look, horizontal);
    normalize(horizontal);
    rotatePoint(horizontal, -PI / 8, eye);
    rotatePoint(horizontal, -PI / 8, up);
}

// Forward and Backward
void moveForward()
{
    double direction[3];
    direction[0] = center[0] - eye[0];
    direction[1] = center[1] - eye[1];
    direction[2] = center[2] - eye[2];
    float speed = 0.1;
    eye[0] += direction[0] * speed;
    eye[1] += direction[1] * speed;
    eye[2] += direction[2] * speed;

    center[0] += direction[0] * speed;
    center[1] += direction[1] * speed;
    center[2] += direction[2] * speed;
}

void moveBackword()
{
    double direction[3];
    direction[0] = center[0] - eye[0];
    direction[1] = center[1] - eye[1];
    direction[2] = center[2] - eye[2];
    float speed = 0.1;
    eye[0] -= direction[0] * speed;
    eye[1] -= direction[1] * speed;
    eye[2] -= direction[2] * speed;

    center[0] -= direction[0] * speed;
    center[1] -= direction[1] * speed;
    center[2] -= direction[2] * speed;
}


void init(void)
{
    glMatrixMode(GL_PROJECTION);
    gluPerspective(60.0,
        1.0,
        1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}


void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2],
        center[0], center[1], center[2],
        up[0], up[1], up[2]);

    //glutSwapBuffers();


    glPushMatrix();

    glTranslatef(0.0, 1.0, -2.0);     // To show the whole body


    ////////Body//////////


    glPushMatrix();
    glScalef(1.5, 3.0, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    //////////////////////////

    ////////Head//////////

    glPushMatrix();
    glTranslatef(0.0, 2.75, 0.0);
    glutWireSphere(0.75, 14.0, 14.0);
    glPopMatrix();

    //////////////////////////

    //////// Right arm //////////

    glPushMatrix();

    glTranslatef(0.0, 1.3, 0.0);

    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslatef(-0.75, 0.0, 0.0);
    glRotatef((GLfloat)inner_rightarm, 1.0, 0.0, 0.0);
    glRotatef((GLfloat)Rightshoulder, 0.0, 0.0, 1.0);
    glTranslatef(-0.75, 0.0, 0.0);


    //Right Shoulder 

    glPushMatrix();
    glScalef(1.5, 0.4, 0.5);
    glutWireCube(1.0);
    glPopMatrix();

    //Right Elbow

    glTranslatef(-0.75, 0.0, 0.0);
    glRotatef((GLfloat)Rightelbow, 0.0, 0.0, 1.0);
    glTranslatef(-0.75, 0.0, 0.0);

    glPushMatrix();
    glScalef(1.5, 0.4, 0.5);
    glutWireCube(1.0);
    glPopMatrix();

    glPopMatrix();

    /////////////////////////////

    //////// Left arm ////////

    glPushMatrix();

    glTranslatef(0.0, 1.3, 0.0);

    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslatef(0.75, 0.0, 0.0);
    glRotatef((GLfloat)inner_leftarm, 1.0, 0.0, 0.0);
    glRotatef((GLfloat)Leftshoulder, 0.0, 0.0, 1.0);
    glTranslatef(0.75, 0.0, 0.0);


    //Left Shoulder 

    glPushMatrix();
    glScalef(1.5, 0.4, 0.5);
    glutWireCube(1.0);
    glPopMatrix();

    //Left Elbow

    glTranslatef(0.75, 0.0, 0.0);
    glRotatef((GLfloat)Leftelbow, 0.0, 0.0, 1.0);
    glTranslatef(0.75, 0.0, 0.0);

    glPushMatrix();
    glScalef(1.5, 0.4, 0.5);
    glutWireCube(1.0);
    glPopMatrix();

    glPopMatrix();

    /////////////////////////////

    ////////Right leg//////////
    glPushMatrix();

    glTranslatef(-0.5, 0.0, 0.0);

    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslatef(0.0, -1.25, 0.0);
    glRotatef((GLfloat)Rightleg_side, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)Rightleg, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -1.25, 0.0);


    //Right thigh

    glPushMatrix();
    glScalef(0.5, 2.0, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    //right knee
    glTranslatef(0.0, -1.0, 0.0);
    glRotatef((GLfloat)Rightknee, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -1.0, 0.0);
    glPushMatrix();
    glScalef(0.5, 2.0, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    //right foot
    glTranslatef(0.0, -1.0, 0.0);
    glPushMatrix();
    glScalef(0.5, 0.5, 1.5);
    glutSolidCube(1.0);
    glPopMatrix();


    glPopMatrix();
    /////////////////////////////


    ////////Left leg//////////
    glPushMatrix();

    glTranslatef(0.5, 0.0, 0.0);

    glRotatef(angle2, 1.0, 0.0, 0.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslatef(0.0, -1.25, 0.0);
    glRotatef((GLfloat)Leftleg_side, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)Leftleg, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -1.25, 0.0);


    //Left thigh

    glPushMatrix();
    glScalef(0.5, 2.0, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    //Left knee
    glTranslatef(0.0, -1.0, 0.0);
    glRotatef((GLfloat)Leftknee, 1.0, 0.0, 0.0);
    glTranslatef(0.0, -1.0, 0.0);
    glPushMatrix();
    glScalef(0.5, 2.0, 1.0);
    glutWireCube(1.0);
    glPopMatrix();

    //Left foot
    glTranslatef(0.0, -1.0, 0.0);
    glPushMatrix();
    glScalef(0.5, 0.5, 1.5);
    glutSolidCube(1.0);
    glPopMatrix();


    glPopMatrix();
    /////////////////////////////

    //End
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(85.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void reset()
{
    double e[] = { 0.0, 0.0, 5.0 };
    double c[] = { 0.0, 0.0, 0.0 };
    double u[] = { 0.0, 1.0, 0.0 };
    for (int i = 0; i < 3; i++)
    {
        eye[i] = e[i];
        center[i] = c[i];
        up[i] = u[i];
    }
}
void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        lookLeft();
        break;
    case GLUT_KEY_RIGHT:
        lookRight();
        break;
    case GLUT_KEY_UP:
        lookUp();
        break;
    case GLUT_KEY_DOWN:
        lookDown();
        break;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 's':
        if (Leftshoulder < 90)
            Leftshoulder = (Leftshoulder + 5) % 360;

        break;
    case 'S':
        if (Leftshoulder > -90)
            Leftshoulder = (Leftshoulder - 5) % 360;

        break;

    case 'i':
        if (inner_leftarm > -80)
            inner_leftarm = (inner_leftarm - 5) % 360;

        break;
    case 'I':
        if (inner_leftarm < 0)
            inner_leftarm = (inner_leftarm + 5) % 360;

        break;

    case 'c':
        if (Rightshoulder > -90)
            Rightshoulder = (Rightshoulder - 5) % 360;

        break;

    case 'C':
        if (Rightshoulder < 90)
            Rightshoulder = (Rightshoulder + 5) % 360;

        break;

    case 'o':
        if (inner_rightarm > -80)
            inner_rightarm = (inner_rightarm - 5) % 360;

        break;
    case 'O':
        if (inner_rightarm < 0)
            inner_rightarm = (inner_rightarm + 5) % 360;

        break;


    case 'e':
        if (Leftelbow < 150)
            Leftelbow = (Leftelbow + 5) % 360;

        break;
    case 'E':
        if (Leftelbow > -150)
            Leftelbow = (Leftelbow - 5) % 360;

        break;

    case 'l':
        if (Rightelbow > -150)
            Rightelbow = (Rightelbow - 5) % 360;

        break;
    case 'L':
        if (Rightelbow < 150)
            Rightelbow = (Rightelbow + 5) % 360;

        break;

    case 't':
        if (Leftleg > -80)
            Leftleg = (Leftleg - 5) % 360;

        break;
    case 'T':
        if (Leftleg < 80)
            Leftleg = (Leftleg + 5) % 360;

        break;

    case 'h':
        if (Leftleg_side < 80)
            Leftleg_side = (Leftleg_side + 5) % 360;

        break;
    case 'H':
        if (Leftleg_side > 0)
            Leftleg_side = (Leftleg_side - 5) % 360;
        break;


    case 'j':
        if (Rightleg > -80)
            Rightleg = (Rightleg - 5) % 360;
        break;
    case 'J':
        if (Rightleg < 80)
            Rightleg = (Rightleg + 5) % 360;
        break;

    case 'g':
        if (Rightleg_side > -80)
            Rightleg_side = (Rightleg_side - 5) % 360;
        break;
    case 'G':
        if (Rightleg_side < 0)
            Rightleg_side = (Rightleg_side + 5) % 360;
        break;


    case 'n':
        if (Leftknee > -80)
            Leftknee = (Leftknee - 5) % 360;
        break;
    case 'N':
        if (Leftknee < 80)
            Leftknee = (Leftknee + 5) % 360;
        break;

    case 'k':
        if (Rightknee > -80)
            Rightknee = (Rightknee - 5) % 360;
        break;
    case 'K':
        if (Rightknee < 80)
            Rightknee = (Rightknee + 5) % 360;
        break;






    case 'f':
        moveForward();
        break;
    case 'b':
        moveBackword();
        break;
    case 'r':
        reset();
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

static void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            moving = 1;
            startx = x;
            starty = y;
        }
        if (state == GLUT_UP) {
            moving = 0;
        }
    }
}


static void motion(int x, int y)
{
    if (moving) {
        angle = angle + (x - startx);
        angle2 = angle2 + (y - starty);
        startx = x;
        starty = y;
        glutPostRedisplay();
    }
}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}