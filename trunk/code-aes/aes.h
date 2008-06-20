/*
  Title: WSN - Secure comunications with AES algoritms
  Company: University of Trento - Faculty of Computer Science
  @author Nicola Manica (128851 - nicola.manica@gmail.com), 
          Matteo Saloni (130196 - matteo.saloni@gmail.com), 
          Toldo Paolo (128723 - paolo.toldo@gmail.com - www.paolotoldo.it)
*/

#ifndef _AES_H
#define _AES_H

#define AES_ENCRYPT     1
#define AES_DECRYPT     0

/**
 * \brief          AES context structure
 */
typedef struct aes_context
{
    int nr;                     /*!<  number of rounds  */
    uint32_t *rk;          /*!<  AES round keys    */
    uint32_t buf[68];      /*!<  unaligned data    */
}
aes_context;

/**
 * \brief          AES key schedule (encryption)
 *
 * \param ctx      AES context to be initialized
 * \param key      encryption key
 * \param keysize  must be 128, 192 or 256
 */
void aes_setkey_enc( aes_context *ctx, unsigned char *key, int keysize );

/**
 * \brief          AES key schedule (decryption)
 *
 * \param ctx      AES context to be initialized
 * \param key      decryption key
 * \param keysize  must be 128, 192 or 256
 */
void aes_setkey_dec( aes_context *ctx, unsigned char *key, int keysize );

/**
 * \brief          AES-ECB block encryption/decryption
 *
 * \param ctx      AES context
 * \param mode     AES_ENCRYPT or AES_DECRYPT
 * \param input    16-byte input block
 * \param output   16-byte output block
 */
void aes_crypt_ecb( aes_context *ctx,
                    int mode,
                    unsigned char input[16],
                    unsigned char output[16] );

/**
 * \brief          AES-CBC buffer encryption/decryption
 *
 * \param ctx      AES context
 * \param mode     AES_ENCRYPT or AES_DECRYPT
 * \param length   length of the input data
 * \param iv       initialization vector (updated after use)
 * \param input    buffer holding the input data
 * \param output   buffer holding the output data
 */
void aes_crypt_cbc( aes_context *ctx,
                    int mode,
                    int length,
                    unsigned char iv[16],
                    unsigned char *input,
                    unsigned char *output );

/**
 * \brief          AES-CFB buffer encryption/decryption
 *
 * \param ctx      AES context
 * \param mode     AES_ENCRYPT or AES_DECRYPT
 * \param length   length of the input data
 * \param iv_off   offset in IV (updated after use)
 * \param iv       initialization vector (updated after use)
 * \param input    buffer holding the input data
 * \param output   buffer holding the output data
 */
void aes_crypt_cfb( aes_context *ctx,
                    int mode,
                    int length,
                    int *iv_off,
                    unsigned char iv[16],
                    unsigned char *input,
                    unsigned char *output );

/**
 * \brief          Checkup routine
 *
 * \return         0 if successful, or 1 if the test failed
 */
int aes_self_test( int verbose );

#endif /* aes.h */
