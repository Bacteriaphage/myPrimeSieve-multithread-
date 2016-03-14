#include "next_7_finder.h"

extern _u8 digits[4][20] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
                            ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 
	                        ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 
	                        ,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
extern bool consecutive[4] = { false, false, false, false };
extern _ulong low[4] = { 0, 0, 0, 0 };
extern _ulong high[4]= { 0, 0, 0, 0 };

_ulong init_finder(_ulong sieve_base, _uint mul) {
	consecutive[mul] = false;
	for (_u8 i = 0; i < 20; i++) {
		digits[mul][i] = 0;
	}

	while (sieve_base) {
		digits[mul][digits[mul][19]] = (sieve_base % 10);
		sieve_base = sieve_base / 10;
		digits[mul][19]++;
	}
	_u8 i, j, k;
	_ulong current = 0;
	for (i = digits[mul][19] - 1; i >= 0; i--) {
		if (digits[mul][i] == 7) break;
	}
	switch (i) {
	case -1: case 0: {
		if (digits[mul][0] < 7) {
			digits[mul][0] = 7;
		}
		else {
			for (j = 1; ;j++) {
				if (digits[mul][j] != 9) break;
			}
			if (digits[mul][j] == 6) {
				low[mul] = 0;
				digits[mul][0] = 9;
				for (i = 18; i >= 0; i--) {
					low[mul] = low[mul] * 10 + digits[mul][i];
				}
				low[mul]++;
				digits[mul][j] = 8;
				consecutive[mul] = true;
			}
			else {
				digits[mul][j]++;
			}
			for (k = j - 1;k > 0; k--) {
				digits[mul][k] = 0;
			}
			if (consecutive[mul] == true) {
				high[mul] = 0;
				digits[mul][0] = 0;
				for (i = 18; i >= 0; i--) {
					high[mul] = high[mul] * 10 + digits[mul][i];
				}
			}
			digits[mul][k] = 7;
		}
		break;
	}
	default: {
		if (digits[mul][i] == 6) {
			low[mul] = 0;
			digits[mul][i] = 8;
			for (i = 18; i >= 0; i--) {
				low[mul] = low[mul] * 10 + digits[mul][i];
			}
			consecutive[mul] = true;
		}
		else {
			digits[mul][i]++;
		}
		for (k = i - 1;k > 0; k--) {
			digits[mul][k] = 0;
		}
		if (consecutive[mul] == true) {
			high[mul] = 0;
			digits[mul][0] = 0;
			for (i = 18; i >= 0; i--) {
				high[mul] = high[mul] * 10 + digits[mul][i];
			}
		}
		digits[mul][k] = 7;
		break;
	}
	}
	for (i = 18; i >= 0; i--) {
		current = current * 10 + digits[mul][i];
	}
	return current;
}

_ulong next_7(_uint mul) {
	_u8 i,j,k;
	_ulong current = 0;
	if (consecutive[mul] == true) consecutive[mul] = false;
	for (j = 1; ;j++) {
		if (digits[mul][j] != 9) break;
	}
	if (digits[mul][j] == 6) {
		low[mul] = 0;
		digits[mul][0] = 9;
		for (i = 18; i >= 0; i--) {
			low[mul] = low[mul] * 10 + digits[mul][i];
		}
		low[mul]++;
		digits[mul][j] = 8;
		consecutive[mul] = true;
	}
	else {
		digits[mul][j]++;
	}
	for (k = j - 1;k > 0; k--) {
		digits[mul][k] = 0;
	}
	if (consecutive[mul] == true) {
		high[mul] = 0;
		digits[mul][0] = 0;
		for (i = 18; i >= 0; i--) {
			high[mul] = high[mul] * 10 + digits[mul][i];
		}
	}
	digits[mul][k] = 7;

	for (i = 18; i >= 0; i--) {
		current = current * 10 + digits[mul][i];
	}
	return current;
}
