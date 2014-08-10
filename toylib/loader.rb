
if $Toypath
	puts $Toypath
else
	$Toypath="./toylib/?.rb"
end

class Skynet

	def initialize
	end

	def load(file)
		if 
