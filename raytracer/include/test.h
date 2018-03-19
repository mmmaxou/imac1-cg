#ifndef TEST_H
#define TEST_H

#include "geometry.h"
#include "colors.h"

void run_all_tests();
void run_case_tests();

/* GEOMETRY */
int TEST_point_creation();
int TEST_vector_creation();
int TEST_vector_from_A_B();
int TEST_point_plus_vector();
int TEST_add();
int TEST_sub();
int TEST_mult();
int TEST_div();
int TEST_dot();
int TEST_norm();
int TEST_normalize();
void displayPoint(Point3D p);
void displayVector(Vector3D v);

/* COLORS */
int TEST_addColors();
int TEST_subColors();
int TEST_multColors();
int TEST_multColor();
int TEST_divColor();
void displayColor(Color3f c);

#endif