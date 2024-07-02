#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H


bool areParallelVectors(const Vector3* vector1, const Vector3* vector2);
bool areOrthogonalVectors(const Vector3* vector1, const Vector3* vector2);
Vector3 clamp_vector(const Vector3* vector, float maxLength);

Vector3 closestPointOnSegmentToPoint(const Vector3* segPointA, const Vector3* segPointB, const Vector3* pointC);
void getClosestPointsBetweenTwoSegments(const Vector3* seg1PointA, const Vector3* seg1PointB, const Vector3* seg2PointA, const Vector3* seg2PointB, Vector3* closestPointSeg1, Vector3* closestPointSeg2);

void getBarycentricCoordinatesInTriangle(const Vector3* a, const Vector3* b, const Vector3* c,  const Vector3* p, float* u, float* v, float* w);

float intersectionPlaneAndSegment(const Vector3* segA, const Vector3* segB, float planeD, const Vector3* planeNormal);
float distancePointToLine(const Vector3* linePointA, const Vector3* linePointB, const Vector3* point);
Vector3 projectionPointOnPlane(const Vector3* point, const Vector3* unitPlaneNormal, const Vector3* planePoint);
float distancePointToPlane(const Vector3* point, const Vector3* planeNormal, const Vector3* planePoint);
bool isPowerOfTwo(uint64_t number);
uint64_t nextPowerOfTwo64Bits(uint64_t number);
uint64_t pairNumbers(uint32_t number1, uint32_t number2);


/* areParallelVectors
return true if two vectors are parallel */
inline bool areParallelVectors(const Vector3* vector1, const Vector3* vector2) {
    Vector3 crossProduct = {
        vector1->y * vector2->z - vector1->z * vector2->y,
        vector1->z * vector2->x - vector1->x * vector2->z,
        vector1->x * vector2->y - vector1->y * vector2->x
    };
    return (crossProduct.x * crossProduct.x + crossProduct.y * crossProduct.y + crossProduct.z * crossProduct.z) < 0.00001f;
}

/* areOrthogonalVectors
return true if two vectors are orthogonal */
inline bool areOrthogonalVectors(const Vector3* vector1, const Vector3* vector2) {
    float dotProduct = vector1->x * vector2->x + vector1->y * vector2->y + vector1->z * vector2->z;
    return fabsf(dotProduct) < 0.001f;
}

/* clamp_vector
clamp a vector such that it is no longer than a given maximum length */
inline Vector3 clamp_vector(const Vector3* vector, float maxLength) {
    float lengthSquare = vector->x * vector->x + vector->y * vector->y + vector->z * vector->z;
    if (lengthSquare > maxLength * maxLength) {
        float length = qi_sqrt(lengthSquare);
        return (Vector3){ vector->x * maxLength / length, vector->y * maxLength / length, vector->z * maxLength / length };
    }
    return *vector;
}

/* closestPointOnSegmentToPoint
compute and return a point on segment from "segPointA" and "segPointB" that is closest to point "pointC" */
inline Vector3 closestPointOnSegmentToPoint(const Vector3* segPointA, const Vector3* segPointB, const Vector3* pointC) {
    Vector3 ab = { segPointB->x - segPointA->x, segPointB->y - segPointA->y, segPointB->z - segPointA->z };
    Vector3 ac = { pointC->x - segPointA->x, pointC->y - segPointA->y, pointC->z - segPointA->z };
    float abLengthSquare = ab.x * ab.x + ab.y * ab.y + ab.z * ab.z;

    // If the segment has almost zero length
    if (abLengthSquare < 1e-6f) {
        // Return one end-point of the segment as the closest point
        return *segPointA;
    }

    // Project point C onto "AB" line
    float t = (ac.x * ab.x + ac.y * ab.y + ac.z * ab.z) / abLengthSquare;

    // If projected point onto the line is outside the segment, clamp it to the segment
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    // Return the closest point on the segment
    return (Vector3){ segPointA->x + t * ab.x, segPointA->y + t * ab.y, segPointA->z + t * ab.z };
}

