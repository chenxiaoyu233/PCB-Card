	.cpu cortex-m0plus
	.arch armv6s-m
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"led.c"
	.text
	.align	1
	.global	main
	.syntax unified
	.code	16
	.thumb_func
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	sub	sp, sp, #8
	add	r7, sp, #0
	ldr	r3, .L7
	movs	r2, #2
	str	r2, [r3]
	ldr	r3, .L7+4
	ldr	r2, .L7+8
	str	r2, [r3]
	ldr	r3, .L7+12
	movs	r2, #255
	str	r2, [r3]
.L6:
	movs	r3, #0
	str	r3, [r7, #4]
	b	.L2
.L5:
	movs	r2, #1
	ldr	r3, [r7, #4]
	lsls	r2, r2, r3
	ldr	r3, .L7+12
	str	r2, [r3]
	movs	r3, #0
	str	r3, [r7]
	b	.L3
.L4:
	ldr	r3, [r7]
	adds	r3, r3, #1
	str	r3, [r7]
.L3:
	ldr	r3, [r7]
	ldr	r2, .L7+16
	cmp	r3, r2
	ble	.L4
	ldr	r3, [r7, #4]
	adds	r3, r3, #1
	str	r3, [r7, #4]
.L2:
	ldr	r3, [r7, #4]
	cmp	r3, #7
	ble	.L5
	b	.L6
.L8:
	.align	2
.L7:
	.word	1073877036
	.word	1342178304
	.word	1431655765
	.word	1342178324
	.word	49999
	.size	main, .-main
	.ident	"GCC: (Homebrew ARM GCC 9.5.0) 9.5.0"
