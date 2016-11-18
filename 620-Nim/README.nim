17.X.2003

NIM

int FindGoodMove(int nCoins) {
   for (ka¿dego mo¿liwego ruchu) {
     Oblicz warto¶æ uk³adu po wykonaniu tego ruchu.
     Je¶li pozycja jest z³a (prowadzi do przegranej),
        to wykonaj ten ruch.
   }
   Zwróæ NoGoodMove wskazuj±c w ten sposób, 
   ¿e nie ma dobrego ruchu.
}

gdzie, np. NoGoodMove==-1.

int FindGoodMove(int nCoins) {
   int nTaken;
   for (nTaken=1; nTaken<=MaxTake; nTaken++) {
      if (isBadPosition(nCoins-nTaken))
         return nTaken;
   }
   return NoGoodMove;
}

bool IsBadPosition(int nCoins) {
   if (nCoins==1) return TRUE;
   return (FindGoodMove(nCoins)==NoGoodMove);  
}
