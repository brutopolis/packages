name list
version 0.1.8
description "buxu list library, basically a bruter wrapper"
files list.c
setup()
{
    gcc -fPIC -shared -O3 -Wl,-rpath=/lib -o list.brl list.c
}