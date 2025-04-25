#pragma once

#include "Vec3.h"
#include "VecN.h"

struct MatMN {
	int M;
	int N;
	VecN* rows;

	MatMN();
	MatMN(int M, int N);
	MatMN(const MatMN& m);
	~MatMN();

	void Zero();
	MatMN Transpose() const;
	MatMN Inverse()const;

	const MatMN& operator = (const MatMN& m);
	VecN operator * (const VecN& v) const;
	MatMN operator * (const MatMN& m) const;
	VecN& operator [] (int i);	

	static VecN SolveGaussSeidel(const MatMN& A, const VecN& b);
};

Vec3 operator* (const MatMN& m, const Vec3& v);

