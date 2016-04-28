/* Twofish Cipher C API
Copyright © 1998 Matthew Skala.
Copyright © 1998 Werner Koch.
Copyright © Marc Mutz.
Copyright © Colin Slater.
	      __	   __
  _______ ___/ /______ ___/ /__
 / __/ -_) _  / __/ _ \ _  / -_)
/_/  \__/\_,_/\__/\___/_,_/\__/
Copyright © 2011-2016 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#ifndef __cipher_Twofish_H__
#define __cipher_Twofish_H__

#include <Z/ABIs/generic/cipher.h>

#define TWOFISH_KEY_MINIMUM_SIZE 16
#define TWOFISH_KEY_MAXIMUM_SIZE 32
#define TWOFISH_KEY_WORD_SIZE	 8
#define TWOFISH_WORD_SIZE	 16

typedef struct {
	zuint32 s[4][256], w[8], k[32];
} Twofish;

Z_C_SYMBOLS_BEGIN

#ifndef CIPHER_TWOFISH_ABI
#	ifdef CIPHER_TWOFISH_AS_STATIC
#		define CIPHER_TWOFISH_ABI
#	else
#		define CIPHER_TWOFISH_ABI Z_API
#	endif
#endif

CIPHER_TWOFISH_ABI extern ZCipherABI const abi_cipher_twofish;

#ifndef CIPHER_TWOFISH_OMIT_FUNCTION_PROTOTYPES

#	ifndef CIPHER_TWOFISH_API
#		ifdef CIPHER_TWOFISH_AS_STATIC
#			define CIPHER_TWOFISH_API
#		else
#			define CIPHER_TWOFISH_API Z_API
#		endif
#	endif

	CIPHER_TWOFISH_API void twofish_set_key	 (Twofish*    object,
						  void const* key,
						  zsize	      key_size);

	CIPHER_TWOFISH_API void twofish_encipher (Twofish*    object,
						  void const* block,
						  zsize	      block_size,
						  void*	      output);

	CIPHER_TWOFISH_API void twofish_decipher (Twofish*    object,
						  void const* block,
						  zsize	      block_size,
						  void*	      output);

#endif

Z_C_SYMBOLS_END

#endif /* __cipher_Twofish_H__ */