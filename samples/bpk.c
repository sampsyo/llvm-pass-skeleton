void bpk(float * restrict a, float * restrict b, float k, int n) {
  for (int i = 0; i < n; i++)
    a[i] = b[i] + k;
}
