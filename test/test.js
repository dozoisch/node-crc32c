var crc32c = require('../bin/crc32c');

console.log(crc32c.compute(new Buffer('hello\n')));

console.log(crc32c.compute(new Buffer('{"jsonString":"property1","jsonArray":["arr1","arr2","arr3"]}')));

console.log(crc32c.compute('{"jsonString":"property1","jsonArray":["arr1","arr2","arr3"]}'));

var fails = 0;
var error;
var N = 100000
var label = 'batch ' + N;
console.time(label);
for( var i = 0; i < N; ++i) {
    try {
        crc32c.compute('{"jsonString":"property1","jsonArray":["arr1","arr2","arr3"]}');

    } catch (err) {
        error = err;
        ++fails;
    }
}
console.timeEnd(label);

if (fails) {
    console.log(fails);
    console.log(error);
}