name os
version 0.1.2
description "buxu operating system"
files os.c
setup()
{
    gcc -fPIC -shared -O3 -Wl,-rpath=/lib -o os.brl os.c
}