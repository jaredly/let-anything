
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

module Result = {
  include Belt.Result;
  let let_ = (v, fn) => switch v {
    | Ok(o) => fn(o)
    | Error(_) => v
  };
  let try_ = (v, fn) => switch v {
    | Ok(_) => v
    | Error(e) => fn(e)
  };
};

let z = {
  let%Result x = Ok(5);
  let%Result y = try%Result (Error("fail")) {
    | x => Ok(40)
  };
  Ok(x + y)
}

let x = {
  let%Opt y = Some(2);
  let%Opt_map x = Some(10);
  x + 2 + y
};
