PATH := $(HOME)/.cargo/bin:$(PATH)
export LIBCLANG_PATH := /usr/lib64/llvm22/lib64
export LD_LIBRARY_PATH := /usr/lib64/llvm22/lib64:/usr/lib64:$(LD_LIBRARY_PATH)
export LIBRARY_PATH := /usr/lib64/llvm22/lib64:/usr/lib64:$(LIBRARY_PATH)

.PHONY: check clean

c:
	@echo "Library checking..."
	cargo build --target riscv32imac-unknown-none-elf

verify:
	cppcheck --addon=misra --enable=all --std=c99 -I include/ --suppressions-list=suppressions.txt src/

clean:
	cargo clean
