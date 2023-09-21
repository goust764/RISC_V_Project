#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include "../include/rv32ias/asm_line.h"
#include "../include/rv32ias/list.h"
#include "../include/rv32ias/string.h"
#include "../include/unitest/logging.h"

insn_t insnset2insn(insnset_t insn_set) {
    insn_t insn;
    insn.insn = insn_set;

    if (insn_set < 0)        insn.type = TYPE_UNDEF;
    // NOP instruction
    if      (insn_set == 0)  insn.type = TYPE_NOP;
    // Register-register instructions
    else if (insn_set < 11)  insn.type = TYPE_REGREG;
    // Register-immediate instructions
    else if (insn_set < 20)  insn.type = TYPE_REGIMM;
    // Branch instructions
    else if (insn_set < 26)  insn.type = TYPE_BRANCH;
    // Upper immediate instructions
    else if (insn_set == 26) insn.type = TYPE_LUI;
    else if (insn_set == 27) insn.type = TYPE_AUIPC;
    // Load instructions
    else if (insn_set < 33)  insn.type = TYPE_LOAD;
    // Store instructions
    else if (insn_set < 36)  insn.type = TYPE_STORE;
    // Jump instructions
    else if (insn_set == 36) insn.type = TYPE_JAL;
    else                     insn.type = TYPE_JALR;
    return insn;
}

insn_t str2insn(char *str) {
    int i = 0;

    if (!strcmp(str, "insn::NOP"))   return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::ADD"))   return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::AND"))   return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::SLL"))   return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::SRL"))   return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::OR"))    return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::XOR"))   return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::SLTU"))  return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::SLT"))   return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::SRA"))   return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::SUB"))   return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::ADDI"))  return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::ANDI"))  return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::SLLI"))  return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::SRLI"))  return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::ORI"))   return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::XORI"))  return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::SLTIU")) return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::SLTI"))  return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::SRAI"))  return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::BEQ"))   return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::BNE"))   return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::BGEU"))  return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::BGE"))   return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::BLTU"))  return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::BLT"))   return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::LUI"))   return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::AUIPC")) return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::LBU"))   return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::LHU"))   return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::LB"))    return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::LH"))    return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::LW"))    return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::SB"))    return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::SW"))    return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::SH"))    return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::JAL"))   return insnset2insn(i); else i++;
    if (!strcmp(str, "insn::JALR"))  return insnset2insn(i); else i++;

    return insnset2insn(-1);
}

reg_t str2reg(char *str) {
    int i = 0;

    if (!strcmp(str, "r0") || !strcmp(str, "zero"))
                             return i; else i++;
    if (!strcmp(str, "r1") || !strcmp(str, "ra"))
                             return i; else i++;
    if (!strcmp(str, "r2") || !strcmp(str, "sp"))
                             return i; else i++;
    if (!strcmp(str, "r3"))  return i; else i++;
    if (!strcmp(str, "r4"))  return i; else i++;
    if (!strcmp(str, "r5"))  return i; else i++;
    if (!strcmp(str, "r6"))  return i; else i++;
    if (!strcmp(str, "r7"))  return i; else i++;
    if (!strcmp(str, "r8") || !strcmp(str, "s0")) 
                             return i; else i++;
    if (!strcmp(str, "r9") || !strcmp(str, "s1")) 
                             return i; else i++;
    if (!strcmp(str, "r10") || !strcmp(str, "a0"))
                             return i; else i++;
    if (!strcmp(str, "r11") || !strcmp(str, "a1"))
                             return i; else i++;
    if (!strcmp(str, "r12") || !strcmp(str, "a2"))
                             return i; else i++;
    if (!strcmp(str, "r13") || !strcmp(str, "a3"))
                             return i; else i++;
    if (!strcmp(str, "r14") || !strcmp(str, "a4"))
                             return i; else i++;
    if (!strcmp(str, "r15") || !strcmp(str, "a5"))
                             return i; else i++;
    if (!strcmp(str, "r16") || !strcmp(str, "a6"))
                             return i; else i++;
    if (!strcmp(str, "r17") || !strcmp(str, "a7"))
                             return i; else i++;
    if (!strcmp(str, "r18")) return i; else i++;
    if (!strcmp(str, "r19")) return i; else i++;
    if (!strcmp(str, "r20")) return i; else i++;
    if (!strcmp(str, "r21")) return i; else i++;
    if (!strcmp(str, "r22")) return i; else i++;
    if (!strcmp(str, "r23")) return i; else i++;
    if (!strcmp(str, "r24")) return i; else i++;
    if (!strcmp(str, "r25")) return i; else i++;
    if (!strcmp(str, "r26")) return i; else i++;
    if (!strcmp(str, "r27")) return i; else i++;
    if (!strcmp(str, "r28")) return i; else i++;
    if (!strcmp(str, "r29")) return i; else i++;
    if (!strcmp(str, "r30")) return i; else i++;
    if (!strcmp(str, "r31")) return i; else i++;

    return -1;
}

char* reg2code(reg_t reg) {
    switch (reg) {
        case R0 : return R0_CODE;
        case R1 : return R1_CODE;
        case R2 : return R2_CODE;
        case R3 : return R3_CODE;
        case R4 : return R4_CODE;
        case R5 : return R5_CODE;
        case R6 : return R6_CODE;
        case R7 : return R7_CODE;
        case R8 : return R8_CODE;
        case R9 : return R9_CODE;
        case R10: return R10_CODE;
        case R11: return R11_CODE;
        case R12: return R12_CODE;
        case R13: return R13_CODE;
        case R14: return R14_CODE;
        case R15: return R15_CODE;
        case R16: return R16_CODE;
        case R17: return R17_CODE;
        case R18: return R18_CODE;
        case R19: return R19_CODE;
        case R20: return R20_CODE;
        case R21: return R21_CODE;
        case R22: return R22_CODE;
        case R23: return R23_CODE;
        case R24: return R24_CODE;
        case R25: return R25_CODE;
        case R26: return R26_CODE;
        case R27: return R27_CODE;
        case R28: return R28_CODE;
        case R29: return R29_CODE;
        case R30: return R30_CODE;
        case R31: return R31_CODE;
        default: return NULL;
    }
}

asm_line_t* asm_line_new() {
    asm_line_t* line = malloc(sizeof(asm_line_t));
    assert(line);
    line->type = INSN_LINE;
    line->insn_line.insn.insn = NOP;
    line->insn_line.insn.type = TYPE_NOP;
    line->insn_line.rd = 0;
    line->insn_line.rs1 = 0;
    line->insn_line.rs2 = 0;
    line->insn_line.imm = 0;
    string_new(&(line->insn_line.label), "", 0);
    line->insn_line.line_addr = 0;
    return line;
}

