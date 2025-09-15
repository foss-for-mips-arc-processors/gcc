/* { dg-do run } */

extern int _f(int,int);
#pragma intrinsic(_f,"apex_xd_sub",7)

int main() {
   return _f(8,8);
}
