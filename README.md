# 42-fdf

# Logbook

- [2024-09-06 07:36] What i knew beforehand, as i use NixOS, **and** a tiling
  wayland compositor, using the MiniLibX library, written for X11 won't be easy.
  The `shell.nix` for building the  library:

  ```nix
  { pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
      name = "fdf-env";
  
      buildInputs = with pkgs; [
          libbsd
              xorg.libXext
              xorg.libX11.dev
      ];
  shellHook = ''
          CC=gcc
          NIX11="${pkgs.xorg.libX11.dev}/include"
          '';
  }
  ```

  The $NIX11 env-var was i used to patch the `./configure` script and manually set:
  
  ```sh
  local xlib_inc=$NIX11
  ```
- [2024-09-06 13:48] The main problem remains: when i run this test under my
  Windowmanager etc. setup i don't see any window popping up:

  ```c
  #include "mlx.h"
  #include <stdlib.h>
  #include <time.h>
  #include <stdio.h>

  void *mlx;
  void *win1;

  int main()
  {
      srandom(time(0));
      mlx = mlx_init();
      win1 = mlx_new_window(mlx,300,300,"win1");
      if (!win1)
          printf("NULL!\n");
      mlx_loop(mlx);
  }
  ```
  Running this in a VM with a normal X11 setup a window is popping up.

- [2024-09-09 09:50] Okay. Had to comment out `mlx_int_anti_resize_win()` function in
  `mlx_new_window.c` -> TODO maybe file this as issue with hyprland because
  making windows non-resizable is archieved through setting WMHints which can be
  ignored. But just not showing them is not desired behaviour, imho.

- [2024-09-09 20:22] Time to outline the parsing process:

    1) Read the mapfile into an 2d integer array and do some error checking
    2) From the int-array generate a linked list of 3dim vectors. Introduce an
       extra field `edge_vertex` for vertices sitting on the edges of the map,
       because they will have less connection lines.
    3) Maybe do it differently. Create a struct t_vec { x,y,z}. so the map will
       be a 2d t_vec array.

- [2024-09-10 21:09] Diving into LinAlg... But the function i need nevertheless
  is some kind of `draw_map` function which draws all the lines derived from the
  `t_map` member `t_vec **vec_map`. but how should this function look like? i
  want it to be versatile. this means:
  
  + it should be working for 3d vectors as well as the first testing case of 2d
    vecs.
  + it should allow the use of different distance functions (maybe make this a
    param of draw_map).
  + maybe because of the first point i first need to introduce a
    matrix-multiplication in order to project the read-in map on the xy-plane by
    mulitplying with
    ```math
    \begin{pmatrix} 1 & 0 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 0 \end{pmatrix}
    ```
- [2024-09-10 21:55] OK. matrix-multiplication first implementation is done. now
  i want to draw just the map-grid with thick points. What immediately pops into
  my mind is: How do i set the distance between points? I realized: This is the
  question of the zoom level!!! And i really want to implement at least zooming
  and padding....

- [2024-09-10 23:14]
  [Wikipedia](https://en.wikipedia.org/wiki/Isometric_projection) says the
  isometric projection for a vector
  ```math
  \vec{v} = (v_1, v_2, v_3)^T
  ```
  is defined by the matrix-multiplication chain:
  ```math
  \begin{pmatrix} 1&0&0\\0&1&0\\0&0&0\end{pmatrix} \begin{pmatrix} 1&0&0\\1&\cos\alpha&\sin\alpha\\0&-sin\alpha&\cos\alpha\end{pmatrix} \begin{pmatrix} \cos\beta&0&-sin\beta\\0&1&0\\\sin\beta&0&\cos\beta\end{pmatrix} \vec{v}
  ```
  where
  ```math
  \begin{align}
  \alpha &= \arcsin(\tan 30^\degree) \\
  \beta &= 45^\degree 
  \end{align}
  ```
  The whole matrix product equals to
  ```math
  \begin{pmatrix} \sqrt{3}&0&-\sqrt{3}\\1&2&1\\0&0&0 \end{pmatrix}
  ```
- [2024-09-12 16:45] I need to somehow normalize my map before every trafo. That
  means

    1) move it back to origin
    2) normalize vectors
    3) put it back to its original position
    4) ... or, somehow integrate this into my trafo functions.

- [2024-09-13 00:30] Continue tomorrow. Angles also need to persist. Furthermore
  i should make up a way for centering the whole map on screen.
