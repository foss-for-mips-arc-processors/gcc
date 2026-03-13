/* { dg-do compile } */
/* { dg-options "-march=rv64gc_ziccamoa_za64rs_zicbom_zicbop_zicboz_sstc_smdbltrp_ssdbltrp_smrnmi_smcntrpmf_sscofpmf_smcsrind_sscsrind -mabi=lp64d" } */

/* Test for additional supervisor extensions required for downstream GCC 15:
   - Ziccamoa: Main memory supports atomics
   - Za64rs: Reservation set size is not greater than 64 bytes
   - Zicbom: Cache block management
   - Zicbop: Cache block prefetching
   - Zicboz: Cache block zeroing
   - Sstc: Supervisor-mode timers
   - Smdbltrp, Ssdbltrp: Double trap
   - Smrnmi: Resumable NMI
   - Smcntrpmf, Sscofpmf: Privilege-mode filtering of counters
   - Smcsrind, Sscsrind: Indirect CSR access
*/

void foo(){}

/* { dg-final { scan-assembler ".attribute arch, \"rv64i2p1_m2p0_a2p1_f2p2_d2p2_c2p0" } } */
/* { dg-final { scan-assembler "_zicbom1p0_zicbop1p0_zicboz1p0_ziccamoa1p0_zicsr2p0" } } */
/* { dg-final { scan-assembler "_zifencei2p0_zmmul1p0_za64rs1p0_zaamo1p0_zalrsc1p0" } } */
/* { dg-final { scan-assembler "_zca1p0_zcd1p0_smcntrpmf1p0_smcsrind1p0_smdbltrp1p0" } } */
/* { dg-final { scan-assembler "_smrnmi1p0_sscofpmf1p0_sscsrind1p0_ssdbltrp1p0_sstc1p0" } } */
