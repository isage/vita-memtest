#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/clib.h>
#include <psp2/kernel/dmac.h>
#include <psp2/kernel/sysmem/memblock.h>

void memcpy_speed(unsigned long buf_size, unsigned long iters){
    uint64_t start, end;
    unsigned char * pbuff_1;
    unsigned char * pbuff_2;

    SceUID buf1_uid = sceKernelAllocMemBlock("buf1", SCE_KERNEL_MEMBLOCK_TYPE_USER_RW, buf_size, NULL);
    SceUID buf2_uid = sceKernelAllocMemBlock("buf2", SCE_KERNEL_MEMBLOCK_TYPE_USER_NC_RW, buf_size, NULL);

    sceKernelGetMemBlockBase(buf1_uid, &pbuff_1);
    sceKernelGetMemBlockBase(buf2_uid, &pbuff_2);


//    pbuff_1 = malloc(buf_size);
//    pbuff_2 = malloc(buf_size);

    start = sceKernelGetProcessTimeWide();

    for(int i = 0; i < iters; ++i){
        memcpy(pbuff_2, pbuff_1, buf_size);
    }

    end = sceKernelGetProcessTimeWide();
    printf("LIBC: Size: %lu, %5.3f MB/s\n", buf_size, ((buf_size*iters)/(1.024*1.024)) / ((end - start)));


    start = sceKernelGetProcessTimeWide();
    for(int i = 0; i < iters; ++i){
        memcpy_neon(pbuff_2, pbuff_1, buf_size);
    }
    end = sceKernelGetProcessTimeWide();
    printf("NEON: Size: %lu, %5.3f MB/s\n", buf_size, ((buf_size*iters)/(1.024*1.024)) / ((end - start)));


    start = sceKernelGetProcessTimeWide();
    for(int i = 0; i < iters; ++i){
        sceClibMemcpy(pbuff_2, pbuff_1, buf_size);
    }
    end = sceKernelGetProcessTimeWide();
    printf("CLIB: Size: %lu, %5.3f MB/s\n", buf_size, ((buf_size*iters)/(1.024*1.024)) / ((end - start)));

    start = sceKernelGetProcessTimeWide();
    for(int i = 0; i < iters; ++i){
        sceDmacMemcpy(pbuff_2, pbuff_1, buf_size);
    }
    end = sceKernelGetProcessTimeWide();
    printf("DMAC: Size: %lu, %5.3f MB/s\n", buf_size, ((buf_size*iters)/(1.024*1.024)) / ((end - start)));

    printf("\n");
//    free(pbuff_1);
//    free(pbuff_2);
    sceKernelFreeMemBlock(buf1_uid);
    sceKernelFreeMemBlock(buf2_uid);
}

int main(void)
{
    memcpy_speed(4096, 1000);
    memcpy_speed(4096*2, 1000);
    memcpy_speed(4096*4, 1000);
    memcpy_speed(4096*8, 1000);
    memcpy_speed(4096*16, 1000);
    memcpy_speed(4096*256, 1000);
    memcpy_speed(4096*1024, 1000);
    memcpy_speed(4096*1024*2, 1000);
    memcpy_speed(4096*1024*4, 1000);

/*
    memcpy_speed(12, 1000);
    memcpy_speed(33, 1000);
    memcpy_speed(66, 1000);
    memcpy_speed(99, 1000);
    memcpy_speed(127, 1000);
    memcpy_speed(129, 1000);
    memcpy_speed(999, 1000);
    memcpy_speed(9999, 1000);
    memcpy_speed(99999, 1000);

    memcpy_speed(32, 1000);
    memcpy_speed(64, 1000);
    memcpy_speed(128, 1000);
    memcpy_speed(256, 1000);
    memcpy_speed(512, 1000);
    memcpy_speed(1024, 1000);

    memcpy_speed(12*1024, 1000);
    memcpy_speed(33*1024, 1000);
    memcpy_speed(66*1024, 1000);
    memcpy_speed(99*1024, 1000);
    memcpy_speed(999*1024, 1000);

    memcpy_speed(32*1024, 1000);
    memcpy_speed(64*1024, 1000);
    memcpy_speed(128*1024, 1000);
    memcpy_speed(256*1024, 1000);
    memcpy_speed(512*1024, 1000);
    memcpy_speed(1024*1024, 1000);*/
}