#ifndef _BLOWFISH_H_
#define _BLOWFISH_H_

/*
blowfish.h:  Header file for blowfish.c

Copyright (C) 1997 by Paul Kocher

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.
You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


See blowfish.c for more information about this file.
*/

extern "C" class Blowfish {
public:
	Blowfish();
	virtual ~Blowfish();
private:
	unsigned long P[16 + 2];
	unsigned long S[4][256];
private:
	static const unsigned long ORIG_P[16 + 2];
	static const unsigned long ORIG_S[4][256];
	unsigned long F(unsigned long x);
public:
	void Init(unsigned char *key, int keyLen);
	void Encrypt(unsigned long *xl, unsigned long *xr);
	void Decrypt(unsigned long *xl, unsigned long *xr);
	void SwapEndian(unsigned long *src);
public:
	void Encrypt(const void *buf, unsigned int llen);
	void Decrypt(const void *buf, unsigned int llen);
};

#endif


