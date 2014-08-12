
class Skynet

	@@PROTO_TYPE = [
	   	:PTYPE_TEXT => 0,
		:PTYPE_RESPONSE => 1,
		:PTYPE_MULTICAST => 2,
		:PTYPE_CLIENT => 3,
		:PTYPE_SYSTEM => 4,
		:PTYPE_HARBOR => 5,
		:PTYPE_SOCKET => 6,
		:PTYPE_ERROR => 7,
		:PTYPE_QUEUE => 8,
		:PTYPE_DEBUG => 9,
		:PTYPE_LUA => 10, 
		:PTYPE_SNAX => 11]

	attr_reader :proto
	attr_accessor :sid_to_fiber,:fiber_to_sid

	def self.now
		self.command("NOW").to_i
	end

	def self.starttime
		self.command("STARTTIME").to_i
	end

	def self.time
		self.now() / 100.0 + self.starttime()
	end

	def start(&start_func)
		self.callback(self.method(:dispatch_msg))
		self.timeout(0) do
		   	init_service(start_func)
	   	end
	end

	def dispatch_msg(prototype,msg,sz,session,source,*rest)
		if prototype == PROTO_TYPE[:PTYPE_RESPONSE]
			puts "type response"
		else
			puts "other type"
		end
	end

end

