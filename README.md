# kit-OS-2023
Kit & template dasar untuk IF2230 - Sistem Operasi 2023

Spesifikasi dan guidebook dapat diakses pada link Google Docs yang dikirim pada milis atau folder [docs](docs/)

Kit list
1. https://github.com/Sister20/kit-OS-2023
2. https://github.com/Sister20/kit-OS-milestone-2-2023
3. https://github.com/Sister20/kit-OS-milestone-3-2023

Disusun oleh tim asisten laboratorium sistem terdistribusi '20

Disclaimer : Seluruh material yang digunakan pada spesifikasi dan kit digunakan untuk kepentingan edukasional dan memenuhi mata kuliah IF2230 - Sistem Operasi tahun 2023

command list

`gcc -ffreestanding -fshort-wchar -g -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -m32 -c -Isrc src/kernel.c -o bin/kernel.o`

`nasm -f elf32 -g -F dwarf src/kernel_loader.s -o bin/kernel_loader.o`

`ld -T src/linker.ld -melf_i386 bin/kernel.o bin/kernel_loader.o -o bin/kernel`

```
genisoimage -R	\
	-b boot/grub/grub1	\
	-no-emul-boot		\
	-boot-load-size 4	\
	-A os			\
	-input-charset utf8	\
	-quiet			\
	-boot-info-table	\
	-o OS2023.iso		\
	iso
```

`qemu-system-i386 -s -cdrom OS2023.iso`