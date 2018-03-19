#ifndef TEST_H
#define TEST_H

#include "geometry.h"

void run_all_tests();
int TEST_point_creation();
int TEST_vector_creation();
int TEST_vector_from_A_B();
void displayPoint(Point3D p);
void displayVector(Vector3D v);

#endif