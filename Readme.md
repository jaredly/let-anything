# let%Anything

This is a ppx that looks for `let%Anything`, where Anything is a valid module identifier (e.g. captialized), and turns it into `Anything.let_(value, pattern => continuation)`.

It's an exploration of [this PR to the reason repo](https://github.com/facebook/reason/pull/2140).

Here's an example of using it ([source](https://github.com/notablemind/renm/blob/949e1583d4df5e6d61ea066767a52828f8f8069b/src/core/Store.re#L116
))
```re
let%OptIf () = id != store.data.root;
let%Opt node = get(store, id);
let%Opt parent = get(store, node.parent);
Some((
  [NodeChildren(parent.id, parent.children |. List.keep((!=)(node.id))), DeleteNode(node.id),
  View({...store.view, active: nextId})
  ],
  [Event.Node(parent.id), Event.View(Node(nextId))]
))
```


And here's are the modules used ([source](https://github.com/notablemind/renm/blob/949e1583d4df5e6d61ea066767a52828f8f8069b/src/utils/Lets.re))
```re
module Opt = {
  let let_ = (a, b) => switch (a) {
    | None => None
    | Some(x) => b(x)
  }
};

module OptIf = {
  let let_ = (a, b) => if (a) {
    b()
  } else {
    None
  }
};
```
