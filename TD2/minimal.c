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
#define SCALE_X 8
#define SCALE_Y 6


/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = 100 * SCALE_X;
static unsigned int WINDOW_HEIGHT = 100 * SCALE_Y;
void resizeWindow();
void normalized_glVertex2f(int x, int y);
void drawSquare(int full);
void drawLandmark();
void drawCircle(int full);

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
  glMatrixMode(GL_MODELVIEW);

  /* On veut dessiner en tres tres bleu */
  glColor3ub(0, 0, 255);

  /* Boucle d'affichage */
  int loop = 1;
  float center_x = 0;
  float center_y = 0;
  int rotating = 0;
  int rotate_start_x = 0;
  int rotate_start_y = 0;
  int rotate_angle = 0;
  float rand_x = 0;
  float rand_y = 0;
  
  srand(time(NULL));

  while(loop) {

    /* Récupération du temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();
    glClear(GL_COLOR_BUFFER_BIT);

    /* Placer ici le code de dessin */
    drawLandmark();
    float delta_x = (float) rand() /(float) RAND_MAX;
    float delta_y = (float) rand() /(float) RAND_MAX;
    delta_x -= 0.5;
    delta_y -= 0.5;
    rand_x += delta_x / 5;
    rand_y += delta_y / 5;
    
    if ( rand_x >= SCALE_X/2 ) rand_x = SCALE_X/2;
    if ( rand_y >= SCALE_Y/2 ) rand_y = SCALE_Y/2;
    if ( rand_x <= -SCALE_X/2 ) rand_x = -SCALE_X/2;
    if ( rand_y <= -SCALE_Y/2 ) rand_y = -SCALE_Y/2;
    
    /* 
      Changement de la matrice
      Cercle centré en (1, 2)
    */
    glColor3ub(255, 120, 0);
    glTranslatef(1, 2, 0);
    drawCircle( 1 );
    glTranslatef(-1, -2, 0);
    
    /*
      Carré
      Rotation de 45 degres
      Translation de 2 axe des X
    */
    int alpha = 45;
    glColor3ub(255, 0, 0);
    glRotatef(alpha, 0.0, 0.0, 1.0);
    glTranslatef(2, 0, 0);
    drawSquare( 1 );    
    glTranslatef(-2, 0, 0);
    glRotatef(-alpha, 0.0, 0.0, 1.0);   
    
    /*
      Carré
      Rotation de 45 degres
      Translation de 2 axe des X
    */
    glColor3ub(255, 0, 255);
    glTranslatef(2, 0, 0);
    glRotatef(alpha, 0.0, 0.0, 1.0);
    drawSquare( 1 );    
    glRotatef(-alpha, 0.0, 0.0, 1.0);    
    glTranslatef(-2, 0, 0);
    
    /*
      Carré jaune centré en la pos de la souris
    */
    glColor3ub(255, 255, 0);
    glTranslatef(center_x, center_y, 0);
    glRotatef(rotate_angle, 0.0, 0.0, 1.0);
    drawSquare( 1 );  
    glRotatef(-rotate_angle, 0.0, 0.0, 1.0); 
    glTranslatef(-center_x, -center_y, 0);
    
    /*
      Cercle bleu aleatoire
    */
    glColor3ub(0, 0, 255);
    glTranslatef(rand_x, rand_y, 0);
    drawCircle( 1 );
    glTranslatef(-rand_x, -rand_y, 0);
    
    

    

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
          if ( e.button.button == SDL_BUTTON_RIGHT ) {
            rotating = 0;
          }
          break;

        case SDL_MOUSEBUTTONDOWN:
          if ( e.button.button == SDL_BUTTON_LEFT ) {
            /* printf("clic en (%d, %d)\n", e.button.x, e.button.y); */
            center_x = -(SCALE_X/2) + (float) SCALE_X * e.button.x/WINDOW_WIDTH;
            center_y = -(-(SCALE_Y/2) + (float) SCALE_Y * e.button.y/WINDOW_HEIGHT);
          } else {
            rotating = 1;
            rotate_start_x = e.button.x;
            rotate_start_y = e.button.y;
          }
          break;
          
        case SDL_MOUSEMOTION:
          if ( rotating == 1 ) {
            rotate_angle = ( rotate_start_x - e.button.x ) + ( rotate_start_y - e.button.y );
          }
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
  gluOrtho2D((float) -SCALE_X/2, (float) SCALE_X/2, (float) -SCALE_Y/2, (float) SCALE_Y/2);

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