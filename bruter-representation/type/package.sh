name type
version 0.0.2
description "buxu standard type library"
files type.c
setup()
{
    gcc -fPIC -shared -O3 -Wl,-rpath=/lib -o type.brl type.c
}