// Ugly way to wait Module to load
setTimeout(function(){
    test("Keygen", function () {
        let keypair = new Module.Keypair();
        keypair = Module.keygen();
        secret = keypair.get(0);
        public = [keypair.get(1), keypair.get(2),
                  keypair.get(3), keypair.get(4)];
        console.log(public);
        ok(true);
    });
}, 500);
