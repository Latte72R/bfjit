#define _GNU_SOURCE

#include "bfjit_internal.h"

#include <stdint.h>
#include <stdio.h>

static int bf_io_putchar(int c) { return putchar_unlocked(c); }

static int bf_io_getchar(void) { return getchar_unlocked(); }

static uint8_t *bf_io_scan_index(uint8_t *tape, uint8_t *tape_end,
                                 uint8_t *start_ptr, int64_t step) {
    uint8_t *ptr;

    if (tape == NULL || tape_end == NULL || start_ptr == NULL || step == 0 ||
        start_ptr < tape || start_ptr >= tape_end) {
        return NULL;
    }

    ptr = start_ptr;

    while (ptr >= tape && ptr < tape_end) {
        if (*ptr == 0) {
            return ptr;
        }
        ptr += step;
    }

    return NULL;
}

static uint8_t *bf_io_scan_index_step4(uint8_t *tape, uint8_t *tape_end,
                                       uint8_t *start_ptr) {
    uint8_t *ptr;

    if (tape == NULL || tape_end == NULL || start_ptr == NULL ||
        start_ptr < tape || start_ptr >= tape_end) {
        return NULL;
    }

    ptr = start_ptr;

    while (ptr + 12 < tape_end) {
        if (ptr[0] == 0) {
            return ptr;
        }
        if (ptr[4] == 0) {
            return ptr + 4;
        }
        if (ptr[8] == 0) {
            return ptr + 8;
        }
        if (ptr[12] == 0) {
            return ptr + 12;
        }
        ptr += 16;
    }

    while (ptr < tape_end) {
        if (*ptr == 0) {
            return ptr;
        }
        if (ptr + 4 < tape_end) {
            ptr += 4;
        } else {
            break;
        }
    }

    return NULL;
}

LLVMOrcMaterializationUnitRef bf_create_io_symbols(LLVMOrcLLJITRef jit) {
    LLVMOrcCSymbolMapPair io_symbols[4];

    io_symbols[0].Name = LLVMOrcLLJITMangleAndIntern(jit, "bf_io_putchar");
    io_symbols[0].Sym.Address =
        (LLVMOrcExecutorAddress)(uintptr_t)bf_io_putchar;
    io_symbols[0].Sym.Flags.GenericFlags =
        LLVMJITSymbolGenericFlagsExported | LLVMJITSymbolGenericFlagsCallable;
    io_symbols[0].Sym.Flags.TargetFlags = 0;

    io_symbols[1].Name = LLVMOrcLLJITMangleAndIntern(jit, "bf_io_getchar");
    io_symbols[1].Sym.Address =
        (LLVMOrcExecutorAddress)(uintptr_t)bf_io_getchar;
    io_symbols[1].Sym.Flags.GenericFlags =
        LLVMJITSymbolGenericFlagsExported | LLVMJITSymbolGenericFlagsCallable;
    io_symbols[1].Sym.Flags.TargetFlags = 0;

    io_symbols[2].Name = LLVMOrcLLJITMangleAndIntern(jit, "bf_io_scan_index");
    io_symbols[2].Sym.Address =
        (LLVMOrcExecutorAddress)(uintptr_t)bf_io_scan_index;
    io_symbols[2].Sym.Flags.GenericFlags =
        LLVMJITSymbolGenericFlagsExported | LLVMJITSymbolGenericFlagsCallable;
    io_symbols[2].Sym.Flags.TargetFlags = 0;

    io_symbols[3].Name =
        LLVMOrcLLJITMangleAndIntern(jit, "bf_io_scan_index_step4");
    io_symbols[3].Sym.Address =
        (LLVMOrcExecutorAddress)(uintptr_t)bf_io_scan_index_step4;
    io_symbols[3].Sym.Flags.GenericFlags =
        LLVMJITSymbolGenericFlagsExported | LLVMJITSymbolGenericFlagsCallable;
    io_symbols[3].Sym.Flags.TargetFlags = 0;

    return LLVMOrcAbsoluteSymbols(io_symbols, 4);
}
