#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include <assert.h>
#include <sys/types.h>

#include "config.h"
#include "extern.h"
#include "emulater.h"

#include "p386.h"

static void *segfault(void);

static int p386_int_handler(void);
static void p386_int3_handler(void);

static int inst_00(void);
static int inst_01(void);
static int inst_02(void);
static int inst_03(void);
static int inst_04(void);
static int inst_05(void);
static int inst_06(void);
static int inst_07(void);
static int inst_08(void);
static int inst_09(void);
static int inst_0a(void);
static int inst_0b(void);
static int inst_0c(void);
static int inst_0d(void);
static int inst_0e(void);
static int inst_0f(void);
static int inst_0f84(void);
static int inst_0f85(void);
static int inst_0f8c(void);
static int inst_0f8d(void);
static int inst_0f8e(void);
static int inst_0f8f(void);

static int inst_10(void);
static int inst_11(void);
static int inst_12(void);
static int inst_13(void);
static int inst_14(void);
static int inst_15(void);
static int inst_16(void);
static int inst_17(void);
static int inst_18(void);
static int inst_19(void);
static int inst_1a(void);
static int inst_1b(void);
static int inst_1c(void);
static int inst_1d(void);
static int inst_1e(void);
static int inst_1f(void);

static int inst_20(void);
static int inst_21(void);
static int inst_22(void);
static int inst_23(void);
static int inst_24(void);
static int inst_25(void);
static int inst_26(void);
static int inst_27(void);
static int inst_28(void);
static int inst_29(void);
static int inst_2a(void);
static int inst_2b(void);
static int inst_2c(void);
static int inst_2d(void);
static int inst_2e(void);
static int inst_2f(void);

static int inst_30(void);
static int inst_31(void);
static int inst_32(void);
static int inst_33(void);
static int inst_34(void);
static int inst_35(void);
static int inst_36(void);
static int inst_37(void);
static int inst_38(void);
static int inst_39(void);
static int inst_3a(void);
static int inst_3b(void);
static int inst_3c(void);
static int inst_3d(void);
static int inst_3e(void);
static int inst_3f(void);

static int inst_40(void);
static int inst_41(void);
static int inst_42(void);
static int inst_43(void);
static int inst_44(void);
static int inst_45(void);
static int inst_46(void);
static int inst_47(void);
static int inst_48(void);
static int inst_49(void);
static int inst_4a(void);
static int inst_4b(void);
static int inst_4c(void);
static int inst_4d(void);
static int inst_4e(void);
static int inst_4f(void);

static int inst_50(void);
static int inst_51(void);
static int inst_52(void);
static int inst_53(void);
static int inst_54(void);
static int inst_55(void);
static int inst_56(void);
static int inst_57(void);
static int inst_58(void);
static int inst_59(void);
static int inst_5a(void);
static int inst_5b(void);
static int inst_5c(void);
static int inst_5d(void);
static int inst_5e(void);
static int inst_5f(void);

static int inst_60(void);
static int inst_61(void);
static int inst_62(void);
static int inst_63(void);
static int inst_64(void);
static int inst_65(void);
static int inst_66(void);
static int inst_67(void);
static int inst_68(void);
static int inst_69(void);
static int inst_6a(void);
static int inst_6b(void);
static int inst_6c(void);
static int inst_6d(void);
static int inst_6e(void);
static int inst_6f(void);

static int inst_70(void);
static int inst_71(void);
static int inst_72(void);
static int inst_73(void);
static int inst_74(void);
static int inst_75(void);
static int inst_76(void);
static int inst_77(void);
static int inst_78(void);
static int inst_79(void);
static int inst_7a(void);
static int inst_7b(void);
static int inst_7c(void);
static int inst_7d(void);
static int inst_7e(void);
static int inst_7f(void);

static int inst_80(void);
static int inst_81(void);
static int inst_82(void);
static int inst_83(void);
static int inst_84(void);
static int inst_85(void);
static int inst_86(void);
static int inst_87(void);
static int inst_88(void);
static int inst_89(void);
static int inst_8a(void);
static int inst_8b(void);
static int inst_8c(void);
static int inst_8d(void);
static int inst_8e(void);
static int inst_8f(void);

static int inst_90(void);
static int inst_91(void);
static int inst_92(void);
static int inst_93(void);
static int inst_94(void);
static int inst_95(void);
static int inst_96(void);
static int inst_97(void);
static int inst_98(void);
static int inst_99(void);
static int inst_9a(void);
static int inst_9b(void);
static int inst_9c(void);
static int inst_9d(void);
static int inst_9e(void);
static int inst_9f(void);

static int inst_a0(void);
static int inst_a1(void);
static int inst_a2(void);
static int inst_a3(void);
static int inst_a4(void);
static int inst_a5(void);
static int inst_a6(void);
static int inst_a7(void);
static int inst_a8(void);
static int inst_a9(void);
static int inst_aa(void);
static int inst_ab(void);
static int inst_ac(void);
static int inst_ad(void);
static int inst_ae(void);
static int inst_af(void);

static int inst_b0(void);
static int inst_b1(void);
static int inst_b2(void);
static int inst_b3(void);
static int inst_b4(void);
static int inst_b5(void);
static int inst_b6(void);
static int inst_b7(void);
static int inst_b8(void);
static int inst_b9(void);
static int inst_ba(void);
static int inst_bb(void);
static int inst_bc(void);
static int inst_bd(void);
static int inst_be(void);
static int inst_bf(void);

static int inst_c0(void);
static int inst_c1(void);
static int inst_c2(void);
static int inst_c3(void);
static int inst_c4(void);
static int inst_c5(void);
static int inst_c6(void);
static int inst_c7(void);
static int inst_c8(void);
static int inst_c9(void);
static int inst_ca(void);
static int inst_cb(void);
static int inst_cc(void);
static int inst_cd(void);
static int inst_ce(void);
static int inst_cf(void);

static int inst_d0(void);
static int inst_d1(void);
static int inst_d2(void);
static int inst_d3(void);
static int inst_d4(void);
static int inst_d5(void);
static int inst_d6(void);
static int inst_d7(void);
static int inst_d8(void);
static int inst_d9(void);
static int inst_da(void);
static int inst_db(void);
static int inst_dc(void);
static int inst_dd(void);
static int inst_de(void);
static int inst_df(void);

static int inst_e0(void);
static int inst_e1(void);
static int inst_e2(void);
static int inst_e3(void);
static int inst_e4(void);
static int inst_e5(void);
static int inst_e6(void);
static int inst_e7(void);
static int inst_e8(void);
static int inst_e9(void);
static int inst_ea(void);
static int inst_eb(void);
static int inst_ec(void);
static int inst_ed(void);
static int inst_ee(void);
static int inst_ef(void);

static int inst_f0(void);
static int inst_f1(void);
static int inst_f2(void);
static int inst_f3(void);
static int inst_f4(void);
static int inst_f5(void);
static int inst_f6(void);
static int inst_f7(void);
static int inst_f8(void);
static int inst_f9(void);
static int inst_fa(void);
static int inst_fb(void);
static int inst_fc(void);
static int inst_fd(void);
static int inst_fe(void);
static int inst_ff(void);

