
-- $Revision: 1.3 $
-- $Date: 2004/03/09 20:57:11 $

-- Funkcja obliczaj±ca silniê

module Factorial where
fac 0 = 1
fac n = n * fac (n-1)
			 
