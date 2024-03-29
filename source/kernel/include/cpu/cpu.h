#ifndef CPU_H
#define CPU_H

#include "comm/types.h"

#pragma pack(1)

typedef struct _segment_desc_t {
    uint16_t limit15_0;
    uint16_t base15_0;
    uint8_t base23_16;
    uint16_t attr;
    uint8_t base31_24;
}segment_desc_t;

typedef struct _gate_desc_t {
    uint16_t offset15_0;
    uint16_t selector;
    uint16_t attr;
    uint16_t offset31_16;
}gate_desc_t;

#pragma pack()

typedef struct _exception_frame_t {
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t num, error_code;
    uint32_t eip, cs, eflags;
}exception_frame_t;

void cpu_init(void);
void segment_desc_set(int selector, uint32_t base, uint32_t limit, uint16_t attr);
void gate_desc_set(gate_desc_t *desc, uint16_t selector, uint32_t offset, uint16_t attr);

// for gdt descriptors
#define SEG_G (1 << 15) // granularity is 4KB
#define SEG_D (1 << 14) // set to 32 bits mode
#define SEG_P_PRESENT (1 << 7) // descriptor exists

#define SEG_DPL0 (0 << 5)
#define SEG_DPL3 (3 << 5)

#define SEG_S_SYSTEM (0 << 4)
#define SEG_S_NORMAL (1 << 4)

#define SEG_TYPE_CODE (1 << 3)
#define SEG_TYPE_DATA (0 << 3)

#define SEG_TYPE_RW (1 << 1)

// for idt descriptors
#define GATE_P_PRESENT (1 << 15)
#define GATE_DPL0 (0 << 13)
#define GATE_DPL3 (3 << 13)
#define GATE_D (1 << 11)
#define GATE_TYPE_INT (6 << 8)

#define IRQ0_DE 0

#endif