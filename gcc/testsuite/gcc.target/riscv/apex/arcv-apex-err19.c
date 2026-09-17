/* { dg-do compile } */

int instname_XD (int, int);
#pragma intrinsic (instname_XD,"instname_XD", 256,"XD") /* { dg-error "pragma intrinsic: APEX opcode value '256' must be an integer constant in the range 0 to 0xff, inclusive" } */

int instname_XS (int, int);
#pragma intrinsic ( instname_XS,"instname_XS", 64,"XS") /* { dg-error "pragma intrinsic: APEX opcode value '64' must be an integer constant in the range 0 to 0x3f, inclusive" } */

int instname_XC (int, int);
#pragma intrinsic (instname_XC,"instname_XC", 32,"XC") /* { dg-error "pragma intrinsic: APEX opcode value '32' must be an integer constant in the range 0 to 0x1f, inclusive" } */

int instname_XI (int);
#pragma intrinsic (instname_XI,"instname_XI", 32,"XI") /* { dg-error "pragma intrinsic: APEX opcode value '32' must be an integer constant in the range 0 to 0x1f, inclusive" } */