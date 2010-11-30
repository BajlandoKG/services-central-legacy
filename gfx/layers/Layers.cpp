/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 * vim: sw=2 ts=8 et :
 */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Mozilla Code.
 *
 * The Initial Developer of the Original Code is
 *   The Mozilla Foundation
 * Portions created by the Initial Developer are Copyright (C) 2010
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Chris Jones <jones.chris.g@gmail.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifdef MOZ_IPC
# include "mozilla/layers/ShadowLayers.h"
#endif  // MOZ_IPC

#include "ImageLayers.h"
#include "Layers.h"
#include "gfxPlatform.h"

using namespace mozilla::layers;
 
#ifdef MOZ_LAYERS_HAVE_LOG
FILE*
FILEOrDefault(FILE* aFile)
{
  return aFile ? aFile : stderr;
}
#endif // MOZ_LAYERS_HAVE_LOG

namespace {

// XXX pretty general utilities, could centralize

nsACString&
AppendToString(nsACString& s, const gfxPattern::GraphicsFilter& f,
               const char* pfx="", const char* sfx="")
{
  s += pfx;
  switch (f) {
  case gfxPattern::FILTER_FAST:      s += "fast"; break;
  case gfxPattern::FILTER_GOOD:      s += "good"; break;
  case gfxPattern::FILTER_BEST:      s += "best"; break;
  case gfxPattern::FILTER_NEAREST:   s += "nearest"; break;
  case gfxPattern::FILTER_BILINEAR:  s += "bilinear"; break;
  case gfxPattern::FILTER_GAUSSIAN:  s += "gaussian"; break;
  default:
    NS_ERROR("unknown filter type");
    s += "???";
  }
  return s += sfx;
}

nsACString&
AppendToString(nsACString& s, const gfxRGBA& c,
               const char* pfx="", const char* sfx="")
{
  s += pfx;
  s += nsPrintfCString(
    128, "rgba(%d, %d, %d, %g)",
    PRUint8(c.r*255.0), PRUint8(c.g*255.0), PRUint8(c.b*255.0), c.a);
  return s += sfx;
}

nsACString&
AppendToString(nsACString& s, const gfx3DMatrix& m,
               const char* pfx="", const char* sfx="")
{
  s += pfx;
  if (m.IsIdentity())
    s += "[ I ]";
  else {
    gfxMatrix matrix;
    if (m.Is2D(&matrix)) {
      s += nsPrintfCString(
        96, "[ %g %g; %g %g; %g %g; ]",
        matrix.xx, matrix.yx, matrix.xy, matrix.yy, matrix.x0, matrix.y0);
    } else {
      s += nsPrintfCString(
        256, "[ %g %g %g %g; %g %g %g %g; %g %g %g %g; %g %g %g %g; ]",
        m._11, m._12, m._13, m._14,
        m._21, m._22, m._23, m._24,
        m._31, m._32, m._33, m._34,
        m._41, m._42, m._43, m._44);
    }
  }
  return s += sfx;
}

nsACString&
AppendToString(nsACString& s, const nsIntPoint& p,
               const char* pfx="", const char* sfx="")
{
  s += pfx;
  s += nsPrintfCString(128, "(x=%d, y=%d)", p.x, p.y);
  return s += sfx;
}

nsACString&
AppendToString(nsACString& s, const nsIntRect& r,
               const char* pfx="", const char* sfx="")
{
  s += pfx;
  s += nsPrintfCString(
    256, "(x=%d, y=%d, w=%d, h=%d)",
    r.x, r.y, r.width, r.height);
  return s += sfx;
}

nsACString&
AppendToString(nsACString& s, const nsIntRegion& r,
               const char* pfx="", const char* sfx="")
{
  s += pfx;

  nsIntRegionRectIterator it(r);
  s += "< ";
  while (const nsIntRect* sr = it.Next())
    AppendToString(s, *sr) += "; ";
  s += ">";

  return s += sfx;
}

nsACString&
AppendToString(nsACString& s, const nsIntSize& sz,
               const char* pfx="", const char* sfx="")
{
  s += pfx;
  s += nsPrintfCString(128, "(w=%d, h=%d)", sz.width, sz.height);
  return s += sfx;
}

nsACString&
AppendToString(nsACString& s, const FrameMetrics& m,
               const char* pfx="", const char* sfx="")
{
  s += pfx;
  AppendToString(s, m.mViewportSize, "{ viewport=");
  AppendToString(s, m.mViewportScrollOffset, " viewportScroll=");
  AppendToString(s, m.mDisplayPort, " displayport=", " }");
  return s += sfx;
}

} // namespace <anon>

