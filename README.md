Node-crc32c
===========

Basic c modules for NodeJS with crc32c (castagnoli) implementation for Linux.

This module is not meant for secure hashing but really for something like ETags or anything that is easier to compare using a hash than the full string.

##Building

    node-gyp configure build

or 

    npm install crc32c

##Usage

```javascript
var crc32c = require('crc32c');

var toHash = "HELLOWORLD";

console.log(crc32c.compute(toHash));
```


##License

The plugin is under MIT license, please see the LICENSE file provided with the module.
