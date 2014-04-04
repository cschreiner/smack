var x: int;

procedure foo1();
   modifies x;

implementation foo1()
{
   x:= 1;
}

procedure foo2();
   modifies x;

implementation foo2()
{
   x:= 2;
}


procedure { :public } main();
   modifies x;
implementation main()
{
   x:= 0;
   call /*async*/ foo1();
   call /*async*/ foo2();
   assert x== 2;
}

