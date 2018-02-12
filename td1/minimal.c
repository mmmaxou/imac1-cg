#include <SDL/SDL.h>

#include <w32api/GL/gl.h>
#include <w32api/GL/glu.h>

#include <stdlib.h>
#include <stdio.h>

typedef struct Point{
  int x, y; /* Position 2D du point */
  unsigned char r, g, b; /* Couleur du point */
  struct Point* next; /* Point suivant à dessiner */
} Point, *PointList;


/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = 400;
static unsigned int WINDOW_HEIGHT = 400;
void resizeWindow();
void reset(int *x1, int *x2, int *x3, int *y1, int *y2, int *y3);
Point* allocPoint(int x, int y, unsigned char r, unsigned char g,
                  unsigned char b);
void addPointToList(Point* point, PointList list);
void afficherPoint(Point* pt);
void afficherListe(PointList l);

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

int main(int argc, char** argv) {

  /* float red, green, blue; */
  int x1, x2, x3, y1, y2, y3;
  reset(&x1, &x2, &x3, &y1, &y2, &y3);
  PointList lignes = NULL;
  Point *current;
  
  int primitive = GL_POINTS;
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

  while(loop) {

    /* Récupération du temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();

    /* Placer ici le code de dessin */
    if ( x1 != 0 && y1 != 0 ) {
      glBegin(primitive);
      glVertex2f(-1 + 2. * x1 / WINDOW_WIDTH,
                 -(-1 + 2. * y1 / WINDOW_HEIGHT));
      if ( primitive == GL_POINTS ) {
        reset(&x1, &x2, &x3, &y1, &y2, &y3);
      }
      if ( x2 != -1 && y2 != -1 ) {
        glVertex2f(-1 + 2. * x2 / WINDOW_WIDTH,
                   -(-1 + 2. * y2 / WINDOW_HEIGHT));
        if ( primitive == GL_LINES ) {
          reset(&x1, &x2, &x3, &y1, &y2, &y3);
        }
        if ( x3 != -1 && y3 != -1 ) {
          glVertex2f(-1 + 2. * x3 / WINDOW_WIDTH,
                     -(-1 + 2. * y3 / WINDOW_HEIGHT));
          if ( primitive == GL_TRIANGLES ) {
            reset(&x1, &x2, &x3, &y1, &y2, &y3);
          }
        }
      }
      glEnd();
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

      /* La touche Q est 97 */
      if(e.type == SDL_KEYDOWN && (e.key.keysym.sym == 97 || e.key.keysym.sym == 113)) {
        printf("Quit\n");
        loop = 0;
        break;
      }
      if(e.type == SDL_KEYDOWN && e.key.keysym.sym == 'p') {
        printf("Points\n");
        primitive = GL_POINTS;
        reset(&x1, &x2, &x3, &y1, &y2, &y3);
      }
      if(e.type == SDL_KEYDOWN && e.key.keysym.sym == 'l') {
        printf("Lignes\n");
        primitive = GL_LINES;
        reset(&x1, &x2, &x3, &y1, &y2, &y3);
      }			
      if(e.type == SDL_KEYDOWN && e.key.keysym.sym == 't') {
        printf("Triangles\n");
        primitive = GL_TRIANGLES;
        reset(&x1, &x2, &x3, &y1, &y2, &y3);
      }

      /* Quand on clique, la couleur change */
      /*
						if(e.type == SDL_MOUSEBUTTONUP) {
							red = e.button.x;
							green = e.button.y;
							red = red / WINDOW_WIDTH;
							green = green / WINDOW_HEIGHT;
							blue = 0;
							glClearColor( red, green, blue, 1);
						}
						*/

      /* Quand on bouge, la couleur change */
      /*
						if(e.type == SDL_MOUSEMOTION) {
							red = e.button.x;
							green = e.button.y;
							red = red / WINDOW_WIDTH;
							green = green / WINDOW_HEIGHT;
							blue = 0;
							glClearColor( red, green, blue, 1);
						}
            */

      /* Quand on redimensionne, on redimensionne */
      if(e.type == SDL_VIDEORESIZE) {
        WINDOW_WIDTH = e.resize.w;
        WINDOW_HEIGHT = e.resize.h;
        resizeWindow();
      }

      if (e.type == SDL_MOUSEBUTTONDOWN) {

        /* On ajoute un point */
        current = allocPoint(e.button.x+10, e.button.y+10, 'R', 'G', 'B');
        addPointToList( current, lignes );
        afficherListe( lignes );

        if ( x1 == -1 && y1 == -1 ) {
          x1 = e.button.x;
          y1 = e.button.y;
        } else if ( x2 == -1 && y2 == -1 ) {
          x2 = e.button.x;
          y2 = e.button.y;
        } else if ( x3 == -1 && y3 == -1 ) {
          x3 = e.button.x;
          y3 = e.button.y;
        } else {
          reset(&x1, &x2, &x3, &y1, &y2, &y3);
        }
      }

      /* Quelques exemples de traitement d'evenements : */
      switch(e.type) {

          /* Clic souris */
        case SDL_MOUSEBUTTONUP:
          printf("clic en (%d, %d)\n", e.button.x, e.button.y);
          break;

          /* Touche clavier */
        case SDL_KEYDOWN:
          printf("touche pressée (code = %d, char = '%c')\n", e.key.keysym.sym, e.key.keysym.sym);
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

void reset(int *x1, int *x2, int *x3, int *y1, int *y2, int *y3) {
  *x1 = -1;
  *x2 = -1;
  *x3 = -1;
  *y1 = -1;
  *y2 = -1;
  *y3 = -1;
}

Point* allocPoint(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
  Point *tmp = (Point*) malloc( sizeof( Point ) );
  if ( tmp ) {
    tmp->x = x;
    tmp->y = y;
    tmp->r = r;
    tmp->g = g;
    tmp->b = b;
    tmp->next = NULL;
    return tmp;
  } else {
    fprintf(stderr, "Allocation mémoire du Point échouée. Fin du programme.\n");
    exit(1);
  }
}

void afficherPoint( Point * pt ) {
  printf("Point || x:%d y:%d r:%c g:%c b:%c\n", pt->x, pt->y, pt->r, pt->g, pt->b);
}

void addPointToList(Point* point, PointList list) {
  Point *last;

  if ( list == NULL )  {
    list = point;
    return;
  } else {
    last = list;
    while ( last->next != NULL ) {
      last = last->next;        
    }
    last->next = point;
    return;
  }
}

void afficherListe(PointList l) {
  if ( l != NULL ) {
    printf("%d:%d -> ", l->x, l->y);
    afficherListe( l->next );
  } else {
    printf("NULL\n");
    return;
  } 
}