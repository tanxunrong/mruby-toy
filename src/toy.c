#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>

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


int main(void)
{
    printf("Hello World!\n");
    mrb_state * mrb = mrb_open();

    mrb_close(mrb);
    return 0;
}

