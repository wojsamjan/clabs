.mode col
.headers on
.nullvalue NULL
/*
      Michael Owens
      The Definitive Guide to SQLite
      Chapter4: SQL
     
      sqlite3 foods.db < foods.sql
*/

-- verb   subject      predicate
-- SELECT * FROM foods WHERE name='JujyFruit' AND type_id=9;


drop table if exists contacts ;


-- CREATE [tmp] TABLE table_name (column_definitions [, constraints]) ;

create table contacts 
       (id integer primary key, 
       name text non null collate nocase,
       phone text not null default 'unknown',
       unique (name, phone));

--  ALTER TABLE table { RENAME TO name | ADD COLUMN column_def } ;

alter table contacts 
      add column email text not null default '' collate nocase;

-- INSERT INTO table_name VALUES(value_list) ;

INSERT INTO contacts VALUES(1, 'Włodek', 'unknown', 'wlodek@home.org');
INSERT INTO contacts VALUES(2, 'Renia', '+48 058 111 2222', 'renia@home.org');
INSERT INTO contacts VALUES(3, 'Bazylek', 'unknown', '');
