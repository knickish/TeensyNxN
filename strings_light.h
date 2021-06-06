#pragma once

unsigned stou(char* text_num)
{
    unsigned int acc = 0; // Accumulator

	while (*text_num) {
		char c = *text_num++;
		if (c >= '0' && c <= '9') {
			acc = acc * 10 + (c - '0');
		} else {
			break;
			
		}
    }
	return acc;
}

char* utos(unsigned uint_val)
{
	static char str_ret[20] = {0};

	switch (uint_val){ //special cases
		case 0:
			return str_ret;
		case 1:
		{
			str_ret[0] = '1';
			return str_ret;
		}
		default:
			break;
	}

	unsigned short index = 0;
	unsigned acc = 1; 
	while(acc<uint_val)
	{
		acc *= 10;
	}
	unsigned uint_val_tmp = uint_val;
	acc = acc/10;

	while (acc) {
		char c = '0' + uint_val_tmp/acc;
		uint_val_tmp -= uint_val_tmp%acc;
		acc /= 10;
		str_ret[index] = c;
		index++;
    }
	return str_ret;
}

int strncpy(char* dest, char* src, int maxchars)
{
	if(!dest || !src)
		return 0;
	int copied = 0;
	while (copied<maxchars && *(src+copied)){
		*(dest+copied)= *(src+copied);
		copied++;
	}
	return copied;
}