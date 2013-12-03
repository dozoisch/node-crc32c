Node-crc32c
===========

Basic C  modules for NodeJS with crc32c (Castagnoli) implementation for Linux. The implementation uses the native Linux library "AF\_ALG".

This module is not meant for secure hashing but really for something like ETags or anything that is easier to compare using a hash than the full string.

##Building

    node-gyp configure build

or

    npm install crc32c

##Usage

From JavaScript:
```javascript
var crc32c = require('crc32c');

// Works with strings!
var toHash = "HELLOWORLD";
console.log(crc32c.compute(toHash));

// Or buffers!
console.log(crc32c.compute(new Buffer('{"jsonString":"property1","jsonArray":["arr1","arr2","arr3"]}')));
```

From cli:
```shell
crc32c <filename>
```
*It currently supports only one file at the time.*

##License

The plugin is under MIT license, please see the LICENSE file provided with the module.
