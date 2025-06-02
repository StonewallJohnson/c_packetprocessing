#include <nfp.h>
#include <stdint.h>
#include <nfp_cluster_target_ring.h>

//ring 0
__export __global __addr40 __ctm_n(3) __align(128 * sizeof(uint32_t)) uint32_t ctm_ring_head[128];

int main(void)
{
    SIGNAL sig;
    __xwrite uint32_t wxfer = 0xdeadbeef;
    __xread uint32_t rxfer;
    __gpr uint32_t val;
    if (__ctx() == 0){
        cmd_cluster_target_ring_init(0, ctm_ring_head, CTM_RING_SIZE_128, CTM_RING_FULL | CTM_RING_EMPTY, ctx_swap, &sig);

        cmd_cluster_target_ring_put(&xfer, 3, 0, 1, ctx_swap, &sig);
        xfer = 0xc0debad0;
        cmd_cluster_target_ring_put(&xfer, 3, 0, 1, ctx_swap, &sig);
    }
    

    cmd_cluster_target_ring_get(&rxfer, 3, 0, 1, ctx_swap, &sig);
    val = rxfer;
    if(val == 0){
        __asm local_csr_wr[local_csr_mailbox0, 0xff];    
    }
    else{
        __asm local_csr_wr[local_csr_mailbox1, val];
    }

    cmd_cluster_target_ring_get(&rxfer, 3, 0, 1, ctx_swap, &sig);
    val = rxfer;
    if(val == 0){
        __asm local_csr_wr[local_csr_mailbox0, 0xff];    
    }
    else{
        __asm local_csr_wr[local_csr_mailbox2, val];
    }

    return 0;

}