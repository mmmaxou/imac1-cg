#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define SEG_NUMBER 50
#define SEG_SPACE PI/SEG_NUMBER
#define PI 3.141592


static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 800;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void drawLandmark();
void drawSquare(int full);
void drawCircle(int full);
void resizeViewport();

/* CE TP */
void drawClock();
void drawSmallNeedle( int angle );
void drawMiddleNeedle( int angle );
void drawLargeNeedle( int angle );

int main(int argc, char** argv) {
  // Initialisation de la SDL
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
      fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
      return EXIT_FAILURE;
  }

  // Ouverture d'une fenêtre et création d'un contexte OpenGL
  if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
      fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
      return EXIT_FAILURE;
  }
  SDL_WM_SetCaption("C L O C K", NULL);
  resizeViewport();


  /* Boucle de dessin (à décommenter pour l'exercice 3) */
  int loop = 1;
  glClearColor(0.1, 0.1, 0.1 ,1.0);    
  
  /* TIME */
  time_t rawtime;
  struct tm * timeinfo;

  while(loop) {

    Uint32 startTime = SDL_GetTicks();

    // TODO: Code de dessin
    glClear(GL_COLOR_BUFFER_BIT);

    // ROTATING CLOCK
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    drawClock();
    glColor3ub(0,0,0);
    drawSmallNeedle(timeinfo->tm_sec * 6);
    drawMiddleNeedle(timeinfo->tm_min * 6 + (timeinfo->tm_sec/10));
    drawLargeNeedle(timeinfo->tm_hour * 30 + (timeinfo->tm_min/2));

    // Fin du code de dessin

    SDL_Event e;
    while(SDL_PollEvent(&e)) {

      switch(e.type) {

        case SDL_QUIT:
            loop = 0;
            break;

        /* Touche clavier */
        case SDL_KEYDOWN:
          if (e.key.keysym.sym == SDLK_q) {
            loop = 0;
            printf("Quit\n");
          }
          break;

        case SDL_VIDEORESIZE:
            WINDOW_WIDTH = e.resize.w;
            WINDOW_HEIGHT = e.resize.h;
            resizeViewport();

        default:
            break;
      }
    }

    SDL_GL_SwapBuffers();
    Uint32 elapsedTime = SDL_GetTicks() - startTime;
    if(elapsedTime < FRAMERATE_MILLISECONDS) {
        SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }    

  // Liberation des ressources associées à la SDL
  SDL_Quit();

  return EXIT_SUCCESS;
}

void drawLandmark() {  
  glColor3ub(255, 0, 0);
  glBegin(GL_LINES);
  glVertex2f(0, 0);
  glVertex2f(1, 0);
  
  glColor3ub(0, 255, 0);
  glVertex2f(0, 0);
  glVertex2f(0, 1);
  glEnd();

}
void drawSquare(int full) {
  if ( full == 1 )
    glBegin(GL_QUADS);
  else
    glBegin(GL_LINE_LOOP);
  glVertex2f(-0.5, -0.5);
  glVertex2f(-0.5, 0.5);
  glVertex2f(0.5, 0.5);
  glVertex2f(0.5, -0.5);
  glEnd();
}
void drawCircle(int full) {
  int i;
  float x, y;  

  if ( full == 1 )
    glBegin(GL_POLYGON);
  else
    glBegin(GL_LINE_LOOP);
  for ( i=0; i<SEG_NUMBER; i++) {
    x = cos(SEG_SPACE * i * 2)/2;
    y = sin(SEG_SPACE * i * 2)/2;
    glVertex2f(x , y);
  }
  glEnd();
}
void resizeViewport() {
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1., 1., -1., 1.);
    SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}

void drawClock() {
  int i;
  int angle = 0;
  float SCALE = 0.005;
  int SCALE_X = 8;
  // Cercles
  glPushMatrix();
    // Cercle exterieur 1
    glColor3ub(0,0,0);
    glScalef(2,2,1);
    drawCircle(1);
  
    // Cercle blanc interieur
    glColor3ub(255,255,255);
    glScalef(0.97,0.97,1);
    drawCircle(1);
  
    // Cercle Noir Exterieur
    glColor3ub(0,0,0);
    glScalef(0.98,0.98,1);
    drawCircle(0);
  glPopMatrix();
  
  for (i=0; i<60; i++) {    
    glPushMatrix();
      glColor3ub(0,0,0);
      glRotatef(angle, 0, 0, 1);
      // Deplacement
      glTranslatef(0.8, 0, 0);
    
      // Ellongation
      glScalef(SCALE_X, 1, 1);
      // Mise a l'echelle
      glScalef(SCALE, SCALE, 1);
    
      // Grosse delimitation
      if ( i%5 == 0 ) {
        glScalef(2, 2, 1);
      }    
      drawSquare(1);
    glPopMatrix();
    
    angle += 6;
  }
}
void drawSmallNeedle( int angle ) {
  float SCALE_X = 0.01;
  float SCALE_Y = 1;
  
  glPushMatrix();
    glRotatef(-angle, 0, 0, 1);
    glTranslatef(0, SCALE_Y * 0.4, 0);    
    glScalef(SCALE_X, SCALE_Y, 1);
    drawSquare(1);
  glPopMatrix();
  
}
void drawMiddleNeedle( int angle ) {
  float SCALE_X = 0.02;
  float SCALE_Y = 0.85;
  
  glPushMatrix();
    glRotatef(-angle, 0, 0, 1);
    glTranslatef(0, SCALE_Y * 0.4, 0);    
    glScalef(SCALE_X, SCALE_Y, 1);
    drawSquare(1);
  glPopMatrix();
  
}
void drawLargeNeedle( int angle ) {
  float SCALE_X = 0.03;
  float SCALE_Y = 0.7;
  
  glPushMatrix();
    glRotatef(-angle, 0, 0, 1);
    glTranslatef(0, SCALE_Y * 0.4, 0);    
    glScalef(SCALE_X, SCALE_Y, 1);
    drawSquare(1);
  glPopMatrix();
}

