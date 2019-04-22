#ifndef COLOR_H
#define COLOR_H


enum class font
{
	bold              = 1,
	faint             = 2,
	italic            = 3,
	underline         = 4,
	blink             = 5,
	rblink            = 6,
	reversed          = 7,
	conceal           = 8,
	crossed           = 9
};

enum class color
{
	__init            = -2,
	__default         = -1,

	black             = 0,
	red               = 1,
	green             = 2,
	yellow            = 3,
	blue              = 4,
	magenta           = 5,
	cyan              = 6,
	white             = 7,
	grey              = 8,
	maroon            = 9,
	lime              = 10,
	olive             = 11,
	navy              = 12,
	fuchsia           = 13,
	purple            = fuchsia,
	aqua              = 14,
	teal              = aqua,
	silver            = 15,
	grey0             = 16,
	navyblue          = 17,
	darkblue          = 18,
	blue3             = 19,
	darkgreen         = 22,
	deepskyblue4      = 23,
	dodgerblue2       = 27,
	green4            = 28,
	springgreen4      = 29,
	turquoise4        = 30,
	deepskyblue3      = 31,
	green3            = 34,
	springgreen3      = 35,
	darkcyan          = 36,
	lightseagreen     = 37,
	deepskyblue2      = 38,
	deepskyblue1      = 39,
	cyan3             = 43,
	darkturquoise     = 44,
	turquoise2        = 45,
	green1            = 46,
	mediumspringgreen = 49,
	darkred           = 52,
	deeppink4         = 53,
	purple4           = 54,
	blueviolet        = 57,
	orange4           = 58,
	grey37            = 59,
	mediumpurple4     = 60,
	slateblue3        = 61,
	chartreuse4       = 64,
	darkseagreen4     = 65,
	paleturquoise4    = 66,
	steelblue         = 67,
	steelblue3        = 68,
	cornflowerblue    = 69,
	chartreuse3       = 70,
	steelblue1        = 75,
	seagreen3         = 78,
	aquamarine3       = 79,
	mediumturquoise   = 80,
	seagreen2         = 83,
	seagreen1         = 84,
	darkslategray2    = 87,
	plum4             = 96,
	mediumpurple3     = 97,
	yellow4           = 100,
	wheat4            = 101,
	grey53            = 102,
	lightslategrey    = 103,
	mediumpurple      = 104,
	lightslateblue    = 105,
	darkseagreen      = 108,
	lightskyblue3     = 109,
	darkslategray3    = 116,
	skyblue1          = 117,
	chartreuse1       = 118,
	lightgreen        = 119,
	red3              = 124,
	magenta3          = 127,
	indianred         = 131,
	hotpink3          = 132,
	mediumorchid3     = 133,
	mediumorchid      = 134,
	mediumpurple2     = 135,
	darkgoldenrod     = 136,
	lightsalmon3      = 137,
	rosybrown         = 138,
	grey63            = 139,
	gold3             = 142,
	darkkhaki         = 143,
	navajowhite3      = 144,
	grey69            = 145,
	lightsteelblue3   = 146,
	lightsteelblue    = 147,
	yellow3           = 148,
	lightcyan3        = 152,
	lightskyblue1     = 153,
	greenyellow       = 154,
	darkolivegreen2   = 155,
	paleturquoise1    = 159,
	orchid            = 170,
	mediumorchid1     = 171,
	orange3           = 172,
	pink3             = 175,
	plum3             = 176,
	violet            = 177,
	tan               = 180,
	mistyrose3        = 181,
	thistle3          = 182,
	plum2             = 183,
	lightgoldenrod2   = 186,
	lightyellow3      = 187,
	grey84            = 188,
	lightsteelblue1   = 189,
	yellow2           = 190,
	darkolivegreen1   = 191,
	lightcyan1        = 195,
	red1              = 196,
	deeppink2         = 197,
	deeppink1         = 198,
	orangered1        = 202,
	indianred1        = 203,
	salmon1           = 209,
	lightcoral        = 210,
	palevioletred1    = 211,
	orchid2           = 212,
	orchid1           = 213,
	lightsalmon1      = 216,
	lightpink1        = 217,
	pink1             = 218,
	plum1             = 219,
	gold1             = 220,
	mistyrose1        = 224,
	thistle1          = 225,
	yellow1           = 226,
	lightgoldenrod1   = 227,
	khaki1            = 228,
	wheat1            = 229,
	cornsilk1         = 230,
	grey100           = 231,
	grey3             = 232,
	grey7             = 233,
	grey11            = 234,
	grey15            = 235,
	grey19            = 236,
	grey23            = 237,
	grey27            = 238,
	grey30            = 239,
	grey35            = 240,
	grey39            = 241,
	grey42            = 242,
	grey46            = 243,
	grey50            = 244,
	grey54            = 245,
	grey58            = 246,
	grey62            = 247,
	grey66            = 248,
	grey70            = 249,
	grey74            = 250,
	grey78            = 251,
	grey82            = 252,
	grey85            = 253,
	grey89            = 254,
	grey93            = 255
};

#endif