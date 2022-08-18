
.cpu cortex-m0plus
.thumb

# stack addr
.word 0x20002000
.word _start

.text
.thumb_func
.global _start
_start:

BL main

loop:
B loop
