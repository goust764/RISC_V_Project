;#include <stdio.h>
;//#define DEBUG
;
;#ifdef DEBUG
;void print_binary(int n, int size) {
;    int i;
;    for (i = size - 1; i >= 0; i--) {
;        int k = n >> i;
;        if (k & 1)
;            printf("1");
;        else
;            printf("0");
;    }
;}
;#endif
;
;#define CHECK_VALUE(NOTES, VALUE, SIZE) \
;    printf(NOTES "\n"); \
;    print_binary(VALUE, SIZE); 
;
;#define VALUE1 0x0E
;#define VALUE2 0x0F
;#define VALUE3 0x01
;
;#define VALUE4 0xFFFE
;#define VALUE5 0x000F
;#define VALUE6 0x0000
;
;#define VALUE7 0xFFFFFFFE
;#define VALUE8 0x0F0F0E0F
;#define VALUE9 0x00000000
;
;#define RESET_VAR_VALUES \
;a = VALUE1; \
;b = VALUE2; \
;c = VALUE3; \
;d = VALUE4; \
;e = VALUE5; \
;f = VALUE6; \
;g = VALUE7; \
;asm( \
;    "lui     a5,252645135\n\t" \
;    "addi    a5,a5,1807\n\t" \
;    "sw      a5,-40(s0)" \
;); \
;i = VALUE9;
;
;//ATTENTION : les 3 premiere ligne du code assembleur correspondant a la ligne en C ci-dessous ont ete modifie !
;asm(
;    "main:\n\t"
;    "addi    sp,sp,0\n\t"
;    "sw      s0,48(sp)\n\t"
;    "addi    s0,sp,48\n\t"
;    "----- A SUPPRIMER -----"
;);
;int main() {
;    unsigned char  a = 0;
;    unsigned char  b = 0;
;    unsigned char  c = 0;
;    unsigned short d = 0;
;    unsigned short e = 0;
;    unsigned short f = 0;
;    unsigned int   g = 0;
;    unsigned int   h = 0;
;    unsigned int   i = 0;
;    asm("---------------------");
;    //----- SB, ADDI, SH, SW
;    RESET_VAR_VALUES;
;
;    //----- ADD
;    // avec aussi LBU, SB, LW, SW
;    // Pas de test avec un overflow on 8 bit -> detecte par le compilateur
;    // c = a + b + c;
;    asm(
;        "lbu     a4,-17(s0)\n\t"      // a dans a4
;        "lbu     a5,-25(s0)\n\t"      // b dans a5
;        "lbu     a6,-26(s0)\n\t"      // c dans a6
;        "add     a4,a4,a5\n\t"        // a + b
;        "add     a6,a4,a6\n\t"        // (a + b) + c (dependance a gauche)
;        "add     a5,zero,a6\n\t"      // Dependance a droite
;        "sb      a5,-26(s0)\n\t"      // On ecrit c
;    );
;    
;    i = g + h;                        // Debordement
;
;    #ifdef DEBUG
;    CHECK_VALUE("c = a + b + c (ADD)", c, 8)
;    CHECK_VALUE("i = g + h (ADD debordement)", i, 32)
;    #endif
;    RESET_VAR_VALUES
;
;    //----- AND
;    // avec LW et SW
;    i = g & h;
;    #ifdef DEBUG
;    CHECK_VALUE("i = g & h (AND)", i, 32)
;    #endif
;    RESET_VAR_VALUES
;
;    //----- SLL
;    // avec LHU et SH
;    f = d << e;
;    #ifdef DEBUG
;    CHECK_VALUE("f = d << e (SLL)", f, 16)
;    #endif
;    RESET_VAR_VALUES
;
;    //----- SRL
;    // avec LHU et SH
;    asm(                             //f = d >> e avec debordement
;        "lhu     a4,-28(s0)\n\t"
;        "lhu     a5,-30(s0)\n\t"
;        "srl     a5,a4,a5\n\t"
;        "sh      a5,-32(s0)"
;    );
;    #ifdef DEBUG
;    CHECK_VALUE("f = d >> e (SRL)", f, 16)
;    #endif
;    RESET_VAR_VALUES
;
;    //----- OR
;    // avec LW et SW
;    i = g | h;
;    #ifdef DEBUG
;    CHECK_VALUE("i = g | h (OR)", i, 32)
;    #endif
;    RESET_VAR_VALUES
;
;    //----- XOR
;    // avec LW et SW
;    i = g ^ h;
;    #ifdef DEBUG
;    CHECK_VALUE("i = g ^ h (XOR)", i, 32)
;    #endif
;    RESET_VAR_VALUES
;
;    //----- SLTU
;     // avec LBU, LHU, SB, SH et ANDI
;    c = a < b;                        // = 1
;    f = d < e;                        // = 0
;    #ifdef DEBUG
;    CHECK_VALUE("c = a < b (SLTU)", c, 8)
;    CHECK_VALUE("f = e < d (SLTU)", f, 16)
;    #endif
;    RESET_VAR_VALUES
;
;    //----- SLT
;    // avec LB, LH, SB, SH et ANDI
;    // c = a < b;
;    // f = e < d;
;    asm(
;        "lb      a4,-17(s0)\n\t"
;        "lb      a5,-25(s0)\n\t"
;        "slt     a5,a4,a5\n\t"
;        "andi    a5,a5,255\n\t"
;        "sb      a5,-19(s0)\n\t"
;        "lh      a4,-30(s0)\n\t"
;        "lh      a5,-28(s0)\n\t"
;        "slt     a5,a5,a4\n\t"
;        "andi    a5,a5,255\n\t"
;        "sh      a5,-26(s0)\n\t"
;    );
;    #ifdef DEBUG
;    CHECK_VALUE("c = a < b (SLT)", c, 8)
;    CHECK_VALUE("f = e < d (SLT)", f, 16)
;    #endif
;    RESET_VAR_VALUES
;
;    //----- SRA
;    // avec LHU et SH
;    f = d >> e;                      // Debordement
;    #ifdef DEBUG
;    CHECK_VALUE("f = d >> e (SRA)", f, 16)
;    #endif
;    RESET_VAR_VALUES
;
;    //----- SUB
;    // avec LB, LH, SB et SH
;    //c = b - a;
;    //f = e - d;                       // Debordement
;    asm(
;        "lbu     a4,-25(s0)\n\t"
;        "lbu     a5,-17(s0)\n\t"
;        "sub     a5,a4,a5\n\t"
;        "sb      a5,-26(s0)\n\t"
;        "lhu     a4,-30(s0)\n\t"
;        "lhu     a5,-28(s0)\n\t"
;        "sub     a5,a4,a5\n\t"
;        "sh      a5,-32(s0)"
;    );
;    #ifdef DEBUG
;    CHECK_VALUE("c = a - b (SUB)", c, 8)
;    CHECK_VALUE("f = e - d (SUB)", f, 16)
;    #endif
;    RESET_VAR_VALUES
;
;    //----- ADDI --> Deja teste avec les LI
;    //----- ANDI --> Deja teste
;    //----- SLLI
;    // avec LHU, LBU, SB et SH
;    f = d << 5;                      // Debordement
;    c = a << 5;
;    #ifdef DEBUG
;    CHECK_VALUE("f = d << 5 (SLLI)", f, 16)
;    CHECK_VALUE("c = a << 5 (SLLI)", c, 8)
;    #endif
;    RESET_VAR_VALUES
;
;    //----- SRLI
;    // avec LHU, LBU, SB et SH
;    //a = a >> 1;
;    asm(
;        "lbu     a5,-17(s0)\n\t"
;        "srli    a5,a5,1\n\t"
;        "sh      a5,-17(s0)\n\t"
;    );
;    c = a >> 3;
;    /*#ifdef DEBUG
;    CHECK_VALUE("f = d >> 5 (SRLI)", f, 16)
;    CHECK_VALUE("c = a >> 5 (SRLI)", c, 8)
;    #endif*/
;    RESET_VAR_VALUES
;
;    //----- ORI
;    // avec LW et SW
;    asm(
;        "lw      a4,-44(s0)\n\t"       // Chargement de i
;        "nop"
;        "ori     a4,a4,1807\n\t"       // i = i | 70F (VALUE8 & 0FFF pour etre sur 12 bits)
;        "ori     a5,a4,2047\n\t"       // h = i | 7FF;
;        "sw      a4,-44(s0)\n\t"       // Stockage de i
;        "sw      a5,-40(s0)"           // Stockage de h
;    );
;    /*#ifdef DEBUG
;    CHECK_VALUE("i = g | VALUE8 (ORI)", i, 32)
;    CHECK_VALUE("h = i | 0x0F0F0000 (ORI)", h, 32)
;    #endif*/
;    RESET_VAR_VALUES
;
;    //----- XORI
;    asm(                               // i = h ^ VALUE7;
;        "lw      a4,-40(s0)\n\t"
;        "xori    a5,a4,4094\n\t"
;        "nop\n\t"
;        "nop\n\t"
;        "sw      a5,-44(s0)"
;        "nop\n\t"
;        "nop\n\t"
;        "nop"
;    );
;    
;    /*#ifdef DEBUG
;    CHECK_VALUE("i = g ^ VALUE4 (XORI)", i, 32)
;    #endif*/
;    RESET_VAR_VALUES
;
;    //----- SLTIU
;    // avec LHU, LBU, SB et SH
;    c = a < VALUE2;
;    // f = d < VALUE5;
;    asm(
;        "lhu     a4,-28(s0)\n\t"
;        "sltiu   a5,a4,15\n\t"
;        "andi    a5,a5,255\n\t"
;        "sh      a5,-32(s0)\n\t"
;    );
;    #ifdef DEBUG
;    CHECK_VALUE("c = a < VALUE2 (SLTIU)", c, 8)
;    CHECK_VALUE("f = d < VALUE5 (SLTIU)", f, 16)
;    #endif
;    RESET_VAR_VALUES
;
;    //----- SLTI
;    // avec LH, LB, SB et SH
;    //c = a < VALUE2;
;    asm(
;        "lb      a4,-17(s0)\n\t"
;        "slti    a5,a4,15\n\t"
;        "andi    a5,a5,255\n\t"
;        "sh      a5,-26(s0)"
;    );
;    // f = d < VALUE5;
;    asm(
;        "lh      a4,-28(s0)\n\t"
;        "slti    a5,a4,15\n\t"
;        "andi    a5,a5,255\n\t"
;        "sh      a5,-32(s0)"
;    );
;    #ifdef DEBUG
;    CHECK_VALUE("c = a < VALUE2 (SLTI)", c, 8)
;    CHECK_VALUE("f = d < VALUE5 (SLTI)", f, 16)
;    #endif
;    RESET_VAR_VALUES
;
;    //----- SRAI
;    // avec LHU et SH
;    //f = d >> VALUE5;                      // Debordement
;    asm(
;        "lhu     a5,-28(s0)\n\t"
;        "srai    a5,a5,15\n\t"
;        "sh      a5,-32(s0)\n\t"
;    );
;    #ifdef DEBUG
;    CHECK_VALUE("f = d >> VALUE5 (SRAI)", f, 16)
;    #endif
;    RESET_VAR_VALUES
;
;    //----- BEQ
;    // avec LBU et ADDI
;    if (a != VALUE1) {
;        a = 0;
;    }
;    asm (
;        "lbu     a4,-17(s0)\n\t"
;        "li      a5,14\n\t"
;        "beq     a4,a5,LABEL6\n\t"
;        "li      a5,0\n"
;        "LABEL6:\n\t"
;        "sb      a5,-17(s0)"
;    );
;    #ifdef DEBUG
;    CHECK_VALUE("a != VALUE1 alors a = 0 (BEQ)", a, 8)
;    #endif
;    RESET_VAR_VALUES
;
;    //----- BNE vrai
;    // Si a == a (donc VALUE1 14), a = 0 <-- devrait etre le resultat
;    asm (
;        "lbu     a4,-17(s0)\n\t"
;        "li      a5,14\n\t"
;        "bne     a4,a5,LABEL5\n\t"
;        "li      a5,0\n"
;        "LABEL5:\n\t"
;        "sb      a5,-17(s0)"
;    );
;    #ifdef DEBUG
;    CHECK_VALUE("a == VALUE1 alors a = 0 (BNE)", a, 8)
;    #endif
;    RESET_VAR_VALUES
;
;    //----- BGEU
;    // avec LBU et ADDI
;    /*if (a < VALUE1) {
;        a = 0;
;    }*/
;    asm(
;        "lbu     a4,-17(s0)\n\t"
;        "li      a5,15\n\t"
;        "bgeu    a4,a5,LABEL0\n\t"
;        "sb      zero,-17(s0)\n\t"
;        "LABEL0:\n\t"
;    );
;    #ifdef DEBUG
;    CHECK_VALUE("a < VALUE1 alors a = 0 (BGEU)", a, 8)
;    #endif
;    RESET_VAR_VALUES
;
;    //----- BGE
;    // avec LB et ADDI
;    /*if (a < VALUE1) {
;        a = 0;
;    }*/
;    asm(
;        "lbu     a4,-17(s0)\n\t"
;        "li      a5,15\n\t"
;        "bge     a4,a5,LABEL1\n\t"
;        "sb      zero,-17(s0)\n\t"
;        "LABEL1:\n\t"
;    );
;    #ifdef DEBUG
;    CHECK_VALUE("a < VALUE1 alors a = 0 (BGE)", a, 8)
;    #endif
;    RESET_VAR_VALUES
;
;    //----- BLTU
;    // avec LBU et ADDI
;    /*if (a >= VALUE1) {
;        a = 0;
;    }*/
;    asm(
;        "lbu     a4,-17(s0)\n\t"
;        "li      a5,14\n\t"
;        "bltu    a4,a5,LABEL2\n\t"
;        "sb      zero,-17(s0)\n\t"
;        "LABEL2:\n\t"
;    );
;    #ifdef DEBUG
;    CHECK_VALUE("a >= VALUE1 alors a = 0 (BLTU)", a, 8)
;    #endif
;    RESET_VAR_VALUES
;
;    //----- BLT
;    // avec LB et ADDI
;    /*if (a >= VALUE1) {
;        a = 0;
;    }*/
;    asm(
;        "lb     a4,-17(s0)\n\t"
;        "li      a5,14\n\t"
;        "blt     a4,a5,LABEL3\n\t"
;        "sb      zero,-17(s0)\n\t"
;        "LABEL3:\n\t"
;    );
;    #ifdef DEBUG
;    CHECK_VALUE("a >= VALUE1 alors a = 0 (BLT)", a, 8)
;    #endif
;    RESET_VAR_VALUES
;
;    //----- LUI
;    // avec SW et LW
;    // Verifier s'il est necessaire de faire des modifs dans le compilateur
;    asm(
;        "lw      a4,-40(s0)\n\t"        // On charge i
;        "lui     a4,14\n\t"             // lui a4,VALUE1
;        "sw      a4,-40(s0)\n\t"        // On range i
;    );
;    #ifdef DEBUG
;    CHECK_VALUE("LUI i,VALUE1", i, 32)
;    #endif
;    RESET_VAR_VALUES
;
;    //----- AUIPC
;    // avec SW et LW
;    // Verifier s'il est necessaire de faire des modifs dans le compilateur
;    asm(
;        "lw      a4,-40(s0)\n\t"        // On charge i
;        "auipc   a4,57344\n\t"
;        "sw      a4,-40(s0)\n\t"        // On range i
;    );
;    #ifdef DEBUG
;    CHECK_VALUE("AUIPC i,VALUE1", i, 32)
;    #endif
;    RESET_VAR_VALUES
;
;    //----- LBU --> Deja teste
;    //----- LHU --> Deja teste
;    //----- LB --> Deja teste
;    //----- LH --> Deja teste
;    //----- LW --> Deja teste
;    //----- JAL
;    // avec du monde
;    a = 0;
;    for (int j = 0; j < 1; j=j+1) {
;        a = a + 1;
;    }
;    asm("sw      r6,-40(s0)\n\t");   // R6 utilise pour remplace l'instruction J par JAL, on le stock dans i
;    #ifdef DEBUG
;    CHECK_VALUE("JAL i,offset", i, 32)
;    #endif
;    RESET_VAR_VALUES
;
;    //----- JALR
;    // Probleme avec le bit 11, on fait une somme pour eviter d'avoir ce probleme la
;    asm(
;        "addi    a5,zero,2047\n\t"
;        "nop\n\t"
;        "jalr    a4,a5,573\n\t"
;        "addi    a4,zero,0\n"             // Si ca marche pas i = 0
;        "LABEL4:"
;    );
;    #ifdef DEBUG
;    CHECK_VALUE("JALR i,offset", i, 32)
;    #endif
;    RESET_VAR_VALUES
;
;    return 0;
;}
;        .file   "example.c"
;        .option nopic
;        .attribute arch, "rv32i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
;        .attribute unaligned_access, 0
;        .attribute stack_align, 16

