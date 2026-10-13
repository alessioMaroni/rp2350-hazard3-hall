use std::env;
use std::path::PathBuf;

fn main() {
    println!("cargo:rerun-if-changed=include/rp2350_hall.h");
    println!("cargo:rerun-if-changed=src/serial.c");

    let mut build = cc::Build::new();
    build
        .file("src/serial.c")
        .include("include")
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
        .header("include/rp2350_hall.h")
        .use_core() // Genera binding compatibili no_std
        .ctypes_prefix("core::ffi")
        .generate()
        .expect("Impossibile generare i bindings C");

    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Impossibile scrivere bindings.rs");
}