/* { dg-require-effective-target arm_neon_hw } */
/* { dg-options "-O2 -mfpu=neon -mfloat-abi=softfp -ftree-vectorize" } */
/* { dg-final { scan-assembler "vmla\\.f32" } } */

/* Verify that VMLA is used.  */
void f1(int n, float a, float x[], float y[]) {
  int i;
  for (i = 0; i < n; ++i)
    y[i] = a * x[i] + y[i];
}
