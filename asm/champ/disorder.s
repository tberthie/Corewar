live: live %1
.name "zork"
l2: sti r1,%:live,%1
.comment "just a basic living prog"
and r1,%0,r1
zjmp %:live
