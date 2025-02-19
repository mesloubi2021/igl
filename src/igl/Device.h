/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <igl/Common.h>
#include <igl/DeviceFeatures.h>
#include <igl/IResourceTracker.h>
#include <igl/PlatformDevice.h>
#include <igl/Texture.h>
#include <utility>
#include <vector>

namespace igl {

struct BufferDesc;
struct CommandQueueDesc;
struct ComputePipelineDesc;
struct DepthStencilStateDesc;
struct FramebufferDesc;
struct RenderPipelineDesc;
struct SamplerStateDesc;
struct ShaderLibraryDesc;
struct ShaderModuleDesc;
struct ShaderStagesDesc;
struct TextureDesc;
struct VertexInputStateDesc;
class IBuffer;
class ICommandQueue;
class ICommandBuffer;
class IComputePipelineState;
class IDepthStencilState;
class IDevice;
class IFramebuffer;
class IRenderPipelineState;
class ISamplerState;
class IShaderLibrary;
class IShaderModule;
class IShaderStages;
class ITexture;
class IVertexInputState;

/**
 * @brief Interface to a GPU that is used to draw graphics or do parallel computation.
 */
class IDevice : public ICapabilities {
 public:
  ~IDevice() override = default;

  /**
   * @brief Creates a command queue.
   * @see igl::CommandQueueDesc
   * @param desc Description for the desired resource.
   * @param outResult Pointer to where the result (success, failure, etc) is written. Can be null if
   * no reporting is desired.
   * @return Shared pointer to the created queue.
   */
  virtual std::shared_ptr<ICommandQueue> createCommandQueue(const CommandQueueDesc& desc,
                                                            Result* IGL_NULLABLE outResult) = 0;

  /**
   * @brief Creates a buffer resource.
   * @see igl::BufferDesc
   * @param desc Description for the desired resource.
   * @param outResult Pointer to where the result (success, failure, etc) is written. Can be null if
   * no reporting is desired.
   * @return Unique pointer to the created buffer.
   */
  virtual std::unique_ptr<IBuffer> createBuffer(const BufferDesc& desc,
                                                Result* IGL_NULLABLE outResult) const noexcept = 0;

  /**
   * @brief Creates a depth stencil state.
   * @see igl::DepthStencilStateDesc
   * @param desc Description for the desired resource.
   * @param outResult Pointer to where the result (success, failure, etc) is written. Can be null if
   * no reporting is desired.
   * @return Shared pointer to the created depth stencil state.
   */
  virtual std::shared_ptr<IDepthStencilState> createDepthStencilState(
      const DepthStencilStateDesc& desc,
      Result* IGL_NULLABLE outResult) const = 0;

  /**
   * @brief Creates a sampler state.
   * @see igl::SamplerStateDesc
   * @param desc Description for the desired resource.
   * @param outResult Pointer to where the result (success, failure, etc) is written. Can be null if
   * no reporting is desired.
   * @return Shared pointer to the created sampler state.
   */
  virtual std::shared_ptr<ISamplerState> createSamplerState(const SamplerStateDesc& desc,
                                                            Result* IGL_NULLABLE
                                                                outResult) const = 0;

  /**
   * @brief Creates a texture resource.
   * @see igl::TextureDesc
   * @param desc Description for the desired resource.
   * @param outResult Pointer to where the result (success, failure, etc) is written. Can be null if
   * no reporting is desired.
   * @return Shared pointer to the created texture.
   */
  virtual std::shared_ptr<ITexture> createTexture(const TextureDesc& desc,
                                                  Result* IGL_NULLABLE
                                                      outResult) const noexcept = 0;

  /**
   * @brief Creates a vertex input state.
   * @see igl::VertexInputStateDesc
   * @param desc Description for the desired resource.
   * @param outResult Pointer to where the result (success, failure, etc) is written. Can be null if
   * no reporting is desired.
   * @return Shared pointer to the created vertex input state.
   */
  virtual std::shared_ptr<IVertexInputState> createVertexInputState(
      const VertexInputStateDesc& desc,
      Result* IGL_NULLABLE outResult) const = 0;

