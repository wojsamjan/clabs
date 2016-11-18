#!/usr/bin/ruby

require 'foo'

puts "Foo.bar = #{Foo.bar}"
puts "Foo.sin(3.1416) = #{Foo.sin(3.1416)}"
puts "Foo.strcmp('ala', 'ola') = #{Foo.strcmp('ala', 'ola')}"
puts "  stałe:"
puts "Foo::STATUS = #{Foo::STATUS}"
puts "Foo::VERSION = #{Foo::VERSION}"
puts "Foo::Bar = #{Foo::Bar}"
