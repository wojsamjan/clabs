#!/usr/bin/ruby 
#  
#  $URL: http://manta.univ.gda.pl/svn/wb/labs/c/750-Sqlite/schema/dziekanat2.rb $ 
#  $Revision: 160 $ 
#
#  Active Record Basics
#
#  Przykład 1


require "rubygems"
require_gem "activerecord"

ActiveRecord::Base.pluralize_table_names = false

ActiveRecord::Base.establish_connection( 
    :adapter => 'sqlite3',
    :dbfile => 'dziekanat2.sqlite3'
)

class Student < ActiveRecord::Base
end

require "pp"

#create table student (
#       id    	      integer		primary key autoincrement,
#       nazwisko      varchar(128)	not null,
#       imie          varchar(128)	not null,
#       email	      varchar(128)	not null,
#       data          datetime,
#       uwagi         text
#);

#  CRUD -- Create, Read, Update, Delete

#an_student = Student.new
#an_student.nazwisko = "Puchatek"
#an_student.imie = "Kubuś"
#an_student.email = "kpuchatek@manta.univ.gda.pl"
#an_student.data = Time.now
#an_student.save

#Student.new do |s|
#  s.nazwisko = "Puchatek2"
#  s.imie = "Kubuś2"
#  s.email = "kpuchatek2@manta.univ.gda.pl"
#  s.data = Time.now
#  s.save
#end

#Student.create(
#  :nazwisko => "Puchatek3",
#  :imie => "Kubuś3",
#  :email => "kpuchatek3@manta.univ.gda.pl",
#  'data' => Time.now # można i tak
#)

pp Student.count
pp Student.count( [ "imie = ?", 'Marcin' ] )

pp Student.count_by_sql("select count(*) from student")

#  dynamic finders

#pp Student.find_by_imie('Marcin')
pp Student.find( :first, :conditions => ["imie = ?", 'Marcin' ] )
pp Student.find_all_by_imie('Marcin')

#pp Student.find_by_email('...')
#pp Student.find_all_by_email('..')

an_student = Student.find(7)
an_student.imie = "XXXXXXXX"
an_student.save

an_student = Student.find(8)
an_student.update_attributes( :nazwisko => 'ZZZZZZZZ', :email => 'z@ab.com' )

Student.update(3, :nazwisko => 'Ooooooooo!' )

Student.update_all( "nazwisko = '--------'", "imie like '%ar%'" )


an_student = Student.find(1)
an_student.imie = "XXXXXXXX"

begin
  an_student.save!
rescue
  # validation failed
end

# deletion

#Student.delete(4)
#Student.delete([3,5])

Student.delete_all( "imie like '%ar%'" )
