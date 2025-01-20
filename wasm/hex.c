#include <stdint.h>
#include <stdbool.h>

#define WASM_EXPORT(x) __attribute__((export_name(x)))

extern int gl_bindBuffer(unsigned long, unsigned long);
extern int gl_bufferData(unsigned long, void *, unsigned long, unsigned long);
extern int gl_vertexAttribPointer(unsigned long, unsigned long, unsigned long, bool, unsigned long, unsigned long);
extern int gl_drawElements(unsigned long, unsigned long, unsigned long, unsigned long);

extern int putchar(int);
extern float sqrtf(float);
extern float cosf(float);
extern float sinf(float);
extern int gl_createBuffer();
extern int gl_createShader(unsigned long);
extern int gl_shaderSource(unsigned long, char *);
extern int gl_compileShader(unsigned long);
extern int gl_getShaderParameter(void);
extern int gl_getShaderInfoLog(void);
extern int gl_createProgram(void);
extern int gl_attachShader(unsigned long, unsigned long);
extern int gl_linkProgram(unsigned long);
extern int gl_getProgramParameter(void);
extern int gl_getProgramInfoLog(void);
extern int gl_getActiveAttrib(void);
extern int gl_getAttribLocation(unsigned long, char *);
extern int gl_getActiveUniform(void);
extern int gl_getUniformLocation(unsigned long, char *);
extern int gl_createTexture(void);
extern int gl_bindTexture(void);
extern int gl_texImage2D(void);
extern int gl_texParameteri(void);
extern int gl_blendFunc(unsigned long, unsigned long);
extern int gl_enable(int);
extern int gl_depthFunc(int);
extern int gl_clearColor(float, float, float, float);
extern int gl_clear(unsigned long);
extern int gl_useProgram(unsigned long);
extern int gl_enableVertexAttribArray(unsigned long);
extern int gl_uniform2f(unsigned long, float, float);
extern int gl_uniform1f(unsigned long, float);
extern int gl_viewport(float, float, float, float);

#define gl_ONE                  1
#define gl_ONE_MINUS_SRC_ALPHA  771
#define gl_BLEND                3042
#define gl_DEPTH_TEST           2929
#define gl_LEQUAL               515
#define gl_COLOR_BUFFER_BIT     (1 << 14)
#define gl_DEPTH_BUFFER_BIT     (1 << 8)
#define gl_VERTEX_SHADER        35633
#define gl_FRAGMENT_SHADER      35632
#define gl_ARRAY_BUFFER         34962
#define gl_STATIC_DRAW          35044
#define gl_ELEMENT_ARRAY_BUFFER 34963
#define gl_UNSIGNED_BYTE        5121
#define gl_UNSIGNED_SHORT       5123
#define gl_FLOAT                5126
#define gl_TRIANGLES            4

#define M_PI 3.141592653589793

unsigned long program;
unsigned long shaders_geo_a_pos;
unsigned long shaders_geo_a_col;
unsigned long shaders_geo_u_camera_pos;
unsigned long shaders_geo_u_camera_zoom;

unsigned long geo_vbuf_pos;
unsigned long geo_vbuf_col;
unsigned long geo_ibuf;

struct {
    struct { float x, y; } pos;
    float zoom;
} camera = {
    .pos = { 0, 0 },
    .zoom = 1
};
struct { float size_x, size_y; } canvas = {0};
struct {
    bool  mouse_down;
    float mouse_down_x;
    float mouse_down_y;
    float mouse_down_camera_x;
    float mouse_down_camera_y;

    float mouse_world_x;
    float mouse_world_y;
    float mouse_screen_x;
    float mouse_screen_y;
} input = {0};
void input_update_mouse_world(void) {
    input.mouse_world_x = (input.mouse_screen_x - camera.pos.x)/camera.zoom;
    input.mouse_world_y = (input.mouse_screen_y - camera.pos.y)/camera.zoom;
}

WASM_EXPORT("mousedown")
void mousedown(float offset_x, float offset_y) {
    input.mouse_world_x = input.mouse_down_x = offset_x;
    input.mouse_world_y = input.mouse_down_y = offset_y;
    input_update_mouse_world();
    input.mouse_down_camera_x = camera.pos.x;
    input.mouse_down_camera_y = camera.pos.y;
    input.mouse_down = true;
}

WASM_EXPORT("mouseup")
void mouseup(void) {
    input.mouse_down = false;
}

WASM_EXPORT("resize")
void resize(float size_x, float size_y) {
    canvas.size_x = size_x;
    canvas.size_y = size_y;
    gl_viewport(0, 0, size_x, size_y);
}

