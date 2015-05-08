all: install test

install:
	npm install -g node-gyp
	npm install .

build: clean configure compile

configure:
	node-gyp configure

compile: configure
	node-gyp build

test: build
	npm test

benchmarks: build
	node ./benchmarks/benchmarks.js

clean:
	node-gyp clean


.PHONY: clean test build benchmarks install
