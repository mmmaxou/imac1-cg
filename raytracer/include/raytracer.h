#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "shape.h"
#include "geometry.h"
#include "colors.h"
#include "test.h"

#define SPHERE_SIZE 20

typedef struct Ray {
	Point3D origin;
	Vector3D direction;
} Ray;

typedef struct Intersection {
	Point3D position;
	Color3f color;
} Intersection;

typedef struct Scene {
	Sphere spheres[SPHERE_SIZE];
	int tailleSphere;
} Scene;

Ray createRay(Point3D origin, Vector3D direction);
/* 
	Teste si le rayon intersecte la sphere
	Rempli les champs de l'intersection si oui et renvoi 1
	Sinon, renvoi 0
*/
int intersectsSphere(Ray r, Sphere s, Intersection *i);

/* 
	Créer et initialiser les différents champs de la structure
*/
Scene createScene();

/*
	Ajoute une sphere a la scene
*/
void addSphereToScene(Scene *scene, Sphere sphere);

/*
	Boucle sur tous les objets de la scene afin de trouver l'intersection la plus proche avec le rayon passé en parametre
	Renvoi 1 si il y a une intersection
	0 sinon
*/
int throwRayOnScene(Ray ray, const Scene *scene, Intersection *intersection);

#endif