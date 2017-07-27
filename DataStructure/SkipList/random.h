#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <stdint.h>


class Random {
    private:
        uint32_t _seed;

    public:
        explicit Random(uint32_t s) : _seed(s & 0x7fffffffu) {
            if (_seed == 0 || _seed == 2147483645L) {
                _seed = 1;
            }
        }

        uint32_t next() {
            static const uint32_t M = 2147483647L; // 2^31 - 1
            static const uint64_t A = 16807; // bits 14,8,7, 5,2,1,0

            uint64_t product = _seed * A;
            _seed = static_cast<uint32_t>((product >> 31) + (product & M));

            if (_seed > M) {
                _seed -= M;
            }

            return _seed;
        }

        uint32_t uniform(int n) {
            return (next() % n);
        }
};

#endif
