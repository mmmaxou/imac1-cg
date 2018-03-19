#include <stdlib.h>
#include <stdio.h>

#include "geometry.h"
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
	printf("Test running:\n");
	fails += TEST_point_creation();
	fails += TEST_vector_creation();
	fails += TEST_vector_from_A_B();
	fails += TEST_add();
	printf("FAILS : %d\n", fails);
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
	Vector3D v1 = vectorXYZ(x1, y1, z1);
	Vector3D v2 = vectorXYZ(x2, y2, z2);
	
	Vector3D v = vector(v2, v1);
	fail += v.x == x2-x1 ? 0 : 1;
	fail += v.y == y2-y1 ? 0 : 1;
	fail += v.z == z2-z1 ? 0 : 1;
	
	printf(" > TEST_vector_creation (%d)\n", fail);
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

int TEST_sub();
int TEST_mult();
int TEST_div();

void displayPoint(Point3D p) {
	printf("Point(%f|%f|%f)\n", p.x, p.y, p.z);
}

void displayVector(Vector3D v) {
	printf("Vector(%f|%f|%f)\n", v.x, v.y, v.z);
}