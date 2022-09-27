#include <bits/stdc++.h>
#include <stdint.h>
using namespace std;
#define BLOCK_SIZE 1024
#define Ch(x, y, z) ((x & y) ^ (~x & z))
#define Maj(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define RotR(x, n) ((x >> n) | (x << ((sizeof(x) << 3) - n)))
#define Sig0(x) ((RotR(x, 28)) ^ (RotR(x, 34)) ^ (RotR(x, 39))) // for a
#define Sig1(x) ((RotR(x, 14)) ^ (RotR(x, 18)) ^ (RotR(x, 41))) // for e
#define sig0(x) (RotR(x, 1) ^ RotR(x, 8) ^ (x >> 7))
#define sig1(x) (RotR(x, 19) ^ RotR(x, 61) ^ (x >> 6))
string input;
int bufferSize;
const uint64_t hInitial[8] = {0x6a09e667f3bcc908ULL,
							  0xbb67ae8584caa73bULL,
							  0x3c6ef372fe94f82bULL,
							  0xa54ff53a5f1d36f1ULL,
							  0x510e527fade682d1ULL,
							  0x9b05688c2b3e6c1fULL,
							  0x1f83d9abfb41bd6bULL,
							  0x5be0cd19137e2179ULL};
const uint64_t k[80] = {0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL, 0xb5c0fbcfec4d3b2fULL, 0xe9b5dba58189dbbcULL, 0x3956c25bf348b538ULL,
						0x59f111f1b605d019ULL, 0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL, 0xd807aa98a3030242ULL, 0x12835b0145706fbeULL,
						0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL, 0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL, 0x9bdc06a725c71235ULL,
						0xc19bf174cf692694ULL, 0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL, 0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL,
						0x2de92c6f592b0275ULL, 0x4a7484aa6ea6e483ULL, 0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL, 0x983e5152ee66dfabULL,
						0xa831c66d2db43210ULL, 0xb00327c898fb213fULL, 0xbf597fc7beef0ee4ULL, 0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL,
						0x06ca6351e003826fULL, 0x142929670a0e6e70ULL, 0x27b70a8546d22ffcULL, 0x2e1b21385c26c926ULL, 0x4d2c6dfc5ac42aedULL,
						0x53380d139d95b3dfULL, 0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL, 0x81c2c92e47edaee6ULL, 0x92722c851482353bULL,
						0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL, 0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL, 0xd192e819d6ef5218ULL,
						0xd69906245565a910ULL, 0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL, 0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL,
						0x2748774cdf8eeb99ULL, 0x34b0bcb5e19b48a8ULL, 0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL, 0x5b9cca4f7763e373ULL,
						0x682e6ff3d6b2b8a3ULL, 0x748f82ee5defb2fcULL, 0x78a5636f43172f60ULL, 0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL,
						0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL, 0xbef9a3f7b2c67915ULL, 0xc67178f2e372532bULL, 0xca273eceea26619cULL,
						0xd186b8c721c0c207ULL, 0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL, 0x06f067aa72176fbaULL, 0x0a637dc5a2c898a6ULL,
						0x113f9804bef90daeULL, 0x1b710b35131c471bULL, 0x28db77f523047d84ULL, 0x32caab7b40c72493ULL, 0x3c9ebe0a15c9bebcULL,
						0x431d67c49c100d4cULL, 0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL, 0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817ULL};
void takeInput()
{
	getline(cin, input);
}
void appendLength(int length, uint64_t &lo, uint64_t &hi)
{
	lo = length;
	hi = 0x00ULL;
}
void moduloF(uint64_t **buffer)
{
	uint64_t h[8]; // Initialize Vector
	uint64_t s[8];
	uint64_t w[80];

	memcpy(h, hInitial, 8 * sizeof(uint64_t));

	for (int i = 0; i < bufferSize; i++)
	{
		// make message scheduler
		memcpy(w, buffer[i], 16 * sizeof(uint64_t)); // first 16 words direct copy from buffer

		for (int j = 16; j < 80; j++) // fill next 80 words
		{
			w[j] = w[j - 16] + sig0(w[j - 15]) + w[j - 7] + sig1(w[j - 2]);
		}

		memcpy(s, h, 8 * sizeof(uint64_t)); // initialize 8 registers with h initial

		for (int j = 0; j < 80; j++)
		{
			// s[0]=a, s[1]=b, s[2]=c, s[3]=d, s[4]=e, s[5]=f, s[6]=g, s[7]=h
			uint64_t t1 = s[7] + Sig1(s[4]) + Ch(s[4], s[5], s[6]) + k[j] + w[j]; // t1=  h+ ch(e,f,g)_sig1(e)+w+k
			uint64_t t2 = Sig0(s[0]) + Maj(s[0], s[1], s[2]);					  // sig0(a)+maj(a,b,c)
			s[7] = s[6];														  // h=g
			s[6] = s[5];														  // g=f
			s[5] = s[4];														  // f=e
			s[4] = s[3] + t1;													  // e=d+t1
			s[3] = s[2];														  // d=c
			s[2] = s[1];														  // c=b
			s[1] = s[0];														  // b=a
			s[0] = t1 + t2;														  // a=t1+t2
		}
		for (int j = 0; j < 8; j++)
		{
			h[j] += s[j]; // add to edit VECTOR
		}
	}
	for (int i = 0; i < 8; i++)
	{
		cout << hex << h[i];
	}
}
uint64_t **padding(unsigned char *input)
{
	int len = strlen((const char *)input);
	int l = len * 8; // byte to bit
	int k = (896 - 1 - l) % BLOCK_SIZE;
	bufferSize = (l + 1 + k + 128) / BLOCK_SIZE;

	// initialize input buffer
	uint64_t **buffer = new uint64_t *[bufferSize]; // total n

	for (int i = 0; i < bufferSize; i++)
	{
		buffer[i] = new uint64_t[16]; // 64 bits er 16 ta array lagbe
	}
	uint64_t in;
	int index;

	// Either copy existing message, add 1 bit or add 0 bit
	for (int i = 0; i < bufferSize; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			in = 0x0ULL;
			for (int k = 0; k < 8; k++)
			{
				index = i * 128 + j * 8 + k;
				if (index < len)
				{
					in = in << 8 | (uint64_t)input[index]; // if less than len take from input
				}
				else if (index == len)
				{
					in = in << 8 | 0x80ULL; // if equal to len use 1
				}
				else
				{
					in = in << 8 | 0x0ULL; // if greater pad 0
				}
			}
			buffer[i][j] = in;
		}
	}
	appendLength(l, buffer[bufferSize - 1][15], buffer[bufferSize - 1][14]); // last er duita bit length
	return buffer;
}
void sha()
{
	uint64_t **buffer; // pura message ta etay rakhbo total 16*64bits	   // 512 bit word 8 ta 8 bit

	buffer = padding((unsigned char *)input.c_str()); // prepared n*16*64 bit blocks using padding
	moduloF(buffer);
}
int main()
{
	takeInput();
	sha();
}