main:
        addi    sp,sp,0
        nop;sw      s0,48(sp)

        lui     a0,-4096
        lui     a1,2772
        addi    s0,sp,2772 ;addi    s0,sp,48
        xor     s0,s0,a0
        add     s0,s0,a1
        addi    a0,zero,0
        addi    a1,zero,0
        
        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        lbu     a4,-17(s0)
        lbu     a5,-25(s0)
        lbu     a6,-26(s0)
        add     a4,a4,a5
        add     a6,a4,a6
        add     a5,zero,a6
        sb      a5,-26(s0)

        lw      a4,-36(s0)
        lw      a5,-40(s0)
        add     a5,a4,a5
        sw      a5,-44(s0)
        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        lw      a4,-36(s0)
        lw      a5,-40(s0)
        and     a5,a4,a5
        sw      a5,-44(s0)
        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        lhu     a4,-28(s0)
        lhu     a5,-30(s0)
        sll     a5,a4,a5
        sh      a5,-32(s0)
        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        lhu     a4,-28(s0)
        lhu     a5,-30(s0)
        srl     a5,a4,a5
        sh      a5,-32(s0)

        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        lw      a4,-36(s0)
        lw      a5,-40(s0)
        or      a5,a4,a5
        sw      a5,-44(s0)
        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        lw      a4,-36(s0)
        lw      a5,-40(s0)
        xor     a5,a4,a5
        sw      a5,-44(s0)
        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        lbu     a4,-17(s0)
        lbu     a5,-25(s0)
        sltu    a5,a4,a5
        andi    a5,a5,255
        sb      a5,-26(s0)
        lhu     a4,-28(s0)
        lhu     a5,-30(s0)
        sltu    a5,a4,a5
        andi    a5,a5,255
        sh      a5,-32(s0)
        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        lb      a4,-17(s0)
        lb      a5,-18(s0)
        slt     a5,a4,a5
        andi    a5,a5,255
        sb      a5,-19(s0)
        lh      a4,-30(s0)
        lh      a5,-28(s0)
        slt     a5,a5,a4
        andi    a5,a5,255
        sh      a5,-26(s0)

        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        lhu     a4,-28(s0)
        lhu     a5,-30(s0)
        sra     a5,a4,a5
        sh      a5,-32(s0)
        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        lbu     a4,-25(s0)
        lbu     a5,-17(s0)
        sub     a5,a4,a5
        sb      a5,-26(s0)
        lhu     a4,-30(s0)
        lhu     a5,-28(s0)
        sub     a5,a4,a5
        sh      a5,-32(s0)
        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        lhu     a5,-28(s0)
        slli    a5,a5,5
        sh      a5,-32(s0)
        lbu     a5,-17(s0)
        slli    a5,a5,5
        sb      a5,-26(s0)
        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        lhu     a5,-17(s0)
        srli    a5,a5,1
        sh      a5,-17(s0)

        lbu     a5,-17(s0)
        srli    a5,a5,3
        sb      a5,-26(s0)
        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        lw      a4,-44(s0)
        nop
        ori     a4,a4,1807
        ori     a5,a4,2047
        sw      a4,-44(s0)
        sw      a5,-40(s0)
        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        lw      a4,-40(s0)
        xori    a5,a4,4094
        nop
        nop
        sw      a5,-44(s0)
        nop
        nop
        nop
        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        lbu     a5,-17(s0)
        sltiu   a5,a5,15
        andi    a5,a5,255
        sb      a5,-26(s0)
        lhu     a4,-28(s0)
        sltiu   a5,a4,15
        andi    a5,a5,255
        sh      a5,-32(s0)

        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        lb      a4,-17(s0)
        slti    a5,a4,15
        andi    a5,a5,255
        sh      a5,-26(s0)
        lh      a4,-28(s0)
        slti    a5,a4,15
        andi    a5,a5,255
        sh      a5,-32(s0)
        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        lhu     a5,-28(s0)
        srai    a5,a5,15
        sh      a5,-32(s0)

        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        lbu     a4,-17(s0)
        li      a5,14
        beq     a4,a5,LABEL6
        li      a5,0
