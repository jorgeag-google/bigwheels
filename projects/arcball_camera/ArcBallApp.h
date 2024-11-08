// Copyright 2024 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef ARCBALLAPP_H
#define ARCBALLAPP_H

#include "ppx/ppx.h"
#include "ppx/camera.h"
#include "ppx/graphics_util.h"
using namespace ppx;


class ArcBallApp
    : public ppx::Application
{
public:
    virtual void Config(ppx::ApplicationSettings& settings) override;
    virtual void Setup() override;
    virtual void MouseMove(int32_t x, int32_t y, int32_t dx, int32_t dy, uint32_t buttons) override;
    virtual void Scroll(float dx, float dy) override;
    virtual void Render() override;

private:
    struct PerFrame
    {
        grfx::CommandBufferPtr cmd;
        grfx::SemaphorePtr     imageAcquiredSemaphore;
        grfx::FencePtr         imageAcquiredFence;
        grfx::SemaphorePtr     renderCompleteSemaphore;
        grfx::FencePtr         renderCompleteFence;
    };

    struct Entity
    {
        grfx::MeshPtr          mesh;
        grfx::DescriptorSetPtr descriptorSet;
        grfx::BufferPtr        uniformBuffer;
    };

    std::vector<PerFrame>        mPerFrame;
    grfx::ShaderModulePtr        mVS;
    grfx::ShaderModulePtr        mPS;
    grfx::PipelineInterfacePtr   mPipelineInterface;
    grfx::DescriptorPoolPtr      mDescriptorPool;
    grfx::DescriptorSetLayoutPtr mDescriptorSetLayout;
    grfx::GraphicsPipelinePtr    mTrianglePipeline;
    Entity                       mCube;
    grfx::GraphicsPipelinePtr    mWirePipeline;
    Entity                       mWirePlane;

    ArcballCamera mArcballCamera;

private:
    void SetupEntity(const TriMesh& mesh, const GeometryCreateInfo& createInfo, Entity* pEntity);
    void SetupEntity(const WireMesh& mesh, const GeometryCreateInfo& createInfo, Entity* pEntity);
};

#endif // ARCBALLAPP_H
