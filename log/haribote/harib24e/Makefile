# command alias
MAKE = make -r
PRE_MAKE = mkdir -p target/bin && mkdir -p target/kernel && mkdir -p target/obj/kernel/system_call && mkdir -p target/obj/lib && mkdir -p target/obj/app && mkdir -p target/app
DEL = rm -rf
CC = i386-elf-gcc
CFLAGS = -m32 -fno-builtin


# paths
TARGET_PATH = ./target
OBJ_PATH = ./target/obj
BIN_PATH = ./target/bin


# files
OBJS_boot = \
	$(OBJ_PATH)/kernel/boot.o \
	$(OBJ_PATH)/kernel/naskfunc.o \
	$(OBJ_PATH)/kernel/graphic.o \
	$(OBJ_PATH)/kernel/dsctbl.o \
	$(OBJ_PATH)/kernel/int.o \
	$(OBJ_PATH)/kernel/queue.o \
	$(OBJ_PATH)/kernel/keyboard.o \
	$(OBJ_PATH)/kernel/mouse.o \
	$(OBJ_PATH)/kernel/memory.o \
	$(OBJ_PATH)/kernel/sheet.o \
	$(OBJ_PATH)/kernel/timer.o \
	$(OBJ_PATH)/kernel/mtask.o \
	$(OBJ_PATH)/kernel/window.o \
	$(OBJ_PATH)/kernel/console.o \
	$(OBJ_PATH)/kernel/file.o \
	$(OBJ_PATH)/lib/sprintf.o \
	$(OBJ_PATH)/lib/strcmp.o \
	$(OBJ_PATH)/lib/hankaku.o

SYS_CALL_OBJS = \
	$(OBJ_PATH)/kernel/system_call/api001.o \
	$(OBJ_PATH)/kernel/system_call/api002.o \
	$(OBJ_PATH)/kernel/system_call/api003.o \
	$(OBJ_PATH)/kernel/system_call/api004.o \
	$(OBJ_PATH)/kernel/system_call/api005.o \
	$(OBJ_PATH)/kernel/system_call/api006.o \
	$(OBJ_PATH)/kernel/system_call/api007.o \
	$(OBJ_PATH)/kernel/system_call/api008.o \
	$(OBJ_PATH)/kernel/system_call/api009.o \
	$(OBJ_PATH)/kernel/system_call/api010.o \
	$(OBJ_PATH)/kernel/system_call/api011.o \
	$(OBJ_PATH)/kernel/system_call/api012.o \
	$(OBJ_PATH)/kernel/system_call/api013.o \
	$(OBJ_PATH)/kernel/system_call/api014.o \
	$(OBJ_PATH)/kernel/system_call/api015.o \
	$(OBJ_PATH)/kernel/system_call/api016.o \
	$(OBJ_PATH)/kernel/system_call/api017.o \
	$(OBJ_PATH)/kernel/system_call/api018.o \
	$(OBJ_PATH)/kernel/system_call/api019.o \
	$(OBJ_PATH)/kernel/system_call/api020.o

APPS = \
		$(TARGET_PATH)/app/a.hrb \
		$(TARGET_PATH)/app/hello.hrb \
		$(TARGET_PATH)/app/hello2.hrb \
		$(TARGET_PATH)/app/hello3.hrb \
		$(TARGET_PATH)/app/hello4.hrb \
		$(TARGET_PATH)/app/hello5.hrb \
		$(TARGET_PATH)/app/walk.hrb \
		$(TARGET_PATH)/app/win.hrb \
		$(TARGET_PATH)/app/win2.hrb \
		$(TARGET_PATH)/app/win3.hrb \
		$(TARGET_PATH)/app/star1.hrb \
		$(TARGET_PATH)/app/star2.hrb \
		$(TARGET_PATH)/app/stars.hrb \
		$(TARGET_PATH)/app/lines.hrb \
		$(TARGET_PATH)/app/noodle.hrb \
		$(TARGET_PATH)/app/beepdown.hrb \
		$(TARGET_PATH)/app/color.hrb \
		$(TARGET_PATH)/app/color2.hrb \
		$(TARGET_PATH)/app/crack7.hrb


# Commands
default : 
	$(MAKE) img

img :
	$(PRE_MAKE)
	$(MAKE) $(TARGET_PATH)/haribote.img

run :
	$(PRE_MAKE)
	$(MAKE) img
	qemu-system-i386 -drive file=$(TARGET_PATH)/haribote.img,format=raw,if=floppy -boot a -m 1G

