int x;

void foo1()
   modifies x
{
   x:= 1;
}

void foo2()
   modifies x
{
   x:= 2;
}


void main { entrypoint } main()
   modifies x
{
   x:= 0;
   async foo1();
   async foo2();
   assert x== 2;
}

