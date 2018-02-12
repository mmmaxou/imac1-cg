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

#include "list.h"


/* Dimensions de la fenêtre */
static unsigned int WINDOW_WIDTH = 400;
static unsigned int WINDOW_HEIGHT = 400;
void resizeWindow();
void drawColorSelectionView();  

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;
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
static const unsigned int NB_COLORS = sizeof(COLORS) / (3 * sizeof(unsigned char));

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
  
  
  /* Primitives a dessiner */
  PrimitiveList primitives = NULL;
  Point *current = NULL;
  addPrimitive(allocPrimitive(GL_POINTS), &primitives);

  /* On veut dessiner en tres tres bleu */
  glColor3ub(0, 0, 255);

  /* Boucle d'affichage */
  int loop = 1;
  int mode = 0;
  unsigned int currentColor = 1;

  while(loop) {

    /* Récupération du temps au début de la boucle */
    Uint32 startTime = SDL_GetTicks();

    /* Placer ici le code de dessin */
    if ( mode == 1 ) {
      /* Mode selection des couleurs */
      drawColorSelectionView();   
    } else {
      glClear(GL_COLOR_BUFFER_BIT);
      glColor3ub(0, 0, 255);
      drawPrimitives( primitives );
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
          if ( mode == 1 ) {
            /* Selection de couleur */
            currentColor = e.button.x * NB_COLORS / WINDOW_WIDTH;
            printf("Current color: %d\n", currentColor);
          } else {
            /* Dessin */
            current = allocPoint( (int) e.button.x , (int) e.button.y, COLORS[currentColor * 3], COLORS[currentColor * 3 + 1], COLORS[currentColor * 3 + 2]);
            addPoint(current, &primitives->points);
          }
          /* affichePrimitives( primitives ); */ 
          break;

          /* Touche clavier */
        case SDL_KEYDOWN:
          printf("touche pressée (code = %d, char = '%c')\n", e.key.keysym.sym, e.key.keysym.sym);
          if(e.key.keysym.sym == SDLK_SPACE) {
            mode = 1;
          } else if (e.key.keysym.sym == SDLK_q) {
            loop = 0;
            printf("Quit\n");
            break;
          }
          break;
          
        case SDL_KEYUP:
          if(e.key.keysym.sym == SDLK_SPACE) {
            mode = 0;
          } else {
            switch(e.key.keysym.sym) {
              case SDLK_p:
                addPrimitive(allocPrimitive(GL_POINTS), &primitives);      
        printf("Points\n");
                break;
              case SDLK_l:
                addPrimitive(allocPrimitive(GL_LINES), &primitives);
        printf("Lignes\n");
                break;
              case SDLK_t:
                addPrimitive(allocPrimitive(GL_TRIANGLES), &primitives);
        printf("Triangles\n");
                break;
              default:
                break;
            }            
          }
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
  deletePrimitives(primitives);

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
void drawColorSelectionView() {
  int i;
  GLfloat dx = 2.f / NB_COLORS;
  glBegin(GL_QUADS);
    for(i = 0; i < NB_COLORS; ++i) {
      glColor3ubv(COLORS + i * 3);      
      glVertex2f(-1 + i * dx, -1);
      glVertex2f(-1 + (i + 1) * dx, -1);
      glVertex2f(-1 + (i + 1) * dx, 1);
      glVertex2f(-1 + i * dx, 1);
    }
  glEnd();
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
  printf("Point || x:%d y:%d r:%d g:%d b:%d\n", pt->x, pt->y, pt->r, pt->g, pt->b);
}
void drawPoints(PointList list) { 
  if ( list != NULL ) {
    glVertex2f(-1 + 2. * list->x / WINDOW_WIDTH,
                 -(-1 + 2. * list->y / WINDOW_HEIGHT));
    drawPoints( list->next );
  } 
}
void addPoint(Point* point, PointList* list) {
  assert(point);
  assert(list);
  if(*list == NULL) {
    *list = point;
  } else {
    addPoint(point, &(*list)->next);
  }
}
void deletePoints(PointList list) {
  if ( list != NULL ) {
    deletePoints( list->next );      
    free(list);
  }  
}
Primitive* allocPrimitive(GLenum primitiveType) {
  Primitive *tmp = (Primitive*) malloc( sizeof( Primitive ));
   if ( tmp ) {
     tmp->primitiveType = primitiveType;
     tmp->points = NULL;
     tmp->next = NULL;
    return tmp;
  } else {
    fprintf(stderr, "Allocation mémoire de la Primitive échouée. Fin du programme.\n");
    exit(1);
  }
}
void addPrimitive(Primitive* primitive, PrimitiveList* list) {
  assert(primitive);
  assert(list);
  /* On ajoute au début */
  primitive->next = *list;
  *list = primitive;  
}
void deletePrimitives(PrimitiveList list) {
  assert(list);
  if ( list != NULL ) {
    deletePoints( list->points );
    deletePrimitives( list->next );
    free(list);
  }  
}
void drawPrimitives(PrimitiveList list) {
  while(list) {
    glBegin(list->primitiveType);
    drawPoints(list->points);
    glEnd();
    list = list->next;
  }  
}
void affichePrimitives(PrimitiveList list) {
  PointList current;
  assert( list );
  while ( list ) {
    current = list->points;
    assert( current );
    printf("Primitive\n");
    while ( current ) {
      afficherPoint( current );
      current = current->next;
    }
    list = list->next;        
  }
}