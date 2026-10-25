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
		.wrap_unsafe_ops(true)
		.ctypes_prefix("core::ffi")
		.generate()
		.expect("Error");

	let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
	bindings
		.write_to_file(out_path.join("bindings.rs"))
		.expect("Error");
}
