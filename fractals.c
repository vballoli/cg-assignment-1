#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

/*! \brief Initializes the OpenGL window where all plots will be rendered.
*
*   Default: Set's window co-ordinates ranging from -200 to 200 pixels in x and y axes.
*
*   \param point_size Size of Pixel.
*/
void init_window (float point_size);

/*! \brief Calculates final_vertex and plots line using the Midpoint line algorithm.
*
*
*   \param start_vertex[] integer array of length 2 : {x,y} start_vertex.
*   \param slope float variable : angle in degrees.
*   \param length integer variable : length of line.
*/
void midpoint_line_slope (int start_vertex[], float slope, int length);

/*! \brief Recursive function that plots a fractal.
*
*   Recursively plots lines using the Midpoint line algorithm with random slopes and a fixed length.
*
*   \param current_position[] integer array of length 2 : {x,y} start-point co-ordinates.
*   \param max_depth integer variable : Maximum value of either x or y co-ordinates.
*   \param length integer variable : Length of line drawn from the start_point.
*/
void draw (int current_position[], int max_depth, int length);

/*! \brief Runs Mipoint Line Algorithm and Midpoint Circle Algorithm
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

    glutInitWindowSize(400, 400); // Dimensions of the window
    glutInitWindowPosition(200, 200); // Position of the window on the screen

    glutCreateWindow("Fractal"); // Naming the window
    init_window(1.0);

    glutDisplayFunc(display);
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
    if (d <= 0)
    {
      d += incrE;
    } else {
      d += incrNE;
      y++;
    }
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

void midpoint_line_slope(int start_vertex[], float slope, int length)
{
  slope = slope * (3.14/180);
  int x0 = start_vertex[0];
  int y0 = start_vertex[1];

  printf("%f\n", length*cos(slope));
  int x1 = (int)(start_vertex[0] + (rand() % 9)*(length*cos(slope)));
  int y1 = (int)(start_vertex[1] + (rand() % 9)*(length*sin(slope)));
  int end_vertex[] = {x1, y1};
  midpoint_line(start_vertex, end_vertex);
}

void draw(int current_position[], int max_depth, int length)
{
  if ((current_position[0] > max_depth) || (current_position[1] > max_depth)) {
    return;
  }

  // Slope in degrees
  int slope_p = 40 + (rand() % 40);
  int slope_n = 40 - (rand() % 40);
  double val = (float)rand()/RAND_MAX;
  glColor3f(val, val, val);
  midpoint_line_slope(current_position, slope_p, length);
  midpoint_line_slope(current_position, slope_n, length);
  current_position[0] += (rand() % 2);
  current_position[1] += (rand() % 2);
  draw(current_position, max_depth, length);
}

void display (void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    int start[] = {0,0};
    draw(start, 200, 15);
    glEnd();
    glFlush();
}
