#!/usr/bin/ruby

require 'example'

# wywołaj funkcję `add' z example.c

puts "Example.add(7, 6) = #{Example.add(7, 6)}"

# wywołaj funkcję `getwinsize' z example.c

wd, ht = Example.getwinsize(69)
puts "Example.getwinsize(69) => (#{wd}, #{ht})"

a = 6.9;
b = Example.negate(a);
puts "a = 6.9; b = Example.negate(a) => a = #{a}, b = #{b}"