void asm_line_regreg_add(list_t* insn_list, insn_t insn, reg_t rd, reg_t rs1, reg_t rs2, int line_addr) {
    asm_line_t* line = asm_line_new();
    line->type = INSN_LINE;
    line->insn_line.insn = insn;
    line->insn_line.rd = rd;
    line->insn_line.rs1 = rs1;
    line->insn_line.rs2 = rs2;
    line->insn_line.line_addr = line_addr;

    *insn_list = list_add_last(*insn_list, line);
}

void asm_line_imm_add(list_t* insn_list, insn_t insn, reg_t rd, reg_t rs1, int imm, int line_addr) {
    asm_line_t* line = asm_line_new();
    line->type = INSN_LINE;
    line->insn_line.insn = insn;
    line->insn_line.rd = rd;
    line->insn_line.rs1 = rs1;
    line->insn_line.imm = imm;
    line->insn_line.line_addr = line_addr;

    *insn_list = list_add_last(*insn_list, line);
}

void asm_line_branch_add(list_t* insn_list, insn_t insn, reg_t rs1, reg_t rs2, char* label, int line_addr) {
    asm_line_t* line = asm_line_new();
    line->type = INSN_LINE;
    line->insn_line.insn = insn;
    line->insn_line.rs1 = rs1;
    line->insn_line.rs2 = rs2;
    line->insn_line.label = string_convert(label);
    line->insn_line.line_addr = line_addr;

    *insn_list = list_add_last(*insn_list, line);
}

void asm_line_load_add(list_t* insn_list, insn_t insn, reg_t rd, reg_t rs1, int imm, int line_addr) {
    asm_line_t* line = asm_line_new();
    line->type = INSN_LINE;
    line->insn_line.insn = insn;
    line->insn_line.rd = rd;
    line->insn_line.rs1 = rs1;
    line->insn_line.imm = imm;
    line->insn_line.line_addr = line_addr;

    *insn_list = list_add_last(*insn_list, line);
}

void asm_line_store_add(list_t* insn_list, insn_t insn, reg_t rs1, reg_t rs2, int imm, int line_addr) {
    asm_line_t* line = asm_line_new();
    line->type = INSN_LINE;
    line->insn_line.insn = insn;
    line->insn_line.rs1 = rs1;
    line->insn_line.rs2 = rs2;
    line->insn_line.imm = imm;
    line->insn_line.line_addr = line_addr;

    *insn_list = list_add_last(*insn_list, line);
}

void asm_line_jal_add(list_t* insn_list, insn_t insn, reg_t rd, char* label, int line_addr) {
    asm_line_t* line = asm_line_new();
    line->type = INSN_LINE;
    line->insn_line.insn = insn;
    line->insn_line.rd = rd;
    line->insn_line.label = string_convert(label);
    line->insn_line.line_addr = line_addr;

    *insn_list = list_add_last(*insn_list, line);
}

void asm_line_jalr_add(list_t* insn_list, insn_t insn, reg_t rd, reg_t rs1, int imm, int line_addr) {
    asm_line_t* line = asm_line_new();
    line->type = INSN_LINE;
    line->insn_line.insn = insn;
    line->insn_line.rd = rd;
    line->insn_line.rs1 = rs1;
    line->insn_line.imm = imm;
    line->insn_line.line_addr = line_addr;

    *insn_list = list_add_last(*insn_list, line);
}

void asm_line_upper_add(list_t* insn_list, insn_t insn, reg_t rd, int imm, int line_addr) {
    asm_line_t* line = asm_line_new();
    line->type = INSN_LINE;
    line->insn_line.insn = insn;
    line->insn_line.rd = rd;
    line->insn_line.imm = imm;
    line->insn_line.line_addr = line_addr;

    *insn_list = list_add_last(*insn_list, line);
}

void asm_line_label_add(list_t* insn_list, char* name, int line_addr) {
    asm_line_t* line = asm_line_new();
    line->type = LABEL_LINE;
    line->label.name = string_convert(name);
    line->label.name.length = line->label.name.length - 1; // On enleve le : de la fin
    line->label.line_addr = line_addr;

    *insn_list = list_add_last(*insn_list, line);
}

void asm_line_nop_add(list_t* insn_list, int line_addr) {
    asm_line_t* line = asm_line_new();
    line->type = INSN_LINE;
    insn_t insn_nop;
    insn_nop.insn = NOP;
    insn_nop.type = TYPE_NOP;
    line->insn_line.insn = insn_nop;
    line->insn_line.line_addr = line_addr;

    *insn_list = list_add_last(*insn_list, line);
}

int asm_line_update_adress(list_t* insn_list) {
    asm_line_t* line;
    int label_found = 0;
    // Cherche tous les instructions de banchement ou de saut dans le code
    for (list_t l = *insn_list; !list_empty(l) ; l = list_next(l)) {
        label_found = 0;
        line = list_first(l);
        if (line->type                == INSN_LINE   && (
            line->insn_line.insn.type == TYPE_BRANCH ||
            line->insn_line.insn.type == TYPE_JAL)) {
                // Cherche le label correspondant
                for (list_t l = *insn_list; !list_empty(l) ; l = list_next(l)) {
                    asm_line_t* line2 = list_first(l);
                    if (line2->type == LABEL_LINE && string_compare(line2->label.name, line->insn_line.label)) {
                        line->insn_line.imm = line2->label.line_addr - line->insn_line.line_addr;
                        label_found = 1;
                    }
                }
                if (!label_found) {
                    STYLE(stderr, COLOR_RED, STYLE_HIGH_INTENSITY_TEXT);
                    printf("Impossible de trouver le label \"");
                    string_print(line->insn_line.label);
                    printf("\".\n");
                    STYLE_RESET(stderr);
                    return -1;
                }
        }
    }
    return 0;
}

void print_binary(FILE* file, int n, int size) {
    int i;
    for (i = size - 1; i >= 0; i--) {
        int k = n >> i;
        if (k & 1)
            fprintf(file, "1");
        else
            fprintf(file, "0");
    }
}

