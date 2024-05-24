/* { dg-do compile } */
/* { dg-options "-fdump-tree-crc-details" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-O3" "-flto"} } */

// crc.ii, CRC16
#include <stdio.h>
typedef unsigned short u16;

void GenerateCRC32Table(u16 polynomial, u16 *table)
{
  for (u16 i = 0; i <= 255; i++) {
      u16 crc = i;
      for (u16 j = 0; j < 8; j++) { // latch's next bb is loop header
	  crc = (crc >> 1) ^ ((crc & 1) ? 0x2342 : 0);
	}
      table[i] = crc;
    }
}

int main ()
{
  u16 table [256];
  GenerateCRC32Table (0x4, table);
}


/* { dg-final { scan-tree-dump "calculates CRC!" "crc"} } */