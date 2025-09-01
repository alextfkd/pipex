cc mal_code.c -o segv.o                   
cc exit0_code.c -o exit0.o
cc exit1_code.c -o exit1.o
chmod +x segv.o 
chmod +x exit0.o      
chmod +x exit1.o

PIPEX=./pipex
INFILE=./srcs/main.c

chmod 0 $INFILE

I=1
CMD1='cat'
CMD2='wc -l'

OUTFILE=outfile_$I.out
ANSFILE=outfile_$I.ans
echo "--- test $I: $PIPEX $INFILE '$CMD1' '$CMD2' $OUTFILE ---"
rm -f $OUTFILE $ANSFILE
$PIPEX $INFILE "$CMD1" "$CMD2" $OUTFILE
< $INFILE $CMD1 | $CMD2 > $ANSFILE
diff -u $OUTFILE $ANSFILE
if [ $? -eq 0 ]; then
	echo "--> [PASS] "
else
	echo "--> [FAIL] "
fi;

I=2
CMD1='grep if'
CMD2='wc -l'

OUTFILE=outfile_$I.out
ANSFILE=outfile_$I.ans
echo "--- test $I: $PIPEX $INFILE '$CMD1' '$CMD2' $OUTFILE ---"
rm -f $OUTFILE $ANSFILE
$PIPEX $INFILE "$CMD1" "$CMD2" $OUTFILE
< $INFILE $CMD1 | $CMD2 > $ANSFILE
diff -u $OUTFILE $ANSFILE
if [ $? -eq 0 ]; then
	echo "--> [PASS] "
else
	echo "--> [FAIL] "
fi;

I=3
CMD1='./exit0.o'
CMD2='wc'

OUTFILE=outfile_$I.out
ANSFILE=outfile_$I.ans
echo "--- test $I: $PIPEX $INFILE '$CMD1' '$CMD2' $OUTFILE ---"
rm -f $OUTFILE $ANSFILE
$PIPEX $INFILE "$CMD1" "$CMD2" $OUTFILE
< $INFILE $CMD1 | $CMD2 > $ANSFILE
diff -u $OUTFILE $ANSFILE
if [ $? -eq 0 ]; then
	echo "--> [PASS] "
else
	echo "--> [FAIL] "
fi;

I=4
CMD1='./exit1.o'
CMD2='wc'

OUTFILE=outfile_$I.out
ANSFILE=outfile_$I.ans
echo "--- test $I: $PIPEX $INFILE '$CMD1' '$CMD2' $OUTFILE ---"
rm -f $OUTFILE $ANSFILE
$PIPEX $INFILE "$CMD1" "$CMD2" $OUTFILE
< $INFILE $CMD1 | $CMD2 > $ANSFILE
diff -u $OUTFILE $ANSFILE
if [ $? -eq 0 ]; then
	echo "--> [PASS] "
else
	echo "--> [FAIL] "
fi;

I=5
CMD1='./segv.o'
CMD2='wc'

OUTFILE=outfile_$I.out
ANSFILE=outfile_$I.ans
echo "--- test $I: $PIPEX $INFILE '$CMD1' '$CMD2' $OUTFILE ---"
rm -f $OUTFILE $ANSFILE
$PIPEX $INFILE "$CMD1" "$CMD2" $OUTFILE
< $INFILE $CMD1 | $CMD2 > $ANSFILE
diff -u $OUTFILE $ANSFILE
if [ $? -eq 0 ]; then
	echo "--> [PASS] "
else
	echo "--> [FAIL] "
fi;

I=6
CMD1='grep if'
CMD2='./exit0.o'

OUTFILE=outfile_$I.out
ANSFILE=outfile_$I.ans
echo "--- test $I: $PIPEX $INFILE '$CMD1' '$CMD2' $OUTFILE ---"
rm -f $OUTFILE $ANSFILE
$PIPEX $INFILE "$CMD1" "$CMD2" $OUTFILE
< $INFILE $CMD1 | $CMD2 > $ANSFILE
diff -u $OUTFILE $ANSFILE
if [ $? -eq 0 ]; then
	echo "--> [PASS] "
else
	echo "--> [FAIL] "
fi;

I=7
CMD1='grep if'
CMD2='./exit1.o'

OUTFILE=outfile_$I.out
ANSFILE=outfile_$I.ans
echo "--- test $I: $PIPEX $INFILE '$CMD1' '$CMD2' $OUTFILE ---"
rm -f $OUTFILE $ANSFILE
$PIPEX $INFILE "$CMD1" "$CMD2" $OUTFILE
< $INFILE $CMD1 | $CMD2 > $ANSFILE
diff -u $OUTFILE $ANSFILE
if [ $? -eq 0 ]; then
	echo "--> [PASS] "
else
	echo "--> [FAIL] "
fi;

I=8
CMD1='grep if'
CMD2='./segv.o'

OUTFILE=outfile_$I.out
ANSFILE=outfile_$I.ans
echo "--- test $I: $PIPEX $INFILE '$CMD1' '$CMD2' $OUTFILE ---"
rm -f $OUTFILE $ANSFILE
$PIPEX $INFILE "$CMD1" "$CMD2" $OUTFILE
< $INFILE $CMD1 | $CMD2 > $ANSFILE
diff -u $OUTFILE $ANSFILE
if [ $? -eq 0 ]; then
	echo "--> [PASS] "
else
	echo "--> [FAIL] "
fi;