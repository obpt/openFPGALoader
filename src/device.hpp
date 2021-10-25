// SPDX-License-Identifier: Apache-2.0
/*
 * Copyright (C) 2019 Gwenhael Goavec-Merou <gwenhael.goavec-merou@trabucayre.com>
 */

#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <iostream>
#include <string>

#include "display.hpp"
#include "jtag.hpp"

/* GGM: TODO: program must have an optional
 * offset
 * and question: bitstream to load bitstream in SPI mode must
 * be hardcoded or provided by user?
 */
class Device {
	public:
		enum prog_mode {
			NONE_MODE = 0,
			SPI_MODE = 1,
			FLASH_MODE = 1,
			MEM_MODE = 2,
			READ_MODE = 3,
		};

		typedef enum {
			WR_SRAM = 0,
			WR_FLASH = 1,
			RD_FLASH = 2
		} prog_type_t;

		Device(Jtag *jtag, std::string filename, const std::string &file_type,
				bool verify, int8_t verbose = false);
		virtual ~Device();
		virtual void program(unsigned int offset = 0,
				bool unprotect_flash = false) = 0;
		virtual bool dumpFlash(const std::string &filename,
			uint32_t base_addr, uint32_t len) {
			(void)filename; (void) base_addr; (void) len;
			printError("dump flash not supported"); return false;}
		virtual int  idCode() = 0;
		virtual void reset();

	protected:
		Jtag *_jtag;
		std::string _filename;
		std::string _file_extension;
		enum prog_mode _mode;
		bool _verify; /**< verify flash write */
		bool _verbose;
		bool _quiet;
};

#endif
