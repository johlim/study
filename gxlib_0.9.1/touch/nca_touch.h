/*-------------------------- [ Comment ] --------------------------------*\
	File name	: 
	Project		: 
	Description :

	Copyright(c) 
  -----------------------------------------------------------------------
	C0000 - 
	C0001 -
\*-----------------------------------------------------------------------*/

#ifndef __IO_NCA_TOUCH_H__
#define __IO_NCA_TOUCH_H__

/* Header file include --------------------------------------------------*/

/* Define  --------------------------------------------------------------*/

#define VIEW_WIDTH		320
#define VIEW_HEIGHT		240
#define LCD_WIDTH	 		240
#define LCD_HEIGHT	 	320

typedef struct tagTOUCH_POINT
{
	int	x;
	int	y;
		
} NC_TOUCH_POINT;

typedef enum tagTOUCH_CTRL
{
	NCA_CTRL_TOUCH_END,
	NCA_CTRL_TOUCH_CALLBACK,
	NCA_CTRL_TOUCH_INTERVAL,
	NCA_CTRL_TOUCH_MONITORING,
	NCA_CTRL_TOUCH_START,
	NCA_CTRL_TOUCH_STOP,
	NCA_CTRL_TOUCH_MAX
}NCA_CTRL_TOUCH;

struct NCA_TOUCH_OPERATION
{
	const char		*name;
	int				ctxsize;
	int				maxctrl;

	/* common function */
	int				(*open)			(void *ctx);
	int				(*close)			(void *ctx);
//	unsigned int		(*read)			( void *ctx_t,void *data,  int size);
//	unsigned int		(*write)			(void *ctx, unsigned char *data, unsigned int size);
	int				(*control)		(void *ctx, NCA_CTRL_TOUCH type, ...);

	/* component dependent fuction */
};

/* Define variable  -----------------------------------------------------*/
extern struct NCA_TOUCH_OPERATION nca_touch;

/* Define extern variable & function  -----------------------------------*/
#endif /* __NCA_TOUCH_H__ */
