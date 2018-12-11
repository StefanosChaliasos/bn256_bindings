function fill_vector(vector, array) {
    for (let i in array) {
        vector.push_back(array[i]);
    }
    return vector;
}

export class BN256 {
    constructor(module) {
        this.wasm = module;
    }

    keygen() {
        let keypair = new this.wasm.Vector();
        keypair = this.wasm.keygen();
        let secret = keypair.get(0);
        let pub = [keypair.get(1), keypair.get(2), keypair.get(3), keypair.get(4)];
        return [pub, secret];
    }

    encrypt(pk, message) {
        let mes = new this.wasm.Vector();
        mes = this.wasm.int_to_element(message);
        let pub = new this.wasm.Vector();
        pub = fill_vector(pub, pk);
        let encrypted = new this.wasm.Vector();
        encrypted = this.wasm.encrypt(pub, mes);
        let alpha = [encrypted.get(0), encrypted.get(1),
                     encrypted.get(2), encrypted.get(3)];
        let beta = [encrypted.get(4), encrypted.get(5),
                     encrypted.get(6), encrypted.get(7)];
        let secret = encrypted.get(8);
        let ciphertext = [alpha, beta];
        return [ciphertext, secret];
    }

    prove_encryption(ciphertext, secret) {
        let alpha = ciphertext[0];
        let beta = ciphertext[1];
        let a = new this.wasm.Vector();
        a = fill_vector(a, alpha);
        let b = new this.wasm.Vector();
        b = fill_vector(b, beta);
        let proofs = new this.wasm.Vector();
        proofs = this.wasm.prove_encryption(a, b, secret);
        let commitment = [proofs.get(0), proofs.get(1),
                         proofs.get(2), proofs.get(3)];
        let challenge = proofs.get(4);
        let response = proofs.get(5);
        return [commitment, challenge, response];
    }

    compute_decryption_factor(ciphertext, secret) {
        let alpha = ciphertext[0];
        let a = new this.wasm.Vector();
        a = fill_vector(a, alpha);
        let factor = new this.wasm.Vector();
        factor = this.wasm.compute_decryption_factor(a, secret);
        let data = [factor.get(0), factor.get(1),
                    factor.get(2), factor.get(3)];
        let base_commitment = [factor.get(4), factor.get(5),
                    factor.get(6), factor.get(7)];
        let message_commitment = [factor.get(8), factor.get(9),
                    factor.get(10), factor.get(11)];
        let challege = factor.get(12);
        let response = factor.get(13);
        return [data, [base_commitment, message_commitment, challege, response]];
    }

    compute_decryption_factors(ciphertexts, secret) {
        let factors = [];
        for (let i in ciphertexts) {
            factors.push(this.compute_decryption_factor(ciphertexts[i], secret));
        }
        return factors;
    }
}
// module.exports.BN256 = BN256;
