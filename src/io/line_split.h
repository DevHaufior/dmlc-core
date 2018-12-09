/*!
 *  Copyright (c) 2015 by Contributors
 * \file line_split.h
 * \brief base class implementation of input splitter
 * \author Tianqi Chen
 */
#ifndef DMLC_IO_LINE_SPLIT_H_
#define DMLC_IO_LINE_SPLIT_H_

#include <dmlc/io.h>
#include <vector>
#include <cstdio>
#include <string>
#include <cstring>
#include "./input_split_base.h"

namespace dmlc {
namespace io {
/*! \brief class that split the files by line */
class LineSplitter : public InputSplitBase {
 public:
  LineSplitter(FileSystem *fs,
               const char *uri,
               unsigned rank,
               unsigned nsplit) {
    this->Init(fs, uri, 1);  // 从文件的角度看，得到了文件的offset, [0, file1size, file1sise+file2size, ...]
    this->ResetPartition(rank, nsplit); /**
    根据上面的文件offset结果，得到rank of nsplit那部分的offset_begin_,offset_end_，并将真实offset_curr_调整至offset_begin_
    **/ 
  }

  virtual bool ExtractNextRecord(Blob *out_rec, Chunk *chunk);
 protected:
  virtual size_t SeekRecordBegin(Stream *fi); 
  virtual const char*
  FindLastRecordBegin(const char *begin, const char *end);
};
}  // namespace io
}  // namespace dmlc
#endif  // DMLC_IO_LINE_SPLIT_H_