static int (* const (inst_tbl[]))(void) = {
  &inst_00, &inst_01, &inst_02, &inst_03, &inst_04, &inst_05, &inst_06, &inst_07,
  &inst_08, &inst_09, &inst_0a, &inst_0b, &inst_0c, &inst_0d, &inst_0e, &inst_0f,
  &inst_10, &inst_11, &inst_12, &inst_13, &inst_14, &inst_15, &inst_16, &inst_17,
  &inst_18, &inst_19, &inst_1a, &inst_1b, &inst_1c, &inst_1d, &inst_1e, &inst_1f,
  &inst_20, &inst_21, &inst_22, &inst_23, &inst_24, &inst_25, &inst_26, &inst_27,
  &inst_28, &inst_29, &inst_2a, &inst_2b, &inst_2c, &inst_2d, &inst_2e, &inst_2f,
  &inst_30, &inst_31, &inst_32, &inst_33, &inst_34, &inst_35, &inst_36, &inst_37,
  &inst_38, &inst_39, &inst_3a, &inst_3b, &inst_3c, &inst_3d, &inst_3e, &inst_3f,
  &inst_40, &inst_41, &inst_42, &inst_43, &inst_44, &inst_45, &inst_46, &inst_47,
  &inst_48, &inst_49, &inst_4a, &inst_4b, &inst_4c, &inst_4d, &inst_4e, &inst_4f,
  &inst_50, &inst_51, &inst_52, &inst_53, &inst_54, &inst_55, &inst_56, &inst_57,
  &inst_58, &inst_59, &inst_5a, &inst_5b, &inst_5c, &inst_5d, &inst_5e, &inst_5f,
  &inst_60, &inst_61, &inst_62, &inst_63, &inst_64, &inst_65, &inst_66, &inst_67,
  &inst_68, &inst_69, &inst_6a, &inst_6b, &inst_6c, &inst_6d, &inst_6e, &inst_6f,
  &inst_70, &inst_71, &inst_72, &inst_73, &inst_74, &inst_75, &inst_76, &inst_77,
  &inst_78, &inst_79, &inst_7a, &inst_7b, &inst_7c, &inst_7d, &inst_7e, &inst_7f,
  &inst_80, &inst_81, &inst_82, &inst_83, &inst_84, &inst_85, &inst_86, &inst_87,
  &inst_88, &inst_89, &inst_8a, &inst_8b, &inst_8c, &inst_8d, &inst_8e, &inst_8f,
  &inst_90, &inst_91, &inst_92, &inst_93, &inst_94, &inst_95, &inst_96, &inst_97,
  &inst_98, &inst_99, &inst_9a, &inst_9b, &inst_9c, &inst_9d, &inst_9e, &inst_9f,
  &inst_a0, &inst_a1, &inst_a2, &inst_a3, &inst_a4, &inst_a5, &inst_a6, &inst_a7,
  &inst_a8, &inst_a9, &inst_aa, &inst_ab, &inst_ac, &inst_ad, &inst_ae, &inst_af,
  &inst_b0, &inst_b1, &inst_b2, &inst_b3, &inst_b4, &inst_b5, &inst_b6, &inst_b7,
  &inst_b8, &inst_b9, &inst_ba, &inst_bb, &inst_bc, &inst_bd, &inst_be, &inst_bf,
  &inst_c0, &inst_c1, &inst_c2, &inst_c3, &inst_c4, &inst_c5, &inst_c6, &inst_c7,
  &inst_c8, &inst_c9, &inst_ca, &inst_cb, &inst_cc, &inst_cd, &inst_ce, &inst_cf,
  &inst_d0, &inst_d1, &inst_d2, &inst_d3, &inst_d4, &inst_d5, &inst_d6, &inst_d7,
  &inst_d8, &inst_d9, &inst_da, &inst_db, &inst_dc, &inst_dd, &inst_de, &inst_df,
  &inst_e0, &inst_e1, &inst_e2, &inst_e3, &inst_e4, &inst_e5, &inst_e6, &inst_e7,
  &inst_e8, &inst_e9, &inst_ea, &inst_eb, &inst_ec, &inst_ed, &inst_ee, &inst_ef,
  &inst_f0, &inst_f1, &inst_f2, &inst_f3, &inst_f4, &inst_f5, &inst_f6, &inst_f7,
  &inst_f8, &inst_f9, &inst_fa, &inst_fb, &inst_fc, &inst_fd, &inst_fe, &inst_ff
};

void
p386_reset(void)
{
  p386_EIP = P386_TEXT_START;
  p386_ESP = P386_STACK_START;
  p386_state = P386_STATE_INIT;
}

int
p386_step(void)
{
  p386_state = P386_STATE_RUNNING;

  if ((p386_EIP - P386_TEXT_START) > P386_TEXT_LIMIT)
    {
      /* segmentation fault */
      return 1;
    }

  return (*(inst_tbl[p386_text[p386_EIP - P386_TEXT_START]]))();
}

int
p386_run(void)
{
  int r;

  p386_state = P386_STATE_RUNNING;

  do
    {
      if ((p386_EIP - P386_TEXT_START) > P386_TEXT_LIMIT)
        {
          /* segmentation fault */
          return 1;
        }
    }
  while ((r = (*(inst_tbl[p386_text[p386_EIP - P386_TEXT_START]]))()) == 0);

  return r;
}

static int
p386_int_handler(void)
{
  assert(p386_text[p386_EIP - P386_TEXT_START] == 0xcdU);
  switch (p386_text[(p386_EIP + 1UL) - P386_TEXT_START])
    {
    case 3:
      longjmp(p386_jmpbuf_int3, 1);
      break;
    case 192:
      p386_EAX = fgetc(stdin);
      break;
    case 193:
      fputc((int)p386_EAX, stdout);
      break;
    default:
      p386_state = P386_STATE_UNKINT;
      return 1;
    }

  p386_state = P386_STATE_RUNNING;
  p386_EIP += 2UL;

  return 0;
}

static void
p386_int3_handler(void)
{
  assert(p386_text[p386_EIP - P386_TEXT_START] == 0xccU);
  longjmp(p386_jmpbuf_int3, 1);
}

static void *
segfault(void)
{
  fprintf(stderr, "p386 VM segmentation fault\n");
  exit(1);
}

#define UNSRPT(op) \
static int \
inst_ ## op(void) \
{ \
  p386_state = P386_STATE_UNSRPT; \
\
  return 1; \
}

UNSRPT(00)
UNSRPT(02)
UNSRPT(04)
UNSRPT(05)
UNSRPT(06)
UNSRPT(07)

UNSRPT(08)
UNSRPT(0a)
UNSRPT(0c)
UNSRPT(0d)
UNSRPT(0e)

UNSRPT(10)
UNSRPT(11)
UNSRPT(12)
UNSRPT(13)
UNSRPT(14)
UNSRPT(15)
UNSRPT(16)
UNSRPT(17)

