#ifndef DEFINES_H
# define DEFINES_H

/*	LOGICALS */
# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define FAILURE 1
# define INCREASING 1
# define DECREASING -1

/*	SCREEN RESOLUTION */
# define RES_Y 720
# define RES_X 1280

/*	KEYCODES */
# define ESC 65307
# define PLUS 65451
# define MINUS 65453
# define UP_ARR 65362
# define DN_ARR 65364
# define LE_ARR 65361
# define RI_ARR 65363

/*	MOUSE CODES */
# define UP_SCR 4
# define DN_SCR 5
# define L_CLK 1
# define R_CLK 2
# define M_CLK 3

/*	FRACTAL VARIABLES */
# define MANDE 0
# define JULIA 1
# define BND_X -2.5
# define BND_Y -1.0
# define CH_ITE 8
# define LIM_ITE 1056

/*	JULIA PARAMS */
/*
#define cRe -0.7
#define cIm 0.27015
*/
/*
#define cRe -0.038088
#define cIm 0.9754633
*/
#define cRe 0.285
#define cIm 0.013


/*	COLORS */
# define BLACK 0x0
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0xFF00
# define BLUE 0xFF

#endif
