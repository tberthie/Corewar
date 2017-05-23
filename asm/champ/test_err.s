   .name   "zork"     
	.comment      	"just a basic living prog"		
l2:  sti r1 , %:live , %1
   and r1,%0,r1   
 live: live  %1
zjmp		%:live
ld  2,r1
	ld %-23	,r3		
ld %:l2,r3
ld %:live,r3



