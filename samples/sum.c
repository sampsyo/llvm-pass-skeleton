float sum(float *a, int n) {
  float s = 0;
  for (int i = 0; i < n; i++)
    s += a[i];
  return s;
}
