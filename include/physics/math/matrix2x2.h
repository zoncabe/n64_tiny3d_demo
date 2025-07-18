#ifndef MATRIX2X2_H
#define MATRIX2X2_H


typedef struct {

    Vector2 row[2];

} Matrix2x2;


// Function prototypes

void matrix2x2_init(Matrix2x2* matrix);
void matrix2x2_clear(Matrix2x2* matrix);

void matrix2x2_set(Matrix2x2* matrix, float a1, float a2, float b1, float b2);
void matrix2x2_setWithValue(Matrix2x2* matrix, float value);

Vector2 matrix2x2_returnColumn(const Matrix2x2* matrix, int i);
Vector2 matrix2x2_returnRow(const Matrix2x2* matrix, int i);

Matrix2x2 matrix2x2_sum(const Matrix2x2* matrix1, const Matrix2x2* matrix2);
void matrix2x2_add(Matrix2x2* matrix1, const Matrix2x2* matrix2);

Matrix2x2 matrix2x2_difference(const Matrix2x2* matrix1, const Matrix2x2* matrix2);
void matrix2x2_subtract(Matrix2x2* matrix1, const Matrix2x2* matrix2);

Matrix2x2 matrix2x2_returnScaled(const Matrix2x2* matrix, float scalar);
void matrix2x2_scale(Matrix2x2* matrix, float scalar);

Matrix2x2 matrix2x2_returnProduct(const Matrix2x2* matrix1, const Matrix2x2* matrix2);
Vector2 matrix2x2_returnProductByVector(const Matrix2x2* matrix, const Vector2* vector);

Matrix2x2 matrix2x2_returnNegative(const Matrix2x2* matrix);
Matrix2x2 matrix2x2_returnTranspose(const Matrix2x2* matrix);
float matrix2x2_returnDeterminant(const Matrix2x2* matrix);
float matrix2x2_returnTrace(const Matrix2x2* matrix);
Matrix2x2 matrix2x2_returnInverse(const Matrix2x2* matrix);
Matrix2x2 matrix2x2_returnAbsoluteMatrix(const Matrix2x2* matrix);

void matrix2x2_setIdentity(Matrix2x2* matrix);
Matrix2x2 matrix2x2_returnIdentity();

int matrix2x2_equals(const Matrix2x2* matrix1, const Matrix2x2* matrix2);
int matrix2x2_notEquals(const Matrix2x2* matrix1, const Matrix2x2* matrix2);

#endif 
