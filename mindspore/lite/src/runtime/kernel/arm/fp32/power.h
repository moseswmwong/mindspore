/**
 * Copyright 2020 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_FP32_POWER_H_
#define MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_FP32_POWER_H_

#include <vector>
#include "include/context.h"
#include "src/lite_kernel.h"
#include "src/runtime/kernel/arm/nnacl/power.h"

namespace mindspore::kernel {
class PowerCPUKernel : public LiteKernel {
 public:
  PowerCPUKernel(OpParameter *param, const std::vector<lite::tensor::Tensor *> &inputs,
                 const std::vector<lite::tensor::Tensor *> &outputs, const lite::Context *ctx)
      : LiteKernel(param, inputs, outputs),
        ctx_(ctx),
        thread_count_(ctx->thread_num_),
        scale_(reinterpret_cast<PowerParameter *>(opParameter)->scale_),
        shift_(reinterpret_cast<PowerParameter *>(opParameter)->shift_) {}
  ~PowerCPUKernel() override = default;

  int Init() override;
  int ReSize() override;
  int Run() override;
  int RunImpl(int task_id);

 private:
  const lite::Context *ctx_;
  int thread_count_;
  float scale_;
  float shift_;
};
}  // namespace mindspore::kernel

#endif  // MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_FP32_POWER_H_
