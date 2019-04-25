/*!
 *  Copyright (c) 2019 by Contributors if not otherwise specified
 * \file cu_decoder.h
 * \brief NVCUVID based decoder
 */

#ifndef DECORD_VIDEO_NVCODEC_CU_DECODER_H_
#define DECORD_VIDEO_NVCODEC_CU_DECODER_H_

#include <iostream>
#include <memory>

#include <cuda.h>
#include <cuda_runtime.h>


namespace decord {
namespace cuda {
#ifdef __cuda_cuda_h__
inline bool CHECK(CUresult e, int iLine, const char *szFile) {
    if (e != CUDA_SUCCESS) {
        const char* err;
        cuGetErrorString(e, &err);
        std::cerr << "CUDA error " << e << " at line " << iLine << " in file " << szFile
                   << ": " << err << std::endl;
        return false;
    }
    return true;
}
#endif

#ifdef __CUDA_RUNTIME_H__
inline bool CHECK(cudaError_t e, int iLine, const char *szFile) {
    if (e != cudaSuccess) {
        std::cerr << "CUDA runtime error " << e << " at line " << iLine
                   << " in file " << szFile
                   << ": " << cudaGetErrorString(e)
                   << std::endl;
        return false;
    }
    return true;
}
#endif

#define CHECK_CUDA_CALL(call) CHECK(call, __LINE__, __FILE__)
}  // namespace decord
}  // namespace cuda
#endif

