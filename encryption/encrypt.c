#include<openssl/evp.h>
#include<string.h>
#include <openssl/core_names.h>

int main(){

	unsigned char msg[50];// = "Hello world";

	//char buffer[30];
	printf("Enter data to encrypt\n");
	scanf("%s",&msg);
	
	
	EVP_MD *md = EVP_MD_fetch(NULL,"SHA256",NULL);

	size_t digest_size = EVP_MD_size(md);
	
	unsigned char digest[digest_size];


	EVP_MD_CTX *md_ctx = EVP_MD_CTX_new();
	
	EVP_DigestInit_ex2(md_ctx,md,NULL);

	EVP_DigestUpdate(md_ctx,msg,strlen((char *)msg));

	EVP_DigestFinal_ex(md_ctx,digest,(unsigned int *)&digest_size);

	printf("SHA2-256 output of data entered:\n ");
		for(size_t i ; i < digest_size; i++)
			printf("%02x",digest[i]);
		printf("\n");

	printf("\nLet's Encrypt\n\n");


	//Create a digest of the text hello world, should be SHA-2-256
	//
	//hajime
	


	EVP_MD_free(md);
	EVP_MD_CTX_free(md_ctx);
	return 0;
}
