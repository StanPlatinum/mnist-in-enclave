/*
 * Copyright (C) 2011-2019 Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "Enclave.h"
#include "Enclave_t.h" /* print_string */
#include <stdarg.h>
#include <stdio.h> /* vsnprintf */
#include <string.h>

#include "sgx_utils.h"

extern "C" int initialize();

extern "C" int mnist_cnn();

extern "C" void destroy();


int debugprintf(const char* fmt, ...)
{
    char buf[BUFSIZ] = { '\0' };
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, BUFSIZ, fmt, ap);
    va_end(ap);
    ocall_print_string(buf);
    return (int)strnlen(buf, BUFSIZ - 1) + 1;
}
#define perf_test
void test_ecall(void)
{
//   if(create_mspace_with_base_default((void *)((uint64_t)get_heap_base()+get_heap_size()/2), get_heap_size()/4, 0) == 1) return;
   debugprintf("# Enclave test.\n");
   
   initialize();
   
   uint64_t begin, end;
   
   mnist_cnn();

   
  /* debugprintf("\n\n **************** GenerateHash finished. ***********\n\n\n ");
   
   rdtsc(&begin);
   mnist_cnn((void *)get_enclave_base());

#ifdef perf_test
   generateHash((void *)get_enclave_base());
#endif   
//   debugprintf("\n\n **************** Test 0 finished. ***********\n\n\n ");
   
   mnist_cnn((void *)get_enclave_base());
#ifdef perf_test
   check_hash_measurement((void *)get_enclave_base());
#endif   
//   debugprintf("\n\n **************** Test 1 finished. ***********\n\n\n ");
   
   mnist_cnn((void *)get_enclave_base());
#ifdef perf_test
   check_hash_measurement((void *)get_enclave_base());
#endif   
//   debugprintf("\n\n **************** Test 2 finished. ***********\n\n\n ");
   
   mnist_cnn((void *)get_enclave_base());
#ifdef perf_test
   check_hash_measurement((void *)get_enclave_base());
#endif   
//   debugprintf("\n\n **************** Test 3 finished. ***********\n\n\n ");
   
   rdtsc(&end);
   
   debugprintf("\ntime: %lld cycles\n", end-begin);*/
   destroy();  
}
