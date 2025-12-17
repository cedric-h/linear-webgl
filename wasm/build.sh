clear && time clang --target=wasm32 \
          -O3 \
          -g \
          -flto \
          -nostdlib \
          -Wl,--no-entry \
          -Wl,--lto-O3 \
          -Wl,--allow-undefined \
          -Wall \
          -mbulk-memory \
          -o hex.wasm \
          hex.c && echo 'compiled hex.wasm\n'

