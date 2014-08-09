

SKYNET_ENV = { 
"root"=>"./",
"thread"=> 8,
"logger"=> nil,
"harbor"=> 1,
"address"=>"127.0.0.1:2526",
"master"=>"127.0.0.1:2013",
"start"=>"main",
"bootstrap"=>"snlua bootstrap",	## The service for bootstrap,
"standalone"=>"0.0.0.0:2013",
"luaservice"=>"./" +"service/?.lua;" +"./" +"test/?.lua;" +"./" +"examples/?.lua",
"lualoader"=>"lualib/loader.lua",
"snax"=>"./" +"examples/?.lua;" +"./" +"test/?.lua",
"cpath"=>"./" +"cservice/?.so"
}
## preload"=>"./examples/preload.lua"	
## run preload.lua before every lua service run,
## daemon => "./skynet.pid",
