double foo  = 2.7172;

int suma(int n, int m) {
  return n + m;
}

int silnia(int n) {
  if (n <= 1)
    return 1;
  else
    return n*silnia(n-1);
}

