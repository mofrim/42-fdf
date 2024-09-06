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
