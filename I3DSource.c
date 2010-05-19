/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 3DSource implementation */

#include "sles_allinclusive.h"

static SLresult I3DSource_SetHeadRelative(SL3DSourceItf self,
    SLboolean headRelative)
{
    I3DSource *this = (I3DSource *) self;
    interface_lock_poke(this);
    this->mHeadRelative = headRelative;
    interface_unlock_poke(this);
    return SL_RESULT_SUCCESS;
}

static SLresult I3DSource_GetHeadRelative(SL3DSourceItf self,
    SLboolean *pHeadRelative)
{
    if (NULL == pHeadRelative)
        return SL_RESULT_PARAMETER_INVALID;
    I3DSource *this = (I3DSource *) self;
    interface_lock_peek(this);
    SLboolean headRelative = this->mHeadRelative;
    interface_unlock_peek(this);
    *pHeadRelative = headRelative;
    return SL_RESULT_SUCCESS;
}

static SLresult I3DSource_SetRolloffDistances(SL3DSourceItf self,
    SLmillimeter minDistance, SLmillimeter maxDistance)
{
    I3DSource *this = (I3DSource *) self;
    interface_lock_exclusive(this);
    this->mMinDistance = minDistance;
    this->mMaxDistance = maxDistance;
    interface_unlock_exclusive(this);
    return SL_RESULT_SUCCESS;
}

static SLresult I3DSource_GetRolloffDistances(SL3DSourceItf self,
    SLmillimeter *pMinDistance, SLmillimeter *pMaxDistance)
{
    if (NULL == pMinDistance || NULL == pMaxDistance)
        return SL_RESULT_PARAMETER_INVALID;
    I3DSource *this = (I3DSource *) self;
    interface_lock_shared(this);
    SLmillimeter minDistance = this->mMinDistance;
    SLmillimeter maxDistance = this->mMaxDistance;
    interface_unlock_shared(this);
    *pMinDistance = minDistance;
    *pMaxDistance = maxDistance;
    return SL_RESULT_SUCCESS;
}

static SLresult I3DSource_SetRolloffMaxDistanceMute(SL3DSourceItf self,
    SLboolean mute)
{
    I3DSource *this = (I3DSource *) self;
    interface_lock_poke(this);
    this->mRolloffMaxDistanceMute = mute;
    interface_unlock_poke(this);
    return SL_RESULT_SUCCESS;
}

static SLresult I3DSource_GetRolloffMaxDistanceMute(SL3DSourceItf self,
    SLboolean *pMute)
{
    if (NULL == pMute)
        return SL_RESULT_PARAMETER_INVALID;
    I3DSource *this = (I3DSource *) self;
    interface_lock_peek(this);
    SLboolean mute = this->mRolloffMaxDistanceMute;
    interface_unlock_peek(this);
    *pMute = mute;
    return SL_RESULT_SUCCESS;
}

static SLresult I3DSource_SetRolloffFactor(SL3DSourceItf self,
    SLpermille rolloffFactor)
{
    I3DSource *this = (I3DSource *) self;
    interface_lock_poke(this);
    this->mRolloffFactor = rolloffFactor;
    interface_unlock_poke(this);
    return SL_RESULT_SUCCESS;
}

static SLresult I3DSource_GetRolloffFactor(SL3DSourceItf self,
    SLpermille *pRolloffFactor)
{
    I3DSource *this = (I3DSource *) self;
    interface_lock_peek(this);
    SLpermille rolloffFactor = this->mRolloffFactor;
    interface_unlock_peek(this);
    *pRolloffFactor = rolloffFactor;
    return SL_RESULT_SUCCESS;
}

static SLresult I3DSource_SetRoomRolloffFactor(SL3DSourceItf self,
    SLpermille roomRolloffFactor)
{
    I3DSource *this = (I3DSource *) self;
    interface_lock_poke(this);
    this->mRoomRolloffFactor = roomRolloffFactor;
    interface_unlock_poke(this);
    return SL_RESULT_SUCCESS;
}

