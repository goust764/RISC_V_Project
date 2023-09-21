main:                                   ; @main
        addi    sp,sp,48
        sw      ra,28(sp)                      ; 4-byte Folded Spill
        sw      s0,24(sp)                      ; 4-byte Folded Spill
        addi    s0,sp,32
        li      a0,0
        sw      a0,-12(s0)
        li      a0,5
        sw      a0,-16(s0)
        sw      a0,-20(s0)
        lw      a1,-16(s0)
        lw      a0,-20(s0)
        ble     a0,a1,.LBB0_2
        j       .LBB0_1
.LBB0_1:
        lw      a0,-16(s0)
        addi    a0,a0,1
        sw      a0,-16(s0)
        j       .LBB0_2
.LBB0_2:
        li      a0,0
        lw      ra,28(sp)                      ; 4-byte Folded Reload
        lw      s0,24(sp)                      ; 4-byte Folded Reload
        addi    sp,sp,32