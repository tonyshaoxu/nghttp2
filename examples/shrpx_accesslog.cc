/*
 * Spdylay - SPDY Library
 *
 * Copyright (c) 2012 Tatsuhiro Tsujikawa
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include "shrpx_accesslog.h"

#include <ctime>
#include <cstdio>
#include <cstring>

namespace shrpx {

namespace {
void get_datestr(char *buf)
{
  time_t now = time(0);
  if(ctime_r(&now, buf) == 0) {
    buf[0] = '\0';
  } else {
    size_t len = strlen(buf);
    if(len == 0) {
      buf[0] = '\0';
    } else {
      buf[strlen(buf)-1] = '\0';
    }
  }
}
} // namespace

void upstream_connect(const std::string& client_ip)
{
  char datestr[64];
  get_datestr(datestr);
  fprintf(stderr, "[%s] %s\n", datestr, client_ip.c_str());
  fflush(stderr);
}

void upstream_spdy_stream(const std::string& client_ip, int32_t stream_id)
{
  char datestr[64];
  get_datestr(datestr);
  fprintf(stderr, "[%s] %s stream_id=%d\n", datestr, client_ip.c_str(),
          stream_id);
  fflush(stderr);
}

} // namespace shrpx
