name std
files std.c
version 0.2.1
description "buxu standard library"
setup()
{
    gcc -fPIC -shared -O3 -Wl,-rpath=/lib -o std.brl std.c
}