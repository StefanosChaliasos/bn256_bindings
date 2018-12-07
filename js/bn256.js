export function keygen() {
    let keypair = new Module.Vector();
    keypair = Module.keygen();
    let secret = keypair.get(0);
    let pub = [keypair.get(1), keypair.get(2), keypair.get(3), keypair.get(4)];
    return [pub, secret];
}

export function encrypt(pk, message) {
    let mes = new Module.Vector();
    mes = Module.int_to_element(message);
    let pub = new Module.Vector();
    for (let i in pk) {
        pub.push_back(pk[i]);
    }
    let encrypted = new Module.Vector();
    encrypted = Module.encrypt(pub, mes);
    let alpha = [encrypted.get(0), encrypted.get(1),
                 encrypted.get(2), encrypted.get(3)];
    let beta = [encrypted.get(4), encrypted.get(5),
                 encrypted.get(6), encrypted.get(7)];
    let secret = encrypted.get(8);
    let ciphertext = [alpha, beta];
    return [ciphertext, secret];
}

