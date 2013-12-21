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

// It also supports numbers, if you really need to compute on a single integer/float!
console.log(crc32c.compute(3.141592654);
```

### For batch computing

*With >100 iterations I get a 3x to 5x performance improvements. It really shows up at more than 10K iterations though.*

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

### Want more examples?

**SOON** See the example sections!

##License

The plugin is under MIT license, please see the LICENSE file provided with the module.


## Benchmarks

Run the script by doing `node benchmarks/benchmarks.js`!

*I think that pure times are not representative of reality, since every setup will get different results. This is why I've put the times in ratio using AF_ALG batch as the base (1).*

- **AF_ALG batch**: This test has used this library in single socket (batch) mode.
- **AF_ALG std**: This test has used this library in multi socket (standard) mode.
- **SSE4.2**: Using the SSE4.2 Implementation by Voxer, which is using x86 asm implementation.
- **Pure JS (table)**: This is using the pure JS CRC32 implementation, using a pre-baked table.
- **Pure JS (direct)**: This is using the pure JS CRC32 implementation, without using a pre-calculated table.

*For the original times see benchmarks/results.txt*

| Test | AF_ALG batch | AF_ALG std | SSE4.2 | Pure JS (table) | Pure JS (direct) |
| ---- |:------------:|:----------:|:------:|:---------------:|:----------------:|
| TEST_STRING_1024 | 1 | 4.4 | 0.3 | 60.4 | 97.4 |
| TEST_STRING_2048 | 1 | 4.6 | 0.4 | 119.8 | 186.9 |
| TEST_BUFFER_1024 | 1 | 5.7 | 0.4 | 8.9 | 45.5 |
| TEST_BUFFER_2048 | 1 | 5.2 | 0.5 | 95.0 | 86.5 |
| TEST_STRING_OBJECT_1024 | 1 | 3.5 | *N/A* | 50.6 | 115.8 |
| TEST_STRING_OBJECT_2048 | 1 | 3.3 | *N/A* | 103.9 | 208.6 |

*N/A* means that it is not available because not supported.

### Interesting things

- The library closely always takes the same times to execute even though the data is bigger. The main bottleneck is the data unboxing.
- The single-socket can improve the performance by a lot when needing to do a lot of calculations
- Yes the assembly implementation is faster, and that is not really surprising. Why taking crc32c? Because it's a cross platform implementation, that uses a core linux library (so very robust implementation). Also, this library support string objects.
- The pure JS library is waaaaaaaaaay slower with 1024 bytes strings and gets slower and slower when the string is bigger. The C implementation is pretty stable, and the only thing slowing it in the unboxing from JavaScript to pure C.
