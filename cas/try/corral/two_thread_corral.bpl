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


procedure { :public } {:entrypoint } main()
   modifies x;
{
   x:= 0;
   async call foo1();
   async call foo2();
   assert x== 2;
}

