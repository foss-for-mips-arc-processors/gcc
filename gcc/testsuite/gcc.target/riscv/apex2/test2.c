/* { dg-do run } */

extern int _f(int,int);
#pragma intrinsic(_f,"apex_xd_add",8)

int main() {
   int s = _f(1,1)-1;
   return s;
}
