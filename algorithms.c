#include<stdio.h>
#include<GL/glut.h>


void init_window (float point_size)
{
    glClearColor(0.0, 0.0, 0.0, 1.0); // Colouring the background black (rgb(0,0,0))
    glColor3f(1.0, 1.0, 1.0); // Setting plot pixels to White (rgb(1,1,1))
    glPointSize(point_size); // Set's size of point plotted on the window
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // setting window dimension in X- and Y- direction
    gluOrtho2D(-200, 200, -200, 200);
}

void midpoint_line(int start_vertex[], int end_vertex[])
{
  int x0 = start_vertex[0];
  int y0 = start_vertex[1];
  int x1 = end_vertex[0];
  int y1 = end_vertex[1];

  int dx = x1 - x0;
  int dy = y1 - y0;
  int d = (2*dy) - dx;
  int incrE = (2*dy);
  int incrNE = (2*(dy-dx));
  int x = x0;
  int y = y0;
  glVertex2i(x,y);

  while (x < x1)
  {
    printf("%d \t", x);
    printf("%d \n", y);
    if (d <= 0)
    {
      d += incrE;
    } else {
      d += incrNE;
      y++;
    }
    x++;
    glVertex2i(x,y);
  }
}

void midpoint_circle(int radius)
{
  int x = 0;
  int y = radius;
  int d = 1 - radius;
  int deltaE = 3;
  int deltaSE = (-2*radius) + 5;

  glVertex2i(x,y);
  glVertex2i(y,x);
  glVertex2i(-x,-y);
  glVertex2i(-y,-x);

  while(y > x)
  {
    if (d < 0) {
      d += deltaE;
      deltaSE += 2;
    } else {
      d += deltaSE;
      deltaSE += 4;
      y--;
    }
    deltaE += 2;
    x++;

    glVertex2i(x,y);
    glVertex2i(-x,y);
    glVertex2i(x,-y);
    glVertex2i(-x,-y);
    glVertex2i(y,x);
    glVertex2i(-y,x);
    glVertex2i(y,-x);
    glVertex2i(-y,-x);
  }
}

void display (void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    int start_vertex[] = {0,0};
    int end_vertex[] = {100,100};
    midpoint_line(start_vertex, end_vertex);
    midpoint_circle(50);
    glEnd();
    glFlush();
}


int main (int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // giving window size in X- and Y- direction
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(200, 200);

    // Giving name to window
    glutCreateWindow("Midpoint Algorithms");
    init_window(1.0);

    glutDisplayFunc(display);
    glutMainLoop();
}
