/*
YUV422 data formatting
 _______________________________________________
|  Y0[4:0]  |  U0[2:0]  |  Y1[4:0]  |  V0[2:0]  |
'-----------'-----------'-----------'-----------'

The signals are mux based, so index 2 is always ignored.

*/
#include <iostream>

#define CLIP(RGB) ( (RGB) > 255 ? 255 : (RGB) < 0 ? 0 : RGB)
#define HD_SD		0		//HD=0, SD=1

void collectYUV()
{
	//code here that reads the encoded image and puts YUV into a buffer
	int buffer [3]; 			//YCbCr
								//when all 3 have been stored, call decode
	int rgb[3];
	decodeColors(buffer, rgb);
}

//decodes based on definition
void decodeColors(int* buf, int* rgb)
{
	if(HD_SD)
	{
		YUV2RGB_HD(buf, rgb);
	}
	else
	{
		YUV2RGB_SD(buf, rgb);
	}
}

//High Defn
void YUV2RGB_HD(int* yuv, int* rgb)
{
	rgb[0] = CLIP(1.164(yuv[0] - 16) + 1.793(yuv[2] - 128));
	rgb[1] = CLIP(1.164(yuv[0] - 16) - 0.534(yuv[2] - 128) - 0.213(yuv[1] - 128));
	rgb[2] = CLIP(1.164(yuv[0] - 16) + 2.115(yuv[2] - 128));
}

//Standard Defn
void YUV2RGB_SD(int* yuv, int* rgb)
{
	rgb[0] = CLIP(1.164(yuv[0] - 16) + 1.596(yuv[2] - 128));
	rgb[1] = CLIP(1.164(yuv[0] - 16) - 0.813(yuv[2] - 128) - 0.391(yuv[1] - 128));
	rgb[2] = CLIP(1.164(yuv[0] - 16) + 2.018(yuv[2] - 128));
}





//R = std::max(0, std::min(255, 1.164(Y - 16) + 1.596(Cr - 128)));
//assumes yuv is a 3 bit array
//yuv = [Y, U, V]
