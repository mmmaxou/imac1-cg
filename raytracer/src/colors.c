#include "colors.h"

#include <stdlib.h>
#include <stdio.h>

Color3f color(float r, float g, float b) {
	Color3f tmp;
	tmp.r = r;
	tmp.g = g;
	tmp.b = b;
	return tmp;
}

Color3f normColor(Color3f c) {
	float r,g,b;
	r = c.r;
	g = c.g;
	b = c.b;
	
	r = r>1.0 ? r-1: r;
	r = r<0.0 ? r+1: r;
	
	g = g>1.0 ? g-1: g;
	g = g<0.0 ? g+1: g;
	
	b = b>1.0 ? b-1: b;
	b = b<0.0 ? b+1: b;
	return color(r, g, b);
}
Color3f addColors(Color3f c1, Color3f c2) {
	float r,g,b;
	r = c1.r + c2.r;
	g = c1.g + c2.g;
	b = c1.b + c2.b;
	Color3f c = color(r, g, b);
	return normColor(c);
}
Color3f subColors(Color3f c1, Color3f c2) {
	float r,g,b;
	r = c1.r - c2.r;
	g = c1.g - c2.g;
	b = c1.b - c2.b;
	Color3f c = color(r, g, b);
	return normColor(c);
}
Color3f multColors(Color3f c1, Color3f c2) {
	float r,g,b;
	r = c1.r * c2.r;
	g = c1.g * c2.g;
	b = c1.b * c2.b;
	Color3f c = color(r, g, b);
	return normColor(c);
}
Color3f multColor(Color3f c, float a) {
	float r,g,b;
	r = c.r * a;
	g = c.g * a;
	b = c.b * a;
	Color3f tmp = color(r, g, b);
	return normColor(tmp);
}
Color3f divColor(Color3f c, float a) {
	float r,g,b;
	r = c.r / a;
	g = c.g / a;
	b = c.b / a;
	Color3f tmp = color(r, g, b);
	return normColor(tmp);
	
}