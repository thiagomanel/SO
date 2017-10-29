# Process

Code here is based on OSTEP book and xv6 manuals

The assembly code works for macOS (from https://lord.io/blog/2014/assembly-on-osx/)

To assemble your code, run:
# Generate object file from assembly:
nasm -f macho64 -o hello_world.o hello_world.asm

# Link object file:
ld hello_world.o -o hello_world

# Run executable:
./hello_world
