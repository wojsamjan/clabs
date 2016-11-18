#!/bin/sh

Max=50;
Min=1;
w=100;
x=0.27;
y=0.33;

Ground=1000; 

LO=`echo $Ground $Min|awk '{print ($1+$2)}'`
HI=`echo $Ground $Max|awk '{print ($1+$2)}'`

while [ $LO -le $HI ]
do
  n=`echo $Max $HI $LO|awk '{print ($1-($2-$3))}'`
  echo 'making picture' $n 'of' $Max
  s=`echo $n $Max|awk '{print (1-($1-1)/$2)}'`;
  julia -x $x -y $y -w $w -s $s -n 100 -c colormaps/volcano.map>$LO.pic.ppm
  ppmtogif $LO.pic.ppm>$LO.pic.gif
  LO=`expr $LO + 1`
done

echo 'Making zoom movie'
gifmerge -l0 -10 *.pic.gif>../gif/example.gif
rm *.pic.ppm
rm *.pic.gif

echo 'Showing zoom movie'
xanim ../gif/example.gif

