/* { dg-do compile } */
/* { dg-options "-fdump-tree-crc-details" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-O3" "-flto"} } */

#include <stdint.h>
//File - as_format
uint32_t crc32r(const uint8_t *data, uint32_t size)
{

    uint32_t crc = 0xffffffff;
    for(uint32_t i=0; i != size; i++) {
        crc = crc ^ data[i];
        for(int j=0; j<8; j++)
            if(crc & 1)
                crc = (crc >> 1) ^ 0xedb88320;
            else
                crc = crc >> 1;
    }
    return ~crc;
}

/* { dg-final { scan-tree-dump "calculates CRC!" "crc"} } */