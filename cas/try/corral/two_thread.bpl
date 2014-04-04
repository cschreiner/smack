var x: int;

procedure foo1()
   modifies x;
{
   x:= 1;
}

procedure foo2()
   modifies x;
{
   x:= 2;
}


procedure { :public } main()
   modifies x;
{
   x:= 0;
   call /*async*/ foo1();
   call /*async*/ foo2();
   assert x== 2;
}

