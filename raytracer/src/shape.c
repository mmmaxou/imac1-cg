#include "shape.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Construit un cube */
Cube createCube(Point3D min, Point3D max, Color3f color) {
	Cube tmp;
	tmp.min = min;
	tmp.max = max;
	tmp.color = color;
	return tmp;
}

/* Construit une sphere */
Sphere createSphere(Point3D center, int rayon, Color3f color) {
	Sphere tmp;
	tmp.center = center;
	tmp.rayon = rayon;
	tmp.color = color;
	return tmp;
}