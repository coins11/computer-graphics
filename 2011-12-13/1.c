#include <GL/glut.h>
#include <math.h>
int  width=600, height=600; // 初期ウィンドウの大きさ

void  ploti(int x, int y)
{
  glBegin(GL_POINTS); glVertex2i(x,y); glEnd();
}

void line(int x1, int y1, int x2, int y2)
{
    int x = x1, y = y1, e = 0;
    while(1){
        ploti(x, y);
        x++;
        e += y2-y1;
        if(x2-x1 <= e){
            e -= (x2-x1);
            y++;
        }
        if(x == x2) break;
    }
}

void octant(int r)
{
    int x = 0, y = r, d = 3 - 2*r;
    while(1){
        ploti(x, y);
        if(d < 0){
            d += 6+4*x;
        }
        else{
            d += 10+4*x-4*y;
            y--;
        }
        x++;
        if(y < x) break;
    }
}

void  display(void)
{
  int i,x,y,x2;
  double a=1.99239, u=0., v=0.087156, w;
  double p=1., q=0.99619, r, m=400.;

  glClear(GL_COLOR_BUFFER_BIT);
  line( 0,0,(int)m,0 );
  line( 0,0,(int)(m*q),(int)(m*v) );
  for( i=5; i<45; i+=5 ){
    w = a*v - u;  r = a*q - p;
    x = (int)(m*r); y = (int)(m*w);  line( 0,0,x,y );
    u = v; v = w; p = q; q = r;
  }
  for( i=20; i<=400; i+=20 ) octant( i );
  glFlush();
}

void myinit(void)
{
  glClearColor (1.0, 1.0, 1.0, 0.0); /* background color */
  glColor3f(0.,0.,0.);             /* drawing color */
}

void  reshape(int w, int h)
{
  h = (h == 0) ? 1 : h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  width = w; height = h;
  glOrtho(-100.,width-101.,-100.,height-101.,-1.,1. );
  glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
    case 27:  /* ESC code */
    case 13:  exit(0);  /* RETURN code */
    default:  break;
  }
}

int  main(int argc, char** argv)
{
  glutInitWindowSize (width, height);
  glutInitWindowPosition (10, 10);
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutCreateWindow (argv[0]);
  myinit();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}

