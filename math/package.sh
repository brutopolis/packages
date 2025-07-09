name math
version 0.1.0
description "buxu math library"
files math.c
setup()
{
    gcc -fPIC -shared -O3 -Wl,-rpath=/lib -o math.brl math.c -lm
}