int asm_line_write(list_t* insn_list, char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        STYLE(stderr, COLOR_RED, STYLE_HIGH_INTENSITY_TEXT);
        printf("Impossible d'ouvrir le fichier \"%s\".\n", filename);
        STYLE_RESET(stderr);
        return -1;
    }

    for (list_t l = *insn_list; !list_empty(l) ; l = list_next(l)) {
        asm_line_t* line = list_first(l);
        if (line->type == INSN_LINE) {
            switch (line->insn_line.insn.type) {
                case TYPE_NOP:
                    print_binary(file, 0, 32);                                          //31-0
                    fprintf(file, "\n");
                break;
                case TYPE_REGREG:
                    switch (line->insn_line.insn.insn) {
                        case ADD:
                            fprintf(file, "%s", ADD_FUNCT7);                             // 31-25
                            fprintf(file, "%s", reg2code(line->insn_line.rs2));          // 24-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", ADD_FUNCT3);                             // 14-12
                            fprintf(file, "%s", reg2code(line->insn_line.rd));           // 11-7
                        break;
                        case SUB:
                            fprintf(file, "%s", SUB_FUNCT7);                             // 31-25
                            fprintf(file, "%s", reg2code(line->insn_line.rs2));          // 24-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", SUB_FUNCT3);                             // 14-12
                            fprintf(file, "%s", reg2code(line->insn_line.rd));           // 11-7
                        break;
                        case AND:
                            fprintf(file, "%s", AND_FUNCT7);                             // 31-25
                            fprintf(file, "%s", reg2code(line->insn_line.rs2));          // 24-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", AND_FUNCT3);                             // 14-12
                            fprintf(file, "%s", reg2code(line->insn_line.rd));           // 11-7
                        break;
                        case OR:
                            fprintf(file, "%s", OR_FUNCT7);                              // 31-25
                            fprintf(file, "%s", reg2code(line->insn_line.rs2));          // 24-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", OR_FUNCT3);                              // 14-12
                            fprintf(file, "%s", reg2code(line->insn_line.rd));           // 11-7
                        break;
                        case XOR:
                            fprintf(file, "%s", XOR_FUNCT7);                             // 31-25
                            fprintf(file, "%s", reg2code(line->insn_line.rs2));          // 24-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", XOR_FUNCT3);                             // 14-12
                            fprintf(file, "%s", reg2code(line->insn_line.rd));           // 11-7
                        break;
                        case SLL:
                            fprintf(file, "%s", SLL_FUNCT7);                             // 31-25
                            fprintf(file, "%s", reg2code(line->insn_line.rs2));          // 24-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", SLL_FUNCT3);                             // 14-12
                            fprintf(file, "%s", reg2code(line->insn_line.rd));           // 11-7
                        break;
                        case SRL:
                            fprintf(file, "%s", SRL_FUNCT7);                             // 31-25
                            fprintf(file, "%s", reg2code(line->insn_line.rs2));          // 24-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", SRL_FUNCT3);                             // 14-12
                            fprintf(file, "%s", reg2code(line->insn_line.rd));           // 11-7
                        break;
                        case SRA:
                            fprintf(file, "%s", SRA_FUNCT7);                             // 31-25
                            fprintf(file, "%s", reg2code(line->insn_line.rs2));          // 24-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", SRA_FUNCT3);                             // 14-12
                            fprintf(file, "%s", reg2code(line->insn_line.rd));           // 11-7
                        break;
                        case SLT:
                            fprintf(file, "%s", SLT_FUNCT7);                             // 31-25
                            fprintf(file, "%s", reg2code(line->insn_line.rs2));          // 24-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", SLT_FUNCT3);                             // 14-12
                            fprintf(file, "%s", reg2code(line->insn_line.rd));           // 11-7
                        break;
                        case SLTU:
                            fprintf(file, "%s", SLTU_FUNCT7);                            // 31-25
                            fprintf(file, "%s", reg2code(line->insn_line.rs2));          // 24-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", SLTU_FUNCT3);                            // 14-12
                            fprintf(file, "%s", reg2code(line->insn_line.rd));           // 11-7
                        break;
                        default:

                        break;
                    }
                    fprintf(file, "%s\n", REGREG_OPCODE);                                // 6-0
                break;
                case TYPE_REGIMM:
                    switch (line->insn_line.insn.insn) {
                        case ADDI:
                            print_binary(file, line->insn_line.imm, 12);                 // 31-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", ADDI_FUNCT3);                            // 14-12
                            fprintf(file, "%s", reg2code(line->insn_line.rd));           // 11-7
                        break;
                        case ANDI:
                            print_binary(file, line->insn_line.imm, 12);                 // 31-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", ANDI_FUNCT3);                            // 14-12
                            fprintf(file, "%s", reg2code(line->insn_line.rd));           // 11-7
                        break;
                        case ORI:
                            print_binary(file, line->insn_line.imm, 12);                 // 31-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", ORI_FUNCT3);                             // 14-12
                            fprintf(file, "%s", reg2code(line->insn_line.rd));           // 11-7
                        break;
                        case XORI:
                            print_binary(file, line->insn_line.imm, 12);                 // 31-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", XORI_FUNCT3);                            // 14-12
                            fprintf(file, "%s", reg2code(line->insn_line.rd));           // 11-7
                        break;
                        case SLLI:
                            fprintf(file, "%s", SLLI_FUNCT7);                            // 31-25
                            print_binary(file, line->insn_line.imm, 5);                  // 24-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", SLLI_FUNCT3);                            // 14-12
                            fprintf(file, "%s", reg2code(line->insn_line.rd));           // 11-7
                        break;
                        case SRLI:
                            fprintf(file, "%s", SRLI_FUNCT7);                            // 31-25
                            print_binary(file, line->insn_line.imm, 5);                  // 24-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", SRLI_FUNCT3);                            // 14-12
                            fprintf(file, "%s", reg2code(line->insn_line.rd));           // 11-7
                        break;
                        case SRAI:
                            fprintf(file, "%s", SRAI_FUNCT7);                            // 31-25
                            print_binary(file, line->insn_line.imm, 5);                  // 24-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", SRAI_FUNCT3);                            // 14-12
                            fprintf(file, "%s", reg2code(line->insn_line.rd));           // 11-7
                        break;
                        case SLTI:
                            print_binary(file, line->insn_line.imm, 12);                 // 31-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", SLTI_FUNCT3);                            // 14-12
                            fprintf(file, "%s", reg2code(line->insn_line.rd));           // 11-7
                        break;
                        case SLTIU:
                            print_binary(file, line->insn_line.imm, 12);                 // 31-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", SLTIU_FUNCT3);                           // 14-12
                            fprintf(file, "%s", reg2code(line->insn_line.rd));           // 11-7
                        break;
                        default:

                        break;
                    }
                    fprintf(file, "%s\n", REGIMM_OPCODE);                                // 6-0
                break;
                case TYPE_BRANCH:
                    switch (line->insn_line.insn.insn) {
                        case BEQ:
                            fprintf(file, "%d", (line->insn_line.imm >> 12) & 1);        // 31
                            print_binary(file, (line->insn_line.imm >> 5) & 0x3F, 6);    // 30-25
                            fprintf(file, "%s", reg2code(line->insn_line.rs2));          // 24-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", BEQ_FUNCT3);                             // 14-12
                            print_binary(file, (line->insn_line.imm >> 1) & 0x0F, 4);    // 11-8
                            fprintf(file, "%d", (line->insn_line.imm >> 11) & 1);        // 7
                        break;
                        case BNE:
                            fprintf(file, "%d", (line->insn_line.imm >> 12) & 1);        // 31
                            print_binary(file, (line->insn_line.imm >> 5) & 0x3F, 6);    // 30-25
                            fprintf(file, "%s", reg2code(line->insn_line.rs2));          // 24-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", BNE_FUNCT3);                             // 14-12
                            print_binary(file, (line->insn_line.imm >> 1) & 0x0F, 4);    // 11-8
                            fprintf(file, "%d", (line->insn_line.imm >> 11) & 1);        // 7
                        break;
                        case BLT:
                            fprintf(file, "%d", (line->insn_line.imm >> 12) & 1);        // 31
                            print_binary(file, (line->insn_line.imm >> 5) & 0x3F, 6);    // 30-25
                            fprintf(file, "%s", reg2code(line->insn_line.rs2));          // 24-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", BLT_FUNCT3);                             // 14-12
                            print_binary(file, (line->insn_line.imm >> 1) & 0x0F, 4);    // 11-8
                            fprintf(file, "%d", (line->insn_line.imm >> 11) & 1);        // 7
                        break;
                        case BGE:
                            fprintf(file, "%d", (line->insn_line.imm >> 12) & 1);        // 31
                            print_binary(file, (line->insn_line.imm >> 5) & 0x3F, 6);    // 30-25
                            fprintf(file, "%s", reg2code(line->insn_line.rs2));          // 24-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", BGE_FUNCT3);                             // 14-12
                            print_binary(file, (line->insn_line.imm >> 1) & 0x0F, 4);    // 11-8
                            fprintf(file, "%d", (line->insn_line.imm >> 11) & 1);        // 7
                        break;
                        case BLTU:
                            fprintf(file, "%d", (line->insn_line.imm >> 12) & 1);        // 31
                            print_binary(file, (line->insn_line.imm >> 5) & 0x3F, 6);    // 30-25
                            fprintf(file, "%s", reg2code(line->insn_line.rs2));          // 24-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", BLTU_FUNCT3);                            // 14-12
                            print_binary(file, (line->insn_line.imm >> 1) & 0x0F, 4);    // 11-8
                            fprintf(file, "%d", (line->insn_line.imm >> 11) & 1);        // 7
                        break;
                        case BGEU:
                            fprintf(file, "%d", (line->insn_line.imm & 0x1000) >> 12);   // 31
                            print_binary(file, (line->insn_line.imm >> 5) & 0x3F, 6);    // 30-25
                            fprintf(file, "%s", reg2code(line->insn_line.rs2));          // 24-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", BGEU_FUNCT3);                            // 14-12
                            print_binary(file, (line->insn_line.imm >> 1) & 0x0F, 4);    // 11-8
                            fprintf(file, "%d", (line->insn_line.imm >> 11) & 1);        // 7
                        break;
                        default:

                        break;
                    }
                    fprintf(file, "%s\n", BRANCH_OPCODE);                                // 6-0
                break;
                case TYPE_LOAD:
                    switch (line->insn_line.insn.insn) {
                        case LB:
                            print_binary(file, line->insn_line.imm, 12);                 // 31-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", LB_FUNCT3);                              // 14-12
                            fprintf(file, "%s", reg2code(line->insn_line.rd));           // 11-7
                        break;
                        case LH:
                            print_binary(file, line->insn_line.imm, 12);                 // 31-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", LH_FUNCT3);                              // 14-12
                            fprintf(file, "%s", reg2code(line->insn_line.rd));           // 11-7
                        break;
                        case LW:
                            print_binary(file, line->insn_line.imm, 12);                 // 31-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", LW_FUNCT3);                              // 14-12
                            fprintf(file, "%s", reg2code(line->insn_line.rd));           // 11-7
                        break;
                        case LBU:
                            print_binary(file, line->insn_line.imm, 12);                 // 31-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", LBU_FUNCT3);                             // 14-12
                            fprintf(file, "%s", reg2code(line->insn_line.rd));           // 11-7
                        break;
                        case LHU:
                            print_binary(file, line->insn_line.imm, 12);                 // 31-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", LHU_FUNCT3);                             // 14-12
                            fprintf(file, "%s", reg2code(line->insn_line.rd));           // 11-7
                        break;
                        default:

                        break;
                    }
                    fprintf(file, "%s\n", LOAD_OPCODE);                                  // 6-0
                break;
                case TYPE_STORE:
                    switch (line->insn_line.insn.insn) {
                        case SB:
                            print_binary(file, (line->insn_line.imm >> 5), 7);           // 31-25
                            fprintf(file, "%s", reg2code(line->insn_line.rs2));          // 24-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", SB_FUNCT3);                              // 14-12
                            print_binary(file, line->insn_line.imm & 0x1F, 5);           // 11-7
                        break;
                        case SH:
                            print_binary(file, (line->insn_line.imm >> 5), 7);           // 31-25
                            fprintf(file, "%s", reg2code(line->insn_line.rs2));          // 24-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", SH_FUNCT3);                              // 14-12
                            print_binary(file, line->insn_line.imm & 0x1F, 5);           // 11-7
                        break;
                        case SW:
                            print_binary(file, (line->insn_line.imm >> 5), 7);           // 31-25
                            fprintf(file, "%s", reg2code(line->insn_line.rs2));          // 24-20
                            fprintf(file, "%s", reg2code(line->insn_line.rs1));          // 19-15
                            fprintf(file, "%s", SW_FUNCT3);                              // 14-12
                            print_binary(file, line->insn_line.imm & 0x1F, 5);           // 11-7
                        break;
                        default:

                        break;
                    }
                    fprintf(file, "%s\n", STORE_OPCODE);                                 // 6-0
                break;
                case TYPE_JAL:/*
                    fprintf(file, "%d", (line->insn_line.imm & 0x40000) >> 20);          // 31
                    print_binary(file, (line->insn_line.imm >> 1) & 0x3FF, 10);          // 30-21
                    fprintf(file, "%d", (line->insn_line.imm & 0x800) >> 11);            // 20
                    print_binary(file, (line->insn_line.imm & 0x7F800) >> 12, 8);        // 19-12
                    fprintf(file, "%s", reg2code(line->insn_line.rd));                   // 11-7
                    fprintf(file, "%s\n", JAL_OPCODE);                                   // 6-0*/
                    fprintf(file, "%d", (line->insn_line.imm >> 20) & 1);                // 31
                    print_binary(file,  (line->insn_line.imm >> 1 ) & 0x3FF, 10);        // 30-21
                    fprintf(file, "%d", (line->insn_line.imm >> 11) & 1);                // 20
                    print_binary(file,  (line->insn_line.imm >> 12) & 0xFF, 8);          // 19-12
                    fprintf(file, "%s", reg2code(line->insn_line.rd));                   // 11-7
                    fprintf(file, "%s\n", JAL_OPCODE);                                   // 6-0
                break;
                case TYPE_JALR:
                    print_binary(file, line->insn_line.imm, 12);                         // 31-20
                    fprintf(file, "%s", reg2code(line->insn_line.rs1));                  // 19-15
                    fprintf(file, "%s", JALR_FUNCT3);                                    // 14-12
                    fprintf(file, "%s", reg2code(line->insn_line.rd));                   // 11-7
                    fprintf(file, "%s\n", JALR_OPCODE);                                  // 6-0
                break;
                case TYPE_LUI:
                    print_binary(file, line->insn_line.imm >> 12, 20);                   // 31-12
                    fprintf(file, "%s", reg2code(line->insn_line.rd));                   // 11-7
                    fprintf(file, "%s\n", LUI_OPCODE);                                   // 6-0
                break;
                case TYPE_AUIPC:
                    print_binary(file, line->insn_line.imm >> 12, 20);                   // 31-12
                    fprintf(file, "%s", reg2code(line->insn_line.rd));                   // 11-7
                    fprintf(file, "%s\n", AUIPC_OPCODE);                                 // 6-0
                break;
                default:

                break;
            }
        }
    }

    fclose(file);

    return 0;
}

