#include <stdio.h>
#include <string.h>

#ifdef BSD
	#include <net/bpf.h>
#endif
/*
 * Instruction classes
 */

#define BPF_CLASS(code) ((code) & 0x07)
#define         BPF_LD          0x00
#define         BPF_LDX         0x01
#define         BPF_ST          0x02
#define         BPF_STX         0x03
#define         BPF_ALU         0x04
#define         BPF_JMP         0x05
#define         BPF_RET         0x06
#define         BPF_MISC        0x07

/* ld/ldx fields */
#define BPF_SIZE(code)  ((code) & 0x18)
#define         BPF_W           0x00
#define         BPF_H           0x08
#define         BPF_B           0x10
#define BPF_MODE(code)  ((code) & 0xe0)
#define         BPF_IMM         0x00
#define         BPF_ABS         0x20
#define         BPF_IND         0x40
#define         BPF_MEM         0x60
#define         BPF_LEN         0x80
#define         BPF_MSH         0xa0

/* alu/jmp fields */
#define BPF_OP(code)    ((code) & 0xf0)
#define         BPF_ADD         0x00
#define         BPF_SUB         0x10
#define         BPF_MUL         0x20
#define         BPF_DIV         0x30
#define         BPF_OR          0x40
#define         BPF_AND         0x50
#define         BPF_LSH         0x60
#define         BPF_RSH         0x70
#define         BPF_NEG         0x80
#define         BPF_MOD         0x90
#define         BPF_XOR         0xa0

#define         BPF_JA          0x00
#define         BPF_JEQ         0x10
#define         BPF_JGT         0x20
#define         BPF_JGE         0x30
#define         BPF_JSET        0x40
#define BPF_SRC(code)   ((code) & 0x08)
#define         BPF_K           0x00
#define         BPF_X           0x08

/* ret - BPF_K and BPF_X also apply */
#define BPF_RVAL(code)  ((code) & 0x18)
#define         BPF_A           0x10
 
/* misc */
#define BPF_MISCOP(code) ((code) & 0xf8)
#define         BPF_TAX         0x00
#define         BPF_TXA         0x80

#ifndef BPF_MAXINSNS
#define BPF_MAXINSNS 4096
#endif

// from https://github.com/01org/prd/blob/master/tools/net/bpf_dbg.c
 
#define BPF_LDX_B	(BPF_LDX | BPF_B)
#define BPF_LDX_W	(BPF_LDX | BPF_W)
#define BPF_JMP_JA	(BPF_JMP | BPF_JA)
#define BPF_JMP_JEQ	(BPF_JMP | BPF_JEQ)
#define BPF_JMP_JGT	(BPF_JMP | BPF_JGT)
#define BPF_JMP_JGE	(BPF_JMP | BPF_JGE)
#define BPF_JMP_JSET	(BPF_JMP | BPF_JSET)
#define BPF_ALU_ADD	(BPF_ALU | BPF_ADD)
#define BPF_ALU_SUB	(BPF_ALU | BPF_SUB)
#define BPF_ALU_MUL	(BPF_ALU | BPF_MUL)
#define BPF_ALU_DIV	(BPF_ALU | BPF_DIV)
#define BPF_ALU_MOD	(BPF_ALU | BPF_MOD)
#define BPF_ALU_NEG	(BPF_ALU | BPF_NEG)
#define BPF_ALU_AND	(BPF_ALU | BPF_AND)
#define BPF_ALU_OR	(BPF_ALU | BPF_OR)
#define BPF_ALU_XOR	(BPF_ALU | BPF_XOR)
#define BPF_ALU_LSH	(BPF_ALU | BPF_LSH)
#define BPF_ALU_RSH	(BPF_ALU | BPF_RSH)
#define BPF_MISC_TAX	(BPF_MISC | BPF_TAX)
#define BPF_MISC_TXA	(BPF_MISC | BPF_TXA)
#define BPF_LD_B	(BPF_LD | BPF_B)
#define BPF_LD_H	(BPF_LD | BPF_H)
#define BPF_LD_W	(BPF_LD | BPF_W)

#define OP(_op, _name)      [_op] = _name

static const char * const op_table[] = {
	OP(BPF_ST, "st"),
	OP(BPF_STX, "stx"),
	OP(BPF_LD_B, "ldb"),
	OP(BPF_LD_H, "ldh"),
	OP(BPF_LD_W, "ld"),
	OP(BPF_LDX, "ldx"),
	OP(BPF_LDX_B, "ldxb"),
	OP(BPF_JMP_JA, "ja"),
	OP(BPF_JMP_JEQ, "jeq"),
	OP(BPF_JMP_JGT, "jgt"),
	OP(BPF_JMP_JGE, "jge"),
	OP(BPF_JMP_JSET, "jset"),
	OP(BPF_ALU_ADD, "add"),
	OP(BPF_ALU_SUB, "sub"),
	OP(BPF_ALU_MUL, "mul"),
	OP(BPF_ALU_DIV, "div"),
	OP(BPF_ALU_MOD, "mod"),
	OP(BPF_ALU_NEG, "neg"),
	OP(BPF_ALU_AND, "and"),
	OP(BPF_ALU_OR, "or"),
	OP(BPF_ALU_XOR, "xor"),
	OP(BPF_ALU_LSH, "lsh"),
	OP(BPF_ALU_RSH, "rsh"),
	OP(BPF_MISC_TAX, "tax"),
	OP(BPF_MISC_TXA, "txa"),
	OP(BPF_RET, "ret"),
};

