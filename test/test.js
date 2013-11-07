var crc32c = require('../bin/crc32c');

console.log(crc32c.compute('hello'));

console.log(crc32c.compute('{"jsonString":"property1","jsonArray":["arr1","arr2","arr3"]}'));
