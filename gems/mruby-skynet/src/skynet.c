#include <mruby.h>
#include <mruby/variable.h>
#include <stdio.h>
#include "skynet.h"
/*
static int
_cb(struct skynet_context * context, void * ud, int type, int session, uint32_t source, const void * msg, size_t sz) {

	return 0;
}
*/

static mrb_value
mrb_skynet_callback(mrb_state *mrb, mrb_value self)
{
	mrb_sym ctxSym = mrb_intern_cstr(mrb,"@@CTX");
	mrb_value ctxV = mrb_const_get(mrb,self,ctxSym);
	struct skynet_context *ctx = mrb_cptr(ctxV);
	if (ctx == NULL)
	{
		puts("fail to get ctx");
	}
	//skynet_callback(ctx,_cb);
	return self;
}

static mrb_value
mrb_skynet_command(mrb_state *mrb,mrb_value self)
{
	mrb_sym ctxSym = mrb_intern_cstr(mrb,"@@CTX");
	mrb_value ctxV = mrb_const_get(mrb,self,ctxSym);
	struct skynet_context *ctx = mrb_cptr(ctxV);
	if (ctx == NULL)
	{
		puts("fail to get ctx");
	}

	const char *ret = NULL;
	const char *cmd = NULL,*param = NULL;
	mrb_get_args(mrb,"z|z",&cmd,&param);
	ret = skynet_command(ctx,cmd,param);
	if (ret)
	{
		return mrb_str_new_cstr(mrb,ret);
	}
	return mrb_nil_value();
}


void
mrb_mruby_skynet_gem_init(mrb_state* mrb) {
  struct RClass *skynet;
  skynet = mrb_define_class(mrb,"Skynet",mrb->object_class);
  mrb_define_class_method(mrb, skynet, "callback", mrb_skynet_callback, MRB_ARGS_NONE());
  mrb_define_class_method(mrb, skynet, "command", mrb_skynet_command, MRB_ARGS_ARG(1,1));
}

void
mrb_mruby_skynet_gem_final(mrb_state* mrb) {
  /* finalizer */
}
