// Ugly way to wait Module to load
import * as bn256 from './bn256.js'
setTimeout(function(){
    test("Keygen", function () {
        let keys = bn256.keygen();
        let pub = keys[0];
        let secret = keys[1]
        console.log(pub);
        console.log(secret);
        ok(true);
    });
    test("Encrypt", function () {
        let keys = bn256.keygen();
        let pub = keys[0];
        let message = "10";
        let result = bn256.encrypt(pub, message);
        let ciphertexts = result[0];
        let secret = result[1];
        console.log(ciphertexts);
        console.log(secret);
        ok(true);
    });
}, 500);
