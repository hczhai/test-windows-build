
#include <iostream>
#include <vector>

using namespace std;

extern "C" {

extern void dgemm(const char *transa, const char *transb,
                        const int *m, const int *n, const int *k,
                        const double *alpha, const double *a,
                        const int *lda, const double *b,
                        const int *ldb, const double *beta, double *c,
                        const int *ldc) noexcept;

}

int main(int argc, char *argv[]) {

    cout << sizeof(long long int) << endl;
    int nx = 5;
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

    cout << "ok2" << endl;
    return 0;
}