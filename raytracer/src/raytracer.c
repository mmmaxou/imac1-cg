#include "raytracer.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Construit un rayon */
Ray createRay(Point3D origin, Vector3D direction) {
	Ray tmp;
	tmp.origin = origin;
	tmp.direction = direction;
	return tmp;
}

/* 
	Teste si le rayon intersecte la sphere
	Rempli les champs de l'intersection si oui et renvoi 1
	Sinon, renvoi 0
*/
int intersectsSphere(Ray r, Sphere s, Intersection *i) {
	float a, b, c;
	
	/* calcul de a, b, c dans l'equation at² + bt + c */
	/* On considere que d est normalisé */
	a = 1;
	
	/* b = OP.(-A + d) */
	Point3D M;
	Point3D O = pointXYZ(0,0,0);
	Vector3D OP = vector(r.origin, O);
	Vector3D OA = vector(s.center, O);
	Vector3D minusAD = vector(r.direction, s.center);
	b = dot(OP, minusAD);
	
	c = norm(OP) + norm(OA) - 2*dot(OP, OA) - (s.rayon*s.rayon);
	
	float delta = b*b - 4*a*c;
	/*
	printf("a:%f, b:%f, c:%f\n", a, b, c);
	printf("delta:%f\n", delta);
	*/
	if ( delta > 0) {
		float t1 = (-b + sqrt(delta))/2*a;
		float t2 = (-b - sqrt(delta))/2*a;
		/*
		printf("t1:%f , t2:%f\n",t1,t2);
		*/
		if ( t1<0 && t2>=0 ) {
			/* Une solution : t2 */
			M = pointPlusVector(OP, multVectors(r.direction, t2));
			
		} else if ( t1>=0 && t2<0 ) {
			/* Une solution : t1 */
			M = pointPlusVector(OP, multVectors(r.direction, t1));
			
		} else if ( t1>=0 && t2>=0 && t1<t2 ){
			/* Une solution : t1 */
			M = pointPlusVector(OP, multVectors(r.direction, t1));
			
		} else if ( t1>=0 && t2>=0 ){
			/* Une solution : t2 */
			M = pointPlusVector(OP, multVectors(r.direction, t2));
			
		} else {
			/* t1 et t2 negatifs */
			return 0;
		}
		
		return 1;
	} else if ( delta == 0 ) {
		float t = -b/2*a;
		/*
		printf("t:%f\n",t);
		*/
		if ( t>=0 ) {
			M = pointPlusVector(OP, multVectors(r.direction, t));
		} else {
			return 0;
		}
	} else {
		return 0;
	}
	/*
	displayVector(M);
	*/
	i->position = M;
	i->color = s.color;	
	return 1;
}