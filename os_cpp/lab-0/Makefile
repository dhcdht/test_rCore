MODE        := debug
KERNEL_FILE := ./build/os.out
BIN_FILE    := ./build/kernel.bin

OBJDUMP     := riscv64-unknown-elf-objdump
OBJCOPY     := riscv64-unknown-elf-objcopy

.PHONY: doc kernel build clean qemu run

# 默认 build 为输出二进制文件
build: $(BIN_FILE) 

# 编译 kernel
kernel:
	@riscv64-unknown-elf-gcc -c main.cpp -o ./build/main.o -mcmodel=medany
	@riscv64-unknown-elf-gcc -c sbi.cpp -o ./build/sbi.o -mcmodel=medany
	@riscv64-unknown-elf-gcc -c console.cpp -o ./build/console.o -mcmodel=medany
	@riscv64-unknown-elf-ld -Tlinker.ld ./build/*.o -o ${KERNEL_FILE}

# 生成 kernel 的二进制文件
$(BIN_FILE): kernel
	@$(OBJCOPY) $(KERNEL_FILE) --strip-all -O binary $@

# 查看反汇编结果
asm:
	@$(OBJDUMP) -d $(KERNEL_FILE) | less

# 清理编译出的文件
clean:
	@rm -rf ./build/*

# 运行 QEMU
qemu: build
	@qemu-system-riscv64 \
            -machine virt \
            -nographic \
            -bios ../../rustsbi-qemu.bin \
            -device loader,file=$(BIN_FILE),addr=0x80200000

# 一键运行
run: build qemu