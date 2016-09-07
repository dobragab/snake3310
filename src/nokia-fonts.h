/*
 * nokia-fonts.h: Nokia 3310 fonts
 *
 * Copyright (c) 2013, Přemysl Janouch <p.janouch@gmail.com>
 * All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#ifndef NOKIA_FONTS_H
#define NOKIA_FONTS_H

struct nokia_menu_char
{
	short width;
	short advance;
	unsigned char rows[6];
};

struct nokia_small_char
{
	short width;
	short advance;

	// This font seems to have one additional line above and one
	// under to have the proper line height for display.
	unsigned char rows[8];
};

struct nokia_big_char
{
	short width;
	short advance;

	// This font seems to have one additional line above
	// to have the proper line height for display.
	unsigned short rows[13];
};

struct nokia_menu_char   *nokia_get_menu_char             (char    ch);
struct nokia_small_char  *nokia_get_small_char            (char    ch);
struct nokia_small_char  *nokia_get_small_bold_char       (char    ch);
struct nokia_big_char    *nokia_get_big_char              (char    ch);

struct nokia_small_char  *nokia_get_small_char_wide       (wchar_t ch);
struct nokia_small_char  *nokia_get_small_bold_char_wide  (wchar_t ch);
struct nokia_big_char    *nokia_get_big_char_wide         (wchar_t ch);

#endif // ! NOKIA_FONTS_H

