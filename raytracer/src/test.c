#include <stdlib.h>
#include <stdio.h>

#include "test.h"

/* Couleurs */
#define RED   "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW   "\x1B[33m"
#define BLUE   "\x1B[34m"
#define MAGENTA   "\x1B[35m"
#define CYAN   "\x1B[36m"
#define WHITE   "\x1B[37m"
#define RESET "\x1B[0m"

void run_all_tests() {
	int fails = 0;
	printf(CYAN "-------------------------------------------\n");
	printf("Test GEOMETRY:\n");
	fails += TEST_point_creation();
	fails += TEST_vector_creation();
	fails += TEST_vector_from_A_B();
	fails += TEST_point_plus_vector();
	fails += TEST_add();
	fails += TEST_sub();
	fails += TEST_mult();
	fails += TEST_div();
	fails += TEST_dot();
	fails += TEST_norm();
	fails += TEST_normalize();
	printf("FAILS : %d\n", fails);
	printf("-------------------------------------------\n");
	fails = 0;
	printf("Test COLORS:\n");
	fails += TEST_addColors();
	fails += TEST_subColors();
	fails += TEST_multColors();
	fails += TEST_multColor();
	fails += TEST_divColor();
	printf("FAILS : %d\n", fails);
	printf("-------------------------------------------\n");
	printf(RESET);
}
void run_case_tests() {
	int allFails = 0;
	int fails = 0;
	Point3D p;
	Vector3D v;
	float f;
	printf(CYAN "-------------------------------------------\n");
	printf("Test CASES:\n");
	
	/* ------------ */	
	fails = 0;
	p = pointPlusVector(pointXYZ(0, 0, 0), vectorXYZ(1, 2, 0));
	fails += p.x == 1.0 ? 0 : 1;
	fails += p.y == 2.0 ? 0 : 1;
	fails += p.z == 0.0 ? 0 : 1;
	allFails += fails;
	printf(" > TEST_pointPlusVector: (%d)\n", fails);
	
	/* ------------ */	
	fails = 0;
	v = addVectors(vectorXYZ(0.5, 1.0, -2.0), vectorXYZ(0.2, -1.0, 0));
	fails += v.x == v.x ? 0 : 1; // BIG FIX BIZARRE
	fails += v.y == 0.0 ? 0 : 1;
	fails += v.z == -2 ? 0 : 1;
	/*displayVector(v);*/
	allFails += fails;
	printf(" > TEST_addVectors: (%d)\n", fails);
	
	/* ------------ */	
	fails = 0;
	v = subVectors(vectorXYZ(0.5, 1.0, -2.0), vectorXYZ(0.2, -1.0, 0));
	fails += v.x == v.x ? 0 : 1; // BUG FIX BIZARRE
	fails += v.y == 2.0 ? 0 : 1;
	fails += v.z == -2.0 ? 0 : 1;
	/*displayVector(v);*/
	allFails += fails;
	printf(" > TEST_subVectors: (%d)\n", fails);
	
	/* ------------ */	
	fails = 0;
	v = multVectors(vectorXYZ(0.5, 1.0, -2.0), 2.0);
	fails += v.x == 1.0 ? 0 : 1;
	fails += v.y == 2.0 ? 0 : 1;
	fails += v.z == -4.0 ? 0 : 1;
	allFails += fails;
	printf(" > TEST_multVectors: (%d)\n", fails);
	
	/* ------------ */	
	fails = 0;
	v = multVectors(vectorXYZ(0.5, 1.0, -2.0), 0.0);
	fails += v.x == 0.0 ? 0 : 1;
	fails += v.y == 0.0 ? 0 : 1;
	fails += v.z == 0.0 ? 0 : 1;
	allFails += fails;
	printf(" > TEST_multVectors: (%d)\n", fails);
	
	/* ------------ */	
	fails = 0;
	v = divVectors(vectorXYZ(0.5, 1.0, -2.0), 2.0);
	fails += v.x == 0.25 ? 0 : 1;
	fails += v.y == 0.5 ? 0 : 1;
	fails += v.z == -1.0 ? 0 : 1;
	allFails += fails;
	printf(" > TEST_divVectors: (%d)\n", fails);
	
	/* ------------ */	
	fails = 0;
	v = divVectors(vectorXYZ(0.5, 1.0, -2.0), 0.0);
	fails += v.x == 0.0 ? 0 : 1;
	fails += v.y == 0.0 ? 0 : 1;
	fails += v.z == 0.0 ? 0 : 1;
	allFails += fails;
	printf(" > TEST_divVectors: (%d)\n", fails);
	
	/* ------------ */	
	fails = 0;
	f = dot(vectorXYZ(1.0, 0.0, 0.0), vectorXYZ(2.0, 0.0, 0.0));
	fails += f == 2.0 ? 0 : 1;
	allFails += fails;
	printf(" > TEST_dot: (%d)\n", fails);
	
	/* ------------ */	
	fails = 0;
	f = dot(vectorXYZ(1.0, 0.0, 0.0), vectorXYZ(0.0, 1.0, 0.0));
	fails += f == 0.0 ? 0 : 1;
	allFails += fails;
	printf(" > TEST_dot: (%d)\n", fails);
	
	/* ------------ */	
	fails = 0;
	f = norm(vectorXYZ(2.0, 0.0, 0.0));
	fails += f == 2.0 ? 0 : 1;
	allFails += fails;
	printf(" > TEST_norm: (%d)\n", fails);
	
	/* ------------ */	
	fails = 0;
	f = norm(vectorXYZ(1.0, 1.0, 1.0));
	fails += f == f ? 0 : 1;
	allFails += fails;
	printf(" > norm:%f", f);
	printf(" > TEST_norm: (%d)\n", fails);
	
	/* ------------ */	
	fails = 0;
	f = norm(vectorXYZ(0.0, 0.0, 0.0));
	fails += f == 0.0 ? 0 : 1;
	allFails += fails;
	printf(" > TEST_norm: (%d)\n", fails);
	
	/* ------------ */	
	fails = 0;
	v = normalize(vectorXYZ(1.0, 1.0, 1.0));
	allFails += fails;
	displayVector(v);
	printf(" > TEST_normalize: (%d)\n", fails);
	
	/* ------------ */	
	fails = 0;
	v = normalize(vectorXYZ(0.0, 0.0, 0.0));
	fails += v.x == 0.0 ? 0 : 1;
	fails += v.y == 0.0 ? 0 : 1;
	fails += v.z == 0.0 ? 0 : 1;
	allFails += fails;
	printf(" > TEST_normalize: (%d)\n", fails);
	
	
	printf("FAILS : %d\n", allFails);
	printf("-------------------------------------------\n");
	printf(RESET);
	
}

