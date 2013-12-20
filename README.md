Node-crc32c
===========

Basic C  modules for NodeJS with crc32c (Castagnoli) implementation for Linux. The implementation uses the native Linux library "AF\_ALG".

It supports strings, string objects, buffers, numbers! Works well with mongoose. Just do a toString on the entity to hash!

This module is not meant for secure hashing but really for something like ETags or anything that is easier to compare using a hash than the full string.

##Building

    node-gyp configure build

or

    npm install crc32c

##Usage

### For small number of computation needed

You have the function `compute`, which takes only one argument, the string to hash.

From JavaScript:
```javascript
var crc32c = require('crc32c');

// Works with strings!
var toHash = "HELLOWORLD";
console.log(crc32c.compute(toHash));

// Or buffers!
console.log(crc32c.compute(new Buffer('{"jsonString":"property1","jsonArray":["arr1","arr2","arr3"]}')));

// Or String Objects!
console.log(crc32c.compute(new String('A superb string!')));
```

### For batch computing

*With >100 iterations I get a 3x perf improvements. It really shows up at more than 10K iterations though.*

You have to create an object called a Batcher. This object then has 3 methods: `openSocket`, `closeSocket`, and `compute`.

From JavaScript:
```javascript
var crc32c = require('crc32c');
var Batcher = new crc32c.Batcher(); // You can create as many as you want. Every instance will use a single socket.
var Batcher.openSocket();
console.log(Batcher.compute(new Buffer('{"jsonString":"property1","jsonArray":["arr1","arr2","arr3"]}')));
// ... Iterate on many strings/buffer/etc.
Batcher.closeSocket();
```

From cli:
```shell
crc32c <filename>
```
*It currently supports only one file at the time.*

##License

The plugin is under MIT license, please see the LICENSE file provided with the module.


## Benchmarks

Run the script `node benchmarks/benchmarks.js`!

*Soon more info.*
