// PR c++/124957
// { dg-do compile { target c++17 } }
// { dg-additional-options "-fmodules -fno-module-lazy" }

module mod;
import :partition;

// OK, no bogus abi_tag mismatch error for the imported x's
