// test reading speed from a InputSplit
#include <cstdlib>
#include <cstdio>
#include <dmlc/io.h>
#include <dmlc/timer.h>
#include "../src/data/libsvm_parser.h"
#include <iostream>


int main(int argc, char *argv[]) {
  if (argc < 5) {
    printf("Usage: <libsvm> partid npart nthread\n");
    return 0;
  }
  using namespace dmlc;
  InputSplit *split = InputSplit::Create(argv[1],
                                         atoi(argv[2]),
                                         atoi(argv[3]),
                                         "text");
  // 确定了partid of npart那部分整块数据的offset_begin_和offset_end_并调整offset_current_为offset_begin_                                    
  int nthread = atoi(argv[4]);

  data::LibSVMParser<unsigned> parser(split, nthread);
  while (parser.Next()) {
    auto batch = parser.Value();
    std::cout<<batch.size<<std::endl;
    // for (size_t i = batch.offset[0]; i < batch.offset[batch.size]; ++i) {
    //   auto index = batch.index[i];
    //   auto fvalue = batch.value == nullptr ? 1.0f : batch.value[i];
    //   std::cout<<index<<":"<<fvalue<<std::endl;
    // }
    std::cout<<batch.offset[0]<<std::endl;
    for (size_t i = batch.offset[0]; i < batch.offset[1]; i++) {
        auto fvalue = batch.value == nullptr ? 1.0f : batch.value[i];
        std::cout<<batch.index[i]<<":"<<fvalue<<" ";
    }
    std::cout<<std::endl;
  }
  return 0;
}
// 0 1:1 9:1 19:1 21:1 24:1 34:1 36:1 39:1 42:1 53:1 56:1 65:1 69:1 77:1 86:1 88:1 92:1 95:1 102:1 106:1 117:1 122:1