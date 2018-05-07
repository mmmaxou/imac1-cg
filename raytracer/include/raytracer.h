#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "shape.h"
#include "geometry.h"
#include "colors.h"
#include "test.h"

typedef struct Ray {
	Point3D origin;
	Vector3D direction;
} Ray;

typedef struct Intersection {
	Point3D position;
	Color3f color;
} Intersection;

typedef struct Scene {
	Sphere spheres[20];
} Scene;

Ray createRay(Point3D origin, Vector3D direction);
/* 
	Teste si le rayon intersecte la sphere
	Rempli les champs de l'intersection si oui et renvoi 1
	Sinon, renvoi 0
*/
int intersectsSphere(Ray r, Sphere s, Intersection *i);

#endif