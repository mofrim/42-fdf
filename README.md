# 42-fdf

# Logbook

- **[2024-09-06 07:36]** What i knew beforehand, as i use NixOS, **and** a tiling
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
- **[2024-09-06 13:48]** The main problem remains: when i run this test under my
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

- **[2024-09-09 09:50]** Okay. Had to comment out `mlx_int_anti_resize_win()` function in
  `mlx_new_window.c` -> TODO maybe file this as issue with hyprland because
  making windows non-resizable is archieved through setting WMHints which can be
  ignored. But just not showing them is not desired behaviour, imho.

- **[2024-09-09 20:22]** Time to outline the parsing process:

    1) Read the mapfile into an 2d integer array and do some error checking
    2) From the int-array generate a linked list of 3dim vectors. Introduce an
       extra field `edge_vertex` for vertices sitting on the edges of the map,
       because they will have less connection lines.
    3) Maybe do it differently. Create a struct t_vec { x,y,z}. so the map will
       be a 2d t_vec array.

- **[2024-09-10 21:09]** Diving into LinAlg... But the function i need nevertheless
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
- **[2024-09-10 21:55]** OK. matrix-multiplication first implementation is done. now
  i want to draw just the map-grid with thick points. What immediately pops into
  my mind is: How do i set the distance between points? I realized: This is the
  question of the zoom level!!! And i really want to implement at least zooming
  and padding....

- **[2024-09-10 23:14]**
  [Wikipedia](https://en.wikipedia.org/wiki/Isometric_projection) says the
  isometric projection for a vector

  ```math
  \vec{v} = (v_1, v_2, v_3)^T
  ```

  is defined by the matrix-multiplication chain of a rotation around z-axis by
  angle beta, rotation around x-axis by alpha and the projection onto the
  xy-plane:

  ```math
  \begin{pmatrix} 1&0&0\\0&1&0\\0&0&0\end{pmatrix} \begin{pmatrix} 1&0&0\\1&\cos\alpha&\sin\alpha\\0&-sin\alpha&\cos\alpha\end{pmatrix} \begin{pmatrix} \cos\beta&0&-sin\beta\\0&1&0\\\sin\beta&0&\cos\beta\end{pmatrix} \vec{v}
  ```
  where

  ```math
  \begin{align}
  \alpha &= \arcsin(\tan 30^\degree) = \arcsin(1/\sqrt{3}) = \arctan(1/\sqrt{2}) \approx 0.61548 \\
  \beta &= 45^\degree = \pi/4
  \end{align}
  ```

  The whole matrix product equals to

  ```math
  \frac{1}{\sqrt{6}} \begin{pmatrix} \sqrt{3}&0&-\sqrt{3}\\1&2&1\\0&0&0 \end{pmatrix}
  ```

- **[2024-09-12 16:45]** I need to somehow normalize my map before every trafo. That
  means

    1) move it back to origin
    2) normalize vectors
    3) put it back to its original position
    4) ... or, somehow integrate this into my trafo functions.

- **[2024-09-13 00:30]** Continue tomorrow. Angles also need to persist. Furthermore
  i should make up a way for centering the whole map on screen.

- **[2024-09-13 07:46]** Or maybe i should just maintain an untranslated copy of the
  whole map, which remains at the origin and is not zoomed  (except from
  initially read values) or projected to the xy-plane. I could call it
  `map_orig` 🤣. Then, whenever the view is updated, translated, zoomed or the
  map should be drawn at all, duplicate `map_orig` and apply this to the map.
  Another **IDEA** for centering the map is: find min_x/y, max_x/y and calculate
  the middle of map by (min_x+max_x)/2 ..., then calculate the difference
  between middle of window (winsize_x/2, winsize_y/2) and translate by that
  values.

- **[2024-09-13 08:02]** Baaaaammmm!!! That's it!!! The last IDEA was really the
  thing! Next steps:

    1) introduce variable for *steepnes** which is the z-coordinate multiplier
       applied to orig_map allowing to have a better distinction for the
       3d-ness.
    2) make the steepness modifiable through interactive (that would involve
       having an `initial_map` where we can apply that to 🤔 otherwise we would
       have to transform the height increase... nope.) So i really have to save
       all the trafo-values applied to my initial_map in order to be able to
       redisplay nicely.
    3) implement the `initial_resize_map` which will be carried out after
       `read_map()` using the some sane values derived from `winsize_x/y`
       (something by `winsize_x/10`) . The question that arises here is that of
       **ascpect ratio**! i want a square to be a square, and a rectangle, a
       rectangle so i have to apply the same
       multiplier to `x` and `y` coordinates. am i right?!?
    4) initially i want the map to be drawn as centered as possible (use the
       above outlined trick for that). but later i would like to allow for
       translation zooming and rotating freestyle (maybe within the window
       boundaries)

- **[2024-09-14 09:56]** Wow. Got so many things right. But there is still a lot
  of work left to do:

    1. solve the shrinking problem. Somehow after multiple rotation along x-axis
       the y-coordinates are more and more decreased. after multiple rotations
       around z-axis the same happens with the x-coordinates. this might be a
       numerical artifact... could avoid this / verify / falsify this hypothesis
       really keeping an original copy of the initial map and apply all trafo on
       it. right now i operate in-place on `mxv->cur_map`.
       **UPDATE:** by now i am investigating if this is a numerical issue. F.ex.
       the exact values in a `rot_x` matrix in my program are:

       ```math
       \begin{pmatrix}
       1.000000 & 0.000000 & 0.000000 \\
       0.000000 & 0.995004 & 0.099833 \\
       0.000000 &-0.099833 & 0.995004
       \end{pmatrix}

       ```
       Hmmm, well, `det(rot_x)=0.999999587905`. This is not exactly one, but also
       numerically pretty close. This cannot be responsible for the rapid
       shrinking i observe 🤔.

    2. maybe a add some more colors (height dependent).

    3. implement some better centering algorithm (and a key shortcut).

    4. find out how to break up the `key_win1` function into smaller pieces.

- **[2024-09-15 23:23]** Tomorrow maybe quickly implement a ft_printf for float
  by using `(int)var` as the integer part and some dirty hack using
  multiplications by powers of ten and the precission field for printing stuff
  after the decimal. Ah, and: it is definitely due to the numerical errors in
  the rotations matrices that i witness this shrinking.

- **[2024-09-19 09:02]** so far so good. fixed the numerical problems by
  accumulating rotation angles and applying rotations always as a whole to the
  original map. in principle everything is running. i am not quite sure about
  what to do about the left-hand-right-hand coordinate system problem. So, here
  is the list of feature i still want to implement / bugs i want to fix / things
  i want to clarify:

    1) left-hand-right-hand coordinate system problem.
    2) norminette.
    3) color_map for different z-values.
    4) control height-exaggeration. init with a good compromise value.
    5) show some info on the screen, like: current zoom, angle, ...
    6) draw a small coordinate system on the screen and rotate it along with the
       map.
    7) draw_map_points_size with a circle not a rectangle!!

- **[2024-09-19 10:19]** `draw_map_points_size_circle()`. how to draw a circle?
    
  + size = 1: x and y
  + size = 2: x-1, x, x+1 and y-1, y, y+1
  + size = 3: (x-2 ... x+2, y) and (x-1 ... x+1, y+1) and (x, y+2) also (x-1 ...
    x+1, y-1) and (x, y-2) should be drawn.
  + size = 4: (x-3 ... x+3, y) and now: (x-3 ... x+3, y+1) ...

  => i would need some kind of pixelized circle pixel generator function which
  outputs a list of points to be drawn which will as close as possible represent
  a circle.


