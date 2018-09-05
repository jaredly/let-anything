# let%Anything

This is a ppx that looks for `let%Anything`, where Anything is a valid module identifier (e.g. captialized), and turns it into `Anything.let_(value, pattern => continuation)`.

It's an exploration of [this PR to the reason repo](https://github.com/facebook/reason/pull/2140).