LABEL6:
        sb      a5,-17(s0)
        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        lbu     a4,-17(s0)
        li      a5,14
        bne     a4,a5,LABEL5
        ;sw a0,-1000(s0)
        li      a5,0
LABEL5:
        sb      a5,-17(s0)
        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        lbu     a4,-17(s0)
        li      a5,15
        bgeu    a4,a5,LABEL0
        sb      zero,-17(s0)
LABEL0:

        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        lbu     a4,-17(s0)
        li      a5,15
        bge     a4,a5,LABEL1
        sb      zero,-17(s0)
LABEL1:

        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        lbu     a4,-17(s0)
        li      a5,14
        bltu    a4,a5,LABEL2
        sb      zero,-17(s0)
LABEL2:

        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        lb     a4,-17(s0)
        li      a5,14
        blt     a4,a5,LABEL3
        sb      zero,-17(s0)
LABEL3:

        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        lw      a4,-40(s0)
        lui     a4,14
        sw      a4,-40(s0)

        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        lw      a4,-40(s0)
        auipc   a4,57344
        sw      a4,-40(s0)

        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        sb      zero,-17(s0)
        sw      zero,-24(s0)
        j       .L4
.L5:
        lbu     a5,-17(s0)
        addi    a5,a5,1
        sb      a5,-17(s0)
        lw      a5,-24(s0)
        addi    a5,a5,1
        sw      a5,-24(s0)
.L4:
        lw      a5,-24(s0)
        ble     a5,zero,.L5
        sw      r6,-40(s0)

        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)
        addi    a5,zero,2047
        jalr    a4,a5,593
        addi    a4,zero,0
LABEL4:
        li      a5,14
        sb      a5,-17(s0)
        li      a5,15
        sb      a5,-25(s0)
        li      a5,1
        sb      a5,-26(s0)
        li      a5,-2
        sh      a5,-28(s0)
        li      a5,15
        sh      a5,-30(s0)
        sh      zero,-32(s0)
        li      a5,-2
        sw      a5,-36(s0)
        lui     a5,252645135
        addi    a5,a5,1807
        sw      a5,-40(s0)
        sw      zero,-44(s0)