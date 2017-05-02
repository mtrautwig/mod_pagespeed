/*
 * Copyright 2011 Google Inc.
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

// Author: marcus@trautwig.de (Marcus Trautwig)

#include <cstdio>

#include "pagespeed/kernel/base/basictypes.h"
#include "pagespeed/kernel/base/stdio_file_system.h"
#include "pagespeed/kernel/base/mock_message_handler.h"
#include "pagespeed/kernel/base/null_mutex.h"
#include "pagespeed/kernel/base/string.h"
#include "pagespeed/kernel/base/string_util.h"
#include "pagespeed/kernel/base/string_writer.h"
#include "pagespeed/kernel/image/image_optimizer.h"
#include "pagespeed/kernel/image/image_util.h"

namespace net_instaweb {

    class MessageHandler;

}  // namespace net_instaweb

using net_instaweb::MessageHandler;
using net_instaweb::GoogleMessageHandler;
using net_instaweb::StrCat;
using pagespeed::image_compression::ImageOptimizer;
using pagespeed::image_compression::ImageOptions;
using pagespeed::image_compression::ImageFormat;

bool ReadStdin(GoogleString* content,
               MessageHandler* message_handler) {
  content->clear();
  net_instaweb::StdioFileSystem file_system;
  net_instaweb::StringWriter writer(content);
  return(file_system.ReadFile(file_system.Stdin(), &writer, message_handler));
}

bool ReadFile(const GoogleString& file_name,
              GoogleString* content,
              MessageHandler* message_handler) {
  content->clear();
  net_instaweb::StdioFileSystem file_system;
  net_instaweb::StringWriter writer(content);
  return(file_system.ReadFile(file_name.c_str(), &writer, message_handler));
}

bool WriteStdout(const GoogleString& content,
                 MessageHandler* message_handler) {
  net_instaweb::StdioFileSystem file_system;
  return file_system.Stdout()->Write(content, message_handler);
}

int help(char** argv) {
  fprintf(stderr, "Usage: %s < input_file > output_file\n", argv[0]);
  return 2;
}

int main(int argc, char** argv) {
  if (argc != 1) {
    return help(argv);
  }
    
  GoogleMessageHandler message_handler;

  GoogleString original_image;
  if (!ReadStdin(&original_image, &message_handler)) {
    fprintf(stderr, "unable to process input file\n");
    return 1;
  }
  if (original_image.length() == 0) {
    return help(argv);
  }

  GoogleString rewritten_image;
  ImageFormat rewritten_format;
  
  ImageOptions options;
  options.set_must_reduce_bytes(false);
  options.set_allow_png(true);
  options.set_allow_jpeg(true);
  options.set_allow_webp_lossy(false);
  options.set_allow_convert_lossless_to_lossy(false);
  
  ImageOptimizer optimizer(&message_handler);
  optimizer.set_options(options);
    
  bool result = optimizer.Optimize(StringPiece(original_image), 
      &rewritten_image, &rewritten_format);
    
  if (result) {
    fprintf(stderr, "Format: %s\nSize: %ix%i\n", 
            ImageFormatToMimeTypeString(rewritten_format),
            optimizer.optimized_width(), 
            optimizer.optimized_height());
    WriteStdout(rewritten_image, &message_handler);
    return 0;
  } else {
    fprintf(stderr, "unable to optimize file\n");
    WriteStdout(original_image, &message_handler);
    return 1;
  }
}
