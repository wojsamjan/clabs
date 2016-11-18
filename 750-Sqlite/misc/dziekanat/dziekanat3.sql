--
--  dziekanat3.sql 
--
--  $URL: http://manta.univ.gda.pl/svn/wb/labs/c/750-Sqlite/schema/dziekanat3.sql $
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

drop table if exists przedmiot;

create table przedmiot (
       id    	      integer		primary key autoincrement,
       nazwa 	      varchar(128)	not null,
       kod 	      varchar(128)	not null,
       rodzaj	      varchar(128)	not null,
       data           datetime,
       uwagi          text
);

drop table if exists przedmiot_student;

create table przedmiot_student (
       przedmiot_id   int      not null,
       student_id     int      not null,
       grupa	      int      not null default 0,
       data           datetime,
       constraint fk_ps_przedmiot foreign key (przedmiot_id) references przedmiot(id),
       constraint fk_ps_student foreign key (student_id) references student(id),
       primary key (przedmiot_id, student_id)
);


-- Student

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

-- Przedmiot

insert into przedmiot(nazwa, kod, rodzaj, data) 
       values('Języki Programowania', 'jp', 'wykład', datetime('now'));
insert into przedmiot(nazwa, kod, rodzaj, data) 
       values('Języki Programowania', 'jp', 'laboratorium', datetime('now'));
insert into przedmiot(nazwa, kod, rodzaj, data) 
       values('Obliczenia w sieci WWW', 'webcmpt', 'seminarium', datetime('now'));
