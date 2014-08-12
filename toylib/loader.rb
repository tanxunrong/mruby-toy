
begin

	Skynet.callback()

	class Skynet
		attr_reader :CTX
		def self.putCtx
			puts @@CTX
		end
	end

	Skynet.putCtx()

	puts Skynet.now()
	puts Skynet.time()
rescue Exception => detail
	puts detail
end
