// Copyright 2017 The Abseil Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//
// NOTE FOR GOOGLERS:
//
// IWYU pragma: private, include "base/log_severity.h"

#ifndef S2_THIRD_PARTY_ABSL_BASE_INTERNAL_LOG_SEVERITY_H_
#define S2_THIRD_PARTY_ABSL_BASE_INTERNAL_LOG_SEVERITY_H_

#include <array>

#include "s2/third_party/absl/base/attributes.h"

namespace absl {

enum class LogSeverity : int {
  kInfo = 0,
  kWarning = 1,
  kError = 2,
  kFatal = 3,
};

// Returns an iterable of all standard `absl::LogSeverity` values, ordered from
// least to most severe.
constexpr std::array<absl::LogSeverity, 4> LogSeverities() {
  return {{absl::LogSeverity::kInfo, absl::LogSeverity::kWarning,
           absl::LogSeverity::kError, absl::LogSeverity::kFatal}};
}

// absl::kLogDebugFatal equals absl::LogSeverity::kFatal in debug builds (i.e.
// when NDEBUG is not defined) and absl::LogSeverity::kError otherwise.
// It is extern to prevent ODR violations when compilation units with different
// build settings are linked together.
ABSL_CONST_INIT extern const absl::LogSeverity kLogDebugFatal;

constexpr const char* LogSeverityName(absl::LogSeverity s) {
  return s == absl::LogSeverity::kInfo
             ? "INFO"
             : s == absl::LogSeverity::kWarning
                   ? "WARNING"
                   : s == absl::LogSeverity::kError
                         ? "ERROR"
                         : s == absl::LogSeverity::kFatal ? "FATAL" : "UNKNOWN";
}

// Note that out-of-range severities normalize to kInfo or kError, never kFatal.
constexpr absl::LogSeverity NormalizeLogSeverity(absl::LogSeverity s) {
  return s < absl::LogSeverity::kInfo
             ? absl::LogSeverity::kInfo
             : s > absl::LogSeverity::kFatal ? absl::LogSeverity::kError : s;
}
constexpr absl::LogSeverity NormalizeLogSeverity(int s) {
  return NormalizeLogSeverity(static_cast<absl::LogSeverity>(s));
}

}  // namespace absl

#endif  // S2_THIRD_PARTY_ABSL_BASE_INTERNAL_LOG_SEVERITY_H_
