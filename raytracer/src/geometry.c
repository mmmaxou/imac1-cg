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
Point3D pointPlusVector(Point3D P, Vector3D V) {
	float x, y, z;
	x = P.x + V.x;
	y = P.y + V.y;
	z = P.z + V.z;
	return pointXYZ(x, y, z);
}

/* Addition de vecteurs */
Vector3D addVectors(Vector3D A, Vector3D B) {
	float x, y, z;
	x = A.x + B.x;
	y = A.y + B.y;
	z = A.z + B.z;
	return vectorXYZ(x, y, z);
}

/* Soustraction de vecteurs */
Vector3D subVectors(Vector3D A, Vector3D B) {
	float x, y, z;
	x = A.x - B.x;
	y = A.y - B.y;
	z = A.z - B.z;
	return vectorXYZ(x, y, z);
}

/* Multiplication de vecteurs */
Vector3D multVectors(Vector3D V, float a) {
	float x, y, z;
	x = V.x * a;
	y = V.y * a;
	z = V.z * a;
	return vectorXYZ(x, y, z);
}

/* Multiplication de vecteurs */
Vector3D divVectors(Vector3D V, float a) {
	float x, y, z;
	x = V.x / a;
	y = V.y / a;
	z = V.z / a;
	return vectorXYZ(x, y, z);
}

/* Produit scalaire de deux vecteurs */
float dot(Vector3D A, Vector3D B) {
	return A.x*B.x + A.y*B.y + A.z*B.z;
}

/* Norme d'un vecteur */
float norm(Vector3D V) {	
	return V.x*V.x + V.y*V.y + V.z*V.z;
}

/* Retourne le vecteur normalisé passé en parametre */
Vector3D normalize(Vector3D V) {
	float n = norm(V);
	V.x /= n;
	V.y /= n;
	V.z /= n;
	return V;
}