
if $Toypath
	puts $Toypath
else
	$Toypath="./toylib/?.rb"
end

Skynet.callback()

class Skynet
	attr_reader :CTX
	def self.putCtx
		puts @@CTX
		puts "shit"
	end
end

Skynet.putCtx()
puts "shit"
