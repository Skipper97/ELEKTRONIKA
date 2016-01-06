/*
Some examples of the functions of the lcddriver library, by Huub Smeitink, using a modified library from Dryden

Just connect the screen to the pic as configured in the code, use a 8mhz crystal

For more information: HMSProjects.com
*/


#include "lcddriver.c"

// TFT display connections
char TFT_DP_Lo at latB;
char TFT_DP_Hi at latD;
sbit TFT_WR at latA1_bit;
sbit TFT_RD at latA2_bit;
sbit TFT_CS at latA3_bit;
sbit TFT_RS at latA4_bit;
sbit TFT_RST at latA5_bit;

char TFT_DP_Lo_Direction at TRISB;
char TFT_DP_Hi_Direction at TRISD;
sbit TFT_WR_Direction at TRISA1_bit;
sbit TFT_RD_Direction at TRISA2_bit;
sbit TFT_CS_Direction at TRISA3_bit;
sbit TFT_RS_Direction at TRISA4_bit;
sbit TFT_RST_Direction at TRISA5_bit;
// End of TFT display connections


const unsigned int image[] =
{
0x5AEB,0x2945,0x2945,0x5289,0xADB3,0xB613,0xADD2,0xBE35,0xEF9B,0xF7BC,0xF7DE,0xFFFF,0xFFFF,0xFFFF,0xAD75,0x73CD,0x5B2A,0x52A9,0x4207,0x4227,
0x39E6,0x4207,0x4208,0x3A07,0x39E7,0x39E7,0x39E7,0x39E7,0x39E7,0x3A07,0x4207,0x39C6,0x39C6,0x4207,0x39E7,0x39C6,0x4208,0x4228,0x39C6,0x4228,
0x4A48,0x18C3,0x1082,0x20E3,0x6BAB,0xBE33,0xADB1,0xCED6,0xE779,0xF7FD,0xFFDE,0xFFFF,0xFFFF,0xFFFF,0xE73C,0x73EE,0x52C9,0x4247,0x3A06,0x4247,
0x2944,0x2144,0x3185,0x3185,0x31C6,0x2985,0x2965,0x2965,0x2965,0x2964,0x2944,0x2944,0x2965,0x31A5,0x31A5,0x2144,0x2944,0x2965,0x2124,0x31C6,
0x39E7,0x2124,0x0861,0x18C2,0x4227,0xAD92,0xD6D5,0xD6F6,0xCEB7,0xE73B,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xBDF6,0x6BAC,0x5B0A,0x52A9,0x3A06,
0x31A5,0x3185,0x39C6,0x39C6,0x4227,0x31A5,0x31A5,0x39E6,0x39C6,0x3185,0x2964,0x2964,0x2964,0x39E6,0x4A88,0x39C6,0x31A5,0x39C6,0x31A5,0x4227,
0x2104,0x18C3,0x18C3,0x18C3,0x18E3,0x8C90,0xBE35,0xA571,0x94CF,0x7C0E,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xF79D,0xAD94,0x7C4E,0x6BAC,0x4A67,
0x4206,0x31A5,0x31A5,0x31C5,0x3A06,0x3A06,0x39E6,0x4227,0x4247,0x4206,0x4206,0x31C5,0x31C5,0x39E6,0x4227,0x3A06,0x39C6,0x31C6,0x31A5,0x4227,
0x2104,0x2104,0x10A2,0x18E3,0x1082,0x4A48,0xAD74,0x848E,0x846D,0x52C9,0xDEFA,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xEF7D,0xA573,0x9510,0x73AC,
0x4A67,0x39E5,0x4227,0x4A68,0x4247,0x4A68,0x52A9,0x4AA8,0x4A68,0x4247,0x4A88,0x4206,0x4A67,0x4A88,0x4247,0x39C6,0x39C6,0x31C5,0x39C6,0x4A89,
0x18E3,0x18E3,0x0841,0x31A6,0x0020,0x39C6,0xE75B,0xBE55,0x8CCF,0x4A68,0x9CF2,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xCE98,0x9D31,0x7C2D,
0x5B09,0x4267,0x4AA8,0x5B09,0x52C9,0x4267,0x52A8,0x4A88,0x4A87,0x4A67,0x4A68,0x52A9,0x5AE9,0x4AA8,0x4247,0x4206,0x3A06,0x4227,0x4A88,0x52A9,
0x20E4,0x1082,0x0000,0x39C7,0x18A3,0x0861,0xA552,0xCED7,0x6BEB,0x52C9,0x39E6,0xEF5C,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xE75C,0xA593,0x94F0,
0x7C4E,0x73ED,0x7C4D,0x638B,0x636A,0x52E8,0x634B,0x5AE9,0x4247,0x4247,0x4A47,0x4A88,0x632A,0x5AE9,0x4A67,0x4A88,0x4A88,0x4226,0x4227,0x52A9,
0x20E4,0x10A2,0x0000,0x31A6,0x4207,0x0000,0x630B,0xEF9A,0x8C8D,0x52A9,0x10A2,0x94D1,0xF7DE,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFDF,0xCE98,0x9D51,
0xA551,0x8C8F,0x8CAF,0x73CC,0x6BAB,0x7C0C,0x846E,0x634A,0x4AA8,0x4A88,0x52E9,0x52C9,0x5AE9,0x5AE9,0x52C8,0x5B09,0x4A88,0x4247,0x4A68,0x52C9,
0x2965,0x1062,0x0000,0x1082,0x39C7,0x0020,0x2944,0xDEF9,0xD6D7,0x31A5,0x1082,0x31A4,0xD6D9,0xFFFF,0xFFFF,0xFFFF,0xF7DE,0xDF1A,0xE75B,0xC676,
0xBE54,0xB5F3,0xA571,0x9D30,0x9510,0x9D30,0x94F0,0x7C0D,0x5B2A,0x52E9,0x52E9,0x5B09,0x52E9,0x52C8,0x6B8B,0x634A,0x4A67,0x4A88,0x4227,0x52C9,
0x31A6,0x0861,0x0000,0x0000,0x4228,0x0841,0x18E3,0xBDF5,0xEFBB,0x52A8,0x0861,0x0861,0x634C,0xFFFF,0xFFFE,0xFFFF,0xFFFF,0xADB3,0xB616,0xD6D8,
0xE79A,0xCEB7,0x73CC,0x2964,0x844E,0xD6F8,0xA551,0x846E,0x7C0D,0x636A,0x6BAC,0x6B8B,0x634A,0x5B2A,0x6B8B,0x5B2A,0x5AE9,0x5AC9,0x4A47,0x632A,
0x2124,0x0000,0x0000,0x0000,0x4208,0x39C7,0x0020,0x73AD,0xE759,0x73CD,0x10A2,0x0881,0x2124,0xA553,0xF7BC,0xEF9C,0xD6F9,0xB615,0x740D,0x848F,
0x7C4E,0x4267,0x2144,0x52A9,0x31C6,0xA554,0xC676,0xA572,0x94EF,0x73EC,0x73CC,0x6B8B,0x636A,0x634B,0x636B,0x634A,0x634A,0x6B6B,0x632A,0x7BED,
0x18C3,0x0000,0x0000,0x0000,0x10A2,0x6B4D,0x0000,0x1082,0xA552,0x73AD,0x18C3,0x0860,0x1081,0x18C2,0x9490,0xDF39,0x9D31,0x9531,0x6C2D,0x5309,
0x4267,0x4247,0x7C2E,0xF7FB,0xA573,0x52AA,0xE75B,0xADD3,0x9D30,0x740C,0x846D,0x7C2C,0x636A,0x632A,0x634A,0x634A,0x5B09,0x73ED,0x7C2D,0x6BAC,
0x18C3,0x0000,0x0000,0x0000,0x0000,0x5AAA,0x1061,0x0000,0x632B,0xA532,0x2945,0x0841,0x0861,0x10A3,0x2144,0x9D11,0xE77A,0xADD3,0x8CCF,0x63AB,
0x4AE8,0x5B4A,0xBE35,0xF7FC,0x9D52,0x31A5,0xCEB8,0xB5F4,0x9D30,0x848E,0x9D30,0x9D51,0x6BAB,0x52E9,0x5B09,0x634A,0x6BAB,0x8CAF,0xB5D4,0x73CC,
0x18A3,0x0000,0x0000,0x0000,0x0000,0x39E7,0x3186,0x0000,0x1082,0x94D0,0xADB2,0x5AE9,0x2103,0x1082,0x18E3,0x2144,0x8450,0xDF19,0xCE96,0xADD3,
0x742D,0x5B6A,0xA592,0xADD4,0x4288,0x29A4,0xBE16,0xC655,0xA571,0x8C8F,0x7C2C,0x846E,0x6BAB,0x632A,0x5B09,0x5B09,0x6B8B,0x7C0C,0x9510,0x94F0,
0x18A3,0x0000,0x0000,0x0000,0x0000,0x3185,0x630B,0x0000,0x0000,0x10A2,0x8CAE,0xC655,0xA571,0x4A67,0x0020,0x18E3,0x2964,0x6BAC,0xE75B,0xF7FD,
0xDF3A,0x9D72,0x5B69,0x4AC8,0x4267,0x4267,0xADB3,0xBE34,0x9D71,0x9D51,0x8CAE,0x7C4D,0x6BAB,0x52C8,0x73EC,0x740C,0x7C0C,0x73EC,0x94F0,0x848E,
0x18E3,0x0000,0x0000,0x0000,0x0000,0x0841,0x73CD,0x10A2,0x0000,0x0000,0x10A2,0x634B,0xB5F4,0xB5D4,0x9CD2,0x634C,0x31A5,0x2984,0x73CD,0xEF9C,
0xF7BC,0xF7DD,0xB5F5,0x63AB,0x42A8,0x5B6A,0xBE54,0xC675,0xB634,0xA572,0x7C4D,0x844E,0x73EC,0x5B29,0x7C2C,0x8CCF,0x94F0,0x9510,0xAD92,0x9D31,
0x39C7,0x0000,0x0000,0x0020,0x0000,0x0000,0x52AA,0x3185,0x0000,0x0000,0x0001,0x0000,0x10A2,0x844E,0xEFBB,0xC657,0x9D32,0x73ED,0x52E9,0xAD94,
0xFFFE,0xFFFF,0xFFFF,0xE75C,0xA553,0x8CCF,0xD6D7,0xDF39,0xD6D7,0xAD92,0x848E,0x7C2D,0x6B8B,0x5B2A,0x7C2C,0x846D,0x94EF,0xADB2,0x9D30,0xB5F3,
0x39C7,0x0821,0x0000,0x0000,0x0000,0x0000,0x18C3,0x31A6,0x0000,0x0000,0x0000,0x1082,0x2103,0x4247,0x8C6F,0x73AC,0x73CD,0x6B6C,0x634C,0x4A89,
0x52EA,0x5B2B,0x5B4B,0x636C,0x8450,0xA513,0xE75C,0xF7BD,0xD6F8,0xADB2,0x9510,0x846E,0x740D,0x7C2D,0x94EF,0x9510,0x9510,0xA571,0x94EF,0xA592,
0x18C3,0x0000,0x0000,0x0000,0x0000,0x0000,0x0841,0x20E4,0x0841,0x1062,0x20E4,0x2124,0x2103,0x2124,0x18C3,0x0861,0x0841,0x0841,0x0861,0x10A2,
0x10A2,0x10A2,0x10C2,0x18E2,0x1903,0x2123,0x4A68,0xCE78,0xE77A,0xB614,0xA551,0xA571,0x8CCE,0x848E,0x8CAE,0x9510,0x9510,0xA591,0xADD2,0xA592,
0x18C3,0x0000,0x0000,0x0000,0x1062,0x1082,0x0841,0x0841,0x0841,0x0821,0x0841,0x0000,0x0000,0x0000,0x0000,0x0020,0x0841,0x0841,0x0861,0x0861,
0x0861,0x0861,0x0861,0x0861,0x10A2,0x18C2,0x10C2,0x3A07,0xC677,0xCED7,0xADD3,0xA572,0xA572,0x9D30,0xA591,0xA551,0x9D50,0xA591,0xADB2,0xBE14,
0x18C3,0x0020,0x0841,0x18A3,0x18E3,0x1062,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0020,0x0821,
0x0841,0x0841,0x0841,0x0861,0x1061,0x1082,0x10A2,0x2124,0xBE36,0xCEB7,0xADB3,0xADB3,0xADB3,0xADB1,0xBE54,0x9D50,0x9D50,0xAD92,0xB5F3,0xBE34,
0x2104,0x0861,0x0841,0x0821,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0020,0x0841,0x1082,0x10A2,0x1082,0x0861,0x0020,0x0000,0x0021,0x0821,
0x0821,0x0861,0x0861,0x0020,0x0000,0x0000,0x0882,0x2965,0xAD93,0xD717,0xB5F3,0xD6B7,0xD6F8,0xCE96,0xBE54,0xADD2,0xA571,0xB5F3,0xC675,0xC696,
0x18C3,0x0020,0x0821,0x0000,0x0000,0x0000,0x0000,0x0000,0x1081,0x6B6C,0x39C7,0x1082,0x10A2,0x0861,0x2104,0x2104,0x1062,0x0020,0x0842,0x0841,
0x1061,0x0861,0x10A2,0x4A8A,0x6B4C,0x7BEE,0xA533,0xB5F5,0xCEB7,0xD6D6,0xB5F3,0xDF39,0xDF18,0xDF39,0xDF18,0xB5F3,0xBE34,0xD6F7,0xC695,0xC675,
0x18E3,0x0821,0x0821,0x0020,0x0000,0x0020,0x0000,0x0000,0x18E2,0xBE34,0x5ACA,0x0021,0x0000,0x0000,0x0000,0x0000,0x0000,0x0020,0x0021,0x0862,
0x1082,0x2124,0x31A6,0x8430,0xE75B,0xFFFD,0xF7DC,0xEF7A,0xE759,0xEF9B,0xCE97,0xEF9B,0xDF39,0xD6F8,0xDF39,0xC675,0xBE54,0xC675,0xA571,0xA592,
0x2104,0x0861,0x0861,0x0841,0x0841,0x0841,0x0841,0x0841,0x1082,0x4207,0x2124,0x1082,0x0020,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
0x0020,0x1082,0x2924,0x20E3,0x7BED,0xD6D7,0xF7DB,0xE77A,0x842F,0x6B6C,0x8C91,0xB5D6,0xDF1A,0xE77A,0xDF39,0xDF18,0xD718,0xC695,0xA571,0x9D51,
0x2965,0x1082,0x1061,0x1061,0x0861,0x0841,0x0841,0x0821,0x20E4,0x5AC9,0x4A67,0x73AE,0x18C3,0x31A6,0x52A9,0x4A48,0x5288,0x31A6,0x18C3,0x0000,
0x0000,0x0000,0x0820,0x0841,0x4226,0xCE75,0xF7BC,0xB5D5,0x18C3,0x0840,0x10A1,0x5B0B,0xD6B9,0xEF7C,0xEF7B,0xE759,0xCED7,0xC696,0xBE34,0xADD2,
0x31A6,0x10A2,0x1082,0x1082,0x0861,0x0861,0x0861,0x1061,0x1062,0x3164,0x39E7,0x7BEF,0x18E3,0x2924,0x4A88,0x4A68,0x5AC9,0x6B6C,0x6B6C,0x39C7,
0x0000,0x0000,0x0000,0x0000,0x0840,0xA552,0xC655,0x9D12,0x2965,0x0840,0x0881,0x29A5,0xAD95,0xEF9C,0xEFBC,0xE77A,0xD6F7,0xBE34,0xB613,0xC675,
0x39C6,0x18E3,0x10A2,0x1061,0x1061,0x0861,0x20E3,0x10C2,0x1082,0x736B,0x630A,0x2944,0x1082,0x1082,0x0841,0x0821,0x0000,0x0821,0x4227,0x7BCD,
0x6B4C,0x4207,0x4228,0x3185,0x2104,0x4A88,0x5B09,0x5ACA,0x31A6,0x0020,0x10A2,0x39E6,0xCE98,0xFFDE,0xEF7B,0xEFBB,0xD718,0xCEB6,0xCEB6,0xC695,
0x39C7,0x20E3,0x2103,0x9CD2,0x9490,0x5289,0x7BCE,0x4A89,0x18C3,0x52A8,0x9CF0,0x630B,0x18A3,0x1082,0x1083,0x0841,0x18C2,0x842E,0xADB2,0xA551,
0xA551,0xA551,0x73AD,0x4A68,0x4A48,0x4207,0x39C6,0x1082,0x630C,0x3186,0x18E3,0x4AA8,0xCE98,0xE75C,0xEF7B,0xE75A,0xCEB6,0xCEB6,0xC695,0xC675,
0x39A7,0x18A3,0x2964,0xD6B9,0xDEF9,0xAD74,0x6B4C,0x9491,0x630B,0x39C5,0xC657,0xF79D,0x5289,0x4247,0x18E3,0x4207,0x9CF1,0x6B6B,0x4247,0x5AE9,
0x632A,0x4248,0x2944,0x2124,0x39E7,0x5289,0x2965,0x0821,0x2104,0x2965,0x31A6,0x7BEC,0xCE77,0xEF7B,0xF7DC,0xE77B,0xD6F8,0xD6F7,0xDF18,0xD717,
0x3185,0x18C3,0x18A2,0x31A6,0x31A6,0x18E3,0x2103,0x2985,0x8C90,0x738C,0x73AC,0x8C6F,0xB5B4,0xC635,0x3185,0x52A9,0x5B0A,0x4207,0x39C7,0x5ACA,
0x4248,0x18E3,0x18E3,0x0000,0x0821,0x18E3,0x0841,0x18C3,0x62EB,0x1081,0x2124,0x9CF0,0xD6F9,0xEF9D,0xF7DD,0xF7BD,0xEF9B,0xE77A,0xE77A,0xD6F8,
0x2965,0x18A3,0x10A2,0x0841,0x0842,0x10A2,0x20E3,0x18C2,0x4227,0x4A48,0x39E7,0x9D11,0xB5F4,0xA571,0x3A27,0x18C3,0x2944,0x31A6,0x2945,0x2944,
0x0841,0x528A,0x39C7,0x0000,0x1062,0x1082,0x0000,0x39C7,0x4A68,0x842F,0x52AA,0xAD92,0xE73A,0xF79D,0xF7DE,0xF7BD,0xEFBC,0xEF9B,0xEF9B,0xE75A,
0x2945,0x1082,0x1062,0x1062,0x1082,0x1062,0x1082,0x20E3,0x2103,0x3185,0x4228,0x632B,0x632B,0x632A,0x2965,0x0021,0x39A6,0x18C3,0x18C3,0x18A2,
0x2104,0x3186,0x0000,0x0000,0x1082,0x2124,0x4A49,0x2965,0x1082,0x630B,0x5ACA,0x8C8F,0xCED6,0xEFBB,0xF7DD,0xF7DE,0xF7DE,0xF7DE,0xF7DD,0xF7BC,
0x2945,0x1082,0x1062,0x1082,0x1062,0x0861,0x0861,0x1062,0x10A2,0x18C2,0x2103,0x2124,0x3185,0x2123,0x1081,0x1061,0x39E7,0x1062,0x0821,0x20E3,
0x630C,0x0820,0x0000,0x0000,0x18E3,0x2104,0x52AA,0x6B4C,0x0000,0x18E3,0x3186,0x5B09,0x9D30,0xD6B6,0xEF9B,0xF7BD,0xF7BE,0xFFFF,0xFFDE,0xF7DD,
0x2124,0x1062,0x0861,0x0841,0x0841,0x0821,0x0000,0x0000,0x0820,0x1082,0x2124,0x4A48,0x5AC9,0x6B6C,0x4A88,0x2103,0x2124,0x2124,0x0820,0x2104,
0x2104,0x0000,0x0000,0x0841,0x2945,0x3166,0x2945,0x5ACA,0x632B,0x528A,0x1082,0x5B0A,0xBE34,0xCE95,0xC674,0xD6D8,0xF7BE,0xFFFF,0xFFFF,0xF7DE,
0x20E4,0x0841,0x0841,0x0821,0x0000,0x0000,0x0000,0x1082,0x2944,0x31A5,0x39C6,0x4A68,0x8C8F,0xAD73,0xA553,0x73AD,0x2124,0x18A2,0x2104,0x2104,
0x0841,0x0000,0x0000,0x0821,0x39C7,0x39C7,0x2124,0x2944,0x9CF2,0x4228,0x0821,0x1903,0x4AA8,0x842D,0xB5D2,0xDEF7,0xF7DD,0xFFFE,0xF7DE,0xFFFF,
0x2104,0x0841,0x0020,0x0841,0x1061,0x18A2,0x2944,0x2965,0x5ACA,0x4A89,0x2944,0x39E6,0x52A9,0x632A,0xB5D5,0xAD74,0x0840,0x0020,0x1062,0x3186,
0x18E3,0x0000,0x0020,0x0020,0x2104,0x31A6,0x2104,0x18C2,0x9CF2,0x18E3,0x0861,0x18C3,0x3186,0x39E6,0x73CC,0xBE34,0xEFBB,0xFFFE,0xFFFF,0xFFFF,
0x2104,0x0861,0x0841,0x18C3,0x18E3,0x632C,0x94B1,0x6B6C,0x5AEA,0x5AEA,0x2124,0x31A6,0x4A48,0x630B,0xB5B4,0xA552,0x4A68,0x3185,0x0841,0x2945,
0x3186,0x0000,0x0841,0x0841,0x0821,0x0021,0x0861,0x4207,0x94B1,0x1082,0x2945,0x4A68,0x6B8C,0x73CC,0x842D,0xBE13,0xD6F7,0xEF7C,0xEF9D,0xEF9D,
0x18A3,0x0841,0x0861,0x0821,0x0021,0x1082,0x8450,0x8C70,0x6B4C,0x4227,0x18E3,0x18E3,0x2965,0x2965,0x31A5,0x3185,0x39E6,0x5ACA,0x5ACA,0x1082,
0x2944,0x0861,0x0861,0x0841,0x0821,0x2104,0x52A9,0xA532,0x5ACA,0x18E3,0x634C,0x94D1,0x848E,0x7C2D,0x9D12,0xBE14,0xBE13,0xC656,0xD6D9,0xDED9,
0x18C3,0x0841,0x0820,0x0021,0x10A3,0x1082,0x2965,0xAD73,0x5AEA,0x2104,0x2104,0x2124,0x2104,0x20E3,0x18A2,0x18A2,0x1081,0x2103,0x52A9,0x1081,
0x2944,0x1081,0x0841,0x10A2,0x2944,0x39C6,0x4207,0x52AA,0x2104,0x0020,0x31A6,0x2965,0x31A5,0x4227,0x94D1,0xB612,0xD6F6,0xE779,0xF7BB,0xFFFE,
0x18C3,0x0821,0x0020,0x1082,0x31A7,0x3186,0x2104,0x94D0,0x2964,0x0021,0x18C3,0x2124,0x1082,0x1082,0x1082,0x1082,0x1082,0x1081,0x20E3,0x10A2,
0x2965,0x1061,0x0020,0x2104,0x4207,0x4228,0x5289,0x8430,0x4208,0x18E3,0x2944,0x3165,0x39C6,0x39E8,0xAD73,0xC673,0xD6F6,0xEF79,0xEFBA,0xF7DD,
0x18C3,0x0841,0x0020,0x0841,0x39C6,0x39C6,0x0841,0x5AEA,0x1082,0x0000,0x0000,0x0000,0x0000,0x0020,0x0821,0x0841,0x0861,0x0841,0x0020,0x1061,
0x1062,0x0821,0x0821,0x0841,0x1082,0x1061,0x0841,0x18A2,0x18E3,0x18C3,0x18E3,0x2104,0x2124,0x2945,0x9CF1,0xB612,0xC654,0xE778,0xEF79,0xF7DD,
0x18C3,0x0821,0x0000,0x1062,0x31A6,0x2945,0x18C3,0x2944,0x0820,0x0820,0x0020,0x0841,0x1062,0x0020,0x0020,0x0821,0x0821,0x0841,0x0841,0x0000,
0x0020,0x0000,0x0821,0x0841,0x0841,0x1062,0x0861,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x8C90,0xBE32,0xBE33,0xDF37,0xEF9A,0xF7DC,
0x18A3,0x0821,0x0000,0x0020,0x18E3,0x18C3,0x20E4,0x10A2,0x1082,0x0841,0x18E3,0x2104,0x18E3,0x10A2,0x1082,0x10A2,0x0821,0x18E3,0x18A3,0x0000,
0x0000,0x0000,0x0841,0x18C3,0x1082,0x18C3,0x0862,0x0841,0x0000,0x0000,0x0000,0x0000,0x0821,0x0000,0x73AD,0xCE75,0xDF16,0xCEB6,0xE759,0xF7DC,
0x18A3,0x0821,0x0861,0x0020,0x0841,0x1062,0x2965,0x20E4,0x1062,0x10A2,0x39C7,0x10A2,0x0841,0x0841,0x0000,0x1082,0x18A3,0x2945,0x1062,0x0000,
0x0000,0x0000,0x0000,0x0841,0x0861,0x0841,0x0821,0x0000,0x0841,0x10A2,0x2965,0x18A3,0x0000,0x0000,0x2104,0x8C90,0xAD74,0xB5D5,0xD6B8,0xD6F9,
0x18A3,0x0000,0x0841,0x1062,0x1082,0x18E3,0x2104,0x1082,0x1082,0x2104,0x18C3,0x2965,0x18E3,0x18C3,0x1082,0x0000,0x0841,0x0841,0x0841,0x0020,
0x0000,0x0000,0x0000,0x0020,0x2104,0x18C3,0x18A3,0x1082,0x10A2,0x3185,0x5ACA,0xB595,0x7BCE,0x0821,0x0861,0x18A3,0x31A6,0x5B4B,0x740D,0xA572,
0x18A3,0x0000,0x0000,0x0000,0x0020,0x0861,0x1062,0x1082,0x2124,0x10A2,0x1062,0x31A6,0x31A6,0x10A2,0x10A2,0x0000,0x0000,0x0000,0x0020,0x0000,
0x0000,0x0000,0x0000,0x0000,0x2124,0x2965,0x1082,0x1082,0x8C8E,0x73AC,0x2944,0x630B,0xF7BD,0x5289,0x1082,0x20E4,0x4248,0x5B2B,0x638B,0x8CAF,
0x18A3,0x0000,0x0000,0x0000,0x0000,0x0020,0x1082,0x18C3,0x10A2,0x0821,0x0000,0x1082,0x2104,0x18E3,0x10A2,0x0000,0x0000,0x0841,0x0821,0x0000,
0x0000,0x0000,0x0000,0x0000,0x0841,0x2965,0x18C3,0x2124,0xA550,0x5AE9,0x3186,0x3185,0xC656,0x8C6F,0x0020,0x2104,0x4227,0x52CA,0x52CA,0x7C0E,
0x18A3,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0841,0x0841,0x0861,0x0841,0x0020,0x0020,0x0020,0x0000,0x0000,0x0000,0x0000,0x0821,0x0000,
0x0000,0x0000,0x0000,0x0000,0x0000,0x31A6,0x2125,0x18C3,0x8C6E,0x6BAB,0x630B,0x31C5,0x844E,0x4A68,0x0840,0x2104,0x2124,0x1904,0x2965,0xADB4,
0x18A3,0x0000,0x0000,0x0000,0x0000,0x0821,0x18C3,0x31A6,0x39C7,0x2945,0x10A2,0x0841,0x0000,0x0000,0x0000,0x0020,0x0000,0x10A2,0x0861,0x0020,
0x0000,0x0000,0x0000,0x0000,0x0000,0x1082,0x2945,0x0000,0x6B6B,0x94F0,0x52A9,0x18E3,0x3185,0x1062,0x1082,0x1062,0x0001,0x18A3,0xAD74,0xE77A,
0x18A3,0x0000,0x0000,0x0000,0x0000,0x0821,0x2104,0x3186,0x31A6,0x18C3,0x0841,0x0841,0x0020,0x0000,0x0000,0x0000,0x0000,0x1082,0x0841,0x0000,
0x0000,0x0000,0x0000,0x0000,0x0020,0x18C3,0x2124,0x18E3,0x18C3,0x39A6,0x20E3,0x18A3,0x0841,0x0020,0x0841,0x3186,0x6B8D,0xCE78,0xEFBB,0xCED6,
0x18A3,0x0000,0x0000,0x0000,0x0000,0x0000,0x0841,0x18E3,0x18A2,0x0861,0x0020,0x0020,0x0020,0x0000,0x0000,0x0000,0x0000,0x0020,0x0000,0x0000,
0x0020,0x0000,0x0821,0x0841,0x1082,0x1062,0x0020,0x10A2,0x630C,0x0862,0x10A2,0x0861,0x0000,0x39E7,0xBE16,0xE75A,0xEF9B,0xE79A,0xC695,0xCED6,
0x18A3,0x0000,0x0000,0x0000,0x0000,0x0000,0x1082,0x2124,0x2104,0x2104,0x1062,0x0020,0x0000,0x0000,0x0000,0x0841,0x18A3,0x1082,0x0821,0x0020,
0x0821,0x0020,0x0841,0x0000,0x0000,0x0841,0x1062,0x39E7,0x4A49,0x0000,0x0000,0x0000,0x0000,0xBE16,0xF7DC,0xEF9A,0xDF38,0xDF18,0xD717,0xD717,
0x18A3,0x0000,0x0821,0x0841,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0020,0x0020,0x0000,0x0000,0x0020,0x1082,0x0861,0x0000,0x0821,0x0821,
0x0020,0x0000,0x0841,0x2124,0x2925,0x2124,0x18E3,0x10A2,0x0820,0x0020,0x0000,0x0000,0x52CA,0xDF38,0xCED6,0xDF18,0xDF18,0xD717,0xDF58,0xB634,
0x18A3,0x0000,0x0000,0x0841,0x0841,0x0000,0x0000,0x0841,0x0841,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
0x0020,0x0000,0x0020,0x0861,0x1062,0x1082,0x0000,0x0000,0x0020,0x0020,0x0000,0x2104,0xA572,0xC695,0xB5F2,0xB613,0xC695,0xBE75,0xC675,0xB5F3,
0x18A3,0x0000,0x0000,0x0000,0x0841,0x0841,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
0x0000,0x0000,0x0000,0x0000,0x0861,0x2125,0x20E4,0x0021,0x0821,0x0000,0x18C2,0xAD73,0xC675,0xADB2,0xA591,0xADD2,0xADD2,0xADD2,0xADD2,0xBE34,
0x18A3,0x0000,0x0000,0x0000,0x0000,0x0841,0x0000,0x0020,0x0020,0x0841,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
0x0000,0x0000,0x0000,0x0020,0x18C3,0x0841,0x8C70,0x738D,0x39E7,0x4207,0x4247,0x94CF,0xB613,0xADD2,0xBE33,0xC674,0xADD2,0xA591,0xADD2,0xADD3,
0x18A3,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0020,0x0020,0x0020,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
0x0000,0x0000,0x0841,0x1061,0x0000,0x6B6C,0xDF38,0xD6F8,0xD6F7,0xD6F7,0xB5F3,0xA591,0xADB2,0x9D51,0xA592,0xB613,0xCED6,0xD717,0xC695,0xB614,
0x18A3,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0020,0x0000,0x0841,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0841,
0x0841,0x0841,0x0842,0x0000,0x39C6,0xAD73,0xCEB6,0xD6F7,0xDF38,0xBE34,0xADB2,0xADB1,0xADD2,0xA571,0x9D30,0x950F,0xB613,0xCEB6,0xADD2,0xBE34,
0x18A3,0x0000,0x0000,0x0000,0x0000,0x0000,0x0841,0x0861,0x0000,0x0020,0x0020,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0841,0x0841,
0x0821,0x0841,0x0862,0x6B4D,0xC656,0xCED7,0xCEB7,0xDF18,0xC675,0xA591,0xADB1,0xA591,0xADB2,0xA591,0x9530,0x9510,0xA571,0xB5F3,0x950F,0xAD92,
0x18A3,0x0000,0x0000,0x0000,0x0000,0x0000,0x0020,0x0821,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
0x0000,0x4228,0x7BCD,0xF7DB,0xD6F7,0xD6F7,0xDF39,0xDF18,0xCED6,0xB5F2,0x9D30,0x9D50,0xA570,0xA591,0x9D30,0xA571,0x9530,0x8CCE,0x950F,0x9D51,
0x18C3,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
0x0020,0x2945,0x5288,0x6B6A,0x9D50,0xB634,0xDF38,0xEF9B,0xB5F3,0xB633,0xA571,0xB613,0xADD2,0xA591,0xA591,0xA571,0x9D30,0x9D50,0xA571,0x9D51,
0x18C3,0x0020,0x0821,0x0841,0x0020,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0020,0x0000,0x0000,0x0000,0x0000,
0x0000,0x0841,0x2104,0x31C6,0x4A88,0x6BCB,0xADB1,0xDF17,0xADD3,0xADF3,0xA571,0xBE34,0xADB2,0x9D50,0xA591,0xA591,0xA571,0xA591,0xA571,0xADD3,
0x18A3,0x0000,0x0020,0x0841,0x1062,0x0841,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0841,0x0000,0x0000,0x0000,0x0000,
0x0000,0x1082,0x2966,0x4208,0x4A89,0x5B4A,0x6B8A,0xBDF3,0xAD92,0xA571,0x9D30,0xBE34,0xB613,0xADD2,0xA591,0xA571,0xA571,0xA571,0xA571,0xAD92,
0x18A3,0x0000,0x0000,0x0000,0x0000,0x0000,0x0841,0x0841,0x0020,0x0821,0x1082,0x0841,0x0020,0x0000,0x0861,0x1082,0x0000,0x0000,0x0000,0x0000,
0x0821,0x18A3,0x2925,0x39A7,0x4A69,0x52E9,0x8CAE,0xAD72,0x73CD,0x8CAE,0x8CAE,0xB613,0xB613,0xBE54,0xB5F3,0x950F,0xADB2,0xADD2,0x9D50,0xA551,
0x18C3,0x0000,0x0000,0x0000,0x0000,0x0000,0x18C3,0x1082,0x0000,0x0000,0x0841,0x2945,0x18E3,0x0841,0x1062,0x1062,0x0861,0x0841,0x0841,0x0821,
0x1082,0x2104,0x2985,0x4247,0x5AE9,0x7C0D,0x7C2D,0x5B09,0x7C2D,0x94EF,0x950F,0xB5F3,0xB613,0xB613,0xA591,0x8CCF,0x9D30,0xA570,0x8CCE,0x9D10,
0x18C3,0x0000,0x0000,0x0000,0x0000,0x0021,0x2945,0x0821,0x0000,0x0000,0x1082,0x3186,0x2104,0x18C3,0x18E3,0x18C3,0x2104,0x18C3,0x18C3,0x39C7,
0x39C6,0x528A,0x6B6C,0x634B,0x4A88,0x632A,0x73EC,0xADD3,0xA571,0xA571,0xB5F3,0xB5F3,0xB613,0xB613,0xB5F3,0xADB2,0xAD92,0xA591,0x844D,0x846E,
0x18C3,0x0000,0x0000,0x0000,0x0000,0x20E4,0x39C7,0x0000,0x0000,0x1082,0x4A49,0x4228,0x2104,0x20E4,0x1062,0x0841,0x0841,0x0000,0x18A2,0x4A89,
0x0841,0x10A2,0x1082,0x0821,0x0000,0x738D,0xD6F7,0x94EF,0x9D30,0x8CCE,0x94EF,0xB5F3,0xA592,0x9D50,0x9D50,0x9D30,0x8CCE,0x94CF,0x6BCB,0x846E,
0x18C3,0x0821,0x0000,0x0000,0x0000,0x2124,0x10A2,0x0000,0x0020,0x39C7,0x5ACB,0x31A6,0x10A2,0x0821,0x0000,0x0000,0x0000,0x18A3,0x1082,0x0000,
0x0000,0x0000,0x0000,0x0000,0x1062,0x39C6,0xD6F8,0xA550,0x8CCE,0x8CAE,0x94EE,0xADB2,0xADB2,0x9D51,0x94CF,0x94EF,0x8C8E,0x8CAE,0x6BAB,0x846E,
0x18C3,0x0000,0x0000,0x0000,0x0000,0x39C6,0x0861,0x0000,0x18A2,0x4A69,0x2965,0x0861,0x0000,0x0000,0x0000,0x0000,0x18A3,0x18C3,0x0020,0x0000,
0x0000,0x0020,0x18C3,0x31C6,0x2124,0x2125,0xA552,0xADB2,0x9D50,0x8CCF,0x94EF,0x9D50,0xA591,0x9D51,0x8CCF,0x8C8E,0x8CAE,0x94EF,0x7C0C,0x846F,
0x18C3,0x0000,0x0000,0x0000,0x0861,0x31A6,0x0000,0x0020,0x39C7,0x2124,0x0000,0x0000,0x0000,0x0000,0x0821,0x18C3,0x10A2,0x0000,0x0000,0x0000,
0x0020,0x0000,0x632B,0xCEB6,0x5AE9,0x2125,0x630A,0xADD2,0x9D71,0x950F,0x950F,0x8CCE,0x94EF,0x94EF,0x8CCE,0x846D,0x7C4D,0x7C2D,0x636A,0x844E,
0x20E4,0x0000,0x0000,0x0000,0x10A2,0x18E3,0x0000,0x18A3,0x2965,0x0020,0x0000,0x0000,0x0000,0x0000,0x18E3,0x1082,0x0000,0x0000,0x0000,0x0000,
0x0000,0x10A3,0x73CD,0xB613,0x73ED,0x18C4,0x5AEA,0xADB2,0xA571,0x9510,0x7C4C,0x848D,0x846D,0x844D,0x846D,0x7C4D,0x73EC,0x634A,0x5B09,0x6B8C,
0x2945,0x0000,0x0000,0x0000,0x2124,0x0861,0x0020,0x2965,0x18E3,0x0000,0x0000,0x0000,0x0821,0x18E3,0x1082,0x0000,0x0000,0x0000,0x0000,0x18A2,
0x18C3,0x2145,0x844E,0x8CAE,0x4247,0x1904,0x6BAC,0x9D30,0x8CCE,0x848E,0x6BCB,0x846D,0x740C,0x73CB,0x73CB,0x6BAB,0x6B8B,0x632A,0x52C9,0x632B,
0x4A89,0x0841,0x0000,0x0821,0x2124,0x0000,0x18C3,0x4228,0x18C3,0x0000,0x0000,0x0000,0x18A3,0x1082,0x0000,0x0000,0x0000,0x0000,0x0821,0x18E3,
0xA553,0x844E,0x52A9,0x2985,0x2104,0x52CA,0x8C8E,0x848E,0x848E,0x73CB,0x6BCB,0x73EC,0x6B8B,0x73CC,0x6BAB,0x634A,0x5AE9,0x5AE9,0x4A67,0x5ACA,
0x5AEB,0x18C3,0x0000,0x18C3,0x2945,0x0000,0x2944,0x39C7,0x0821,0x0000,0x0000,0x0861,0x20E4,0x0000,0x0000,0x0000,0x0000,0x0000,0x0841,0x4247,
0xCEB5,0xB613,0x846E,0x632A,0x636B,0x7C0C,0x8C8E,0x8CAE,0x6BCB,0x7C0D,0x7C0D,0x6BCC,0x634A,0x634A,0x5B09,0x5B09,0x52C8,0x4A88,0x4247,0x52A9,
0x4228,0x2103,0x0000,0x2945,0x10A2,0x0000,0x2945,0x2945,0x0000,0x0000,0x0000,0x18E3,0x0841,0x0000,0x0000,0x0000,0x0020,0x18C3,0x2986,0x8CAF,
0xA550,0x94EF,0x7C0D,0x73CC,0x73CC,0x73CC,0x6B8B,0x636B,0x5B09,0x5B2A,0x636B,0x636A,0x52E9,0x52A8,0x4227,0x4247,0x4247,0x4227,0x3A06,0x52C9,
0x31A6,0x2104,0x0020,0x2965,0x0020,0x0841,0x3186,0x1082,0x0000,0x0000,0x10A2,0x18E3,0x0000,0x0000,0x0000,0x0000,0x10A3,0x2965,0x5B0A,0x844D,
0x73CB,0x6B8C,0x6B8B,0x6B8B,0x636A,0x5B09,0x52C9,0x52A8,0x52C9,0x52C8,0x52E9,0x52E9,0x4AA8,0x4227,0x39E6,0x4226,0x3A06,0x4227,0x4227,0x52A9,
0x2965,0x2124,0x0020,0x10A2,0x0000,0x10A2,0x31A6,0x0861,0x0000,0x0020,0x2925,0x0841,0x0000,0x0000,0x0020,0x1082,0x2946,0x4A48,0x6BAB,0x6BAB,
0x5B2A,0x52C9,0x52A8,0x5B0A,0x52E9,0x52C9,0x4A67,0x4206,0x4227,0x4A88,0x4A88,0x4267,0x4247,0x4A88,0x4247,0x4227,0x4247,0x4227,0x3A06,0x4A88,
0x2965,0x2945,0x18A2,0x10A2,0x0000,0x10A2,0x2124,0x0821,0x0000,0x0861,0x10A2,0x0000,0x0841,0x0861,0x18A3,0x2965,0x39C6,0x5B0A,0x5AE9,0x52E9,
0x4A87,0x4A87,0x4227,0x4A88,0x4A67,0x4A68,0x4227,0x39E6,0x39E6,0x4227,0x3A06,0x3A06,0x39E6,0x4206,0x4227,0x4226,0x31C5,0x39E6,0x31C5,0x4247,
0x2945,0x2104,0x2104,0x10A2,0x0020,0x18E3,0x0861,0x0000,0x0000,0x0821,0x0000,0x0020,0x1062,0x10A2,0x2125,0x31C6,0x4A88,0x5AE9,0x4A88,0x4A68,
0x4247,0x4A47,0x39E6,0x31A5,0x3A06,0x3A06,0x3A07,0x31C6,0x31A5,0x39E6,0x39E6,0x3A06,0x39C6,0x31C5,0x39E6,0x39E6,0x2984,0x2985,0x3185,0x4227,
0x39E7,0x18E3,0x0000,0x0000,0x1062,0x2104,0x0841,0x0000,0x0000,0x0000,0x0020,0x0861,0x1082,0x18C3,0x3186,0x3A07,0x52A9,0x4A88,0x4A68,0x4A68,
0x3A06,0x39E6,0x39E6,0x31C6,0x31C5,0x39C6,0x4207,0x3A07,0x39C6,0x31C6,0x3185,0x31C6,0x31A5,0x2964,0x3185,0x3185,0x2964,0x2985,0x2965,0x39E7,
0x4A69,0x1082,0x0000,0x0000,0x18A2,0x1082,0x0020,0x0020,0x0000,0x0000,0x0821,0x0861,0x1082,0x2124,0x3186,0x4227,0x4247,0x3A06,0x39C6,0x31A5,
0x31A5,0x31A5,0x31A6,0x31C6,0x31A5,0x31A5,0x31A5,0x31C6,0x31A5,0x31A5,0x2985,0x2965,0x2944,0x2944,0x2144,0x2124,0x2144,0x2124,0x2124,0x31A6,
0x52AA,0x18C3,0x18C3,0x2104,0x2965,0x18E3,0x18E3,0x18E3,0x18C3,0x18C3,0x18E3,0x2104,0x2945,0x39C7,0x4A48,0x52A9,0x4A68,0x4248,0x3A07,0x39E7,
0x39E7,0x39E7,0x39E7,0x4228,0x3A07,0x3A07,0x4207,0x4207,0x4227,0x4207,0x3A07,0x3A07,0x39E6,0x39C6,0x39E7,0x39C7,0x39C6,0x31A6,0x3186,0x4A28,
};