int asm_line_print(void* asm_line) {
    asm_line_t* line = (asm_line_t*)asm_line;
    printf("----------\n");
    printf("Type : %s", line->type == INSN_LINE ? "INSN_LINE\n" : "LABEL_LINE\n");
    if (line->type == INSN_LINE) {
        printf("Instruction : %d (%d)\n", line->insn_line.insn.insn, line->insn_line.insn.type);
        printf("Rd : %d\n", line->insn_line.rd);
        printf("Rs1 : %d\n", line->insn_line.rs1);
        printf("Rs2 : %d\n", line->insn_line.rs2);
        printf("Imm : %d\n", line->insn_line.imm);
        printf("Label : "); string_print(line->insn_line.label); printf("\n");
        printf("Address : %d\n", line->insn_line.line_addr);
    } else {
        printf("Label : "); string_print(line->label.name); printf("\n");
        printf("Address : %d\n", line->label.line_addr);
    }
    return 0;
}

int asm_line_print_pretty(void* asm_line) {

    asm_line_t* line = (asm_line_t*)asm_line;

    char** insn_name = calloc(INSN_COUNT, sizeof(*insn_name));
    insn_name[0] = "nop";
    insn_name[1] = "add";
    insn_name[2] = "and";
    insn_name[3] = "sll";
    insn_name[4] = "srl";
    insn_name[5] = "or";
    insn_name[6] = "xor";
    insn_name[7] = "sltu";
    insn_name[8] = "slt";
    insn_name[9] = "sra";
    insn_name[10] = "sub";
    insn_name[11] = "addi";
    insn_name[12] = "andi";
    insn_name[13] = "slli";
    insn_name[14] = "srli";
    insn_name[15] = "ori";
    insn_name[16] = "xori";
    insn_name[17] = "sltiu";
    insn_name[18] = "slti";
    insn_name[19] = "srai";
    insn_name[20] = "beq";
    insn_name[21] = "bne";
    insn_name[22] = "bgeu";
    insn_name[23] = "bge";
    insn_name[24] = "bltu";
    insn_name[25] = "blt";
    insn_name[26] = "lui";
    insn_name[27] = "auipc";
    insn_name[28] = "lbu";
    insn_name[29] = "lhu";
    insn_name[30] = "lb";
    insn_name[31] = "lh";
    insn_name[32] = "lw";
    insn_name[33] = "sb";
    insn_name[34] = "sw";
    insn_name[35] = "sh";
    insn_name[36] = "jal";
    insn_name[37] = "jalr";

    char** regname = malloc(32 * sizeof(char*));
    regname[0] = "zero";
    regname[1] = "ra";
    regname[2] = "sp";
    regname[3] = "gp";
    regname[4] = "tp";
    regname[5] = "t0";
    regname[6] = "t1";
    regname[7] = "t2";
    regname[8] = "fp";
    regname[9] = "s1";
    regname[10] = "a0";
    regname[11] = "a1";
    regname[12] = "a2";
    regname[13] = "a3";
    regname[14] = "a4";
    regname[15] = "a5";
    regname[16] = "a6";
    regname[17] = "a7";
    regname[18] = "s2";
    regname[19] = "s3";
    regname[20] = "s4";
    regname[21] = "s5";
    regname[22] = "s6";
    regname[23] = "s7";
    regname[24] = "s8";
    regname[25] = "s9";
    regname[26] = "s10";
    regname[27] = "s11";
    regname[28] = "t3";
    regname[29] = "t4";
    regname[30] = "t5";
    regname[31] = "t6";
    
    if (line->type == INSN_LINE) {
        STYLE(stderr, COLOR_GREEN, STYLE_REGULAR);
        fprintf(stderr, "%05d ", line->insn_line.line_addr);
        STYLE(stderr, COLOR_CYAN, STYLE_REGULAR);
        fprintf(stderr, "%s\t", insn_name[line->insn_line.insn.insn]);
        switch (line->insn_line.insn.type) {
            case TYPE_NOP:
                printf("\n");
            break;
            case TYPE_REGREG:
                STYLE_RESET(stderr);
                fprintf(stderr, "%s,%s,%s\n", regname[line->insn_line.rd], regname[line->insn_line.rs1], regname[line->insn_line.rs2]);
            break;
            case TYPE_REGIMM:
                STYLE_RESET(stderr);
                fprintf(stderr, "%s,%s,", regname[line->insn_line.rd], regname[line->insn_line.rs1]);
                STYLE(stderr, COLOR_YELLOW, STYLE_HIGH_INTENSITY_TEXT);
                fprintf(stderr, "%d\n", line->insn_line.imm);
            break;
            case TYPE_LOAD:
                STYLE_RESET(stderr);
                fprintf(stderr, "%s,", regname[line->insn_line.rd]);
                STYLE(stderr, COLOR_YELLOW, STYLE_HIGH_INTENSITY_TEXT);
                fprintf(stderr, "%d", line->insn_line.imm);
                STYLE_RESET(stderr);
                fprintf(stderr, "(%s)\n", regname[line->insn_line.rs1]);
            break;
            case TYPE_STORE:
                STYLE_RESET(stderr);
                fprintf(stderr, "%s,", regname[line->insn_line.rs2]);
                STYLE(stderr, COLOR_YELLOW, STYLE_HIGH_INTENSITY_TEXT);
                fprintf(stderr, "%d", line->insn_line.imm);
                STYLE_RESET(stderr);
                fprintf(stderr, "(%s)\n", regname[line->insn_line.rs1]);
            break;
            case TYPE_BRANCH:
                STYLE_RESET(stderr);
                fprintf(stderr, "%s,%s,", regname[line->insn_line.rs1], regname[line->insn_line.rs2]);
                STYLE(stderr, COLOR_MAGENTA, STYLE_HIGH_INTENSITY_TEXT);
                string_print(line->insn_line.label);
                STYLE(stderr, COLOR_GREEN, STYLE_REGULAR);
                fprintf(stderr, "\t%d ", line->insn_line.imm);
                printf("\n");
            break;
            case TYPE_JAL:
                STYLE_RESET(stderr);
                fprintf(stderr, "%s,", regname[line->insn_line.rd]);
                STYLE(stderr, COLOR_MAGENTA, STYLE_HIGH_INTENSITY_TEXT);
                string_print(line->insn_line.label);
                STYLE(stderr, COLOR_GREEN, STYLE_REGULAR);
                fprintf(stderr, "\t%d ", line->insn_line.imm);
                printf("\n");
            break;
            case TYPE_JALR:
                STYLE_RESET(stderr);
                fprintf(stderr, "%s,%s,", regname[line->insn_line.rd], regname[line->insn_line.rs1]);
                STYLE(stderr, COLOR_YELLOW, STYLE_HIGH_INTENSITY_TEXT);
                fprintf(stderr, "%d\n", line->insn_line.imm);
            break;
            case TYPE_LUI:
                STYLE_RESET(stderr);
                fprintf(stderr, "%s,", regname[line->insn_line.rd]);
                STYLE(stderr, COLOR_YELLOW, STYLE_HIGH_INTENSITY_TEXT);
                fprintf(stderr, "%d\n", line->insn_line.imm);
            break;
            case TYPE_AUIPC:
                STYLE_RESET(stderr);
                fprintf(stderr, "%s,", regname[line->insn_line.rd]);
                STYLE(stderr, COLOR_YELLOW, STYLE_HIGH_INTENSITY_TEXT);
                fprintf(stderr, "%d\n", line->insn_line.imm);
            break;
            case TYPE_UNDEF:
                printf("UNDEFINED\n");
            break;
        }
    }
    else {
        STYLE_RESET(stderr);
        printf("      ");
        STYLE(stderr, COLOR_MAGENTA, STYLE_HIGH_INTENSITY_BACKGROUND);
        string_print(line->label.name);
        printf(":");
        STYLE_RESET(stderr);
        printf("\n");
    }
    STYLE_RESET(stderr);

    free(insn_name);
    free(regname);

    return 0;
}

