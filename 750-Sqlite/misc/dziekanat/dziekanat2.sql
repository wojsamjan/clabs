--
--  dziekanat.sql 
--
--  $URL: http://manta.univ.gda.pl/svn/wb/labs/c/750-Sqlite/schema/dziekanat2.sql $
--  $Revision: 160 $

drop table if exists student;

create table student (
       id    	      integer		primary key autoincrement,
       nazwisko       varchar(128)	not null,
       imie           varchar(128)	not null,
       email	      varchar(128)	not null,
       data           datetime,
       uwagi          text
);


insert into student(nazwisko, imie, email, data) 
       values('Plichta', 'Arek', 'aplichta@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imie, email, data) 
       values('Stenka', 'Adam', 'astenka@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imie, email, data) 
       values('Dembowski', 'Marcin', 'mdembows@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imie, email, data) 
       values('Pilecki', 'Jerzy', 'jpilecki@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imie, email, data) 
       values('Pawłowski', 'Kamil', 'kpawlows@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imie, email, data) 
       values('Ślósarczyk', 'Kasia', 'kslosarc@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imie, email, data) 
       values('Reszka', 'Łukasz', 'lreszka@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imie, email, data) 
       values('Cała', 'Mariusz', 'mcala@manta.univ.gda.pl', datetime('now'));
insert into student(nazwisko, imie, email, data) 
       values('Pietraszko', 'Marcin', 'mpietras@manta.univ.gda.pl', datetime('now'));