void main() {

  ADCON0 = 0x0F;           // turn off analog inputs
  ADCON1 = 0x0F;           // turn off analog inputs
  CMCON  |= 7;                            // Disable comparators

    TRISA = 0;
    TRISB = 0;
    TRISD = 0;
    TRISE = 0;
    latA = 0x00;
    latB = 0x00;
    latD = 0x00;
    latE = 0x00;

   TFT_Init();
   TFT_Fill(black);

   TFT_Text("A small text",0,0,8,black,white);
   delay_ms(1000);
   TFT_Text("A large text",0,20,16,black,white);
   delay_ms(1000);


   delay_ms(500);
   TFT_Fill(blue);
   delay_ms(500);
   TFT_Fill(black);
   delay_ms(500);
   TFT_Fill(green);
   delay_ms(500);
   TFT_Fill(l_gray);
   delay_ms(500);
   TFT_Fill(d_gray);
   delay_ms(500);
   TFT_Fill(cyan);
   delay_ms(500);
   TFT_Fill(red);
   delay_ms(500);
   TFT_Fill(yellow);
   delay_ms(1000);
   
   TFT_Box(10,10,60,80,blue);
   delay_ms(1000);
   
   TFT_Dot(100,50,black);
   delay_ms(1000);
   
   TFT_Line(10,10,200,200,purple);
   delay_ms(1000);
   
   TFT_H_Line(100,150,100,l_gray);
   delay_ms(1000);
   
   TFT_V_Line(100,150,100,l_gray);
   delay_ms(1000);
   
   TFT_Rectangle(10,10,200,200,d_gray);
   delay_ms(1000);
   
   TFT_Circle(80,80,20,1,black);
   delay_ms(1000);
   
   TFT_Circle(80,80,20,0,purple);
   delay_ms(1000);
   
   TFT_Image(0,240,40,83,image);

}