#include "Engine.h"
#include <math.h>
int Engine::SCREEN_WIDTH;
int Engine::SCREEN_HEIGHT;
unsigned int Engine::refreshMillis = 1000/60;

int Engine::mouseX = 0;
int Engine::mouseY = 0;
bool Engine::mouse[2];

bool Engine::keyStates[256];


void Engine::Init(const char* title,const unsigned int width,const unsigned int height,int gl_argc, char** gl_argv)
{
    glutInit(&gl_argc, gl_argv);

    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(title);
    glutDisplayFunc(display);

    glutMotionFunc(onMouseMotion);
    glutPassiveMotionFunc(onMouseMotion);
    glutReshapeFunc(onReshape);
    glutMouseFunc(onMouseClick);

    glutKeyboardFunc(onKeyPress);
    glutKeyboardUpFunc(onKeyRelease);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, SCREEN_WIDTH-1, 0.0, SCREEN_HEIGHT-1);

    Start();
    glutTimerFunc(0, update, 0);
    glutMainLoop();

}
void Engine::display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    Render();

    glFlush();
}

void Engine::onReshape(int width, int height)
{
    // Update the SCREEN_WIDTH and SCREEN_HEIGHT when the window is resized
    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;

    // Set the viewport and projection matrix accordingly
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}



void Engine::update(int value)
{
    glutPostRedisplay();

    Update();

    glutTimerFunc(refreshMillis, update, 0);
}
void Engine::onMouseClick(int button, int state, int x, int y)
{
    mouse[button] = state == GLUT_DOWN;
    mouseX = x;
    mouseY = SCREEN_HEIGHT-y;
}


void Engine::onMouseMotion(int x, int y)
{
    mouseX = x;
    mouseY = SCREEN_HEIGHT-y;
}
void Engine::onKeyPress(unsigned char key, int x, int y)
{
    keyStates[key] = true;
}
void Engine::onKeyRelease(unsigned char key, int x, int y)
{
    keyStates[key] = false;
}
void Engine::SetTargetFPS(unsigned int FPS)
{
    if (FPS == 0)
    {
        refreshMillis = 0;
        return;
    }
    refreshMillis = 1000/FPS;
}

void Draw_Circle(float centerX, float centerY, float radius, float angleStart, float angleEnd, int numSegments)
{

    const float angleStep = (angleEnd - angleStart) / numSegments;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY); // Center point

    for (int i = 0; i <= numSegments; ++i)
    {
        const float angle = angleStart + i * angleStep;
        const float x = centerX + radius * cos(angle * M_PI / 180.0f);
        const float y = centerY + radius * sin(angle * M_PI / 180.0f);
        glVertex2f(x, y);
    }

    glEnd();

}
void Draw_Rectangle(float x, float y, float width, float height) {
    // Calculate the coordinates of the four corners of the rectangle
    float x1 = x;
    float y1 = y;
    float x2 = x + width;
    float y2 = y;
    float x3 = x;
    float y3 = y + height;
    float x4 = x + width;
    float y4 = y + height;

    glBegin(GL_TRIANGLES);

    // First triangle (top-left, top-right, bottom-left)
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x3, y3);

    // Second triangle (top-right, bottom-left, bottom-right)
    glVertex2f(x2, y1);
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);

    glEnd();
}




