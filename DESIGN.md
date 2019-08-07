# Logic


### Random salt generation 
Use openssl 
```C
#include <openssl/rand.h>
int RAND_bytes(unsigned char *buf, int num);
```

### Generate a key from the stored app hash 
```C
 #include <openssl/evp.h>

 int PKCS5_PBKDF2_HMAC(const char *pass, int passlen,
                       const unsigned char *salt, int saltlen, int iter,
                       const EVP_MD *digest,
                       int keylen, unsigned char *out);
 const EVP_MD *EVP_sha512(void);

```
