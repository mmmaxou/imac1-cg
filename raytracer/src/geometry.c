#include "geometry.h"

#include <stdlib.h>
#include <stdio.h>

/* Construit le point x y z */
Point3D pointXYZ(float x, float y, float z) {
	Point3D tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return tmp;
}

/* Construit le vecteur x y z */
Vector3D vectorXYZ(float x, float y, float z) {
	Vector3D tmp;
	tmp.x = x;
	tmp.y = y;
	tmp.z = z;
	return tmp;
}

/* Construit le vecteur AB = B-A */
Vector3D vector(Point3D A, Point3D B) {
	float x, y, z;
	x = A.x - B.x;
	y = A.y - B.y;
	z = A.z - B.z;
	return vectorXYZ(x, y, z);
}

/* Construit le point P + V */
Point3D pointPlusVector(Point3D P, Vector3D V);

/* Addition de vecteurs */
Vector3D addVectors(Vector3D A, Vector3D B) {
	float x, y, z;
	x = A.x + B.x;
	y = A.y + B.y;
	z = A.z + B.z;
	return vectorXYZ(x, y, z);
}

/* Soustraction de vecteurs */
Vector3D subVectors(Vector3D A, Vector3D B);

/* Multiplication de vecteurs */
Vector3D multVectors(Vector3D V, float a);

/* Multiplication de vecteurs */
Vector3D divVectors(Vector3D V, float a);

/* Produit scalaire de deux vecteurs */
float dot(Vector3D A, Vector3D B);

/* Norme d'un vecteur */
float norm(Vector3D V);

/* Retourne le vecteur normalisé passé en parametre */
Vector3D normalize(Vector3D V);