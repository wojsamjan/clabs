#!/usr/bin/ruby 
#  
#  $URL: http://manta.univ.gda.pl/svn/wb/labs/c/750-Sqlite/schema/dziekanat3.rb $ 
#  $Revision: 161 $ 
#
#  Active Record Basics:  Relation between Tables
#   

require "rubygems"
require_gem "activerecord"

ActiveRecord::Base.pluralize_table_names = false

ActiveRecord::Base.establish_connection( 
    :adapter => 'sqlite3',
    :dbfile => 'dziekanat3.sqlite3'
)

#  http://localhost:8808/doc_root/activerecord-1.14.4/rdoc/index.html
#
#  Adds the following methods for retrieval and query. collection is
#  replaced with the symbol passed as the first argument, so
#  has_and_belongs_to_many :przedmiot would add among others
#  przedmiot.empty?

class Student < ActiveRecord::Base
  has_and_belongs_to_many :przedmiot

  def zapisz_na_przedmiot(p, nr)
    przedmiot.push_with_attributes(p, :grupa => nr, :data => Time.now)
  end

end

class Przedmiot < ActiveRecord::Base
  has_and_belongs_to_many :student

  def zapisz_studenta(s, nr)
    student.push_with_attributes(s, :grupa => nr, :data => Time.now)
  end

end

#  klasa automatycznie tworzona
#class Przedmiot_Student < ActiveRecord::Base
#end

require "pp"

#create table student (
#       id    	      integer		primary key autoincrement,
#       nazwisko      varchar(128)	not null,
#       imie          varchar(128)	not null,
#       email	      varchar(128)	not null,
#       data          datetime,
#       uwagi         text
#);
#create table przedmiot (
#       id    	      integer		primary key autoincrement,
#       nazwa 	      varchar(128)	not null,
#       kod 	      varchar(128)	not null,
#       rodzaj	      varchar(128)	not null,
#       data          datetime,
#       uwagi         text
#);
#create table przedmiot_student (
#       przedmiot_id  int      not null,
#       student_id    int      not null,
#       grupa	      int      not null default 0,
#       data          datetime,
#       ...
#);

an_student = Student.find_by_nazwisko('Ślósarczyk')

pp an_student

#  wyszukujemy pierwszy obiekt spełniający podane warunki
an_przedmiot = Przedmiot.find_by_kod_and_rodzaj('jp', 'laboratorium')
an_student.zapisz_na_przedmiot(an_przedmiot, 2)

#  j.w.
an_przedmiot = Przedmiot.find_by_kod_and_rodzaj('webcmpt', 'seminarium')
an_student.zapisz_na_przedmiot(an_przedmiot, 0)  # jest tylko 1 grupa

#  lista przedmiów na jakie jest zapisany student z id 6
an_student = Student.find(6)
lista_przedmiotow = an_student.przedmiot

pp lista_przedmiotow[0].nazwa
pp lista_przedmiotow[1].nazwa

#  zapisujemy studenta na przedmiot i do grupy

an_przedmiot = Przedmiot.find_by_kod_and_rodzaj('jp', 'wykład')

pp an_przedmiot
an_przedmiot.zapisz_studenta(an_student, 0)