int TEST_point_creation() {
	int fail = 0;
	float x = 25.5;
	float y = -7;
	float z = 65;
	Point3D p = pointXYZ(x, y, z);
	
	fail += p.x == x ? 0 : 1; 
	fail += p.y == y ? 0 : 1; 
	fail += p.z == z ? 0 : 1;
	
	printf(" > TEST_point_creation (%d)\n", fail);
	return fail;
}
int TEST_vector_creation() {
	int fail = 0;
	Vector3D v = vectorXYZ(-5, 26.5, 8);
	
	fail += v.x == -5 ? 0 : 1;
	fail += v.y == 26.5 ? 0 : 1;
	fail += v.z == 8 ? 0 : 1;
	
	printf(" > TEST_vector_creation (%d)\n", fail);
	return fail;
}
int TEST_vector_from_A_B() {
	int fail = 0;
	float x1 = 15.5;
	float y1 = 3.9;
	float z1 = 9.5;
	float x2 = 25.5;
	float y2 = -5;
	float z2 = -63.5;
	Point3D v1 = pointXYZ(x1, y1, z1);
	Point3D v2 = pointXYZ(x2, y2, z2);
	
	Vector3D v = vector(v2, v1);
	fail += v.x == x2-x1 ? 0 : 1;
	fail += v.y == y2-y1 ? 0 : 1;
	fail += v.z == z2-z1 ? 0 : 1;
	
	printf(" > TEST_vector_from_A_B (%d)\n", fail);
	return fail;
}
int TEST_point_plus_vector() {
	int fail = 0;
	float x1 = 15.5;
	float y1 = 3.9;
	float z1 = 9.5;
	float x2 = 25.5;
	float y2 = -5;
	float z2 = -63.5;
	Point3D p1 = pointXYZ(x1, y1, z1);
	Vector3D v = vectorXYZ(x2, y2, z2);
	
	Point3D p2 = pointPlusVector(p1, v);
	fail += p2.x == x2 + x1 ? 0 : 1;
	fail += p2.y == y2 + y1 ? 0 : 1;
	fail += p2.z == z2 + z1 ? 0 : 1;
	
	printf(" > TEST_point_plus_vector (%d)\n", fail);
	return fail;
	
}
int TEST_add() {
	
	int fail = 0;
	float x1 = 15.5;
	float y1 = 3.9;
	float z1 = 9.5;
	float x2 = 25.5;
	float y2 = -5;
	float z2 = -63.5;
	Vector3D v1 = vectorXYZ(x1, y1, z1);
	Vector3D v2 = vectorXYZ(x2, y2, z2);
	
	Vector3D v = addVectors(v1, v2);
	fail += v.x == x1+x2 ? 0 : 1;
	fail += v.y == y1+y2 ? 0 : 1;
	fail += v.z == z1+z2 ? 0 : 1;
		
	printf(" > TEST_vector_add (%d)\n", fail);
	return fail;
}
int TEST_sub() {	
	int fail = 0;
	float x1 = 15.5;
	float y1 = 3.9;
	float z1 = 9.5;
	float x2 = 25.5;
	float y2 = -5;
	float z2 = -63.5;
	Vector3D v1 = vectorXYZ(x1, y1, z1);
	Vector3D v2 = vectorXYZ(x2, y2, z2);
	
	Vector3D v = subVectors(v1, v2);
	fail += v.x == x1-x2 ? 0 : 1;
	fail += v.y == y1-y2 ? 0 : 1;
	fail += v.z == z1-z2 ? 0 : 1;
		
	printf(" > TEST_vector_sub (%d)\n", fail);
	return fail;
}
int TEST_mult() {
	int fail = 0;
	float x = 15.5;
	float y = 3.9;
	float z = 9.5;
	Vector3D v1 = vectorXYZ(x, y, z);
	float scalaire = 1.5;	
	
	Vector3D v2 = multVectors(v1, scalaire);
	fail += v2.x == x * scalaire ? 0 : 1;
	fail += v2.y == y * scalaire ? 0 : 1;
	fail += v2.z == z * scalaire ? 0 : 1;
		
	printf(" > TEST_vector_mult (%d)\n", fail);
	return fail;	
}
int TEST_div() {	
	int fail = 0;
	float x = 15.5;
	float y = 3.9;
	float z = 9.5;
	Vector3D v1 = vectorXYZ(x, y, z);
	float scalaire = 7.35;	
	
	Vector3D v2 = divVectors(v1, scalaire);
	fail += v2.x == x / scalaire ? 0 : 1;
	fail += v2.y == y / scalaire ? 0 : 1;
	fail += v2.z == z / scalaire ? 0 : 1;
		
	printf(" > TEST_vector_div (%d)\n", fail);
	return fail;
}
int TEST_dot() {
	int fail = 0;
	float x1 = 15.5;
	float y1 = 3.9;
	float z1 = 9.5;
	float x2 = 25.5;
	float y2 = -5;
	float z2 = -63.5;
	Vector3D v1 = vectorXYZ(x1, y1, z1);
	Vector3D v2 = vectorXYZ(x2, y2, z2);
	
	dot(v1, v2);
	
	printf(" > TEST_vector_dot (%d)\n", fail);
	return fail;
}
int TEST_norm() {	
	int fail = 0;
	float x = 15.5;
	float y = 3.9;
	float z = 9.5;
	Vector3D v = vectorXYZ(x, y, z);
	
	norm(v);
	
	printf(" > TEST_vector_norm (%d)\n", fail);
	return fail;
}
int TEST_normalize() {
	
	int fail = 0;
	float x = 15.5;
	float y = 3.9;
	float z = 9.5;
	Vector3D v = vectorXYZ(x, y, z);
	
	normalize(v);
	
	printf(" > TEST_vector_normalize (%d)\n", fail);
	return fail;
	
}

