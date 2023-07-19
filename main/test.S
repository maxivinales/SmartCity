// Use defines to reference registers, los numeros mas bajos de a son las entradas
#define p_x a2
#define p_y a3
#define p_z a4
#define x f1
#define y f2
#define z f3


 
  .text                   # Code section
  .align                  # Align the byte boundaries - needed?
  .global test_asm         # Make the symbol available to C/C++ for call
  .type   test_asm,@function
test_asm:
  entry a1,    32           # Create a window for execution
  lsi x, p_x, 0
  lsi y, p_y, 0
  lsi z, p_z, 0

  msub.s x, y, x

  ssi x, p_x, 0
  retw          