/* getClosestPointsBetweenTwoSegments
compute the closest points between two segments */
inline void getClosestPointsBetweenTwoSegments(const Vector3* seg1PointA, const Vector3* seg1PointB,
                                                  const Vector3* seg2PointA, const Vector3* seg2PointB,
                                                  Vector3* closestPointSeg1, Vector3* closestPointSeg2) {

    Vector3 d1 = { seg1PointB->x - seg1PointA->x, seg1PointB->y - seg1PointA->y, seg1PointB->z - seg1PointA->z };
    Vector3 d2 = { seg2PointB->x - seg2PointA->x, seg2PointB->y - seg2PointA->y, seg2PointB->z - seg2PointA->z };
    Vector3 r = { seg1PointA->x - seg2PointA->x, seg1PointA->y - seg2PointA->y, seg1PointA->z - seg2PointA->z };
    float a = d1.x * d1.x + d1.y * d1.y + d1.z * d1.z;
    float e = d2.x * d2.x + d2.y * d2.y + d2.z * d2.z;
    float f = d2.x * r.x + d2.y * r.y + d2.z * r.z;
    float s, t;

    // If both segments degenerate into points
    if (a <= 1e-6f && e <= 1e-6f) {
        *closestPointSeg1 = *seg1PointA;
        *closestPointSeg2 = *seg2PointA;
        return;
    }
    if (a <= 1e-6f) {   // If first segment degenerates into a point
        s = 0.0f;
        // Compute the closest point on second segment
        t = clamp_float(f / e, 0.0f, 1.0f);
    } else {
        float c = d1.x * r.x + d1.y * r.y + d1.z * r.z;
        // If the second segment degenerates into a point
        if (e <= 1e-6f) {
            t = 0.0f;
            s = clamp_float(-c / a, 0.0f, 1.0f);
        } else {
            float b = d1.x * d2.x + d1.y * d2.y + d1.z * d2.z;
            float denom = a * e - b * b;
            // If the segments are not parallel
            if (denom != 0.0f) {
                // Compute the closest point on line 1 to line 2 and
                // clamp to first segment.
                s = clamp_float((b * f - c * e) / denom, 0.0f, 1.0f);
            } else {
                // Pick an arbitrary point on first segment
                s = 0.0f;
            }
            // Compute the point on line 2 closest to the closest point
            // we have just found
            t = (b * s + f) / e;
            // If this closest point is inside second segment (t in [0, 1]), we are done.
            // Otherwise, we clamp the point to the second segment and compute again the
            // closest point on segment 1
            if (t < 0.0f) {
                t = 0.0f;
                s = clamp_float(-c / a, 0.0f, 1.0f);
            } else if (t > 1.0f) {
                t = 1.0f;
                s = clamp_float((b - c) / a, 0.0f, 1.0f);
            }
        }
    }

    // Compute the closest points on both segments
    *closestPointSeg1 = (Vector3){ seg1PointA->x + d1.x * s, seg1PointA->y + d1.y * s, seg1PointA->z + d1.z * s };
    *closestPointSeg2 = (Vector3){ seg2PointA->x + d2.x * t, seg2PointA->y + d2.y * t, seg2PointA->z + d2.z * t };
}

/* getBarycentricCoordinatesInTriangle
compute the barycentric coordinates u, v, w of a point p inside the triangle (a, b, c) */
inline void getBarycentricCoordinatesInTriangle(const Vector3* a, const Vector3* b, const Vector3* c,
                                                    const Vector3* p, float* u, float* v, float* w) {
    Vector3 v0 = { b->x - a->x, b->y - a->y, b->z - a->z };
    Vector3 v1 = { c->x - a->x, c->y - a->y, c->z - a->z };
    Vector3 v2 = { p->x - a->x, p->y - a->y, p->z - a->z };

    float d00 = v0.x * v0.x + v0.y * v0.y + v0.z * v0.z;
    float d01 = v0.x * v1.x + v0.y * v1.y + v0.z * v1.z;
    float d11 = v1.x * v1.x + v1.y * v1.y + v1.z * v1.z;
    float d20 = v2.x * v0.x + v2.y * v0.y + v2.z * v0.z;
    float d21 = v2.x * v1.x + v2.y * v1.y + v2.z * v1.z;

    float denom = d00 * d11 - d01 * d01;
    *v = (d11 * d20 - d01 * d21) / denom;
    *w = (d00 * d21 - d01 * d20) / denom;
    *u = 1.0f - *v - *w;
}