int asm_line_free(void* asm_line) {
    free(asm_line);
    return 0;
}

int asm_line_sim(list_t* insn_list, unsigned int mem_size) {
    //========== Définition des rescources
    unsigned int regfile[REG_COUNT];
    unsigned char* mem = calloc(mem_size, sizeof(*mem));
    int pc = 0;
    int next_pc = 0;
    int nb_tests = 0;

    //========== Initialisation des rescources
    for (int i = 0; i < REG_COUNT; i=i+1)
        regfile[i] = 0;
    
    for (unsigned int i = 0; i < mem_size; i=i+1)
        mem[i] = MEM_DEFAULT_VALUE;
    
    //========== Simulation
    //----- Fetch
    asm_line_t* line = NULL;
    list_t l;
    int interpreted_imm = 0;             // Immediate value interpreted as a signed integer

    for (int clk = 0; clk < MAX_SIM_CYCLES; clk=clk+1) {
        // Find the instruction at the current pc
        pc = next_pc;
        l = *insn_list;
        if (!list_empty(l)) line = list_first(l);
        while (!list_empty(l) && (line->type != INSN_LINE || line->insn_line.line_addr != pc)) {
            l = list_next(l);
            if (!list_empty(l)) line = list_first(l);
        }
        // If no instruction at the current pc, print a warning and return
        if (line->type != INSN_LINE || line->insn_line.line_addr != pc) {
            asm_line_sim_print(PRINT_SIM_WARN, regfile, pc, line, "No instruction at address 0x%08x\n", pc);
            free(mem);
            return 0;
        }
        // If we reach the end of the program, print a info and return
        if (line->type == INSN_LINE && line->insn_line.insn.insn == JALR && line->insn_line.rs1 == R0 && line->insn_line.imm == 0) {
            asm_line_sim_print(PRINT_SIM_INFO, regfile, pc, NULL, "End of program\n");
            print_registers(regfile, pc);
            asm_line_sim_print(PRINT_SIM_INFO, regfile, pc, NULL, "Number of tests : %d\n", nb_tests);
            free(mem);
            return 0;
        }

        next_pc = pc + 4;
        
        // Process interpretation of immediate values (reproduce the behavior of the ImmSel block)
        interpreted_imm = line->insn_line.imm & 0xFFF;
        if (interpreted_imm & 0x800) interpreted_imm = line->insn_line.imm | 0xFFFFF000;

        //----- Decode & Execution
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wsign-compare"

        // printf("clk = %d\tpc = %d\n", clk, pc);

        switch (line->insn_line.insn.insn) {
            case NOP:

            break;
            case ADD:
                regfile[line->insn_line.rd] = regfile[line->insn_line.rs1] + regfile[line->insn_line.rs2];
            break;
            case SUB:
                regfile[line->insn_line.rd] = regfile[line->insn_line.rs1] - regfile[line->insn_line.rs2];
            break;
            case AND:
                regfile[line->insn_line.rd] = regfile[line->insn_line.rs1] & regfile[line->insn_line.rs2];
            break;
            case SLL:
                regfile[line->insn_line.rd] = regfile[line->insn_line.rs1] << regfile[line->insn_line.rs2];
            break;
            case SRL:
                regfile[line->insn_line.rd] = regfile[line->insn_line.rs1] >> regfile[line->insn_line.rs2];
            break;
            case OR:
                regfile[line->insn_line.rd] = regfile[line->insn_line.rs1] | regfile[line->insn_line.rs2];
            break;
            case XOR:
                regfile[line->insn_line.rd] = regfile[line->insn_line.rs1] ^ regfile[line->insn_line.rs2];
            break;
            case SLTU:
                regfile[line->insn_line.rd] = regfile[line->insn_line.rs1] < regfile[line->insn_line.rs2];
            break;
            case SLT:
                regfile[line->insn_line.rd] = regfile[line->insn_line.rs1] < (int)regfile[line->insn_line.rs2];
            break;
            case SRA:
                regfile[line->insn_line.rd] = (int)regfile[line->insn_line.rs1] >> regfile[line->insn_line.rs2];
            break;
            case ADDI:
                regfile[line->insn_line.rd] = regfile[line->insn_line.rs1] + interpreted_imm;
            break;
            case ANDI:
                regfile[line->insn_line.rd] = regfile[line->insn_line.rs1] & interpreted_imm;
            break;
            case SLLI:
                regfile[line->insn_line.rd] = regfile[line->insn_line.rs1] << interpreted_imm;
            break;
            case SRLI:
                regfile[line->insn_line.rd] = regfile[line->insn_line.rs1] >> interpreted_imm;
            break;
            case ORI:
                regfile[line->insn_line.rd] = regfile[line->insn_line.rs1] | interpreted_imm;
            break;
            case XORI:
                regfile[line->insn_line.rd] = regfile[line->insn_line.rs1] ^ interpreted_imm;
            break;
            case SLTIU:
                regfile[line->insn_line.rd] = regfile[line->insn_line.rs1] < interpreted_imm;
            break;
            case SLTI:
                regfile[line->insn_line.rd] = regfile[line->insn_line.rs1] < (int)interpreted_imm;
            break;
            case SRAI:
                regfile[line->insn_line.rd] = (int)regfile[line->insn_line.rs1] >> interpreted_imm;
            break;
            case BEQ:
                if (regfile[line->insn_line.rs1] == regfile[line->insn_line.rs2]) {
                    next_pc = pc + interpreted_imm;
                    clk = clk + 4;           // +4 because of the time for the processor to jump
                }
            break;
            case BNE:
                if (regfile[line->insn_line.rs1] != regfile[line->insn_line.rs2]) {
                    next_pc = pc + interpreted_imm;
                    clk = clk + 4;           // +4 because of the time for the processor to jump
                }
            break;
            case BLTU:
                if (regfile[line->insn_line.rs1] < regfile[line->insn_line.rs2]) {
                    next_pc = pc + interpreted_imm;
                    clk = clk + 4;           // +4 because of the time for the processor to jump
                }
            break;
            case BLT:
                if (regfile[line->insn_line.rs1] < (int)regfile[line->insn_line.rs2]) {
                    next_pc = pc + interpreted_imm;
                    clk = clk + 4;           // +4 because of the time for the processor to jump
                }
            break;
            case BGEU:
                if (regfile[line->insn_line.rs1] >= regfile[line->insn_line.rs2]) {
                    next_pc = pc + interpreted_imm;
                    clk = clk + 4;           // +4 because of the time for the processor to jump
                }
            break;
            case BGE:
                if (regfile[line->insn_line.rs1] >= (int)regfile[line->insn_line.rs2]) {
                    next_pc = pc + interpreted_imm;
                    clk = clk + 4;           // +4 because of the time for the processor to jump
                }
            break;
            case LUI:
                regfile[line->insn_line.rd] = line->insn_line.imm & 0xFFFFF000;
            break;
            case AUIPC:
                // +8 because of the time for the processor to process the instruction
                regfile[line->insn_line.rd] = pc + (line->insn_line.imm & 0xFFFFF000);
            break;
            case LBU:
                if (regfile[line->insn_line.rs1] + interpreted_imm < mem_size &&
                    (int)regfile[line->insn_line.rs1] + (int)interpreted_imm >= 0)
                    regfile[line->insn_line.rd] = mem[regfile[line->insn_line.rs1] + interpreted_imm] & 0xFF;
                else {
                    asm_line_sim_print(
                        PRINT_SIM_ERR, 
                        regfile, 
                        pc, 
                        line, 
                        "Memory out of bounds : Read of %d bytes @ 0x%08x\n", 
                        1, 
                        regfile[line->insn_line.rs1] + interpreted_imm
                    );
                    free(mem);
                    return -1;
                }
            break;
            case LHU:
                if (regfile[line->insn_line.rs1] + interpreted_imm + 1 < mem_size &&
                    (int)regfile[line->insn_line.rs1] + (int)interpreted_imm     >= 0)
                    regfile[line->insn_line.rd] = (mem[regfile[line->insn_line.rs1] + interpreted_imm] + 
                                                  (mem[regfile[line->insn_line.rs1] + interpreted_imm  + 1] << 8)) & 0xFFFF;
                else {
                    asm_line_sim_print(
                        PRINT_SIM_ERR, 
                        regfile, 
                        pc, 
                        line, 
                        "Memory out of bounds : Read of %d bytes @ 0x%08x\n", 
                        2, 
                        regfile[line->insn_line.rs1] + interpreted_imm
                    );
                    free(mem);
                    return -1;
                }
            break;
            case LB:
                if (regfile[line->insn_line.rs1] + interpreted_imm < mem_size &&
                    (int)regfile[line->insn_line.rs1] + (int)interpreted_imm >= 0) {
                    regfile[line->insn_line.rd] = (mem[regfile[line->insn_line.rs1] + interpreted_imm] |
                                                  (mem[regfile[line->insn_line.rs1] + interpreted_imm] & 0x80 ? 0xFFFFFF00 : 0)) & 0xFF;
                }
                else {
                    asm_line_sim_print(
                        PRINT_SIM_ERR, 
                        regfile, 
                        pc, 
                        line, 
                        "Memory out of bounds : Read of %d bytes @ 0x%08x\n", 
                        1, 
                        regfile[line->insn_line.rs1] + interpreted_imm
                    );
                    free(mem);
                    return -1;
                }
            break;
            case LH:
                if (regfile[line->insn_line.rs1] + interpreted_imm + 1 < mem_size &&
                    (int)regfile[line->insn_line.rs1] + (int)interpreted_imm     >= 0) {
                    regfile[line->insn_line.rd] = ((mem[regfile[line->insn_line.rs1] + interpreted_imm] + 
                                                   (mem[regfile[line->insn_line.rs1] + interpreted_imm  + 1] << 8)) |
                                                   (mem[regfile[line->insn_line.rs1] + interpreted_imm  + 1] & 0x80 ? 0xFFFF0000 : 0)) & 0xFFFF;
                }
                else {
                    asm_line_sim_print(
                        PRINT_SIM_ERR, 
                        regfile, 
                        pc, 
                        line, 
                        "Memory out of bounds : Read of %d bytes @ 0x%08x\n", 
                        2, 
                        regfile[line->insn_line.rs1] + interpreted_imm
                    );
                    free(mem);
                    return -1;
                }
            break;
            case LW:
                if (regfile[line->insn_line.rs1] + interpreted_imm + 3 < mem_size &&
                    (int)regfile[line->insn_line.rs1] + (int)interpreted_imm     >= 0) {
                    regfile[line->insn_line.rd] = (mem[regfile[line->insn_line.rs1] + interpreted_imm] + 
                                                  (mem[regfile[line->insn_line.rs1] + interpreted_imm  + 1] << 8 ) + 
                                                  (mem[regfile[line->insn_line.rs1] + interpreted_imm  + 2] << 16) + 
                                                  (mem[regfile[line->insn_line.rs1] + interpreted_imm  + 3] << 24));
                }
                else {
                    asm_line_sim_print(
                        PRINT_SIM_ERR, 
                        regfile, 
                        pc, 
                        line, 
                        "Memory out of bounds : Read of %d bytes @ 0x%08x\n", 
                        4, 
                        regfile[line->insn_line.rs1] + interpreted_imm
                    );
                    free(mem);
                    return -1;
                }
            break;
            case SB:
                if (regfile[line->insn_line.rs1] + interpreted_imm < mem_size &&
                    (int)regfile[line->insn_line.rs1] + (int)interpreted_imm >= 0) {
                    mem[regfile[line->insn_line.rs1] + interpreted_imm] = regfile[line->insn_line.rs2] & 0xFF;
                    print_test_bench(
                        clk,
                        pc,
                        line,
                        regfile[line->insn_line.rs1] + interpreted_imm,
                        8,
                        regfile[line->insn_line.rs2],
                        &nb_tests
                    );
                }
                else {
                    asm_line_sim_print(
                        PRINT_SIM_ERR, 
                        regfile, 
                        pc, 
                        line, 
                        "Memory out of bounds : Write of %d bytes @ 0x%08x\n", 
                        1, 
                        regfile[line->insn_line.rs1] + interpreted_imm
                    );
                    free(mem);
                    return -1;
                }
            break;
            case SH:
                if (regfile[line->insn_line.rs1] + interpreted_imm + 1 < mem_size &&
                    (int)regfile[line->insn_line.rs1] + (int)interpreted_imm     >= 0) {
                    mem[regfile[line->insn_line.rs1] + interpreted_imm]     =  regfile[line->insn_line.rs2]       & 0xFF;
                    mem[regfile[line->insn_line.rs1] + interpreted_imm + 1] = (regfile[line->insn_line.rs2] >> 8) & 0xFF;
                    print_test_bench(
                        clk,
                        pc,
                        line,
                        regfile[line->insn_line.rs1] + interpreted_imm,
                        16,
                        regfile[line->insn_line.rs2],
                        &nb_tests
                    );
                }
                else {
                    asm_line_sim_print(
                        PRINT_SIM_ERR, 
                        regfile, 
                        pc, 
                        line, 
                        "Memory out of bounds : Write of %d bytes @ 0x%08x\n", 
                        2, 
                        regfile[line->insn_line.rs1] + interpreted_imm
                    );
                    free(mem);
                    return -1;
                }
            break;
            case SW:
                if (regfile[line->insn_line.rs1] + interpreted_imm + 3 < mem_size &&
                    (int)regfile[line->insn_line.rs1] + (int)interpreted_imm     >= 0) {
                    mem[regfile[line->insn_line.rs1] + interpreted_imm]     =  regfile[line->insn_line.rs2]        & 0xFF;
                    mem[regfile[line->insn_line.rs1] + interpreted_imm + 1] = (regfile[line->insn_line.rs2] >> 8 ) & 0xFF;
                    mem[regfile[line->insn_line.rs1] + interpreted_imm + 2] = (regfile[line->insn_line.rs2] >> 16) & 0xFF;
                    mem[regfile[line->insn_line.rs1] + interpreted_imm + 3] = (regfile[line->insn_line.rs2] >> 24) & 0xFF;
                    print_test_bench(
                        clk,
                        pc,
                        line,
                        regfile[line->insn_line.rs1] + interpreted_imm,
                        32,
                        regfile[line->insn_line.rs2],
                        &nb_tests
                    );
                }
                else {
                    asm_line_sim_print(
                        PRINT_SIM_ERR, 
                        regfile, 
                        pc, 
                        line, 
                        "Memory out of bounds : Write of %d bytes @ 0x%08x\n", 
                        4, 
                        regfile[line->insn_line.rs1] + interpreted_imm
                    );
                    free(mem);
                    return -1;
                }
            break;
            case JAL:
                regfile[line->insn_line.rd] = next_pc;
                clk = clk + 4;           // +4 because of the time for the processor to jump
                next_pc = pc + interpreted_imm;
            break;
            case JALR:
                regfile[line->insn_line.rd] = next_pc;
                clk = clk + 4;           // +4 because of the time for the processor to jump
                next_pc = regfile[line->insn_line.rs1] + interpreted_imm;
            break;
            default:
                asm_line_sim_print(
                    PRINT_SIM_ERR, 
                    regfile, 
                    pc, 
                    line, 
                    "Unknown instruction\n"
                );
            break;
        }
        regfile[0] = 0;                  // Register 0 is hardwired to 0
    }
    #pragma GCC diagnostic pop

    // PRINT_SIM_WARN(regfile, pc, "Maximum number of cycles reached\n")
    asm_line_sim_print(
        PRINT_SIM_WARN, 
        regfile, 
        pc, 
        NULL, 
        "Maximum number of cycles reached\n"
    );

    free(mem);
    return 0;
}

