// PRELOADING OOBRAZKÓW:

var obrazki=new Array('skoczek_on.gif','skoczek_down.gif');
var imgpath=new Array('./img/');
var pics=new Array();

for(i=0;i<obrazki.length;i++)
    {
         pics[i]=new Image();
         pics[i].src=imgpath+"/"+obrazki[i];
    }



// OBS£UGA GUZIKÓW UMOZLIWIA UMIESZCZENIE NA STRONIE 52 TAKICH SAMYCH GUZIKÓW


var PrzechowajNazwe;

function on(Name,multi)
{
PrzechowajNazwe = Name;
if (multi==1) {SwitchImg = PrzechowajNazwe.substr(0,PrzechowajNazwe.length-2) + "_on.gif";}
else {SwitchImg = PrzechowajNazwe + "_on.gif";}
document.images[Name].src=SwitchImg;
} 



function off(multi)
{
if (multi)
{
SwitchImg = PrzechowajNazwe.substr(0,PrzechowajNazwe.length-2) + "_off.gif";
}
else{SwitchImg = PrzechowajNazwe + "_off.gif";}
document.images[PrzechowajNazwe].src=SwitchImg;
} 


function down(Name,multi)
{
PrzechowajNazwe = Name;
if (multi==1) {SwitchImg = PrzechowajNazwe.substr(0,PrzechowajNazwe.length-2) + "_down.gif";}
else {SwitchImg = PrzechowajNazwe + "_down.gif";}
document.images[Name].src=SwitchImg;
} 


function up(Name,multi)
{
on(Name,multi);
} 


function go(pole)
{
document.forms[0].elements[0].value=pole;
document.forms[0].submit();
}
