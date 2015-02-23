{ stdenv ? (import <nixpkgs> {}).stdenv }:

stdenv.mkDerivation {
  name = "ccsds-tool";
  src = ./.;
  buildInputs = [ ];
  installPhase = ''
    mkdir -p $out/bin
    cp ccsds-tool-libclang $out/bin
  '';
}

