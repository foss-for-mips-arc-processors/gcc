// PR c++/125115
// { dg-do compile { target c++17 } }
// { dg-additional-options "-fmodules -fno-module-lazy" }

#include "auto-9.h"
import "auto-9_a.H";
