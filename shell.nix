{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  nativeBuildInputs = [ 
    pkgs.pkg-config
    pkgs.SDL2
    pkgs.SDL2_image
  ];
}
