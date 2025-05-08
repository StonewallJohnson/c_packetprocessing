#include <nfp.h>
#include <nfp/mem_atomic.h>
#include <nfp/mem_bulk.h>
typedef __packed struct my my_t;
__packed struct my{
    __mem40 my_t *size_8_field;
    __mem40 my_t *size_8_field2;
    uint32_t size_4_field;
    uint8_t size_1_field;
};

typedef __packed struct my2 my2_t;
__packed struct my2{
    __mem40 my2_t *size_8_field;
    __mem40 my2_t *size_8_field2;
    uint32_t size_4_field;
    uint8_t size_1_field;
    uint8_t size_1_field2;
};
/* DEBUG MACROS */

__volatile __export __emem uint32_t debug[8192*64];
__volatile __export __emem uint32_t debug_idx;
#define DEBUG(_a, _b, _c, _d) do { \
    __xrw uint32_t _idx_val = 4; \
    __xwrite uint32_t _dvals[4]; \
    mem_test_add(&_idx_val, \
            (__mem40 void *)&debug_idx, sizeof(_idx_val)); \
    _dvals[0] = _a; \
    _dvals[1] = _b; \
    _dvals[2] = _c; \
    _dvals[3] = _d; \
    mem_write_atomic(_dvals, (__mem40 void *)\
                    (debug + (_idx_val % (1024 * 64))), sizeof(_dvals)); \
    } while(0)


int main(void)
{
        DEBUG(0xdeadbeef, sizeof(my2_t), sizeof(my_t), 0xdeadbeef);
}