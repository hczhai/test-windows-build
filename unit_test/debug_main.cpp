
/*
 * block2: Efficient MPO implementation of quantum chemistry DMRG
 * Copyright (C) 2020-2021 Huanchen Zhai <hczhai@caltech.edu>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 */

// #include "block2_core.hpp"
#include <iostream>

using namespace std;
using namespace block2;

extern "C" {

extern void dgemm(const char *transa, const char *transb,
                        const long long int *m, const long long int *n, const long long int *k,
                        const double *alpha, const double *a,
                        const long long int *lda, const double *b,
                        const long long int *ldb, const double *beta, double *c,
                        const long long int *ldc) noexcept;
}

int main(int argc, char *argv[])
{
    // cout << "ok1" << endl;
    // shared_ptr<VectorAllocator<double>> d_alloc = make_shared<VectorAllocator<double>>();
    // GMatrix<double> mat(nullptr, 5, 5);
    // mat.data = d_alloc->allocate(mat.size());
    // Random::fill<double>(mat.data, mat.size());
    // cout << "1:" << mat << endl;

    // GMatrix<double> mat2(nullptr, 5, 5);
    // mat2.data = d_alloc->allocate(mat2.size());
    // Random::fill<double>(mat2.data, mat2.size());
    // cout << "2:" << mat2 << endl;

    // GMatrix<double> mat3(nullptr, 5, 5);
    // mat3.data = d_alloc->allocate(mat3.size());
    // Random::fill<double>(mat3.data, mat3.size());
    // cout << "3:" << mat3 << endl;

    cout << sizeof(long long int) << endl;
    long long int nx = 5;
    double alpha = 1.0, beta = 0.0;

    vector<double> mat(25);
    mat[0] = 1, mat[1] = 2;

    vector<double> mat2(25);
    mat2[0] = 1, mat2[1] = 2;

    vector<double> mat3(25);
    mat3[0] = 1, mat3[1] = 2;

    dgemm("n", "n", &nx, &nx, &nx, &alpha, mat.data(),
                        &nx, mat2.data(),
                        &nx, &beta, mat3.data(),
                        &nx);

    // cout << "f:" << mat3 << endl;

    // GMatrixFunctions<double>::multiply(mat, 0, mat2, 0, mat3, 1.0, 0.0);
    cout << "ok2" << endl;
    // cout << SU2() << endl;
    return 0;
}