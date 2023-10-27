/*

This file is part of VROOM.

Copyright (c) 2015-2022, Julien Coupey.
All rights reserved (see LICENSE).

*/

#include "structures/vroom/time_window.h"
#include "utils/exception.h"

namespace vroom {

constexpr Duration TimeWindow::default_length =
  std::numeric_limits<Duration>::max();

TimeWindow::TimeWindow()
  : start(0), end(std::numeric_limits<Duration>::max()), length(end - start) {
}

TimeWindow::TimeWindow(UserDuration start, UserDuration end)
  : start(utils::scale_from_user_duration(start)),
    end(utils::scale_from_user_duration(end)),
    length(utils::scale_from_user_duration(end - start)) {
  if (start > end) {
    throw InputException("Invalid time window: [" + std::to_string(start.count()) +
                         ", " + std::to_string(end.count()) + "]");
  }
}

bool TimeWindow::contains(Duration time) const {
  return (start <= time) && (time <= end);
}

bool TimeWindow::is_default() const {
  return end - start == default_length;
}

bool operator<(const TimeWindow& lhs, const TimeWindow& rhs) {
  return lhs.start < rhs.start || (lhs.start == rhs.start && lhs.end < rhs.end);
}

} // namespace vroom
