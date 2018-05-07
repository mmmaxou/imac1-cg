#ifndef COLORS_H
#define COLORS_H

typedef struct Color3f {
	float r,g,b;
} Color3f;

Color3f color(float r, float g, float b);
 
/* Fonction qui calcule la somme de deux couleurs */
Color3f addColors(Color3f c1, Color3f c2);

/* L’équivalent pour la soustraction et la multiplication. */
Color3f subColors(Color3f c1, Color3f c2);
Color3f multColors(Color3f c1, Color3f c2);

/* Fonctions de multiplication et division d’une couleur par un scalaire */
Color3f multColor(Color3f c, float a);
Color3f divColor(Color3f c, float a);

#endif