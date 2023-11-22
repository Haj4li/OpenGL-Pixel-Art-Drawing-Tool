#ifndef ENGINE_H
#define ENGINE_H
#include <GL/glut.h>

// An Ali Nakhaee OpenGL Engine (trying my best to improve this boy)

class Engine {
public:
  static void Init(const char* title,const unsigned int width,const unsigned int height,int gl_argc = 0, char** gl_argv = nullptr);

  // The Engine call this function only once (At the beginning of the game)
  static void Start();
  // Use this function to render your shapes on the game screen
  static void Render();
  // This function runs in each frames of the game (Before the Renderer)
  static void Update();

  // Use this function to limit the Frames Per Second of the game screen's refresh rate
  // 0 means no limit
  static void SetTargetFPS(unsigned int FPS);


private:
    static int SCREEN_WIDTH;
    static int SCREEN_HEIGHT;
    static unsigned int refreshMillis;

    static int mouseX ;
    static int mouseY;
    static bool mouse[2];

    static bool keyStates[256];


    static void display();
    static void onMouseMotion(int x, int y);
    static void onReshape(int width, int height);
    static void onMouseClick(int button, int state, int x, int y);
    static void onKeyPress(unsigned char key, int x, int y);
    static void onKeyRelease(unsigned char key, int x, int y);
    static void update(int value);
};
void Draw_Circle(float centerX, float centerY, float radius, float angleStart, float angleEnd, int numSegments);


void Draw_Rectangle(float x, float y, float width, float height);



#endif // ENGINE_H
