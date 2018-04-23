#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MEM_LOOP 1	//メモリ量解析ループ

struct WAV_DATA
{
	unsigned char riff[4];
	unsigned int fs;
	unsigned char wave[4];
	unsigned char fmt[4];
	unsigned int ms;
	unsigned short format;
	unsigned short channel;
	unsigned int hz;
	unsigned int byte_s;
	unsigned short bloc_size;
	unsigned short bit_size;
	unsigned short h_size;
	unsigned char fact[4];
	unsigned int wav_size;
	unsigned char data[4];
	unsigned int data_size;
};

void main()
{
	//WAV形式情報
	WAV_DATA wav_data;
	//ファイルデータ
	unsigned char* pData = 0;
	unsigned Size = 0;

	//waveファイルをメモリ内に展開
	FILE* fp = fopen("b3.wav", "rb");

	if (fp == NULL) return ;

	//ファイルサイズ
	while (MEM_LOOP)
	{
		if (fgetc(fp) == EOF)
			break;
		Size++;
	}

	//メモリに移す
	fseek(fp, 0, SEEK_SET);
	pData = new unsigned char[Size];
	fread(pData, Size, 1, fp);

	//WAV情報取得
	memmove(wav_data.riff, &pData[0], sizeof(unsigned char) * 4);
	memmove(&wav_data.fs, &pData[4], sizeof(unsigned int));
	memmove(wav_data.wave, &pData[8], sizeof(unsigned char) * 4);
	memmove(wav_data.fmt, &pData[12], sizeof(unsigned char) * 4);
	memmove(&wav_data.ms, &pData[16], sizeof(unsigned int));
	memmove(&wav_data.format, &pData[20], sizeof(unsigned short));
	memmove(&wav_data.channel, &pData[22], sizeof(unsigned short));
	memmove(&wav_data.hz, &pData[24], sizeof(unsigned int));
	memmove(&wav_data.byte_s, &pData[28], sizeof(unsigned int));
	memmove(&wav_data.bloc_size, &pData[32], sizeof(unsigned short));
	memmove(&wav_data.bit_size, &pData[34], sizeof(unsigned short));
	memmove(&wav_data.h_size, &pData[36], sizeof(unsigned short));
	memmove(wav_data.fact, &pData[38], sizeof(unsigned char) * 4);
	memmove(&wav_data.wav_size, &pData[42], sizeof(unsigned int));
	memmove(&wav_data.data, &pData[46 + wav_data.wav_size], sizeof(unsigned char) * 4);
	memmove(&wav_data.data_size, &pData[50 + wav_data.wav_size], sizeof(unsigned int));
	fclose(fp);

	//音ビジュアル化
	for (int i = 0; i < wav_data.data_size; i++)
	{
		short s = 0;
		memmove(&s, &pData[50 + wav_data.wav_size + i], sizeof(short));

		float f = (s + 32768.0f) / 65534.0f;

		for (float j = 0.0f; j < f; j += 0.1f)
		{
			printf("■");
		}
		printf("□\n");
	}

	delete[] pData;
}