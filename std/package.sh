name std
files std.c
version 0.0.3
description "rawer standard library"
setup()
{
    gcc -fPIC -shared -O3 -Wl,-rpath=/lib -o std.brl std.c
}