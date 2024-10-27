
#include "block2_core.hpp"

using namespace block2;

int main(int argc, char *argv[])
{
    size_t isize = 1LL << 24;
    size_t dsize = 1LL << 28;
    using FL = double;
    Random::rand_seed(0);
    unsigned int sd = (unsigned)Random::rand_int(1, 1 << 30);
    cout << "seed = " << sd << endl;
    Random::rand_seed(sd);
    frame_<FL>() = make_shared<DataFrame<FL>>(isize, dsize, "nodex");

    int n_tests = 100;

    const FL thrd = is_same<FL, double>::value ? 1E-12 : 1E-6;
    shared_ptr<BatchGEMMSeq<FL>> seq = make_shared<BatchGEMMSeq<FL>>(0, SeqTypes::None);
    for (int i = 0; i < n_tests; i++)
    {
        MKL_INT m = Random::rand_int(1, 200), n = Random::rand_int(1, 200);
        GMatrix<FL> a(dalloc_<FL>()->allocate(m * n), m, n);
        GMatrix<FL> c(dalloc_<FL>()->allocate(m * n), m, n);
        GMatrix<FL> b(dalloc_<FL>()->allocate(m * n), m, n);
        uint8_t conjb = Random::rand_int(0, 3);
        uint8_t ii = Random::rand_int(0, 2), jj = Random::rand_int(0, 2);
        FL scale, cfactor;
        Random::fill<FL>(&scale, 1);
        Random::fill<FL>(&cfactor, 1);
        Random::fill<FL>(a.data, a.size());
        Random::fill<FL>(b.data, b.size());
        if (ii)
            scale = 1.0;
        if (jj)
            cfactor = 1.0;
        if (conjb == 2)
            cfactor = 1;
        GMatrix<FL> tb = b;
        if (conjb)
        {
            tb = GMatrix<FL>(dalloc_<FL>()->allocate(n * m), n, m);
            for (MKL_INT ik = 0; ik < m; ik++)
                for (MKL_INT jk = 0; jk < n; jk++)
                    tb(jk, ik) = b(ik, jk);
        }
        GMatrixFunctions<FL>::copy(c, a);
        if (conjb == 2)
            GMatrixFunctions<FL>::transpose(c, tb, scale);
        else
            GMatrixFunctions<FL>::iadd(c, tb, scale, (bool)conjb, cfactor);
        for (MKL_INT ik = 0; ik < m; ik++)
            for (MKL_INT jk = 0; jk < n; jk++)
                if (!(
                        abs(cfactor * a(ik, jk) + scale * b(ik, jk) - c(ik, jk)) <
                        thrd + thrd * abs(c(ik, jk))))
                {
                    cout << abs(cfactor * a(ik, jk) + scale * b(ik, jk) - c(ik, jk)) << "," << thrd + thrd * abs(c(ik, jk)) << endl;
                    abort();
                }
        if (conjb != 2)
        {
            GMatrixFunctions<FL>::copy(c, a);
            seq->iadd(c, tb, scale, conjb, cfactor);
            seq->simple_perform();
            for (MKL_INT ik = 0; ik < m; ik++)
                for (MKL_INT jk = 0; jk < n; jk++)
                    if (!(
                            abs(cfactor * a(ik, jk) + scale * b(ik, jk) - c(ik, jk)) <
                            thrd + thrd * abs(c(ik, jk))))
                    {
                        cout << abs(cfactor * a(ik, jk) + scale * b(ik, jk) - c(ik, jk)) << "," << thrd + thrd * abs(c(ik, jk)) << endl;
                        abort();
                    }
        }
        if (conjb)
            tb.deallocate();
        b.deallocate();
        c.deallocate();
        a.deallocate();
    }

    return 0;
}
