/* 
 *
 * Shove data into dev-random, and bump entropy-avail
 *
 * Copyright (c) 2008 Janne Johansson, Stockholms Universitet
 * (Stockholm University, Stockholm, Sweden).
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "add-entropy.h"

int main()
{

  size_t size=0;

  char hex[512];

  size=fread(hex, 1, sizeof(hex), stdin);
  if (-1 == size || size == 0)
    errx(1,"failed to read anything from stdin");
  if (size < sizeof(hex) )
    warn("Only got a little data (%d bytes), running with what we got",
	 size);

  if (add_entropy(hex, size))
  {
      return 1;
  }

  return 0;
}

int
add_entropy(char *data, int count) {

  struct apool mypool;

  int randfd=0;
  int returncode=0;

  if (count > sizeof(mypool.buf)) {
    warn("Too large buffer, limiting to %d bytes", sizeof(mypool.buf));
  }

  mypool.entropy_count=count*8;
  mypool.buf_size=count;
  memcpy(mypool.buf,data,count);

  // printf("Starting\n");

  randfd = open("/dev/random", O_WRONLY);
  if (0 == randfd) errx(1, "could not open random device file");

  //  printf("test: %d < sizeof mypool\n", sizeof(apool));

  returncode = ioctl(randfd, RNDADDENTROPY, &mypool);
  if (returncode)
  {
    err(2, "Could not make ioctl, error %d", errno);
  }  

  return returncode;
}

