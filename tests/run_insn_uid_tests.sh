#!/bin/bash
# Test RTL instruction UID debug output from a built gcc_insn_num toolchain.

set -euo pipefail

SC="${SC:-/home/loeka/SC}"
TOOLCHAIN="$SC/gcc_insn_num-build-rhx/install"
GCC="$TOOLCHAIN/bin/riscv32-unknown-elf-gcc"
OBJDUMP="$TOOLCHAIN/bin/riscv32-unknown-elf-objdump"
READELF="$TOOLCHAIN/bin/riscv32-unknown-elf-readelf"
TESTDIR="$SC/gcc_insn_num/tests"
WORKDIR="${TMPDIR:-/tmp}/gcc-insn-uid-test-$$"
PASS=0
FAIL=0

die() {
  echo "ERROR: $*" >&2
  exit 1
}

check() {
  local name="$1"
  shift
  if "$@"; then
    echo "PASS: $name"
    PASS=$((PASS + 1))
  else
    echo "FAIL: $name"
    FAIL=$((FAIL + 1))
  fi
}

[ -x "$GCC" ] || die "Compiler not found at $GCC (run build_gcc.sh first)"

mkdir -p "$WORKDIR"
trap 'rm -rf "$WORKDIR"' EXIT

compile_test() {
  local src="$1"
  local base
  base="$(basename "$src" .c)"
  "$GCC" -g -O0 -c "$src" -o "$WORKDIR/$base.o"
  "$GCC" -g -O0 -S "$src" -o "$WORKDIR/$base.s"
  echo "$WORKDIR/$base"
}

echo "=== insn_uid debug tests ==="

for src in "$TESTDIR"/insn_uid_*.c; do
  [ -f "$src" ] || continue
  base="$(compile_test "$src")"

  check "$(basename "$src"): assembly contains insn labels" \
    grep -q 'Linsn' "$base.s"

  check "$(basename "$src"): object has rtl_insn_map section" \
    sh -c '"$0" -W -S "$1" | grep -q gnu.gcc.rtl_insn_map' "$READELF" "$base.o"

  check "$(basename "$src"): object disassembly references insn labels" \
    sh -c '"$0" -dr "$1" | grep -q Linsn' "$OBJDUMP" "$base.o"
done

# Verify map section has non-zero size for the control-flow test.
cf_obj="$WORKDIR/insn_uid_control_flow.o"
if [ -f "$cf_obj" ]; then
  map_size="$("$READELF" -W -S "$cf_obj" | awk '/gnu.gcc.rtl_insn_map/ {print $6; exit}')"
  check "control flow map section is non-empty" \
    test -n "$map_size" -a "$map_size" != "000000"
fi

# Without -g, labels should not be emitted.
"$GCC" -O0 -c "$TESTDIR/insn_uid_simple.c" -o "$WORKDIR/no_debug.o"
check "no debug: rtl_insn_map section absent" \
  sh -c '! "$0" -W -S "$1" | grep -q gnu.gcc.rtl_insn_map' "$READELF" "$WORKDIR/no_debug.o"

echo ""
echo "Results: $PASS passed, $FAIL failed"
[ "$FAIL" -eq 0 ]
