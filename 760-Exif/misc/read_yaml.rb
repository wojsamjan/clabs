#! /usr/bin/ruby

require 'yaml'

yaml_obj = YAML.load_file( 'photos.yaml' )

puts "Class: #{yaml_obj.class}"

yaml_obj.each do |photo|
  puts "=="
  puts photo[:filename]
  puts photo[:fnumber]
  puts photo[:exposuretime]
end



