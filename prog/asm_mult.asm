;//int mult(int a, int b) {
;int mult() {
;    int a = 764;
;    int b = 10;
;    int res = 0;
;
;    for (int i = 0; i < 32; i=i+1) {
;        if (b & 1) res = res + (a << i);
;        b = b >> 1;
;    }
;
;    return res;
;}
;
;        .file   "example.cpp"
;        .option nopic
;        .attribute arch, "rv32i2p1_m2p0_a2p1_f2p2_d2p2_c2p0_zicsr2p0_zifencei2p0"
;        .attribute unaligned_access, 0
;        .attribute stack_align, 16

mult:
        ; Init
        ;sw      s0,28(sp)
        addi    s0,sp,216
        ; int a = 764
        li      a5,764
        sw      a5,-32(s0)
        ; int b = 9
        li      a5,9
        sw      a5,-20(s0)
        ; int res = 0
        sw      zero,-24(s0)
        ; for (int i = 0
        sw      zero,-28(s0)
        j       .L2
.L4:
        ; if (b & 1)
        lw      a5,-20(s0)
        andi    a5,a5,1
        beq     a5,zero,.L3
        ; res = res + (a << i)
        lw      a5,-28(s0)
        lw      a4,-32(s0)
        sll     a5,a4,a5
        lw      a4,-24(s0)
        add     a5,a4,a5
        sw      a5,-24(s0)
        ; b = b >> 1
.L3:
        lw      a5,-20(s0)
        srai    a5,a5,1
        sw      a5,-20(s0)
        ; i = i + 1
        lw      a5,-28(s0)
        addi    a5,a5,1
        sw      a5,-28(s0)
        ; i < 32
.L2:
        lw      a4,-28(s0)
        li      a5,31
        ble     a4,a5,.L4
        lw      a5,-24(s0)