./asm_zaz $1 > test_off.txt
./asm $1 > test_off1.txt
if [ ! -e test_off1.txt ] || [ -e *.cor ] || [ diff test_off.txt test_off1.txt ]
then
	echo $1 "invalide1: [KO]"
else
	echo "invalide1: [OK]"
fi
if [ -e test_off1.txt ]
then
rm test_off1.txt
fi
rm test_off.txt
if [ -e *.cor ]
then
rm *.cor
fi
