.name 		"Turox"
.comment	"your mother so big, can't be malloc"

start:
	ld 		%0, r8
	ld		192, r5
	sti 	r1, %:alive, %1
	sti 	r1, %:step2, %1
	sti 	r1, %:step1, %1
	fork 	%:step2
	zjmp	%:start
	ld 		%251658255, r2
	ld 		%251658255, r3

alive:
	live	%42
	ld 		%274, r11
	ld 		%0, r8
	fork 	%:step2
	live 	%-1
	ld 		%276, r8
	st 		r2, -301

step1:
	live	%42
	ld		%70, r10
	ld		%85, r11
	ld		%67, r12
	ld		%75, r13
	aff		r10
	aff		r11
	aff		r12
	aff		r13
	ld		%89, r11
	ld		%79, r12
	ld		%85, r13
	aff		r11
	aff		r12
	aff		r13
	ld		%0, r13
	zjmp	%:step1


step2:
	live	%42
	fork 	%:step1
	ld 		%0, r8
	sti		r5, %:start, %7
	zjmp	%:start
