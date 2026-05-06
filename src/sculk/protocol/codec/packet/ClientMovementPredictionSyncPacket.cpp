// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/packet/ClientMovementPredictionSyncPacket.hpp"

namespace sculk::protocol::inline abi_v975 {

MinecraftPacketIds ClientMovementPredictionSyncPacket::getId() const noexcept {
    return MinecraftPacketIds::ClientMovementPredictionSync;
}
std::string_view ClientMovementPredictionSyncPacket::getName() const noexcept {
    return "ClientMovementPredictionSyncPacket";
}

void ClientMovementPredictionSyncPacket::MovementAttributesComponent::write(BinaryStream& stream) const {
    stream.writeFloat(mMovementSpeed);
    stream.writeFloat(mUnderwaterMovementSpeed);
    stream.writeFloat(mLavaMovementSpeed);
    stream.writeFloat(mJumpStrength);
    stream.writeFloat(mHealth);
    stream.writeFloat(mHunger);
    stream.writeFloat(mUnknown1);
    stream.writeFloat(mUnknown2);
    stream.writeFloat(mUnknown3);
}

Result<> ClientMovementPredictionSyncPacket::MovementAttributesComponent::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readFloat(mMovementSpeed));
    _SCULK_READ(stream.readFloat(mUnderwaterMovementSpeed));
    _SCULK_READ(stream.readFloat(mLavaMovementSpeed));
    _SCULK_READ(stream.readFloat(mJumpStrength));
    _SCULK_READ(stream.readFloat(mHealth));
    _SCULK_READ(stream.readFloat(mHunger));
    _SCULK_READ(stream.readFloat(mUnknown1));
    _SCULK_READ(stream.readFloat(mUnknown2));
    return stream.readFloat(mUnknown3);
}

void ClientMovementPredictionSyncPacket::write(BinaryStream& stream) const {
    stream.writeBitset(mActorFlags);
    mActorBoundingBox.write(stream);
    mMovementAttributes.write(stream);
    stream.writeVarInt64(mActorID);
    stream.writeBool(mFlying);
}

Result<> ClientMovementPredictionSyncPacket::read(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readBitset(mActorFlags));
    _SCULK_READ(mActorBoundingBox.read(stream));
    _SCULK_READ(mMovementAttributes.read(stream));
    _SCULK_READ(stream.readVarInt64(mActorID));
    return stream.readBool(mFlying);
}

} // namespace sculk::protocol::inline abi_v975
