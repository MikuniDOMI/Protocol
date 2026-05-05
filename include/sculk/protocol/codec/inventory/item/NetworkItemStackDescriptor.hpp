// Copyright © 2026 SculkCatalystMC. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include "sculk/protocol/codec/utility/deps/BinaryStream.hpp"
#include "sculk/protocol/codec/utility/deps/ReadOnlyBinaryStream.hpp"
#include <optional>

namespace sculk::protocol::inline abi_v975 {

struct NetworkItemStackDescriptor {
    short              mId{};
    std::uint16_t      mStackSize{};
    std::uint32_t      mAux{};
    std::optional<int> mNetId{};
    std::uint32_t      mBlockRuntimeId{};
    std::string        mUserData{};

    void write(BinaryStream& stream) const;

    [[nodiscard]] Result<> read(ReadOnlyBinaryStream& stream);

    void writeCereal(BinaryStream& stream) const;

    [[nodiscard]] Result<> readCereal(ReadOnlyBinaryStream& stream);
};

} // namespace sculk::protocol::inline abi_v975
