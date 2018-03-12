#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define SEG_NUMBER 50
#define SEG_SPACE PI/SEG_NUMBER
#define PI 3.141592

#define ORBITAL_BODIES 20
#define ORBITAL_SPEED_DIVIDER 30
#define WINDOW_SCALE 60
#define ORBITAL_BODIES_SCALE 20

typedef struct planet {
  char name[100];
  float size; // Given in AU
  float sun_dist; // Given in AU
  float rot_speed; // Given in km/s
  float angle;
  int r, g, b;
} *Planet;

static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 800;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void drawLandmark();
void drawSquare(int full);
void drawCircle(int full);
void resizeViewport();
Planet createPlanet(char name[100], float size, float sun_dist, float rot_speed, int r, int g, int b);
void drawPlanet(Planet p);

int main(int argc, char** argv) {
  int i;
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
  SDL_WM_SetCaption("S O L A R I S", NULL);
  resizeViewport();
  
  
  /* Creation des donnees */
  Planet systemeSolaire[ORBITAL_BODIES];
  for (i=0; i<ORBITAL_BODIES; i++) {
    systemeSolaire[i] = NULL;
  }
  systemeSolaire[0] = createPlanet("sun", 0.0047, 0, 0, 255, 204, 0);
  systemeSolaire[1] = createPlanet("mercury", 0.00001626, 0.466, 47, 51, 51, 51);
  systemeSolaire[2] = createPlanet("venus", 0.00004034, 0.728, 35, 155, 155, 155);
  systemeSolaire[3] = createPlanet("earth", 0.00004247, 1, 30, 51, 153, 255);
  systemeSolaire[4] = createPlanet("mars", 0.000022593, 1.666, 24, 255, 153, 51);
  systemeSolaire[5] = createPlanet("jupiter", 0.000466667, 5.458, 13, 255, 204, 102);
  systemeSolaire[6] = createPlanet("saturn", 0.0004, 10.123, 9, 255, 51, 204);
  systemeSolaire[7] = createPlanet("uranus", 0.000166, 20.11, 6.8, 102, 204, 255);
  systemeSolaire[8] = createPlanet("neptune", 0.00016, 30.33, 5.43, 102, 204, 255);

  int loop = 1;
  glClearColor(0.1, 0.1, 0.1 ,1.0); 
  
  while(loop) {

    Uint32 startTime = SDL_GetTicks();

    // TODO: Code de dessin
    glClear(GL_COLOR_BUFFER_BIT);
    
    for (i=0; i<ORBITAL_BODIES; i++) {
      if ( systemeSolaire[i] ) drawPlanet(systemeSolaire[i]);
    }
    
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
          
        case SDL_MOUSEWHEEL:
          printf("Wheel: %d", e.wheel.y);

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

Planet createPlanet(char name[100], float size, float sun_dist, float rot_speed, int r, int g, int b) {
  Planet tmp = malloc( sizeof ( *tmp ));
  if ( !tmp ) {
    printf("Erreur allocation memoire\n");
    exit(0);
  }
  strcpy(tmp->name, name);
  tmp->size = size;
  tmp->sun_dist = sun_dist;
  tmp->rot_speed = rot_speed;
  tmp->angle = 0;
  tmp->r = r;
  tmp->g = g;
  tmp->b = b;
  return tmp;
}
void drawPlanet(Planet p) {
  if (!p) return;
  glPushMatrix();
    glColor3ub(p->r, p->g, p->b);
    glRotatef(p->angle, 0, 0, 1);
    glTranslatef(0, p->sun_dist, 0);
    glScalef(p->size, p->size, 1);      
    glScalef(WINDOW_SCALE * ORBITAL_BODIES_SCALE, WINDOW_SCALE * ORBITAL_BODIES_SCALE, 1);      
    drawCircle(1);
  glPopMatrix();
  
  if ( p->rot_speed != 0 ) {
    p->angle += p->rot_speed / ORBITAL_SPEED_DIVIDER;
  }
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
  gluOrtho2D(-WINDOW_SCALE/2, WINDOW_SCALE/2, -WINDOW_SCALE/2, WINDOW_SCALE/2);
  SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}