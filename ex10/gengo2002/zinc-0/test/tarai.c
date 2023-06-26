main()
{
  tarai(14, 7, 0);
}

tarai(x, y, z)
int x;
int y;
int z;
{
  if (x > y) {
    return tarai(tarai(x - 1, y, z), tarai(y - 1, z, x), tarai(z - 1, x, y));
  } else {
    return y;
  }
}
