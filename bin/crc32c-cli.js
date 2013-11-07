#! /usr/bin/env node
;(function () {

var fs = require('fs');
var crc32c = require('./crc32c.node');

if(process.argv.length < 3) {
    console.err('Expected an argument');
    console.log('Correct usage: crc32c <filename>');
}

// Currently only support a single file.
var filename = process.argv[2];
var result;

console.log(filename);

var s = fs.ReadStream(filename);

s.on('data', function (data) { result = crc32c.compute(data); });
s.on('end', function () { console.log(result); });
})();
