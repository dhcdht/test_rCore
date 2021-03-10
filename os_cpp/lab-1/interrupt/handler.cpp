//
// Created by 董宏昌 on 2021/3/9.
//

#include "handler.h"
#include "context.h"
#include "../console.h"


namespace interrupt {

extern "C" {

void handle_interrupt(const Context context) {
    console::puts("handle_interrupt");
}

}

}

