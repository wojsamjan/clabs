--
--  projekt bazy danych dla przedmiotu języki programowania
--

drop table if exists studenci;

create table studenci (
  id        integer       primary key autoincrement,
  nazwisko  varchar(128)  not null,
  imię      varchar(128)  not null,
  login     varchar(128)  not null collate nocase,
  data      datetime,
  uwagi     text          default ''
);

--  zaliczenia.sql

drop table if exists zaliczenia;

create table zaliczenia (
  id          integer       primary key autoincrement,
  student_id  integer       not null,  -- klucz obcy
  ocena       varchar(128)  default 'unknown' collate nocase,
  kiedy       datetime,
  termin      text          default 'pierwszy'
);

-- wyzwalacz automatycznie wstawiający datę w polu kiedy
create trigger wstaw_do_zaliczeń_kiedy after insert on zaliczenia
begin
  update zaliczenia set kiedy = datetime('now') where rowid = new.rowid;
end;