UNSRPT(18)
UNSRPT(19)
UNSRPT(1a)
UNSRPT(1b)
UNSRPT(1c)
UNSRPT(1d)
UNSRPT(1e)
UNSRPT(1f)

UNSRPT(20)
UNSRPT(22)
UNSRPT(24)
UNSRPT(25)
UNSRPT(26)
UNSRPT(27)

UNSRPT(28)
UNSRPT(2a)
UNSRPT(2c)
UNSRPT(2d)
UNSRPT(2e)
UNSRPT(2f)

UNSRPT(30)
UNSRPT(32)
UNSRPT(34)
UNSRPT(35)
UNSRPT(36)
UNSRPT(37)

UNSRPT(38)
UNSRPT(3a)
UNSRPT(3c)
UNSRPT(3d)
UNSRPT(3e)
UNSRPT(3f)

UNSRPT(40)
UNSRPT(41)
UNSRPT(42)
UNSRPT(43)
UNSRPT(44)
UNSRPT(45)
UNSRPT(46)
UNSRPT(47)

UNSRPT(48)
UNSRPT(49)
UNSRPT(4a)
UNSRPT(4b)
UNSRPT(4c)
UNSRPT(4d)
UNSRPT(4e)
UNSRPT(4f)

UNSRPT(56)
UNSRPT(57)

UNSRPT(5e)
UNSRPT(5f)

UNSRPT(60)
UNSRPT(61)
UNSRPT(62)
UNSRPT(63)
UNSRPT(64)
UNSRPT(65)
UNSRPT(66)
UNSRPT(67)

UNSRPT(68)
UNSRPT(69)
UNSRPT(6a)
UNSRPT(6b)
UNSRPT(6c)
UNSRPT(6d)
UNSRPT(6e)
UNSRPT(6f)

UNSRPT(70)
UNSRPT(71)
UNSRPT(72)
UNSRPT(73)
UNSRPT(76)
UNSRPT(77)

UNSRPT(78)
UNSRPT(79)
UNSRPT(7a)
UNSRPT(7b)

UNSRPT(80)
UNSRPT(82)
UNSRPT(84)
UNSRPT(85)
UNSRPT(86)
UNSRPT(87)

UNSRPT(88)
UNSRPT(8a)
UNSRPT(8c)
UNSRPT(8d)
UNSRPT(8e)
UNSRPT(8f)

UNSRPT(91)
UNSRPT(92)
UNSRPT(93)
UNSRPT(94)
UNSRPT(95)
UNSRPT(96)
UNSRPT(97)

UNSRPT(98)
UNSRPT(9a)
UNSRPT(9b)
UNSRPT(9c)
UNSRPT(9d)
UNSRPT(9e)
UNSRPT(9f)

UNSRPT(a0)
UNSRPT(a1)
UNSRPT(a2)
UNSRPT(a3)
UNSRPT(a4)
UNSRPT(a5)
UNSRPT(a6)
UNSRPT(a7)

UNSRPT(a8)
UNSRPT(a9)
UNSRPT(aa)
UNSRPT(ab)
UNSRPT(ac)
UNSRPT(ad)
UNSRPT(ae)
UNSRPT(af)

UNSRPT(b0)
UNSRPT(b1)
UNSRPT(b2)
UNSRPT(b3)
UNSRPT(b4)
UNSRPT(b5)
UNSRPT(b6)
UNSRPT(b7)

UNSRPT(b8)
UNSRPT(b9)
UNSRPT(ba)
UNSRPT(bb)
UNSRPT(bc)
UNSRPT(bd)
UNSRPT(be)
UNSRPT(bf)

UNSRPT(c0)
UNSRPT(c1)
UNSRPT(c2)
UNSRPT(c4)
UNSRPT(c5)
UNSRPT(c6)

UNSRPT(c8)
UNSRPT(ca)
UNSRPT(cb)
UNSRPT(ce)
UNSRPT(cf)

UNSRPT(d0)
UNSRPT(d1)
UNSRPT(d2)
UNSRPT(d4)
UNSRPT(d5)
UNSRPT(d6)
UNSRPT(d7)

UNSRPT(d8)
UNSRPT(d9)
UNSRPT(da)
UNSRPT(db)
UNSRPT(dc)
UNSRPT(dd)
UNSRPT(de)
UNSRPT(df)

UNSRPT(e0)
UNSRPT(e1)
UNSRPT(e2)
UNSRPT(e3)
UNSRPT(e4)
UNSRPT(e5)
UNSRPT(e6)
UNSRPT(e7)

UNSRPT(ea)
UNSRPT(eb)
UNSRPT(ec)
UNSRPT(ed)
UNSRPT(ee)
UNSRPT(ef)

UNSRPT(f0)
UNSRPT(f1)
UNSRPT(f2)
UNSRPT(f3)
UNSRPT(f5)
UNSRPT(f6)

UNSRPT(f8)
UNSRPT(f9)
UNSRPT(fa)
UNSRPT(fb)
UNSRPT(fc)
UNSRPT(fd)
UNSRPT(fe)
UNSRPT(ff)

#undef UNSRPT

#define I386_FLAG_ZERO 0x00000040
#define I386_FLAG_SIGN 0x00000080
#define I386_FLAG_OVFL 0x00000800

#define SET_FLAG(flag) (p386_EFLAGS |= (flag))
#define RESET_FLAG(flag) (p386_EFLAGS &= ~(flag))

#define MEM_RESOLV(addr) \
  ( \
   (((P386_STACK_START - 1UL) - ((u_int32_t)(addr))) <= P386_STACK_LIMIT) \
   ? ((void* )(&(p386_stack[((u_int32_t)(addr)) - (P386_STACK_START - P386_STACK_SIZE)]))) \
   : ( \
      ((((u_int32_t)(addr)) - P386_DATA_START) <= P386_DATA_LIMIT) \
      ? ((void *)(&(p386_data[((u_int32_t)(addr)) - P386_DATA_START]))) \
      : (segfault()) \
     ) \
  )

#define B5_3SET \
do \
  { \
    switch ((modbyte >> 3) & 7) \
      {  /* 片方はいつもレジスタ */ \
      case 0: \
        b5_3 = &p386_EAX; \
        break; \
      case 1: \
        b5_3 = &p386_ECX; \
        break; \
      case 2: \
        b5_3 = &p386_EDX; \
        break; \
      case 3: \
        b5_3 = &p386_EBX; \
        break; \
      case 4: \
        b5_3 = &p386_ESP; \
        break; \
      case 5: \
          b5_3 = &p386_EBP; \
        break; \
      case 6: \
      case 7: \
        p386_state = P386_STATE_UNSRPT; \
        return 1; \
      default: \
        assert(0); \
      } \
  } \
while (0)

