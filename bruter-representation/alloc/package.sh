name alloc
version 0.0.9
description "buxu standard alloc library"
files alloc.c
setup() { 
    gcc -fPIC -O3 -shared -o alloc.brl alloc.c
}