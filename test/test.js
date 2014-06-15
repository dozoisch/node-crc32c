'use strict';
var crc32c = require('../bin/crc32c');

// 1024b ytes
var String1024 = 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Morbi mollis cursus metus vel tristique. Proin congue massa massa, a malesuada dolor ullamcorper a. Nulla eget leo vel orci venenatis placerat. Donec semper condimentum justo, vel sollicitudin dolor consequat id. Nunc sed aliquet felis, eget congue nisi. Mauris eu justo suscipit, elementum turpis ut, molestie tellus. Mauris ornare rutrum fringilla. Nulla dignissim luctus pretium. Nullam nec eros hendrerit sapien pellentesque sollicitudin. Integer eget ligula dui. Mauris nec cursus nibh. Nunc interdum elementum leo, eu sagittis eros sodales nec. Duis dictum nulla sed tincidunt malesuada. Quisque in vulputate sapien. Sed sit amet tellus a est porta rhoncus sed eu metus. Mauris non pulvinar nisl, volutpat luctus enim. Suspendisse est nisi, sagittis at risus quis, ultricies rhoncus sem. Donec ullamcorper purus eget sapien facilisis, eu eleifend felis viverra. Suspendisse elit neque, semper aliquet neque sed, egestas tempus leo. Duis condimentum turpis duis.';
// 2048 bytes
var String2048 = 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas auctor hendrerit orci, eget accumsan erat tristique id. Nullam dignissim erat eget erat viverra, et vehicula leo pulvinar. Nulla viverra lacinia ullamcorper. Nullam condimentum, nibh sed blandit mattis, purus odio commodo quam, sit amet sollicitudin arcu justo condimentum quam. Nullam eu neque nibh. Mauris et placerat lacus, sed varius nisl. Quisque viverra ante augue, et aliquam nisl imperdiet in. Donec ac sapien quam. Phasellus imperdiet, felis non tincidunt pretium, velit odio suscipit diam, eu cursus lorem mauris vitae magna. Ut consectetur a dui dapibus consequat. Pellentesque volutpat non orci ac suscipit. Sed elit dui, blandit quis eleifend a, pretium vitae eros. Nunc dapibus, purus nec fringilla ullamcorper, nunc quam viverra urna, id scelerisque ligula quam nec magna.Quisque sit amet posuere sapien. Nunc viverra convallis ipsum sit amet pellentesque. Vestibulum molestie iaculis ultrices. Nulla id lacus pretium, varius nunc et, vestibulum mauris. Quisque convallis, erat eu tempus pretium, leo odio varius tellus, quis ultrices arcu eros eget leo. Integer porttitor pharetra adipiscing. In eu mauris eu diam fringilla pharetra tempor eget velit. Etiam viverra commodo mauris nec dignissim. Nulla imperdiet mauris dui. Donec laoreet porttitor elit, ac lobortis quam aliquam in. Donec auctor eros eget turpis hendrerit fermentum sit amet nec dolor. Praesent ullamcorper, eros ac feugiat mollis, quam metus tristique quam, vel varius ante sem at ante. Fusce id dignissim metus, et molestie sem. Phasellus fermentum tincidunt est, quis blandit nisl imperdiet dignissim. Sed rhoncus elementum orci, sit amet vestibulum mi rutrum et.Pellentesque eget metus diam. Phasellus id turpis porttitor ipsum congue lobortis ut interdum est. Curabitur viverra consequat sem, at accumsan risus rutrum eu. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Etiam convallis odio dui, eleifend aliquet tortor malesuada at. Nullam ac metus.';
// numbers
var n_int_1 = 91238120;
var n_int_2 = 2321;
var n_float_1 = 9.9123810293123;
var n_float_2 = 3.141592654;

// different test cases
var tests = {
    TEST_STRING_1024 : String1024,
    TEST_STRING_2048 : String2048,
    TEST_BUFFER_1024 : new Buffer( String1024 ),
    TEST_BUFFER_2048 : new Buffer( String2048 ),
    TEST_STRING_OBJECT_1024 : new String( String1024 ),
    TEST_STRING_OBJECT_2048 : new String( String2048 ),
    TEST_INTEGER_1: n_int_1,
    TEST_INTEGER_2: n_int_2,
    TEST_FLOAT_1: n_float_1,
    TEST_FLOAT_2: n_float_2
};


//*** Standard way
console.log("Calls to calculate CRC with CRC32C AF_ALG, multi sockets...");
Object.keys(tests).forEach(function (key) {
    console.log("\t" + key + ": " + crc32c.compute(tests[key]));
});


//*** Batcher
var batcher = new crc32c.Batcher();

console.log("\nCalls to calculate CRC with CRC32C AF_ALG, single socket...");
batcher.openSocket();
Object.keys(tests).forEach(function (key) {
    console.log("\t" + key + ": " + batcher.compute(tests[key]));
});
batcher.closeSocket();