  /**
   * @brief Creates a compute pipeline state.
   * @see igl::ComputePipelineDesc
   * @param desc Description for the desired resource.
   * @param outResult Pointer to where the result (success, failure, etc) is written. Can be null if
   * no reporting is desired.
   * @return Shared pointer to the created compute pipeline state.
   */
  virtual std::shared_ptr<IComputePipelineState> createComputePipeline(
      const ComputePipelineDesc& desc,
      Result* IGL_NULLABLE outResult) const = 0;

  /**
   * @brief Creates a render pipeline state.
   * @see igl::RenderPipelineDesc
   * @param desc Description for the desired resource.
   * @param outResult Pointer to where the result (success, failure, etc) is written. Can be null if
   * no reporting is desired.
   * @return Shared pointer to the created render pipeline state.
   */
  virtual std::shared_ptr<IRenderPipelineState> createRenderPipeline(const RenderPipelineDesc& desc,
                                                                     Result* IGL_NULLABLE
                                                                         outResult) const = 0;

  /**
   * @brief Creates a shader module from either source code or pre-compiled data.
   * @see igl::ShaderModuleDesc
   * @param desc Description for the desired resource.
   * @param outResult Pointer to where the result (success, failure, etc) is written. Can be null if
   * no reporting is desired.
   * @return Shared pointer to the created shader module.
   */
  virtual std::shared_ptr<IShaderModule> createShaderModule(const ShaderModuleDesc& desc,
                                                            Result* IGL_NULLABLE
                                                                outResult) const = 0;

  /**
   * @brief Creates a frame buffer object.
   * @see igl::FramebufferDesc
   * @param desc Description for the desired resource.
   * @param outResult Pointer to where the result (success, failure, etc) is written. Can be null if
   * no reporting is desired.
   * @return Shared pointer to the created frame buffer.
   */
  virtual std::shared_ptr<IFramebuffer> createFramebuffer(const FramebufferDesc& desc,
                                                          Result* IGL_NULLABLE outResult) = 0;

  /**
   * @brief Returns a platform-specific device. If the requested device type does not match that of
   * the actual underlying device, then null is returned.
   * @return Pointer to the underlying platform-specific device.
   */
  template<typename T, typename = std::enable_if_t<std::is_base_of<IPlatformDevice, T>::value>>
  T* IGL_NULLABLE getPlatformDevice() noexcept {
    return const_cast<T*>(static_cast<const IDevice*>(this)->getPlatformDevice<T>());
  }

  /**
   * @brief Returns a platform-specific device. If the requested device type does not match that of
   * the actual underlying device, then null is returned.
   * @return Pointer to the underlying platform-specific device.
   */
  template<typename T, typename = std::enable_if_t<std::is_base_of<IPlatformDevice, T>::value>>
  const T* IGL_NULLABLE getPlatformDevice() const noexcept {
    const IPlatformDevice& platformDevice = getPlatformDevice();
    if (platformDevice.isType(T::Type)) {
      return static_cast<const T*>(&platformDevice);
    }
    return nullptr;
  }

  /**
   * @brief Returns a platform-specific device. Returned value should not be held longer than the
   * original `IDevice`.
   * @return Pointer to the underlying platform-specific device.
   */
  IPlatformDevice& getPlatformDevice() noexcept {
    return const_cast<IPlatformDevice&>(static_cast<const IDevice*>(this)->getPlatformDevice());
  }

  /**
   * @brief Returns a platform-specific device. Returned value should not be held longer than the
   * original `IDevice`.
   * @return Pointer to the underlying platform-specific device.
   */
  virtual const IPlatformDevice& getPlatformDevice() const noexcept = 0;

  /**
   * @brief Allow clients to verify that the scope that they are making IGL calls is current and
   * valid.
   * @return Whether or not the current scope is valid.
   */
  virtual bool verifyScope() {
    return defaultVerifyScope();
  }

  /**
   * @brief Returns the actual graphics API backing this IGL device (Metal, OpenGL, etc).
   * @return The type of the underlying backend.
   */
  virtual BackendType getBackendType() const = 0;

