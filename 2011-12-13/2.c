
#include <GL/glut.h>
#include <math.h>
int width=600, height=600; /* 初期ウィンドウの大きさ */

#define SWAP(type, a, b) do { type tmp = a; a = b; b = tmp; } while(0)

void  ploti(int x, int y)
{ glBegin(GL_POINTS); glVertex2i(x,y); glEnd(); }

void  linei(int x1, int y1, int x2, int y2)
{
    int f1, f2, f3, x = 0, y = 0, e = 0;
    if(f1 = (x2 <= x1)){
        SWAP(int, x1, x2);
    }
    if(f2 = (y2 <= y1)){
        SWAP(int, y1, y2);
    }
    if(f3 = (x2 - x1 <= y2 - y1)){
        SWAP(int, x1, y1);
        SWAP(int, x2, y2);
    }
    while(1){
        int rx = f1 ? x2 - x : x1 + x, ry = f2 ? y2 - y : y1 + y;
        if(f3) ploti(ry, rx);
        else ploti(rx, ry);
        x++;
        e += y2-y1;
        if(x2-x1 <= e){
            e -= (x2 - x1);
            y++;
        }
        if(x == x2 - x1) break;
    }
}

void  circlei(int x, int y, int r)
{
    int cx = 0, cy = r, d = 3 - 2*r;
    while(1){
        ploti(x+cx, y+cy);
        ploti(x+cx, y-cy);
        ploti(x-cx, y+cy);
        ploti(x-cx, y-cy);
        ploti(x+cy, y+cx);
        ploti(x+cy, y-cx);
        ploti(x-cy, y+cx);
        ploti(x-cy, y-cx);
        if(d < 0){
            d += 6+4*cx;
        }
        else{
            d += 10+4*cx-4*cy;
            cy--;
        }
        cx++;
        if(cy < cx) break;
    }
}

void  display(void)
{
  int i,ix,iy, ix1,iy1;
  double a=1.995128, y0=0., y2, x1=0.069756;
  double b=1.989043, x0=0., x2, y1=0.104528;
  double mag;

  glClear(GL_COLOR_BUFFER_BIT);
  mag = width/3;
  ix = width/2;  iy = height/2;
  for( i=0; i<180; i++ ){
    ix1 = (int)(x1*mag) + width/2;
    iy1 = (int)(y1*mag) + height/2;
    linei( ix,iy,ix1,iy1 );
    x2 = a*x1-x0;  x0 = x1; x1 = x2;ix = ix1;
    y2 = b*y1-y0;  y0 = y1; y1 = y2;iy = iy1;
  }
  circlei( ix,iy,iy/4 );
  glFlush();
}

void  myinit(void)
{
  glClearColor (1.0, 1.0, 1.0, 0.0);  /* 背景色(白) */
  glColor3f(0.,0.,0.);                /* 描画色(黒) */
}

void  reshape(int w, int h)
{
  h = (h == 0) ? 1 : h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity(); width = w; height = h;
  glOrtho( 0.,width-1., 0.,height-1., -0.5, 10. );
  glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
    case 27:  /* ESC code */
    case 13:  exit(0);  /* RETURN (Enter) code */
    default:break;
  }
}

int  main(int argc, char** argv)
{
  glutInitWindowSize (width, height);
  glutInitWindowPosition (10, 10);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
  glutCreateWindow (argv[0]);
  myinit();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;
}
