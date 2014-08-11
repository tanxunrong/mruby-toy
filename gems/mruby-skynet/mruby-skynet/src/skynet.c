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
	assert(ctx != NULL);
	//skynet_callback(ctx,_cb);
	return self;
}

void
mrb_mruby_skynet_gem_init(mrb_state* mrb) {
  struct RClass *skynet;
  skynet = mrb_define_class(mrb,"Skynet",mrb->object_class);
  mrb_define_class_method(mrb, skynet, "callback", mrb_skynet_callback, MRB_ARGS_NONE());
}

void
mrb_mruby_skynet_gem_final(mrb_state* mrb) {
  /* finalizer */
}