#define B2_0SET \
do \
  { \
    switch ((modbyte >> 6) & 3) \
      { \
      case 0:  /* レジスタ間接のみおよびディスプレイスメントのみ */ \
        switch (modbyte & 7) \
          {  /* [BP] というアドレシングがないことに注意 */ \
          case 0: \
            b2_0 = MEM_RESOLV(p386_EAX); \
            break; \
          case 1: \
            b2_0 = MEM_RESOLV(p386_ECX); \
            break; \
          case 2: \
            b2_0 = MEM_RESOLV(p386_EDX); \
            break; \
          case 3: \
            b2_0 = MEM_RESOLV(p386_EBX); \
            break; \
          case 4: \
            p386_state = P386_STATE_UNSRPT; \
            return 1; \
          case 5: \
            eip_inc += 4UL;  /* 32 bit ディスプレイスメント。他は追加バイト無し */ \
            b2_0 = MEM_RESOLV(*((u_int32_t *)(&(p386_text[(p386_EIP + 2UL) - P386_TEXT_START])))); \
            break; \
          case 6: \
          case 7: \
            p386_state = P386_STATE_UNSRPT; \
            return 1; \
          default: \
            assert(0); \
          } \
        break; \
      case 1: \
        eip_inc += 1UL;  /* レジスタ + 8 bit ディスプレイスメント。符号拡張が必要 */ \
        switch (modbyte & 7) \
          { \
          case 0: \
            b2_0 = MEM_RESOLV(p386_EAX + ((int32_t)(*((signed char *)(&(p386_text[(p386_EIP + 2UL) - P386_TEXT_START])))))); \
            break; \
          case 1: \
            b2_0 = MEM_RESOLV(p386_ECX + ((int32_t)(*((signed char *)(&(p386_text[(p386_EIP + 2UL) - P386_TEXT_START])))))); \
            break; \
          case 2: \
            b2_0 = MEM_RESOLV(p386_EDX + ((int32_t)(*((signed char *)(&(p386_text[(p386_EIP + 2UL) - P386_TEXT_START])))))); \
            break; \
          case 3: \
            b2_0 = MEM_RESOLV(p386_EBX + ((int32_t)(*((signed char *)(&(p386_text[(p386_EIP + 2UL) - P386_TEXT_START])))))); \
            break; \
          case 4: \
            p386_state = P386_STATE_UNSRPT; \
            return 1; \
          case 5: \
            b2_0 = MEM_RESOLV(p386_EBP + ((int32_t)(*((signed char *)(&(p386_text[(p386_EIP + 2UL) - P386_TEXT_START])))))); \
            break; \
          case 6: \
          case 7: \
            p386_state = P386_STATE_UNSRPT; \
            return 1; \
          default: \
            assert(0); \
          } \
        break; \
      case 2: \
        eip_inc += 4UL;  /* レジスタ + 32 bit ディスプレイスメント */ \
        switch (modbyte & 7) \
          { \
          case 0: \
            b2_0 = MEM_RESOLV(p386_EAX + (*((u_int32_t *)(&(p386_text[(p386_EIP + 2UL) - P386_TEXT_START]))))); \
            break; \
          case 1: \
            b2_0 = MEM_RESOLV(p386_ECX + (*((u_int32_t *)(&(p386_text[(p386_EIP + 2UL) - P386_TEXT_START]))))); \
            break; \
          case 2: \
            b2_0 = MEM_RESOLV(p386_EDX + (*((u_int32_t *)(&(p386_text[(p386_EIP + 2UL) - P386_TEXT_START]))))); \
            break; \
          case 3: \
            b2_0 = MEM_RESOLV(p386_EBX + (*((u_int32_t *)(&(p386_text[(p386_EIP + 2UL) - P386_TEXT_START]))))); \
            break; \
          case 4: \
            p386_state = P386_STATE_UNSRPT; \
            return 1; \
          case 5: \
            b2_0 = MEM_RESOLV(p386_EBP + (*((u_int32_t *)(&(p386_text[(p386_EIP + 2UL) - P386_TEXT_START]))))); \
            break; \
          case 6: \
          case 7: \
            p386_state = P386_STATE_UNSRPT; \
            return 1; \
          default: \
            assert(0); \
          } \
        break; \
      case 3:  /* レジスタ直接 */ \
        switch (modbyte & 7) \
          { \
          case 0: \
            b2_0 = &p386_EAX; \
            break; \
          case 1: \
            b2_0 = &p386_ECX; \
            break; \
          case 2: \
            b2_0 = &p386_EDX; \
            break; \
          case 3: \
            b2_0 = &p386_EBX; \
            break; \
          case 4: \
            b2_0 = &p386_ESP; \
            break; \
          case 5: \
            b2_0 = &p386_EBP; \
            break; \
          case 6: \
          case 7: \
            p386_state = P386_STATE_UNSRPT; \
            return 1; \
          default: \
            assert(0); \
          } \
        break; \
      default: \
        assert(0); \
      } \
  } \
while (0)

#define ADD(code, src, dst) \
static int \
inst_ ## code(void) \
{ \
  u_int8_t modbyte; \
  u_int32_t *b5_3; \
  u_int32_t *b2_0; \
  u_int32_t old_dist;  /* オーバフローフラグ設定のための比較用 */ \
  u_int32_t eip_inc;  /* EIP の増分 */ \
\
  eip_inc = 2UL;  /* オペコードとオペランドの最初のバイト */ \
\
  modbyte = p386_text[(p386_EIP + 1UL) - P386_TEXT_START]; \
\
  B5_3SET; \
  B2_0SET; \
\
  old_dist = (*dst); \
\
  (*dst) += (*src); \
\
  if (*dst) \
    RESET_FLAG(I386_FLAG_ZERO); \
  else \
    SET_FLAG(I386_FLAG_ZERO); \
\
  if ((*dst) & 0x80000000UL) \
    SET_FLAG(I386_FLAG_SIGN); \
  else \
    RESET_FLAG(I386_FLAG_SIGN); \
\
  if ((~(old_dist ^ (*src))) & (old_dist ^ (*dst)) & 0x80000000UL) \
    SET_FLAG(I386_FLAG_OVFL); \
  else \
    RESET_FLAG(I386_FLAG_OVFL); \
\
  p386_EIP += eip_inc; \
\
  return 0; \
}

ADD(01, b5_3, b2_0)
ADD(03, b2_0, b5_3)

#undef ADD

static int
inst_0f(void)
{
  u_int8_t b2;

  if ((b2 = (p386_text[(p386_EIP + 1UL) - P386_TEXT_START] - 0x80U)) > 0xf) {
    p386_state = P386_STATE_UNSRPT;
    return 1;
  }

  /* 拡張命令は遠距離条件分岐のみのサポート */
  switch (b2)
    {
    case 0:
    case 1:
    case 2:
    case 3:
      p386_state = P386_STATE_UNSRPT;
      return 1;
    case 4:
      return inst_0f84();
    case 5:
      return inst_0f85();
    case 6:
    case 7:
    case 8:
    case 9:
    case 0xa:
    case 0xb:
      p386_state = P386_STATE_UNSRPT;
      return 1;
    case 0xc:
      return inst_0f8c();
    case 0xd:
      return inst_0f8d();
    case 0xe:
      return inst_0f8e();
    case 0xf:
      return inst_0f8f();
    default:
      assert(0);
    }
}

