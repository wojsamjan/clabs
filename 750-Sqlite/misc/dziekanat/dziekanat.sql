--
--  dziekanat.sql 
--
--  $URL: http://manta.univ.gda.pl/svn/wb/labs/c/750-Sqlite/schema/dziekanat.sql $
--  $Revision: 160 $

drop table if exists student;

create table student (
       id    	      integer		primary key autoincrement,
       nazwisko       varchar(128)	not null,
       imię           varchar(128)	not null,
       email	      varchar(128)	not null,
       data           datetime,
       uwagi          text
);


-- poniedziałek 08:30

insert into student(nazwisko, imię, email, data) 
       values('Plichta', 'Arek', 'aplichta@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Stenka', 'Adam', 'astenka@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Pilecki', 'Jerzy', 'jpilecki@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Pawłowski', 'Kamil', 'kpawlows@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Ślósarczyk', 'Kasia', 'kslosarc@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Reszka', 'Łukasz', 'lreszka@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Cała', 'Mariusz', 'mcala@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Dembowski', 'Marcin', 'mdembows@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Pietraszko', 'Marcin', 'mpietras@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Truszczyńska', 'Marta', 'mtruszcz@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Olejniczak', 'Paweł', 'polejnic@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Soróbka', 'Piotr', 'psorobka@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Szczepaniak', 'Piotr', 'pszczepa@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Tuptanowski', 'Piotr', 'ptuptano@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Wiśniewski', 'Piotr', 'pwisnie@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Zduniak', 'Paweł', 'pzduniak@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Wasilewski', 'Tomasz', 'twasilew@manta.univ.gda.pl', datetime('now'));


-- poniedziałek 12:00

insert into student(nazwisko, imię, email, data) 
       values('Jezionek', 'Artur', 'ajezione@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Lech', 'Anna', 'alech@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Kucz', 'Dominika', 'dkucz@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Kurek', 'Wojciech', 'jkurek@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Łopaciński', 'Karol', 'klopacin@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Lotkowski', 'Karol', 'klotkows@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Lotkowski', 'Łukasz', 'llotkows@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Irek', 'Marcin', 'mirek@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Juński', 'Michał', 'mjunski@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Korwel', 'Mateusz', 'mkorwel@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Leszko', 'Mateusz', 'mleszko@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Kalinowski', 'Tomasz', 'tkalinow@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Kusz', 'Wojciech', 'wkusz@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Romaszko', 'Wojciech', 'wromaszk@manta.univ.gda.pl', datetime('now'));


-- poniedziałek 14:00

insert into student(nazwisko, imię, email, data) 
       values('Brym', 'Anna', 'abrym@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Burchardt', 'Anna', 'aburchar@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Gardzielewska', 'Agnieszka', 'agardzie@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Białek', 'Grzegorz', 'gbialek@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Demecki', 'Grzegorz', 'gdemecki@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Bela', 'Jarosław', 'jbela@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Frymel', 'Jarosław', 'jfrymel@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Cichocki', 'Krzysztof', 'kcichocki@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Kurszewski', 'Krzysztof', 'kkurszew@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Cichy', 'Łukasz', 'lcichy@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Długowolski', 'Michał', 'mdlugowo@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Dziadyk', 'Mirosław', 'mdziadyk@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Dulęba', 'Paweł', 'pduleba@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Gołebiowki', 'Piotr', 'pgolebio@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imię, email, data) 
       values('Chmielecki', 'Tomasz', 'tchmiele@manta.univ.gda.pl', datetime('now'));