  /**
   * @brief Returns the range of Z values in normalized device coordinates considered to be within
   * the viewing volume ie. [-1, 1], [0, 1]. Can be used when a client needs a generic way to adapt
   * how different backends handle NDC.
   * @return The Z value range within the viewing volume.
   */
  virtual NormalizedZRange getNormalizedZRange() const {
    return NormalizedZRange::NegOneToOne;
  }

  /**
   * @brief Returns the number of draw calls made using this device.
   * @return The number of draw calls made so far.
   */
  virtual size_t getCurrentDrawCount() const = 0;

  /**
   * @brief Creates a shader library with one or more shader modules.
   * @see igl::ShaderCompileDesc
   * @param desc The description for the shader library to be created.
   * @param outResult Pointer to where the result (success, failure, etc) is written. Can be null if
   * no reporting is desired.
   * @return Unique pointer to the created shader library.
   */
  virtual std::unique_ptr<IShaderLibrary> createShaderLibrary(const ShaderLibraryDesc& desc,
                                                              Result* IGL_NULLABLE
                                                                  outResult) const = 0;

  /**
   * @brief This is only used by EGL-based clients, e.g. Android, to set the default framebuffer to
   * render to. For all other clients, this is a no-op.
   * @param nativeWindowType Pointer to the native window to be rendered to.
   */
  virtual void updateSurface(void* IGL_NONNULL nativeWindowType);

  /**
   * @brief Creates a shader stages object.
   * @see igl::ShaderStagesDesc
   * @param desc The description for the desired resource.
   * @param outResult Pointer to where the result (success, failure, etc) is written. Can be null if
   * no reporting is desired.
   * @return Unique pointer to the created shader stages object.
   */
  virtual std::unique_ptr<IShaderStages> createShaderStages(const ShaderStagesDesc& desc,
                                                            Result* IGL_NULLABLE
                                                                outResult) const = 0;

 protected:
  virtual void beginScope();
  virtual void endScope();
  TextureDesc sanitize(const TextureDesc& desc) const;
  IDevice() = default;

 public:
  /**
   * @brief Sets the resource tracker used by this device.
   * @see igl::IResourceTracker
   * @param tracker Shared pointer to the tracker.
   */
  void setResourceTracker(std::shared_ptr<IResourceTracker> tracker) noexcept {
    resourceTracker_ = std::move(tracker);
  }

  /**
   * @brief Returns the resource tracker used by this device.
   * @see igl::IResourceTracker
   * @return Shared pointer to the tracker.
   */
  std::shared_ptr<IResourceTracker> getResourceTracker() const noexcept {
    return resourceTracker_;
  }

  /**
   * @brief Returns a backend-specific color for debugging purposes
   *  - OpenGL: Yellow
   *  - Metal: Magenta
   *  - Vulkan: Cyan
   // @fb-only
   */
  Color backendDebugColor() const noexcept;

 private:
  bool defaultVerifyScope();

  int scopeDepth_ = 0;
  std::shared_ptr<IResourceTracker> resourceTracker_;

  friend struct DeviceScope;
};

/**
 * @brief Delineates a scope for making API calls into IGL. Useful for marking diagnostics
 * boundaries.
 * @details To use this, instantiate a DeviceScope at the beginning of a code block that contains
 * a sequence of IGL calls. Typically, you do this at a top-level call such as initialization or a
 * per-frame render function. For clarity, it's best to place this sequence of calls inside braces.
 * For methods that call IGL, it's best to add an assert verifying the scope to ensure that the call
 * is occurring inside a valid DeviceScope.
 */
struct DeviceScope final {
  /**
   * @brief Creates a device scope associated with a given device.
   * @param device The device to be associated with the created scope.
   */
  DeviceScope(IDevice& device);
  ~DeviceScope();

 private:
  IDevice& device_;

  // Prevent heap allocation
  static void* IGL_NONNULL operator new(std::size_t);
  static void* IGL_NONNULL operator new[](std::size_t);
};

} // namespace igl
