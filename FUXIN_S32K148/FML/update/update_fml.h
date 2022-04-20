

#include "Cpu.h"

extern status_t flash_app_set_fml(void);
extern void erase_updata_pflash_fml(uint32_t address);
extern uint8_t read_pflsh_fml(uint16_t index,uint32_t base_address);
status_t erase_dfalsh_fml(uint32_t address);