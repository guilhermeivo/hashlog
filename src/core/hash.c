#include <hashlog/core/hash.h>

/**
 * https://wiki.openssl.org/index.php/EVP_Message_Digests
 */
int create_hash(char** buffer, size_t length, unsigned char** digest, unsigned int* digest_len) {
    EVP_MD_CTX *mdctx;

	if((mdctx = EVP_MD_CTX_new()) == NULL)
		goto err;

	if(1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL))
		goto err;

	if(1 != EVP_DigestUpdate(mdctx, *buffer, length))
		goto err;

	if((*digest = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_sha256()))) == NULL) {
		perror("Execution exceeded memory limit.");
		goto err;
	}

	if(1 != EVP_DigestFinal_ex(mdctx, *digest, digest_len))
		goto err;

    EVP_MD_CTX_free(mdctx);
    return 1;

    err:
        EVP_MD_CTX_free(mdctx);
        return 0;
}