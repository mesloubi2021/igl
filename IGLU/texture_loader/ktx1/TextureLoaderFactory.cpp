/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <IGLU/texture_loader/ktx1/TextureLoaderFactory.h>

#include <IGLU/texture_loader/ktx1/Header.h>
#include <IGLU/texture_loader/ktx1/TextureLoader.h>

namespace iglu::textureloader::ktx1 {

uint32_t TextureLoaderFactory::headerLength() const noexcept {
  return kHeaderLength;
}

bool TextureLoaderFactory::isHeaderValidInternal(DataReader reader,
                                                 igl::Result* IGL_NULLABLE
                                                     outResult) const noexcept {
  return TextureLoader::isHeaderValid(reader, outResult);
}

std::unique_ptr<ITextureLoader> TextureLoaderFactory::tryCreateInternal(
    DataReader reader,
    igl::Result* IGL_NULLABLE outResult) const noexcept {
  return TextureLoader::tryCreate(reader, outResult);
}

} // namespace iglu::textureloader::ktx1