static void bpf_disasm(int i[4])
{
	const char *op;

	switch (i[0]) {
	case BPF_RET | BPF_K:
		op = op_table[BPF_RET];
		break;
	case BPF_RET | BPF_A:
		op = op_table[BPF_RET];
		break;
	case BPF_RET | BPF_X:
		op = op_table[BPF_RET];
		break;
	case BPF_MISC_TAX:
		op = op_table[BPF_MISC_TAX];
		break;
	case BPF_MISC_TXA:
		op = op_table[BPF_MISC_TXA];
		break;
	case BPF_ST:
		op = op_table[BPF_ST];
		break;
	case BPF_STX:
		op = op_table[BPF_STX];
		break;
	case BPF_LD_W | BPF_ABS:
		op = op_table[BPF_LD_W];
		break;
	case BPF_LD_H | BPF_ABS:
		op = op_table[BPF_LD_H];
		break;
	case BPF_LD_B | BPF_ABS:
		op = op_table[BPF_LD_B];
		break;
	case BPF_LD_W | BPF_LEN:
		op = op_table[BPF_LD_W];
		break;
	case BPF_LD_W | BPF_IND:
		op = op_table[BPF_LD_W];
		break;
	case BPF_LD_H | BPF_IND:
		op = op_table[BPF_LD_H];
		break;
	case BPF_LD_B | BPF_IND:
		op = op_table[BPF_LD_B];
		break;
	case BPF_LD | BPF_IMM:
		op = op_table[BPF_LD_W];
		break;
	case BPF_LDX | BPF_IMM:
		op = op_table[BPF_LDX];
		break;
	case BPF_LDX_B | BPF_MSH:
		op = op_table[BPF_LDX_B];
		break;
	case BPF_LD | BPF_MEM:
		op = op_table[BPF_LD_W];
		break;
	case BPF_LDX | BPF_MEM:
		op = op_table[BPF_LDX];
		break;
	case BPF_JMP_JA:
		op = op_table[BPF_JMP_JA];
		break;
	case BPF_JMP_JGT | BPF_X:
		op = op_table[BPF_JMP_JGT];
		break;
	case BPF_JMP_JGT | BPF_K:
		op = op_table[BPF_JMP_JGT];
		break;
	case BPF_JMP_JGE | BPF_X:
		op = op_table[BPF_JMP_JGE];
		break;
	case BPF_JMP_JGE | BPF_K:
		op = op_table[BPF_JMP_JGE];
		break;
	case BPF_JMP_JEQ | BPF_X:
		op = op_table[BPF_JMP_JEQ];
		break;
	case BPF_JMP_JEQ | BPF_K:
		op = op_table[BPF_JMP_JEQ];
		break;
	case BPF_JMP_JSET | BPF_X:
		op = op_table[BPF_JMP_JSET];
		break;
	case BPF_JMP_JSET | BPF_K:
		op = op_table[BPF_JMP_JSET];
		break;
	case BPF_ALU_NEG:
		op = op_table[BPF_ALU_NEG];
		break;
	case BPF_ALU_LSH | BPF_X:
		op = op_table[BPF_ALU_LSH];
		break;
	case BPF_ALU_LSH | BPF_K:
		op = op_table[BPF_ALU_LSH];
		break;
	case BPF_ALU_RSH | BPF_X:
		op = op_table[BPF_ALU_RSH];
		break;
	case BPF_ALU_RSH | BPF_K:
		op = op_table[BPF_ALU_RSH];
		break;
	case BPF_ALU_ADD | BPF_X:
		op = op_table[BPF_ALU_ADD];
		break;
	case BPF_ALU_ADD | BPF_K:
		op = op_table[BPF_ALU_ADD];
		break;
	case BPF_ALU_SUB | BPF_X:
		op = op_table[BPF_ALU_SUB];
		break;
	case BPF_ALU_SUB | BPF_K:
		op = op_table[BPF_ALU_SUB];
		break;
	case BPF_ALU_MUL | BPF_X:
		op = op_table[BPF_ALU_MUL];
		break;
	case BPF_ALU_MUL | BPF_K:
		op = op_table[BPF_ALU_MUL];
		break;
	case BPF_ALU_DIV | BPF_X:
		op = op_table[BPF_ALU_DIV];
		break;
	case BPF_ALU_DIV | BPF_K:
		op = op_table[BPF_ALU_DIV];
		break;
	case BPF_ALU_MOD | BPF_X:
		op = op_table[BPF_ALU_MOD];
		break;
	case BPF_ALU_MOD | BPF_K:
		op = op_table[BPF_ALU_MOD];
		break;
	case BPF_ALU_AND | BPF_X:
		op = op_table[BPF_ALU_AND];
		break;
	case BPF_ALU_AND | BPF_K:
		op = op_table[BPF_ALU_AND];
		break;
	case BPF_ALU_OR | BPF_X:
		op = op_table[BPF_ALU_OR];
		break;
	case BPF_ALU_OR | BPF_K:
		op = op_table[BPF_ALU_OR];
		break;
	case BPF_ALU_XOR | BPF_X:
		op = op_table[BPF_ALU_XOR];
		break;
	case BPF_ALU_XOR | BPF_K:
		op = op_table[BPF_ALU_XOR];
		break;
	default:
		op = "nosup";
		break;
	}

	printf("[%2x,%2x,%2x,%08x]\t%s\t%x\n", i[0], i[1], i[2], i[3], op, i[3]);
}

