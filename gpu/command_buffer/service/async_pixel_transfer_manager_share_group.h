// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GPU_COMMAND_BUFFER_SERVICE_ASYNC_PIXEL_TRANSFER_MANAGER_SHARE_GROUP_H_
#define GPU_COMMAND_BUFFER_SERVICE_ASYNC_PIXEL_TRANSFER_MANAGER_SHARE_GROUP_H_

#include "gpu/command_buffer/service/async_pixel_transfer_manager.h"

#include "base/memory/ref_counted.h"

namespace gfx {
class GLContext;
}

namespace gpu {
class AsyncPixelTransferDelegateShareGroup;
class AsyncPixelTransferUploadStats;

class AsyncPixelTransferManagerShareGroup : public AsyncPixelTransferManager {
 public:
  explicit AsyncPixelTransferManagerShareGroup(gfx::GLContext* context);
  virtual ~AsyncPixelTransferManagerShareGroup();

  // AsyncPixelTransferManager implementation:
  virtual void BindCompletedAsyncTransfers() OVERRIDE;
  virtual void AsyncNotifyCompletion(
      const AsyncMemoryParams& mem_params,
      const CompletionCallback& callback) OVERRIDE;
  virtual uint32 GetTextureUploadCount() OVERRIDE;
  virtual base::TimeDelta GetTotalTextureUploadTime() OVERRIDE;
  virtual void ProcessMorePendingTransfers() OVERRIDE;
  virtual bool NeedsProcessMorePendingTransfers() OVERRIDE;

  // State shared between Managers and Delegates.
  struct SharedState {
    SharedState();
    ~SharedState();

    scoped_refptr<AsyncPixelTransferUploadStats> texture_upload_stats;
    typedef std::list<base::WeakPtr<AsyncPixelTransferDelegateShareGroup> >
        TransferQueue;
    TransferQueue pending_allocations;
  };

 private:
  // AsyncPixelTransferManager implementation:
  virtual AsyncPixelTransferDelegate* CreatePixelTransferDelegateImpl(
      gles2::TextureRef* ref,
      const AsyncTexImage2DParams& define_params) OVERRIDE;

  SharedState shared_state_;

  DISALLOW_COPY_AND_ASSIGN(AsyncPixelTransferManagerShareGroup);
};

}  // namespace gpu

#endif  // GPU_COMMAND_BUFFER_SERVICE_ASYNC_PIXEL_TRANSFER_MANAGER_SHARE_GROUP_H_