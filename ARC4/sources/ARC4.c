/* ARC4 Cipher
Copyright (C) 2011 Jon Oberheide.
Copyright (C) 2011-2018 Manuel Sainz de Baranda y Goñi.
Released under the terms of the GNU Lesser General Public License v3. */

#if defined(CIPHER_ARC4_HIDE_API)
#	define CIPHER_ARC4_API static
#elif defined(CIPHER_ARC4_STATIC)
#	define CIPHER_ARC4_API
#else
#	define CIPHER_ARC4_API Z_API_EXPORT
#endif

#if defined(CIPHER_ARC4_HIDE_ABI)
#	define CIPHER_ARC4_ABI static
#elif defined(CIPHER_ARC4_STATIC)
#	define CIPHER_ARC4_ABI
#else
#	define CIPHER_ARC4_ABI Z_API_EXPORT
#endif

#define CIPHER_ARC4_OMIT_FUNCTION_PROTOTYPES

#if defined(CIPHER_ARC4_USE_LOCAL_HEADER)
#	include "ARC4.h"
#else
#	include <cipher/ARC4.h>
#endif


CIPHER_ARC4_API
void arc4_set_key(ARC4 *object, zuint8 const *key, zusize key_size)
	{
	int i, j = 0, k = 0;
	zuint8 a;

	object->x = 1;
	object->y = 0;

	for (i = 0; i < 256; i++) object->s[i] = i;

	for (i = 0; i < 256; i++)
		{
		a = object->s[i];
		j = (j + key[k] + a) & 0xFF;
		object->s[i] = object->s[j];
		object->s[j] = a;
		if (++k >= key_size) k = 0;
		}
	}


CIPHER_ARC4_API
void arc4_cipher(ARC4 *object, zuint8 const *block, zusize block_size, zuint8 *output)
	{
	zuint8 *const s = object->s;
	zuint8 x = object->x, y = object->y, a, b;

	for (; block_size; block_size--)
		{
		a = s[x];
		y = (y + a) & 0xFF;
		b = s[y];
		s[x] = b;
		s[y] = a;
		x = (x + 1) & 0xFF;
		*output++ = *block++ ^ s[(a + b) & 0xFF];
		}

	object->x = x;
	object->y = y;
	}


#if defined(CIPHER_ARC4_BUILD_ABI) || defined(CIPHER_ARC4_BUILD_MODULE_ABI)

	CIPHER_ARC4_ABI ZCipherABI const abi_cipher_arc4 = {
		/* test_key		 */ NULL,
		/* set_key		 */ (ZCipherSetKey )arc4_set_key,
		/* encipher		 */ (ZCipherProcess)arc4_cipher,
		/* decipher		 */ (ZCipherProcess)arc4_cipher,
		/* enciphering_size	 */ NULL,
		/* deciphering_size	 */ NULL,
		/* instance_size	 */ sizeof(ARC4),
		/* key_minimum_size	 */ ARC4_KEY_MINIMUM_SIZE,
		/* key_maximum_size	 */ ARC4_KEY_MAXIMUM_SIZE,
		/* key_word_size	 */ ARC4_KEY_WORD_SIZE,
		/* enciphering_word_size */ ARC4_WORD_SIZE,
		/* deciphering_word_size */ ARC4_WORD_SIZE,
		/* features		 */ FALSE
	};

#endif

#if defined(CIPHER_ARC4_BUILD_MODULE_ABI)

#	include <Z/ABIs/generic/module.h>

	static ZModuleUnit const unit = {
		"ARC4", "ARC4", Z_VERSION(1, 0, 0), &abi_cipher_arc4
	};

	static ZModuleDomain const domain = {"Cipher", Z_VERSION(1, 0, 0), 1, &unit};
	Z_API_WEAK_EXPORT ZModuleABI const __module_abi__ = {1, &domain};

#endif


/* ARC4.c EOF */
