/*!
 *  Copyright (c) 2019 by Contributors if not otherwise specified
 * \file cu_stream.cc
 * \brief CUDA stream
 */

#include "cu_stream.h"

namespace decord {
namespace cuda {
CUStream::CUStream(int device_id, bool default_stream) : created_{false}, stream_{0} {
    if (!default_stream) {
        int orig_device;
        cudaGetDevice(&orig_device);
        auto set_device = false;
        if (device_id >= 0 && orig_device != device_id) {
            set_device = true;
            cudaSetDevice(device_id);
        }
        cucall(cudaStreamCreateWithFlags(&stream_, cudaStreamNonBlocking));
        created_ = true;
        if (set_device) {
            cucall(cudaSetDevice(orig_device));
        }
    }
}

CUStream::~CUStream() {
    if (created_) {
        cucall(cudaStreamDestroy(stream_));
    }
}

CUStream::CUStream(CUStream&& other)
    : created_{other.created_}, stream_{other.stream_}
{
    other.stream_ = 0;
    other.created_ = false;
}

CUStream& CUStream::operator=(CUStream&& other) {
    stream_ = other.stream_;
    created_ = other.created_;
    other.stream_ = 0;
    other.created_ = false;
    return *this;
}

CUStream::operator cudaStream_t() {
    return stream_;
}
}  // namespace cuda
}  // namespace decord