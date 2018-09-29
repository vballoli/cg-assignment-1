#include<stdio.h>
#include<GL/glut.h>

/*! \brief Initializes the OpenGL window where all plots will be rendered.
*
*   Default: Set's window co-ordinates ranging from -200 to 200 pixels in x and y axes.
*
*   \param point_size float variable: Size of Pixel.
*/
void init_window(float point_size);

/*! \brief Midpoint Line Algorithm.
*
*   Implements midpoint algorithm to choose between East or North-East pixel.
*
*   \param start_vertex[] integer array of length 2 : {x,y} starting vertex of the line.
*   \param end_vertex[] integer array of length 2 : {x,y} ending vertex of the line.
*/
void midpoint_line (int start_vertex[], int end_vertex[]);

/*! \brief Midpoint Circle Algorithm
*
*   Implements midpoint algorithm to choose between East or South-East pixel.
*   Algorithm return co-ordinates one quadrant and that is repeated across all
*   the other seven quadrants.
*
*   \param radius integer variable: Radius of the circle.
*/
void midpoint_circle (int radius);

/*! \brief Runs Mipoint Line Algorithm and Midpoint Circle Algorithm and plots on the window
*
*   This is the callback function passed into OpenGL.
*   Runs midpoint line algorithm to plot a line from {50,50} to {100,100}
*   Runs mipoint circle algorithm to plot a circle of radius 50 at origin.
*/
void display (void);

int main (int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(400, 400); // Window Dimensions
    glutInitWindowPosition(200, 200); // Window position on the screen

    glutCreateWindow("Midpoint Algorithms"); // Naming the Window
    init_window(1.0);

    glutDisplayFunc(display); // Pass the callback function
    glutMainLoop();
}

void init_window (float point_size)
{
    glClearColor(0.0, 0.0, 0.0, 1.0); // Colouring the background black (rgb(0,0,0))
    glColor3f(1.0, 1.0, 1.0); // Setting plot pixels to White (rgb(1,1,1))
    glPointSize(point_size); // Set's size of point plotted on the window
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200); // Window co-ordinate system.
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
    int start_vertex[] = {50,50};
    int end_vertex[] = {100,100};
    midpoint_line(start_vertex, end_vertex);
    midpoint_circle(50);
    glEnd();
    glFlush();
}
