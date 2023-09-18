rm a.asm a.o a.out -rf
../bin/jaspl std_test.jaspl > a.asm;
nasm -f elf a.asm -o a.o; ld a.o -m elf_i386
#rm a.asm a.o -rf
