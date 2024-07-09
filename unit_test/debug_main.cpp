
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

#include "block2_core.hpp"
#include <iostream>

extern "C"
{
    int mkl_serv_intel_cpu_true() { return 1; }
}

using namespace std;
using namespace block2;

int main(int argc, char *argv[])
{
    cout << "ok1" << endl;
    cout << mkl_serv_intel_cpu_true()  << endl;
    shared_ptr<VectorAllocator<double>> d_alloc = make_shared<VectorAllocator<double>>();
    GMatrix<double> mat(nullptr, 5, 5);
    mat.data = d_alloc->allocate(mat.size());
    Random::fill<double>(mat.data, mat.size());
    cout << "1:" << mat << endl;

    GMatrix<double> mat2(nullptr, 5, 5);
    mat2.data = d_alloc->allocate(mat2.size());
    Random::fill<double>(mat2.data, mat2.size());
    cout << "2:" << mat2 << endl;

    GMatrix<double> mat3(nullptr, 5, 5);
    mat3.data = d_alloc->allocate(mat3.size());
    Random::fill<double>(mat3.data, mat3.size());
    cout << "3:" << mat3 << endl;

    // GMatrixFunctions<double>::multiply(mat, 0, mat2, 0, mat3, 1.0, 0.0);
    cout << "ok2" << endl;
    cout << SU2() << endl;
    return 0;
}