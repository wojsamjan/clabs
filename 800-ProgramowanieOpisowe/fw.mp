%-----------------------------------------------------------
% (WB)                               Friday, 30 October 1998
%-----------------------------------------------------------
input boxes
%-----------------------------------------------------------

verbatimtex
\font\rm=plr7
\rm
etex

def arrow_join(suffix boxa, boxb) =
  drawarrow boxa.s--boxb.n cutbefore bpath boxa cutafter bpath boxb;
enddef;

% unit of measure
  uu:=0.903cm; % E/3
% default font
  defaultfont:="plr7";
% arrow
  ahangle:=30;
% 
  pickup pencircle scaled 0.3pt;
  
%-----------------------------------------------------------
beginfig(1); % Tree for fw.w

pair t[];
pair branch[];

branch[0]:=dir -36 rotated -90 scaled 2uu;
branch[1]:=dir 36 rotated -90 scaled 2uu;
branch[2]:=dir -36 rotated -90 scaled 2uu;
branch[3]:=dir 36 rotated -90 scaled 2uu;
branch[4]:=dir -36 rotated -90 scaled 2uu;
branch[5]:=dir 36 rotated -90 scaled 2uu;

t[1]=origin;
t[3]=t[1]+branch[1];
t[6]=t[3]+branch[2];
t[7]=t[3]+branch[3];
t[12]=t[6]+branch[4];
t[13]=t[6]+branch[5];
t[15]=t[7]+branch[5];

defaultdx:=7pt;
defaultdy:=0pt;

boxjoin(a.se-a.sw=b.se-b.sw);

boxit.v1(btex\strut chocia¿ etex);
v1.c=t[1];
drawboxed(v1);

boxit.v3(btex\strut krowie etex);
v3.c=t[3];
drawboxed(v3);

boxit.v6(btex\strut dasz etex);
v6.c=t[6];
drawboxed(v6);

boxit.v7(btex\strut nie etex);
v7.c=t[7];
drawboxed(v7);

boxit.v12(btex\strut czekolady etex);
v12.c=t[12];
drawboxed(v12);

boxit.v13(btex\strut kakao etex);
v13.c=t[13];
drawboxed(v13);

boxit.v15(btex\strut wydoisz etex);
v15.c=t[15];
drawboxed(v15);

arrow_join(v1,v3);
arrow_join(v3,v6);
arrow_join(v3,v7);
arrow_join(v6,v12);
arrow_join(v6,v13);
arrow_join(v7,v15);

defaultdx:=0.903uu;
defaultdy:=1uu;

%pickup pencircle scaled 0.2pt;
%boxjoin();
%boxit.frame(currentpicture);
%drawboxed(frame);

endfig;

end

