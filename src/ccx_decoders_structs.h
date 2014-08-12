#ifndef CCX_DECODERS_STRUCTS_H

#include "ccx_common_platform.h"

/* flag raised when end of display marker arrives in Dvb Subtitle */
#define SUB_EOD_MARKER (1 << 0 )
struct cc_bitmap
{
	int x;
	int y;
	int w;
	int h;
	int nb_colors;
	unsigned char *data[2];
	int linesize[2];
};

/**
* Raw Subtitle struct used as output of decoder (cc608)
* and input for encoder (sami, srt, transcript or smptett etc)
*/
struct cc_subtitle
{
	/**
	* A generic data which contain data according to decoder
	* just now only struct cc_eia608_screen is placed here
	* @warn decoder cant output multiple types of data
	*/
	void *data;
	/** number of data */
	unsigned int nb_data;
	/**  type of subtitle */
	enum subtype type;
	/* set only when all the data is to be displayed at same time */
	LLONG start_time;
	LLONG end_time;
	/* flags */
	int flags;
	/* index of language table */
	int lang_index;
	/** flag to tell that decoder has given output */
	int got_output;
};

enum ccx_eia608_format
{
	SFORMAT_CC_SCREEN,
	SFORMAT_CC_LINE,
	SFORMAT_XDS
};

enum cc_modes
{
	MODE_POPON = 0,
	MODE_ROLLUP_2 = 1,
	MODE_ROLLUP_3 = 2,
	MODE_ROLLUP_4 = 3,
	MODE_TEXT = 4,
	MODE_PAINTON = 5,
	// Fake modes to emulate stuff
	MODE_FAKE_ROLLUP_1 = 100
};

/**
* This structure have fields which need to be ignored according to format,
* for example if format is SFORMAT_XDS then all fields other then
* xds related (xds_str, xds_len and  cur_xds_packet_class) should be
* ignored and not to be derefrenced.
*
* TODO use union inside struct for each kind of fields
*/
typedef struct eia608_screen // A CC buffer
{
	/** format of data inside this structure */
	enum ccx_eia608_format format;
	unsigned char characters[15][33];
	unsigned char colors[15][33];
	unsigned char fonts[15][33]; // Extra char at the end for a 0
	int row_used[15]; // Any data in row?
	int empty; // Buffer completely empty?
	/** start time of this CC buffer */
	LLONG start_time;
	/** end time of this CC buffer */
	LLONG end_time;
	enum cc_modes mode;
	int channel; // Currently selected channel
	int my_field; // Used for sanity checks
	/** XDS string */
	char *xds_str;
	/** length of XDS string */
	size_t xds_len;
	/** Class of XDS string */
	int cur_xds_packet_class;
} eia608_screen;

#define CCX_DECODERS_STRUCTS_H
#endif