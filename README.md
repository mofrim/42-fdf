# 42-fdf

# Todo list

- [x] draw_map_points_size with a circle not a rectangle 
- [x] control height-exaggeration. init with a good compromise value.
- [x] implement: a centering-algorithm for the map in the window
- [x] fix rotation problem
- [x] find performance improvements for bigger maps, like drawing only very
2nd pixel or what not.
- [x] add toggle markers control key
- [x] implement: 'r' resets to beginning
- [x] implement: 'i' shows isometric view
- [x] color_map for different z-values.
- [x] implement color map reading in read_map !!!!
- [ ] add toggle option for color / nocolor drawing of map
- [ ] do what subject pdf wants: esc should close window (in a clean way!),
  clicking on the cross too, minimizing and switching to other window should
  not be a problem.
- [ ] make the initial_resizing/scaling more intelligent and compatible to
  large maps
- [ ] **ensure** if rotation problem is really solved
- [ ] write the `init_mxv()` function!
- [ ] left-hand-right-hand coordinate system problem.
- [ ] norminette.
- [ ] draw a small coordinate system on the screen and rotate it along with
      the map.

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

  - [x] draw_map_points_size with a circle not a rectangle 
  - [x] control height-exaggeration. init with a good compromise value.
  - [x] implement: a centering-algorithm for the map in the window
  - [x] fix rotation problem
  - [ ] do what subject pdf wants: esc should close window (in a clean way!),
    clicking on the cross too, minimizing and switching to other window should
    not be a problem.
  - [ ] add toggle markers control key
  - [ ] make the initial_resizing/scaling more intelligent and compatible to
    large maps
  - [ ] **ensure** if rotation problem is really solved
  - [x] implement: 'r' resets to beginning
  - [x] implement: 'i' shows isometric view
  - [ ] implement: 'p' shows current map parameters
  - [ ] write the `init_mxv()` function!
  - [ ] left-hand-right-hand coordinate system problem.
  - [ ] norminette.
  - [ ] implement color map reading in read_map !!!!
  - [ ] color_map for different z-values.
  - [ ] draw a small coordinate system on the screen and rotate it along with
        the map.
  - [ ] find performance improvements for bigger maps, like drawing only very
    2nd pixel or what not.


- **[2024-09-19 10:19]** `draw_map_points_size_circle()`. how to draw a circle?
    
  + size = 1: x and y
  + size = 2: x-1, x, x+1 and y-1, y, y+1
  + size = 3: (x-2 ... x+2, y) and (x-1 ... x+1, y+1) and (x, y+2) also (x-1 ...
    x+1, y-1) and (x, y-2) should be drawn.
  + size = 4: (x-3 ... x+3, y) and now: (x-3 ... x+3, y+1) ...

  => i would need some kind of pixelized circle pixel generator function which
  outputs a list of points to be drawn which will as close as possible represent
  a circle.

- **[2024-09-20 09:04]** the solution to the circle draw "problem":

  ```c
  t_pxlcloud	*calc_disk_cloud(int x, int y, int radius)
  {
    t_pxlcloud	*pc;
    int			i;
    int			j;

    pc = NULL;
    i = -1;
    while (++i < radius)
    {
      j = -1;
      while (++j < sqrt(radius * radius - i * i))  // <-- this is it!
      {
        pxcl_add_back(&pc, pxcl_new(x - i, y + j));
        pxcl_add_back(&pc, pxcl_new(x - i, y - j));
        pxcl_add_back(&pc, pxcl_new(x + i, y + j));
        pxcl_add_back(&pc, pxcl_new(x + i, y - j));
      }
    }
    return (pc);
  }
  ```
- **[2024-09-21 16:22]** so much progress!!! first of all i got different fonts
  working by adding my `~/.fonts` to X11-fontdirspath by `xset +fp ~/.fonts`.
  Then i could use `xlsfonts` to list all available fonts: `xlsfonts -l | less`
  and choose one.
  
- **[2024-09-23 08:30]** Found the performance killer in my implementation:
  `generate_linelst()`! Of course! There is way too much mallocing going on in
  here. Here is the proof found by benchmarking:

      time for generate linelst: 3.067954
      time for drawing linelst: 0.007492

  => drawing all the lines is actually pretty fast. So. If i would like to stick
  to a linelst kind of structure i could use an array of lines and do only one
  alloc of this whole array. or, even better, draw every line directly without
  any intermediate storage in a freshly mallocced `t_line` struct.

- **[2024-09-23 12:33]** well, i have colors running, in principle one
  **Problem** remains: if i have a gradient, i will now also have to ensure that
  lines are always drawn in the ascending direction. or, i have to include
  z-values in the draw_line algorithm, even though they are not used in printing
  to screen, i have to determine the color of the current pixel using them.
  sounds like an idea....

- **[2024-09-23 14:00]** OKay. i quickly hacked together some gradient
  generation alog. but now i am facing a real big problem again: when rotate and
  project my map, the z-values become any negative and positive values.
  depending on the projection. so the coloring gradient is not constant but
  changes on each line drawn depending on the projection -> somehow i have to
  save and connect the original z-values to each point and line between the
  points.

- **[2024-09-24 22:23]** cylindrical projection... claude says:
  ```c
  #include <stdio.h>
  #include <math.h>

  #define PI 3.14159265358979323846

  // Function to perform cylindrical projection
  void cylindrical_projection(int num_points, float *x, float *y, float *z, float *x_proj, float *y_proj) {
      for (int i = 0; i < num_points; i++) {
          float r = sqrt(x[i] * x[i] + y[i] * y[i]);
          float theta = atan2(y[i], x[i]);
          x_proj[i] = r * cos(theta);
          y_proj[i] = z[i];
      }
  }
  ```

  The key steps for the cylindrical projection are:

  1. Iterate through the 3D model points (x, y, z).
  2. Calculate the radial distance `r` from the origin to the point using `sqrt(x^2 + y^2)`.
  3. Calculate the angle `theta` between the positive x-axis and the point using `atan2(y, x)`.
  4. The new x-coordinate is `r * cos(theta)`, and the new y-coordinate is `z`, effectively projecting the 3D point onto a cylinder.
  5. Store the new x and y coordinates in the `x_proj` and `y_proj` arrays, respectively.

  The example usage in the `main()` function demonstrates how to initialize a sample 3D model, call the `cylindrical_projection()` function, and then draw the projected 2D model (which is already solved).

  Let me know if you have any other questions!
