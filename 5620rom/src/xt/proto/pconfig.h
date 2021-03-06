/* */
/*									*/
/*	Copyright (c) 1985,1986,1987,1988,1989,1990,1991,1992   AT&T	*/
/*			All Rights Reserved				*/
/*									*/
/*	  THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T.		*/
/*	    The copyright notice above does not evidence any		*/
/*	   actual or intended publication of such source code.		*/
/*									*/
/* */
/*
**	Configuration data required by packet protocol driver
*/

typedef unsigned char	uchar;

struct Pconfig
{
	int	(*xfuncp)();		/* Function to be called for output */
	int	(*rfuncp)();		/* Function to be called for input */
	void	(*rcfuncp)();		/* Function to be called for control input */
	short	xfdesc;			/* File descriptor for output */
	short	xtimo;			/* Transmit timeout in tscan units */
	uchar	rtimo;			/* Receive timeout in tscan units */
	uchar	cdata;			/* Control information for reply packet */
	uchar	tscan;			/* Timeout scan rate */
	uchar	tflag;			/* Timeout running flag */
};

extern struct Pconfig	pconfig;

#define	MAXTIMORETRYS	1		/* Maximum packets retransmitted per timeout */
#define	Pscanrate	pconfig.tscan
#define	Prtimeout	pconfig.rtimo
#define	Pxtimeout	pconfig.xtimo
#define	Pxfuncp		pconfig.xfuncp
#define	Prfuncp		pconfig.rfuncp
#define	Prcfuncp	pconfig.rcfuncp
#define	Pxfdesc		pconfig.xfdesc
#define	Pcdata		pconfig.cdata
#define	Ptflag		pconfig.tflag

/*
**	Default timeout settings for 1200 baud
*/

#define	PSCANRATE	1		/* Scan once a second */
#define	PRTIMEOUT	2		/* Packet should complete arrival in less than 1 second */
#define	PXTIMEOUT	9		/* Time to transmit 16 full sized packets */
