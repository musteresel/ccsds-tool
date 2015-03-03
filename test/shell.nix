{ stdenv ? (import <nixpkgs> {}).stdenv
, ccsds-tool ? (import ../)
}:
stdenv.mkDerivation {
  name = "serialize-test";
  buildInputs = [ ccsds-tool ];
  src = ./.;
}
