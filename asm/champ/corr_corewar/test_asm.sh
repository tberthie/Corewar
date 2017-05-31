make
./asm_zaz valid.s
mv valid.cor valid2.cor
./asm valid.s
if [ ! -e valid.cor ] || [ diff valid.cor valid2.cor ]
then
	echo $1 "valide: [KO]"
fi
if [ -e valid.cor ]
then
	rm valid.cor
fi
rm valid2.cor
sh function_asm.sh invalid1.s
sh function_asm.sh invalid2.s
sh function_asm.sh invalid3.s
sh function_asm.sh invalid4.s
sh function_asm.sh invalid5.s
sh function_asm.sh invalid6.s
sh function_asm.sh invalid7.s
sh function_asm.sh invalid8.s
sh function_asm.sh invalid9.s
sh function_asm.sh invalid10.s
sh function_asm.sh invalid11.s
sh function_asm.sh invalid12.s
sh function_asm.sh invalid13.s
sh function_asm.sh invalid14.s
sh function_asm.sh invalid15.s
sh function_asm.sh invalid16.s
sh function_asm.sh invalid17.s
sh function_asm.sh invalid18.s
sh function_asm.sh invalid19.s
sh function_asm.sh invalid20.s
sh function_asm.sh invalid21.s
sh function_asm.sh invalid22.s
sh function_asm.sh invalid23.s
sh function_asm.sh invalid24.s
sh function_asm.sh invalid25.s
sh function_asm.sh invalid26.s
sh function_asm.sh invalid27.s
sh function_asm.sh invalid28.s
sh function_asm.sh invalid29.s
sh function_asm.sh invalid30.s
sh function_asm.sh invalid31.s
sh function_asm.sh invalid32.s
sh function_asm.sh invalid33.s
sh function_asm.sh invalid34.s
sh function_asm.sh invalid35.s
sh function_asm.sh invalid36.s
sh function_asm.sh invalid37.s
sh function_asm.sh invalid38.s
sh function_asm.sh invalid39.s
sh function_asm.sh invalid40.s
sh function_asm.sh invalid41.s
sh function_asm.sh invalid42.s
sh function_asm.sh invalid43.s
sh function_asm.sh invalid44.s
sh function_asm.sh invalid45.s
sh function_asm.sh invalid46.s
sh function_asm.sh invalid47.s
sh function_asm.sh invalid48.s
sh function_asm.sh invalid49.s
sh function_asm.sh invalid50.s
sh function_asm.sh invalid51.s
sh function_asm.sh invalid52.s
sh function_asm.sh invalid53.s
sh function_asm.sh invalid54.s
sh function_asm.sh invalid55.s
sh function_asm.sh invalid56.s
sh function_asm.sh invalid57.s
sh function_asm.sh invalid58.s
sh function_asm.sh invalid59.s
sh function_asm.sh invalid60.s
sh function_asm.sh invalid61.s
sh function_asm.sh invalid62.s
sh function_asm.sh invalid63.s
sh function_asm.sh invalid64.s
sh function_asm.sh invalid65.s
sh function_asm.sh invalid66.s
sh function_asm.sh invalid67.s
sh function_asm.sh invalid68.s
sh function_asm.sh invalid69.s
sh function_asm.sh invalid70.s
sh function_asm.sh invalid71.s
sh function_asm.sh invalid72.s
sh function_asm.sh invalid73.s
sh function_asm.sh invalid74.s
sh function_asm.sh invalid75.s
sh function_asm.sh invalid76.s
sh function_asm.sh invalid77.s
sh function_asm.sh invalid78.s
sh function_asm.sh invalid79.s
sh function_asm.sh invalid80.s
sh function_asm.sh invalid81.s
sh function_asm.sh invalid82.s
sh function_asm.sh invalid83.s
sh function_asm.sh invalid84.s
sh function_asm.sh invalid85.s
sh function_asm.sh invalid86.s
sh function_asm.sh invalid87.s
sh function_asm.sh invalid88.s
sh function_asm.sh invalid89.s
sh function_asm.sh invalid90.s
sh function_asm.sh invalid91.s
sh function_asm.sh invalid92.s
make fclean
