#ifndef OPENGL_TP1_LIST
#define OPENGL_TP1_LIST

#include <GL/gl.h>

/* Listes de points : */


typedef struct Point{
  int x, y; /* Position 2D du point */
  int r, g, b; /* Couleur du point */
  struct Point* next; /* Point suivant à dessiner */
} Point, *PointList;

Point* allocPoint(int x, int y, unsigned char r, unsigned char g,
                  unsigned char b);
void afficherPoint(Point* pt);
void afficherListe(PointList l);
void addPoint(Point* point, PointList* list);
void drawPoints(PointList list);
void deletePoints(PointList list);

/* Listes de primitives : */

typedef struct Primitive {
  GLenum primitiveType; // Type de primive ie. GL_POINTS, GL_LINES, ect.
  PointList points; // Points a dessiner
  struct Primitive* next;
} Primitive, *PrimitiveList;

Primitive* allocPrimitive(GLenum primitiveType);
void addPrimitive(Primitive* primitive, PrimitiveList* list);
void deletePrimitives(PrimitiveList list);
void drawPrimitives(PrimitiveList list);
void affichePrimitives( PrimitiveList list );

#endif