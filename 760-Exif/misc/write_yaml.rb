#! /usr/bin/ruby

require 'yaml'

test_obj = [
  { :filename => '08100015.jpg', :fnumber => 'f/4.0'},
  { :filename => '08100016.jpg', :fnumber => 'f/2.6'},
  { :filename => '08100017.jpg', :fnumber => 'f/8.0'},
]

yaml_obj = YAML::dump( test_obj )

puts yaml_obj.to_s

#ruby_obj = YAML::load( yaml_obj )
