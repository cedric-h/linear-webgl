EDIT: this started out with the lofty goals stated below, and quickly just became my scratchpad where I test out random ideas, only most of which are WebGL-related ...

# webgl demos in a single file, the way god intended

If you ask me, any attempt to make an abstraction over WebGL ... only makes it more difficult to use.

But don't take it from me, let's look at the numbers:

- Higher level abstractions [suffer from performance issues](https://benchmarks.slaylines.io)

- Lower level abstractions like [picogl](https://tsherif.github.io/picogl.js/), [twgl](https://twgljs.org/) and [regl](https://regl-project.github.io/regl/) hardly offer enough to be worth the marginally larger bundle size. (coming in at 67k, 52k, and 86k respectively ... [i fit a minimal minecraft clone in under 96kb](https://github.com/cedric-h/cedcraft) and [you should really only block on the loading of 650kb max, ever](https://infrequently.org/2024/01/performance-inequality-gap-2024/))

WebGPU will be nice, but [I've been waiting for it since 2018](https://github.com/cedric-h/stockRPG/blob/master/src/wgpu/game_renderer.rs). It's only just been rolled out in a single browser, it will be forever before it makes it to low-end mobile devices, and that's where performance (and therefore clever graphics programming) matters the most.

So raw, unadulterated WebGL it is. [Webglfundamentals.org](https://webglfundamentals.org) is great, but it's just that: fundamentals. I want scrollbars and dropshadows and examples where those "fundamentals" are used to do __real shit__.

Ergo: flat, linear WebGL.

Other useful resources in the same vein:
- [WebGL2Samples](https://github.com/WebGLSamples/WebGL2Samples)
- [Webglfundamentals.org](https://webglfundamentals.org) 
- [Webgl2fundamentals.org](https://webgl2fundamentals.org/) 

## simple

| **link**                                                                       | **desc**                                                                                                              |
|--------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------------|
| [tri        ](https://cedric-h.github.io/linear-webgl/tri.html)                | triangle; starting-off point; _well, I tri-d._                                                                        |
| [lines      ](https://cedric-h.github.io/linear-webgl/lines.html)              | shows how to do constant-screenspace-thickness 3D-based lines.                                                        |
| [gazebo     ](https://cedric-h.github.io/linear-webgl/gazebo.html)             | simple OBJ model                                                                                                      |

<img width="400" alt="Screenshot 2024-03-08 at 2 54 01 PM" src="https://github.com/cedric-h/linear-webgl/assets/25539554/b1d41550-0d5b-4051-af55-6846f1738175">


## from cube to simple 3D editor

| **link**                                                                       | **desc**                                                                                                              |
|--------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------------|
| [cube       ](https://cedric-h.github.io/linear-webgl/cube.html)               | it's a cube.                                                                                                          |
| [cube grid  ](https://cedric-h.github.io/linear-webgl/cube_grid.html)          | this cube has a grid!                                                                                                 |
| [cube camera](https://cedric-h.github.io/linear-webgl/cube_camera.html)        | this cube has a grid AND mouse-based camera controls!                                                                 |
| [cube gizmos](https://cedric-h.github.io/linear-webgl/cube_gizmos.html)        | cube, grid, mouse-based camera controls, and "gizmos" (translate, rotate, scale                                       |
| [cube editor](https://cedric-h.github.io/linear-webgl/cube_editor.html)        | everything in gizmos + support for multiple things, undo/redo, etc.                                                   |

<img width="400"  alt="Screenshot 2024-05-06 at 12 48 29 PM" src="https://github.com/cedric-h/linear-webgl/assets/25539554/0a29393a-fd07-4b64-bdca-1bc77735678f">


## shadows and lighting

| **link**                                                                       | **desc**                                                                                                              |
|--------------------------------------------------------------------------------|-----------------------------------------------------------------------------------------------------------------------|
| [shadow       ](https://cedric-h.github.io/linear-webgl/shadow.html)           | super simple shadow with no PCF, etc. just reprojection                                                               |
| [shadow_bake  ](https://cedric-h.github.io/linear-webgl/shadow_bake.html)      | soft shadows + ambient occlusion + shadows dynamically from progressive lightmap                                      |
| [paint        ](https://cedric-h.github.io/linear-webgl/shadow.html)           | technically NOT shadows/lighting, but can be helpful to read alongside them. also silly, messy, and fun!              |

<img width="400"  alt="Screenshot 2024-05-06 at 12 45 15 PM" src="https://github.com/cedric-h/linear-webgl/assets/25539554/293a9cff-318e-48b1-8859-baeb620c8317">

https://github.com/cedric-h/linear-webgl/assets/25539554/359ae242-8e6a-483d-a227-658fd1cc6fe5



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

| **link**                                                                          | **desc**                                                                                                                  |
|-----------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------|
| [image       ](https://cedric-h.github.io/linear-webgl/image.html)                | emoji -> canvas -> texture -> quad -> screen                                                                              |
| [image_atlas ](https://cedric-h.github.io/linear-webgl/image_atlas.html)          | like "image," but demonstrates how to use several images on a single atlas.                                               |
| [galaxy      ](https://cedric-h.github.io/linear-webgl/image_atlas_prebake.html)  | see above + fun with gaussian blur                                                                                        |
| [skybox      ](https://cedric-h.github.io/linear-webgl/skybox.html)               | all that, inside a spinning cube!                                                                                         |
| [shadow      ](https://cedric-h.github.io/linear-webgl/image_generate_shadow.html)| has a one-shot function which adds a (customizable) shadow to a texture. pretty handy!                                    |

<img width="400" alt="Screenshot 2024-06-04 at 2 32 42 PM" src="https://github.com/cedric-h/linear-webgl/assets/25539554/2296cf76-d1d5-4d39-9665-8952e68395ec">
<img width="400"  alt="Screenshot 2024-05-06 at 12 49 59 PM" src="https://github.com/cedric-h/linear-webgl/assets/25539554/f8bcb3ee-8e0c-4da9-bc79-739b839778aa">

## 🚀 instancing 🚀

| **link**                                                                        | **desc**                                                                                                                       |
|---------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------|
| [pulling_texture](https://cedric-h.github.io/linear-webgl/pulling_texture.html) | useful when your instances need random access to a buffer of data (e.g. compute-type things)
| [pulling_buffer ](https://cedric-h.github.io/linear-webgl/pulling_buffer.html)  | useful when your instances can use sequential data from a buffer; output looks just like pulling_texture
| [graph_slow     ](https://cedric-h.github.io/linear-webgl/graph_slow.html)      | just calls drawLine; naive, slow, CPU-bound graph
| [graph_fast     ](https://cedric-h.github.io/linear-webgl/graph_fast.html)      | exactly the same as graph_slow, but it does the slow part on the GPU.
| [graph_100k     ](https://cedric-h.github.io/linear-webgl/graph_100k.html)      | stress test; graphing 100k datapoints in red, and 2 million in blue. works well on M2 Max
| [graph          ](https://cedric-h.github.io/linear-webgl/graph.html)           | where I keep the actual good up-to-date graph code.

super performant graph, outperforms chart.js, echarts, amcharts by about x100
<img width="400" alt="Screenshot 2024-06-01 at 9 38 09 PM" src="https://github.com/cedric-h/linear-webgl/assets/25539554/5b609b5f-f56e-4e10-8467-c6ca43dced0c">

# errata

I'll fix these eventually, but

I say "high-retina" in almost every demo, where I should say "high-resolution retina" (one brain skip, copy/pasted a million times)

paint.html is the only demo which has a touchscreen rotatable camera, and almost the only demo where the camera doesn't skip if you rotate up too far. (That is just a one-line fix after `yaw =`.) More work is necessary for many demos to make sure they work on mobile. EDIT: some issues with the touch controls here, needs a rework. Probably need to completely separate this codepath from mouse controls.

On the topic of camera controls, scroll_thick.html and sphere_texture.html have _much smoother_ camera controls than cube_camera, cube_grid, cube_editor, etc. Also probably some other demos which use that camera code outside of the cube family which I have forgotten.

I say "set up premultiplied alpha," then do `gl.blendFunc(gl.SRC_ALPHA, gl.ONE_MINUS_DST_ALPHA)` but the way premultiplied alpha works, the color should be multiplied by ... nothing. `gl.ONE`. It's premultiplied. So I need to audit transparency in a lot of places. Alternatively, I could keep that "premultiplied alpha" blend func, and simply divide `rgb` by `a` in the shader, which may be preferable since premultiplication is lossy. Should note if so though because it's not obvious.

There are some places where things aren't especially "linear" or flat. I do have indirection/object orientation/etc. in some instances. I ought to audit myself to see if I'm doing so tastefully. Or perhaps it simply doesn't matter.

In several .htmls (cube family in particular) `input.released` is commented "true for a frame after up," when it is actually "true for a frame after down." Not as simple as just updating the comment, because `_released` shouldn't be the field name.

Pretty much all of the files have a `let shaders; { }` block, but they switch between `vs_shader`/`fs_shader` vs. `shader_fs`/`shader_vs`, and this should be homogenized.

# errata - optimization
Plenty of matrices are allocated that don't need to be.

Plenty of buffers are recreated every frame when they could be created once at init, and almost everywhere buffers are created dynamically, the TypedArray is created on the fly every frame, and I would prefer to avoid the allocation if possible.

There are examples which do not perform well on my iPhone 8 (2017). Warrants investigation. I suspect the `dampedEvent *= 0.8` could be exacerbating things, should probably use a framerate independent approach there.
