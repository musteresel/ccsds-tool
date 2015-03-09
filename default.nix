{ stdenv ? (import <nixpkgs> {}).stdenv
, clang ? (import <nixpkgs> {}).clang
, llvmPackages ? (import <nixpkgs> {}).llvmPackages}:

stdenv.mkDerivation {
  name = "ccsds-tool";
  src = ./.;
  buildInputs = [ clang llvmPackages.clang ];
  installPhase = ''make install INSTALL_PATH=$out'';
#    mkdir -p $out/bin
#    cp ccsds-tool $out/bin
#  '';
}
