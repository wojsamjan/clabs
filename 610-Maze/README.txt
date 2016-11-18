   14.01.2002

*  Przygotował Szymon Kochański <skochans@manta.univ.gda.pl>


1. Algorytm generowania labiryntu. Definicja labiryntu doskonałego.

Sama idea algorytmu została zaczerpnięta ze strony:

     http://www.flint.umich.edu/Departments/ITS/crac/maze.algorithm.html

Przedstawiony tam (w postaci słownej) algorytm jest niezwykle
prymitywny, ale ,,w prostocie siła'', i choć stworzony przeze mnie
algorytm jest dużo bardziej skomplikowany (wprowadziłem m.in. dwa
rodzaje ścian), to jednak tamten był ,,ziarenkiem'', które pchnęło 
mnie do działania i przekonało, że generowanie labiryntów wcale 
nie jest problemem aż tak trudnym, jakby się wydawało. 
Ale do rzeczy...

Oznaczenia:

    '#' -- ściana ,,zwykła'', czyli ,,rozwalalna''
    '@' -- ściana ,,nierozwalalna''
    ' ' -- ścieżka

 ###########   	Na początku stwórzmy planszę i zapełnijmy ją ścianami
 ###########
 ###########
 ###########
 ###########
 ###########
 ###########
 ###########
 ###########
 ###########
 ###########


@@@@@@@@@@@@@	Teraz dla pewności otoczmy naszą planszę 
@###########@	,,niezniszczlnym'' murem.
@###########@
@###########@
@###########@
@###########@
@###########@
@###########@
@###########@
@###########@	(Co prawda mój algorytm poradziłby sobie i bez tego,
@###########@	ale ,,pewności nigdy za wiele'').
@###########@
@@@@@@@@@@@@@

@@@@@@@@@@@@@	No to teraz trzeba się zdecydować od czego zacząć.	
@###########@	Proponuję zacząć w lewym górnym rogu.
@# #########@	Burzymy jedną ścianę.
@###########@
@###########@
@###########@
@###########@
@###########@
@###########@
@###########@
@###########@
@###########@
@@@@@@@@@@@@@

@@@@@@@@@@@@@	Teraz wybieramy punkt oddalony o dwa od bieżącego punktu,
@###########@	sprawdzamy czy jest ,,rozwalalną'' ścianą i czy jest otoczony
@#   #######@	przez ściany. Jeśli te warunki są spełnione i ściana po
@###########@	drodze też jest rozwalalną ścianą, to idziemy do tego punktu
@###########@	rozwalając ścianę po drodze. Punkt, do którego doszliśmy 
@###########@	oznaczamy jako ścieżkę.
@###########@
@###########@	Ja poszedłem poziomo, ale równie dobrze można było iść pionowo.
@###########@
@###########@
@###########@
@###########@
@@@@@@@@@@@@@

@@@@@@@@@@@@@ 	Powtarzamy tę procedurę losowo wybierając kierunek wśród 
@###########@	wszystkich dostępnych.
@#   #   ###@
@### ### ###@	Jeżeli wejdziemy w ,,ślepą uliczkę'', to cofamy się do miejsca
@###     ###@	gdzie mieliśmy więcej możliwości. Ja to rozwiązałem
@###########@	za pomocą rekurencji, ale są też inne sposoby.
@###########@
@###########@
@###########@
@###########@
@###########@
@###########@
@@@@@@@@@@@@@

@@@@@@@@@@@@@	A tak może wyglądać przykładowy labirynt wygenerowany przez
@###########@	algorytm.
@#   #     #@
@### ### # #@
@# #     # #@
@# ####### #@
@# #       #@
@# # ### ###@
@#     #   #@
@### # #####@
@#   #     #@
@###########@	
@@@@@@@@@@@@@

(porównaj z: http://www.flint.umich.edu/Departments/ITS/crac/maze.algorithm.html)


Co ciekawe, labirynt wygenerowany w ten sposób jest tzw. labiryntem
doskonałym, co oznacza, że nie ma on pętli, cykli ani niedostępnych
obszarów. Z każdego punktu prowadzi dokładnie jedna droga do dowolnego
innego punktu labiryntu. Taki labirynt ma zawsze dokładnie jedno
rozwiązanie. (Definicja na podstawie: http://www.astrolog.org/labyrnth/glossary.htm
http://www.astrolog.org/labyrnth/algrithm.htm)

Ze względu na specyficzne właściwości labiryntów doskonałych wejście
(początek) i wyjście (koniec) można umieścić w dowolnym punkcie.

Algorytm jest uniwersalny i pozwala genrować labirynty o kształtach 
innych niż prostokąt.


                               @@@
                               @ @
                             @@@ @@@
                             @   # @
                           @@@ ### @@@
                           @   #   # @
                         @@@## # ### @@@
                         @       #     @
                       @@@ ######### # @@@
                       @   #   #   # #   @
                     @@@ # # ### # # ### @@@
                     @   #   #   # # #   # @
                   @@@ ##### ### # # ### # @@@
                   @     #       #     #     @
                   @@@@@@@@@@@@@@@@@@@@@@@@@@@


2. Algorytm rozwiązywania labiryntu.

Do przechodzenia labiryntu użyłem algorytmu przedstawionego na
wykładzie dr Włodzimierza Bzyla. Algorytm ten jest opisany m.in. 
na stronie http://www.astrolog.org/labyrnth/algrithm.htm
(pod nazwą ,,Recursive backtracker'') oraz na
http://webpages.charter.net/kevinast/AmazingMazes pod nazwą ,,NESW''.

3. Ciekawe adresy.

Ponieważ wcale nie tak łatwo jest odnaleźć ciekawe strony dotyczące
labiryntów, poniżej zamieszczam kilka adresów.

http://www.mazebuilder.com/
   Generowanie labiryntów online. Różne kształty (także w kształcie słów).

http://www.billsgames.com/mazegenerator/
   Jeszcze jedna strona generująca labirynty online.

http://webpages.charter.net/kevinast/AmazingMazes
   Dużo teorii. Przykładowe kody zródłowe. Aplety testujace skutecznosc 
   różnych algorytmów przechodzacych labirynty. Skarbnica wiedzy.

http://web.kyoto-inet.or.jp/people/eisaku/e_maze/ 
   Duża kolekcja labiryntów o ciekawych kształtach. Dobre do wydrukowania 
   i powieszenia sobie na scianę. :)

http://www.billsgames.com/invisiblemaze/
   Interaktywna gra polegajaca na przechodzeniu stopniowo odsłaniajacego się
   labiryntu. Doskonała zabawa dla dzieci (i nie tylko). 