static SLresult I3DSource_GetRoomRolloffFactor(SL3DSourceItf self,
    SLpermille *pRoomRolloffFactor)
{
    I3DSource *this = (I3DSource *) self;
    interface_lock_peek(this);
    SLpermille roomRolloffFactor = this->mRoomRolloffFactor;
    interface_unlock_peek(this);
    *pRoomRolloffFactor = roomRolloffFactor;
    return SL_RESULT_SUCCESS;
}

static SLresult I3DSource_SetRolloffModel(SL3DSourceItf self, SLuint8 model)
{
    I3DSource *this = (I3DSource *) self;
    interface_lock_poke(this);
    this->mDistanceModel = model;
    interface_unlock_poke(this);
    return SL_RESULT_SUCCESS;
}

static SLresult I3DSource_GetRolloffModel(SL3DSourceItf self, SLuint8 *pModel)
{
    I3DSource *this = (I3DSource *) self;
    interface_lock_peek(this);
    SLuint8 model = this->mDistanceModel;
    interface_unlock_peek(this);
    *pModel = model;
    return SL_RESULT_SUCCESS;
}

static SLresult I3DSource_SetCone(SL3DSourceItf self, SLmillidegree innerAngle,
    SLmillidegree outerAngle, SLmillibel outerLevel)
{
    I3DSource *this = (I3DSource *) self;
    interface_lock_exclusive(this);
    this->mConeInnerAngle = innerAngle;
    this->mConeOuterAngle = outerAngle;
    this->mConeOuterLevel = outerLevel;
    interface_unlock_exclusive(this);
    return SL_RESULT_SUCCESS;
}

static SLresult I3DSource_GetCone(SL3DSourceItf self,
    SLmillidegree *pInnerAngle, SLmillidegree *pOuterAngle,
    SLmillibel *pOuterLevel)
{
    if (NULL == pInnerAngle || NULL == pOuterAngle || NULL == pOuterLevel)
        return SL_RESULT_PARAMETER_INVALID;
    I3DSource *this = (I3DSource *) self;
    interface_lock_shared(this);
    SLmillidegree innerAngle = this->mConeInnerAngle;
    SLmillidegree outerAngle = this->mConeOuterAngle;
    SLmillibel outerLevel = this->mConeOuterLevel;
    interface_unlock_shared(this);
    *pInnerAngle = innerAngle;
    *pOuterAngle = outerAngle;
    *pOuterLevel = outerLevel;
    return SL_RESULT_SUCCESS;
}

static const struct SL3DSourceItf_ I3DSource_Itf = {
    I3DSource_SetHeadRelative,
    I3DSource_GetHeadRelative,
    I3DSource_SetRolloffDistances,
    I3DSource_GetRolloffDistances,
    I3DSource_SetRolloffMaxDistanceMute,
    I3DSource_GetRolloffMaxDistanceMute,
    I3DSource_SetRolloffFactor,
    I3DSource_GetRolloffFactor,
    I3DSource_SetRoomRolloffFactor,
    I3DSource_GetRoomRolloffFactor,
    I3DSource_SetRolloffModel,
    I3DSource_GetRolloffModel,
    I3DSource_SetCone,
    I3DSource_GetCone
};

void I3DSource_init(void *self)
{
    I3DSource *this = (I3DSource *) self;
    this->mItf = &I3DSource_Itf;
#ifndef NDEBUG
    this->mHeadRelative = SL_BOOLEAN_FALSE;
    this->mRolloffMaxDistanceMute = SL_BOOLEAN_FALSE;
    this->mConeOuterLevel = 0;
    this->mRoomRolloffFactor = 0;
#endif
    this->mMaxDistance = SL_MILLIMETER_MAX;
    this->mMinDistance = 1000;
    this->mConeInnerAngle = 360000;
    this->mConeOuterAngle = 360000;
    this->mRolloffFactor = 1000;
    this->mDistanceModel = SL_ROLLOFFMODEL_EXPONENTIAL;
}
