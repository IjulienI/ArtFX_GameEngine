/**
 * @file MatMN.cpp
 * @brief Implementation of the MatMN class, which represents an MxN matrix and provides various matrix operations.
 */

#include "MatMN.h"

#include <cmath>

#include "Core/Physic/PhysicConstants.h"

/**
 * @brief Default constructor for MatMN. Initializes an empty matrix.
 */
MatMN::MatMN() : M(0), N(0), rows(nullptr)
{
}

/**
 * @brief Constructs an MxN matrix and initializes its rows.
 * @param M Number of rows.
 * @param N Number of columns.
 */
MatMN::MatMN(int M, int N) : M(M), N(N)
{
    rows = new VecN[M];
    for (int i = 0; i < M; i++)
    {
        rows[i] = VecN(N);
    }
}

/**
 * @brief Copy constructor for MatMN.
 * @param m Matrix to copy.
 */
MatMN::MatMN(const MatMN& m)
{
    *this = m;
}

/**
 * @brief Destructor for MatMN. Releases allocated memory.
 */
MatMN::~MatMN()
{
    delete[] rows;
}

/**
 * @brief Sets all elements of the matrix to zero.
 */
void MatMN::Zero()
{
    for (int i = 0; i < M; i++)
    {
        rows[i].Zero();
    }
}

/**
 * @brief Computes the transpose of the matrix.
 * @return Transposed matrix.
 */
MatMN MatMN::Transpose() const
{
    MatMN result(N, M);
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            result.rows[j][i] = rows[i][j];
        }
    }
    return result;
}

/**
 * @brief Computes the inverse of the matrix using Gaussian elimination.
 * @return Inverted matrix if the matrix is square and invertible, otherwise an empty matrix.
 */
MatMN MatMN::Inverse() const
{
    if (M != N)
    {
        return MatMN();
    }

    MatMN augmented(M, 2 * N);
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            augmented.rows[i][j] = rows[i][j];
            augmented.rows[i][j + N] = (i == j) ? 1.0f : 0.0f;
        }
    }

    for (int i = 0; i < M; i++)
    {
        float pivot = augmented.rows[i][i];
        if (fabs(pivot) < EPSILON)
        {
            return MatMN();
        }

        for (int j = 0; j < 2 * N; j++)
        {
            augmented.rows[i][j] /= pivot;
        }

        for (int k = 0; k < M; k++)
        {
            if (k != i)
            {
                float factor = augmented.rows[k][i];
                for (int j = 0; j < 2 * N; j++)
                {
                    augmented.rows[k][j] -= factor * augmented.rows[i][j];
                }
            }
        }
    }

    MatMN result(M, N);
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            result.rows[i][j] = augmented.rows[i][j + N];
        }
    }

    return result;
}

/**
 * @brief Assignment operator for MatMN.
 * @param m Matrix to assign.
 * @return Reference to the assigned matrix.
 */
const MatMN& MatMN::operator=(const MatMN& m)
{
    M = m.M;
    N = m.N;
    rows = new VecN[M];
    for (int i = 0; i < M; i++)
    {
        rows[i] = m.rows[i];
    }
    return *this;
}

/**
 * @brief Multiplies the matrix with a vector.
 * @param v Vector to multiply.
 * @return Resulting vector after multiplication.
 */
VecN MatMN::operator*(const VecN& v) const
{
    if (v.N != N)
    {
        return v;
    }
    VecN result(M);
    for (int i = 0; i < M; i++)
    {
        result[i] = v.Dot(rows[i]);
    }
    return result;
}

/**
 * @brief Multiplies the matrix with another matrix.
 * @param m Matrix to multiply.
 * @return Resulting matrix after multiplication.
 */
MatMN MatMN::operator*(const MatMN& m) const
{
    if (m.M != N && m.N != M)
        return m;
    MatMN tranposed = m.Transpose();
    MatMN result(M, m.N);
    for (int i = 0; i < M; i++)
        for (int j = 0; j < m.N; j++)
            result.rows[i][j] = rows[i].Dot(tranposed.rows[j]);
    return result;
}

/**
 * @brief Accesses a specific row of the matrix.
 * @param i Index of the row.
 * @return Reference to the row vector.
 */
VecN& MatMN::operator[](int i)
{
    return rows[i];
}

/**
 * @brief Solves a linear system using the Gauss-Seidel method.
 * @param A Coefficient matrix.
 * @param b Right-hand side vector.
 * @return Solution vector.
 */
VecN MatMN::SolveGaussSeidel(const MatMN& A, const VecN& b)
{
    const int N = b.N;
    VecN X(N);
    X.Zero();

    for (int iterations = 0; iterations < N; iterations++)
    {
        for (int i = 0; i < N; i++)
        {
            float dx = (b[i] / A.rows[i][i]) - (A.rows[i].Dot(X) / A.rows[i][i]);
            if (dx == dx)
            {
                X[i] += dx;
            }
        }
    }
    return X;
}

/**
 * @brief Multiplies a 3x3 matrix with a 3D vector.
 * @param m Matrix to multiply.
 * @param v Vector to multiply.
 * @return Resulting vector after multiplication.
 */
Vec3 operator*(const MatMN& m, const Vec3& v)
{
    float x = m.rows[0][0] * v.x + m.rows[0][1] * v.y + m.rows[0][2] * v.z;
    float y = m.rows[1][0] * v.x + m.rows[1][1] * v.y + m.rows[1][2] * v.z;
    float z = m.rows[2][0] * v.x + m.rows[2][1] * v.y + m.rows[2][2] * v.z;

    return Vec3(x, y, z);
}
