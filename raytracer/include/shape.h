#ifndef SHAPE_H
#define SHAPE_H

#include "geometry.h"
#include "colors.h"

typedef struct cube {
	Point3D min;
	Point3D max;
	Color3f color;
} Cube;

typedef struct sphere {
	Point3D center;
	int rayon;
	Color3f color;
} Sphere;

Cube createCube(Point3D min, Point3D max, Color3f color);
Sphere createSphere(Point3D center, int rayon, Color3f color);

#endif