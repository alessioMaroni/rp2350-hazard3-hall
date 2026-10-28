#![no_std]

<<<<<<< HEAD
#[allow(unsafe_code)]
#[allow(clippy::all)]
=======
<<<<<<< Updated upstream
=======
#[allow(warnings)]
#[allow(unsafe_op_in_unsafe_fn)]
#[allow(clippy::all)]
#[allow(unsafe_code)]
>>>>>>> Stashed changes
>>>>>>> uart
#[allow(non_upper_case_globals)]
#[allow(non_camel_case_types)]
#[allow(non_snake_case)]
#[allow(dead_code)]
mod raw {
	include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
}

pub mod uart {
	pub use super::raw::uart_init;
	pub use super::raw::uart_write_byte;
}