int main(){
   int a[][4] = {
	{    0,  0,  0, 0x00000000 },
	{  0x2,  0,  0, 0x00000000 },
	{ 0x61,  0,  0, 0x00000000 },
	{ 0x48,  0,  0, 0x00000000 },
	{  0x2,  0,  0, 0x00000001 },
	{    0,  0,  0, 0x00000180 },
	{  0x2,  0,  0, 0x00000002 },
	{ 0x61,  0,  0, 0x00000002 },
	{ 0x60,  0,  0, 0x00000001 },
	{ 0x1c,  0,  0, 0x00000000 },
	{ 0x15, 32,  0, 0x00000000 },
	{ 0x28,  0,  0, 0x0000000c },
	{ 0x15,  0, 11, 0x00000800 },
	{    0,  0,  0, 0x00000001 },
	{  0x2,  0,  0, 0x00000002 },
	{ 0x61,  0,  0, 0x00000002 },
	{ 0x50,  0,  0, 0x0000000e },
	{  0x2,  0,  0, 0x00000003 },
	{    0,  0,  0, 0x00000000 },
	{  0x2,  0,  0, 0x00000004 },
	{ 0x61,  0,  0, 0x00000004 },
	{ 0x60,  0,  0, 0x00000003 },
	{ 0x1c,  0,  0, 0x00000000 },
	{ 0x15,  0, 19, 0x00000000 },
	{ 0x28,  0,  0, 0x0000000c },
	{ 0x15,  0, 18, 0x000086dd },
	{    0,  0,  0, 0x00000000 },
	{  0x2,  0,  0, 0x00000004 },
	{ 0x61,  0,  0, 0x00000004 },
	{ 0x48,  0,  0, 0x0000000e },
	{  0x2,  0,  0, 0x00000005 },
	{    0,  0,  0, 0x00000ff0 },
	{  0x2,  0,  0, 0x00000006 },
	{ 0x61,  0,  0, 0x00000006 },
	{ 0x60,  0,  0, 0x00000005 },
	{ 0x5c,  0,  0, 0x00000000 },
	{  0x2,  0,  0, 0x00000006 },
	{    0,  0,  0, 0x00000000 },
	{  0x2,  0,  0, 0x00000007 },
	{ 0x61,  0,  0, 0x00000007 },
	{ 0x60,  0,  0, 0x00000006 },
	{ 0x1c,  0,  0, 0x00000000 },
	{ 0x15,  1,  0, 0x00000000 },
	{  0x6,  0,  0, 0x0000ffff },
	{  0x6,  0,  0, 0x00000000 },
   };

   int b[][4] = {
     { 0x28,  0,  0, 0x00000000 },
     { 0x15,  7,  0, 0x00000180 },
     { 0x28,  0,  0, 0x0000000c },
     { 0x15,  0,  2, 0x00000800 },
     { 0x30,  0,  0, 0x0000000f },
     { 0x15,  4,  3, 0x00000000 },
     { 0x15,  0,  3, 0x000086dd },
     { 0x28,  0,  0, 0x0000000e },
     { 0x45,  0,  1, 0x00000ff0 },
     {  0x6,  0,  0, 0x0000ffff },
     {  0x6,  0,  0, 0x00000000 },
   };
   int len = sizeof(a)/sizeof(a[0]);
   int k = 0;
   for (k=0;k<len;k++)
       bpf_disasm(a[k]);
   
   printf("\n");

   len = sizeof(b)/sizeof(b[0]);
   for (k=0;k<len;k++)
       bpf_disasm(b[k]);
   return 0;
}
