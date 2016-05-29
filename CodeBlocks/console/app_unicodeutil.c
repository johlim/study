#ifndef _APP_UNICODEUTIL_C_
#define _APP_UNICODEUTIL_C_
/**
 * Copyright (c) 2007-2009 Core Logic, Inc. All Rights Reserved.
 *
 * THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
 * BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
 * CORE LOGIC, INC.
 *
 *
 *

	\File 	:	app_variable.c
	\Author :	CBU Development Team
	\Date 	:	6/24/2010
	\Brief	: 	This file contains Global Variable for Blackbox Application.

	\Revision history :
 		-

 */
//==============================================================================
// includes
//==============================================================================
#ifdef ARM
#include <glib.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>
#include <fcntl.h>
#include <locale.h>

#include "app_unicodeutil.h"

//==============================================================================
// defines
//==============================================================================
// #defineÀ» ÀÌ¿ëÇÑ constant/function macrožŠ Á€ÀÇÇÑŽÙ. Constant macro ÀÌÈÄ¿¡
// function macrožŠ À§Ä¡œÃÅ²ŽÙ. žžŸà constnat definitionÀÌ Æ¯Á€ Àü¿ª º¯Œö¿Í
// °ü·ÃÀÌ ÀÖÀ» °æ¿ì, º» Á€ÀÇŽÂ ±× Àü¿ª º¯ŒöžŠ Á€ÀÇÇÏ±â ¹Ù·Î Àü¿¡ ÇÏµµ·Ï ÇÏžç,
// Æ¯Á€ structure¿Í °ü·ÃÀÌ ÀÖÀ» °æ¿ì¿¡ŽÂ, ±× structureÀÇ typedef ŸÈ¿¡Œ­ Á€ÀÇ
// ÇÏµµ·Ï ÇÑŽÙ.
//==============================================================================
#define UNICODE_MAX_PATH        255
#define SSAL_OS_CopyStr strcpy
#define SSAL_OS_FindChar strchr
//==============================================================================
// typedefs
//==============================================================================
// typedefžŠ ÀÌ¿ëÇÑ µ¥ÀÌÅÍÀÇ ÅžÀÔ ¹× œºÆ®·°ÃÄžŠ Á€ÀÇÇÑŽÙ.
//==============================================================================


//==============================================================================
// import vaiables
//==============================================================================


//==============================================================================
// import functions
//==============================================================================


//==============================================================================
// globals
//==============================================================================
// µÑ ÀÌ»óÀÇ ÆÄÀÏ¿¡Œ­ °øÀ¯ µÇŽÂ Àü¿ª º¯ŒöžŠ Á€ÀÇÇÑŽÙ.
//==============================================================================


//==============================================================================
// locals
//==============================================================================
// ÀÌ ÆÄÀÏ¿¡Œ­žž »ç¿ëµÇŽÂ Àü¿ª º¯ŒöžŠ Á€ÀÇÇÑŽÙ.
// static keywordžŠ ¹ÝµåœÃ ºÙÀÎŽÙ.
//==============================================================================


//==============================================================================
// locals functions
//==============================================================================
// ÀÌ ÆÄÀÏ¿¡Œ­žž »ç¿ëµÇŽÂ ÇÔŒöžŠ Á€ÀÇÇÑŽÙ.
// static keywordžŠ ¹ÝµåœÃ ºÙÀÎŽÙ.
//==============================================================================
#ifdef UTF_8_CONVERT
void Convert_UTF82Unicode(unsigned char *utf8, unsigned short *uni)
{
    unsigned short  ScalarValue;
    unsigned int    CodeRange[4] = {
        {0x80},
        {0xC0},
        {0xE0},
        {0xF0}
    };
    unsigned short  i;

    ScalarValue = *utf8;

    while (ScalarValue)
    {
        for (i = 0; i < 4; i++)
        {
            if (ScalarValue < CodeRange[i])
            {
                switch (i)
                {
                case 0:
                    *uni = *utf8 & 0x7F;
                    break;

                case 1:
                    ScalarValue = (*utf8 & 0x1F) << 6;
                    utf8++;
                    ScalarValue |= *utf8 & 0x3F;
                    *uni = ScalarValue;
                    break;

                case 2:
                case 3:
                    ScalarValue = (*utf8 & 0x0F) << 12;
                    utf8++;
                    ScalarValue |= (*utf8 & 0x3F) << 6;
                    utf8++;
                    ScalarValue |= *utf8 & 0x3F;
                    *uni = ScalarValue;
                    break;
                }
                break;
            }

        }
        utf8++;
        uni++;
        ScalarValue = *utf8;
    }
    *uni = NULL;
}


