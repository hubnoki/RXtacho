/*
 * lowlvl.c
 *
 *  Created on: 2015/09/10
 *      Author: akihiro
 */

#include "hardware_lib.h"
#include "uart.h"

#include <stdio.h>

// functions and defines for STANDARD IO

#include <string.h>
/* ファイル番号 */
#define STDIN 0 /* 標準入力( コンソール)*/
#define STDOUT 1 /* 標準出力( コンソール)*/
#define STDERR 2 /* 標準エラー出力 ( コンソール)*/
#define FLMIN 0 /* 最小のファイル番号*/
#define FLMAX 3 /* ファイル数の最大値*/

#define _MOPENR 0x1
#define _MOPENW 0x2
#define _MOPENA 0x4
#define _MTRUNC 0x8
#define _MCREAT 0x10
#define _MBIN 0x20
#define _MEXCL 0x40
#define _MALBUF 0x40
#define _MALFIL 0x80
#define _MEOF 0x100
#define _MERR 0x200
#define _MLBF 0x400
#define _MNBF 0x800
#define _MREAD 0x1000
#define _MWRITE 0x2000
#define _MBYTE 0x4000
#define _MWIDE 0x8000

/* ファイルのフラグ */
#define O_RDONLY 0x0001
#define O_WRONLY 0x0002
#define O_RDWR 0x0004
#define O_CREAT 0x0008
#define O_TRUNC 0x0010
#define O_APPEND 0x0020
/* 特殊文字コード */
#define CR 0x0d /* 復帰*/
#define LF 0x0a /* 改行*/

char flmod[FLMAX]; /* オープンしたファイルのモード設定場所 */

/******************************************************************************/
/* open: ファイルのオープン */
/* リターン値：ファイル番号( 成功) */
/* -1 ( 失敗) */
/******************************************************************************/
long _open(const char *name, long mode, long flg)
{
	/* ファイル名に従ってモードをチェックし、ファイル番号を返す */
	if (strcmp(name,"stdin")==0) { /* 標準入力ファイル */
		if ((mode&O_RDONLY)==0) {
			return (-1);
		}
		flmod[STDIN]=mode;
		return (STDIN);
	}
	else if (strcmp(name,"stdout")==0) { /* 標準出力ファイル */
		if ((mode&O_WRONLY)==0) {
			return (-1);
		}
		flmod[STDOUT]=mode;
		return (STDOUT);
	}
	else if (strcmp(name,"stderr")==0){ /* 標準エラー出力ファイル */
		if ((mode&O_WRONLY)==0) {
			return (-1);
		}
		flmod[STDERR]=mode;
		return (STDERR);
	}
	else {
		return (-1); /* エラー */
	}
}

/******************************************************************************/
/* close: ファイルのクローズ */
/* リターン値：0 ( 成功) */
/* -1 ( 失敗) */
/******************************************************************************/
long _close(long fileno)
{
	if (fileno<FLMIN || FLMAX<fileno) { /* ファイル番号の範囲チェック */
		return -1;
	}
	flmod[fileno]=0; /* ファイルのモードリセット */
	return 0;
}

/******************************************************************************/
/* read: データの読み込み */
/* リターン値：実際に読み込んだ文字数( 成功) */
/* -1 ( 失敗) */
/******************************************************************************/
long _read(long fileno, /* ファイル番号 */
		unsigned char *buf, /* 転送先バッファアドレス */
		long count) /* 読み込み文字数 */
{
	unsigned long i;

	/* ファイル名に従ってモードをチェックし、一文字づつ入力してバッファに格納 */
//	if ( (flmod[fileno] & O_RDONLY) || (flmod[fileno] & O_RDWR) ) {
		for (i = count; i > 0; i--) {
			*buf = uart_getc();
			if (*buf == CR) { /* 改行文字の置き換え */
				*buf = LF;
			}
			buf++;
		}
		return count;
//	}
//	else {
//		return -1;
//	}

}

/******************************************************************************/
/* write: データの書き出し */
/* リターン値：実際に書き出した文字数( 成功) */
/* -1 ( 失敗) */
/******************************************************************************/
long _write(long fileno, /* ファイル番号 */
		const unsigned char *buf, /* 転送元バッファアドレス */
		long count) /* 書き出し文字数 */
{
	unsigned long i;
	unsigned char c;

	/* ファイル名に従ってモードをチェックし、一文字づつ出力 */
//	if ( (flmod[fileno] & O_WRONLY) || (flmod[fileno] & O_RDWR) ) {
		for (i = count; i > 0; i--) {
			c=*buf++;
			uart_putc(c);
		}

		return count;

//	}
//	else {
//		return -1;
//	}

}

