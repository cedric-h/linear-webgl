# webgl demos in a single file, the way god intended

^.^

This probably isn't useful to you unless you already hack on graphics programming enough to know the APIs by sight and just need to see the calls flat, without abstraction, so that you can quickly prototype something, and then see the best abstractions afterwards.

The exception here, for me, is matrix math, a blob of functions for which I simply paste into the top of each script. I've internalized a lot of CG relevant matrix math to the point where I can recite it from memory where necessary, but I'm not hacking on the primitives of matrix math so much as I'm trying to find really efficient ways to render :sparkles: quirky things :sparkles:. So each file just has a blob of matrix functions at the top.

## cube
[cube](https://cedric-h.github.io/linear-webgl/cube.html)

it's a cube.


## gazebo
[gazebo](https://cedric-h.github.io/linear-webgl/gazebo.html)

simple OBJ model

## nodes

<img width="1347" alt="Screenshot 2024-03-08 at 2 40 15 PM" src="https://github.com/cedric-h/linear-webgl/assets/25539554/223cbe91-9ad0-449d-b0cd-7df599854b87">

interactive data thing with text, drop shadows, zooming, panning, scrollbars, etc.

[nodes](https://cedric-h.github.io/linear-webgl/nodes.html)

also a WebGL 1 version that works (~25 fps) at low resolutions on a raspberry pi Model B that only supports WebGL 1
(this was a rewrite of an application that got 200ms frametimes (5 fps) on a $3000 macbook)

[nodes-rpi](https://cedric-h.github.io/linear-webgl/nodes-rpi)

## text

simple text demo, based on mapbox's TinySDF

I wanna clean it up a bit.

[text](https://cedric-h.github.io/linear-webgl/text)

## text-clipped

example of how to clip text without scissor rects, useful for doing a lot of text with few drawcalls

[text](https://cedric-h.github.io/linear-webgl/text)