WASM_EXPORT("mousemove")
int mousemove(float offset_x, float offset_y) {
    input.mouse_screen_x = offset_x;
    input.mouse_screen_y = offset_y;
    input_update_mouse_world();
    if (!input.mouse_down) { return 0; }

    float delta_x = offset_x - input.mouse_down_x;
    float delta_y = offset_y - input.mouse_down_y;
    camera.pos.x = input.mouse_down_camera_x + delta_x;
    camera.pos.y = input.mouse_down_camera_y + delta_y;
    input_update_mouse_world();
    return 1;
}

WASM_EXPORT("mousewheel")
int mousewheel(float zoom_delta_y) {

    float next_zoom = camera.zoom * (1 - zoom_delta_y * 0.0004);
    // next_zoom = max(0.15, next_zoom);

    /* offset camera.x such that it stays centered around the mouse,
     * accounting for the new zoom */
    {
        float x_t = input.mouse_world_x / canvas.size_x;
        float  nowSizeX = canvas.size_x * camera.zoom;
        float nextSizeX = canvas.size_x * next_zoom;
        float deltaX = nextSizeX - nowSizeX;
        camera.pos.x -= deltaX * x_t;
    }

    /* ditto on the Y axis; keep the mouse as the focal point */
    {
        float y_t = input.mouse_world_y / canvas.size_y;
        float  nowSizeY = canvas.size_y * camera.zoom;
        float nextSizeY = canvas.size_y * next_zoom;
        float deltaY = nextSizeY - nowSizeY;
        camera.pos.y -= deltaY * y_t;
    }

    camera.zoom = next_zoom;
    input_update_mouse_world();

    return 1;
}

WASM_EXPORT("init")
void init(void) {
    geo_vbuf_pos = gl_createBuffer();
    geo_vbuf_col = gl_createBuffer();
    geo_ibuf     = gl_createBuffer();

    program = gl_createProgram();

    unsigned long vertex_shader = gl_createShader(gl_VERTEX_SHADER);
    gl_shaderSource(
        vertex_shader, 
        "attribute vec3 a_pos;"
        "attribute vec4 a_col;"

        "varying vec4 v_col;"

        "uniform vec2  u_camera_pos;"
        "uniform float u_camera_zoom;"

        "void main() {"
        "    gl_Position = vec4(a_pos.xy*u_camera_zoom + u_camera_pos, a_pos.z, 1);"
        "    v_col = a_col;"
        "}"
    );
    gl_compileShader(vertex_shader);
    gl_attachShader(program, vertex_shader);

    unsigned long fragment_shader = gl_createShader(gl_FRAGMENT_SHADER);
    gl_shaderSource(
        fragment_shader, 
        "precision mediump float;"

        "varying vec4 v_col;"

        "void main() {"
        "    gl_FragColor = v_col;"
        "}"
    );
    gl_compileShader(fragment_shader);
    gl_attachShader(program, fragment_shader);

    gl_linkProgram(program);

    shaders_geo_a_pos = gl_getAttribLocation(program, "a_pos");
    shaders_geo_a_col = gl_getAttribLocation(program, "a_col");
    shaders_geo_u_camera_pos  = gl_getUniformLocation(program, "u_camera_pos" );
    shaders_geo_u_camera_zoom = gl_getUniformLocation(program, "u_camera_zoom");
}

uint16_t geo_idx[1 << 11];
float    geo_pos[1 << 11];
uint8_t  geo_col[1 << 11];
uint16_t *geo_idx_wtr = geo_idx;
float    *geo_pos_wtr = geo_pos;
uint8_t  *geo_col_wtr = geo_col;

void draw_hex(float px, float py, float size, float thickness) {
    uint32_t vbuf_i = (geo_pos_wtr - geo_pos) / 3;

    float outer_radius = size + thickness * 0.5;
    float inner_radius = size - thickness * 0.5;
    for (int i = 0; i < 7; i++) {
        float x = cosf((float)(i) / 6 * M_PI * 2);
        float y = sinf((float)(i) / 6 * M_PI * 2);

        float ar = canvas.size_x / canvas.size_y;
        *geo_pos_wtr++ = px + x * inner_radius, *geo_pos_wtr++ = py + y * inner_radius * ar, *geo_pos_wtr++ = 0.1;
        *geo_pos_wtr++ = px + x * outer_radius, *geo_pos_wtr++ = py + y * outer_radius * ar, *geo_pos_wtr++ = 0.1;
        *geo_col_wtr++ = 255, *geo_col_wtr++ = 165, *geo_col_wtr++ = 50, *geo_col_wtr++ = 255;
        *geo_col_wtr++ = 255, *geo_col_wtr++ = 165, *geo_col_wtr++ = 50, *geo_col_wtr++ = 255;
    }

    for (int i = 0; i < 6; i++) {
        *geo_idx_wtr++ = vbuf_i + 0, *geo_idx_wtr++ = vbuf_i + 1, *geo_idx_wtr++ = vbuf_i + 2;
        *geo_idx_wtr++ = vbuf_i + 2, *geo_idx_wtr++ = vbuf_i + 3, *geo_idx_wtr++ = vbuf_i + 1;
        vbuf_i += 2;
    }
}

