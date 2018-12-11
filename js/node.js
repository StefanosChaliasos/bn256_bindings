const Module = require('./functions_node.js');
const bn = require('./bn256_class.js');
const wasm = Module({wasmBinaryFile: 'functions_node.wasm'});
wasm.onRuntimeInitialized = function() {
    let bn256 = new bn.BN256(wasm);
    // keygen
    let keys = bn256.keygen();
    let pub = keys[0];
    let secret = keys[1];
    // encrypt
    let message1 = "10";
    let message2 = "11";
    let encrypted1 = bn256.encrypt(pub, message1);
    let encrypted2 = bn256.encrypt(pub, message2);
    let ciphertext1 = encrypted1[0];
    let secret1 = encrypted1[1];
    let ciphertext2 = encrypted2[0];
    let secret2 = encrypted2[1];
    let proofs1 = bn256.prove_encryption(ciphertext1, secret1);
    let proofs2 = bn256.prove_encryption(ciphertext2, secret2);
    // factors
    let ciphertexts = [ciphertext1, ciphertext2];
    let factors = bn256.compute_decryption_factors(ciphertexts, secret);
    console.log(factors);
};
