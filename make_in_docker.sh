#!/bin/sh

docker run --rm -v $(pwd):/slcc -w /slcc slcc make