/* intersectionPlaneAndSegment
compute the intersection between a plane and a segment */
inline float intersectionPlaneAndSegment(const Vector3* segA, const Vector3* segB, float planeD, const Vector3* planeNormal) {
    const float parallelEpsilon = 0.0001f;
    float t = -1.0f;

    Vector3 ab = { segB->x - segA->x, segB->y - segA->y, segB->z - segA->z };
    float nDotAB = planeNormal->x * ab.x + planeNormal->y * ab.y + planeNormal->z * ab.z;

    // If the segment is not parallel to the plane
    if (fabsf(nDotAB) > parallelEpsilon) {
        t = (planeD - (planeNormal->x * segA->x + planeNormal->y * segA->y + planeNormal->z * segA->z)) / nDotAB;
    }

    return t;
}

/* distancePointToLine
compute the distance between a point "point" and a line given by the points "linePointA" and "linePointB" */
inline float distancePointToLine(const Vector3* linePointA, const Vector3* linePointB, const Vector3* point) {
    float distAB = qi_sqrt((linePointB->x - linePointA->x) * (linePointB->x - linePointA->x) +
                         (linePointB->y - linePointA->y) * (linePointB->y - linePointA->y) +
                         (linePointB->z - linePointA->z) * (linePointB->z - linePointA->z));

    if (distAB < 1e-6f) {
        return qi_sqrt((point->x - linePointA->x) * (point->x - linePointA->x) +
                     (point->y - linePointA->y) * (point->y - linePointA->y) +
                     (point->z - linePointA->z) * (point->z - linePointA->z));
    }

    Vector3 crossProduct = { (point->y - linePointA->y) * (point->z - linePointB->z) - (point->z - linePointA->z) * (point->y - linePointB->y),
                             (point->z - linePointA->z) * (point->x - linePointB->x) - (point->x - linePointA->x) * (point->z - linePointB->z),
                             (point->x - linePointA->x) * (point->y - linePointB->y) - (point->y - linePointA->y) * (point->x - linePointB->x) };

    float crossLength = qi_sqrt(crossProduct.x * crossProduct.x + crossProduct.y * crossProduct.y + crossProduct.z * crossProduct.z);

    return crossLength / distAB;
}

/* projectionPointOnPlane
project a point onto a plane that is given by a point and its unit length normal */
inline Vector3 projectionPointOnPlane(const Vector3* point, const Vector3* unitPlaneNormal, const Vector3* planePoint) {
    float dotProduct = unitPlaneNormal->x * (point->x - planePoint->x) +
                       unitPlaneNormal->y * (point->y - planePoint->y) +
                       unitPlaneNormal->z * (point->z - planePoint->z);

    return (Vector3){ point->x - dotProduct * unitPlaneNormal->x,
                      point->y - dotProduct * unitPlaneNormal->y,
                      point->z - dotProduct * unitPlaneNormal->z };
}

/* distancePointToPlane
return the distance between a point and a plane (the plane normal must be normalized) */
inline float distancePointToPlane(const Vector3* point, const Vector3* planeNormal, const Vector3* planePoint) {
    return planeNormal->x * (point->x - planePoint->x) +
           planeNormal->y * (point->y - planePoint->y) +
           planeNormal->z * (point->z - planePoint->z);
}

/* isPowerOfTwo
return true if a number is a power of two */
inline bool isPowerOfTwo(uint64_t number) {
    return number != 0 && !(number & (number - 1));
}

/* nextPowerOfTwo64Bits
return the next power of two larger than the number in parameter */
inline uint64_t nextPowerOfTwo64Bits(uint64_t number) {
    number--;
    number |= number >> 1;
    number |= number >> 2;
    number |= number >> 4;
    number |= number >> 8;
    number |= number >> 16;
    number |= number >> 32;
    number++;
    return number;
}

/* pairNumbers
return a unique integer from two integer numbers (pairing function) */
inline uint64_t pairNumbers(uint32_t number1, uint32_t number2) {
    assert(number1 >= number2);
    uint64_t nb1 = number1;
    uint64_t nb2 = number2;
    return nb1 * nb1 + nb1 + nb2;
}

#endif
