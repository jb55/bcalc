{ nixpkgs ? import <nixpkgs> {} }:

with nixpkgs;
stdenv.mkDerivation rec {
  name = "bcalc";
  version = "0.1";

  src = ./.;

  installFlags = "PREFIX=$(out)";

  nativeBuildInputs = [ tinycc ];
  buildInputs = [ bison flex ];

  meta = with stdenv.lib; {
    description = "A calculator that understands bitcoin units";
    homepage = "https://github.com/jb55/bcalc";
    maintainers = with maintainers; [ jb55 ];
    license = licenses.mit;
  };
}
