import main from './main.js';

console.log("javascript", "_foo");
main._foo(2);

console.log("javascript", "non_c_function_object");
console.log(main.non_c_function_object());
console.log("javascript", "non_c_function_array");
console.log(main.non_c_function_array());

console.log("javascript", "Freyr");
const freyr = new main.Freyr();
console.log("javascript", "Freyr.foo");
freyr.foo(3);

console.log("javascript", "Freki");
const freki = new main.Freki();
console.log("javascript", "Freki.foo");
freki.foo(freyr);

console.log("javascript", "Freki.fizz");
freki.fizz({ x: 300 });

console.log("javascript", "Freki.fuzz");
freki.fuzz([ 400 ]);

freyr.delete();
freki.delete();
