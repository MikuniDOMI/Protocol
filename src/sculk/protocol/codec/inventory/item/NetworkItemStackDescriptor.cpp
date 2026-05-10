// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "sculk/protocol/codec/inventory/item/NetworkItemStackDescriptor.hpp"

namespace sculk::protocol::inline abi_v975 {

void NetworkItemStackDescriptor::write(BinaryStream& stream) const {
    if (mId == 0) {
        stream.writeVarInt(0);
    } else {
        stream.writeVarInt(mId);
        stream.writeUnsignedShort(mStackSize);
        stream.writeUnsignedVarInt(mAux);
        stream.writeOptional(mNetId, &BinaryStream::writeVarInt);
        stream.writeVarInt(mBlockRuntimeId);
        stream.writeString(mUserData);
    }
}

[[nodiscard]] Result<> NetworkItemStackDescriptor::read(ReadOnlyBinaryStream& stream) {
    int id{};
    _SCULK_READ(stream.readVarInt(id));
    mId = static_cast<short>(id);
    if (mId == 0) {
        return {}; // Empty item stack
    } else {
        _SCULK_READ(stream.readUnsignedShort(mStackSize));
        _SCULK_READ(stream.readUnsignedVarInt(mAux));
        _SCULK_READ(stream.readOptional(mNetId, &ReadOnlyBinaryStream::readVarInt));
        int blockRuntimeId{};
        _SCULK_READ(stream.readVarInt(blockRuntimeId));
        mBlockRuntimeId = static_cast<std::uint32_t>(blockRuntimeId);
        return stream.readString(mUserData);
    }
}

void NetworkItemStackDescriptor::writeCereal(BinaryStream& stream) const {
    stream.writeSignedShort(mId);
    stream.writeUnsignedShort(mStackSize);
    stream.writeUnsignedVarInt(mAux);
    stream.writeOptional(mNetId, &BinaryStream::writeVarInt);
    if (mNetId.has_value()) {
        stream.writeBool(true);
        stream.writeUnsignedVarInt(0); // Unused in v975
        stream.writeVarInt(mNetId.value());
    } else {
        stream.writeBool(false);
    }
    stream.writeUnsignedVarInt(mBlockRuntimeId);
    stream.writeString(mUserData);
}

[[nodiscard]] Result<> NetworkItemStackDescriptor::readCereal(ReadOnlyBinaryStream& stream) {
    _SCULK_READ(stream.readSignedShort(mId));
    _SCULK_READ(stream.readUnsignedShort(mStackSize));
    _SCULK_READ(stream.readUnsignedVarInt(mAux));
    _SCULK_READ(stream.readOptional(mNetId, &ReadOnlyBinaryStream::readVarInt));
    bool hasValue = false;
    _SCULK_READ(stream.readBool(hasValue));
    if (hasValue) {
        uint32_t u;
        _SCULK_READ(stream.readUnsignedVarInt(u));
        switch (u) {
        case 0:
        case 1:
        case 2:
            int32_t netid;
            _SCULK_READ(stream.readVarInt(netid));
            mNetId = std::optional<int32_t>(netid);
            break;
        }
    }
    _SCULK_READ(stream.readUnsignedVarInt(mBlockRuntimeId));
    return stream.readString(mUserData);
}

} // namespace sculk::protocol::inline abi_v975
