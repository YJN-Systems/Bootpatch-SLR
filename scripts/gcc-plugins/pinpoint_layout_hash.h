#pragma once

#include <array>
#include <cstddef>

#include <pinpoint_stage0.h>

std::array<std::byte, 16> layout_hash(const TargetType &target);
