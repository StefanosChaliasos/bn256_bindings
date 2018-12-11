// Ugly way to wait Module to load
import * as bn from './bn256_class.js'
setTimeout(function(){
    test("Keygen", function () {
        let bn256 = new bn.BN256(Module);
        let keys = bn256.keygen();
        let pub = keys[0];
        let secret = keys[1];
        ok(true);
    });
    test("Encrypt-Prove", function () {
        let bn256 = new bn.BN256(Module);
        let keys = bn256.keygen();
        let pub = keys[0];
        let message = "10";
        let result = bn256.encrypt(pub, message);
        let ciphertext = result[0];
        let secret = result[1];
        let proofs = bn256.prove_encryption(ciphertext, secret);
        ok(true);
    });
    test("Factors", function () {
        let bn256 = new bn.BN256(Module);
        let keys = bn256.keygen();
        let pub = keys[0];
        let secret = keys[1]
        let message1 = "10";
        let result1 = bn256.encrypt(pub, message1);
        let ciphertext1 = result1[0];
        let message2 = "11";
        let result2 = bn256.encrypt(pub, message2);
        let ciphertext2 = result2[0];
        let ciphertexts = [ciphertext1, ciphertext2];
        let factors = bn256.compute_decryption_factors(ciphertexts, secret);
        ok(true);
    });
}, 500);
