#![no_std]

pub mod ffi {
    include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
}