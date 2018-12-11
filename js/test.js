// Ugly way to wait Module to load
import * as bn from './bn256_class.js'
setTimeout(function(){
    test("Keygen", function () {
        let bn256 = new bn.BN256(Module);
        let keys = bn256.keygen();
        let pub = keys["public"]["data"];
        let secret = keys["secret"];
        ok(true);
    });
    test("Encrypt-Prove", function () {
        let bn256 = new bn.BN256(Module);
        let keys = bn256.keygen();
        let pub = keys["public"]["data"];
        let message = "10";
        let result = bn256.encrypt(pub, message);
        ok(true);
    });
    test("Factors", function () {
        let bn256 = new bn.BN256(Module);
        let keys = bn256.keygen();
        let pub = keys["public"]["data"];
        let secret = keys["secret"];
        let message1 = "10";
        let result1 = bn256.encrypt(pub, message1);
        let ciphertext1 = result1["ciphertext"];
        let message2 = "11";
        let result2 = bn256.encrypt(pub, message2);
        let ciphertext2 = result2["ciphertext"];
        let ciphertexts = [ciphertext1, ciphertext2];
        let factors = bn256.compute_decryption_factors(ciphertexts, secret);
        console.log(factors);
        ok(true);
    });
}, 500);
