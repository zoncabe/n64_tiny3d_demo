#ifndef PHYSICS_MATH_COMMON_H
#define PHYSICS_MATH_COMMON_H


#define PI 3.141592653589f
#define PI_TIMES_2 6.28318530f

#define TOLERANCE 0.000001f

// function prototypes

float rad(float angle);
float deg(float rad);

int clamp_int(int value, int lowerLimit, int upperLimit);
float clamp(float value, float lowerLimit, float upperLimit);

float max2(float a, float b);
float min2(float a, float b);

float min3(float a, float b, float c);
float max3(float a, float b, float c);

bool sameSign(float a, float b);
bool approxEqual(float a, float b);

bool isfinite(float x);


#endif
