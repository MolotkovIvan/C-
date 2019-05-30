#include <iostream>
#include <vector>

using namespace std;

#include <cstdio>

/** Interface */

inline int readChar();
template <class T = int> inline T readInt(); 
template <class T> inline void writeInt( T x, char end = 0 );
inline void writeChar( int x ); 
inline void writeWord( const char *s );

/** Read */

static const int buf_size = 4096;

inline int getChar() {
	static char buf[buf_size];
	static int len = 0, pos = 0;
	if (pos == len)
		pos = 0, len = fread(buf, 1, buf_size, stdin);
	if (pos == len)
		return -1;
	return buf[pos++];
}

inline int readChar() {
	int c = getChar();
	while (c <= 32)
		c = getChar();
	return c;
}

template <class T>
inline T readInt() {
	int s = 1, c = readChar();
	T x = 0;
	if (c == '-')
		s = -1, c = getChar();
	while ('0' <= c && c <= '9')
		x = x * 10 + c - '0', c = getChar();
	return s == 1 ? x : -x;
}

/** Write */

static int write_pos = 0;
static char write_buf[buf_size];

inline void writeChar( int x ) {
	if (write_pos == buf_size)
		fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
	write_buf[write_pos++] = x;
}

template <class T> 
inline void writeInt( T x, char end ) {
	if (x < 0)
		writeChar('-'), x = -x;

	char s[24];
	int n = 0;
	while (x || !n)
		s[n++] = '0' + x % 10, x /= 10;
	while (n--)
		writeChar(s[n]);
	if (end)
		writeChar(end);
}

inline void writeWord( const char *s ) {
	while (*s)
		writeChar(*s++);
}

struct Flusher {
	~Flusher() {
		if (write_pos)
			fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
	}
} flusher;


typedef unsigned long long int ull;
int n, k;
vector<ull> t;
vector<int> a;

void build() {
	t.resize(2*n);
	for (int i = 0; i < n; i++) {
		t[i+n] = a[i];
	}
	for (int i = n-1; i>0; i--) {
		t[i] = t[i*2] + t[i*2+1];
	}
}

ull getSum(int l, int r) {
	ull res = 0;
	for (l += n, r += n; l <= r; l /= 2, r /= 2) {
		if (l % 2 == 1) res += t[l++];
		if (r % 2 == 0) res += t[r--];
	}
	return res;
}

void change(int k, int v) {
	t[k += n] = v;
	for (k /= 2; k >= 1; k/=2) {
		t[k] = t[k*2] + t[k*2+1];
	}
}

int main() {
	n = readInt(), k = readInt();
	int two = 2;
	while (two < n) {two *= 2;}
	n = two;
	a.resize(n, 0);
	build();
	for (int i = 0; i < k; i++) {
		char cmd = readChar();
		if (cmd == 'A') {
			int m = readInt(), v = readInt();
			change(m-1, v);
		} else if (cmd == 'Q') {
			int l = readInt(), r = readInt();
			writeInt(getSum(l-1, r-1)); writeChar('\n');
		}
	}
	return 0;
}