void Convert_Unicode2UTF8(unsigned short *uni, unsigned char *utf8)
{
    unsigned short  UniChar;
    unsigned int    CodeRange[3] = {
        {0xF800},
        {0x0780},
        {0x007F}
    };

    UniChar = *uni;
    while (UniChar)
    {
        if (CodeRange[0] & UniChar)
        {
            *utf8++ = 0xD0 | (0x0F & (UniChar >> 12));
            *utf8++ = 0x80 | (0x3F & (UniChar >> 6));
            *utf8++ = 0x80 | (0x3F & UniChar);
        }
        else if (CodeRange[1] & UniChar)
        {
            *utf8++ = 0xC0 | (0x1F & (UniChar >> 6));
            *utf8++ = 0x80 | (0x3F & UniChar);
        }
        else if (CodeRange[2] & UniChar)
        {
            *utf8++ = (0x7F & UniChar);
        }
        else
            break;

        uni++;
        UniChar = *uni;
    }
    *utf8 = 0;
}
#endif
#ifdef KSC5601_CONVERT
#define	KSC5601_DEFAULT_CHAR	(0x0020)
//==============================================================================
// Function Name :     KSC5601_Uni2ASCII
// Description :
// Input param. :
// Return Value :
//==============================================================================
static unsigned char KSC5601_Uni2ASCII(unsigned short uni, unsigned char *ascii)
{
    unsigned short  uniCHO;
    unsigned short  uniJUNG;
    unsigned short  uniJONG;
    tHSyl           syl;
    unsigned short  uiSyl, uiIdx;

	unsigned short iStart = 0;
	unsigned short iEnd = 2350;
	unsigned short iMid;

    if (uni >= 0xAC00 && uni <= 0xD7A3)
    {
        uniCHO = (unsigned short)((uni - 0xAC00) / 588);
        uniJUNG = (unsigned short)(((uni - 0xAC00) % 588) / 28);
        uniJONG = (unsigned short)((uni - 0xAC00) % 28);

        uniCHO = (unsigned short)(uniCHO + 0x0002);
        syl.hPhoneme.hFlag = 1;
        syl.hPhoneme.hCho = uniCHO;
        syl.hPhoneme.hJung = KSC5601_UNI2KSSM_JUNG[uniJUNG];
        syl.hPhoneme.hJong = KSC5601_UNI2KSSM_JONG[uniJONG];

        while (1)
        {
            iMid = (unsigned short)(((iEnd - iStart) >> 1) + iStart);
            if (KSC5601_table[iMid] == syl.hCode)
                break;

            if (iEnd <= iStart)
                return (unsigned char)HCTBL_NOT_FOUND;
            else if (KSC5601_table[iMid] > syl.hCode)
                iEnd = (unsigned short)(iMid - 1);
            else
                iStart = (unsigned short)(iMid + 1);
        }
        uiIdx = iMid;
        uiSyl = (unsigned short)((((uiIdx/94) + 0xB0) << 8) + (uiIdx % 94) + 0xA1);

        *ascii = (unsigned char)(uiSyl >> 8);
        *(ascii + 1) = (unsigned char)(uiSyl & 0x00ff);
        *(ascii + 2) = '\0';
    }
    else
    {
        *ascii = (unsigned char)uni;
        *(ascii+1) = '\0';
    }
    return 0;
}

//==============================================================================
// Function Name :     KSC5601_ASCII2Uni
// Description :
// Input param. :
// Return Value :
//==============================================================================

static unsigned char KSC5601_ASCII2Uni(unsigned char *ascii, unsigned short *uni)
{
    unsigned char   KSC_char = *ascii;
    unsigned short  KSC_wchar;
    unsigned char   ret = 1;
    short           idx;
    tHSyl           syl;

    if (!(*ascii&0x80))
    {
        *uni = (unsigned short) *ascii;
        return 1;
    }

    KSC_wchar = (unsigned short)((*ascii << 8) | (*(ascii + 1) & 0x00ff));
    if (KSC_char & 0x80)
    {
        if (KSC_wchar >= 0xB0A0 && KSC_wchar <= 0xC8FF)
        {
            idx = (short)(((KSC_wchar >> 8) - 0x00B0) * 94 + ((KSC_wchar & 0x00ff) - 0x00A1));
            syl.hCode = KSC5601_table[idx];
            *uni = (unsigned short)(0xAC00 + ((syl.hPhoneme.hCho - 0x02) * 588) + (KSC5601_KSSM2UNI_JUNG[syl.hPhoneme.hJung]) * 28 + (KSC5601_KSSM2UNI_JONG[syl.hPhoneme.hJong]));
        }
        else
            ret = 0;
    }
    else
        *uni = (unsigned short) KSC_char;
    return ret;//1;
}


