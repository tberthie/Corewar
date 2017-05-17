.name 		"LOL"
.comment	"your mother so big, can't be malloc"

start:
	ld %251658255, r2
	ld %251658255, r3
	ld %274, r11
	ld %0, r8
	fork %:step2
	live %-1
	ld %276, r8
	st r2, -301

step1:
	st r1, 11
	st r2, 11
	st r3, 11

step2:
	sti r10, r11, r12
	sti r7, r8, r12
	sti r10, r11, r12
	sti r10, r11, r12
	sti r10, r11, r12
	sti r10, r11, r12
