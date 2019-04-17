# let%Anything

This is a ppx that looks for `let%Anything`, where Anything is a valid module identifier (e.g. captialized), and turns it into `Anything.let_(value, pattern => continuation)`.

It's an exploration of [this PR to the reason repo](https://github.com/facebook/reason/pull/2140).

Here's an example of using it ([source](https://github.com/notablemind/renm/blob/949e1583d4df5e6d61ea066767a52828f8f8069b/src/core/Store.re#L116
))
```re
let%Opt node = get(store, id);
let%Opt parent = get(store, node.parent);
Some((
  [NodeChildren(parent.id, parent.children |. List.keep((!=)(node.id))), DeleteNode(node.id),
  View({...store.view, active: nextId})
  ],
  [Event.Node(parent.id), Event.View(Node(nextId))]
))
```

### try%Anything
If you have a data type that has a "failure" case (like promises, or the `result` type), the `try%Anything` syntax can be helpful.
Here's the transform:

```
try%Blah someExpr {
  | Something(x) => y
}
```
becomes
```
Blah.try_(someExpr, result => switch result {
  | Something(x) => y
})
```

Let's make a `try_` function for the `result` type that does a *bind* over the error case:
```
module Res = {
  let try_ = (result, handler) => switch result {
    | Ok(v) => Ok(v)
    | Error(e) => handler(e)
  }
}
```
This will come in handy for the case where we want to transform the error side of a result -- either turning it into a different error type, or turning it into a successful value. For example:
```
let v = Error("bad")
try%Res v {
  | "invalid username/password" => Error(UserError)
  | "no user - use default" => Ok(defaultUser)
  | message => Error(ServerError)
}
```

## Addendum

And here are the modules used ([source](https://github.com/notablemind/renm/blob/949e1583d4df5e6d61ea066767a52828f8f8069b/src/utils/Lets.re))
```re
module Opt = {
  let let_ = (a, b) => switch (a) {
    | None => None
    | Some(x) => b(x)
  }
};

module Result = {
  let let_ = (value, fn) => switch value {
    | Ok(v) => fn(v)
    | Error(_) => value
  };
  let try_ = (value, fn) => switch value {
    | Ok(_) => value
    | Error(err) => fn(err)
  };
}
```
