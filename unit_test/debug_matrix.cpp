
#include "block2_core.hpp"

using namespace block2;

int main(int argc, char *argv[]) {
    size_t isize = 1LL << 24;
    size_t dsize = 1LL << 28;
    using FL = double;
    Random::rand_seed(0);
    unsigned int sd = (unsigned)Random::rand_int(1, 1 << 30);
    cout << "seed = " << sd << endl;
    Random::rand_seed(sd);
    frame_<FL>() = make_shared<DataFrame<FL>>(isize, dsize, "nodex");
    return 0;
}
