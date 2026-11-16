# EAL-GFX 0.1

A pure-C embedded graphics library targeting the Fire (EmbedFire) STM32F407
"Overlord" V2 board, an NT35510 800×480 RGB565 LCD, and a GT9xx capacitive
touch controller. The library uses no dynamic memory, keeps test code fully
separated from the library implementation, and never includes STM32 register
headers in its core.

## Project Layout

- `include/` — Stable, application-facing API. Contains no STM32 registers or
  LCD-model-specific code.
- `source/` — Display/touch abstraction, math and linear algebra, 2D
  primitives, and wireframe 3D rendering.
- `ports/stm32f407/` — The only adaptation layer that connects to the original
  `lcd_reg.*` / `touch_reg.*` hardware drivers.
- `examples/` — Demo applications: flat 2D shapes, an auto-rotating wireframe
  cube, and touch-drag rotation.
- `tests/` — Host (PC) unit tests for the library core; no STM32 hardware
  required.

The dependency direction is fixed:
`Example -> EAL-GFX API -> STM32 Port -> Hardware Driver`.
The library core never includes the examples, and never includes
`stm32f4xx.h` directly.

## API Example

```c
EALGFX_Display display;
EALGFX_Surface canvas;

EALGFX_DisplayAttach(&display, &EALGFX_STM32F407_DisplayDriver);
EALGFX_DisplayInit(&display);
EALGFX_SurfaceFromDisplay(&canvas, &display);

EALGFX_Line(&canvas, 20, 20, 200, 120, EALGFX_CYAN);
EALGFX_Circle(&canvas, 300, 180, 60, EALGFX_YELLOW);
```

The 3D module uses `EALGFX_Camera3D` to hold rotation angles, viewing
distance, and projection parameters:

```c
camera.rotation_y += 0.02f;
EALGFX_DrawWireMesh(&canvas, EALGFX_BuiltinCube(), &camera, EALGFX_WHITE);
```

## Module Overview

| Module | Header | Contents |
|---|---|---|
| Types | `ealgfx_types.h` | `EALGFX_Color` (RGB565), vectors, matrices, common color macros |
| Display | `ealgfx_display.h` | `EALGFX_DisplayDriver` contract, attach/init/clear |
| Touch | `ealgfx_touch.h` | `EALGFX_TouchDriver` contract, DOWN/MOVE/UP events, coordinate transforms |
| Math | `ealgfx_math.h` | Vector/matrix helpers for 3D |
| 2D | `ealgfx_gfx2d.h` | `EALGFX_Surface` render target, clipping, pixel/rect/line/circle/triangle |
| 3D | `ealgfx_gfx3d.h` | `EALGFX_Camera3D`, perspective projection, wireframe meshes, built-in cube |

A render target (`EALGFX_Surface`) may be an LCD, a strip buffer, a region
buffer, or a host-side image — anything that provides a `fill_rect` callback.

## Keil Integration

1. Add `include` and `ports/stm32f407` to the Include Paths.
2. Add `source/*.c` and `ports/stm32f407/ealgfx_port_stm32f407.c` to a
   Library group.
3. Add `examples/demo_app.c` to an Example group.
4. For the first bring-up, replace the existing `User/main.c` with
   `examples/stm32_main_example.c`.
5. Keep the original `lcd_reg.c`, `touch_reg.c`, CMSIS, and startup files
   from the board package.

For ARMCC5 projects with MicroLIB enabled, keep the existing settings. The
math module uses `sinf/cosf/sqrtf`, which the linker resolves from the
standard math runtime. A Q16.16 fixed-point math backend may be added in a
later version.

## Current Scope

- Included: driver abstraction, touch DOWN/MOVE/UP, coordinate transforms,
  vector/matrix math, basic 2D primitives, perspective projection, wireframe
  meshes, auto-rotation, touch-drag rotation.
- Not yet included: filled triangles, back-face culling, depth sorting,
  strip-based render targets, fonts, and UI widgets.
- The original board package remains the verified reference baseline for the
  hardware drivers and the advanced demo; nothing in it is overwritten.

## Running the Host Tests

```sh
sh tests/run_tests.sh
```

The script compiles the library core plus `tests/test_core.c` with
`-std=c99 -Wall -Wextra -Werror` and runs the test binary. Set `CC` to
override the compiler.