with (import <nixpkgs> {});
  mkShell {
    buildInputs =  [ 
      glibc
      ];
}
