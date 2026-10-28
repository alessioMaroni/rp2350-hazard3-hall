use std::env;
use std::path::PathBuf;

fn main() {
	let manifest_dir = env::var("CARGO_MANIFEST_DIR").unwrap();
	let manifest_path = PathBuf::from(&manifest_dir);
	let include_dir = manifest_path.join("include");
	let src_uart = manifest_path.join("src").join("uart.c");

	println!("cargo:rerun-if-changed=include/rp2350_hall.h");
	println!("cargo:rerun-if-changed=include/uart.h");
	println!("cargo:rerun-if-changed=include/serial.h");
	println!("cargo:rerun-if-changed=include/helpers.h");
	println!("cargo:rerun-if-changed=src/uart.c");

	println!("cargo:include={}", include_dir.display());

	let mut build = cc::Build::new();
	build
		.file(&src_uart)
		.include(&include_dir)
		.flag("-ffreestanding")
		.flag("-Wall")
		.flag("-Wextra")
		.flag("-Werror");

	let target = env::var("TARGET").unwrap_or_default();
	if target.contains("riscv32") {
		if env::var("CC").is_err() && env::var("CC_riscv32imac_unknown_none_elf").is_err() {
			let candidates = [
				"riscv-none-elf-gcc",
				"riscv64-unknown-elf-gcc",
				"riscv32-unknown-elf-gcc",
				"riscv64-linux-gnu-gcc",
			];

<<<<<<< HEAD
=======
<<<<<<< Updated upstream
    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Impossibile scrivere bindings.rs");
=======
>>>>>>> uart
			for compiler in candidates {
				if std::process::Command::new(compiler)
					.arg("--version")
					.output()
					.is_ok()
				{
					build.compiler(compiler);
					break;
				}
			}
		}

		build
			.flag("-march=rv32imac_zicsr_zifencei_zba_zbb_zbkb_zbs")
			.flag("-mabi=ilp32")
			.flag("-mcmodel=medlow");
	}

	build.compile("rp2350-hazard3-hall");

	let bindings = bindgen::Builder::default()
		.header(include_dir.join("rp2350_hall.h").to_str().unwrap())
		.clang_arg(format!("-I{}", include_dir.display()))
		.use_core()
<<<<<<< HEAD
		.wrap_unsafe_ops(true)
		.ctypes_prefix("core::ffi")
=======
		.ctypes_prefix("core::ffi")
		.wrap_unsafe_ops(true)
		.raw_line("#[allow(warnings)]")
		.raw_line("#[allow(unsafe_op_in_unsafe_fn)]")
>>>>>>> uart
		.generate()
		.expect("Impossibile generare i bindings C");

	let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
	bindings
		.write_to_file(out_path.join("bindings.rs"))
		.expect("Impossibile scrivere bindings.rs");
<<<<<<< HEAD
=======
>>>>>>> Stashed changes
>>>>>>> uart
}
