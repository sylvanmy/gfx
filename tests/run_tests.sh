#!/bin/sh
set -eu
cd "$(dirname "$0")/.."
CC="${CC:-cc}"
OUT="$(mktemp -d)"
trap 'rm -rf "$OUT"' EXIT
"$CC" -std=c99 -Wall -Wextra -Werror -Iinclude \
  source/ealgfx_display.c source/ealgfx_touch.c source/ealgfx_math.c \
  source/ealgfx_gfx2d.c source/ealgfx_gfx3d.c tests/test_core.c -lm -o "$OUT/test_core"
"$OUT/test_core"
