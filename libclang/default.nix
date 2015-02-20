{ stdenv ? (import <nixpkgs> {}).stdenv
, clang ? (import <nixpkgs> {}).clang
, llvmPackages ? (import <nixpkgs> {}).llvmPackages}:

stdenv.mkDerivation {
  name = "ccsds-tool-libclang";
  src = ./.;
  buildInputs = [ clang llvmPackages.clang ];
  installPhase = ''
    mkdir -p $out/bin
    cp ccsds-tool-libclang $out/bin
  '';
}
