
#include "block2_core.hpp"
#include <gtest/gtest.h>
#include <iostream>

using namespace block2;

class TestFFT : public ::testing::Test {
  protected:
    static const int n_tests = 1000;
    void SetUp() override { Random::rand_seed(0); }
    void TearDown() override {}
};

TEST_F(TestFFT, TestFFT) {
    for (int i = 0; i < n_tests; i++) {
        int n;
        if (i < n_tests * 50 / 100)
            n = Random::rand_int(0, 12);
        else if (i < n_tests * 99 / 100)
            n = Random::rand_int(1, 1000);
        else
            n = Random::rand_int(1, 5000);
        FFT fft;
        DFT dft;
        vector<complex<double>> arr(n), arx;
        Random::fill<double>((double *)arr.data(), n * 2);
        arx = arr;
        fft.fft(arx.data(), n, true);
        dft.fft(arr.data(), n, true);
        for (int j = 0; j < n; j++)
            ASSERT_TRUE(abs(arr[j] - arx[j]) < 1E-12 + 1E-5 * abs(arx[j]));
        fft.fft(arx.data(), n, false);
        dft.fft(arr.data(), n, false);
        for (int j = 0; j < n; j++)
            ASSERT_TRUE(abs(arr[j] - arx[j]) < 1E-12 + 1E-5 * abs(arx[j]));
    }
}
