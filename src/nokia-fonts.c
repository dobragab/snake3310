/*
 * nokia-fonts.c: Nokia 3310 fonts
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

#include <wchar.h>
#include <stdio.h>

#include "nokia-fonts.h"

struct nokia_small_char_wide
{
	wchar_t code;
	struct nokia_small_char ch;
};

struct nokia_big_char_wide
{
	wchar_t code;
	struct nokia_big_char ch;
};

static struct nokia_big_char
nokia_big_data[] =
{
	{  3,  4, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
				0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 } }, // space
	{  2,  3, { 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000,
				0xc000, 0x0000, 0xc000, 0xc000, 0x0000, 0x0000 } }, // !
	{  6,  7, { 0x4800, 0x4800, 0x4800, 0x0000, 0x0000, 0x0000, 0x0000,
				0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 } }, // "
	{  7,  8, { 0x0000, 0x0000, 0x6c00, 0x6c00, 0x6c00, 0xfe00, 0x6c00,
				0xfe00, 0x6c00, 0x6c00, 0x6c00, 0x0000, 0x0000 } }, // #
	{  7,  8, { 0x1000, 0x7c00, 0xd600, 0xd000, 0xd000, 0x7c00, 0x1600,
				0x1600, 0x1600, 0xd600, 0x7c00, 0x1000, 0x1000 } }, // $
	{  7,  8, { 0x4600, 0xa400, 0xac00, 0x4800, 0x1800, 0x1000, 0x3000,
				0x2400, 0x6a00, 0x4a00, 0xc400, 0x0000, 0x0000 } }, // %
	{  8,  9, { 0x7000, 0xd800, 0xd800, 0xd800, 0xd800, 0x7200, 0xf600,
				0xdc00, 0xcc00, 0xde00, 0x7300, 0x0000, 0x0000 } }, // &
	{  1,  2, { 0x8000, 0x8000, 0x8000, 0x0000, 0x0000, 0x0000, 0x0000,
				0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 } }, // '
	{  3,  4, { 0x2000, 0x6000, 0x4000, 0xc000, 0xc000, 0xc000, 0xc000,
				0xc000, 0xc000, 0xc000, 0x4000, 0x6000, 0x2000 } }, // (
	{  3,  4, { 0x8000, 0xc000, 0x4000, 0x6000, 0x6000, 0x6000, 0x6000,
				0x6000, 0x6000, 0x6000, 0x4000, 0xc000, 0x8000 } }, // )
	{  7,  8, { 0x0000, 0x0000, 0x0000, 0x4400, 0x6c00, 0x3800, 0xfe00,
				0x3800, 0x6c00, 0x4400, 0x0000, 0x0000, 0x0000 } }, // *
	{  7,  8, { 0x0000, 0x0000, 0x0000, 0x0000, 0x1800, 0x1800, 0x7e00,
				0x1800, 0x1800, 0x0000, 0x0000, 0x0000, 0x0000 } }, // +
	{  3,  4, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
				0x0000, 0x0000, 0x6000, 0x6000, 0xc000, 0x0000 } }, // ,
	{  5,  6, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xf800, 0xf800,
				0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 } }, // -
	{  3,  4, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
				0x0000, 0x0000, 0xc000, 0xc000, 0x0000, 0x0000 } }, // .
	{  5,  6, { 0x1800, 0x1800, 0x3000, 0x3000, 0x3000, 0x6000, 0x6000,
				0x6000, 0xc000, 0xc000, 0xc000, 0x0000, 0x0000 } }, // /
	{  7,  8, { 0x7c00, 0xc600, 0xc600, 0xc600, 0xc600, 0xc600, 0xc600,
				0xc600, 0xc600, 0xc600, 0x7c00, 0x0000, 0x0000 } }, // 0
	{  7,  8, { 0x1800, 0x3800, 0x7800, 0x5800, 0x1800, 0x1800, 0x1800,
				0x1800, 0x1800, 0x1800, 0x1800, 0x0000, 0x0000 } }, // 1
	{  7,  8, { 0x7c00, 0xc600, 0xc600, 0x0600, 0x0600, 0x1c00, 0x7000,
				0xc000, 0xc000, 0xc000, 0xfe00, 0x0000, 0x0000 } }, // 2
	{  7,  8, { 0x7c00, 0xc600, 0x0600, 0x0600, 0x3c00, 0x0600, 0x0600,
				0x0600, 0x0600, 0xc600, 0x7c00, 0x0000, 0x0000 } }, // 3
	{  7,  8, { 0x0400, 0x0c00, 0x1c00, 0x2c00, 0x4c00, 0xcc00, 0xcc00,
				0xfe00, 0x0c00, 0x0c00, 0x0c00, 0x0000, 0x0000 } }, // 4
	{  7,  8, { 0xfc00, 0xc000, 0xc000, 0xc000, 0xfc00, 0xc600, 0x0600,
				0x0600, 0x0600, 0xc600, 0x7c00, 0x0000, 0x0000 } }, // 5
	{  7,  8, { 0x7c00, 0xc600, 0xc000, 0xc000, 0xfc00, 0xc600, 0xc600,
				0xc600, 0xc600, 0xc600, 0x7c00, 0x0000, 0x0000 } }, // 6
	{  7,  8, { 0xfe00, 0x0600, 0x0600, 0x0c00, 0x0c00, 0x1800, 0x1800,
				0x3000, 0x3000, 0x3000, 0x3000, 0x0000, 0x0000 } }, // 7
	{  7,  8, { 0x7c00, 0xc600, 0xc600, 0xc600, 0x7c00, 0xc600, 0xc600,
				0xc600, 0xc600, 0xc600, 0x7c00, 0x0000, 0x0000 } }, // 8
	{  7,  8, { 0x7c00, 0xc600, 0xc600, 0xc600, 0xc600, 0xc600, 0x7e00,
				0x0600, 0x0600, 0xc600, 0x7c00, 0x0000, 0x0000 } }, // 9
	{  3,  4, { 0x0000, 0x0000, 0x0000, 0x0000, 0x6000, 0x6000, 0x0000,
				0x0000, 0x0000, 0x6000, 0x6000, 0x0000, 0x0000 } }, // :
	{  3,  4, { 0x0000, 0x0000, 0x0000, 0x0000, 0x6000, 0x6000, 0x0000,
				0x0000, 0x0000, 0x6000, 0x6000, 0xc000, 0x0000 } }, // ;
	{  5,  6, { 0x0000, 0x0000, 0x0800, 0x1800, 0x3000, 0x6000, 0xc000,
				0x6000, 0x3000, 0x1800, 0x0800, 0x0000, 0x0000 } }, // <
	{  5,  6, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xf800, 0x0000,
				0x0000, 0xf800, 0x0000, 0x0000, 0x0000, 0x0000 } }, // =
	{  5,  6, { 0x0000, 0x0000, 0x8000, 0xc000, 0x6000, 0x3000, 0x1800,
				0x3000, 0x6000, 0xc000, 0x8000, 0x0000, 0x0000 } }, // >
	{  6,  7, { 0x7800, 0x8c00, 0x8c00, 0x0c00, 0x0c00, 0x1800, 0x3000,
				0x3000, 0x0000, 0x3000, 0x3000, 0x0000, 0x0000 } }, // ?
	{  9, 10, { 0x0000, 0x3e00, 0x4100, 0x9480, 0xac80, 0xa480, 0xa480,
				0xa500, 0x9a00, 0x4080, 0x3f00, 0x0000, 0x0000 } }, // @
	{  7,  8, { 0x7c00, 0xc600, 0xc600, 0xc600, 0xc600, 0xc600, 0xc600,
				0xfe00, 0xc600, 0xc600, 0xc600, 0x0000, 0x0000 } }, // A
	{  7,  8, { 0xfc00, 0xc600, 0xc600, 0xc600, 0xfc00, 0xc600, 0xc600,
				0xc600, 0xc600, 0xc600, 0xfc00, 0x0000, 0x0000 } }, // B
	{  6,  7, { 0x7800, 0xcc00, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000,
				0xc000, 0xc000, 0xcc00, 0x7800, 0x0000, 0x0000 } }, // C
	{  7,  8, { 0xf800, 0xcc00, 0xc600, 0xc600, 0xc600, 0xc600, 0xc600,
				0xc600, 0xc600, 0xcc00, 0xf800, 0x0000, 0x0000 } }, // D
	{  7,  8, { 0xfe00, 0xc000, 0xc000, 0xc000, 0xf800, 0xc000, 0xc000,
				0xc000, 0xc000, 0xc000, 0xfe00, 0x0000, 0x0000 } }, // E
	{  7,  8, { 0xfe00, 0xc000, 0xc000, 0xc000, 0xf800, 0xc000, 0xc000,
				0xc000, 0xc000, 0xc000, 0xc000, 0x0000, 0x0000 } }, // F
	{  7,  8, { 0x7c00, 0xc600, 0xc000, 0xc000, 0xc000, 0xce00, 0xc600,
				0xc600, 0xc600, 0xc600, 0x7e00, 0x0000, 0x0000 } }, // G
	{  7,  8, { 0xc600, 0xc600, 0xc600, 0xc600, 0xfe00, 0xc600, 0xc600,
				0xc600, 0xc600, 0xc600, 0xc600, 0x0000, 0x0000 } }, // H
	{  2,  3, { 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000,
				0xc000, 0xc000, 0xc000, 0xc000, 0x0000, 0x0000 } }, // I
	{  5,  6, { 0x1800, 0x1800, 0x1800, 0x1800, 0x1800, 0x1800, 0x1800,
				0x1800, 0x1800, 0x9800, 0x7000, 0x0000, 0x0000 } }, // J
	{  8,  9, { 0xc600, 0xcc00, 0xd800, 0xf000, 0xe000, 0xe000, 0xf000,
				0xd800, 0xcc00, 0xc600, 0xc300, 0x0000, 0x0000 } }, // K
	{  6,  7, { 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000,
				0xc000, 0xc000, 0xc000, 0xfc00, 0x0000, 0x0000 } }, // L
	{  9, 10, { 0x8080, 0xc180, 0xe380, 0xf780, 0xdd80, 0xc980, 0xc180,
				0xc180, 0xc180, 0xc180, 0xc180, 0x0000, 0x0000 } }, // M
	{  7,  8, { 0xc600, 0xc600, 0xe600, 0xe600, 0xf600, 0xd600, 0xde00,
				0xce00, 0xce00, 0xc600, 0xc600, 0x0000, 0x0000 } }, // N
	{  8,  9, { 0x7e00, 0xc300, 0xc300, 0xc300, 0xc300, 0xc300, 0xc300,
				0xc300, 0xc300, 0xc300, 0x7e00, 0x0000, 0x0000 } }, // O
	{  7,  8, { 0xfc00, 0xc600, 0xc600, 0xc600, 0xc600, 0xc600, 0xfc00,
				0xc000, 0xc000, 0xc000, 0xc000, 0x0000, 0x0000 } }, // P
	{  8,  9, { 0x7e00, 0xc300, 0xc300, 0xc300, 0xc300, 0xc300, 0xc300,
				0xc300, 0xd300, 0xdb00, 0x7e00, 0x0600, 0x0000 } }, // Q
	{  8,  8, { 0xfc00, 0xc600, 0xc600, 0xc600, 0xc600, 0xc600, 0xfc00,
				0xd800, 0xcc00, 0xc600, 0xc300, 0x0000, 0x0000 } }, // R
	{  6,  7, { 0x7800, 0xcc00, 0xc000, 0xc000, 0xc000, 0x7800, 0x0c00,
				0x0c00, 0x0c00, 0xcc00, 0x7800, 0x0000, 0x0000 } }, // S
	{  6,  7, { 0xfc00, 0x3000, 0x3000, 0x3000, 0x3000, 0x3000, 0x3000,
				0x3000, 0x3000, 0x3000, 0x3000, 0x0000, 0x0000 } }, // T
	{  7,  8, { 0xc600, 0xc600, 0xc600, 0xc600, 0xc600, 0xc600, 0xc600,
				0xc600, 0xc600, 0xc600, 0x7c00, 0x0000, 0x0000 } }, // U
	{  8,  9, { 0xc300, 0xc300, 0xc300, 0xc300, 0x6600, 0x6600, 0x6600,
				0x2400, 0x3c00, 0x1800, 0x1800, 0x0000, 0x0000 } }, // V
	{ 10, 11, { 0xc0c0, 0xc0c0, 0xc0c0, 0xc0c0, 0x6180, 0x6d80, 0x6d80,
				0x6d80, 0x3f00, 0x3300, 0x3300, 0x0000, 0x0000 } }, // W
	{  7,  8, { 0xc600, 0xc600, 0xc600, 0x6c00, 0x6c00, 0x3800, 0x6c00,
				0x6c00, 0xc600, 0xc600, 0xc600, 0x0000, 0x0000 } }, // X
	{  8,  9, { 0xc300, 0xc300, 0x6600, 0x6600, 0x3c00, 0x3c00, 0x1800,
				0x1800, 0x1800, 0x1800, 0x1800, 0x0000, 0x0000 } }, // Y
	{  7,  8, { 0xfe00, 0x0600, 0x0e00, 0x1c00, 0x3800, 0x7000, 0xe000,
				0xc000, 0xc000, 0xc000, 0xfe00, 0x0000, 0x0000 } }, // Z
	{  4,  5, { 0xf000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000,
				0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xf000 } }, // [
	{  5,  6, { 0xc000, 0xc000, 0x6000, 0x6000, 0x6000, 0x3000, 0x3000,
				0x3000, 0x1800, 0x1800, 0x1800, 0x0000, 0x0000 } }, // backslash
	{  4,  5, { 0xf000, 0x3000, 0x3000, 0x3000, 0x3000, 0x3000, 0x3000,
				0x3000, 0x3000, 0x3000, 0x3000, 0x3000, 0xf000 } }, // ]
	{  5,  6, { 0x2000, 0x7000, 0xd800, 0x8800, 0x0000, 0x0000, 0x0000,
				0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 } }, // ^
	{  8,  8, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
				0x0000, 0x0000, 0x0000, 0x0000, 0xff00, 0x0000 } }, // _
	{  3,  4, { 0x8000, 0x4000, 0x2000, 0x0000, 0x0000, 0x0000, 0x0000,
				0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 } }, // `
	{  6,  7, { 0x0000, 0x0000, 0x0000, 0x7800, 0x0c00, 0x0c00, 0x7c00,
				0xcc00, 0xcc00, 0xcc00, 0x7c00, 0x0000, 0x0000 } }, // a
	{  6,  7, { 0xc000, 0xc000, 0xc000, 0xf800, 0xcc00, 0xcc00, 0xcc00,
				0xcc00, 0xcc00, 0xcc00, 0xf800, 0x0000, 0x0000 } }, // b
	{  5,  6, { 0x0000, 0x0000, 0x0000, 0x7000, 0xc800, 0xc000, 0xc000,
				0xc000, 0xc000, 0xc800, 0x7000, 0x0000, 0x0000 } }, // c
	{  6,  7, { 0x0c00, 0x0c00, 0x0c00, 0x7c00, 0xcc00, 0xcc00, 0xcc00,
				0xcc00, 0xcc00, 0xcc00, 0x7c00, 0x0000, 0x0000 } }, // d
	{  6,  7, { 0x0000, 0x0000, 0x0000, 0x7800, 0xcc00, 0xcc00, 0xfc00,
				0xc000, 0xc000, 0xc400, 0x7800, 0x0000, 0x0000 } }, // e
	{  4,  5, { 0x3000, 0x6000, 0x6000, 0xf000, 0x6000, 0x6000, 0x6000,
				0x6000, 0x6000, 0x6000, 0x6000, 0x0000, 0x0000 } }, // f
	{  6,  7, { 0x0000, 0x0000, 0x0000, 0x7c00, 0xcc00, 0xcc00, 0xcc00,
				0xcc00, 0xcc00, 0xcc00, 0x7c00, 0x0c00, 0x7800 } }, // g
	{  6,  7, { 0xc000, 0xc000, 0xc000, 0xf800, 0xcc00, 0xcc00, 0xcc00,
				0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x0000, 0x0000 } }, // h
	{  2,  3, { 0xc000, 0xc000, 0x0000, 0xc000, 0xc000, 0xc000, 0xc000,
				0xc000, 0xc000, 0xc000, 0xc000, 0x0000, 0x0000 } }, // i
	{  3,  4, { 0x6000, 0x6000, 0x0000, 0x6000, 0x6000, 0x6000, 0x6000,
				0x6000, 0x6000, 0x6000, 0x6000, 0x6000, 0xc000 } }, // j
	{  6,  7, { 0xc000, 0xc000, 0xc000, 0xcc00, 0xd800, 0xf000, 0xe000,
				0xe000, 0xf000, 0xd800, 0xcc00, 0x0000, 0x0000 } }, // k
	{  2,  3, { 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000,
				0xc000, 0xc000, 0xc000, 0xc000, 0x0000, 0x0000 } }, // l
	{  8,  9, { 0x0000, 0x0000, 0x0000, 0xfe00, 0xdb00, 0xdb00, 0xdb00,
				0xdb00, 0xdb00, 0xdb00, 0xdb00, 0x0000, 0x0000 } }, // m
	{  6,  7, { 0x0000, 0x0000, 0x0000, 0xf800, 0xcc00, 0xcc00, 0xcc00,
				0xcc00, 0xcc00, 0xcc00, 0xcc00, 0x0000, 0x0000 } }, // n
	{  6,  7, { 0x0000, 0x0000, 0x0000, 0x7800, 0xcc00, 0xcc00, 0xcc00,
				0xcc00, 0xcc00, 0xcc00, 0x7800, 0x0000, 0x0000 } }, // o
	{  6,  7, { 0x0000, 0x0000, 0x0000, 0xf800, 0xcc00, 0xcc00, 0xcc00,
				0xcc00, 0xcc00, 0xcc00, 0xf800, 0xc000, 0xc000 } }, // p
	{  6,  7, { 0x0000, 0x0000, 0x0000, 0x7c00, 0xcc00, 0xcc00, 0xcc00,
				0xcc00, 0xcc00, 0xcc00, 0x7c00, 0x0c00, 0x0c00 } }, // q
	{  5,  6, { 0x0000, 0x0000, 0x0000, 0xd800, 0xf800, 0xc000, 0xc000,
				0xc000, 0xc000, 0xc000, 0xc000, 0x0000, 0x0000 } }, // r
	{  5,  6, { 0x0000, 0x0000, 0x0000, 0x7800, 0xc000, 0xe000, 0x7000,
				0x3800, 0x1800, 0x1800, 0xf000, 0x0000, 0x0000 } }, // s
	{  4,  5, { 0x6000, 0x6000, 0x6000, 0xf000, 0x6000, 0x6000, 0x6000,
				0x6000, 0x6000, 0x6000, 0x3000, 0x0000, 0x0000 } }, // t
	{  6,  7, { 0x0000, 0x0000, 0x0000, 0xcc00, 0xcc00, 0xcc00, 0xcc00,
				0xcc00, 0xcc00, 0xcc00, 0x7c00, 0x0000, 0x0000 } }, // u
	{  6,  7, { 0x0000, 0x0000, 0x0000, 0xcc00, 0xcc00, 0xcc00, 0xcc00,
				0x4800, 0x7800, 0x3000, 0x3000, 0x0000, 0x0000 } }, // v
	{  9, 10, { 0x0000, 0x0000, 0x0000, 0xc180, 0xc180, 0xc180, 0x6300,
				0x6b00, 0x7f00, 0x3600, 0x3600, 0x0000, 0x0000 } }, // w
	{  6,  7, { 0x0000, 0x0000, 0x0000, 0xcc00, 0xcc00, 0x7800, 0x3000,
				0x3000, 0x7800, 0xcc00, 0xcc00, 0x0000, 0x0000 } }, // x
	{  6,  7, { 0x0000, 0x0000, 0x0000, 0xcc00, 0xcc00, 0xcc00, 0xcc00,
				0xcc00, 0xcc00, 0xcc00, 0x7c00, 0x0c00, 0x7800 } }, // y
	{  6,  7, { 0x0000, 0x0000, 0x0000, 0xfc00, 0x0c00, 0x1c00, 0x3800,
				0x7000, 0xe000, 0xc000, 0xfc00, 0x0000, 0x0000 } }, // z
	{  3,  4, { 0x2000, 0x6000, 0x4000, 0xc000, 0xc000, 0xc000, 0xc000,
				0xc000, 0xc000, 0xc000, 0x4000, 0x6000, 0x2000 } }, // {
	{  3,  4, { 0x8000, 0xc000, 0x4000, 0x6000, 0x6000, 0x6000, 0x6000,
				0x6000, 0x6000, 0x6000, 0x4000, 0xc000, 0x8000 } }, // |
	{  2,  3, { 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000,
				0xc000, 0xc000, 0xc000, 0xc000, 0xc000, 0xc000 } }, // }
	{  7,  8, { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3200, 0x7e00,
				0x4c00, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 } }  // ~
};

static struct nokia_big_char_wide
nokia_big_wide_data[] =
{
	{ L'€', { 11, 12, { 0x0780, 0x1ce0, 0x3820, 0x3000, 0xffc0, 0x3000, 0xff80,
	        			0x3000, 0x3820, 0x1ce0, 0x0780, 0x0000, 0x0000 } } }, // euro
	{ L'£', {  7,  8, { 0x3800, 0x6c00, 0x6000, 0x6000, 0x6000, 0xf800, 0x6000,
	        			0x6000, 0x6000, 0x6600, 0xfc00, 0x0000, 0x0000 } } }, // pound
	{ L'¥', {  8,  9, { 0xc300, 0xc300, 0x6600, 0x6600, 0xff00, 0x1800, 0xff00,
	        			0x1800, 0x1800, 0x1800, 0x1800, 0x0000, 0x0000 } } }, // yen
	{ L'¤', {  9, 10, { 0x0000, 0x8080, 0x5d00, 0x2200, 0x4100, 0x4100, 0x4100,
	        			0x2200, 0x5d00, 0x8080, 0x0000, 0x0000, 0x0000 } } }, // currency
	{ L'¿', {  6,  7, { 0x3000, 0x3000, 0x0000, 0x3000, 0x3000, 0x6000, 0xc000,
	        			0xc000, 0xc400, 0xc400, 0x7800, 0x0000, 0x0000 } } }, // inverted ?
	{ L'¡', {  2,  3, { 0xc000, 0xc000, 0x0000, 0xc000, 0xc000, 0xc000, 0xc000,
	        			0xc000, 0xc000, 0xc000, 0xc000, 0x0000, 0x0000 } } }, // inverted !
	{ L'§', {  6,  7, { 0x3800, 0x6c00, 0x6c00, 0x6000, 0xf000, 0xd800, 0xcc00,
	        			0x6c00, 0x3c00, 0x1800, 0xd800, 0xd800, 0x7000 } } }  // section
};

static struct nokia_menu_char
nokia_menu_data[] =
{
	{  2,  3, { 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00 } }, // -
	{  1,  2, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x80 } }, // .
	{  3,  4, { 0x20, 0x20, 0x40, 0x40, 0x80, 0x80 } }, // /
	{  5,  6, { 0x70, 0xd8, 0xd8, 0xd8, 0xd8, 0x70 } }, // 0
	{  5,  6, { 0x30, 0x70, 0x30, 0x30, 0x30, 0x30 } }, // 1
	{  5,  6, { 0xf0, 0x18, 0x18, 0x70, 0xc0, 0xf8 } }, // 2
	{  5,  6, { 0xf0, 0x18, 0x70, 0x18, 0x18, 0xf0 } }, // 3
	{  5,  6, { 0x18, 0x38, 0x58, 0xf8, 0x18, 0x18 } }, // 4
	{  5,  6, { 0xf0, 0xc0, 0xf0, 0x18, 0x18, 0xf0 } }, // 5
	{  5,  6, { 0x70, 0xc0, 0xf0, 0xd8, 0xd8, 0x70 } }, // 6
	{  5,  6, { 0xf8, 0x18, 0x30, 0x60, 0x60, 0x60 } }, // 7
	{  5,  6, { 0x70, 0xd8, 0x70, 0xd8, 0xd8, 0x70 } }, // 8
	{  5,  6, { 0x70, 0xd8, 0xd8, 0x78, 0x18, 0x70 } }  // 9
};

static struct nokia_small_char
nokia_small_data[] =
{
	{  3,  4, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } }, // space
	{  1,  2, { 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x80, 0x00 } }, // !
	{  3,  4, { 0xa0, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } }, // "
	{  5,  6, { 0x50, 0x50, 0xf8, 0x50, 0x50, 0xf8, 0x50, 0x50 } }, // #
	{  4,  5, { 0x20, 0x70, 0xa0, 0xe0, 0x70, 0x30, 0xe0, 0x20 } }, // $
	{  4,  5, { 0xd0, 0xd0, 0x20, 0x60, 0x40, 0xb0, 0xb0, 0x00 } }, // %
	{  5,  6, { 0x40, 0xa0, 0xa0, 0x40, 0xa8, 0x90, 0x68, 0x00 } }, // &
	{  1,  2, { 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } }, // '
	{  2,  3, { 0x40, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40 } }, // (
	{  2,  3, { 0x80, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x80 } }, // )
	{  5,  6, { 0x00, 0x50, 0x20, 0xf8, 0x20, 0x50, 0x00, 0x00 } }, // *
	{  5,  6, { 0x00, 0x20, 0x20, 0xf8, 0x20, 0x20, 0x00, 0x00 } }, // +
	{  2,  3, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x80 } }, // ,
	{  4,  5, { 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00 } }, // -
	{  1,  2, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00 } }, // .
	{  3,  4, { 0x20, 0x20, 0x40, 0x40, 0x40, 0x80, 0x80, 0x00 } }, // /
	{  4,  5, { 0x60, 0x90, 0x90, 0x90, 0x90, 0x90, 0x60, 0x00 } }, // 0
	{  4,  5, { 0x20, 0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00 } }, // 1
	{  4,  5, { 0xe0, 0x10, 0x10, 0x60, 0x80, 0x80, 0xf0, 0x00 } }, // 2
	{  4,  5, { 0xe0, 0x10, 0x10, 0x60, 0x10, 0x10, 0xe0, 0x00 } }, // 3
	{  4,  5, { 0x10, 0x30, 0x50, 0x90, 0xf0, 0x10, 0x10, 0x00 } }, // 4
	{  4,  5, { 0xe0, 0x80, 0xe0, 0x10, 0x10, 0x10, 0xe0, 0x00 } }, // 5
	{  4,  5, { 0x60, 0x80, 0xe0, 0x90, 0x90, 0x90, 0x60, 0x00 } }, // 6
	{  4,  5, { 0xf0, 0x10, 0x20, 0x20, 0x40, 0x40, 0x40, 0x00 } }, // 7
	{  4,  5, { 0x60, 0x90, 0x90, 0x60, 0x90, 0x90, 0x60, 0x00 } }, // 8
	{  4,  5, { 0x60, 0x90, 0x90, 0x90, 0x70, 0x10, 0x60, 0x00 } }, // 9
	{  1,  2, { 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00 } }, // :
	{  2,  3, { 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x80 } }, // ;
	{  4,  5, { 0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10, 0x00 } }, // <
	{  4,  5, { 0x00, 0x00, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0x00 } }, // =
	{  4,  5, { 0x80, 0x40, 0x20, 0x10, 0x20, 0x40, 0x80, 0x00 } }, // >
	{  4,  5, { 0xe0, 0x10, 0x20, 0x40, 0x40, 0x00, 0x40, 0x00 } }, // ?
	{  5,  6, { 0x70, 0x88, 0xb8, 0xd8, 0xb0, 0x88, 0x70, 0x00 } }, // @
	{  4,  5, { 0x60, 0x90, 0x90, 0x90, 0xf0, 0x90, 0x90, 0x00 } }, // A
	{  4,  5, { 0xe0, 0x90, 0xe0, 0x90, 0x90, 0x90, 0xe0, 0x00 } }, // B
	{  4,  5, { 0x70, 0x80, 0x80, 0x80, 0x80, 0x80, 0x70, 0x00 } }, // C
	{  4,  5, { 0xe0, 0x90, 0x90, 0x90, 0x90, 0x90, 0xe0, 0x00 } }, // D
	{  4,  5, { 0xf0, 0x80, 0xe0, 0x80, 0x80, 0x80, 0xf0, 0x00 } }, // E
	{  4,  5, { 0xf0, 0x80, 0xe0, 0x80, 0x80, 0x80, 0x80, 0x00 } }, // F
	{  4,  5, { 0x70, 0x80, 0xb0, 0x90, 0x90, 0x90, 0x70, 0x00 } }, // G
	{  4,  5, { 0x90, 0x90, 0xf0, 0x90, 0x90, 0x90, 0x90, 0x00 } }, // H
	{  1,  2, { 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00 } }, // I
	{  3,  4, { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xc0, 0x00 } }, // J
	{  4,  5, { 0x90, 0xa0, 0xc0, 0x80, 0xc0, 0xa0, 0x90, 0x00 } }, // K
	{  4,  5, { 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xf0, 0x00 } }, // L
	{  5,  6, { 0x88, 0xd8, 0xa8, 0xa8, 0x88, 0x88, 0x88, 0x00 } }, // M
	{  5,  6, { 0x88, 0xc8, 0xa8, 0x98, 0x88, 0x88, 0x88, 0x00 } }, // N
	{  5,  6, { 0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00 } }, // O
	{  4,  5, { 0xe0, 0x90, 0x90, 0x90, 0xe0, 0x80, 0x80, 0x00 } }, // P
	{  5,  6, { 0x70, 0x88, 0x88, 0x88, 0x88, 0xa8, 0x70, 0x08 } }, // Q
	{  4,  5, { 0xe0, 0x90, 0x90, 0x90, 0xe0, 0xa0, 0x90, 0x00 } }, // R
	{  4,  5, { 0x70, 0x80, 0x80, 0x60, 0x10, 0x10, 0xe0, 0x00 } }, // S
	{  5,  6, { 0xf8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00 } }, // T
	{  4,  5, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x60, 0x00 } }, // U
	{  5,  6, { 0x88, 0x88, 0x88, 0x50, 0x50, 0x20, 0x20, 0x00 } }, // V
	{  7,  8, { 0x82, 0x82, 0x44, 0x54, 0x54, 0x28, 0x28, 0x00 } }, // W
	{  5,  6, { 0x88, 0x88, 0x50, 0x20, 0x50, 0x88, 0x88, 0x00 } }, // X
	{  5,  6, { 0x88, 0x88, 0x50, 0x20, 0x20, 0x20, 0x20, 0x00 } }, // Y
	{  4,  5, { 0xf0, 0x10, 0x20, 0x40, 0x80, 0x80, 0xf0, 0x00 } }, // Z
	{  2,  3, { 0xc0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xc0 } }, // [
	{  3,  4, { 0x80, 0x80, 0x40, 0x40, 0x40, 0x20, 0x20, 0x00 } }, // backslash
	{  2,  3, { 0xc0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0xc0 } }, // ]
	{  3,  4, { 0x40, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } }, // ^
	{  5,  5, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8 } }, // _
	{  2,  3, { 0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } }, // `
	{  4,  5, { 0x00, 0x00, 0x60, 0x10, 0x70, 0x90, 0x70, 0x00 } }, // a
	{  4,  5, { 0x80, 0x80, 0xe0, 0x90, 0x90, 0x90, 0xe0, 0x00 } }, // b
	{  3,  4, { 0x00, 0x00, 0x60, 0x80, 0x80, 0x80, 0x60, 0x00 } }, // c
	{  4,  5, { 0x10, 0x10, 0x70, 0x90, 0x90, 0x90, 0x70, 0x00 } }, // d
	{  4,  5, { 0x00, 0x00, 0x60, 0x90, 0xf0, 0x80, 0x60, 0x00 } }, // e
	{  2,  3, { 0x40, 0x80, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x00 } }, // f
	{  4,  5, { 0x00, 0x00, 0x70, 0x90, 0x90, 0x70, 0x10, 0x60 } }, // g
	{  4,  5, { 0x80, 0x80, 0xe0, 0x90, 0x90, 0x90, 0x90, 0x00 } }, // h
	{  1,  2, { 0x80, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00 } }, // i
	{  2,  3, { 0x40, 0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x80 } }, // j
	{  4,  5, { 0x80, 0x80, 0x90, 0xa0, 0xc0, 0xa0, 0x90, 0x00 } }, // k
	{  1,  2, { 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00 } }, // l
	{  5,  6, { 0x00, 0x00, 0xf0, 0xa8, 0xa8, 0xa8, 0xa8, 0x00 } }, // m
	{  4,  5, { 0x00, 0x00, 0xe0, 0x90, 0x90, 0x90, 0x90, 0x00 } }, // n
	{  4,  5, { 0x00, 0x00, 0x60, 0x90, 0x90, 0x90, 0x60, 0x00 } }, // o
	{  4,  5, { 0x00, 0x00, 0xe0, 0x90, 0x90, 0xe0, 0x80, 0x80 } }, // p
	{  4,  5, { 0x00, 0x00, 0x70, 0x90, 0x90, 0x70, 0x10, 0x10 } }, // q
	{  3,  4, { 0x00, 0x00, 0xa0, 0xe0, 0x80, 0x80, 0x80, 0x00 } }, // r
	{  3,  4, { 0x00, 0x00, 0x60, 0x80, 0x40, 0x20, 0xc0, 0x00 } }, // s
	{  2,  3, { 0x80, 0x80, 0xc0, 0x80, 0x80, 0x80, 0x40, 0x00 } }, // t
	{  4,  5, { 0x00, 0x00, 0x90, 0x90, 0x90, 0x90, 0x70, 0x00 } }, // u
	{  5,  6, { 0x00, 0x00, 0x88, 0x88, 0x50, 0x50, 0x20, 0x00 } }, // v
	{  5,  6, { 0x00, 0x00, 0x88, 0xa8, 0xa8, 0x50, 0x50, 0x00 } }, // w
	{  4,  5, { 0x00, 0x00, 0x90, 0x90, 0x60, 0x90, 0x90, 0x00 } }, // x
	{  4,  5, { 0x00, 0x00, 0x90, 0x90, 0x90, 0x70, 0x10, 0x60 } }, // y
	{  4,  5, { 0x00, 0x00, 0xf0, 0x20, 0x40, 0x80, 0xf0, 0x00 } }, // z
	{  2,  3, { 0x40, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40 } }, // {
	{  1,  2, { 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80 } }, // |
	{  2,  3, { 0x80, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x80 } }, // }
	{  6,  7, { 0x00, 0x00, 0x00, 0x64, 0x98, 0x00, 0x00, 0x00 } }  // ~
};

static struct nokia_small_char_wide
nokia_small_wide_data[] =
{
	{ L'€', {  6,  7, { 0x00, 0x38, 0x44, 0xf8, 0xf0, 0x44, 0x38, 0x00 } } }, // euro
	{ L'£', {  4,  5, { 0x70, 0x80, 0x80, 0xe0, 0x40, 0x40, 0xf0, 0x00 } } }, // pound
	{ L'¥', {  5,  6, { 0x88, 0x50, 0xf8, 0x20, 0x70, 0x20, 0x20, 0x00 } } }, // yen
	{ L'¤', {  4,  5, { 0x00, 0x90, 0x60, 0x90, 0x90, 0x60, 0x90, 0x00 } } }, // currency
	{ L'¿', {  4,  5, { 0x20, 0x00, 0x20, 0x20, 0x40, 0x80, 0x70, 0x00 } } }, // inverted ?
	{ L'¡', {  1,  2, { 0x80, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00 } } }, // inverted !
	{ L'§', {  3,  4, { 0x40, 0xa0, 0xc0, 0xa0, 0xa0, 0x60, 0xa0, 0x40 } } }, // section
};

static struct nokia_small_char
nokia_small_bold_data[] =
{
	{  3,  4, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } }, // space
	{  2,  3, { 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00, 0xc0, 0x00 } }, // !
	{  3,  4, { 0xa0, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } }, // "
	{  5,  6, { 0x50, 0xf8, 0xf8, 0x50, 0xf8, 0xf8, 0x50, 0x00 } }, // #
	{  5,  6, { 0x50, 0x78, 0xd0, 0xf0, 0x78, 0x58, 0xf0, 0x50 } }, // $
	{  6,  7, { 0xc8, 0xd8, 0x10, 0x30, 0x20, 0x6c, 0x4c, 0x00 } }, // %
	{  6,  7, { 0x70, 0xd8, 0x70, 0xf4, 0xdc, 0xdc, 0x74, 0x00 } }, // &
	{  1,  2, { 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } }, // '
	{  3,  4, { 0x20, 0x40, 0xc0, 0xc0, 0xc0, 0xc0, 0x40, 0x20 } }, // (
	{  3,  4, { 0x80, 0x40, 0x60, 0x60, 0x60, 0x60, 0x40, 0x80 } }, // )
	{  5,  6, { 0x20, 0xa8, 0xf8, 0x70, 0xf8, 0xa8, 0x20, 0x00 } }, // *
	{  5,  6, { 0x00, 0x20, 0x20, 0xf8, 0x20, 0x20, 0x00, 0x00 } }, // +
	{  2,  3, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xc0, 0x80 } }, // ,
	{  4,  5, { 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00 } }, // -
	{  2,  3, { 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x00 } }, // .
	{  3,  4, { 0x20, 0x20, 0x60, 0x40, 0xc0, 0x80, 0x80, 0x00 } }, // /
	{  5,  6, { 0x70, 0xd8, 0xd8, 0xd8, 0xd8, 0xd8, 0x70, 0x00 } }, // 0
	{  5,  6, { 0x30, 0x70, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00 } }, // 1
	{  5,  6, { 0xf0, 0x18, 0x18, 0x70, 0xc0, 0xc0, 0xf8, 0x00 } }, // 2
	{  5,  6, { 0xf0, 0x18, 0x18, 0x70, 0x18, 0x18, 0xf0, 0x00 } }, // 3
	{  5,  6, { 0x18, 0x38, 0x58, 0x98, 0xf8, 0x18, 0x18, 0x00 } }, // 4
	{  5,  6, { 0xf0, 0x80, 0xf0, 0x18, 0x18, 0x18, 0xf0, 0x00 } }, // 5
	{  5,  6, { 0x70, 0xc0, 0xf0, 0xd8, 0xd8, 0xd8, 0x70, 0x00 } }, // 6
	{  5,  6, { 0xf8, 0x18, 0x30, 0x30, 0x60, 0x60, 0x60, 0x00 } }, // 7
	{  5,  6, { 0x70, 0xd8, 0xd8, 0x70, 0xd8, 0xd8, 0x70, 0x00 } }, // 8
	{  5,  6, { 0x70, 0xd8, 0xd8, 0xd8, 0x78, 0x18, 0x70, 0x00 } }, // 9
	{  2,  3, { 0x00, 0x00, 0xc0, 0xc0, 0x00, 0xc0, 0xc0, 0x00 } }, // :
	{  2,  3, { 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x40, 0xc0, 0x80 } }, // ;
	{  4,  5, { 0x10, 0x30, 0x60, 0xc0, 0x60, 0x30, 0x10, 0x00 } }, // <
	{  4,  5, { 0x00, 0x00, 0x00, 0xf0, 0x00, 0xf0, 0x00, 0x00 } }, // =
	{  4,  5, { 0x80, 0xc0, 0x60, 0x30, 0x60, 0xc0, 0x80, 0x00 } }, // >
	{  5,  6, { 0xf0, 0x18, 0x30, 0x60, 0x60, 0x00, 0x60, 0x00 } }, // ?
	{  6,  7, { 0x00, 0x78, 0xcc, 0xfc, 0xdc, 0xfc, 0xc0, 0x78 } }, // @
	{  5,  6, { 0x70, 0xd8, 0xd8, 0xd8, 0xf8, 0xd8, 0xd8, 0x00 } }, // A
	{  5,  6, { 0xf0, 0xd8, 0xf0, 0xd8, 0xd8, 0xd8, 0xf0, 0x00 } }, // B
	{  5,  6, { 0x78, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x78, 0x00 } }, // C
	{  5,  6, { 0xf0, 0xd8, 0xd8, 0xd8, 0xd8, 0xd8, 0xf0, 0x00 } }, // D
	{  5,  6, { 0xf8, 0xc0, 0xf0, 0xc0, 0xc0, 0xc0, 0xf8, 0x00 } }, // E
	{  5,  6, { 0xf8, 0xc0, 0xf0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00 } }, // F
	{  5,  6, { 0x70, 0xc0, 0xc0, 0xd8, 0xd8, 0xd8, 0x78, 0x00 } }, // G
	{  5,  6, { 0xd8, 0xd8, 0xf8, 0xd8, 0xd8, 0xd8, 0xd8, 0x00 } }, // H
	{  2,  3, { 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00 } }, // I
	{  4,  5, { 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0xe0, 0x00 } }, // J
	{  6,  7, { 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0x00 } }, // K
	{  4,  5, { 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf0, 0x00 } }, // L
	{  7,  8, { 0x82, 0xc6, 0xee, 0xfe, 0xd6, 0xc6, 0xc6, 0x00 } }, // M
	{  6,  7, { 0x8c, 0xcc, 0xec, 0xfc, 0xdc, 0xcc, 0xc4, 0x00 } }, // N
	{  6,  7, { 0x78, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0x78, 0x00 } }, // O
	{  5,  6, { 0xf0, 0xd8, 0xd8, 0xd8, 0xf0, 0xc0, 0xc0, 0x00 } }, // P
	{  6,  7, { 0x78, 0xcc, 0xcc, 0xcc, 0xcc, 0xdc, 0x78, 0x0c } }, // Q
	{  5,  6, { 0xf0, 0xd8, 0xd8, 0xd8, 0xf0, 0xd0, 0xd8, 0x00 } }, // R
	{  4,  5, { 0x70, 0xc0, 0xc0, 0x60, 0x30, 0x30, 0xe0, 0x00 } }, // S
	{  6,  7, { 0xfc, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00 } }, // T
	{  5,  6, { 0xd8, 0xd8, 0xd8, 0xd8, 0xd8, 0xd8, 0x70, 0x00 } }, // U
	{  6,  7, { 0xcc, 0xcc, 0xcc, 0x78, 0x78, 0x30, 0x30, 0x00 } }, // V
	{  7,  8, { 0xc6, 0xc6, 0xd6, 0xfe, 0x7c, 0x7c, 0x6c, 0x00 } }, // W
	{  6,  7, { 0xcc, 0xcc, 0x78, 0x30, 0x78, 0xcc, 0xcc, 0x00 } }, // X
	{  6,  7, { 0xcc, 0xcc, 0x78, 0x30, 0x30, 0x30, 0x30, 0x00 } }, // Y
	{  5,  6, { 0xf8, 0x18, 0x38, 0x70, 0xe0, 0xc0, 0xf8, 0x00 } }, // Z
	{  3,  4, { 0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0 } }, // [
	{  3,  4, { 0x80, 0x80, 0xc0, 0x40, 0x60, 0x20, 0x20, 0x00 } }, // backslash
	{  3,  4, { 0xe0, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0xe0 } }, // ]
	{  3,  4, { 0x40, 0xe0, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00 } }, // ^
	{  5,  5, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8 } }, // _
	{  2,  3, { 0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } }, // `
	{  5,  6, { 0x00, 0x00, 0x70, 0x18, 0x78, 0xd8, 0x78, 0x00 } }, // a
	{  5,  6, { 0xc0, 0xc0, 0xf0, 0xd8, 0xd8, 0xd8, 0xf0, 0x00 } }, // b
	{  4,  5, { 0x00, 0x00, 0x70, 0xc0, 0xc0, 0xc0, 0x70, 0x00 } }, // c
	{  5,  6, { 0x18, 0x18, 0x78, 0xd8, 0xd8, 0xd8, 0x78, 0x00 } }, // d
	{  5,  6, { 0x00, 0x00, 0x70, 0xd8, 0xf8, 0xc0, 0x78, 0x00 } }, // e
	{  3,  4, { 0x60, 0xc0, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00 } }, // f
	{  5,  6, { 0x00, 0x00, 0x78, 0xd8, 0xd8, 0x78, 0x18, 0x70 } }, // g
	{  5,  6, { 0xc0, 0xc0, 0xf0, 0xd8, 0xd8, 0xd8, 0xd8, 0x00 } }, // h
	{  2,  3, { 0xc0, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00 } }, // i
	{  3,  4, { 0x60, 0x00, 0x60, 0x60, 0x60, 0x60, 0x60, 0xc0 } }, // j
	{  5,  6, { 0xc0, 0xc0, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0x00 } }, // k
	{  2,  3, { 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00 } }, // l
	{  8,  9, { 0x00, 0x00, 0xfe, 0xdb, 0xdb, 0xdb, 0xdb, 0x00 } }, // m
	{  5,  6, { 0x00, 0x00, 0xf0, 0xd8, 0xd8, 0xd8, 0xd8, 0x00 } }, // n
	{  5,  6, { 0x00, 0x00, 0x70, 0xd8, 0xd8, 0xd8, 0x70, 0x00 } }, // o
	{  5,  6, { 0x00, 0x00, 0xf0, 0xd8, 0xd8, 0xf0, 0xc0, 0xc0 } }, // p
	{  5,  6, { 0x00, 0x00, 0x78, 0xd8, 0xd8, 0x78, 0x18, 0x18 } }, // q
	{  4,  5, { 0x00, 0x00, 0xd0, 0xf0, 0xc0, 0xc0, 0xc0, 0x00 } }, // r
	{  4,  5, { 0x00, 0x00, 0x70, 0xc0, 0xf0, 0x30, 0xe0, 0x00 } }, // s
	{  3,  4, { 0xc0, 0xc0, 0xe0, 0xc0, 0xc0, 0xc0, 0x60, 0x00 } }, // t
	{  5,  6, { 0x00, 0x00, 0xd8, 0xd8, 0xd8, 0xd8, 0x78, 0x00 } }, // u
	{  5,  6, { 0x00, 0x00, 0xd8, 0xd8, 0x70, 0x70, 0x20, 0x00 } }, // v
	{  7,  8, { 0x00, 0x00, 0xc6, 0xd6, 0xd6, 0x7c, 0x6c, 0x00 } }, // w
	{  5,  6, { 0x00, 0x00, 0xd8, 0xd8, 0x70, 0xd8, 0xd8, 0x00 } }, // x
	{  5,  6, { 0x00, 0x00, 0xd8, 0xd8, 0xd8, 0x78, 0x18, 0x70 } }, // y
	{  5,  6, { 0x00, 0x00, 0xf8, 0x30, 0x60, 0xc0, 0xf8, 0x00 } }, // z
	{  3,  4, { 0x20, 0x40, 0xc0, 0xc0, 0xc0, 0xc0, 0x40, 0x20 } }, // {
	{  3,  4, { 0x80, 0x40, 0x60, 0x60, 0x60, 0x60, 0x40, 0x80 } }, // |
	{  2,  3, { 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0 } }, // }
	{  6,  7, { 0x00, 0x00, 0x00, 0x64, 0xfc, 0x98, 0x00, 0x00 } }  // ~
};

struct nokia_small_char_wide
nokia_small_bold_wide_data[] =
{
	{ L'€', {  6,  7, { 0x00, 0x38, 0x44, 0xf8, 0xf0, 0x44, 0x38, 0x00 } } }, // euro
	{ L'£', {  5,  6, { 0x38, 0x60, 0x60, 0x60, 0xf0, 0x60, 0xf8, 0x00 } } }, // pound
	{ L'¥', {  6,  7, { 0xcc, 0x78, 0xfc, 0x30, 0xfc, 0x30, 0x30, 0x00 } } }, // yen
	{ L'¤', {  5,  6, { 0x00, 0x88, 0x70, 0xd8, 0xd8, 0x70, 0x88, 0x00 } } }, // currency
	{ L'¿', {  5,  6, { 0x30, 0x00, 0x30, 0x30, 0x60, 0xc0, 0x78, 0x00 } } }, // inverted ?
	{ L'¡', {  2,  3, { 0xc0, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x00 } } }, // inverted !
	{ L'§', {  4,  5, { 0x60, 0xd0, 0xe0, 0xb0, 0xd0, 0x70, 0xb0, 0x60 } } }, // section
};

#define NOKIA_DEFINE_GETTER(type, name, from, to)                 \
	type *                                                        \
	nokia_get_ ## name ## _char (char ch)                         \
	{                                                             \
		if (ch < from || ch > to)                                 \
			return NULL;                                          \
		return &nokia_ ## name ## _data[ch - from];               \
	}

#define NOKIA_DEFINE_WIDE_GETTER(type, name)                      \
	type *                                                        \
	nokia_get_ ## name ## _char_wide (wchar_t ch)                 \
	{                                                             \
		unsigned i;                                               \
		int c;                                                    \
		for (i = 0; i < sizeof nokia_ ## name ## _wide_data       \
				/ sizeof nokia_ ## name ## _wide_data[0]; i++)    \
			if (nokia_ ## name ## _wide_data[i].code == ch)       \
				return &nokia_ ## name ## _wide_data[i].ch;       \
		c = wctob (ch);                                           \
		return c == EOF ? NULL : nokia_get_ ## name ## _char (c); \
	}

NOKIA_DEFINE_GETTER (struct nokia_menu_char,  menu,       '-', '9')
NOKIA_DEFINE_GETTER (struct nokia_small_char, small,      ' ', '~')
NOKIA_DEFINE_GETTER (struct nokia_small_char, small_bold, ' ', '~')
NOKIA_DEFINE_GETTER (struct nokia_big_char,   big,        ' ', '~')

NOKIA_DEFINE_WIDE_GETTER (struct nokia_small_char, small)
NOKIA_DEFINE_WIDE_GETTER (struct nokia_small_char, small_bold)
NOKIA_DEFINE_WIDE_GETTER (struct nokia_big_char,   big)

#undef NOKIA_DEFINE_GETTER
#undef NOKIA_DEFINE_WIDE_GETTER

