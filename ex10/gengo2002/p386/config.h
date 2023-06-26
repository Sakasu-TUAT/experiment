/*
´Ä¶­ÀßÄê
*/

#if !defined _CONFIG_H_
#define _CONFIG_H_

#define P386_TEXT_START  0x00000000UL
#define P386_TEXT_LIMIT  0x0000ffffUL
#define P386_TEXT_SIZE   ((P386_TEXT_LIMIT) + 1UL)

#define P386_DATA_START  0x40000000UL
#define P386_DATA_LIMIT  0x0000ffffUL
#define P386_DATA_SIZE   ((P386_DATA_LIMIT) + 1UL)

#define P386_STACK_START 0xc0000000UL
#define P386_STACK_LIMIT 0x0000ffffUL
#define P386_STACK_SIZE  ((P386_STACK_LIMIT) + 1UL)

typedef unsigned int u_int32_t;
typedef unsigned char u_int8_t;

#endif /* _CONFIG_H_ */