void draw_line(float x0, float y0, float x1, float y1, float thickness) {
    *geo_col_wtr++ = 255, *geo_col_wtr++ = 165, *geo_col_wtr++ = 50, *geo_col_wtr++ = 255;
    *geo_col_wtr++ = 255, *geo_col_wtr++ = 165, *geo_col_wtr++ = 50, *geo_col_wtr++ = 255;
    *geo_col_wtr++ = 255, *geo_col_wtr++ = 165, *geo_col_wtr++ = 50, *geo_col_wtr++ = 255;
    *geo_col_wtr++ = 255, *geo_col_wtr++ = 165, *geo_col_wtr++ = 50, *geo_col_wtr++ = 255;

    float ar = canvas.size_x / canvas.size_y;

    float dx = x0 - x1;
    float dy = y0 - y1;
    float dlen = sqrtf(dx*dx + dy*dy);
    float px = -dy / dlen * thickness*0.5;
    float py =  dx / dlen * thickness*0.5;

    uint32_t vbuf_i = (geo_pos_wtr - geo_pos) / 3;
    *geo_pos_wtr++ = x0 + px, *geo_pos_wtr++ = (y0 + py)*ar, *geo_pos_wtr++ = 0.1;
    *geo_pos_wtr++ = x0 - px, *geo_pos_wtr++ = (y0 - py)*ar, *geo_pos_wtr++ = 0.1;
    *geo_pos_wtr++ = x1 + px, *geo_pos_wtr++ = (y1 + py)*ar, *geo_pos_wtr++ = 0.1;
    *geo_pos_wtr++ = x1 - px, *geo_pos_wtr++ = (y1 - py)*ar, *geo_pos_wtr++ = 0.1;

    *geo_idx_wtr++ = vbuf_i + 0, *geo_idx_wtr++ = vbuf_i + 1, *geo_idx_wtr++ = vbuf_i + 2;
    *geo_idx_wtr++ = vbuf_i + 2, *geo_idx_wtr++ = vbuf_i + 3, *geo_idx_wtr++ = vbuf_i + 1;
}

WASM_EXPORT("frame")
void frame(double timestamp) {

    geo_idx_wtr = geo_idx;
    geo_pos_wtr = geo_pos;
    geo_col_wtr = geo_col;

    draw_hex(0, 0, 0.15, 0.01);
    draw_line(0.095, 0.095, 0.6, 0.41, 0.01);

    /* set up premultiplied alpha */
    gl_blendFunc(gl_ONE, gl_ONE_MINUS_SRC_ALPHA);
    gl_enable(gl_BLEND);

    gl_enable(gl_DEPTH_TEST);
    gl_depthFunc(gl_LEQUAL);

    /* clear all */
    gl_clearColor(30.0f/255.0f, 40.0f/255.0f, 50.0f/255.0f, 255.0f/255.0f);
    gl_clear(gl_COLOR_BUFFER_BIT | gl_DEPTH_BUFFER_BIT);

    /* geo pass */
    {
        gl_useProgram(program);
        gl_enableVertexAttribArray(shaders_geo_a_pos);
        gl_enableVertexAttribArray(shaders_geo_a_col);

        /* upload camera position */
        {
            gl_uniform2f(
                shaders_geo_u_camera_pos,
                2*(0 + camera.pos.x / canvas.size_x) - 1,
                2*(1 - camera.pos.y / canvas.size_y) - 1
            );
            gl_uniform1f(shaders_geo_u_camera_zoom, camera.zoom);
        }

        /* upload/bind geometry */
        {
            gl_bindBuffer(gl_ARRAY_BUFFER, geo_vbuf_pos);
            gl_bufferData(gl_ARRAY_BUFFER, geo_pos, sizeof(float)*(geo_pos_wtr - geo_pos), gl_STATIC_DRAW);
            gl_vertexAttribPointer(shaders_geo_a_pos, 3, gl_FLOAT, false, 0, 0);

            gl_bindBuffer(gl_ARRAY_BUFFER, geo_vbuf_col);
            gl_bufferData(gl_ARRAY_BUFFER, geo_col, geo_col_wtr - geo_col, gl_STATIC_DRAW);
            gl_vertexAttribPointer(shaders_geo_a_col, 4, gl_UNSIGNED_BYTE, true, 0, 0);

            gl_bindBuffer(gl_ELEMENT_ARRAY_BUFFER, geo_ibuf);
            gl_bufferData(gl_ELEMENT_ARRAY_BUFFER, geo_idx, sizeof(uint16_t)*(geo_idx_wtr - geo_idx), gl_STATIC_DRAW);
        }

        gl_drawElements(gl_TRIANGLES, geo_idx_wtr - geo_idx, gl_UNSIGNED_SHORT, 0);
    }
}