/******************************************************************************/
/* lseek: ファイルの読み込み／書き出し位置の設定 */
/* リターン値：読み込み／書き出し位置のファイル先頭からのオフセット ( 成功) */
/* -1 ( 失敗) */
/* ( コンソール入出力では、lseek はサポートしていません) */
/******************************************************************************/
//long lseek(long fileno, /* ファイル番号 */
//		long offset, /* 読み込み／書き出し位置 */
//		long base) /* オフセットの起点 */
//{
//	return -1;
//}

//
//FILE _Stdin, _Stdout, _Stderr;
//
//void _INIT_IOLIB(void)
//{
//	// need to use freopen() because stdin, stdout, stderr are already allocated
//	if( freopen( "stdin", "r", stdin ) == NULL )
//		stdin->_Mode = 0xffff;
//	stdin->_Mode = _MOPENR;
//	stdin->_Mode |= _MNBF;
//	stdin->_Bend = stdin->_Buf + 1;
//	if( freopen( "stdout", "w", stdout ) == NULL )
//		stdout->_Mode = 0xffff;
//	stdout->_Mode |= _MNBF;
//	stdout->_Bend = stdout->_Buf + 1;
//	if( freopen( "stderr", "w", stderr ) == NULL )
//		stderr->_Mode = 0xffff;
//	stderr->_Mode |= _MNBF;
//	stderr->_Bend = stderr->_Buf + 1;
//
////	freopen("stdin", "r", stdin);
////	freopen("stdout", "w", stdout);
////	freopen("stderr", "w", stderr);
//}
//
//void _CLOSEALL(void)
//{
//
//}
//
//#include "typedefine.h"
//_SBYTE *_s1ptr;		// for strtok()
//
//

// You must include errno.h, then disable the macro, like this:
#include <errno.h>
#undef errno
extern int errno;


//// environ ////
// A pointer to a list of environment variables and their values.
// For a minimal environment, this empty list is adequate:
char *__env[1] = { 0 };
char **environ = __env;

//// execve ////
// Transfer control to a new process. Minimal implementation (for a system without processes):
int _execve(char *name, char **argv, char **env) {
  errno = ENOMEM;
  return -1;
}

//// fork ////
// Create a new process. Minimal implementation (for a system without processes):
int _fork(void) {
  errno = EAGAIN;
  return -1;
}

//// fstat ////
// Status of an open file. For consistency with other minimal implementations in these examples,
// all files are regarded as character special devices.
// The sys/stat.h header file required is distributed in the include subdirectory for this C library.
typedef unsigned int wint_t;
#include <sys/stat.h>
int _fstat(int file, struct stat *st) {
  st->st_mode = S_IFCHR;
  return 0;
}


//// getpid ////
// Process-ID; this is sometimes used to generate strings unlikely to conflict with other processes.
// Minimal implementation, for a system without processes:
int _getpid(void) {
  return 1;
}

//// isatty ////
// Query whether output stream is a terminal.
// For consistency with the other minimal implementations, which only support output to stdout,
// this minimal implementation is suggested:
int _isatty(int file) {
  return 1;
}

//// kill ////
//  Send a signal. Minimal implementation:
int _kill(int pid, int sig) {
  errno = EINVAL;
  return -1;
}

//// link ////
// Establish a new name for an existing file. Minimal implementation:
int _link(char *old, char *new) {
  errno = EMLINK;
  return -1;
}

////// stat ////
//// Status of a file (by name). Minimal implementation:
//int stat(const char *file, struct stat *st) {
//  st->st_mode = S_IFCHR;
//  return 0;
//}

////// times ////
//// Timing information for current process. Minimal implementation:
//int times(struct tms *buf) {
//  return -1;
//}


//// unlink ////
// Remove a file’s directory entry. Minimal implementation:
int _unlink(char *name) {
  errno = ENOENT;
  return -1;
}

//// wait ////
// Wait for a child process. Minimal implementation:
int _wait(int *status) {
  errno = ECHILD;
  return -1;
}


