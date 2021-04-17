#pragma once

#include "State.h"

#include <iostream>

namespace program_analyzer {
namespace straight {

enum Sign {
  Positive,
  Negative,
  Zero,
  Unknown
};

class SignState : public State {
  Sign sign_;
public:
  SignState();
  SignState(int number);

  // Define State operators
  friend SignState operator+(SignState lhs,
			     const SignState &rhs);
  friend SignState operator-(SignState lhs,
			     const SignState &rhs);
  friend SignState operator*(SignState lhs,
			    const SignState &rhs);

  // TODO: use better ways to output 
  friend std::ostream &operator<<(std::ostream &os,
				  const SignState &s);
};

}
}
