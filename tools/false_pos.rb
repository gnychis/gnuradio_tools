#!/usr/bin/ruby

gtruth = Hash.new
comp = Hash.new
count=0
total=0

if(ARGV.size != 4)
  printf("Usage: ./prog <ground_truth> <comparisson> <truth_thresh> <comp_thresh>\n")
  exit
end

gtfname = ARGV[0]
cfname = ARGV[1]
tthresh = ARGV[2].to_i
mthresh = ARGV[3].to_i

# Create a hash key for every true location
gtfile = File.open(gtfname, "r")
gtfile.each_line do |line|
  (location, amplitude) = line.split.map {|i| i.to_i}
  if(amplitude>=tthresh)
    gtruth[location]=amplitude
  elsif
    total+=1
  end
end

cffile = File.open(cfname, "r")
cffile.each_line do |line|
  (location, amplitude) = line.split.map {|i| i.to_i}
  if(amplitude>=mthresh)
    count+=1 if(!gtruth.has_key?(location))
  end
end

puts count.to_f/total.to_f
