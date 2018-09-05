
module Opt = {
  let let_ = (a, b) => switch (a) {
    | None => None
    | Some(x) => b(x)
  }
};

module Opt_map = {
  let let_ = (a, b) => switch (a) {
    | None => None
    | Some(x) => Some(b(x))
  }
};

let x = {
  let%Opt y = Some(2);
  let%Opt_map x = Some(10);
  x + 2 + y
};