src_only :
	-$(DEL) $(TARGET_PATH)/*



# os img
target/haribote.img : $(TARGET_PATH)/bin/ipl10.bin $(TARGET_PATH)/haribote.sys $(APPS) Makefile
	mformat -f 1440 -C -B $(TARGET_PATH)/bin/ipl10.bin -i $@ ::
	mcopy -i $(TARGET_PATH)/haribote.img $(TARGET_PATH)/haribote.sys $(APPS) static/main.c ::


# compile libs
target/bin/hankaku_txt_compiler : src/lib/hankaku_txt_compiler.c
	gcc $< -o $@
src/lib/hankaku.c : static/hankaku.txt $(BIN_PATH)/hankaku_txt_compiler
	./$(BIN_PATH)/hankaku_txt_compiler
$(OBJ_PATH)/lib/%.o : src/lib/%.c
	$(CC) $(CFLAGS) -c src/lib/$*.c -o $(OBJ_PATH)/lib/$*.o



# Kernel Build
target/bin/ipl10.bin : src/kernel/asm/ipl10.nasm
	nasm $< -o $@ -l $(TARGET_PATH)/kernel/ipl10.lst

target/bin/asmhead.bin : src/kernel/asm/asmhead.nasm
	nasm $< -o $@ -l $(TARGET_PATH)/kernel/asmhead.lst

$(OBJ_PATH)/kernel/naskfunc.o : src/kernel/asm/naskfunc.nasm 
	nasm -g -f elf $< -o $@ -l $(TARGET_PATH)/kernel/naskfunc.lst

target/boot.hrb : $(OBJS_boot) hrb.ld
	$(CC) $(CFLAGS) -march=i486 -nostdlib -T hrb.ld -Xlinker -Map=$(TARGET_PATH)/boot.map -g $(OBJS_boot) -o $@

target/haribote.sys : $(TARGET_PATH)/bin/asmhead.bin $(TARGET_PATH)/boot.hrb Makefile
	cat $(TARGET_PATH)/bin/asmhead.bin $(TARGET_PATH)/boot.hrb > $(TARGET_PATH)/haribote.sys

$(OBJ_PATH)/kernel/%.o : src/kernel/%.c
	$(CC) $(CFLAGS) -c src/kernel/$*.c -o $(OBJ_PATH)/kernel/$*.o

$(OBJ_PATH)/kernel/system_call/%.o : src/kernel/asm/system_call/%.nasm	
	nasm -g -f elf src/kernel/asm/system_call/$*.nasm -o $(OBJ_PATH)/kernel/system_call/$*.o -l $(TARGET_PATH)/kernel/$*.lst



#  Application Build
$(TARGET_PATH)/app/hello.hrb : src/app/hello.nasm
	nasm $< -o $@ -l hello.lst

$(TARGET_PATH)/app/hello2.hrb : src/app/hello2.nasm
	nasm $< -o $@ -l hello2.lst

$(TARGET_PATH)/app/a.hrb : $(OBJ_PATH)/app/a.o $(SYS_CALL_OBJS) src/app/app.ld 
	$(CC) $(CFLAGS) -march=i486 -nostdlib -T src/app/app.ld -g $(OBJ_PATH)/app/a.o $(SYS_CALL_OBJS) -o $@

$(TARGET_PATH)/app/hello3.hrb : $(OBJ_PATH)/app/hello3.o $(SYS_CALL_OBJS) src/app/app.ld 
	$(CC) $(CFLAGS) -march=i486 -nostdlib -T src/app/app.ld -g $(OBJ_PATH)/app/hello3.o $(SYS_CALL_OBJS) -o $@

$(TARGET_PATH)/app/hello4.hrb : $(OBJ_PATH)/app/hello4.o $(SYS_CALL_OBJS) src/app/app.ld 
	$(CC) $(CFLAGS) -march=i486 -nostdlib -T src/app/app.ld -g $(OBJ_PATH)/app/hello4.o $(SYS_CALL_OBJS) -o $@

$(TARGET_PATH)/app/hello5.hrb : $(OBJ_PATH)/app/hello5.o src/app/app.ld
	$(CC) $(CFLAGS) -march=i486 -nostdlib -T src/app/app.ld -g $(OBJ_PATH)/app/hello5.o -o $@

$(TARGET_PATH)/app/win.hrb : $(OBJ_PATH)/app/win.o $(SYS_CALL_OBJS) src/app/app.ld
	$(CC) $(CFLAGS) -march=i486 -nostdlib -T src/app/app.ld -g $(OBJ_PATH)/app/win.o $(SYS_CALL_OBJS) -o $@

$(TARGET_PATH)/app/win2.hrb : $(OBJ_PATH)/app/win2.o $(SYS_CALL_OBJS) src/app/app.ld
	$(CC) $(CFLAGS) -march=i486 -nostdlib -T src/app/app.ld -g $(OBJ_PATH)/app/win2.o $(SYS_CALL_OBJS) -o $@

$(TARGET_PATH)/app/win3.hrb : $(OBJ_PATH)/app/win3.o $(SYS_CALL_OBJS) src/app/app.ld
	$(CC) $(CFLAGS) -march=i486 -nostdlib -T src/app/app.ld -Os -fdata-sections -ffunction-sections -g $(OBJ_PATH)/app/win3.o $(SYS_CALL_OBJS) -o $@ -Wl,--gc-sections

$(TARGET_PATH)/app/star1.hrb : $(OBJ_PATH)/app/star1.o $(SYS_CALL_OBJS) src/app/app.ld
	$(CC) $(CFLAGS) -march=i486 -nostdlib -T src/app/app.ld -g $(OBJ_PATH)/app/star1.o $(SYS_CALL_OBJS) -o $@

$(TARGET_PATH)/app/star2.hrb : $(OBJ_PATH)/app/star2.o $(SYS_CALL_OBJS) src/app/app.ld
	$(CC) $(CFLAGS) -march=i486 -nostdlib -T src/app/app.ld -g $(OBJ_PATH)/app/star2.o $(SYS_CALL_OBJS) -o $@

$(TARGET_PATH)/app/stars.hrb : $(OBJ_PATH)/app/stars.o $(SYS_CALL_OBJS) src/app/app.ld
	$(CC) $(CFLAGS) -march=i486 -nostdlib -T src/app/app.ld -g $(OBJ_PATH)/app/stars.o $(SYS_CALL_OBJS) -o $@

$(TARGET_PATH)/app/lines.hrb : $(OBJ_PATH)/app/lines.o $(SYS_CALL_OBJS) src/app/app.ld
	$(CC) $(CFLAGS) -march=i486 -nostdlib -T src/app/app.ld -g $(OBJ_PATH)/app/lines.o $(SYS_CALL_OBJS) -o $@

$(TARGET_PATH)/app/walk.hrb : $(OBJ_PATH)/app/walk.o $(SYS_CALL_OBJS) src/app/app.ld
	$(CC) $(CFLAGS) -march=i486 -nostdlib -T src/app/app.ld -g $(OBJ_PATH)/app/walk.o $(SYS_CALL_OBJS) -o $@

$(TARGET_PATH)/app/noodle.hrb : $(OBJ_PATH)/app/noodle.o $(SYS_CALL_OBJS) $(OBJ_PATH)/lib/sprintf.o src/app/app2.ld
	$(CC) $(CFLAGS) -march=i486 -nostdlib -T src/app/app2.ld -g $(OBJ_PATH)/app/noodle.o $(SYS_CALL_OBJS) $(OBJ_PATH)/lib/sprintf.o -o $@

$(TARGET_PATH)/app/beepdown.hrb : $(OBJ_PATH)/app/beepdown.o $(SYS_CALL_OBJS) src/app/app.ld
	$(CC) $(CFLAGS) -march=i486 -nostdlib -T src/app/app.ld -g $(OBJ_PATH)/app/beepdown.o $(SYS_CALL_OBJS) -o $@

$(TARGET_PATH)/app/color.hrb : $(OBJ_PATH)/app/color.o $(SYS_CALL_OBJS) src/app/app.ld
	$(CC) $(CFLAGS) -march=i486 -nostdlib -T src/app/app.ld -g $(OBJ_PATH)/app/color.o $(SYS_CALL_OBJS) -o $@

$(TARGET_PATH)/app/color2.hrb : $(OBJ_PATH)/app/color2.o $(SYS_CALL_OBJS) src/app/app.ld
	$(CC) $(CFLAGS) -march=i486 -nostdlib -T src/app/app2.ld -g $(OBJ_PATH)/app/color2.o $(SYS_CALL_OBJS) -o $@

$(TARGET_PATH)/app/crack7.hrb : $(OBJ_PATH)/app/crack7.o src/app/app.ld
	$(CC) $(CFLAGS) -march=i486 -nostdlib -T src/app/app.ld -g $(OBJ_PATH)/app/crack7.o -o $@

$(OBJ_PATH)/app/%.o : src/app/%.c
	$(CC) $(CFLAGS) -c src/app/$*.c -o $(OBJ_PATH)/app/$*.o

$(OBJ_PATH)/app/%.o : src/app/%.nasm
	nasm -g -f elf src/app/$*.nasm -o $(OBJ_PATH)/app/$*.o -l $(TARGET_PATH)/app/$*.lst