void asm_line_sim_print(print_type_t print_type, unsigned int regfile[REG_COUNT], int pc, asm_line_t* asm_line, const char* format, ...) {
    printf("\n");
    switch (print_type) {
        case PRINT_SIM_ERR:
            STYLE(stderr, COLOR_RED, STYLE_REGULAR);
            fprintf(stderr, "[SIM ERROR] ");
        break;
        case PRINT_SIM_WARN:
            STYLE(stderr, COLOR_YELLOW, STYLE_REGULAR);
            fprintf(stderr, "[SIM WARNING] ");
        break;
        case PRINT_SIM_INFO:
            STYLE(stderr, COLOR_BLUE, STYLE_HIGH_INTENSITY_TEXT);
            fprintf(stderr, "[SIM INFO] ");
        break;
        default:
            STYLE(stderr, COLOR_WHITE, STYLE_REGULAR);
            fprintf(stderr, "[SIM] ");
        break;
    }
    STYLE(stderr, COLOR_WHITE, STYLE_BOLD);

    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    printf("\n");
    STYLE_RESET(stderr);

    if (print_type != PRINT_SIM_INFO) {
        if (asm_line) {
            asm_line_print_pretty(asm_line);
        }
        print_registers(regfile, pc);
    }
}

void print_test_bench(int clock_number, int pc, asm_line_t* asm_line, unsigned int adress, char data_size, unsigned int data, int* nb_tests) {
    switch (asm_line->insn_line.insn.insn) {
        case SB : printf("'{\"PC = %d : SB", pc); break;
        case SH : printf("'{\"PC = %d : SH", pc); break;
        case SW : printf("'{\"PC = %d : SW", pc); break;
        default : printf("'{\"PC = %d :   ", pc); break;
    }
    printf("\", %d, %d, %d, 32'h%08x},\t\t// ", clock_number, adress, data_size, data);
    asm_line_print_pretty(asm_line);
    *nb_tests = *nb_tests + 1;
}