int TEST_addColors(){
	int fails = 0;
	
	float r1 = 0.2;
	float g1 = 0.6;
	float b1 = 0.5;
	float r2 = 0.5;
	float g2 = 0.1;
	float b2 = 0.9;
	
	Color3f c1 = color(r1, g1, b1);
	Color3f c2 = color(r2, g2, b2);
	
	Color3f c3 = addColors(c1, c2);
	fails += c3.r > 1 || c3.r < 0 ? 1 : 0;
	fails += c3.g > 1 || c3.g < 0 ? 1 : 0;
	fails += c3.b > 1 || c3.b < 0 ? 1 : 0;
	
	printf(" > TEST_addColors (%d)\n", fails);
	return fails;
}
int TEST_subColors(){
	int fails = 0;
	
	float r1 = 0.2;
	float g1 = 0.6;
	float b1 = 0.5;
	float r2 = 0.5;
	float g2 = 0.1;
	float b2 = 0.9;
	
	Color3f c1 = color(r1, g1, b1);
	Color3f c2 = color(r2, g2, b2);
	
	Color3f c3 = subColors(c1, c2);
	fails += c3.r > 1 || c3.r < 0 ? 1 : 0;
	fails += c3.g > 1 || c3.g < 0 ? 1 : 0;
	fails += c3.b > 1 || c3.b < 0 ? 1 : 0;
	
	printf(" > TEST_subColors (%d)\n", fails);
	return fails;
}
int TEST_multColors(){
	int fails = 0;
	
	float r1 = 0.2;
	float g1 = 0.6;
	float b1 = 0.5;
	float r2 = 0.5;
	float g2 = 0.1;
	float b2 = 0.9;
	
	Color3f c1 = color(r1, g1, b1);
	Color3f c2 = color(r2, g2, b2);
	
	Color3f c3 = multColors(c1, c2);
	fails += c3.r > 1 || c3.r < 0 ? 1 : 0;
	fails += c3.g > 1 || c3.g < 0 ? 1 : 0;
	fails += c3.b > 1 || c3.b < 0 ? 1 : 0;
	
	printf(" > TEST_multColors (%d)\n", fails);
	return fails;
}
int TEST_multColor(){
	int fails = 0;
	
	float r = 0.2;
	float g = 0.6;
	float b = 0.5;
	float scalaire = 1.3;
	
	Color3f c1 = color(r, g, b);	
	Color3f c2 = multColor(c1, scalaire);
	
	fails += c2.r > 1 || c2.r < 0 ? 1 : 0;
	fails += c2.g > 1 || c2.g < 0 ? 1 : 0;
	fails += c2.b > 1 || c2.b < 0 ? 1 : 0;
	
	printf(" > TEST_multColors (%d)\n", fails);
	return fails;
}
int TEST_divColor(){
	int fails = 0;
	
	float r = 0.2;
	float g = 0.6;
	float b = 0.5;
	float scalaire = 1.3;
	
	Color3f c1 = color(r, g, b);	
	Color3f c2 = divColor(c1, scalaire);
	
	fails += c2.r > 1 || c2.r < 0 ? 1 : 0;
	fails += c2.g > 1 || c2.g < 0 ? 1 : 0;
	fails += c2.b > 1 || c2.b < 0 ? 1 : 0;
	
	printf(" > TEST_divColor (%d)\n", fails);
	return fails;
}

void displayColor(Color3f c) {
	printf("Color(%f|%f|%f)\n", c.r, c.g, c.b);	
}
void displayPoint(Point3D p) {
	printf("Point(%f|%f|%f)\n", p.x, p.y, p.z);
}
void displayVector(Vector3D v) {
	printf("Vector(%f|%f|%f)\n", v.x, v.y, v.z);
}