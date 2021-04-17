#include "SignState.h"

namespace program_analyzer {
namespace condition {

SignState::SignState() {
  sign_ = Unknown;
}

SignState::SignState(int number) {
  if (number > 0) {
    sign_ = Positive;
  } else if (number < 0) {
    sign_ = Negative;
  } else {
    sign_ = Zero;
  }
}

SignState operator+(SignState lhs, const SignState &rhs) {
  if (lhs.sign_ == Unknown || rhs.sign_ == Unknown) {
    return lhs;
  }

  if (lhs.sign_ == rhs.sign_) {
    return lhs;
  }
  
  if (lhs.sign_ == Positive && rhs.sign_ == Zero || lhs.sign_ == Zero && rhs.sign_ == Positive) {
    lhs.sign_ = Positive;
  } else if (lhs.sign_ == Positive && rhs.sign_ == Negative || lhs.sign_ == Negative && rhs.sign_ == Positive) {
    lhs.sign_ = Unknown;
  }

  return lhs;
}

SignState operator-(SignState lhs, const SignState &rhs) {
  if (lhs.sign_ == Unknown || rhs.sign_ == Unknown) {
    return lhs;
  }

  if (lhs.sign_ == Zero && rhs.sign_ == Zero) {
    lhs.sign_ = Zero;
    return lhs;
  }
  
  if (lhs.sign_ == rhs.sign_) {
    lhs.sign_ = Unknown;
    return lhs;
  }

  if (lhs.sign_ == Negative) {
    return lhs;
  }
  
  lhs.sign_ = Positive;
  return lhs;
}

SignState operator*(SignState lhs, const SignState &rhs) {
  if (lhs.sign_ == Unknown || rhs.sign_ == Unknown) {
    return lhs;
  }

  if (lhs.sign_ == Zero || rhs.sign_ == Zero) {
    lhs.sign_ = Zero;
    return lhs;
  }
  
  if (lhs.sign_ == rhs.sign_) {
    lhs.sign_ = Positive;
    return lhs;
  }

  lhs.sign_ = Negative;
  return lhs;
}

bool operator==(const SignState &lhs, const SignState &rhs) {
  return lhs.sign_ == rhs.sign_;
}

bool operator!=(const SignState &lhs, const SignState &rhs) {
  return !(lhs == rhs);
}
  
std::ostream &operator<<(std::ostream &os,
			 const SignState &s) {
  switch (s.sign_) {
  case Negative:
    os << "Negative";
    break;
  case Positive:
    os << "Positive";
    break;
  case Zero:
    os << "Zero";
    break;
  case Unknown:
    os << "Unknown";
    break;
  }
  return os;
}

}
}