void print_registers(unsigned int regfile[REG_COUNT], int pc) {
    char** regname = malloc(32 * sizeof(char*));
    regname[0] = "zero";
    regname[1] = "ra";
    regname[2] = "sp";
    regname[3] = "gp";
    regname[4] = "tp";
    regname[5] = "t0";
    regname[6] = "t1";
    regname[7] = "t2";
    regname[8] = "s0/fp";
    regname[9] = "s1";
    regname[10] = "a0";
    regname[11] = "a1";
    regname[12] = "a2";
    regname[13] = "a3";
    regname[14] = "a4";
    regname[15] = "a5";
    regname[16] = "a6";
    regname[17] = "a7";
    regname[18] = "s2";
    regname[19] = "s3";
    regname[20] = "s4";
    regname[21] = "s5";
    regname[22] = "s6";
    regname[23] = "s7";
    regname[24] = "s8";
    regname[25] = "s9";
    regname[26] = "s10";
    regname[27] = "s11";
    regname[28] = "t3";
    regname[29] = "t4";
    regname[30] = "t5";
    regname[31] = "t6";

    printf("\n============= Registers =============\n");
    printf("ID\t| Name\t| Hex\t\tDec\n");
    printf("-------------------------------------\n");
    printf("x\t| pc\t| 0x%08x\t%d\n", pc, pc);
    for (int i = 0; i < 32; i=i+1) {
        printf("%d\t| %s\t| 0x%08x\t%d\n", i, regname[i], regfile[i], regfile[i]);
    }

    free(regname);
}