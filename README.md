# webgl demos in a single file, the way god intended

If you ask me, any attempt to make an abstraction over WebGL ... only makes it more difficult to use.

But don't take it from me, let's look at the numbers:

- Higher level abstractions [suffer from performance issues](benchmarks.slaylines.io)

- Lower level abstractions like [picogl](https://tsherif.github.io/picogl.js/), [twgl](https://twgljs.org/) and [regl](https://regl-project.github.io/regl/) hardly offer enough to be worth the marginally larger bundle size. (coming in at 67k, 52k, and 86k respectively ... [i fit a minimal minecraft clone in under 96kb](https://github.com/cedric-h/cedcraft) and [you should really only block on the loading of 650kb max, ever](https://infrequently.org/2024/01/performance-inequality-gap-2024/))

WebGPU will be nice, but [I've been waiting for it since 2018](https://github.com/cedric-h/stockRPG/blob/master/src/wgpu/game_renderer.rs). It's only just been rolled out in a single browser, it will be forever before it makes it to low-end mobile devices, and that's where performance (and therefore clever graphics programming) matters the most.

So raw, unadulterated WebGL it is. [Webglfundamentals.org](https://webglfundamentals.org) is great, but it's just that: fundamentals. I want scrollbars and dropshadows and examples where those "fundamentals" are used to do __real shit__.

Ergo: flat, linear WebGL.

## simple

| **link**                                                                       | **desc**                                                                                                                       |
|--------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------|
| [cube  ](https://cedric-h.github.io/linear-webgl/cube.html)                    | it's a cube.                                                                                                                   |
| [gazebo](https://cedric-h.github.io/linear-webgl/gazebo.html)                  | simple OBJ model                                                                                                               |
| [tri   ](https://cedric-h.github.io/linear-webgl/tri.html)                     | triangle; starting-off point; _well, I tri-d._                                                                                 |

<img width="400" alt="Screenshot 2024-03-08 at 2 54 01 PM" src="https://github.com/cedric-h/linear-webgl/assets/25539554/b1d41550-0d5b-4051-af55-6846f1738175">


## nodes

interactive data thing with text, drop shadows, zooming, panning, scrollbars, etc.

[nodes](https://cedric-h.github.io/linear-webgl/nodes.html),
[nodes-rpi](https://cedric-h.github.io/linear-webgl/nodes_rpi)

also: nodes-rpi, a WebGL 1 version that works (~25 fps) at low resolutions on a raspberry pi Model B that only supports WebGL 1

(this was a rewrite of an SVG-based application that got 200ms frametimes (5 fps) on a $3000 macbook)

<img width="400" alt="Screenshot 2024-03-08 at 2 40 15 PM" src="https://github.com/cedric-h/linear-webgl/assets/25539554/223cbe91-9ad0-449d-b0cd-7df599854b87">


## text

simple text demo, based on mapbox's TinySDF

I've tried a lot of different mechanisms for doing text and this one works the best by far with arbitrary zoom

| **link**                                                                       | **desc**                                                                                                                       |
|--------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------|
| [text           ](https://cedric-h.github.io/linear-webgl/text)                | shows off tinysdf, arbitrarily zoomable text on an infinite canvas                                                             |
| [text-dropin    ](https://cedric-h.github.io/linear-webgl/text_dropin)         | simpler text (no controls) you can just drop into an existing project                                                          |
| [text-clipped   ](https://cedric-h.github.io/linear-webgl/text_clipped)        | example of how to clip text without scissor rects, useful for doing a lot of text with few drawcalls                           |

also: example of how to clip text without scissor rects, useful for doing a lot of text with few drawcalls

<img width="400" alt="Screenshot 2024-03-08 at 2 54 36 PM" src="https://github.com/cedric-h/linear-webgl/assets/25539554/b2b341c6-8abb-47b1-abda-5edf6d4fda09">


## quad squad

| **link**                                                                       | **desc**                                                                                                                       |
|--------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------|
| [quad           ](https://cedric-h.github.io/linear-webgl/quad)                | premultiplied alpha                                                                                                            |
| [quad-blur      ](https://cedric-h.github.io/linear-webgl/quad_blur)           | separable gaussian blur                                                                                                        |
| [quad-blur-depth](https://cedric-h.github.io/linear-webgl/quad_blur_depth)     | separable gaussian blur + depth texture attached to rendertarget                                                               |
| [quad-shadow    ](https://cedric-h.github.io/linear-webgl/quad_shadow)         | demonstrates prebaking shadow for static geometry so you don't need to redo every frame -- can be easier for layering as well. |
| [quad-woosh     ](https://cedric-h.github.io/linear-webgl/quad_woosh)          | some fun with feedback transforms                                                                                              |

<img width="400" alt="Screenshot 2024-03-10 at 11 34 47 PM" src="https://github.com/cedric-h/linear-webgl/assets/25539554/9b6be17c-e290-4ac5-8dc9-2e483ac13545">


## ✨ texture time ✨

| **link**                                                                       | **desc**                                                                                                                       |
|--------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------|
| [image       ](https://cedric-h.github.io/linear-webgl/image.html)             | emoji -> canvas -> texture -> quad -> screen                                                                                   |
| [image_atlas ](https://cedric-h.github.io/linear-webgl/image_atlas.html)       | like "image," but demonstrates how to use several images on a single atlas.                                                    |
| [galaxy      ](https://cedric-h.github.io/linear-webgl/galaxy.html)            | see above + fun with gaussian blur                                                                                             |


