#![no_std]

#[allow(non_upper_case_globals)]
#[allow(non_camel_case_types)]
#[allow(non_snake_case)]
#[allow(dead_code)]
mod raw {
	include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
}

pub mod serial {
    	pub use super::raw::uart_write_byte;
    	pub use super::raw::UART0_BASE;
    	pub use super::raw::UART1_BASE;
}

pub mod time {
	pub use super::raw::read_mtime;
    pub use super::raw::write_mtimecmp;
    pub use super::raw::TIME_BASE_ADDR;

	pub const MTIME_ADDR: usize = (TIME_BASE_ADDR as usize) + 0xBFF8;
    pub const MTIMECMP_ADDR: usize = (TIME_BASE_ADDR as usize) + 0x4000;
}
