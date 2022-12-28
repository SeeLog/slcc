#!/bin/sh

docker run -it --rm -v $(pwd)/slcc:/slcc -w /slcc slcc
