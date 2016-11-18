#!/usr/bin/ruby

require 'example'

# sprawdź wartość zmiennej globalnej `foo' zdefiniowanej w C

puts "Example.foo = #{Example.foo} (" + Example.foo.class.to_s + ")"

# wywołaj funkcje `silnia' oraz `suma' napisane w C

puts "Example.silnia(10) = #{Example.silnia(10)}"

puts "Example.suma(13, 7) = #{Example.suma(13, 7)}"
