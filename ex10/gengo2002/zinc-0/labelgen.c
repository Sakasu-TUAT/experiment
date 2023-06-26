int
getnewnum(void)
{
  static int num = 0;

  return ++num;
}
