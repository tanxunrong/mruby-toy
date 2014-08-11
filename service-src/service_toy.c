#include "skynet.h"

#include <mruby.h>
#include <mruby/array.h>
#include <mruby/class.h>
#include <mruby/compile.h>
#include <mruby/data.h>
#include <mruby/dump.h>
#include <mruby/error.h>
#include <mruby/gc.h>
#include <mruby/hash.h>
#include <mruby/irep.h>
#include <mruby/debug.h>
#include <mruby/numeric.h>
#include <mruby/object.h>
#include <mruby/opcode.h>
#include <mruby/proc.h>
#include <mruby/range.h>
#include <mruby/re.h>
#include <mruby/string.h>
#include <mruby/value.h>
#include <mruby/variable.h>

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct toy {
    mrb_state *mrb;
	struct skynet_context * ctx;
};
/*
static int
traceback (mrb_state *mrb) {
    const char *msg = lua_tostring(L, 1);
    if (msg)
        luaL_traceback(L, L, msg, 1);
    else {
        lua_pushliteral(L, "(no error message)");
    }
    return 1;
}

static void
_report_launcher_error(struct skynet_context *ctx) {
    // sizeof "ERROR" == 5
    skynet_sendname(ctx, ".launcher", PTYPE_TEXT, 0, "ERROR", 5);
}
*/
static const char *
optstring(struct skynet_context *ctx, const char *key, const char * str) {
    const char * ret = skynet_command(ctx, "GETENV", key);
    if (ret == NULL) {
        return str;
    }
    return ret;
}

static int
_init(struct toy *mrb, struct skynet_context *ctx, const char * args, size_t sz) {
    mrb_state *M = mrb->mrb;
    mrb->ctx = ctx;

    const char *path = optstring(ctx,"toy_path","./toylib/loader.rb");
    mrb_value snctx = mrb_cptr_value(M,mrb->ctx);
    struct RClass *skynetClass = mrb_class_get(M,"Skynet");
    assert(skynetClass != NULL);
    mrb_define_const(M,skynetClass,"@@CTX",snctx);


    FILE *loadF = fopen(path,"r");
    assert(loadF != NULL);
    mrb_load_file(M,loadF);

//    mrb_print_error(M);

//    lua_gc(L, LUA_GCSTOP, 0);
//    lua_pushboolean(L, 1);  /* signal for libraries to ignore env. vars. */
//    lua_setfield(L, LUA_REGISTRYINDEX, "LUA_NOENV");
    //设置registery[_LUA_NOENV] = 1
//    luaL_openlibs(L);
//    lua_pushlightuserdata(L, ctx);
//    lua_setfield(L, LUA_REGISTRYINDEX, "skynet_context");
    //设置registery[skynet_context] = ctx
//    luaL_requiref(L, "skynet.codecache", codecache , 0);
//    lua_pop(L,1);

//    const char *path = optstring(ctx, "lua_path","./lualib/?.lua;./lualib/?/init.lua");
//    lua_pushstring(L, path);
//    lua_setglobal(L, "LUA_PATH");
//    const char *cpath = optstring(ctx, "lua_cpath","./luaclib/?.so");
//    lua_pushstring(L, cpath);
//    lua_setglobal(L, "LUA_CPATH");
//    const char *service = optstring(ctx, "luaservice", "./service/?.lua");
//    lua_pushstring(L, service);
//    lua_setglobal(L, "LUA_SERVICE");
//    const char *preload = skynet_command(ctx, "GETENV", "preload");
//    lua_pushstring(L, preload);
//    lua_setglobal(L, "LUA_PRELOAD");

//    lua_pushcfunction(L, traceback);
//    assert(lua_gettop(L) == 1);

//    const char * loader = optstring(ctx, "lualoader", "./lualib/loader.lua");

//    int r = luaL_loadfile(L,loader);
//    if (r != LUA_OK) {
//        skynet_error(ctx, "Can't load %s : %s", loader, lua_tostring(L, -1));
//        _report_launcher_error(ctx);
//        return 1;
//    }
//    lua_pushlstring(L, args, sz);
//    r = lua_pcall(L,1,0,1);
//    if (r != LUA_OK) {
//        skynet_error(ctx, "lua loader error : %s", lua_tostring(L, -1));
//        _report_launcher_error(ctx);
//        return 1;
//    }
//    lua_settop(L,0);

//    lua_gc(L, LUA_GCRESTART, 0);


    return 0;
}

static int
_launch(struct skynet_context * context, void *ud, int type, int session, uint32_t source , const void * msg, size_t sz) {
    assert(type == 0 && session == 0);
    struct toy *mrb = ud;
    skynet_callback(context, NULL, NULL);
    int err = _init(mrb, context, msg, sz);
    if (err) {
        skynet_command(context, "EXIT", NULL);
    }

    return 0;
}


//create service instance
int
toy_init(struct toy *mrb, struct skynet_context *ctx, const char * args) {
    int sz = strlen(args);
    char * tmp = skynet_malloc(sz);
    memcpy(tmp, args, sz);
    skynet_callback(ctx, mrb , _launch);
    const char * self = skynet_command(ctx, "REG", NULL);
	//handler first byte is the server id,so need to move 1 byte
    uint32_t handle_id = strtoul(self+1, NULL, 16);
    // it must be first message
	// source = 0 means local
    skynet_send(ctx, 0, handle_id, PTYPE_TAG_DONTCOPY,0, tmp, sz);
    return 0;
}

struct toy *
toy_create(void) {
    struct toy *mrb = skynet_malloc(sizeof(*mrb));
    memset(mrb,0,sizeof(*mrb));
    mrb->mrb = mrb_open();
	assert(mrb->mrb != NULL);
    return mrb;
}

void
toy_release(struct toy *mrb) {
    mrb_close(mrb->mrb);
    skynet_free(mrb);
}

/*
static int
cleardummy(mrb_state *mrb) {
  return 0;
}

static int 
codecache(mrb_state *mrb) {
	luaL_Reg l[] = {
		{ "clear", cleardummy },
		{ NULL, NULL },
	};
	luaL_newlib(L,l);
	lua_getglobal(L, "loadfile");
	lua_setfield(L, -2, "loadfile");
	return 1;
}
*/


