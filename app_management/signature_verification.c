#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <crypto/hash.h>

#define SIG_MAXLEN 256

static int verify_signature(const char *data, size_t datalen, const char *sig, size_t siglen) {
    struct crypto_shash *tfm;
    struct shash_desc *desc;
    char hash[SIG_MAXLEN];
    int ret;
    tfm = crypto_alloc_shash("sha256", 0, 0);
    if (IS_ERR(tfm))
        return PTR_ERR(tfm);
    desc = kmalloc(sizeof(*desc) + crypto_shash_descsize(tfm), GFP_KERNEL);
    if (!desc) {
        crypto_free_shash(tfm);
        return -ENOMEM;
    }
    desc->tfm = tfm;
    desc->flags = 0;
    ret = crypto_shash_digest(desc, data, datalen, hash);
    if (ret == 0 && memcmp(hash, sig, siglen) == 0)
        ret = 1;
    else
        ret = 0;
    kfree(desc);
    crypto_free_shash(tfm);
    return ret;
}

static int __init signature_verification_init(void) {
    return 0;
}

static void __exit signature_verification_exit(void) {}

module_init(signature_verification_init);
module_exit(signature_verification_exit);
MODULE_LICENSE("GPL"); 