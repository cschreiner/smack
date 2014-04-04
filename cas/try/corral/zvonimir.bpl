var int: x;

procedure foo1();
   modifies x;
{
   x:= 1;
}

procedure foo2();
   modifies x;
{
   x:= 2;
}


procedure { :public } main();
   modifies x;
{
   x:= 0;
   async foo1();
   async foo2();
   assert x== 2;
}

