#include <SDL/SDL.h>

#include <w32api/GL/gl.h>
#include <w32api/GL/glu.h>
/*
#include <GL/gl.h>
#include <GL/glu.h>
*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define SEG_NUMBER 50
#define PI 3.141592
#define SEG_SPACE PI/SEG_NUMBER
#define NB_FIG 5

/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 800;
void resizeWindow();
void normalized_glVertex2f(int x, int y);
void drawSquare(int w, int full);
void drawLandmark(int w);
void drawCircle(int w, int full);

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;
/*
static const unsigned char COLORS[] = {
  0, 0, 0 ,
  255, 0, 0 ,
  0, 255, 0 ,
  0, 0, 255 ,
  255, 255, 0 ,
  255, 0, 255 ,
  0, 255, 255 ,
  255, 255, 255 
};
*/

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
  glClearColor(0.1, 0.5, 0.8, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  /* On veut dessiner en tres tres bleu */
  glColor3ub(0, 0, 255);

  /* Boucle d'affichage */
  int loop = 1;
  int mode = 3;

  while(loop) {

    /* Récupération du temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();
    glClear(GL_COLOR_BUFFER_BIT);

    /* Placer ici le code de dessin */
    glColor3ub(0, 0, 255);
    switch ( mode ) {
      case 0:
        drawSquare( 100, 0 );
        break;
      case 1:
        drawLandmark( 100 );
        break;
      case 2:
        drawSquare( 100, 1 );
        break;
      case 3:
        drawCircle( 100, 0 );
        break;
      case 4:
        drawCircle( 100, 1 );
        break;
      default:
        break;
    }

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
          mode = (mode+1) % NB_FIG;
          break;

        case SDL_MOUSEBUTTONDOWN:
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
  gluOrtho2D(-1., 1., -1., 1.);

  SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE);

  glClear(GL_COLOR_BUFFER_BIT);

}
void normalized_glVertex2f(int x, int y) {
  glVertex2f(-1+2.*x/WINDOW_WIDTH,-(-1+2.*y/WINDOW_HEIGHT)); 
}
void drawSquare(int w, int full) {
  int x = (WINDOW_WIDTH/2) - w/2;
  int y = (WINDOW_HEIGHT/2) - w/2;
  if ( full == 1 )
    glBegin(GL_QUADS);
  else
    glBegin(GL_LINE_LOOP);
  normalized_glVertex2f(x, y);
  normalized_glVertex2f(x, y+w);
  normalized_glVertex2f(x+w, y+w);
  normalized_glVertex2f(x+w, y);
  glEnd();
}
void drawLandmark(int w) {  
  int x = (WINDOW_WIDTH/2);
  int y = (WINDOW_HEIGHT/2);
  glColor3ub(255, 0, 0);
  glBegin(GL_LINES);
  normalized_glVertex2f(x, y);
  normalized_glVertex2f(x, y-w);
  glEnd();
  glColor3ub(0, 255, 0);
  glBegin(GL_LINES);
  normalized_glVertex2f(x, y);
  normalized_glVertex2f(x+w, y);
  glEnd();

}
void drawCircle(int w, int full) {
  int i;
  float x, y;
  int center_x = (WINDOW_WIDTH/2);
  int center_y = (WINDOW_HEIGHT/2);
  
  if ( full == 1 )
    glBegin(GL_POLYGON);
  else
    glBegin(GL_LINE_LOOP);
  for ( i=0; i<SEG_NUMBER; i++) {
    x = cos(SEG_SPACE * i * 2) * w;
    y = sin(SEG_SPACE * i * 2) * w;
    /*
    printf("SegSpace:%f", SEG_SPACE);
    printf("x:%f _ y:%f\n",x,y);
    */
    normalized_glVertex2f(center_x + x , center_y + y);
  }
  glEnd();

}