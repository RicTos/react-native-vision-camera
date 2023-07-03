//
// Created by Marc Rousavy on 05.05.23.
//

#include "SkiaPreviewSurface.h"

#include <android/log.h>

#include "SkImage.h"
#include "SkSurface.h"
#include <android/native_window.h>
#include <android/native_window_jni.h>

namespace vision {

using TSelf = jni::local_ref<SkiaPreviewSurface::jhybriddata>;

SkiaPreviewSurface::SkiaPreviewSurface(jni::alias_ref<SkiaPreviewSurface::jhybridobject> jThis,
                                       jint inputWidth, jint inputHeight,
                                       jni::alias_ref<jobject> outputSurface)
        : _javaPart(jni::make_global(jThis)) {
    __android_log_print(ANDROID_LOG_INFO, TAG, "Creating SkiaPreviewSurface...");

    // Create OpenGL context
    _context = GrDirectContext::MakeGL();
    if (_context == nullptr) {
        throw std::runtime_error("Failed to create an OpenGL GrContext!");
    }

    // Create Input Surface
    auto imageInfo = SkImageInfo:: Make(inputWidth,
                                        inputHeight,
                                        SkColorType::kBGRA_8888_SkColorType,
                                        SkAlphaType::kOpaque_SkAlphaType);
    _inputSurface = SkSurface::MakeRenderTarget(_context.get(),
                                                SkBudgeted::kNo,
                                                imageInfo);
    if (!_inputSurface) {
        throw std::runtime_error("Failed to create input Skia Surface!");
    }
}

TSelf SkiaPreviewSurface::initHybrid(jni::alias_ref<jhybridobject> jThis,
                                     jint inputWidth, jint inputHeight,
                                     jni::alias_ref<jobject> outputSurface) {
    return makeCxxInstance(jThis, inputWidth, inputHeight, outputSurface);
}

void SkiaPreviewSurface::registerNatives() {
    registerHybrid({
       makeNativeMethod("initHybrid", SkiaPreviewSurface::initHybrid),
       makeNativeMethod("getInputSurfaceTextureId", SkiaPreviewSurface::getInputSurfaceTextureId),
       makeNativeMethod("setOutputSize", SkiaPreviewSurface::setOutputSize),
    });
}

jint SkiaPreviewSurface::getInputSurfaceTextureId() {
    auto renderTarget = _inputSurface->getBackendRenderTarget(SkSurface::kFlushWrite_BackendHandleAccess);
    if (!renderTarget.isValid()) {
        throw std::runtime_error("Tried to get texture ID of an invalid input surface!");
    }
    GrGLFramebufferInfo info;
    info.fFBOID = -1;
    renderTarget.getGLFramebufferInfo(&info);
    if (info.fFBOID == -1) {
        throw std::runtime_error("Input Surface has invalid backend render target ID (-1)!");
    }
    return static_cast<jint>(info.fFBOID);
}

void SkiaPreviewSurface::setOutputSize(jint width, jint height) {
    // TODO: Set output size
}


} // namespace vision
