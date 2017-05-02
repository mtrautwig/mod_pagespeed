# Image optimization command-Line tool

This is a wrapper around `ImageOptimizer` to call the image optimization built-into mod_pagespeed via the command line. 

## Execution

```
$ imgopt < input-file.img > output-file.img
```

The input image file is provided on STDIN. The compressed output image is written to STDOUT. The status of the compression is returned via exit code,further status messages may be written to STDERR:

Code | Description
-----|------------
0    | no error
1    | error reading the image or producing the output
2    | invocation error, see help message

## Build

In order to build the `imgopt` tool, you must first build the Page Speed Optimization Library (PSOL). It is recommended to build in a Docker image as follows.

```
$ git clone YOUR_PAGESPEED_FORK
$ cd pagespeed
$ git submodule update --init --recursive
$ docker run -it --name pagespeed -v .:/pagespeed ubuntu:16.04
container$ cd /pagespeed
container$ apt update
container$ apt install lsb-release sudo
container$ install/build_psol.sh
```

After that, the `imgopt` binary can be built:
```
container$ cd /pagespeed/imgopt
container$ make
```
