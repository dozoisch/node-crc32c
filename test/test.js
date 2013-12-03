var crc32c = require('../bin/crc32c');

console.log(crc32c.compute(new Buffer('hello\n')));

console.log(crc32c.compute(new Buffer('{"jsonString":"property1","jsonArray":["arr1","arr2","arr3"]}')));

console.log(crc32c.compute('{"jsonString":"property1","jsonArray":["arr1","arr2","arr3"]}'));