#!/usr/bin/ruby 
#  
#  $URL: http://manta.univ.gda.pl/svn/wb/labs/c/750-Sqlite/schema/dziekanat.rb $ 
#  $Revision: 155 $ 
#
#  Active Record Basics
#
#  Przykład 1


require "rubygems"
require_gem "activerecord"

ActiveRecord::Base.pluralize_table_names = false

ActiveRecord::Base.establish_connection( 
    :adapter => 'sqlite3',
    :dbfile => 'dziekanat.sqlite3'
)

class Student < ActiveRecord::Base
end

require "pp"

student = Student.find(5)

pp student

#pp Student.columns.map { |c| c.name } 

#pp Student.columns_hash['imię']

#puts("mapping SQL types to Ruby types")

#create table student (
#       id    	      integer		primary key autoincrement,
#       nazwisko      varchar(128)	not null,
#       imię          varchar(128)	not null,
#       email	      varchar(128)	not null,
#       data          datetime,
#       uwagi         text
#);

#pp student.nazwisko.class
#pp student.data.class

#  If you work with legacy schemas or have databases
#  in languagues other than English, ... 
#  p. 205, Agile Web Development with Rails
#          

#  pp student.imię.class nie działa -- utf-8 w nazwie!
#  pp student[:imię] -- j.w.
#  ale można tak

#pp student['imię'].class
#pp student['nazwisko'].class

#  find..

#  nie działa utf-8
#pp Student.find_by_imię('Kasia')
#  OK
#pp Student.find_by_nazwisko('Truszczyńska')
#  Bad
pp Student.find(:all, :nazwisko  => 'Truszczyńska' )
#pp Student.find(:all, 'nazwisko' => 'Truszczyńska' )

#pp Student.find(:all, :condition => [ "imię = ?", "Marcin" ])

#pp Student.find( :all, 
#                 :conditions => [ "imię = ?", 'Marcin' ],
#                 :order => "nazwisko DESC",
#                 :limit => 2
#               )

#pp Student.find_by_sql("select nazwisko, imię from student where imię='Marcin'")

