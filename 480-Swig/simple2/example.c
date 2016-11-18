int  silnia(int n) {
  if (n <= 1)
    return 1;
  else
    return n*silnia(n-1);
}
