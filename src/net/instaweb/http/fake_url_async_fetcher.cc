/*
 * Copyright 2010 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Author: jmarantz@google.com (Joshua Marantz)

#include "net/instaweb/http/public/fake_url_async_fetcher.h"

#include "net/instaweb/http/public/async_fetch.h"
#include "net/instaweb/http/public/url_fetcher.h"

namespace net_instaweb {

FakeUrlAsyncFetcher::~FakeUrlAsyncFetcher() {
}

void FakeUrlAsyncFetcher::Fetch(const GoogleString& url,
                                MessageHandler* message_handler,
                                AsyncFetch* fetch) {
  bool ret = url_fetcher_->StreamingFetchUrl(
      url, *fetch->request_headers(), fetch->response_headers(), fetch,
      message_handler, fetch->request_context());
  fetch->Done(ret);
}

}  // namespace instaweb
