# webgl demos in a single file, the way god intended

^.^

This probably isn't useful to you unless you already hack on graphics programming enough to know the APIs by sight and just need to see the calls flat, without abstraction, so that you can quickly prototype something, and then see the best abstractions afterwards.

The exception here, for me, is matrix math, because I still think of matrix/quaternion operations in terms of things like "make a rotation matrix," "apply a quaternion," and I haven't internalized them the way I have simpler operations like vector dot product. To be fair, matrices I have internalized a great deal -- I can see the individual basis vectors in the columns, so constructing scale, translate, and rotation etc. matrices makes plenty of sense -- but I'm not hacking on the primitives of matrix math so much as I'm trying to find really efficient ways to render :sparkles: quirky things :sparkles:. So each file just has a blob of matrix functions at the top.

## cube
[cube](https://cedric-h.github.io/linear-webgl/cube.html)


