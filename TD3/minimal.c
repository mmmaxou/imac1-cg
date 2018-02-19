#include <SDL/SDL.h>
/*
#include <w32api/GL/gl.h>
#include <w32api/GL/glu.h>
*/
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <time.h>

#define SEG_NUMBER 50
#define PI 3.141592
#define SEG_SPACE PI/SEG_NUMBER
#define NB_FIG 5


/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 600;
void resizeWindow();
void normalized_glVertex2f(int x, int y);
void drawSquare(int full);
void drawLandmark();
void drawCircle(int full);
void drawRoundedSquare(float sphereRadius, int full);
void drawFirstArm(int full);
void drawSecondArm(int full);

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

int main(int argc, char** argv) {

  /* Initialisation de la SDL */
  if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    return EXIT_FAILURE;
  }

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);

  /* Ouverture d'une fenêtre et création d'un contexte OpenGL */
  if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    return EXIT_FAILURE;
  }

  /* Titre de la fenêtre */
  SDL_WM_SetCaption("J'aime les pates au beurre", NULL);
  resizeWindow();
  glClearColor(0.1, 0.5, 0.8, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  /* On veut dessiner en tres tres bleu */
  glColor3ub(0, 0, 255);

  /* Boucle d'affichage */
  int loop = 1;
  
  srand(time(NULL));

  while(loop) {

    /* Récupération du temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();
    glClear(GL_COLOR_BUFFER_BIT);

    /* Placer ici le code de dessin */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glColor3ub(255, 0, 0);
    
    glPushMatrix();
      glTranslatef(-3, 2, 0);
      drawRoundedSquare( 0.2, 0 );
    glPopMatrix();
    
    glPushMatrix();
      glTranslatef(-1, 2, 0);
      glScalef(0.5, 0.5, 1);
      drawFirstArm( 0 );
    glPopMatrix();
    
    
       

    /* Echange du front et du back buffer : mise à jour de la fenêtre */
    SDL_GL_SwapBuffers();

    /* Boucle traitant les evenements */
    SDL_Event e;
    while(SDL_PollEvent(&e)) {

      /* L'utilisateur ferme la fenêtre : */
      if(e.type == SDL_QUIT) {
        loop = 0;
        break;
      }


      /* Quelques exemples de traitement d'evenements : */
      switch(e.type) {

          /* Clic souris */
        case SDL_MOUSEBUTTONUP:
          break;

        case SDL_MOUSEBUTTONDOWN:
          
          break;
          
        case SDL_MOUSEMOTION:
          break;

          /* Touche clavier */
        case SDL_KEYDOWN:
          if (e.key.keysym.sym == SDLK_q) {
            loop = 0;
            printf("Quit\n");
          }
          break;

        case SDL_KEYUP:
          break;

        case SDL_VIDEORESIZE:
          WINDOW_WIDTH = e.resize.w;
          WINDOW_HEIGHT = e.resize.h;
          resizeWindow();
          break;

        default:
          break;
      }
    }

    /* Calcul du temps écoulé */
    Uint32 elapsedTime = SDL_GetTicks() - startTime;

    /* Si trop peu de temps s'est écoulé, on met en pause le programme */
    if(elapsedTime < FRAMERATE_MILLISECONDS) {
      SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    }
  }

  /* Liberation des ressources associées à la SDL */ 
  SDL_Quit();

  return EXIT_SUCCESS;
}

void resizeWindow() {

  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-4, 4, -3, 3);

  SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE);

  glClear(GL_COLOR_BUFFER_BIT);

}
void normalized_glVertex2f(int x, int y) {
  glVertex2f(-1+2.*x/WINDOW_WIDTH,-(-1+2.*y/WINDOW_HEIGHT)); 
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
void drawRoundedSquare(float sphereRadius, int full) {  
  
  glPushMatrix();
    glScalef(1-2*sphereRadius, 1, 1);
    drawSquare(full);
  glPopMatrix();
  glPushMatrix();
    glScalef(1, 1-2*sphereRadius, 1);
    drawSquare(full);
  glPopMatrix();
  
  glPushMatrix();
    
    glPushMatrix();
      glTranslatef(-0.5+sphereRadius, -0.5+sphereRadius, 0);    
      glScalef(sphereRadius*2, sphereRadius*2, 1);
      drawCircle(full);
    glPopMatrix();
    
    glPushMatrix();
      glTranslatef(-0.5+sphereRadius, 0.5-sphereRadius, 0);    
      glScalef(sphereRadius*2, sphereRadius*2, 1);
      drawCircle(full);
    glPopMatrix();
    
    glPushMatrix();
      glTranslatef(0.5-sphereRadius, -0.5+sphereRadius, 0);    
      glScalef(sphereRadius*2, sphereRadius*2, 1);
      drawCircle(full);
    glPopMatrix();
    
    glPushMatrix();
      glTranslatef(0.5-sphereRadius, 0.5-sphereRadius, 0);    
      glScalef(sphereRadius*2, sphereRadius*2, 1);
      drawCircle(full);
    glPopMatrix();
  
  glPopMatrix();  
}
void drawFirstArm(int full) {
  glPushMatrix();
    glScalef(2, 2, 1);
    drawCircle( full );
  glPopMatrix();
  
  glPushMatrix();
    glTranslatef(3, 0, 0);
    drawCircle( full );
  glPopMatrix();
  
  if ( full )
    glBegin(GL_QUADS);
  else 
    glBegin(GL_LINE_LOOP);
  glVertex2f(0, 1);
  glVertex2f(3, 0.5);
  glVertex2f(3, -0.5);
  glVertex2f(0, -1);
  glEnd();
  
}
void drawSecondArm(int full) {
  
}