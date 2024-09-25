{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  name = "fdf-env";

  buildInputs = with pkgs; [
    libbsd
    xorg.libXext
    xorg.libX11.dev
    qt5.qtwayland
  ];

  shellHook = ''
    CC=gcc
    NIX11="${pkgs.xorg.libX11.dev}/include"
    QT_QPA_PLATFORM=wayland
  '';
}
