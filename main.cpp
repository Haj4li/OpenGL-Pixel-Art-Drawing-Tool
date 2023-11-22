#include "Engine.h"
#include <iostream>
#include <vector>

// https://github.com/Haj4li

#define WIDTH 1000
#define HEIGHT 650

int spaces = 15;

int fixed_pos_x = 0;
int fixed_pos_y = 0;

int r=50,g,b;

bool sliding = false;
unsigned short slide_id = 0;
int start = HEIGHT-50;

struct Box{
    int x,y,r,g,b;
    Box();
    Box(int x, int y, int r, int g, int b)
        : x(x), y(y), r(r), g(g), b(b)
    {}
    void Draw()
    {
        glColor3ub(r,g,b);
        Draw_Rectangle(x,y,spaces,spaces);
    }
};
struct Rectangles {
    float x, y, width, height;
    Rectangles(int x,int y,int w,int h):
        x(x),y(y),width(w),height(h)
        {

        }
};
bool isCollision(const Rectangles& rect1, const Rectangles& rect2) {
    // Calculate the right, left, top, and bottom edges of each rectangle
    float rect1Left = rect1.x;
    float rect1Right = rect1.x + rect1.width;
    float rect1Top = rect1.y + rect1.height;
    float rect1Bottom = rect1.y;

    float rect2Left = rect2.x;
    float rect2Right = rect2.x + rect2.width;
    float rect2Top = rect2.y + rect2.height;
    float rect2Bottom = rect2.y;

    // Check for collision
    if (rect1Right < rect2Left || rect1Left > rect2Right || rect1Top < rect2Bottom || rect1Bottom > rect2Top) {
        // No collision
        return false;
    }

    // Collided
    return true;
}

std::vector<Box> boxes;

void Engine::Start()
{
    Engine::SetTargetFPS(15);

}

void Engine::Update()
{
    // Set a fixed position for drawing pixels (Rects)
    fixed_pos_x = mouseX/15;
    fixed_pos_y = mouseY/15;
    fixed_pos_x *= 15;
    fixed_pos_y *= 15;



    // Check if user trying to slide the color sliders
    if (isCollision(Rectangles(20,start+1,255,13),Rectangles(mouseX,mouseY,1,1)))
    {
        sliding = true;
        slide_id = 0;

    }
    else if (isCollision(Rectangles(20,start+1-20,255,13),Rectangles(mouseX,mouseY,1,1)))
    {
        sliding = true;
        slide_id = 1;

    }
    else if (isCollision(Rectangles(20,start+1-40,255,13),Rectangles(mouseX,mouseY,1,1)))
    {
        sliding = true;
        slide_id = 2;

    }
    else
    {
        sliding = false;
    }



    if (mouse[0] && !sliding)
    {
        if (mouseX < 20+255 && mouseY > start-75)
        {
            ;
        }
        else // Add new pixels
        {
            bool ok = false;
            //mouse[0] = false;
            for (int i = 0;i<boxes.size();++i)
            {
                if (boxes[i].x == fixed_pos_x && boxes[i].y == fixed_pos_y)
                {
                    boxes[i].r =r;
                    boxes[i].g = g;
                    boxes[i].b = b;
                    ok = true;

                }
            }
            if (!ok)
            {
                boxes.push_back(Box(fixed_pos_x,fixed_pos_y,r,g,b));
            }
        }
    }
    if (mouse[2]) // Remove pixels
    {
        //mouse[2] = false;
        for (int i = 0;i<boxes.size();++i)
        {
            if (boxes[i].x == fixed_pos_x && boxes[i].y == fixed_pos_y)
            {
                boxes.erase(boxes.begin()+i);
            }
        }
    }
    if (mouse[0] && sliding) // Change the colors
    {
        if (mouseX >= 20 && mouseX <= 255+20)
        {
            if (slide_id == 0)
                r = mouseX-20;
            else if (slide_id == 1)
                g = mouseX-20;
            else if (slide_id == 2)
                b = mouseX-20;
        }

    }


}
void DrawSlider()
{
    // Red
    glColor3ub(r,0,0);
    Draw_Rectangle(20,start,255,15);
    glColor3ub(255,0,0);
    Draw_Rectangle(20+r,start+1,20,13);
    // Green
    glColor3ub(0,g,0);
    Draw_Rectangle(20,start-20,255,15);
    glColor3ub(0,255,0);
    Draw_Rectangle(20+g,start-20+1,20,13);
    // Green
    glColor3ub(0,0,b);
    Draw_Rectangle(20,start-40,255,15);
    glColor3ub(0,0,255);
    Draw_Rectangle(20+b,start-40+1,20,13);

    // Color
    glColor3ub(r,g,b);
    Draw_Rectangle(20,start-75,50,25);

}
void DrawLines(int width,int height,int space,int line_width = 1)
{
    glLineWidth(line_width);
    glBegin(GL_LINES);
    for (int x = 0; x <= width/space;++x)
    {
        // HORIZONTAL LINES
        glVertex2f((x*space),0);
        glVertex2f((x*space),height);
    }
    for (int y = 0; y <= height/space;++y)
    {
        // VERTICAL LINES
        glVertex2f(0,(y*space));
        glVertex2f(width,(y*space));
    }

    glEnd();
}
void Engine::Render()
{
    glColor3ub(0,0,0);
    DrawLines(WIDTH,HEIGHT,spaces);
    DrawSlider();

    // draw rect in the middle of mouse pointer

    if (mouseX < 20+255 && mouseY > start-75)
    {
        ;
    }
    else
    {
        glColor3ub(r,g,b);
        Draw_Rectangle(fixed_pos_x,fixed_pos_y,spaces,spaces);
    }


    for (int i = 0;i<boxes.size();++i)
    {
        boxes[i].Draw();
    }

}

int main(int argc, char** argv) {
    Engine::Init("Creeper | Ali Nakhaee",WIDTH,HEIGHT);
    return 0;
}
