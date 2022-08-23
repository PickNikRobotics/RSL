// Copyright 2022 PickNik Inc.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of the PickNik Inc. nor the names of its
//      contributors may be used to endorse or promote products derived from
//      this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include "thread_rand/thread_rand.hpp"

#include <algorithm>   // for std::generate_n
#include <array>       // for std::array, std::data,
#include <functional>  // for std::ref
#include <random>      // for std::mt19937, random_device, seed_seq
#include <stdexcept>   // for std::runtime_error

namespace thread_rand {

auto rng(std::seed_seq seed_sequence) -> std::mt19937& {
  thread_local bool first = false;
  thread_local std::mt19937 generator = [&seed_sequence]() {
    first = true;
    if (seed_sequence.size() > 0) {
      return std::mt19937(seed_sequence);
    }
    std::array<int, std::mt19937::state_size> seed_data;
    std::random_device random_device;
    std::generate_n(std::data(seed_data), std::size(seed_data),
                    std::ref(random_device));
    std::seed_seq sequence(std::begin(seed_data), std::end(seed_data));
    return std::mt19937(sequence);
  }();
  if (!first && seed_sequence.size() > 0) {
    throw std::runtime_error("rng cannot be re-seeded on this thread");
  }
  return generator;
}

}  // namespace thread_rand
