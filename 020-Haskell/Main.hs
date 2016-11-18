
-- $Revision: 1.2 $
-- $Date: 2004/03/09 20:51:28 $

module Main where
import Factorial
main = putStr ("witaj swiecie\n" ++ 
	       "44! to " ++ show (fac 44) ++ "\n")

-- aby zapisaæ `witaj swiecie' do pliku "out.txt":
-- main = writeFile "out.txt" ("witaj swiecie\n" ++ show (fac 20))

	       
