#ifndef GEOMETRY_H
#define GEOMETRY_H

typedef struct Vec3 {
	float x,y,z;
} Point3D, Vector3D;

/* _____colornction def _____________ */

/* Construit le point x y z */
Point3D pointXYZ(float x, float y, float z);

/* Construit le vecteur x y z */
Vector3D vectorXYZ(float x, float y, float z);

/* Construit le vecteur AB = B-A */
Vector3D vector(Point3D A, Point3D B);

/* Construit le point P + V */
Point3D pointPlusVector(Point3D P, Vector3D V);

/* Addition de vecteurs */
Vector3D addVectors(Vector3D A, Vector3D B);

/* Soustraction de vecteurs */
Vector3D subVectors(Vector3D A, Vector3D B);

/* Multiplication de vecteurs */
Vector3D multVectors(Vector3D V, float a);

/* Division de vecteurs */
Vector3D divVectors(Vector3D V, float a);

/* Produit scalaire de deux vecteurs */
float dot(Vector3D A, Vector3D B);

/* Norme d'un vecteur */
float norm(Vector3D V);

/* Retourne le vecteur normalisé passé en parametre */
Vector3D normalize(Vector3D V);

#endif