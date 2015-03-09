{ stdenv ? (import <nixpkgs> {}).stdenv
, ccsds-tool ? (import ../default.nix {})
}:
stdenv.mkDerivation {
  name = "serialize-test";
  buildInputs = [ ccsds-tool ];
  src = ./.;
}
