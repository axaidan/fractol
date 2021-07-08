#ifndef ERRORS_H
# define ERRORS_H

enum e_error_codes {
	ER_MLX_INIT,
	ER_WIN_CREA,
	ER_IMG_CREA,
	ER_PATH_CONCAT, // need msg
	ER_BMP_OPEN,	// need msg
	ER_BMP_HDR,		// need msg
	ER_DIB_HDR,		// need msg
	ER_PIX_ARR,		// need msg
	ER_BAD_ARGC,
	ER_BAD_SET,
	ER_BAD_JPRMS,
	ER_ZERO_JPRM,
	ER_EMPTY_ARG
};

#endif