void Convert_Unicode2ASCII(unsigned short *uni, unsigned char *ascii)
{
    unsigned char   kscBuf[128];
    unsigned char  *pstr;
    unsigned long   i;

    for (pstr = ascii, i = 0; uni[i] != 0x0000; i++)
    {
        KSC5601_Uni2ASCII(uni[i], kscBuf);
        SSAL_OS_CopyStr((char *) pstr, (char *) kscBuf);
        pstr = (unsigned char *) SSAL_OS_FindChar((char *) pstr, '\0');
    }
}

void Convert_ASCII2Unicode(unsigned char *ascii, unsigned short *uni)
{
    unsigned char  *pstr;
    unsigned int    i;
    unsigned int    uniLen;

    for (pstr = ascii, i = 0, uniLen = 0; *pstr; pstr++, i++, uniLen++)
    {
        if (!KSC5601_ASCII2Uni(pstr, &uni[i]))
        {
            uni[i] = KSC5601_DEFAULT_CHAR;
        }
        if (*pstr & 0x80)
            pstr++;
    }

    uni[i] = 0x0000;
}

#endif                          //KSC5601

//==============================================================================
// export functions
//==============================================================================
// ŽÙž¥ ÆÄÀÏ¿¡Œ­ È£ÃâµÇŽÂ ÇÔŒöžŠ Á€ÀÇÇÑŽÙ.
//==============================================================================

//==============================================================================
// Function Name :     PromoteASCIItoUNICODE
// Description :       This function converts file name from ASCII to Unicode
// Input param. :  pFileASCII - Pointer to a File name which is in ASCII format
//                     pFileUni - Pointer to a File name which is in UNICODE format
// Return Value :  On successful completion, returns UNICODE_SUCCESS
//                     Otherwise, UNICODE_FAILURE
//==============================================================================
unsigned char PromoteASCIItoUNICODE(unsigned char *pFileASCII, unsigned short *pFileUni)
{
#ifdef KSC5601_CONVERT
    if ((pFileASCII == 0) || (pFileUni == 0))
    {
        return 0;
    }
    Convert_ASCII2Unicode(pFileASCII, pFileUni);

    return 1;
#elif defined(UTF_8_CONVERT)
    Convert_UTF82Unicode(pFileASCII, pFileUni);
    return 1;
#else
    unsigned short          count = 0;

    if ((pFileASCII == 0) || (pFileUni == 0))
    {
        return 0;
    }

    while ((*pFileASCII) != '\0')       // checks for the end of string
    {
        pFileUni[count] = (unsigned short) * pFileASCII;
        count++;
        pFileASCII++;
    }

	/* °æ°í size °¡ ÀÛÀº°æ¿ì memory overwrite ¹ß»ý by limjh */
    pFileUni[count] = (unsigned short) 0;// outut size must be +1 than input size

    return 1;
#endif
}

//==============================================================================
// Function Name :     DemoteUNICODEtoASCII
// Description :       This function converts file name from Unicode  (which is in English) to ASCII
// Input param. :  pFileUni - Pointer to a File name which is in UNICODE format
//                         pFileASCII - Pointer to a File name which is in ASCII format
// Return Value :  On successful completion, returns 1
//                     Otherwise, 0
//==============================================================================
unsigned char DemoteUNICODEtoASCII(unsigned short *pFileUni, unsigned char *pASCII)
{
#ifdef KSC5601_CONVERT
    if ((pFileUni == 0) || (pASCII == 0))
    {
        return 0;
    }
    Convert_Unicode2ASCII(pFileUni, pASCII);

    return 1;
#elif defined(UTF_8_CONVERT)
    Convert_Unicode2UTF8(pFileUni, pASCII);
    return 1;
#else
	unsigned short             size = 0;
	unsigned short             count = 0;
	unsigned short             tempmem;
	unsigned char              Flag;
	//unsigned char             *Str = 0;
	unsigned char              RTN;
	unsigned char              Str[256+1]={0,};
	if ((pFileUni == 0) || (pASCII == 0))
	{
		return 0;
	}

	size = StrLen_Uni(pFileUni);

	count = 0;
	//Str = (unsigned char *) ClFs_malloc(size + 1);
	//if (Str == 0)
	//    return 0;

	Flag = 0;
	RTN = 1;

	while (pFileUni[count] != (unsigned short) 0)
	{
		tempmem = pFileUni[count];
		if (tempmem <= (unsigned short) 128)
		{
			Str[count] = (unsigned char) tempmem;
		}
		else
		{
			Flag = 1;
			Str[count] = (unsigned char) tempmem;
		}
		count++;

	}
	Str[count] = '\0';

	if (Flag == (unsigned char) 0)
	{
		strcpy((char *) pASCII, (char *) Str);
	}
	else
	{
		RTN = 0;
		strcpy((char *) pASCII, (char *) Str);
	}

	//ClFs_free(Str);
	return RTN;
#endif
}

#endif
