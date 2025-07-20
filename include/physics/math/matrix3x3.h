/**
 * @file
 *
 * holds a 3x3 matrix.
 */

#ifndef MATRIX3X3_H
#define MATRIX3X3_H


typedef struct {

    Vector3 row[3];

} Matrix3x3;


// Function prototypes
void matrix3x3_init(Matrix3x3* matrix);
void matrix3x3_clear(Matrix3x3* matrix);

void matrix3x3_set(Matrix3x3* matrix, float a1, float a2, float a3, float b1, float b2, float b3, float c1, float c2, float c3);
void matrix3x3_setWithValue(Matrix3x3* matrix, float value);

Vector3 matrix3x3_returnColumn(const Matrix3x3* matrix, int i);
Vector3 matrix3x3_returnRow(const Matrix3x3* matrix, int i);

void matrix3x3_add(Matrix3x3* matrix1, const Matrix3x3* matrix2);
Matrix3x3 matrix3x3_sum(const Matrix3x3* matrix1, const Matrix3x3* matrix2);

void matrix3x3_subtract(Matrix3x3* matrix1, const Matrix3x3* matrix2);
Matrix3x3 matrix3x3_difference(const Matrix3x3* matrix1, const Matrix3x3* matrix2);

Matrix3x3 matrix3x3_returnScaled(const Matrix3x3* matrix, float scalar);
void matrix3x3_scale(Matrix3x3* matrix, float scalar);

Matrix3x3 matrix3x3_multiply(const Matrix3x3* matrix1, const Matrix3x3* matrix2);
Vector3 matrix3x3_multiplyByVector(const Matrix3x3* matrix, const Vector3* vector);

Matrix3x3 matrix3x3_returnNegative(const Matrix3x3* matrix);
Matrix3x3 matrix3x3_returnTranspose(const Matrix3x3* matrix);
float matrix3x3_returnDeterminant(const Matrix3x3* matrix);
float matrix3x3_returnTrace(const Matrix3x3* matrix);
Matrix3x3 matrix3x3_returnInverse(const Matrix3x3* matrix);
Matrix3x3 matrix3x3_returnAbsoluteMatrix(const Matrix3x3* matrix);

void matrix3x3_setIdentity(Matrix3x3* matrix);
Matrix3x3 matrix3x3_returnIdentity();

Matrix3x3 matrix3x3_computeSkewSymmetricMatrixForCrossProduct(const Vector3* vector);

int matrix3x3_equals(const Matrix3x3* matrix1, const Matrix3x3* matrix2);
int matrix3x3_notEquals(const Matrix3x3* matrix1, const Matrix3x3* matrix2);


#endif
