var crc32c = require('./build/Release/crc32c');

console.log(crc32c.compute('hello').toString(16));

console.log(crc32c.compute('{"jsonString":"property1","jsonArray":["arr1","arr2","arr3"]}').toString(16));
