
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

using namespace std;
using namespace block2;

int main(int argc, char *argv[]) {
    cout << "ok1" << endl;
    shared_ptr<VectorAllocator<double>> d_alloc = make_shared<VectorAllocator<double>>();
    GMatrix<double> mat(nullptr, 5, 5);
    mat.data = d_alloc->allocate(mat.size());
    Random::fill<double>(mat.data, mat.size());
    cout << mat << endl;
    cout << "ok2" << endl;
    cout << SU2() << endl;
    return 0;
}