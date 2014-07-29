#ifndef ATLANTIS_DEBUGGER_H_
#define ATLANTIS_DEBUGGER_H_

#include <stdint.h>

extern void atlantis_debug_io_reg(uint32_t address, uint32_t value);
extern void atlantis_debug_read_word(uint32_t address, uint32_t value);
extern void atlantis_debug_read_halfword(uint32_t address, uint16_t value);
extern void atlantis_debug_read_signed_halfword(uint32_t address, int16_t value);
extern void atlantis_debug_read_byte(uint32_t address, uint8_t value);
extern void atlantis_debug_write_byte(uint32_t address, uint8_t value);
extern void atlantis_debug_write_halfword(uint32_t address, uint16_t value);
extern void atlantis_debug_write_word(uint32_t address, uint32_t value);
extern void atlantis_debug_instruction(bool arm, uint32_t pc);

#endif /* ATLANTIS_DEBUGGER_H_ */