static int
inst_0f84(void)
{
  if (p386_EFLAGS & I386_FLAG_ZERO)
    p386_EIP += (6UL + (*((u_int32_t *)(&(p386_text[(p386_EIP + 2UL) - P386_TEXT_START])))));
  else
    p386_EIP += 6UL;

  return 0;
}

static int
inst_0f85(void)
{
  if (p386_EFLAGS & I386_FLAG_ZERO)
    p386_EIP += 6UL;
  else
    p386_EIP += (6UL + (*((u_int32_t *)(&(p386_text[(p386_EIP + 2UL) - P386_TEXT_START])))));

  return 0;
}

static int
inst_0f8c(void)
{
  u_int32_t s, o;

  s = (p386_EFLAGS >> 7);
  o = (p386_EFLAGS >> 11);

  if ((s ^ o) & 1L)
    p386_EIP += (6UL + (*((u_int32_t *)(&(p386_text[(p386_EIP + 2UL) - P386_TEXT_START])))));
  else
    p386_EIP += 6UL;

  return 0;
}

static int
inst_0f8d(void)
{
  u_int32_t s, o;

  s = (p386_EFLAGS >> 7);
  o = (p386_EFLAGS >> 11);

  if ((s ^ o) & 1L)
    p386_EIP += 6UL;
  else
    p386_EIP += (6UL + (*((u_int32_t *)(&(p386_text[(p386_EIP + 2UL) - P386_TEXT_START])))));

  return 0;
}

static int
inst_0f8e(void)
{
  u_int32_t z, s, o;

  z = (p386_EFLAGS >> 6);
  s = (p386_EFLAGS >> 7);
  o = (p386_EFLAGS >> 11);

  if (((s ^ o) | z) & 1L)
    p386_EIP += (6UL + (*((u_int32_t *)(&(p386_text[(p386_EIP + 2UL) - P386_TEXT_START])))));
  else
    p386_EIP += 6UL;

  return 0;
}

static int
inst_0f8f(void)
{
  u_int32_t z, s, o;

  z = (p386_EFLAGS >> 6);
  s = (p386_EFLAGS >> 7);
  o = (p386_EFLAGS >> 11);

  if (((s ^ o) | z) & 1L)
    p386_EIP += 6UL;
  else
    p386_EIP += (6UL + (*((u_int32_t *)(&(p386_text[(p386_EIP + 2UL) - P386_TEXT_START])))));

  return 0;
}

#define SUB(code, src, dst) \
static int \
inst_ ## code(void) \
{ \
  u_int8_t modbyte; \
  u_int32_t *b5_3; \
  u_int32_t *b2_0; \
  u_int32_t old_dist;  /* オーバフローフラグ設定のための比較用 */ \
  u_int32_t eip_inc;  /* EIP の増分 */ \
\
  eip_inc = 2UL;  /* オペコードとオペランドの最初のバイト */ \
\
  modbyte = p386_text[(p386_EIP + 1UL) - P386_TEXT_START]; \
\
  B5_3SET; \
  B2_0SET; \
\
  old_dist = (*dst); \
\
  (*dst) -= (*src); \
\
  if (*dst) \
    RESET_FLAG(I386_FLAG_ZERO); \
  else \
    SET_FLAG(I386_FLAG_ZERO); \
\
  if ((*dst) & 0x80000000UL) \
    SET_FLAG(I386_FLAG_SIGN); \
  else \
    RESET_FLAG(I386_FLAG_SIGN); \
\
  if ((old_dist ^ (*src)) & (old_dist ^ (*dst)) & 0x80000000UL) \
    SET_FLAG(I386_FLAG_OVFL); \
  else \
    RESET_FLAG(I386_FLAG_OVFL); \
\
  p386_EIP += eip_inc; \
\
  return 0; \
}

SUB(29, b5_3, b2_0)
SUB(2b, b2_0, b5_3)

#undef SUB

#define LOGIC(code, src, dst, operation) \
static int \
inst_ ## code(void) \
{ \
  u_int8_t modbyte; \
  u_int32_t *b5_3; \
  u_int32_t *b2_0; \
  u_int32_t eip_inc;  /* EIP の増分 */ \
\
  eip_inc = 2UL;  /* オペコードとオペランドの最初のバイト */ \
\
  modbyte = p386_text[(p386_EIP + 1UL) - P386_TEXT_START]; \
\
  B5_3SET; \
  B2_0SET; \
\
  (*dst) operation ## = (*src); \
\
  if (*dst) \
    RESET_FLAG(I386_FLAG_ZERO); \
  else \
    SET_FLAG(I386_FLAG_ZERO); \
\
  if ((*dst) & 0x80000000UL) \
    SET_FLAG(I386_FLAG_SIGN); \
  else \
    RESET_FLAG(I386_FLAG_SIGN); \
\
  RESET_FLAG(I386_FLAG_OVFL); \
\
  p386_EIP += eip_inc; \
\
  return 0; \
}

LOGIC(09, b5_3, b2_0, |)
LOGIC(0b, b2_0, b5_3, |)
LOGIC(21, b5_3, b2_0, &)
LOGIC(23, b2_0, b5_3, &)
LOGIC(31, b5_3, b2_0, ^)
LOGIC(33, b2_0, b5_3, ^)

#undef LOGIC

#define CMP(code, src, dst) \
static int \
inst_ ## code(void) \
{ \
  u_int8_t modbyte; \
  u_int32_t *b5_3; \
  u_int32_t *b2_0; \
  u_int32_t virtual_dist;  /* 仮想ディスティネーション */ \
  u_int32_t eip_inc;  /* EIP の増分 */ \
\
  eip_inc = 2UL;  /* オペコードとオペランドの最初のバイト */ \
\
  modbyte = p386_text[(p386_EIP + 1UL) - P386_TEXT_START]; \
\
  B5_3SET; \
  B2_0SET; \
\
  virtual_dist = (*dst) - (*src); \
\
  if (virtual_dist) \
    RESET_FLAG(I386_FLAG_ZERO); \
  else \
    SET_FLAG(I386_FLAG_ZERO); \
\
  if (virtual_dist & 0x80000000UL) \
    SET_FLAG(I386_FLAG_SIGN); \
  else \
    RESET_FLAG(I386_FLAG_SIGN); \
\
  if (((*dst) ^ (*src)) & ((*dst) ^ virtual_dist) & 0x80000000UL) \
    SET_FLAG(I386_FLAG_OVFL); \
  else \
    RESET_FLAG(I386_FLAG_OVFL); \
\
  p386_EIP += eip_inc; \
\
  return 0; \
}

CMP(39, b5_3, b2_0)
CMP(3b, b2_0, b5_3)

#undef CMP