namespace mozilla {
namespace layers {

//--------------------------------------------------
// LayerManager
already_AddRefed<gfxASurface>
LayerManager::CreateOptimalSurface(const gfxIntSize &aSize,
                                   gfxASurface::gfxImageFormat aFormat)
{
  return gfxPlatform::GetPlatform()->
    CreateOffscreenSurface(aSize, gfxASurface::ContentFromFormat(aFormat));
}

//--------------------------------------------------
// Layer

PRBool
Layer::CanUseOpaqueSurface()
{
  // If the visible content in the layer is opaque, there is no need
  // for an alpha channel.
  if (GetContentFlags() & CONTENT_OPAQUE)
    return PR_TRUE;
  // Also, if this layer is the bottommost layer in a container which
  // doesn't need an alpha channel, we can use an opaque surface for this
  // layer too. Any transparent areas must be covered by something else
  // in the container.
  ContainerLayer* parent = GetParent();
  return parent && parent->GetFirstChild() == this &&
    parent->CanUseOpaqueSurface();
}

#ifdef MOZ_IPC
// NB: eventually these methods will be defined unconditionally, and
// can be moved into Layers.h
const nsIntRect*
Layer::GetEffectiveClipRect()
{
  if (ShadowLayer* shadow = AsShadowLayer()) {
    return shadow->GetShadowClipRect();
  }
  return GetClipRect();
}

const nsIntRegion&
Layer::GetEffectiveVisibleRegion()
{
  if (ShadowLayer* shadow = AsShadowLayer()) {
    return shadow->GetShadowVisibleRegion();
  }
  return GetVisibleRegion();
}

#else

const nsIntRect* Layer::GetEffectiveClipRect() { return GetClipRect(); }
const nsIntRegion& Layer::GetEffectiveVisibleRegion() { return GetVisibleRegion(); }

#endif  // MOZ_IPC

gfx3DMatrix
Layer::SnapTransform(const gfx3DMatrix& aTransform,
                     const gfxRect& aSnapRect,
                     gfxMatrix* aResidualTransform)
{
  if (aResidualTransform) {
    *aResidualTransform = gfxMatrix();
  }

  gfxMatrix matrix2D;
  gfx3DMatrix result;
  if (mManager->IsSnappingEffectiveTransforms() &&
      aTransform.Is2D(&matrix2D) &&
      matrix2D.HasNonIntegerTranslation() &&
      !matrix2D.IsSingular() &&
      !matrix2D.HasNonAxisAlignedTransform()) {
    gfxMatrix snappedMatrix;
    gfxPoint topLeft = matrix2D.Transform(aSnapRect.TopLeft());
    topLeft.Round();
    // first compute scale factors that scale aSnapRect to the snapped rect
    if (aSnapRect.IsEmpty()) {
      snappedMatrix.xx = matrix2D.xx;
      snappedMatrix.yy = matrix2D.yy;
    } else {
      gfxPoint bottomRight = matrix2D.Transform(aSnapRect.BottomRight());
      bottomRight.Round();
      snappedMatrix.xx = (bottomRight.x - topLeft.x)/aSnapRect.Width();
      snappedMatrix.yy = (bottomRight.y - topLeft.y)/aSnapRect.Height();
    }
    // compute translation factors that will move aSnapRect to the snapped rect
    // given those scale factors
    snappedMatrix.x0 = topLeft.x - aSnapRect.pos.x*snappedMatrix.xx;
    snappedMatrix.y0 = topLeft.y - aSnapRect.pos.y*snappedMatrix.yy;
    result = gfx3DMatrix::From2D(snappedMatrix);
    if (aResidualTransform && !snappedMatrix.IsSingular()) {
      // set aResidualTransform so that aResidual * snappedMatrix == matrix2D.
      // (i.e., appying snappedMatrix after aResidualTransform gives the
      // ideal transform.
      gfxMatrix snappedMatrixInverse = snappedMatrix;
      snappedMatrixInverse.Invert();
      *aResidualTransform = matrix2D * snappedMatrixInverse;
    }
  } else {
    result = aTransform;
  }
  return result;
}

const gfx3DMatrix&
Layer::GetLocalTransform()
{
#ifdef MOZ_IPC
  if (ShadowLayer* shadow = AsShadowLayer())
    return shadow->GetShadowTransform();
#endif
  return mTransform;
}

float
Layer::GetEffectiveOpacity()
{
  float opacity = GetOpacity();
  for (ContainerLayer* c = GetParent(); c && !c->UseIntermediateSurface();
       c = c->GetParent()) {
    opacity *= c->GetOpacity();
  }
  return opacity;
}

PRBool
ContainerLayer::HasMultipleChildren()
{
  PRUint32 count = 0;
  for (Layer* child = GetFirstChild(); child; child = child->GetNextSibling()) {
    const nsIntRect *clipRect = child->GetEffectiveClipRect();
    if (clipRect && clipRect->IsEmpty())
      continue;
    if (child->GetVisibleRegion().IsEmpty())
      continue;
    ++count;
    if (count > 1)
      return PR_TRUE;
  }

  return PR_FALSE;
}

void
ContainerLayer::DefaultComputeEffectiveTransforms(const gfx3DMatrix& aTransformToSurface)
{
  gfxMatrix residual;
  gfx3DMatrix idealTransform = GetLocalTransform()*aTransformToSurface;
  mEffectiveTransform = SnapTransform(idealTransform, gfxRect(0, 0, 0, 0), &residual);

  PRBool useIntermediateSurface;
  float opacity = GetEffectiveOpacity();
  if (opacity != 1.0f && HasMultipleChildren()) {
    useIntermediateSurface = PR_TRUE;
  } else {
    useIntermediateSurface = PR_FALSE;
    gfxMatrix contTransform;
    if (!mEffectiveTransform.Is2D(&contTransform) ||
        !contTransform.PreservesAxisAlignedRectangles()) {
      for (Layer* child = GetFirstChild(); child; child = child->GetNextSibling()) {
        const nsIntRect *clipRect = child->GetEffectiveClipRect();
        /* We can't (easily) forward our transform to children with a non-empty clip
         * rect since it would need to be adjusted for the transform.
         * TODO: This is easily solvable for translation/scaling transforms.
         */
        if (clipRect && !clipRect->IsEmpty() && !child->GetVisibleRegion().IsEmpty()) {
          useIntermediateSurface = PR_TRUE;
          break;
        }
      }
    }
  }

  mUseIntermediateSurface = useIntermediateSurface;
  if (useIntermediateSurface) {
    ComputeEffectiveTransformsForChildren(gfx3DMatrix::From2D(residual));
  } else {
    ComputeEffectiveTransformsForChildren(idealTransform);
  }
}

void
ContainerLayer::ComputeEffectiveTransformsForChildren(const gfx3DMatrix& aTransformToSurface)
{
  for (Layer* l = mFirstChild; l; l = l->GetNextSibling()) {
    l->ComputeEffectiveTransforms(aTransformToSurface);
  }
}

#ifdef MOZ_LAYERS_HAVE_LOG

static nsACString& PrintInfo(nsACString& aTo, ShadowLayer* aShadowLayer);

void
Layer::Dump(FILE* aFile, const char* aPrefix)
{
  DumpSelf(aFile, aPrefix);

  if (Layer* kid = GetFirstChild()) {
    nsCAutoString pfx(aPrefix);
    pfx += "  ";
    kid->Dump(aFile, pfx.get());
  }

  if (Layer* next = GetNextSibling())
    next->Dump(aFile, aPrefix);
}

void
Layer::DumpSelf(FILE* aFile, const char* aPrefix)
{
  nsCAutoString str;
  PrintInfo(str, aPrefix);
  fprintf(FILEOrDefault(aFile), "%s\n", str.get());
}

void
Layer::Log(const char* aPrefix)
{
  if (!IsLogEnabled())
    return;

  LogSelf(aPrefix);

  if (Layer* kid = GetFirstChild()) {
    nsCAutoString pfx(aPrefix);
    pfx += "  ";
    kid->Log(pfx.get());
  }

  if (Layer* next = GetNextSibling())
    next->Log(aPrefix);
}

void
Layer::LogSelf(const char* aPrefix)
{
  if (!IsLogEnabled())
    return;

  nsCAutoString str;
  PrintInfo(str, aPrefix);
  MOZ_LAYERS_LOG(("%s", str.get()));
}

nsACString&
Layer::PrintInfo(nsACString& aTo, const char* aPrefix)
{
  aTo += aPrefix;
  aTo += nsPrintfCString(64, "%s%s (0x%p)", mManager->Name(), Name(), this);

  ::PrintInfo(aTo, AsShadowLayer());

  if (mUseClipRect) {
    AppendToString(aTo, mClipRect, " [clip=", "]");
  }
  if (!mTransform.IsIdentity()) {
    AppendToString(aTo, mTransform, " [transform=", "]");
  }
  if (!mVisibleRegion.IsEmpty()) {
    AppendToString(aTo, mVisibleRegion, " [visible=", "]");
  }
  if (1.0 != mOpacity) {
    aTo.AppendPrintf(" [opacity=%g]", mOpacity);
  }
  if (GetContentFlags() & CONTENT_OPAQUE) {
    aTo += " [opaqueContent]";
  }
  if (GetContentFlags() & CONTENT_COMPONENT_ALPHA) {
    aTo += " [componentAlpha]";
  }

  return aTo;
}

nsACString&
ThebesLayer::PrintInfo(nsACString& aTo, const char* aPrefix)
{
  Layer::PrintInfo(aTo, aPrefix);
  if (!mValidRegion.IsEmpty()) {
    AppendToString(aTo, mValidRegion, " [valid=", "]");
  }
  if (mXResolution != 1.0 || mYResolution != 1.0) {
    aTo.AppendPrintf(" [xres=%g yres=%g]", mXResolution, mYResolution);
  }
  return aTo;
}

nsACString&
ContainerLayer::PrintInfo(nsACString& aTo, const char* aPrefix)
{
  Layer::PrintInfo(aTo, aPrefix);
  return mFrameMetrics.IsDefault() ?
    aTo : AppendToString(aTo, mFrameMetrics, " [metrics=", "]");
}

nsACString&
ColorLayer::PrintInfo(nsACString& aTo, const char* aPrefix)
{
  Layer::PrintInfo(aTo, aPrefix);
  AppendToString(aTo, mColor, " [color=", "]");
  return aTo;
}

nsACString&
CanvasLayer::PrintInfo(nsACString& aTo, const char* aPrefix)
{
  Layer::PrintInfo(aTo, aPrefix);
  if (mFilter != gfxPattern::FILTER_GOOD) {
    AppendToString(aTo, mFilter, " [filter=", "]");
  }
  return aTo;
}

nsACString&
ImageLayer::PrintInfo(nsACString& aTo, const char* aPrefix)
{
  Layer::PrintInfo(aTo, aPrefix);
  if (mFilter != gfxPattern::FILTER_GOOD) {
    AppendToString(aTo, mFilter, " [filter=", "]");
  }
  return aTo;
}

//--------------------------------------------------
// LayerManager

void
LayerManager::Dump(FILE* aFile, const char* aPrefix)
{
  FILE* file = FILEOrDefault(aFile);

  DumpSelf(file, aPrefix);

  nsCAutoString pfx(aPrefix);
  pfx += "  ";
  if (!GetRoot()) {
    fprintf(file, "%s(null)", pfx.get());
    return;
  }

  GetRoot()->Dump(file, pfx.get());
}

void
LayerManager::DumpSelf(FILE* aFile, const char* aPrefix)
{
  nsCAutoString str;
  PrintInfo(str, aPrefix);
  fprintf(FILEOrDefault(aFile), "%s\n", str.get());
}

void
LayerManager::Log(const char* aPrefix)
{
  if (!IsLogEnabled())
    return;

  LogSelf(aPrefix);

  nsCAutoString pfx(aPrefix);
  pfx += "  ";
  if (!GetRoot()) {
    MOZ_LAYERS_LOG(("%s(null)", pfx.get()));
    return;
  }

  GetRoot()->Log(pfx.get());
}

void
LayerManager::LogSelf(const char* aPrefix)
{
  nsCAutoString str;
  PrintInfo(str, aPrefix);
  MOZ_LAYERS_LOG(("%s", str.get()));
}

nsACString&
LayerManager::PrintInfo(nsACString& aTo, const char* aPrefix)
{
  aTo += aPrefix;
  return aTo += nsPrintfCString(64, "%sLayerManager (0x%p)", Name(), this);
}

/*static*/ void
LayerManager::InitLog()
{
  if (!sLog)
    sLog = PR_NewLogModule("Layers");
}

/*static*/ bool
LayerManager::IsLogEnabled()
{
  NS_ABORT_IF_FALSE(!!sLog,
                    "layer manager must be created before logging is allowed");
  return PR_LOG_TEST(sLog, PR_LOG_DEBUG);
}

# ifdef MOZ_IPC
static nsACString&
PrintInfo(nsACString& aTo, ShadowLayer* aShadowLayer)
{
  if (!aShadowLayer) {
    return aTo;
  }
  if (const nsIntRect* clipRect = aShadowLayer->GetShadowClipRect()) {
    AppendToString(aTo, *clipRect, " [shadow-clip=", "]");
  }
  if (!aShadowLayer->GetShadowTransform().IsIdentity()) {
    AppendToString(aTo, aShadowLayer->GetShadowTransform(), " [shadow-transform=", "]");
  }
  if (!aShadowLayer->GetShadowVisibleRegion().IsEmpty()) {
    AppendToString(aTo, aShadowLayer->GetShadowVisibleRegion(), " [shadow-visible=", "]");
  }
  return aTo;
}
# else
static nsACString& PrintInfo(nsACString& aTo, ShadowLayer* aShadowLayer)
{
  return aTo;
}
# endif  // MOZ_IPC

#else  // !MOZ_LAYERS_HAVE_LOG

void Layer::Dump(FILE* aFile, const char* aPrefix) {}
void Layer::DumpSelf(FILE* aFile, const char* aPrefix) {}
void Layer::Log(const char* aPrefix) {}
void Layer::LogSelf(const char* aPrefix) {}
nsACString&
Layer::PrintInfo(nsACString& aTo, const char* aPrefix)
{ return aTo; }

nsACString&
ThebesLayer::PrintInfo(nsACString& aTo, const char* aPrefix)
{ return aTo; }

nsACString&
ContainerLayer::PrintInfo(nsACString& aTo, const char* aPrefix)
{ return aTo; }

nsACString&
ColorLayer::PrintInfo(nsACString& aTo, const char* aPrefix)
{ return aTo; }

nsACString&
CanvasLayer::PrintInfo(nsACString& aTo, const char* aPrefix)
{ return aTo; }

nsACString&
ImageLayer::PrintInfo(nsACString& aTo, const char* aPrefix)
{ return aTo; }

void LayerManager::Dump(FILE* aFile, const char* aPrefix) {}
void LayerManager::DumpSelf(FILE* aFile, const char* aPrefix) {}
void LayerManager::Log(const char* aPrefix) {}
void LayerManager::LogSelf(const char* aPrefix) {}

nsACString&
LayerManager::PrintInfo(nsACString& aTo, const char* aPrefix)
{ return aTo; }

/*static*/ void LayerManager::InitLog() {}
/*static*/ bool LayerManager::IsLogEnabled() { return false; }

#endif // MOZ_LAYERS_HAVE_LOG

PRLogModuleInfo* LayerManager::sLog;

} // namespace layers 
} // namespace mozilla
