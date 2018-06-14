/* user and group to drop privileges to */
static const char *user  = "nobody";
static const char *group = "nogroup";

static const char *colorname[NUMCOLS] = {
	[INIT] =   "#84b97c",     /* after initialization */
	[INPUT] =  "#639ee4",   /* during input */
	[FAILED] = "#dc657d",   /* wrong password */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 0;
