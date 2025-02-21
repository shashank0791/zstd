/*
 * Copyright (c) 2016-present, Yann Collet, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under both the BSD-style license (found in the
 * LICENSE file in the root directory of this source tree) and the GPLv2 (found
 * in the COPYING file in the root directory of this source tree).
 * You may select, at your option, one of the above-listed licenses.
 */


#ifndef FILEIO_H_23981798732
#define FILEIO_H_23981798732

#define ZSTD_STATIC_LINKING_ONLY   /* ZSTD_compressionParameters */
#include "zstd.h"                  /* ZSTD_* */

#if defined (__cplusplus)
extern "C" {
#endif


/* *************************************
*  Special i/o constants
**************************************/
#define stdinmark  "/*stdin*\\"
#define stdoutmark "/*stdout*\\"
#ifdef _WIN32
#  define nulmark "NUL"
#else
#  define nulmark "/dev/null"
#endif

/**
 * We test whether the extension we found starts with 't', and if so, we append
 * ".tar" to the end of the output name.
 */
#define LZMA_EXTENSION  ".lzma"
#define XZ_EXTENSION    ".xz"
#define TXZ_EXTENSION   ".txz"

#define GZ_EXTENSION    ".gz"
#define TGZ_EXTENSION   ".tgz"

#define ZSTD_EXTENSION  ".zst"
#define TZSTD_EXTENSION ".tzst"

#define LZ4_EXTENSION   ".lz4"
#define TLZ4_EXTENSION  ".tlz4"


/*-*************************************
*  Types
***************************************/
typedef enum { FIO_zstdCompression, FIO_gzipCompression, FIO_xzCompression, FIO_lzmaCompression, FIO_lz4Compression } FIO_compressionType_t;

typedef struct FIO_prefs_s FIO_prefs_t;

FIO_prefs_t* FIO_createPreferences(void);
void FIO_freePreferences(FIO_prefs_t* const prefs);

typedef struct FIO_display_prefs_s FIO_display_prefs_t;

/*-*************************************
*  Parameters
***************************************/
void FIO_setCompressionType(FIO_prefs_t* const prefs, FIO_compressionType_t compressionType);
void FIO_overwriteMode(FIO_prefs_t* const prefs);
void FIO_setAdaptiveMode(FIO_prefs_t* const prefs, unsigned adapt);
void FIO_setAdaptMin(FIO_prefs_t* const prefs, int minCLevel);
void FIO_setAdaptMax(FIO_prefs_t* const prefs, int maxCLevel);
void FIO_setBlockSize(FIO_prefs_t* const prefs, int blockSize);
void FIO_setChecksumFlag(FIO_prefs_t* const prefs, int checksumFlag);
void FIO_setDictIDFlag(FIO_prefs_t* const prefs, int dictIDFlag);
void FIO_setLdmBucketSizeLog(FIO_prefs_t* const prefs, int ldmBucketSizeLog);
void FIO_setLdmFlag(FIO_prefs_t* const prefs, unsigned ldmFlag);
void FIO_setLdmHashRateLog(FIO_prefs_t* const prefs, int ldmHashRateLog);
void FIO_setLdmHashLog(FIO_prefs_t* const prefs, int ldmHashLog);
void FIO_setLdmMinMatch(FIO_prefs_t* const prefs, int ldmMinMatch);
void FIO_setMemLimit(FIO_prefs_t* const prefs, unsigned memLimit);
void FIO_setNbWorkers(FIO_prefs_t* const prefs, int nbWorkers);
void FIO_setOverlapLog(FIO_prefs_t* const prefs, int overlapLog);
void FIO_setRemoveSrcFile(FIO_prefs_t* const prefs, unsigned flag);
void FIO_setSparseWrite(FIO_prefs_t* const prefs, unsigned sparse);  /**< 0: no sparse; 1: disable on stdout; 2: always enabled */
void FIO_setRsyncable(FIO_prefs_t* const prefs, int rsyncable);
void FIO_setStreamSrcSize(FIO_prefs_t* const prefs, size_t streamSrcSize);
void FIO_setTargetCBlockSize(FIO_prefs_t* const prefs, size_t targetCBlockSize);
void FIO_setSrcSizeHint(FIO_prefs_t* const prefs, size_t srcSizeHint);
void FIO_setTestMode(FIO_prefs_t* const prefs, int testMode);
void FIO_setLiteralCompressionMode(
        FIO_prefs_t* const prefs,
        ZSTD_literalCompressionMode_e mode);

void FIO_setNoProgress(unsigned noProgress);
void FIO_setNotificationLevel(int level);

/*-*************************************
*  Single File functions
***************************************/
/** FIO_compressFilename() :
 * @return : 0 == ok;  1 == pb with src file. */
int FIO_compressFilename (FIO_prefs_t* const prefs,
                          const char* outfilename, const char* infilename,
                          const char* dictFileName, int compressionLevel,
                          ZSTD_compressionParameters comprParams);

/** FIO_decompressFilename() :
 * @return : 0 == ok;  1 == pb with src file. */
int FIO_decompressFilename (FIO_prefs_t* const prefs,
                            const char* outfilename, const char* infilename, const char* dictFileName);

int FIO_listMultipleFiles(unsigned numFiles, const char** filenameTable, int displayLevel);


/*-*************************************
*  Multiple File functions
***************************************/
/** FIO_compressMultipleFilenames() :
 * @return : nb of missing files */
int FIO_compressMultipleFilenames(FIO_prefs_t* const prefs,
                                  const char** inFileNamesTable, unsigned nbFiles,
                                  const char* outDirName,
                                  const char* outFileName, const char* suffix,
                                  const char* dictFileName, int compressionLevel,
                                  ZSTD_compressionParameters comprParams);

/** FIO_decompressMultipleFilenames() :
 * @return : nb of missing or skipped files */
int FIO_decompressMultipleFilenames(FIO_prefs_t* const prefs,
                                    const char** srcNamesTable, unsigned nbFiles,
                                    const char* outDirName,
                                    const char* outFileName,
                                    const char* dictFileName);

/* FIO_checkFilenameCollisions() :
 * Checks for and warns if there are any files that would have the same output path
 */
int FIO_checkFilenameCollisions(const char** filenameTable, unsigned nbFiles);



/*-*************************************
*  Advanced stuff (should actually be hosted elsewhere)
***************************************/

/* custom crash signal handler */
void FIO_addAbortHandler(void);



#if defined (__cplusplus)
}
#endif

#endif  /* FILEIO_H_23981798732 */
