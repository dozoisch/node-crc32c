var crc32c = require('../bin/crc32c');

// Normal usage
console.log(crc32c.compute(new Buffer('hello\n')));
console.log(crc32c.compute(new Buffer('{"jsonString":"property1","jsonArray":["arr1","arr2","arr3"]}')));
console.log(crc32c.compute('{"jsonString":"property1","jsonArray":["arr1","arr2","arr3"]}'));
console.log(crc32c.compute(new String('Lorem ipsum dolor sit amet, consectetur adipiscing elit. Praesent quis ipsum odio. Phasellus gravida mattis sem, at tempus lorem. Etiam hendrerit accumsan pretium. Suspendisse malesuada nisl urna, sed porta eros scelerisque sit amet. Nullam pulvinar metus.')));

// Using the batcher
var Batcher = new crc32c.Batcher();
Batcher.openSocket();
console.log(Batcher.compute(new Buffer('hello\n')));
console.log(Batcher.compute(new Buffer('{"jsonString":"property1","jsonArray":["arr1","arr2","arr3"]}')));
console.log(Batcher.compute('{"jsonString":"property1","jsonArray":["arr1","arr2","arr3"]}'));
console.log(Batcher.compute(new String('Lorem ipsum dolor sit amet, consectetur adipiscing elit. Praesent quis ipsum odio. Phasellus gravida mattis sem, at tempus lorem. Etiam hendrerit accumsan pretium. Suspendisse malesuada nisl urna, sed porta eros scelerisque sit amet. Nullam pulvinar metus.')));
Batcher.closeSocket();