#define PUSH_REG(code, src) \
static int \
inst_ ## code(void) \
{ \
  (*((u_int32_t *)(MEM_RESOLV(p386_ESP - 4UL)))) = (p386_ ## src); \
  p386_ESP -= 4UL; \
\
  p386_EIP += 1; \
\
  return 0; \
}

PUSH_REG(50, EAX)
PUSH_REG(51, ECX)
PUSH_REG(52, EDX)
PUSH_REG(53, EBX)
PUSH_REG(54, ESP)
PUSH_REG(55, EBP)

#undef PUSH_REG

#define POP_REG(code, dst) \
static int \
inst_ ## code(void) \
{ \
  (p386_ ## dst) = (*((u_int32_t *)(MEM_RESOLV(p386_ESP)))); \
  p386_ESP += 4UL; \
\
  p386_EIP += 1; \
\
  return 0; \
}

POP_REG(58, EAX)
POP_REG(59, ECX)
POP_REG(5a, EDX)
POP_REG(5b, EBX)
POP_REG(5c, ESP)
POP_REG(5d, EBP)

#undef POP_REG

static int
inst_74(void)
{
  if (p386_EFLAGS & I386_FLAG_ZERO)
    p386_EIP += (2UL + ((u_int32_t)((int32_t)(*((signed char *)(&(p386_text[(p386_EIP + 1UL) - P386_TEXT_START])))))));
  else
    p386_EIP += 2UL;

  return 0;
}

static int
inst_75(void)
{
  if (p386_EFLAGS & I386_FLAG_ZERO)
    p386_EIP += 2UL;
  else
    p386_EIP += (2UL + ((u_int32_t)((int32_t)(*((signed char *)(&(p386_text[(p386_EIP + 1UL) - P386_TEXT_START])))))));

  return 0;
}

static int
inst_7c(void)
{
  u_int32_t s, o;

  s = (p386_EFLAGS >> 7);
  o = (p386_EFLAGS >> 11);

  if ((s ^ o) & 1L)
    p386_EIP += (2UL + ((u_int32_t)((int32_t)(*((signed char *)(&(p386_text[(p386_EIP + 1UL) - P386_TEXT_START])))))));
  else
    p386_EIP += 2UL;

  return 0;
}

static int
inst_7d(void)
{
  u_int32_t s, o;

  s = (p386_EFLAGS >> 7);
  o = (p386_EFLAGS >> 11);

  if ((s ^ o) & 1L)
    p386_EIP += 2UL;
  else
    p386_EIP += (2UL + ((u_int32_t)((int32_t)(*((signed char *)(&(p386_text[(p386_EIP + 1UL) - P386_TEXT_START])))))));

  return 0;
}

static int
inst_7e(void)
{
  u_int32_t z, s, o;

  z = (p386_EFLAGS >> 6);
  s = (p386_EFLAGS >> 7);
  o = (p386_EFLAGS >> 11);

  if (((s ^ o) | z) & 1L)
    p386_EIP += (2UL + ((u_int32_t)((int32_t)(*((signed char *)(&(p386_text[(p386_EIP + 1UL) - P386_TEXT_START])))))));
  else
    p386_EIP += 2UL;

  return 0;
}

static int
inst_7f(void)
{
  u_int32_t z, s, o;

  z = (p386_EFLAGS >> 6);
  s = (p386_EFLAGS >> 7);
  o = (p386_EFLAGS >> 11);

  if (((s ^ o) | z) & 1L)
    p386_EIP += 2UL;
  else
    p386_EIP += (2UL + ((u_int32_t)((int32_t)(*((signed char *)(&(p386_text[(p386_EIP + 1UL) - P386_TEXT_START])))))));

  return 0;
}

static int
inst_81(void)
{
  u_int8_t modbyte;
  u_int32_t imm_src;
  u_int32_t *b2_0;
  u_int32_t old_dist;
  u_int32_t virtual_dist;
  u_int32_t eip_inc;  /* EIP の増分 */

  eip_inc = 2UL;  /* オペコードとオペランドの最初のバイト */

  modbyte = p386_text[(p386_EIP + 1UL) - P386_TEXT_START];

  B2_0SET;

  imm_src = (*((u_int32_t *)(&(p386_text[(p386_EIP + eip_inc) - P386_TEXT_START]))));
  old_dist = (*b2_0);

  switch ((modbyte >> 3) & 7) {  /* 命令種別 */
  case 0:  /* ADD */
    (*b2_0) = (old_dist + imm_src);

    if (*b2_0)
      RESET_FLAG(I386_FLAG_ZERO);
    else
      SET_FLAG(I386_FLAG_ZERO);

    if ((*b2_0) & 0x80000000UL)
      SET_FLAG(I386_FLAG_SIGN);
    else
      RESET_FLAG(I386_FLAG_SIGN);

    if ((~(old_dist ^ imm_src)) & (old_dist ^ (*b2_0)) & 0x80000000UL)
      SET_FLAG(I386_FLAG_OVFL);
    else
      RESET_FLAG(I386_FLAG_OVFL);

    break;
  case 1:  /* OR */
    (*b2_0) = (old_dist | (*((u_int32_t *)(&(p386_text[(p386_EIP + eip_inc) - P386_TEXT_START])))));

    if (*b2_0)
      RESET_FLAG(I386_FLAG_ZERO);
    else
      SET_FLAG(I386_FLAG_ZERO);

    if ((*b2_0) & 0x80000000UL)
      SET_FLAG(I386_FLAG_SIGN);
    else
      RESET_FLAG(I386_FLAG_SIGN);

    RESET_FLAG(I386_FLAG_OVFL);

    break;
  case 2:  /* ADC */
    p386_state = P386_STATE_UNSRPT;
    return 1;
  case 3:  /* SBB */
    p386_state = P386_STATE_UNSRPT;
    return 1;
  case 4:  /* AND */
    (*b2_0) = (old_dist & imm_src);

    if (*b2_0)
      RESET_FLAG(I386_FLAG_ZERO);
    else
      SET_FLAG(I386_FLAG_ZERO);

    if ((*b2_0) & 0x80000000UL)
      SET_FLAG(I386_FLAG_SIGN);
    else
      RESET_FLAG(I386_FLAG_SIGN);

    RESET_FLAG(I386_FLAG_OVFL);

    break;
  case 5:  /* SUB */
    (*b2_0) = (old_dist - imm_src);

    if (*b2_0)
      RESET_FLAG(I386_FLAG_ZERO);
    else
      SET_FLAG(I386_FLAG_ZERO);

    if ((*b2_0) & 0x80000000UL)
      SET_FLAG(I386_FLAG_SIGN);
    else
      RESET_FLAG(I386_FLAG_SIGN);

    if ((old_dist ^ imm_src) & (old_dist ^ (*b2_0)) & 0x80000000UL)
      SET_FLAG(I386_FLAG_OVFL);
    else
      RESET_FLAG(I386_FLAG_OVFL);

    break;
  case 6:  /* XOR */
    (*b2_0) = (old_dist ^ imm_src);

    if (*b2_0)
      RESET_FLAG(I386_FLAG_ZERO);
    else
      SET_FLAG(I386_FLAG_ZERO);

    if ((*b2_0) & 0x80000000UL)
      SET_FLAG(I386_FLAG_SIGN);
    else
      RESET_FLAG(I386_FLAG_SIGN);

    RESET_FLAG(I386_FLAG_OVFL);

    break;
  case 7:  /* CMP */
    virtual_dist = ((*b2_0) - imm_src);

    if (virtual_dist)
      RESET_FLAG(I386_FLAG_ZERO);
    else
      SET_FLAG(I386_FLAG_ZERO);

    if (virtual_dist & 0x80000000UL)
      SET_FLAG(I386_FLAG_SIGN);
    else
      RESET_FLAG(I386_FLAG_SIGN);

    if (((*b2_0) ^ imm_src) & ((*b2_0) ^ virtual_dist) & 0x80000000UL)
      SET_FLAG(I386_FLAG_OVFL);
    else
      RESET_FLAG(I386_FLAG_OVFL);

    break;
  default:
    assert(0);
  }
  eip_inc += 4UL;

  p386_EIP += eip_inc;

  return 0;
}

static int
inst_83(void)
{
  u_int8_t modbyte;
  u_int32_t imm_src;
  u_int32_t *b2_0;
  u_int32_t old_dist;
  u_int32_t virtual_dist;
  u_int32_t eip_inc;  /* EIP の増分 */

  eip_inc = 2UL;  /* オペコードとオペランドの最初のバイト */

  modbyte = p386_text[(p386_EIP + 1UL) - P386_TEXT_START];

  B2_0SET;

  imm_src = ((u_int32_t)((int32_t)(*((signed char *)(&(p386_text[(p386_EIP + eip_inc) - P386_TEXT_START]))))));
  old_dist = (*b2_0);

  switch ((modbyte >> 3) & 7) {  /* 命令種別 */
  case 0:  /* ADD */
    (*b2_0) = (old_dist + imm_src);

    if (*b2_0)
      RESET_FLAG(I386_FLAG_ZERO);
    else
      SET_FLAG(I386_FLAG_ZERO);

    if ((*b2_0) & 0x80000000UL)
      SET_FLAG(I386_FLAG_SIGN);
    else
      RESET_FLAG(I386_FLAG_SIGN);

    if ((~(old_dist ^ imm_src)) & (old_dist ^ (*b2_0)) & 0x80000000UL)
      SET_FLAG(I386_FLAG_OVFL);
    else
      RESET_FLAG(I386_FLAG_OVFL);

    break;
  case 1:  /* OR */
    (*b2_0) = (old_dist | imm_src);

    if (*b2_0)
      RESET_FLAG(I386_FLAG_ZERO);
    else
      SET_FLAG(I386_FLAG_ZERO);

    if ((*b2_0) & 0x80000000UL)
      SET_FLAG(I386_FLAG_SIGN);
    else
      RESET_FLAG(I386_FLAG_SIGN);

    RESET_FLAG(I386_FLAG_OVFL);

    break;
  case 2:  /* ADC */
    p386_state = P386_STATE_UNSRPT;
    return 1;
  case 3:  /* SBB */
    p386_state = P386_STATE_UNSRPT;
    return 1;
  case 4:  /* AND */
    (*b2_0) = (old_dist & imm_src);

    if (*b2_0)
      RESET_FLAG(I386_FLAG_ZERO);
    else
      SET_FLAG(I386_FLAG_ZERO);

    if ((*b2_0) & 0x80000000UL)
      SET_FLAG(I386_FLAG_SIGN);
    else
      RESET_FLAG(I386_FLAG_SIGN);

    RESET_FLAG(I386_FLAG_OVFL);

    break;
  case 5:  /* SUB */
    (*b2_0) = (old_dist - imm_src);

    if (*b2_0)
      RESET_FLAG(I386_FLAG_ZERO);
    else
      SET_FLAG(I386_FLAG_ZERO);

    if ((*b2_0) & 0x80000000UL)
      SET_FLAG(I386_FLAG_SIGN);
    else
      RESET_FLAG(I386_FLAG_SIGN);

    if ((old_dist ^ imm_src) & (old_dist ^ (*b2_0)) & 0x80000000UL)
      SET_FLAG(I386_FLAG_OVFL);
    else
      RESET_FLAG(I386_FLAG_OVFL);

    break;
  case 6:  /* XOR */
    old_dist = (*b2_0);
    (*b2_0) = (old_dist ^ imm_src);

    if (*b2_0)
      RESET_FLAG(I386_FLAG_ZERO);
    else
      SET_FLAG(I386_FLAG_ZERO);

    if ((*b2_0) & 0x80000000UL)
      SET_FLAG(I386_FLAG_SIGN);
    else
      RESET_FLAG(I386_FLAG_SIGN);

    RESET_FLAG(I386_FLAG_OVFL);

    break;
  case 7:  /* CMP */
    virtual_dist = ((*b2_0) - imm_src);

    if (virtual_dist)
      RESET_FLAG(I386_FLAG_ZERO);
    else
      SET_FLAG(I386_FLAG_ZERO);

    if (virtual_dist & 0x80000000UL)
      SET_FLAG(I386_FLAG_SIGN);
    else
      RESET_FLAG(I386_FLAG_SIGN);

    if (((*b2_0) ^ imm_src) & ((*b2_0) ^ virtual_dist) & 0x80000000UL)
      SET_FLAG(I386_FLAG_OVFL);
    else
      RESET_FLAG(I386_FLAG_OVFL);

    break;
  default:
    assert(0);
  }
  eip_inc += 1UL;

  p386_EIP += eip_inc;

  return 0;
}

#define MOV(code, src, dst) \
static int \
inst_ ## code(void) \
{ \
  u_int8_t modbyte; \
  u_int32_t *b5_3; \
  u_int32_t *b2_0; \
  u_int32_t eip_inc;  /* EIP の増分 */ \
\
  eip_inc = 2UL;  /* オペコードとオペランドの最初のバイト */ \
\
  modbyte = p386_text[(p386_EIP + 1UL) - P386_TEXT_START]; \
\
  B5_3SET; \
  B2_0SET; \
\
  (*dst) = (*src); \
\
  /* MOV でフラグは変化しない */ \
\
  p386_EIP += eip_inc; \
\
  return 0; \
}

MOV(89, b5_3, b2_0)
MOV(8b, b2_0, b5_3)

#undef MOV

static int
inst_90(void)
{
  p386_EIP += 1UL;

  return 0;
}

static int
inst_99(void)
{
  if (p386_EAX > 0x7fffffffUL)
    {
      p386_EDX = 0xffffffffUL;
    }
  else
    {
      p386_EDX = 0UL;
    }

  p386_EIP += 1UL;

  return 0;
}

static int
inst_c3(void)
{
  p386_EIP = (*((u_int32_t *)(MEM_RESOLV(p386_ESP))));
  p386_ESP += 4UL;

  return 0;
}

static int
inst_c7(void)
{
  u_int8_t modbyte;
  u_int32_t *b2_0;
  u_int32_t eip_inc;  /* EIP の増分 */

  eip_inc = 2UL;  /* オペコードとオペランドの最初のバイト */

  modbyte = p386_text[(p386_EIP + 1UL) - P386_TEXT_START];

  B2_0SET;

  switch ((modbyte >> 3) & 7) {  /* 命令種別 */
  case 0:
    (*b2_0) = (*((u_int32_t *)(&(p386_text[(p386_EIP + eip_inc) - P386_TEXT_START]))));
    break;
  case 1:  /* 未定義 ? */
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
    p386_state = P386_STATE_UNSRPT;
    return 1;
  default:
    assert(0);
  }
  eip_inc += 4UL;

  p386_EIP += eip_inc;

  return 0;
}

static int
inst_c9(void)
{
  p386_ESP = p386_EBP;
  p386_EBP = (*((u_int32_t *)(MEM_RESOLV(p386_ESP))));
  p386_ESP += 4UL;
  p386_EIP = (*((u_int32_t *)(MEM_RESOLV(p386_ESP))));
  p386_ESP += 4UL;

  return 0;
}

static int
inst_cc(void)
{
  p386_state = P386_STATE_INT;
  p386_int3_handler();
}

static int
inst_cd(void)
{
  p386_state = P386_STATE_INT;

  return p386_int_handler();
}

static int
inst_d3(void)
{
  u_int8_t modbyte;
  u_int32_t *b2_0;
  u_int32_t old_dist;
  u_int32_t eip_inc;  /* EIP の増分 */

  eip_inc = 2UL;  /* オペコードとオペランドの最初のバイト */

  modbyte = p386_text[(p386_EIP + 1UL) - P386_TEXT_START];

  B2_0SET;

  old_dist = (*b2_0);

  switch ((modbyte >> 3) & 7) {  /* 命令種別 */
  case 0:  /* ROL */
  case 1:  /* ROR */
  case 2:  /* RCL */
  case 3:  /* RCR */
    p386_state = P386_STATE_UNSRPT;
    return 1;
  case 4:  /* SHL */
    (*b2_0) = (old_dist << (p386_ECX & 31));

    if ((old_dist ^ (*b2_0)) & 0x80000000UL)
      SET_FLAG(I386_FLAG_OVFL);
    else
      RESET_FLAG(I386_FLAG_OVFL);

    break;
  case 5:  /* SHR */
    (*b2_0) = (old_dist >> (p386_ECX & 31));

    if ((*b2_0) & 0x40000000UL)
      SET_FLAG(I386_FLAG_OVFL);
    else
      RESET_FLAG(I386_FLAG_OVFL);

    break;
  case 6:  /* === */
    p386_state = P386_STATE_UNSRPT;
    return 1;
  case 7:  /* SAR */
    if (old_dist & 0x80000000UL)
      (*b2_0) = (~((~old_dist) >> (p386_ECX & 31)));
    else
      (*b2_0) = (old_dist >> (p386_ECX & 31));

    if ((p386_ECX & 31) == 1)
      RESET_FLAG(I386_FLAG_OVFL);

    break;
  default:
    assert(0);
  }

  if (*b2_0)
    RESET_FLAG(I386_FLAG_ZERO);
  else
    SET_FLAG(I386_FLAG_ZERO);

  if ((*b2_0) & 0x80000000UL)
    SET_FLAG(I386_FLAG_SIGN);
  else
    RESET_FLAG(I386_FLAG_SIGN);

  /* OverFlow は命令により挙動が異なる */

  p386_EIP += eip_inc;

  return 0;
}

static int
inst_e8(void)
{
  p386_EIP += 5UL;

  (*((u_int32_t *)(MEM_RESOLV(p386_ESP - 4UL)))) = p386_EIP;
  p386_ESP -= 4UL;

  p386_EIP += (*((u_int32_t *)(&(p386_text[(p386_EIP - 4UL) - P386_TEXT_START]))));

  return 0;
}

static int
inst_e9(void)
{
  p386_EIP += 5UL;

  p386_EIP += (*((u_int32_t *)(&(p386_text[(p386_EIP - 4UL) - P386_TEXT_START]))));

  return 0;
}

static int
inst_f4(void)
{
  p386_state = P386_STATE_HALT;

  return 1;
}

static int
inst_f7(void)
{
  u_int8_t modbyte;
  u_int32_t *b2_0;
  u_int32_t old_dist;
  u_int32_t eip_inc;  /* EIP の増分 */
  long long work64;

  eip_inc = 2UL;  /* オペコードとオペランドの最初のバイト */

  modbyte = p386_text[(p386_EIP + 1UL) - P386_TEXT_START];

  B2_0SET;

  old_dist = (*b2_0);

  switch ((modbyte >> 3) & 7) {  /* 命令種別 */
  case 0:  /* TEST Imm ( なぜだかイレギュラー ) */
    p386_state = P386_STATE_UNSRPT;
    return 1;
  case 1:  /* 未定義 ? */
    p386_state = P386_STATE_UNSRPT;
    return 1;
  case 2:  /* NOT */
    (*b2_0) = (~old_dist);
    /* フラグ変化なし ! */
    break;
  case 3:  /* NEG */
    (*b2_0) = ((u_int32_t)(-((int32_t)old_dist)));

    if (*b2_0)
      RESET_FLAG(I386_FLAG_ZERO);
    else
      SET_FLAG(I386_FLAG_ZERO);

    if ((*b2_0) & 0x80000000UL)
      SET_FLAG(I386_FLAG_SIGN);
    else
      RESET_FLAG(I386_FLAG_SIGN);

    if ((*b2_0) == 0x80000000UL)
      SET_FLAG(I386_FLAG_OVFL);
    else
      RESET_FLAG(I386_FLAG_OVFL);

    break;
  case 4:  /* MUL */
    p386_state = P386_STATE_UNSRPT;
    return 1;
  case 5:  /* IMUL */
    work64 = (((long long)((int32_t) p386_EAX)) * ((long long)((int32_t)(*b2_0))));
    p386_EAX = ((u_int32_t)(((unsigned long long)work64) & 0xffffffffULL));
    p386_EDX = ((u_int32_t)((((unsigned long long)work64) >> 32) & 0xffffffffULL));

    if (p386_EAX & 0x80000000)
      {
        if (~p386_EDX)
          SET_FLAG(I386_FLAG_OVFL);
        else
          RESET_FLAG(I386_FLAG_OVFL);
      }
    else
      {
        if (p386_EDX)
          SET_FLAG(I386_FLAG_OVFL);
        else
          RESET_FLAG(I386_FLAG_OVFL);
      }

    break;
  case 6:  /* DIV */
    p386_state = P386_STATE_UNSRPT;
    return 1;
  case 7:  /* IDIV */
    old_dist = p386_EDX;
    work64 = ((long long)((((unsigned long long)p386_EDX) << 32) | ((unsigned long long) p386_EAX)));
    p386_EAX = ((u_int32_t)((int32_t)(work64 / ((long long)((int32_t)(*b2_0))))));
    p386_EDX = ((u_int32_t)((int32_t)(work64 % ((long long)((int32_t)(*b2_0))))));

    if (old_dist & (~p386_EDX) & 0x80000000UL)  /* 被除数がマイナスで余りがプラスの時の補正 */
      {
        if ((*b2_0) & 0x80000000UL)
          {
            p386_EAX--;
            p386_EDX += (*b2_0);
          }
        else
          {
            p386_EAX++;
            p386_EDX -= (*b2_0);
          }
      }
    break;
  default:
    assert(0);
  }

  p386_EIP += eip_inc;

  return 0;
}
