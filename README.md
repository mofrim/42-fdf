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
